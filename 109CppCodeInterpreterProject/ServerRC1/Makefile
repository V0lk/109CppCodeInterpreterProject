OBJS = server.o connection.o garbagecollector.o TCPServerSocket.o TCPSocket.o Thread.o dataFactory.o expressionFactory.o logger.o parse.o storage.o MISNumeric.o MISReal.o MISChar.o MISString.o VAR.o JMP.o JMPZ.o JMPNZ.o JMPGT.o JMPGTE.o JMPLT.o JMPLTE.o SLEEP.o OUT.o ASSIGN.o ADD.o MULT.o DIV.o SUB.o GET_STR_CHAR.o SET_STR_CHAR.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c -std=c++14 -pthread $(DEBUG)
LFLAGS = -Wall -pthread $(DEBUG)
OPERC = VAR.cpp JMP.cpp JMPZ.cpp JMPNZ.cpp JMPGT.cpp JMPGTE.cpp JMPLT.cpp JMPLTE.cpp SLEEP.cpp OUT.cpp ASSIGN.cpp ADD.cpp MULT.cpp DIV.cpp SUB.cpp GET_STR_CHAR.cpp SET_STR_CHAR.cpp
OPERH = VAR.h JMP.h JMPZ.h JMPNZ.h JMPGT.h JMPGTE.h JMPLT.h JMPLTE.h SLEEP.h OUT.h ASSIGN.h ADD.h MULT.h DIV.h SUB.h GET_STR_CHAR.h SET_STR_CHAR.h
DATAT = MISReal.h MISReal.cpp MISChar.h MISChar.cpp MISString.h MISString.cpp MISNumeric.h MISNumeric.cpp

# main program
server_misvm : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o server_misvm

# framework
server.o : common.h includes.h garbagecollector.h garbagecollector.cpp TCPServerSocket.h TCPServerSocket.cpp
	$(CC) $(CFLAGS) server.cpp
	
connection.o : common.h includes.h connection.h connection.cpp parse.h parse.cpp storage.h storage.cpp logger.h logger.cpp
	$(CC) $(CFLAGS) connection.cpp

garbagecollector.o : garbagecollector.h garbagecollector.cpp connection.h connection.cpp
	$(CC) $(CFLAGS) garbagecollector.cpp

TCPServerSocket.o : includes.h TCPSocket.h TCPSocket.cpp TCPServerSocket.h TCPServerSocket.cpp
	$(CC) $(CFLAGS) TCPServerSocket.cpp

TCPSocket.o : includes.h TCPSocket.h TCPSocket.cpp
	$(CC) $(CFLAGS) TCPSocket.cpp

Thread.o : includes.h Thread.h Thread.cpp
	$(CC) $(CFLAGS) Thread.cpp
	
dataFactory.o : dataFactory.cpp dataFactory.h abstractFactory.h dataType.h $(DATAT)
	$(CC) $(CFLAGS) dataFactory.cpp
	
expressionFactory.o: expressionFactory.cpp expressionFactory.h abstractFactory.h expression.h $(OPERC) $(OPERH)
	$(CC) $(CFLAGS) expressionFactory.cpp
	
logger.o: logger.cpp logger.h common.h
	$(CC) $(CFLAGS) logger.cpp
	
parse.o: parse.cpp parse.h common.h
	$(CC) $(CFLAGS) parse.cpp
	
storage.o: storage.cpp storage.h common.h dataType.h dataFactory.h dataFactory.cpp TCPSocket.h TCPSocket.cpp $(DATAT)
	$(CC) $(CFLAGS) storage.cpp

# data types	
MISNumeric.o: MISNumeric.cpp MISNumeric.h dataType.h
	$(CC) $(CFLAGS) MISNumeric.cpp
	
MISChar.o: MISChar.cpp MISChar.h dataType.h
	$(CC) $(CFLAGS) MISChar.cpp
	
MISReal.o: MISReal.cpp MISReal.h dataType.h
	$(CC) $(CFLAGS) MISReal.cpp
	
MISString.o: MISString.cpp MISString.h dataType.h
	$(CC) $(CFLAGS) MISString.cpp
	
# expressions
VAR.o:  VAR.cpp VAR.h expression.h
	$(CC) $(CFLAGS) VAR.cpp
	
JMP.o: JMP.cpp JMP.h expression.h
	$(CC) $(CFLAGS) JMP.cpp
	
JMPZ.o: JMPZ.cpp JMPZ.h expression.h
	$(CC) $(CFLAGS) JMPZ.cpp
	
JMPNZ.o: JMPNZ.cpp JMPNZ.h expression.h
	$(CC) $(CFLAGS) JMPNZ.cpp
	
JMPGT.o: JMPGT.cpp JMPGT.h expression.h
	$(CC) $(CFLAGS) JMPGT.cpp
	
JMPGTE.o: JMPGTE.cpp JMPGTE.h expression.h
	$(CC) $(CFLAGS) JMPGTE.cpp
	
JMPLT.o: JMPLT.cpp JMPLT.h expression.h
	$(CC) $(CFLAGS) JMPLT.cpp
	
JMPLTE.o: JMPLTE.cpp JMPLTE.h expression.h
	$(CC) $(CFLAGS) JMPLTE.cpp
	
SLEEP.o: SLEEP.cpp SLEEP.h expression.h
	$(CC) $(CFLAGS) SLEEP.cpp
	
OUT.o: OUT.cpp OUT.h expression.h
	$(CC) $(CFLAGS) OUT.cpp
	
ASSIGN.o: ASSIGN.cpp ASSIGN.h expression.h
	$(CC) $(CFLAGS) ASSIGN.cpp
	
SUB.o: SUB.cpp SUB.h expression.h
	$(CC) $(CFLAGS) SUB.cpp
	
ADD.o: ADD.cpp ADD.h expression.h
	$(CC) $(CFLAGS) ADD.cpp
	
MULT.o: MULT.cpp MULT.h expression.h
	$(CC) $(CFLAGS) MULT.cpp
	
DIV.o: DIV.cpp DIV.h expression.h
	$(CC) $(CFLAGS) DIV.cpp
	
SET_STR_CHAR.o: SET_STR_CHAR.cpp SET_STR_CHAR.h expression.h
	$(CC) $(CFLAGS) SET_STR_CHAR.cpp

GET_STR_CHAR.o: GET_STR_CHAR.cpp GET_STR_CHAR.h expression.h
	$(CC) $(CFLAGS) GET_STR_CHAR.cpp
	
clean:
	\rm *.o server_misvm
