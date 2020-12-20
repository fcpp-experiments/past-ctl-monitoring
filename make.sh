#!/bin/bash

if [ "$1" == "" ]; then
    echo -e "\033[4musage:\033[0m"
    echo -e "    \033[1m./make.sh [platform] [target...]\033[0m"
    exit 1
fi

platform=$1
if [ "$platform" == windows ]; then
    flag=MinGW
elif [ "$platform" == unix ]; then
    flag=Unix
else
    echo -e "\033[4mUnrecognized platform. Available platforms are:\033[0m"
    echo -e "    \033[1mwindows unix\033[0m"
    exit 1
fi

git submodule init
git submodule update
cmake -S ./ -B ./build -G "$flag Makefiles" -Wno-dev
cmake --build ./build/
for target in "$@"; do
    cd build
    ./$target | tee ../plot/$target.asy
    cd ../plot
#    sed -i "" -E "s| \(mean-mean\)||g" $target.asy
    asy $target.asy -f pdf
    cd ..
done
