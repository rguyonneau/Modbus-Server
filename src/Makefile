# all the files are in the same directory
MODBUSDIR = ./

all: modbusserver

modbusserver: MemInterface.o ModbusServer.o MemoryTest.o 
	g++ MemInterface.o ModbusServer.o MemoryTest.o -I$(MODBUSDIR) main.cpp -o modbuserver

MemInterface.o: MemInterface.cpp MemInterface.h
	g++ -c MemInterface.cpp -o MemInterface.o

MemoryTest.o: MemoryTest.cpp
	g++ -c -I$(MODBUSDIR) MemoryTest.cpp -o MemoryTest.o

ModbusServer.o: ModbusServer.cpp
	g++ -c -I$(MODBUSDIR) ModbusServer.cpp -o ModbusServer.o

clean:
	rm *.o
