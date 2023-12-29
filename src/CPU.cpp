#include "../include/CPU.hpp"

CPU::CPU(){
    reset();
}

void CPU::reset(){
    uint8_t lo = memory[0xFFFC];
    uint8_t hi = memory[0xFFFD];
    this->PC = ( hi << 4) | lo;  // Adjust the starting address as needed
    this->S = 0xFF;
    A = X = Y = P = 0;
    initMemory();
}

void CPU::execute(uint8_t* cycles){
    while (*cycles > 0) {
        uint8_t data = getInstruction(cycles);
        std::cout << "PC: " << static_cast<int>(PC) << std::endl;  // Print PC value
        switch (data) {
            case 0xA9:
                A = getInstruction(cycles);
                resetFlag();
                if (A == 0) {
                    P |= Zero;
                }
                if (A & 0b10000000) {
                    P |= negative;
                }
                break;
        }
    }
}
void CPU::load(std::string fileName){
    std::ifstream inFile(fileName, std::ios::binary);
     if (inFile.is_open()) {
        // Read the content of the file into the memory array
        inFile.read(reinterpret_cast<char*>(memory), sizeof(memory));

        // Close the file
        inFile.close();

    } else {
        std::cerr << "Error opening file " << fileName << std::endl;
    }
}
void CPU::resetFlag(){
    P = 0;
}

uint8_t CPU::getInstruction(uint8_t* cycles){
    (*cycles)--;
    uint8_t instruction = memory[PC];
    PC++;  // Increment the program counter
    std::cout << "instruction: " << static_cast<int>(instruction) << std::endl;
    return instruction;
}

void CPU::initMemory(){
    // Initialize memory to zeros (or any other initial values)
    std::fill(memory, memory + sizeof(memory), 0);
}

int main(int argc, char** argv){
    CPU* cpu = new CPU();
    uint8_t aoeu = 2;
    cpu->load("../output.bin");
    for(int i = 0; i < 0xFFFC; i++){
        cpu->execute(&aoeu);
    }
    
    delete cpu;

    return 0;
}
