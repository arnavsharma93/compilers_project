#!/bin/sh

./Parser < $1 2> .temp.llvm.out

lli .temp.llvm.out

