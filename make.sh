#!/bin/bash

if [ "$1" == "" ]; then
    echo -e "\033[4musage:\033[0m"
    echo -e "    \033[1m./make.sh [platform] target...\033[0m"
    echo
    echo -e "platform can be windows or unix and may be omitted for automatic detection."
    echo
    echo -e "available targets are:"
    for f in run/*.cpp; do
        g=`basename $f .cpp`
        echo -en "    \033[1m$g\033[0m"
    done
    echo
    echo -e "you can also specify \033[1mall\033[0m as target to make all targets."
    echo -e "Targets can be substrings demanding builds for all possible expansions."
    exit 1
fi

git submodule init
git submodule update
platform=$1
if [ "$platform" == windows -o "$platform" == unix ]; then
    shift 1
else
    platform=""
fi
fcpp/src/make.sh $platform gui run -O "$@"
rm -rf plot/*timfail* output/raw
