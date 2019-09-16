#!/bin/bash

src="images_src"
desr="images"

for file in `find images_src/* -type f`; do
    echo $file
    dist_file=${file//images_src\//images/}

    convert $file -type grayscale $dist_file 
done

