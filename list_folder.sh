#!/bin/sh
ROOT_PATH=$PWD

rm list_folder.txt
find $ROOT_PATH -type d > list_folder.txt

