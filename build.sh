#!/bin/bash
# Generated using BSHA - Build .sh assembler for C++
# GitHub: https://github.com/AlexeyFilich/bsha

if [ "$1" == "--full" ] || [ "$1" == "-f" ]; then
    rm -rf build
fi

[ ! -d build ] && mkdir build

main_should_recompile="False"
total=10
current=1

start=$(date '+%s')

printHeader() {
    perc=$((100 * $current / $total))
    leading=${#perc}
    printf -- "[\e[38;05;2;49;24;27m"
    [ $leading == "1" ] && printf -- "  "
    [ $leading == "2" ] && printf -- " "
    printf -- "$perc\e[0m] Building \e[38;05;3;49;04;27m$1\e[0m\n"
    current=$(($current + 1))
}

checkRecomp() {
    [ ! -d $3 ] && mkdir -p $3
    [ ! -f $2 ] && touch $2
    file_hash=$(md5sum $1)
    last_hash=$(cat $2)
    if [ "$file_hash" != "$last_hash" ]
    then
        main_should_recompile="True"
        recompile="True"
        [ -f $4 ] && rm $4
    else
        printf -- "..... \e[38;05;3;49;04;27m$1\e[0m \e[38;05;10;49;24;27mis up to date\e[0m\n"
    fi
}

checkSuccess() {
    if [ ! -f $1 ]
    then
        echo > $2
        printf -- "\e[38;05;1;49;24;27m-- Compilation failed!\e[0m\n"
        exit 1
    fi
}

printf -- "\e[38;05;2;49;24;27m--\e[0m \e[38;05;2;49;04;27mStarting build process\e[0m\n"
printf -- "\e[38;05;2;49;24;27m-- Compiler: \e[0m \e[38;05;3;49;04;27mgcc\e[0m\n\n"

recompile="False"
printHeader src/Menu.c
checkRecomp src/Menu.c build/src/Menu.hash build/src/ build/src/Menu.o 
if [ $recompile == "True" ]
then
    gcc -c -I"include/" -I"third-party/toolbox/" -I"third-party/tools-storage/include/" -I"third-party/tools-stuff/include/" -L"lib/" src/Menu.c -o build/src/Menu.o 
    checkSuccess build/src/Menu.o build/src/Menu.hash
    echo "$(md5sum src/Menu.c)" > build/src/Menu.hash
fi

recompile="False"
printHeader src/Node.c
checkRecomp src/Node.c build/src/Node.hash build/src/ build/src/Node.o 
if [ $recompile == "True" ]
then
    gcc -c -I"include/" -I"third-party/toolbox/" -I"third-party/tools-storage/include/" -I"third-party/tools-stuff/include/" -L"lib/" src/Node.c -o build/src/Node.o 
    checkSuccess build/src/Node.o build/src/Node.hash
    echo "$(md5sum src/Node.c)" > build/src/Node.hash
fi

recompile="False"
printHeader src/NodeAdd.c
checkRecomp src/NodeAdd.c build/src/NodeAdd.hash build/src/ build/src/NodeAdd.o 
if [ $recompile == "True" ]
then
    gcc -c -I"include/" -I"third-party/toolbox/" -I"third-party/tools-storage/include/" -I"third-party/tools-stuff/include/" -L"lib/" src/NodeAdd.c -o build/src/NodeAdd.o 
    checkSuccess build/src/NodeAdd.o build/src/NodeAdd.hash
    echo "$(md5sum src/NodeAdd.c)" > build/src/NodeAdd.hash
fi

recompile="False"
printHeader src/NodeDeleteAll.c
checkRecomp src/NodeDeleteAll.c build/src/NodeDeleteAll.hash build/src/ build/src/NodeDeleteAll.o 
if [ $recompile == "True" ]
then
    gcc -c -I"include/" -I"third-party/toolbox/" -I"third-party/tools-storage/include/" -I"third-party/tools-stuff/include/" -L"lib/" src/NodeDeleteAll.c -o build/src/NodeDeleteAll.o 
    checkSuccess build/src/NodeDeleteAll.o build/src/NodeDeleteAll.hash
    echo "$(md5sum src/NodeDeleteAll.c)" > build/src/NodeDeleteAll.hash
fi

recompile="False"
printHeader src/NodeEdit.c
checkRecomp src/NodeEdit.c build/src/NodeEdit.hash build/src/ build/src/NodeEdit.o 
if [ $recompile == "True" ]
then
    gcc -c -I"include/" -I"third-party/toolbox/" -I"third-party/tools-storage/include/" -I"third-party/tools-stuff/include/" -L"lib/" src/NodeEdit.c -o build/src/NodeEdit.o 
    checkSuccess build/src/NodeEdit.o build/src/NodeEdit.hash
    echo "$(md5sum src/NodeEdit.c)" > build/src/NodeEdit.hash
fi

recompile="False"
printHeader src/NodeViewNonRecursive.c
checkRecomp src/NodeViewNonRecursive.c build/src/NodeViewNonRecursive.hash build/src/ build/src/NodeViewNonRecursive.o 
if [ $recompile == "True" ]
then
    gcc -c -I"include/" -I"third-party/toolbox/" -I"third-party/tools-storage/include/" -I"third-party/tools-stuff/include/" -L"lib/" src/NodeViewNonRecursive.c -o build/src/NodeViewNonRecursive.o 
    checkSuccess build/src/NodeViewNonRecursive.o build/src/NodeViewNonRecursive.hash
    echo "$(md5sum src/NodeViewNonRecursive.c)" > build/src/NodeViewNonRecursive.hash
fi

recompile="False"
printHeader src/NodeViewRecursive.c
checkRecomp src/NodeViewRecursive.c build/src/NodeViewRecursive.hash build/src/ build/src/NodeViewRecursive.o 
if [ $recompile == "True" ]
then
    gcc -c -I"include/" -I"third-party/toolbox/" -I"third-party/tools-storage/include/" -I"third-party/tools-stuff/include/" -L"lib/" src/NodeViewRecursive.c -o build/src/NodeViewRecursive.o 
    checkSuccess build/src/NodeViewRecursive.o build/src/NodeViewRecursive.hash
    echo "$(md5sum src/NodeViewRecursive.c)" > build/src/NodeViewRecursive.hash
fi

recompile="False"
printHeader src/Utils.c
checkRecomp src/Utils.c build/src/Utils.hash build/src/ build/src/Utils.o 
if [ $recompile == "True" ]
then
    gcc -c -I"include/" -I"third-party/toolbox/" -I"third-party/tools-storage/include/" -I"third-party/tools-stuff/include/" -L"lib/" src/Utils.c -o build/src/Utils.o 
    checkSuccess build/src/Utils.o build/src/Utils.hash
    echo "$(md5sum src/Utils.c)" > build/src/Utils.hash
fi

recompile="False"
printHeader src/Window.c
checkRecomp src/Window.c build/src/Window.hash build/src/ build/src/Window.o 
if [ $recompile == "True" ]
then
    gcc -c -I"include/" -I"third-party/toolbox/" -I"third-party/tools-storage/include/" -I"third-party/tools-stuff/include/" -L"lib/" src/Window.c -o build/src/Window.o 
    checkSuccess build/src/Window.o build/src/Window.hash
    echo "$(md5sum src/Window.c)" > build/src/Window.hash
fi

recompile="False"
printHeader src/main.c
checkRecomp src/main.c build/src/main.hash build/src/ build/src/main.out
if [ $recompile == "True" ] || [ $main_should_recompile == "True" ]
then
    printf -- "..... \e[38;05;3;49;04;27mmain.c\e[0m \e[38;05;10;49;24;27mis updating, because other files have changed\e[0m\n"
    gcc -I"include/" -I"third-party/toolbox/" -I"third-party/tools-storage/include/" -I"third-party/tools-stuff/include/" -L"lib/" src/main.c -o build/src/main.out build/src/Menu.o build/src/Node.o build/src/NodeAdd.o build/src/NodeDeleteAll.o build/src/NodeEdit.o build/src/NodeViewNonRecursive.o build/src/NodeViewRecursive.o build/src/Utils.o build/src/Window.o -lncursesw
    checkSuccess build/src/main.out build/src/main.hash
    echo "$(md5sum src/main.c)" > build/src/main.hash
fi

cp build/src/main.out bin/main

printf -- "\n\e[38;05;2;49;24;27mDone! in \e[0m[38;05;3;49;04;27m$(($(date '+%s') - $start))sec.[0m\n"
