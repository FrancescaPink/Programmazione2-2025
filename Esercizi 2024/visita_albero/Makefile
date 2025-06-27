project: main.o tipo.o coda-bfs.o tree.o
	g++ -Wall -o project main.o tipo.o coda-bfs.o tree.o
main.o: main.cc tipo.h tree.h coda-bfs.h
	g++ -Wall -c main.cc tipo.h tree.h coda-bfs.h
tipo.o: tipo.cc tipo.h
	g++ -Wall -c tipo.cc tipo.h
coda-bfs.o: coda-bfs.cc tipo.h tree.h coda-bfs.h
	g++ -Wall -c coda-bfs.cc tipo.h tree.h coda-bfs.h
tree.o: tree.cc tipo.h tree.h
	g++ -Wall -c tree.cc tipo.h tree.h