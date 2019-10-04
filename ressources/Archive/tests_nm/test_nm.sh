#! /usr/bin/env zsh

for file in $(\ls $@)
do
	diff <(nm $file) <(./ft_nm $file) || echo $file >> file_error && echo $file >> file_processed
done
