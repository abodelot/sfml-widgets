#!/bin/bash

clang-format $(find src -type f) -i
echo "Done"
