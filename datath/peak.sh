#!/bin/bash
echo "found:"
ls *x.txt | xargs grep -v '#'
echo "min - max:"
ls *x.txt | xargs cat | tail -n 12 | sort -n | head -n 1
ls *x.txt | xargs cat | tail -n 12 | sort -n | tail -n 1