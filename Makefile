BIN=sfxtree
OBJ=main.o suffix_tree.o
$(BIN):$(OBJ)
	g++ -O2 -o $(BIN) $(OBJ)
%.o : %.cpp
	g++ -O2 -c $^
.PHONY : clean
clean:
	rm -f $(BIN)
	rm -f $(OBJ)
	
