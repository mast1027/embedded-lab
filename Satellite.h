//
// Created by stefan on 05.04.24.
//

#ifndef EMBEDDED_LAB_SATELLITE_H
#define EMBEDDED_LAB_SATELLITE_H


#include <iostream>
#include "globals.h"
#include <cmath>
#include "timer.h"

struct CorrelationResult {
    int delta;
    int correlationValue;
};

class Satellite {
private:
    unsigned short regPos_1;
    unsigned short regPos_2;
    short satellite_id;
    static const int register_length = 10;
    static const int chip_sequence_length = 1023;
    unsigned short shift_register_1[register_length];
    unsigned short shift_register_2[register_length];
    unsigned short chip_sequence[chip_sequence_length];

    unsigned short advanceShiftRegister_1();   // advance shift register 1 by one step

    unsigned short advanceShiftRegister_2();   // advance shift register 2 by one step

    short getNextChipSequenceValue();  // get next chip sequence value (gold-code generator)

    void initializeChipSequence();      // initialize chip sequence

    CorrelationResult lastCorrelationResult; // last correlation result


public:
    // Constructors
    Satellite();

    Satellite(short satellite_id, unsigned short regPos_1, unsigned short regPos_2);

    static int getRegisterLength(); // get register length

    static int getChipSequenceLength(); // get chip sequence length

    void printRegistersPositions() const; // print register positions for gold-code generator

    [[nodiscard]] short getSatelliteId() const; // get satellite id number

    [[maybe_unused]]void printShiftRegisters() const; // print shift registers for gold-code generator

    void printChipSequence() const;

    [[maybe_unused]] void
    crossCorrelate(const int receivedData[RECEIVED_DATA_LENGTH]); // cross-correlate satellite with received data

    CorrelationResult getLastCorrelationResult(); // get last correlation result

};


#endif //EMBEDDED_LAB_SATELLITE_H
