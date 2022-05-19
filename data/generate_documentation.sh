#!/bin/sh
cd ..
mkdir -p docs
cd docs
rm -rf *
cd ..
cp README.md include/dfl/.ignore_main_page.md
doxygen
rm include/dfl/.ignore_main_page.md