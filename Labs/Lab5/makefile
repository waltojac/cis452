writer.o: writer.c

reader.o: reader.c

writer: writer.o
	gcc writer.o -Wall -o writer

reader: reader.o
	gcc reader.o -Wall -o reader

default: reader writer
	rm reader.o
	rm writer.o

