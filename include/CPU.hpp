#ifndef CPU_HPP
#define CPU_HPP
#include<cstdint>
#include<iostream>
#include<fstream>
class CPU{
    public:
        CPU(); //CPU constructor to initialize memory
         uint8_t memory[ 65536]; //16 bit memory addresses. 
        //registers
        uint8_t A; //Accumulator Register
        uint8_t X; //index register X
        uint8_t Y; //index register Y
        uint8_t P; //processor status reg
        uint16_t PC; //program counter
        uint8_t S; //stack pointer
        //status bits for P
        uint8_t negative = 0x80;
        uint8_t overflow = 0x40;
        uint8_t break_command = 0x10;
        uint8_t decimal_mode =  0x08;
        uint8_t IRQ_Disable = 0x04;
        uint8_t Zero = 0x02;
        uint8_t carry = 0x01;
        void reset();
        void execute(uint8_t* cycles);
        void load(std::string fileName);
        
    private:
    void initMemory();
    uint8_t getInstruction(uint8_t* cycles);
    void resetFlag();
};

#endif