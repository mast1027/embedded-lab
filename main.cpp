#include <iostream>
#include <iomanip>
#include "SatelliteNetwork.h"

u_short satellite_registers[24][2] =
        {{1, 5},
         {2, 6},
         {3, 7},
         {4, 8},
         {0, 8},
         {1, 9},
         {0, 7},
         {1, 8},
         {2, 9},
         {1, 2},
         {2, 3},
         {4, 5},
         {5, 6},
         {6, 7},
         {7, 8},
         {8, 9},
         {0, 3},
         {1, 4},
         {2, 5},
         {3, 6},
         {4, 7},
         {5, 8},
         {0, 2},
         {3, 5}};
u_short satellite_shift_registers[24][10] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                             {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                             {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                             {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                             {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                             {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                             {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                             {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                             {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                             {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                             {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                             {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                             {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                             {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                             {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                             {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                             {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                             {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                             {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                             {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                             {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                             {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                             {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                             {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},};

u_short satellite_chip_sequence[24][1023] = {0};

int main() {
    SatelliteNetwork network = SatelliteNetwork();
    for (int i = 0; i < network.getNumSatellites(); i++) {
        std::cout << "Satellite #"
                  << std::setw(2)    // Set the width to 2 characters
                  << std::setfill(' ') // Fill with ' ' if the number has less than 2 characters
                  << i + 1 << " = ";
        SatelliteNetwork::getSatellite(i)->printRegisters();
        std::cout << std::endl;
    }
    return 0;
}
