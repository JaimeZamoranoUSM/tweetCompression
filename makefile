make = testing

run: testing
	./testing


testing: testingDataType.c
	gcc testingDataType.c -o testing -lm
