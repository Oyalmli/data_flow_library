#!/bin/sh
cd ..
~/Library/Python/3.9/bin/quom dfl/dfl.hpp dfl.hpp -s "~> stitch <~" -g DFL_+_HPP -I include/
mkdir -p docs
cd docs
rm -rf *
cd ..
cp README.md include/dfl/.ignore_main_page.md
doxygen
rm include/dfl/.ignore_main_page.md