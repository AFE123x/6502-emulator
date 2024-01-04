#ifndef CPU_HPP
#define CPU_HPP
#include<cstdint>
#include<iostream>
#include<fstream>
/**
 * @brief Header file containing all the declarations for
 * The CPU class
 */
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

        //clock variables
        uint8_t clocks; //clock cycles in instruction
        uint32_t total_clocks; //total accumulated.

        //public cpu functions
        void reset();
        void execute();
        void load(std::string fileName);
        void printstatus();
        typedef struct{
            
        }instruction;
        char flags[8] = "NOBDIZC";
    private:
    void initMemory();
    void resetFlag();
    uint8_t fetch();
};

#endif