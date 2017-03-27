#napisz skrypt zliczający łączną sumę zajętośći katalogóœ w /etc/ (katalogi pierwszego poziomu)

#!/bin/bash
if [ -d /etc ]
then
	
	cd /etc
	out="$(find -type d | du -hs)"
	clear
	echo "Output jest taki:"
	echo "${out}"
fi
