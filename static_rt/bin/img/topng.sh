#!/bin/bash
for ppm in ./*.ppm
do
     echo "${ppm} to ${ppm}.png"
     convert "${ppm}" "${ppm}.png"
done

