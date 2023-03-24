CC=gcc
CFLAGS=-Wall -std=gnu11
SRC=main.c  employees.c

all: rfid_scan
rfid_scan: $(SRC)
	$(CC) -g $(CFLAGS) $^ -o $@
