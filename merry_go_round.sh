#!/bin/bash
pipex=$(./pipex)
start="Hello World"
src=$(./pipex.c)
makefile=$(./Makefile)
out=$(test/test_out.txt)
no_path=$("env -i")
wc_l=$("wc -l")
pause=$(sleep 2)

$pipex $start cat cat $out
$pause
$pipex $out ls $wc_l $out
$pause
$no_path $pipex $src cat cat $out
$pause
