#!/bin/sh
echo "======= BUIDLING ======"
make clean
make

echo "======= COMPILING ======"
./compile.sh $1
