#include "../include/CPU.hpp"
/**
 * @brief Construct a new CPU::CPU object
 *  Resets the CPU and initiliazes the memory.
 */
CPU::CPU(){
    reset();
    initMemory();
}
/**
 * @brief 6502 reset function, to reset the cpu to default values
 * it'll cost 7 clock cycles.
 *
 */
void CPU::reset() {
    uint8_t lo = memory[0xFFFC];
    uint8_t hi = memory[0xFFFD];
    std::cout << "Low: " << static_cast<int>(lo) << " High: " << static_cast<int>(hi) << std::endl;
    this->PC = (hi << 8) + lo;  // Adjust the starting address as needed
    std::cout<<"PC = "<<this->PC<<std::endl;
    this->S = 0xFF; // stack grows upwards
    A = X = Y = P = 0;
    clocks = 7; // reset costs 7 clock cycles
    total_clocks = 0;
}
/**
 * @brief Fetches value in memory where the PC is located.
 *
 * @return uint8_t data where PC is located at in memory
 */
uint8_t CPU::fetch(){
    return memory[PC++];
}
/**
 * @brief Prints out the status of the registers
 * for troubleshooting reasons.
 *
 */
void CPU::printstatus(){
    std::cout<<"***************************************************"<<std::endl;
    std::cout<<"6502 tester"<<std::endl<<std::endl;
    std::cout<<"Registers:"<<std::endl;
    std::cout<<"A = "<<static_cast<int>(A)<<"\tX = "<<static_cast<int>(X)<<"\tY = "<<static_cast<int>(Y)<<std::endl;
    std::cout<<"P = "<<static_cast<int>(P)<<"\tPC = "<<static_cast<int>(PC)<<"\tS = "<<static_cast<int>(S)<<std::endl;
    std::cout<<"flags:";
for (int i = 0; i < 7; i++) {
        std::cout << ((P >> (7 - i)) & 1 ? flags[i] : '_');
    }
    std::cout<<std::endl;
    std::cout<<"Cycles remain: "<<static_cast<int>(clocks)<<"\tcycles accum: "<<total_clocks<<std::endl;
    std::cout<<"***************************************************"<<std::endl;
 }
/**
 * @brief executes our instructions, and figures out situation with clock cycle
 * If there's no remaining clockcycles, it'll start executing new instruction,
 * otherwise, do not execute.
 */

void CPU::execute(){
   if(clocks == 0){
        uint8_t instruction = fetch();
        uint16_t temp_memory_address;
        switch(instruction){
            //LDA instructions
            case 0xA9:
                resetFlag();
                A = fetch();
                P = (A == 0) ? P | Zero : P | 0;
                P = (A & 0x80) ? P | negative : P | 0;
                clocks = 2;
                break;
            case 0xA5:
                resetFlag();
                A = memory[fetch()];
                P = (A == 0) ? P | Zero : P | 0;
                P = (A & 0x80) ? P | negative : P | 0;
                clocks = 3;
                break;
            case 0xB5:
                resetFlag();
                A = (fetch() + X) % 256;
                P = (A == 0) ? P | Zero : P | 0;
                P = (A & 0x80) ? P | negative : P | 0;
                clocks = 4;
                break;
            case 0xAD:
                resetFlag();
                A ^= A;
                temp_memory_address = fetch();
                A = fetch();
                temp_memory_address = (A<<8) | temp_memory_address;
                A = memory[temp_memory_address];
                clocks = 4;
                break;
            default:
                std::cout<<"No instruction defined"<<std::endl;
                return;
            }

        }
           clocks--;
           total_clocks++;
   }

/**
 * @brief resets our status flags
 *
 */
void CPU::resetFlag(){
    P = P ^ P;
}
/**
 * @brief Initializes all values in memory to zero;
 *
 */
void CPU::initMemory(){
    std::fill(memory, memory + sizeof(memory), 0);
}
/**
 * @brief Main function for testing instructions
 * 
 * @param argc cli argument length
 * @param argv cli argments
 * @return int to indicate return condition. 
 */
int main(int argc, char** argv){
    CPU* cpu = new CPU();
    cpu->memory[0xFFFC] = 0;
    cpu-> memory[0xFFFD] = 0x80;
    cpu->memory[0x8000] = 0xA9;
    cpu->memory[0x8001] = 0x45;
    cpu->memory[0x8002] = 0xA5;
    cpu->memory[0x8003] = 0x45;
    cpu->memory[0x0045] = 0xFF;
    cpu->memory[0x8004] = 0xAD;
    cpu->memory[0x8005] = 0x45;
    cpu->memory[0x8006] = 0x44;
    cpu->memory[0x4445] = 0x24; //36
    cpu->reset();
    char b = 'n';
    while(b == 'n'){
        cpu->printstatus();
        std::cin>>b;
        cpu->execute();
    }
    delete cpu;

    return 0;
}
