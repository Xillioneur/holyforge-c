CC=gcc
CFLAGS=-Wall -Wextra -O2
SRC=src/main.c
OUT=generator

all: generate

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

generate: $(OUT)
	./$(OUT)

clean:
	rm -f $(OUT)
	rm -rf public/*.html
