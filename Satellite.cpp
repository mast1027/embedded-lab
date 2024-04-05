//
// Created by stefan on 05.04.24.
//

#include <iomanip>
#include "Satellite.h"

// Constructors
Satellite::Satellite() : register_1(0), register_2(0),
                         shift_register{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, chip_sequence{0} {}

Satellite::Satellite(u_short reg1, u_short reg2) : register_1(reg1), register_2(reg2),
                                                   shift_register{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, chip_sequence{0} {}

// Getter for register_1
u_short Satellite::getRegister1() const {
    return register_1;
}

// Setter for register_1
void Satellite::setRegister1(u_short value) {
    register_1 = value;
}

// Getter for register_2
u_short Satellite::getRegister2() const {
    return register_2;
}

// Setter for register_2
void Satellite::setRegister2(u_short value) {
    register_2 = value;
}

// Getter for shift register array
const std::array<u_short, 10> &Satellite::getShiftRegister() const {
    return shift_register;
}

// Setter for a specific value in the shift register array
void Satellite::setShiftRegisterValue(size_t index, u_short value) {
    if (index < shift_register.size()) {
        shift_register[index] = value;
    }
}

// Getter for chip_sequence
const std::array<unsigned short, 1023> &Satellite::getChipSequence() const {
    return chip_sequence;
}

// Setter for a specific value in chip_sequence
void Satellite::setChipSequenceValue(size_t index, unsigned short value) {
    if (index < chip_sequence.size()) {
        chip_sequence[index] = value;
    }
}

void Satellite::printRegisters() {
    std::cout << "["
              << std::setw(2) << std::setfill(' ') << register_1 + 1
              << ", "
              << std::setw(2) << std::setfill(' ') << register_2 + 1
              << "]";
}
