#!/bin/bash
pipex="./pipex"
start="Hello World"
src="./src/pipex.c"
makefile="./Makefile"
out="test/test_out.txt"
no_path="env -i"
wc_l="wc -l"
forbidden="test/test_forbidden.txt"
sleep3="sleep 3"
sleep1="sleep 1"

echo "
/**********************************************************************\\

  ____ _               _      __  __         ____  _                 
 / ___| |__   ___  ___| | __ |  \/  |_   _  |  _ \(_)_ __   ___  ___ 
| |   | '_ \ / _ \/ __| |/ / | |\/| | | | | | |_) | | '_ \ / _ \/ __|
| |___| | | |  __/ (__|   <  | |  | | |_| | |  __/| | |_) |  __/\__ 
\
 \____|_| |_|\___|\___|_|\_\ |_|  |_|\__, | |_|   |_| .__/ \___||___/
                                     |___/          |_|              

\**********************************************************************/
"
echo "#!/bin/bash" > "./sleep_test.sh"
echo "sleep 3 | sleep 1" >> "./sleep_test.sh"
chmod u+x "./sleep_test.sh"
> $out
sleep 2

echo "First command: $pipex "$src" cat cat "$out""
$pipex "$src" cat cat "$out"
sleep 2
echo "Output file:"
sleep 1
cat "$out"
sleep 2

echo "----"
echo "Second command "$out" ls "$wc_l" "$out""
$pipex "$out" ls "$wc_l" "$out"
sleep 2
echo "Output file:"
sleep 1
cat "$out"
sleep 2

echo "----"
echo "Third command $no_path $pipex "$src" cat cat "$out""
sleep 2
$no_path $pipex "$src" cat cat "$out"
echo "Output file:"
sleep 1
cat "$out"
sleep 2

echo "----"
echo "Fourth command $no_path $pipex "$src" /usr/bin/cat /usr/bin/cat "$out""
sleep 2
$no_path $pipex "$src" "/usr/bin/cat" "/usr/bin/cat" "$out"
echo "Output file:"
sleep 1
cat "$out"

sleep 2

echo "----"
echo "Fifth command $pipex "$src" ls nothing "$out""
$pipex "$src" ls "nothing" "$out"
sleep 2
echo "Output file:"
sleep 1
cat "$out"
sleep 2

echo "----"
echo "Sixth command $pipex "$src" nothing ls "$out""
$pipex "$src" "nothing" ls "$out"
sleep 2
echo "Output file:"
sleep 1
cat "$out"
sleep 2

echo "----"
echo "Second file forbidden :"$src" ls "$wc_l" "$forbidden""
$pipex "$src" ls "$wc_l" "$forbidden"
sleep 2

echo "----"
echo "First file forbidden :"$forbidden" ls "$wc_l" "$out""
$pipex "$forbidden" ls "$wc_l" "$out"
echo "Output file:"
sleep 1
cat "$out"
sleep 2

echo "----"
echo "First cmd empty :"$src" "\"\"" "$wc_l" "$out""
$pipex "$src" "" "$wc_l" "$out"
echo "Output file:"
sleep 1
cat "$out"
sleep 2

echo "----"
echo "Second cmd empty :"$src" "$wc_l" "\"\"" "$out""
$pipex "$src"  ls "" "$out"
echo "Output file:"
sleep 1
cat "$out"
sleep 2

echo "----"
echo "Zombie sleep test:"
time $pipex "$src" "$sleep3" "$sleep1" "$out"
sleep 1
time "./sleep_test.sh"
sleep 2

rm "./sleep_test.sh"
