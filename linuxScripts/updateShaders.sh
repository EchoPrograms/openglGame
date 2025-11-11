#!/bin/bash

cp -r ../res ../build/bin

cd ../build
make
cd bin
./opengl
cd ../../linuxScripts
