#!/bin/sh -e

git clean -fxd

make -C tests

# verify that stage.bin is stable
cp cvm/stage.bin ref.bin
make -C cvm updatebootstrap
cmp cvm/stage.bin ref.bin
rm ref.bin
