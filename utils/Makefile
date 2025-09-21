CC=gcc
CFLAGS= -Wall

all: script table

script: ScriptBuilder.c
	$(CC) $(CFLAGS) ScriptBuilder.c -o Scriptbuilder.exe

table: TableBuilder.c
	$(CC) $(CFLAGS) TableBuilder.c -o TableBuilder.exe

clean:
	rm *.exe