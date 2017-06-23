/***
 * This file is an example of the MemInterface interface implementation
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

#ifndef MEMORYTEST_H
#define MEMORYTEST_H

#include <MemInterface.h>
#include <vector>

#define NBCOILS         50      //number of discrete inputs/outputs of our memory (bits)
#define NBREGISTERS     20      //number of inputs/outputs registers of our memory (16 bits words)

/***
 * This class is an implementation of the MemInterface interface.
 * Note that in this example we consider that the input discrete memory
 * and the output discrete memory are the same.
 * We do the same for the holding registers and the input registers
 * (it is for instance the case for some TSX PLCs).
 * The bit_t, byte_t and word_t types are defined in MemInterface.h
 ***/
class MemoryTest : public MemInterface
{
    public:
        MemoryTest(word_t nbInputCoils = NBCOILS, word_t nbRegisters = NBREGISTERS);
        ~MemoryTest();

        //Implementation of the interface functions
        bool isValidDiscreteOutput(word_t i) const;
        bool isValidDiscreteInput(word_t i) const;
        bool isValidHoldingRegister(word_t i) const;
        bool isValidInputRegister(word_t i) const;
        bool readDiscreteOutputs(word_t startingAddress, word_t nbData, bit_t * data) const;
        bool readDiscreteInputs(word_t startingAddress, word_t nbData, bit_t * data) const;
        bool readHoldingRegisters(word_t startingAddress, word_t nbData, word_t * data) const;
        bool readInputRegisters(word_t startingAddress, word_t nbData, word_t * data) const;
        bool writeSingleOutput(word_t address, bit_t value);
        bool writeHoldingRegister(word_t address, word_t value);
        bool writeMultipleOutputs(word_t address, word_t nbData, bit_t* data);
        bool writeMultipleRegisters(word_t address, word_t nbData, word_t* data);

    private:
        std::vector<bit_t> _coils;          //the vector corresponding to the discrete memory
        std::vector<word_t> _registers;     //the vector corresponding to the register memory
        word_t _min_address_coil;           //the first discrete memory address
        word_t _max_address_coil;           //the last discrete memory address
        word_t _min_address_reg;            //the first register memory address
        word_t _max_address_reg;            //the last register memory address
        void initMemory();                  //A function to test several initialization while
                                            //  developping a client for instance
};

#endif // MEMORYTEST_H
