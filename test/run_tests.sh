#!/bin/bash

# Configuration
cwd=$(pwd)
## Images
samples_folder="$cwd/../samples"
img0="$samples_folder/dog.lp"
img1a="$samples_folder/RGB.lp"
img1b="$samples_folder/gray.lp"
img2="$samples_folder/blur.lp"

## Python script
lp="$cwd/../script/lp.py"

# Compiling lpcv
echo "Compiling lpcv..."
cd ../lpcv
make

if [ "$?" == 0 ]
then
    echo "Compilation: OK!"
else
    echo "Compilation: Fail!"
    exit 1
fi

# Compiling tests 
echo "Compiling tests..."
cd "$cwd"

make
if [ "$?" == 0 ]
then
    echo "Compilation: OK!"
else
    echo "Compilation: Fail!"
    exit 1
fi

# Running tests
echo "Running tests"
success=0
total=4
rm -rf outputs

## Core test
echo ""
echo "Core test"
echo "========="
echo "Testing: [greetings, open, info, copyTo, write and close]."
echo ""

mkdir -p outputs/test_core
./test_core "$img0" "./outputs/test_core/"

if [ "$?" == 0 ]
then
    echo ""
    echo "Core test: OK!"
    success=$((success + 1))
else
    echo ""
    echo "Core test: Fail!"
fi

## Flip test
echo ""
echo "Flip test"
echo "========="
echo "Testing: 'Core test' + [flip]."
echo ""

mkdir -p outputs/test_flips
./test_flips "$img0" "./outputs/test_flips/"

if [ "$?" == 0 ]
then
    echo ""
    echo "Flip test: OK!"
    success=$((success + 1))
else
    echo ""
    echo "Flip test: Fail!"
fi


## Color test
echo ""
echo "Color test"
echo "========="
echo "Testing: 'Core test' + ['open gray images', split, toGray] ."
echo ""

mkdir -p outputs/test_color
./test_color "$img1a" "$img1b" "./outputs/test_color/"

if [ "$?" == 0 ]
then
    echo ""
    echo "Color test: OK!"
    success=$((success + 1))
else
    echo ""
    echo "Color test: Fail!"
fi


## Blur test
echo ""
echo "Blur test"
echo "========="
echo "Testing: 'Core test' + [blur]"
echo ""

mkdir -p outputs/test_blur
./test_blur "$img2" "./outputs/test_blur/"

if [ "$?" == 0 ]
then
    echo ""
    echo "Blur test: OK!"
    success=$((success + 1))
else
    echo ""
    echo "Blur test: Fail!"
fi

echo ""
echo "Finished successfully: $success/$total"


## Convert to JPG
echo ""
echo "Convert to jpg..."
for folder in `find ./outputs/ -type d`
do
    echo "$folder:"
    python "$lp" -f "$folder" -o "$folder" --lp
    echo ""
done