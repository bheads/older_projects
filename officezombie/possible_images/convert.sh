#!/bin/bash
x=0
for file in *.bmp ; do
    convert -gravity Center -crop 96x96+0+0 -transparent "#6a4c30" "$file" "$x.png"
    let x=$x+1
done
