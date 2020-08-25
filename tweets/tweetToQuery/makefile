all: tableMaker queryMaker

tableMaker: tableMaker.c
	gcc tableMaker.c -o tableMaker -lm

queryMaker: queryMaker.c
	gcc queryMaker.c -o queryMaker -lm

clean:
	rm tableMaker queryMaker
