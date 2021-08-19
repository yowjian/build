#!/bin/bash

# Colors
ORANGE='\033[0;33m'
RED='\033[0;31m'
CYAN='\033[0;36m'
CYAN_BOLD='\033[1;36m'
NC='\033[0m'

# Environment
function setup_environment {
    # Directory setup
    [[ ! -d test-runs ]] && mkdir test-runs
    pushd test-runs > /dev/null
    rundir=$(date +%Y-%m-%d-%H-%M-%S) 
    mkdir $rundir
    rundir=$(realpath $rundir)
    popd > /dev/null 

    srcdir=$(realpath .tests)

    # Git repo setup
    [[ ! -d closure ]] && mkdir closure
    pushd closure > /dev/null
    if [[ ! -d program-dependence-graph ]]; then
        git clone https://github.com/gaps-closure/program-dependence-graph.git 
        pushd program-dependence-graph
        git checkout develop
        mkdir build
        pushd build
        cmake ..
        make
        popd
        popd
    fi
    popd
    pdg_dir=$(realpath closure/prog*)
    conflict_analyzer_dir=$(realpath closure/conflict*)

    function envr {
        echo -e "${CYAN_BOLD}Environment:${CYAN}"
        python3 --version
        minizinc --version
        pushd closure > /dev/null
        echo $conflict_analyzer_dir 
        pushd program-dependence-graph > /dev/null 
        echo pdg: $(git log | head -1)
        popd > /dev/null
        popd > /dev/null
        echo -e "$NC"
    }
    env_output=$(envr)
    echo "$env_output"
    echo "$env_output" > $rundir/env.txt 
}
function run_cmd {
    echo -e "${ORANGE}Running $1${NC}" 
    echo "${@:2}"
    output=$({ time "${@:2}"; } 2>&1)
    [[ $VERBOSE == 1 ]] && echo "$output"
    echo "$output" > $1.txt
}
function run_tests {
    # tests='example-1 example2-correct example2-error global-variable-level-mismatch'
    tests=$(ls -1 $srcdir)
    for testname in $tests; do
        cp -r $srcdir/$testname $rundir/
        pushd $rundir/$testname > /dev/null
        echo -e "${RED}Running test: ${NC}$testname"; echo 

        run_cmd "preprocessor" python3 $conflict_analyzer_dir/qd*.py -L -f *.c
        run_cmd "clang" clang -c -emit-llvm -g out.c -o out.bc
        llvm-dis < out.bc > out.ll
        run_cmd "opt" opt -load $pdg_dir/build/libpdg.so -minizinc < out.bc > /dev/null
        run_cmd "clejson2zinc" python3 $conflict_analyzer_dir/CLEJson*.py -f *.clemap.json
        run_cmd "minizinc-gecode" minizinc --solver Gecode $conflict_analyzer_dir/conflict_analyzer_constraints.mzn $conflict_analyzer_dir/conflict_variable_declerations.mzn pdg_instance.mzn cle_instance.mzn enclave_instance.mzn
        run_cmd "minizinc-findmus" minizinc --solver findmus --subsolver Gecode --output-human --depth 3 $conflict_analyzer_dir/conflict_analyzer_constraints.mzn $conflict_analyzer_dir/conflict_variable_declerations.mzn pdg_instance.mzn cle_instance.mzn enclave_instance.mzn
        popd > /dev/null
    done
}
date
setup_environment
time run_tests
date