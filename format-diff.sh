#!/bin/sh

for file in `find $1 -name "*.cpp" -or -name "*.hpp"`;
do
    echo -e "\n\n===$file===\n" ;
    clang-format $file > /tmp/format ;
    diff --color=always $file /tmp/format;
done
