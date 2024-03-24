#!/bin/sh

cmake . && make || exit 1

./maze > picture.rgba 2>picture.txt && convert -size `cat picture.txt` -depth 8 picture.rgba picture.png

rm -rf picture.rgba picture.txt




