#makefile to compile all the files
INC =../inc
BIN =../bin
SRC =../src
OBJ =../obj
DATA =../data

LFLAGS = -o
GCC = gcc #-fprofile-arcs -ftest-coverage
CFLAGS =  -c -g 
IFLAGS = -I $(INC)

all: $(BIN)/client $(BIN)/server

$(OBJ)/clientdef.o : $(SRC)/clientdef.c
	$(GCC) $(CFLAGS) $(SRC)/clientdef.c $(IFLAGS) 
	mv *.o ../obj

$(OBJ)/clientReg.o : $(SRC)/clientReg.c
	$(GCC) $(CFLAGS) $(SRC)/clientReg.c $(IFLAGS) 
	mv *.o ../obj

$(OBJ)/client.o : $(SRC)/client.c
	$(GCC) $(CFLAGS) $(SRC)/client.c $(IFLAGS) 
	mv *.o ../obj

$(BIN)/client : $(OBJ)/clientdef.o $(OBJ)/clientReg.o $(OBJ)/client.o 
	$(GCC) $(OBJ)/clientdef.o $(OBJ)/clientReg.o $(OBJ)/client.o $(LFLAGS) $(BIN)/client

$(OBJ)/serverdef.o : $(SRC)/serverdef.c
	$(GCC) $(CFLAGS) $(SRC)/serverdef.c $(IFLAGS) 
	mv *.o ../obj
	
$(OBJ)/server.o : $(SRC)/server.c 
	$(GCC) $(CFLAGS) $(SRC)/server.c $(IFLAGS)
	mv *.o ../obj

$(BIN)/server : $(OBJ)/serverdef.o $(OBJ)/server.o 
	$(GCC) $(OBJ)/serverdef.o $(OBJ)/server.o $(LFLAGS) $(BIN)/server
