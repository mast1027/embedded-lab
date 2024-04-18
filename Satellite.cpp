//
// Created by stefan on 05.04.24.
//

#include <iomanip>
#include "Satellite.h"

// Constructors
Satellite::Satellite() : regPos_1(0), regPos_2(0),
                         shift_register_1{1}, shift_register_2{1},
                         chip_sequence{0}, satellite_id(-1) {}

Satellite::Satellite(short id, unsigned short reg1, unsigned short reg2) : regPos_1(reg1), regPos_2(reg2),
                                                                           shift_register_1{1},
                                                                           shift_register_2{1},
                                                                           chip_sequence{0}, satellite_id(id) {
    initializeChipSequence();
}


// print register positions for gold-code generator
void Satellite::printRegistersPositions() const {
    std::cout << "["
              << std::setw(2) << std::setfill(' ') << regPos_1 + 1
              << ", "
              << std::setw(2) << std::setfill(' ') << regPos_2 + 1
              << "]";
}

// print shift registers for gold-code generator
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

// print chip sequence
void Satellite::printChipSequence() const {
    short tmp = 0;
    std::cout << "Chip Sequence: ";
    for (auto &i: chip_sequence) {
        tmp = i;
        if (tmp < 0) {
            tmp = 0;
        }
        std::cout << tmp;
    }
}

// advance shift register 1 by one step
unsigned short Satellite::advanceShiftRegister_1() {
    // XOR the 3rd and 10th bit
    unsigned short new_bit_sr1 = shift_register_1[2] ^ shift_register_1[9];
    // Shift all bits to the right
    for (unsigned long i = register_length - 1; i > 0; i--) {
        shift_register_1[i] = shift_register_1[i - 1];
    }
    // Set the first bit to the new bit
    shift_register_1[0] = new_bit_sr1;
    return new_bit_sr1;
}

// advance shift register 2 by one step
unsigned short Satellite::advanceShiftRegister_2() {
    // XOR the bits   2, 3, 6, 8, 9 and 10
    // array position 1, 2, 5, 7, 8 and 9
    unsigned short new_bit_sr2 = shift_register_2[1] ^ shift_register_2[2] ^ shift_register_2[5] ^ shift_register_2[7] ^
                                 shift_register_2[8] ^ shift_register_2[9];
    // Shift all bits to the right
    for (unsigned long i = register_length - 1; i > 0; i--) {
        shift_register_2[i] = shift_register_2[i - 1];
    }
    // Set the first bit to the new bit
    shift_register_2[0] = new_bit_sr2;
    return new_bit_sr2;
}

// get next chip sequence value (gold-code generator)
short Satellite::getNextChipSequenceValue() {
    //fetch last value from shift register 1
    unsigned short last_bit_sr1 = shift_register_1[9];
    //fetch regPos_1 value from shift register 2
    unsigned short regBit_1 = shift_register_2[regPos_1];
    //fetch regPos_2 value from shift register 2
    unsigned short regBit_2 = shift_register_2[regPos_2];

    // advance shift register 1
    advanceShiftRegister_1();
    // advance shift register 2
    advanceShiftRegister_2();

    // XOR the bits and return value
    return (regBit_1 ^ regBit_2) ^ last_bit_sr1;
}

// initialize chip sequence (gold-code generator)
void Satellite::initializeChipSequence() {
    unsigned short tmp = 0;
    for (unsigned short &i: chip_sequence) {
        tmp = getNextChipSequenceValue();
        if (tmp == 0) {
            i = -1;
        } else {
            i = tmp;
        }
    }
}

// cross-correlate satellite with received data
void Satellite::crossCorrelate(const int receivedData[RECEIVED_DATA_LENGTH]) {
    Timer timer("Satellite::crossCorrelate[" + std::to_string(this->satellite_id) + "]");
    int maxCorrelation = 0; // initial value for the maximum correlation
    int bestShift = 0;

    // iterate over the received data
    for (int shift = 0; shift < RECEIVED_DATA_LENGTH; ++shift) {
        int sum = 0; // sum for the current shift
        // iterate over the chip sequence
        for (int i = 0; i < register_length; ++i) {
            // use modulo to wrap around the received data
            int receivedIndex = shift + i;
            sum += receivedData[receivedIndex] * this->chip_sequence[i];
        }
        // check if the current shift has a higher correlation than the previous maximum
        if (abs(sum) > abs(maxCorrelation)) {
            maxCorrelation = sum;
            bestShift = shift;
        }
    }
    this->lastCorrelationResult = {bestShift, maxCorrelation};
}

// get last correlation result
CorrelationResult Satellite::getLastCorrelationResult() {
    return lastCorrelationResult;
}

// get satellite id number
short Satellite::getSatelliteId() const {
    return this->satellite_id;
}

int Satellite::getRegisterLength() {
    return register_length;
}

int Satellite::getChipSequenceLength() {
    return chip_sequence_length;
}
