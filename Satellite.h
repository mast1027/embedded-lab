//
// Created by stefan on 05.04.24.
//

#ifndef EMBEDDED_LAB_SATELLITE_H
#define EMBEDDED_LAB_SATELLITE_H


#include <array>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "globals.h"

struct CorrelationResult {
    int delta;
    int correlationValue;
};

class Satellite {
private:
    u_short regPos_1;
    u_short regPos_2;
    short satellite_id;
    std::array<u_short, 10> shift_register_1;
    std::array<u_short, 10> shift_register_2;
    std::array<short, 1023> chip_sequence;

    u_short advanceShiftRegister_1();   // advance shift register 1 by one step

    u_short advanceShiftRegister_2();   // advance shift register 2 by one step

    short getNextChipSequenceValue();  // get next chip sequence value (gold-code generator)

    void initializeChipSequence();      // initialize chip sequence

    CorrelationResult lastCorrelationResult; // last correlation result


public:
    // Constructors
    Satellite();

    Satellite(short satellite_id, u_short regPos_1, u_short regPos_2);

    void printRegistersPositions() const; // print register positions for gold-code generator

    [[nodiscard]] short getSatelliteId() const; // get satellite id number

    [[maybe_unused]]void printShiftRegisters() const; // print shift registers for gold-code generator

    void printChipSequence() const;

    // check if chip sequence starts with given sequence
    [[nodiscard]] bool chipSequenceStartsWith(const std::array<u_short, 12> &sequence) const;

    [[maybe_unused]] void
    crossCorrelate(const std::vector<int> &receivedData); // cross-correlate satellite with received data

    CorrelationResult getLastCorrelationResult(); // get last correlation result

};


#endif //EMBEDDED_LAB_SATELLITE_H
