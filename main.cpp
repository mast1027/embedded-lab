#include <iostream>
#include <iomanip>
#include "SatelliteNetwork.h"

int main() {
    SatelliteNetwork network = SatelliteNetwork();
    for (int i = 0; i < network.getNumSatellites(); i++) {
        std::cout << "Satellite #"
                  << std::setw(2)    // Set the width to 2 characters
                  << std::setfill(' ') // Fill with ' ' if the number has less than 2 characters
                  << i + 1 << " = ";
        SatelliteNetwork::getSatellite(i)->printRegistersPositions();
        std::cout << "\t";
        SatelliteNetwork::getSatellite(i)->printChipSequence();
        std::cout << std::endl;
    }
    return 0;
}
