# Napisz skrytp robiący bardzo prosty backup plików z roszerzeniem .conf z katlaogu /etc. Bqp powinien być wykonywany jako tar, nazwa pliku w postaci
# backup_dien-miesiac-rok.tar
#!/bin/bash
	clear
	out=~/backup_$(date +%d-%m-%Y).tar
	echo "plik będzie naywał się:"
	echo $out
	cd /etc 
	tar -cf $out *.conf
	cd ~/
