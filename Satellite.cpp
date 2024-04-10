//
// Created by stefan on 05.04.24.
//

#include <iomanip>
#include "Satellite.h"

// Constructors
Satellite::Satellite() : regPos_1(0), regPos_2(0),
                         shift_register_1{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, shift_register_2{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                         chip_sequence{0}, satellite_id(-1) {}

Satellite::Satellite(short id, u_short reg1, u_short reg2) : regPos_1(reg1), regPos_2(reg2),
                                                             shift_register_1{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                                             shift_register_2{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
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
        if (tmp < 0){
            tmp = 0;
        }
        std::cout << tmp;
    }
}

// advance shift register 1 by one step
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

// advance shift register 2 by one step
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

// get next chip sequence value (gold-code generator)
short Satellite::getNextChipSequenceValue() {
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

    // XOR the bits and return value
    return (regBit_1 ^ regBit_2) ^ last_bit_sr1;
}

// initialize chip sequence (gold-code generator)
void Satellite::initializeChipSequence() {
    unsigned short tmp = 0;
    for (short &i: chip_sequence) {
        tmp = getNextChipSequenceValue();
        if (tmp == 0) {
            i = -1;
        } else {
            i = tmp ;
        }
    }

}

// check if chip sequence starts with given sequence, used for testing
bool Satellite::chipSequenceStartsWith(const std::array<u_short, 12> &sequence) const {
    short tmp = 0;
    for (int i = 0; i < sequence.size(); i++) {
        tmp = sequence[i];
        if (tmp == 0) {
            tmp = -1;
        }
        if (chip_sequence[i] != tmp) {
            return false;
        }
    }
    return true;
}

// cross-correlate satellite with received data
void Satellite::crossCorrelate(const std::vector<int> &receivedData) {
    int maxCorrelation = 0; // initial value for the maximum correlation
    int bestShift = 0;

    // iterate over the received data
    for (int shift = 0; shift < receivedData.size(); ++shift) {
        int sum = 0; // sum for the current shift
        // iterate over the chip sequence
        for (int i = 0; i < this->chip_sequence.size(); ++i) {
            // use modulo to wrap around the received data
            int receivedIndex = (shift + i) % receivedData.size();  // TODO: optimize mod operator?
            // ToDo: doppelte sequenz und nur einmal durchschiften
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
