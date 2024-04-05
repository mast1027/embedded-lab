//
// Created by stefan on 05.04.24.
//

#ifndef EMBEDDED_LAB_SATELLITE_H
#define EMBEDDED_LAB_SATELLITE_H


#include <array>
#include <cstddef>
#include <cstdlib>
#include <iostream>

class Satellite {
private:
    u_short register_1;
    u_short register_2;
    std::array<u_short, 10> shift_register;
    std::array<unsigned short, 1023> chip_sequence;


public:
    // Constructors
    Satellite();

    Satellite(u_short reg1, u_short reg2);

    // Getter and setter methods for register_1
    u_short getRegister1() const;

    void setRegister1(u_short value);

    // Getter and setter methods for register_2
    u_short getRegister2() const;

    void setRegister2(u_short value);


    // Method to access the shift register array
    const std::array<u_short, 10> &getShiftRegister() const;

    // Method to modify a specific value in the shift register array
    void setShiftRegisterValue(size_t index, u_short value);

    const std::array<u_short, 1023> &getChipSequence() const;

    void setChipSequenceValue(size_t index, u_short value);

    void printRegisters();
};


#endif //EMBEDDED_LAB_SATELLITE_H
