#!/bin/bash

testsAllCount=0
testsFailCount=0

for inputFile  in input*
do
	fileNumberWithInput=${inputFile%.*}
	fileNumber=${fileNumberWithInput#*_}
	expectedOutputFile="expected_output_${fileNumber}.txt"
	outputFile="output_${fileNumber}.txt"
	diffResultFile="diff_${fileNumber}.txt"
	$1 < $inputFile > $outputFile
	diff $outputFile $expectedOutputFile > $diffResultFile
	if [ $? -ne 0 ]
	then
		echo "Test failed for ${inputFile} : ${expectedOutputFile} Check ${diffResultFile}"
		let "testFailCount++"
	fi
	let "testAllCount++"
done

if [ $testsFailCount -ne 0 ]
then
	echo "${testFailCount}/${testAllCount} TESTS FAILED"
	exit -1
else
	echo "${testAllCount} TESTS PASSED"
	exit 0
fi
