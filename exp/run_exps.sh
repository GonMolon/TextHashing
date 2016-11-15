#!/bin/bash

MAKEFILE="../makefile"
SIMEXE="SimCalculator.exe"
RESULTSDIR="results"
BACKUPDIR="results_backup"
SOURCESDIR="sources"

make

echo "Creating directory ${RESULTSDIR}"
if [ -d "${RESULTSDIR}" ]; then
    echo "Found previous results. Creating backup at ${BACKUPDIR}"
    if ! [ -d "${BACKUPDIR}" ]; then
        mkdir "${BACKUPDIR}"
    fi
    mv --backup=t "${RESULTSDIR}" "${BACKUPDIR}/${RESULTSDIR}"
fi
mkdir "${RESULTSDIR}"

echo "Making sources"
./gen_sources.sh

JACCARD_MODES=(jaccard jaccard_hash jaccard_roll)
MINHASH_MODES=(minhash minhash_roll)
SOURCES=(source50 source100 source1000 source10000)

INI_K=6
INC_K=1
MAX_K=12


# Jaccards ==============================================================
echo "Running jaccard modes"
for mode in ${JACCARD_MODES[@]}
do
    for file1 in ${SOURCES[@]}
    do
        for file2 in $(ls ./${SOURCESDIR} --file-type | grep "${file1}_")
        do
            for k in $(seq $INI_K $INC_K $MAX_K)
            do
                seed=$(./seed_gen.exe)
                filetwo="${SOURCESDIR}/${file2}"
                echo "./${SIMEXE} ${file1} ${filetwo} ${mode} -e --k=${k} --seed=${seed}"
                result=$(./${SIMEXE} ${file1} ${filetwo} ${mode} -e --k=${k} --seed=${seed})
                result="${file1}   ${filetwo}   ${result}   ${seed}"
                echo "${result}"
                echo "${result}" >> "${RESULTSDIR}/results"
            done
        done
    done
done


# Minhash ==============================================================

INI_K=6
INC_K=1
MAX_K=12

INI_T=50
INC_T=50
MAX_T=1000

echo "Running minhash modes"
for mode in ${MINHASH_MODES[@]}
do
    for file1 in ${SOURCES[@]}
    do
        for file2 in $(ls ./${SOURCESDIR} --file-type | grep "${file1}_")
        do
            for k in $(seq $INI_K $INC_K $MAX_K)
            do
                for t in $(seq $INI_T $INC_T $MAX_T)
                do
                    seed=$(./seed_gen.exe)
                    filetwo="${SOURCESDIR}/${file2}"
                    echo "./${SIMEXE} ${file1} ${filetwo} ${mode} -e --k=${k} --t=${t} --seed=${seed}"
                    result=$(./${SIMEXE} ${file1} ${filetwo} ${mode} -e --k=${k} --t=${t} --seed=${seed})
                    result="${file1}   ${filetwo}   ${result}   ${seed}"
                    echo "${result}"
                    echo "${result}" >> "${RESULTSDIR}/results"
                done
            done
        done
    done
done

