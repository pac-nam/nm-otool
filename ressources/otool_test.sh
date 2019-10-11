otool -t $@ > Rnm.txt;
./ft_otool $@ > Rme.txt;
diff Rnm.txt Rme.txt > diff.txt;
