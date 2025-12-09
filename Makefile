CC = gcc
CFLAGS = -Wall -O2

all: extract_api

extract_api: extract_api.c
	$(CC) $(CFLAGS) -o extract_api extract_api.c

list-api: extract_api
	./extract_api > public_api.txt
	@echo "Public API written to public_api.txt"

clean:
	rm -f extract_api public_api.txt
