CC=gcc
CFLAGS=-Wall -Wextra -O2
SRC=src/main.c
OUT=generator

all: generate copy-wasm

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

generate: $(OUT)
	./$(OUT)

copy-wasm:
	mkdir -p public/static/js
	cp ../holyforge-c-wasm/public/*.js public/static/js/
	cp ../holyforge-c-wasm/public/*.wasm public/static/js/

clean:
	rm -f $(OUT)
	find public -name "*.html" -delete
	rm -rf public/games/*.html
	rm -rf public/blog/*.html
