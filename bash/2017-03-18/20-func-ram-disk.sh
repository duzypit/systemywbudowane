#20 napisz funkcję zwracającą informację o zajętośic pamięci ram oraz zajętości dysku.
# http://unix.stackexchange.com/questions/119126/command-to-display-memory-usage-disk-usage-and-cpu-load
#!/bin/bash
function mem {
	clear
	free -m
	echo "Zajętość dysku:"
	df -h
	top -bn1 | grep "Cpu(s)" | sed "s/.*, *\([0-9.]*\)%* id.*/\1/" | awk '{print 100 - $1"%"}'
}

mem
