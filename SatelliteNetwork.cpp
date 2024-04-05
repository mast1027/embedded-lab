//
// Created by stefan on 05.04.24.
//

#include <cassert>
#include "SatelliteNetwork.h"

// Initialize static member outside the class definition
Satellite SatelliteNetwork::satellite_array[SatelliteNetwork::num_satellites] = {};

SatelliteNetwork::SatelliteNetwork() {
    SatelliteNetwork::initializeSatellites();
}

// Definition of initializeSatellites method
void SatelliteNetwork::initializeSatellites() {
    std::array<u_short, 12> check_array{};

    satellite_array[0] = Satellite(1, 5);
    if (DEBUG_MODE) {
        check_array = {1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1};
        assert(satellite_array[0].chipSequenceStartsWith(check_array));
    }


    satellite_array[1] = Satellite(2, 6);
    if (DEBUG_MODE) {
        check_array = {1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1};
        assert(satellite_array[1].chipSequenceStartsWith(check_array));
    }

    satellite_array[2] = Satellite(3, 7);
    satellite_array[3] = Satellite(4, 8);
    satellite_array[4] = Satellite(0, 8);
    satellite_array[5] = Satellite(1, 9);
    satellite_array[6] = Satellite(0, 7);
    satellite_array[7] = Satellite(1, 8);
    satellite_array[8] = Satellite(2, 9);
    satellite_array[9] = Satellite(1, 2);
    satellite_array[10] = Satellite(2, 3);


    satellite_array[11] = Satellite(4, 5);
    if (DEBUG_MODE) {
        check_array = {1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1};
        assert(satellite_array[11].chipSequenceStartsWith(check_array));
    }
    satellite_array[12] = Satellite(5, 6);
    satellite_array[13] = Satellite(6, 7);
    satellite_array[14] = Satellite(7, 8);
    satellite_array[15] = Satellite(8, 9);
    satellite_array[16] = Satellite(0, 3);
    satellite_array[17] = Satellite(1, 4);
    satellite_array[18] = Satellite(2, 5);
    satellite_array[19] = Satellite(3, 6);
    satellite_array[20] = Satellite(4, 7);
    satellite_array[21] = Satellite(5, 8);


    satellite_array[22] = Satellite(0, 2);
    if (DEBUG_MODE) {
        check_array = {1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1};
        assert(satellite_array[22].chipSequenceStartsWith(check_array));
    }


    satellite_array[23] = Satellite(3, 5);
    if (DEBUG_MODE) {
        check_array = {1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0};
        assert(satellite_array[23].chipSequenceStartsWith(check_array));
    }
}

Satellite *SatelliteNetwork::getSatellite(size_t n) {
    if (n < num_satellites) {
        return &satellite_array[n];
    } else {
        return nullptr; // Return nullptr if out of bounds
    }
}

int SatelliteNetwork::getNumSatellites() const {
    return num_satellites;
}

