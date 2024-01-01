#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

int main() {
    // Example machine code (replace this with your actual machine code)
    uint8_t machinecode[65536];
    
    machinecode[0xFFFC] = 0;
    machinecode[0xFFFD] = 0x80;

    // Specify the file name
    std::string fileName = "output.bin";

    // Open the file in binary mode
    std::ofstream outFile(fileName, std::ios::binary);

    if (outFile.is_open()) {
        // Write the machine code to the file
        outFile.write(reinterpret_cast<const char*>(machinecode), sizeof(machinecode));

        // Close the file
        outFile.close();

        std::cout << "Machine code written to " << fileName << std::endl;
    } else {
        std::cerr << "Error opening file " << fileName << std::endl;
        return 1; // Return an error code
    }

    return 0; // Return success
}
