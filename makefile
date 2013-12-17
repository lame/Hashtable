pass.x: spass.o hashtable.o
	g++ -g -o spass.x hashtable.o spass.o -lcrypt
Driver.o: spass.cpp hashtable.h hashtable.cpp
	g++ -g -c spass.cpp
hastable.o: hashtable.h hashtable.cpp
	g++ -c hashtable.h hashtable.cpp
clean:
	rm *.o
