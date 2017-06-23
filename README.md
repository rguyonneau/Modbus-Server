# Modbus-Server

Here is presented a ModBus server implementation in C++. This implementation is based on the MODBUS APPLICATION PROTOCOL SPECIFICATION V1.1b (the pdf can be find here: http://www.modbus.org/docs/Modbus_Application_Protocol_V1_1b.pdf). This ModBus Server is composed of two main classes: ModBusServer and MemInterface. The ModBusServer class processes the Modbus PDU (Protocol Data Unit) and the MemInterface corresponds to the interface between the ModBus Server and the data we want to manage.

## Modbus implemented functions

The implemented Modbus functions are: 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x0F, 0x10

The implemented Modbus exceptions are: 0x01, 0x02, 0x03, 0x04

##  ModbusServer class
The ModbusServer class allows to deal with Modbus pdu (protocol data unit). This implementation is based on the Modbus_Application_Protocol_V1_1b.pdf document (http://www.modbus.org/docs/Modbus_Application_Protocol_V1_1b.pdf). It requires a memory (an implementation of the MemInterface class). Note that the bit_t, byte_t, word_t types are defined in the MemInterface interface 

## MemInterface class
This abstact class in an interface between the ModbusServer class and the memory we want to deal with. You need to create your own Memory class that derivates from MemInterface, by implementing all the needed functions. 

## MemoryTest class
This class is an example of implementation of the MemInterface interface. Note that in this example we consider that the input discrete memory and the output discrete memory are the same. We do the same for the holding registers and the input registers (it is for instance the case for some TSX PLCs). The bit_t, byte_t and word_t types are defined in MemInterface.h 

## main example
Here is a main programm to test the modbus server classes. The main function tests the reading and writing functions of the ModBus server.

## compile and test
With the makefile you only need to do (in the scr folder):

$ make

$ ./modbuserver

it should display

    1 - response (6): 4  4  0  0  0  0

    2 - response (5): 10  0  0  0  2

    3 - response (6): 4  4  ab  cd  12  34

This code has been tested on ubuntu 16.04 LTS
