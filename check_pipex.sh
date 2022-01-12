#!/bin/bash



#1==================without infile and outfile
mkdir -p temporary
cd temporary
touch res1 res2
cd ..

rm -rf infile || true
rm -rf outfile || true

./pipex infile "ls -l" "wc -l" outfile
stat --format="%a" outfile >./temporary/res1
cat outfile >>./temporary/res1

rm -rf infile || true
rm -rf outfile || true

< infile ls -l | wc -l > outfile
stat --format="%a" outfile >./temporary/res2
cat outfile >>./temporary/res2

if cmp -s "./temporary/res1" "./temporary/res2"; then
    printf 'Test 1 - \e[1;32mOK\n\e[0m'
else
    printf 'Test 1 without infile and outfile - \e[1;31mKO\n\e[0m'
fi

rm -rf infile || true
rm -rf outfile || true
rm -rf temporary || true


#2==================with infile and outfile
mkdir -p temporary
cd temporary
touch res1 res2
cd ..

touch infile outfile
chmod 777 infile
chmod 777 outfile
echo blablabla >infile
echo blablabla >outfile

./pipex infile "ls -l" "wc -l" outfile
stat --format="%a" outfile >./temporary/res1
cat outfile >>./temporary/res1

rm -rf infile || true
rm -rf outfile || true

touch infile outfile
chmod 777 infile
chmod 777 outfile
echo blablabla >infile
echo blablabla >outfile

< infile ls -l | wc -l > outfile
stat --format="%a" outfile >./temporary/res2
cat outfile >>./temporary/res2

if cmp -s "./temporary/res1" "./temporary/res2"; then
    printf 'Test 2 - \e[1;32mOK\n\e[0m'
else
    printf 'Test 2 with infile and outfile - \e[1;31mKO\n\e[0m'
fi

rm -rf infile || true
rm -rf outfile || true
rm -rf temporary || true





#3==================with infile and without outfile
mkdir -p temporary
cd temporary
touch res1 res2
cd ..

touch infile
chmod 777 infile
echo blablabla >infile

./pipex infile "ls -l" "wc -l" outfile
stat --format="%a" outfile >./temporary/res1
cat outfile >>./temporary/res1

rm -rf infile || true
rm -rf outfile || true

touch infile
chmod 777 infile
echo blablabla >infile

< infile ls -l | wc -l > outfile
stat --format="%a" outfile >./temporary/res2
cat outfile >>./temporary/res2

if cmp -s "./temporary/res1" "./temporary/res2"; then
    printf 'Test 3 - \e[1;32mOK\n\e[0m'
else
    printf 'Test 3 without outfile - \e[1;31mKO\n\e[0m'
fi

rm -rf infile || true
rm -rf outfile || true
rm -rf temporary || true


#4==================with infile and without outfile
mkdir -p temporary
cd temporary
touch res1 res2
cd ..

touch outfile
chmod 777 outfile
echo blablabla >outfile

./pipex infile "ls -l" "wc -l" outfile
stat --format="%a" outfile >./temporary/res1
cat outfile >>./temporary/res1

rm -rf infile || true
rm -rf outfile || true

touch outfile
chmod 777 outfile
echo blablabla >outfile

< infile ls -l | wc -l > outfile
stat --format="%a" outfile >./temporary/res2
cat outfile >>./temporary/res2

if cmp -s "./temporary/res1" "./temporary/res2"; then
    printf 'Test 4 - \e[1;32mOK\n\e[0m'
else
    printf 'Test 4 without infile - \e[1;31mKO\n\e[0m'
fi

rm -rf infile || true
rm -rf outfile || true
rm -rf temporary || true



#5==================with restricted outfile
mkdir -p temporary
cd temporary
touch res1 res2
cd ..

touch infile outfile
chmod 777 infile
chmod 000 outfile
echo blablabla >infile

./pipex infile "ls -l" "wc -l" outfile
stat --format="%a" outfile >./temporary/res1
cat outfile >>./temporary/res1

rm -rf infile || true
rm -rf outfile || true

touch infile outfile
chmod 777 infile
chmod 000 outfile
echo blablabla >infile

< infile ls -l | wc -l > outfile
stat --format="%a" outfile >./temporary/res2
cat outfile >>./temporary/res2

if cmp -s "./temporary/res1" "./temporary/res2"; then
    printf 'Test 5 - \e[1;32mOK\n\e[0m'
else
    printf 'Test 5 with restricted outfile - \e[1;31mKO\n\e[0m'
fi

rm -rf infile || true
rm -rf outfile || true
rm -rf temporary || true


#6==================with restricted infile
mkdir -p temporary
cd temporary
touch res1 res2
cd ..

touch infile outfile
chmod 000 infile
chmod 777 outfile
echo blablabla >outfile

./pipex infile "ls -l" "wc -l" outfile
stat --format="%a" outfile >./temporary/res1
cat outfile >>./temporary/res1

rm -rf infile || true
rm -rf outfile || true

touch infile outfile
chmod 000 infile
chmod 777 outfile
echo blablabla >outfile

< infile ls -l | wc -l > outfile
stat --format="%a" outfile >./temporary/res2
cat outfile >>./temporary/res2

if cmp -s "./temporary/res1" "./temporary/res2"; then
    printf 'Test 6 - \e[1;32mOK\n\e[0m'
else
    printf 'Test 6 with infile and outfile - \e[1;31mKO\n\e[0m'
fi

rm -rf infile || true
rm -rf outfile || true
rm -rf temporary || true


#7==================with several options
mkdir -p temporary
cd temporary
touch res1 res2
cd ..

touch infile outfile
chmod 777 infile
chmod 777 outfile
echo blablabla >infile
echo blablabla >outfile

./pipex infile "ls -l -a" "wc -l -c" outfile
stat --format="%a" outfile >./temporary/res1
cat outfile >>./temporary/res1

rm -rf infile || true
rm -rf outfile || true

touch infile outfile
chmod 777 infile
chmod 777 outfile
echo blablabla >infile
echo blablabla >outfile

< infile ls -l -a | wc -l -c > outfile
stat --format="%a" outfile >./temporary/res2
cat outfile >>./temporary/res2

if cmp -s "./temporary/res1" "./temporary/res2"; then
    printf 'Test 7 - \e[1;32mOK\n\e[0m'
else
    printf 'Test 7 with several options - \e[1;31mKO\n\e[0m'
fi

rm -rf infile || true
rm -rf outfile || true
rm -rf temporary || true



#8==================wrong cmd2
mkdir -p temporary
cd temporary
touch res1 res2
cd ..

touch infile outfile
chmod 777 infile
chmod 777 outfile
echo blablabla >infile
echo blablabla >outfile

./pipex infile "ls -l" "blabla" outfile
stat --format="%a" outfile >./temporary/res1
cat outfile >>./temporary/res1

rm -rf infile || true
rm -rf outfile || true

touch infile outfile
chmod 777 infile
chmod 777 outfile
echo blablabla >infile
echo blablabla >outfile

< infile ls -l | blabla > outfile
stat --format="%a" outfile >./temporary/res2
cat outfile >>./temporary/res2

if cmp -s "./temporary/res1" "./temporary/res2"; then
    printf 'Test 8 - \e[1;32mOK\n\e[0m'
else
    printf 'Test 8 with wrong cmd2 - \e[1;31mKO\n\e[0m'
fi

rm -rf infile || true
rm -rf outfile || truerm -rf temporary || true
rm -rf temporary || true
