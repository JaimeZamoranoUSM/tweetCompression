CC=gcc
CFLAGS=-Wall -g

all: huffman verifier

huffman: HuffmanGeeks.c
	${CC} ${CFLAGS} -o huffman HuffmanGeeks.c -lm

verifier: BinVerifier.c
	${CC} ${CFLAGS} -o verifier BinVerifier.c -lm

clean:
	rm huffman verifier