#!/bin/bash

MAKEFILE="makeexp"
SIMEXE="SimCalculator"
RESULTSDIR="results"
BACKUPDIR="results_backup"

echo "Creating directory ${RESULTSDIR}"
if [ -d "${RESULTSDIR}" ]; then
    echo "Found previous results. Creating backup at ${BACKUPDIR}"
    if ! [ -d "${BACKUPDIR}" ]; then
        mkdir "${BACKUPDIR}"
    fi
    mv --backup=t "${RESULTSDIR}" "${BACKUPDIR}/${RESULTSDIR}"
fi
mkdir "${RESULTSDIR}"

echo "Compiling executables"
make ${MAKEFILE}
if [ $? ]; then
    echo "Failed to compile executable"
    exit
fi





JACCARD_MODES=(jaccard jaccard_hash jaccard_roll)
MINHASH_MODES=(minhash minhash_roll)
