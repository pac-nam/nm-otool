make;
nm $@ > Rnm.txt;
./ft_nm $@ > Rme.txt;
diff Rnm.txt Rme.txt > diff.txt;
