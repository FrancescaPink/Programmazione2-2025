OBJ= liste.o compito.o tipo.o 

exe: $(OBJ)
	g++ -o exe $(OBJ)

.PHONY: clean cleanall

include dependence

clean:
	rm -f *.o 
cleanall:
	rm -f exe *.o 
dependence:
	g++ -MM *.cc > dependence
