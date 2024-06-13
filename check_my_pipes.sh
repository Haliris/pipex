#!/bin/bash
pipex="./pipex"
start="Hello World"
src="./pipex.c"
makefile="./Makefile"
out="test/test_out.txt"
no_path="env -i"
wc_l="wc -l"
forbidden="test/test_forbidden.txt"
sleep3="sleep 3"
sleep1="sleep 1"

echo "
/**********************************************************************\
*    ___         __  ___                        ___ _____  ___  __  __ *
*   / __\ /\  /\/__\/ __\ /\ /\   /\/\ /\_/\   / _ \\_   \/ _ \/__\/ _\*
*  / /   / /_/ /_\ / /   / //_/  /    \\_ _/  / /_)/ / /\/ /_)/_\  \ \ *
* / /___/ __  //__/ /___/ __ \  / /\/\ \/ \  / ___/\/ /_/ ___//__  _\ \*
* \____/\/ /_/\__/\____/\/  \/  \/    \/\_/  \/   \____/\/   \__/  \__/*
\**********************************************************************/
"
> $out
sleep 2

echo "first command: $pipex "$src" cat cat "$out""
$pipex "$src" cat cat "$out"
sleep 2
echo "Output file:"
sleep 1
cat "$out"
sleep 2

echo "----"
echo "second command "$out" ls "$wc_l" "$out""
$pipex "$out" ls "$wc_l" "$out"
sleep 2
echo "Output file:"
sleep 1
cat "$out"
sleep 2

echo "----"
echo "third command $no_path $pipex "$src" cat cat "$out""
sleep 2
$no_path $pipex "$src" cat cat "$out"
echo "Output file:"
sleep 1
cat "$out"
sleep 2

echo "----"
echo "fourth command $no_path $pipex "$src" /usr/bin/cat /usr/bin/cat "$out""
sleep 2
$no_path $pipex "$src" "/usr/bin/cat" "/usr/bin/cat" "$out"
echo "Output file:"
sleep 1
cat "$out"

sleep 2

echo "----"
echo "fifth command $pipex "$src" ls nothing "$out""
$pipex "$src" ls "nothing" "$out"
sleep 2
echo "Output file:"
sleep 1
cat "$out"
sleep 2

echo "----"
echo "sixth command $pipex "$src" nothing ls "$out""
$pipex "$src" "nothing" ls "$out"
sleep 2
echo "Output file:"
sleep 1
cat "$out"
sleep 2

echo "----"
echo "second command "$src" ls "$wc_l" "$forbidden""
$pipex "$src" ls "$wc_l" "$forbidden"
sleep 2

echo "----"
echo "second command "$forbidden" ls "$wc_l" "$out""
$pipex "$forbidden" ls "$wc_l" "$out"
echo "Output file:"
sleep 1
cat "$out"
sleep 2

echo "----"
echo "zombie sleep test:"
time $pipex "$src" "$sleep3" "$sleep1" "$out"
sleep 1
time "./sleep_test.sh"
sleep 2
