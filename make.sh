#!/bin/bash

if [ "$1" == "" ]; then
    echo -e "\033[4musage:\033[0m"
    echo -e "    \033[1m./make.sh [platform] [target...]\033[0m"
    echo -e "you can specify \"all\" as target to make all targets."
    exit 1
fi

platform=$1
if [ "$platform" == windows ]; then
    flag=MinGW
elif [ "$platform" == unix ]; then
    flag=Unix
else
    echo -e "\033[4mUnrecognized platform \"$platform\". Available platforms are:\033[0m"
    echo -e "    \033[1mwindows unix\033[0m"
    exit 1
fi
shift 1

function make_target {
    target=$1
    if [ ! -f "run/$target.cpp" ]; then
        echo -e "\033[4mUnrecognized target \"$target\".\033[0m"
        exit 1
    fi
    cd bin
    ./$target | tee ../plot/$target.asy
    cd ../plot
    asy $target.asy -f pdf
    rm *timfail*
    cd ..
}

git submodule init
git submodule update
cmake -S ./ -B ./bin -G "$flag Makefiles" -DCMAKE_BUILD_TYPE=Release
if [ $? -ne 0 ]; then
    echo -e "\033[4mCMake error, exiting...\033[0m"
    exit 1
fi
cmake --build ./bin/
if [ $? -ne 0 ]; then
    echo -e "\033[4mCompile error, exiting...\033[0m"
    exit 1
fi
if [ "$1" == "all" ]; then
    for target in crowd_safety drones_recognition service_discovery smart_home; do
        make_target $target
    done
else
    for target in "$@"; do
        make_target $target
    done
fi
