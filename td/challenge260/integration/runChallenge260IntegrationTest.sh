#!/bin/bash

testsAllCount=0
testsFailCount=0

TEST_SETS_DIRECTORY=$2

for inputFile in $TEST_SETS_DIRECTORY/input*
do
	inputFileName=`basename $inputFile`
	fileNumberWithInput=${inputFileName%.*}
	fileNumber=${fileNumberWithInput#*_}
	expectedOutputFile="$TEST_SETS_DIRECTORY/expected_output_${fileNumber}.txt"
	outputFile="$TEST_SETS_DIRECTORY/output_${fileNumber}.txt"
	diffResultFile="$TEST_SETS_DIRECTORY/diff_${fileNumber}.txt"
	$1 < $inputFile > $outputFile
	diff $outputFile $expectedOutputFile > $diffResultFile
	if [ $? -ne 0 ]
	then
		echo "Test failed for ${inputFile} : ${expectedOutputFile} Check ${diffResultFile}"
		let "testsFailCount++"
	fi
	let "testAllCount++"
done

if [ $testsFailCount -ne 0 ]
then
	echo "${testsFailCount}/${testAllCount} TESTS FAILED"
	exit -1
else
	echo "${testAllCount} TESTS PASSED"
	exit 0
fi
