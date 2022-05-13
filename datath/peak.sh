#!/bin/bash
echo "found:"
ls *x.txt | xargs grep -v '#' | tail -n 20
echo "min - max:"
ls ./*x.txt | xargs -I {} sh -c "cat {} | tail -1" | sort -n -k4 | head -1 #least progressed core 
ls ./*x.txt | xargs -I {} sh -c "cat {} | tail -1" | sort -n -k4 | tail -1 #most -||-
