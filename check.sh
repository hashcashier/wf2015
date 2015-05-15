#!/bin/bash

for i in `find cpp`
do
  grep "$i" topics.tex > /dev/null || echo $i;
done
