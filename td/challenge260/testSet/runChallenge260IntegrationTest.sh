#!/bin/bash

$1 < input.txt > output.txt
diff output.txt expected_output.txt

exit $?
