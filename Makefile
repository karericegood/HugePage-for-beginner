CC = gcc 
CFLAGS = -g -Wall 
TARGET = 
all : virt_to test 
	make virt_to 
	make test
	make blast 
	make memory_bloating	
virt_to : virt_to_phys_user.c
	$(CC) $(CFLAGS)-o virt_to_phys_user virt_to_phys_user.c 
test : test.c 
	$(CC) $(CFLAGS)-o test test.c 
blast : blast.cpp
	g++ -o blast blast.cpp
memory_bloating : memory_bloating.c
	$(CC) $(CFLAGS)-o memory_bloating memory_bloating.c

