//
// Created by stefan on 05.04.24.
//

#ifndef EMBEDDED_LAB_SATELLITE_H
#define EMBEDDED_LAB_SATELLITE_H


#include <array>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include "globals.h"

class Satellite {
private:
    u_short regPos_1;
    u_short regPos_2;
    std::array<u_short, 10> shift_register_1;
    std::array<u_short, 10> shift_register_2;
    std::array<u_short, 1023> chip_sequence;

    u_short advanceShiftRegister_1();

    u_short advanceShiftRegister_2();

    ushort getNextChipSequenceValue();

    void initializeChipSequence();


public:
    // Constructors
    Satellite();

    Satellite(u_short regPos_1, u_short regPos_2);

    [[nodiscard]] const std::array<u_short, 1023> &getChipSequence() const;

    void printRegistersPositions() const;

    void printShiftRegisters() const;

    void printChipSequence() const;

    [[nodiscard]] bool chipSequenceStartsWith(const std::array<u_short, 12> &sequence) const;
};


#endif //EMBEDDED_LAB_SATELLITE_H
