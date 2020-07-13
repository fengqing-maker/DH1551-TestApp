#!/bin/sh

current_dir=`pwd`
root_dir=${current_dir}/../../../../..
obj_dir=${root_dir}/obj

date_and_time=`date +%y%m%d%H%M%S`

rm ${obj_dir}/Sabbat_s35x.*.out
rm ${obj_dir}/see_sabbat_s35x.*.out

cp -vf ${obj_dir}/Sabbat_s35x.out ${obj_dir}/Sabbat_s35x.${date_and_time}.out
cp -vf ${obj_dir}/see_sabbat_s35x.out ${obj_dir}/see_sabbat_s35x.${date_and_time}.out

eval sed -i 's/Sabbat_s35x.*\.out/Sabbat_s35x.${date_and_time}\.out/g' ${obj_dir}/*.ini
eval sed -i 's/see_sabbat_s35x.*\.out/see_sabbat_s35x.${date_and_time}\.out/g' ${obj_dir}/*.ini