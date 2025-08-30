CFLAGS = -Wall -Werror
SCR = Main.c utility.c 
CC = gcc
FILE = General_Record.txt   
all: final
	:>$(FILE)
	find ~/Master_Folder/User -mindepth 1 -maxdepth 1 -type d -exec rm -rf {} +

final: Main.o utility.o
	$(CC) $(CFLAGS) $(SCR) -o final

Main.o: Main.c 
	$(CC) $(CFLAGS) -c Main.c

utility.o: utility.c 
	$(CC) $(CFLAGS) -c utility.c

clean: 
	rm utility.o Main.o final


