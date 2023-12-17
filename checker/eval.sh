#!/bin/bash

# Computer Programming - Memory Allocation Simulation
# (C) 2008 Stefan Bucur

# This file controls the main evaluation logic

# Usage:
# ./eval.sh [bonus]
# where 'bonus' is an optional parameter indicating that bonus tests should
# also be run.

ALLOCATOR="./allocator"
REFERENCE="./reference"
GENERATOR="./generator.py"

TESTS_DIR="_tests"

function fail {
	printf "FAIL (%s)\n" "$1"
}

function pass {
	printf "PASS\n"
}

function check_diff {
	OUTPUT=$1
	OUTPUT_REF=$2
	
	if [ -z "$(diff -qwB $OUTPUT $OUTPUT_REF)" ]; then
		pass
	else
		fail "differences found"
		
		echo "-- First lines of the diff below --"
		diff -uwB $OUTPUT $OUTPUT_REF | head -n 10
		echo "-----"
		echo
	fi
}

function run_tests {
	PREFIX=$1
	
	for INPUT in $(ls ${PREFIX}*.in); do
		printf "%-50s" "Testing file $INPUT... "
		
		OUTPUT=${INPUT/%in/out}
		OUTPUT_REF=${INPUT/%in/out.ref}
		
		rm -f $OUTPUT
		rm -f $OUTPUT_REF
		
		# Generating the reference output
		$REFERENCE <$INPUT >$OUTPUT_REF
		
		# Running the program
		$ALLOCATOR <$INPUT >$OUTPUT
		
		check_diff $OUTPUT $OUTPUT_REF
	done
}

function run_random {
	PREFIX=$1
	
	# Generate random input and reference output
	INPUT=${PREFIX}.in
	OUTPUT_REF=${PREFIX}.out.ref
	OUTPUT=${PREFIX}.out
	
	printf "%-50s" "Testing random generated file ($INPUT)... "
	
	rm -f $INPUT
	rm -f $OUTPUT_REF
	rm -f $OUTPUT
	
	$GENERATOR $INPUT $OUTPUT_REF  $2 $3  $4 $5 
	
	# Running the program
	$ALLOCATOR <$INPUT >$OUTPUT
	
	check_diff $OUTPUT $OUTPUT_REF
}

echo "*******************************"
echo "*** Running the basic tests ***"
echo "*******************************"
echo

run_tests "${TESTS_DIR}/basic"

echo
echo "**********************************"
echo "*** Running the advanced tests ***"
echo "**********************************"
echo

run_tests "${TESTS_DIR}/advanced"

echo
echo "****************************"
echo "*** Running random tests ***"
echo "****************************"
echo

run_random "${TESTS_DIR}/random_1"  100 500  50 100
run_random "${TESTS_DIR}/random_2"  500 2000 100 300
run_random "${TESTS_DIR}/random_3"  5000 10000 500 1000

if [ "$1" != "bonus" ]; then
	echo
	echo "*** No bonus testing ***"
	echo
	
	exit 0
fi

echo
echo "*******************************"
echo "*** Running the bonus tests ***"
echo "*******************************"
echo

run_tests "${TESTS_DIR}/bonus"

