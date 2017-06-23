/***
 * This file is part of the MemInterface interface implementation example
 * to use the ModbusServer class.
 *
 * Copyright (C) 2016 - Remy Guyonneau - remy.guyonneau(at)univ-angers.fr
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ***/

#include "MemoryTest.h"

#include <exception>

//constructor
//word_t nbCoils :      number of discrete inputs/outputs for the memory
//word_t nbRegisters :  number of inputs/outputs registers for the memory
MemoryTest::MemoryTest(word_t nbCoils, word_t nbRegisters):
_coils(nbCoils), _registers(nbRegisters){
    _min_address_coil = 0;
    _max_address_coil = nbCoils-1;
    _min_address_reg = 0;
    _max_address_reg = nbRegisters-1;
    initMemory();   //to deal with tests while developping a client for instance
}

MemoryTest::~MemoryTest(){
    //dtor
}

//this function is meant to do some test while using this class
void MemoryTest::initMemory(){
    for(unsigned int i=0; i< _coils.size(); i++){
        _coils[i] = false;
    }
    for(unsigned int i=0; i< _registers.size(); i++){
        _registers[i] = false;
    }
    //ADD SOME FANCY INITIALIZATION HERE
}

//Test if the address corresponds to a correct discrete memory
//return true if the address is correct, false otherwise
//word_t i :    the address we want to test
bool MemoryTest::isValidDiscreteOutput(word_t i) const{
    if(i>= _min_address_coil && i <=_max_address_coil){
        return true;
    }else{
        return false;
    }
}

//Test if the address corresponds to a correct register memory
//return true if the address is correct, false otherwise
//word_t i :    the address we want to test
bool MemoryTest::isValidHoldingRegister(word_t i) const{
    if(i>= _min_address_reg && i <=_max_address_reg){
        return true;
    }else{
        return false;
    }
}

//Test if the address corresponds to a correct register memory
//return true if the address is correct, false otherwise
//word_t i :    the address we want to test
bool MemoryTest::isValidInputRegister(word_t i) const{
    //in this test class, input and holding registers are the same
    return isValidHoldingRegister(i);
}

//Test if the address corresponds to a correct discrete memory
//return true if the address is correct, false otherwise
//word_t i :    the address we want to test
bool MemoryTest::isValidDiscreteInput(word_t i) const{
    //in this test class, discrete inputs and outputs are the same
    return isValidDiscreteOutput(i);
}

//This function reads concecutives discrete outputs
//return true if the reading successed, false otherwise
//word_t startingAddress :  the address of the first bit we want to read
//word_t nbData :           the number of bits we want to read
//bit_t * data :            the array where we want to put the readed bits
bool MemoryTest::readDiscreteOutputs(word_t startingAddress, word_t nbData,
                                     bit_t * data) const{
    bool retval=true;
    try{
        for(int i=0; i<nbData; i++){
            data[i] = _coils[i+startingAddress];
        }
    }catch(...){    //catch all the exceptions
        retval = false;
    }
    return retval;
}

//This function reads concecutives discrete inputs
//return true if the reading successed, false otherwise
//word_t startingAddress :  the address of the first bit we want to read
//word_t nbData :           the number of bits we want to read
//bit_t * data :            the array where we want to put the readed bits
bool MemoryTest::readDiscreteInputs(word_t startingAddress, word_t nbData,
                                    bit_t * data) const{
    //in this test class, discrete inputs and outputs are the same
    return readDiscreteOutputs(startingAddress, nbData, data);
}

//This function reads concecutives holding registers
//return true if the reading successed, false otherwise
//word_t startingAddress :  the address of the first register we want to read
//word_t nbData :           the number of registers we want to read
//word_t * data :           the array where we want to put the readed registers
bool MemoryTest::readHoldingRegisters(word_t startingAddress, word_t nbData,
                                        word_t * data) const{
    bool retval=true;
    try{
        for(int i=0; i<nbData; i++){
            data[i] = _registers[i+startingAddress];
        }
    }catch(...){
        retval = false;
    }
    return retval;
}

//This function reads concecutives input registers
//return true if the reading successed, false otherwise
//word_t startingAddress :  the address of the first register we want to read
//word_t nbData :           the number of registers we want to read
//word_t * data :           the array where we want to put the readed registers
bool MemoryTest::readInputRegisters(word_t startingAddress, word_t nbData,
                                    word_t * data) const{
    //in this test class, input and holding registers are the same
    return readHoldingRegisters(startingAddress, nbData, data);
}

//This function writes one discrete output
//return true if the writing successed, false otherwise
//word_t address :          the address of the bit we want to write
//bit_t value :             the value we want to write
bool MemoryTest::writeSingleOutput(word_t address, bit_t value){
    bool retval=true;
    try{
        _coils[address] = value;
    }catch(...){
        retval = false;
    }
    return retval;
}

//This function writes one holding register
//return true if the writing successed, false otherwise
//word_t address :          the address of the register we want to write
//word_t value :            the value we want to write
bool MemoryTest::writeHoldingRegister(word_t address, word_t value){
    bool retval=true;
    try{
        _registers[address] = value;
    }catch(...){
        retval = false;
    }
    return retval;
}

//This function writes concecutive discrete outputs
//return true if the writing successed, false otherwise
//word_t address :          the address of the first bit we want to write
//word_t nbData :           the number of bits we want to write
//bit_t* data :             the values we want to write
bool MemoryTest::writeMultipleOutputs(word_t address, word_t nbData,
                                        bit_t* data){
    bool retval=true;
    try{
        for(int i=0; i< nbData; i++){
            _coils[address+i] = data[i];
        }
    }catch(...){
        retval = false;
    }
    return retval;
}

//This function writes concecutive holding registers
//return true if the writing successed, false otherwise
//word_t address :          the address of the first register we want to write
//word_t nbData :           the number of registers we want to write
//word_t* data :            the values we want to write
bool MemoryTest::writeMultipleRegisters(word_t address, word_t nbData,
                                        word_t* data){
    bool retval=true;
    try{
        for(int i=0; i< nbData; i++){
            _registers[address+i] = data[i];
        }
    }catch(...){
        retval = false;
    }
    return retval;
}
