#!/usr/bin/env bash
echo "Cleaning & Compiling tsylb2"
cd src/py_unified_parser/tsylb2-1.1 || exit
make clean
make

echo "Configured successfully."
