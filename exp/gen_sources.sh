#!/bin/bash

if ! [ -d ./sources ]; then
    mkdir sources
    for file in $(ls --file-type | grep "source[0-9]")
    do
        for i in $(seq -f "%02g" 1 20)
        do
            echo ./generator.exe "${file}" "./sources/${file}_${i}.txt"
            ./generator.exe "${file}" "./sources/${file}_${i}.txt"
        done
    done
fi
