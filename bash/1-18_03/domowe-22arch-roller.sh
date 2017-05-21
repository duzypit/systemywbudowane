# funkcja przyjmuje jako arg nazwe pliku
# rozpoznaje miniumu 3 rodzaje po rozsrzerzeniu
# po wybraniu odowiedniego programu rozpakowuje arch
#!/bin/bash



function unpack {
#tar
#.gz
#bz2

	ext=${1: - 3}
	echo "Dziń dybry..."

	case "$ext" in
		tar)
			echo "jest tar"
			tar -xvf $1
			;;
		.gz)
			echo "jest gunzip"
			gzip -d $1
			;;
		bz2)
			echo "jest bzip"
			bzip2 -d  $1
			;;
		*)
			echo "Nie obczajam teg typu pliku. Żegnam ozięble..."
		
	esac

}


clear
unpack $1
