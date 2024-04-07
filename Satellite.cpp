//
// Created by stefan on 05.04.24.
//

#include <iomanip>
#include "Satellite.h"

// Constructors
Satellite::Satellite() : regPos_1(0), regPos_2(0),
                         shift_register_1{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, shift_register_2{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                         chip_sequence{0} {}

Satellite::Satellite(u_short reg1, u_short reg2) : regPos_1(reg1), regPos_2(reg2),
                                                   shift_register_1{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                                   shift_register_2{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                                   chip_sequence{0} {
    initializeChipSequence();
}


void Satellite::printRegistersPositions() const {
    std::cout << "["
              << std::setw(2) << std::setfill(' ') << regPos_1 + 1
              << ", "
              << std::setw(2) << std::setfill(' ') << regPos_2 + 1
              << "]";
}

void Satellite::printShiftRegisters() const {
    std::cout << "Shift Register 1: [";
    for (auto &i: this->shift_register_1) {
        std::cout << i;
    }
    std::cout << "]\t";

    std::cout << "Shift Register 2: [";
    for (auto &i: this->shift_register_2) {
        std::cout << i;
    }
    std::cout << "]";

}

void Satellite::printChipSequence() const {
    std::cout << "Chip Sequence: ";
    for (auto &i: chip_sequence) {
        std::cout << i;
    }
}

u_short Satellite::advanceShiftRegister_1() {
    // XOR the 3rd and 10th bit
    u_short new_bit_sr1 = shift_register_1[2] ^ shift_register_1[9];
    // Shift all bits to the right
    for (u_long i = shift_register_1.size() - 1; i > 0; i--) {
        shift_register_1[i] = shift_register_1[i - 1];
    }
    // Set the first bit to the new bit
    shift_register_1[0] = new_bit_sr1;
    return new_bit_sr1;
}

u_short Satellite::advanceShiftRegister_2() {
    // XOR the bits   2, 3, 6, 8, 9 and 10
    // array position 1, 2, 5, 7, 8 and 9
    u_short new_bit_sr2 = shift_register_2[1] ^ shift_register_2[2] ^ shift_register_2[5] ^ shift_register_2[7] ^
                          shift_register_2[8] ^ shift_register_2[9];
    // Shift all bits to the right
    for (u_long i = shift_register_2.size() - 1; i > 0; i--) {
        shift_register_2[i] = shift_register_2[i - 1];
    }
    // Set the first bit to the new bit
    shift_register_2[0] = new_bit_sr2;
    return new_bit_sr2;
}

ushort Satellite::getNextChipSequenceValue() {
    //fetch last value from shift register 1
    u_short last_bit_sr1 = shift_register_1[9];
    //fetch regPos_1 value from shift register 2
    u_short regBit_1 = shift_register_2[regPos_1];
    //fetch regPos_2 value from shift register 2
    u_short regBit_2 = shift_register_2[regPos_2];

    // advance shift register 1
    advanceShiftRegister_1();
    // advance shift register 2
    advanceShiftRegister_2();

    //this->printShiftRegisters();
    //std::cout << std::endl;
    // XOR the bits and return value
    return (regBit_1 ^ regBit_2) ^ last_bit_sr1;
}

void Satellite::initializeChipSequence() {
    for (unsigned short &i: chip_sequence) {
        i = getNextChipSequenceValue();
    }

}

bool Satellite::chipSequenceStartsWith(const std::array<u_short, 12> &sequence) const {
    for (int i = 0; i < sequence.size(); i++) {
        if (chip_sequence[i] != sequence[i]) {
            return false;
        }
    }
    return true;
}
