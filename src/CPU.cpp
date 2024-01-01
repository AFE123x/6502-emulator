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
    std::cout<<"CPU Status"<<std::endl;
    std::cout<<"Clock_cycles: Accumulated: "<<total_clocks<<" On instruction "<<static_cast<int>(clocks)<<std::endl;
    std::cout<<"Register values:   A: "<<static_cast<int>(A)<<std::endl;
    std::cout<<"Program counter: "<<PC<<std::endl;
 }
/**
 * @brief executes our instructions, and figures out situation with clock cycle
 * If there's no remaining clockcycles, it'll start executing new instruction, 
 * otherwise, do not execute. 
 */

void CPU::execute(){
   if(clocks == 0){
        uint8_t instruction = fetch();
        switch(instruction){
            case 0xA9:
                resetFlag();
                A = fetch();
                P = (A == 0) ? P | Zero : P | 0;
                P = (A & 0x80) ? P | negative : P | 0;
                clocks = 2;
                break;
            default:
                std::cout<<"No instruction defined"<<std::endl;

                
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
    // Initialize memory to zeros (or any other initial values)
    std::fill(memory, memory + sizeof(memory), 0);
}

int main(int argc, char** argv){
    CPU* cpu = new CPU();
    cpu->memory[0xFFFC] = 0;
    cpu-> memory[0xFFFD] = 0x80;
    cpu->memory[0x8000] = 0xA9;
    cpu->memory[0x8001] = 0x45;
    cpu->reset();
    char b = 'n';
    while(b = 'n'){
        cpu->printstatus();
        std::cin>>b;
        cpu->execute();
    }
    delete cpu;

    return 0;
}
