#! /usr/bin/env zsh

for file in $(\ls $@)
do
	diff <(otool -t $file) <(./ft_otool $file) || echo $file >> file_error && echo $file >> file_processed
done
