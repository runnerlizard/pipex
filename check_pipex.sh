#!/bin/bash


#1===================================================simple test 1 without infile
mkdir -p temporary
cd temporary
touch res1 res2
cd ..
rm -rf infile || true
./pipex infile "ls -l" "wc -l" outfile
stat --format="%a" outfile >./temporary/res1
cat outfile >>./temporary/res1
rm -rf infile || true
< infile ls -l | wc -l > outfile
stat --format="%a" outfile >./temporary/res2
cat outfile >>./temporary/res2
file1="./temporary/res1"
file2="./temporary/res2"
if cmp -s "$file1" "$file2"; then
    printf 'Test 1 - \e[1;32mOK\n\e[0m'
else
    printf 'Simple test 1 without infile - \e[1;31mKO\n\e[0m'
fi
rm -rf infile || true
rm -rf outfile || true
rm -rf temporary || true



#2===================================================simple test 1 with infile
mkdir -p temporary
cd temporary
touch res1 res2
cd ..
touch infile
cat blablabla >infile
./pipex infile "ls -l" "wc -l" outfile
stat --format="%a" outfile >./temporary/res1
cat outfile >>./temporary/res1
< infile ls -l | wc -l > outfile
stat --format="%a" outfile >./temporary/res2
cat outfile >>./temporary/res2
file1="./temporary/res1"
file2="./temporary/res2"
if cmp -s "$file1" "$file2"; then
    printf 'Test 2 - \e[1;32mOK\n\e[0m'
else
    printf 'Simple test 2 with infile - \e[1;31mKO\n\e[0m'
fi
rm -rf infile || true
rm -rf outfile || true
rm -rf temporary || true