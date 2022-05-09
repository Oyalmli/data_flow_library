#!/bin/sh
mkdir -p docs
cd docs
rm -rf *
cd ..
doxygen
mv docs/html/* docs/