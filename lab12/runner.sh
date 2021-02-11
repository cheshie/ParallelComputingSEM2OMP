
name="lab2_zad2"
if [ $# -eq 2 ]
	then
	name="$name${1}_${2}"
fi

if [ $# -eq 1 ]
then
	name="$name${1}"
fi
	
gcc "$name.c" -fopenmp -lm -o "$name" && ./"$name"


