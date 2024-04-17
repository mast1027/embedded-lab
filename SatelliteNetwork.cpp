//
// Created by stefan on 05.04.24.
//

#include <cassert>
#include "SatelliteNetwork.h"

SatelliteNetwork::SatelliteNetwork() {
    SatelliteNetwork::initializeSatellites();
}

// initialize all satellites, test some if DEBUG_MODE is enabled
void SatelliteNetwork::initializeSatellites() {
    Timer timer("SatelliteNetwork::initializeSatellites");
    std::array<u_short, 12> check_array{};

    satellite_array[0] = Satellite(0, 1, 5);
    if (DEBUG_MODE) {
        check_array = {1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1};
        assert(satellite_array[0].chipSequenceStartsWith(check_array));
    }


    satellite_array[1] = Satellite(1, 2, 6);
    if (DEBUG_MODE) {
        check_array = {1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1};
        assert(satellite_array[1].chipSequenceStartsWith(check_array));
    }

    satellite_array[2] = Satellite(2, 3, 7);
    satellite_array[3] = Satellite(3, 4, 8);
    satellite_array[4] = Satellite(4, 0, 8);
    satellite_array[5] = Satellite(5, 1, 9);
    satellite_array[6] = Satellite(6, 0, 7);
    satellite_array[7] = Satellite(7, 1, 8);
    satellite_array[8] = Satellite(8, 2, 9);
    satellite_array[9] = Satellite(9, 1, 2);
    satellite_array[10] = Satellite(10, 2, 3);


    satellite_array[11] = Satellite(11, 4, 5);
    if (DEBUG_MODE) {
        check_array = {1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1};
        assert(satellite_array[11].chipSequenceStartsWith(check_array));
    }
    satellite_array[12] = Satellite(12, 5, 6);
    satellite_array[13] = Satellite(13, 6, 7);
    satellite_array[14] = Satellite(14, 7, 8);
    satellite_array[15] = Satellite(15, 8, 9);
    satellite_array[16] = Satellite(16, 0, 3);
    satellite_array[17] = Satellite(17, 1, 4);
    satellite_array[18] = Satellite(18, 2, 5);
    satellite_array[19] = Satellite(19, 3, 6);
    satellite_array[20] = Satellite(20, 4, 7);
    satellite_array[21] = Satellite(21, 5, 8);


    satellite_array[22] = Satellite(22, 0, 2);
    if (DEBUG_MODE) {
        check_array = {1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1};
        assert(satellite_array[22].chipSequenceStartsWith(check_array));
    }


    satellite_array[23] = Satellite(23, 3, 5);
    if (DEBUG_MODE) {
        check_array = {1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0};
        assert(satellite_array[23].chipSequenceStartsWith(check_array));
    }
}

// get satellite by index
Satellite *SatelliteNetwork::getSatellite(size_t n) {
    if (n < num_satellites) {
        return &satellite_array[n];
    } else {
        return nullptr; // Return nullptr if out of bounds
    }
}

// get number of satellites
int SatelliteNetwork::getNumSatellites() {
    return num_satellites;
}

// cross-correlate all satellites and return the satellite with the highest correlation
std::vector<Satellite *> SatelliteNetwork::getSatellitesWithHighestCorrelation() {
    Timer timer("SatelliteNetwork::getSatellitesWithHighestCorrelation");
    std::vector<Satellite *> satellitesWithHighestCorrelation;
    int n = getSatellite(0)->getRegisterLength();
    double exponent = (n + 2) / 2.0;
    double delta_one_satellite = pow(-2, exponent) - 1;
    double max_delta = delta_one_satellite * satellites_to_search;
    double threshold = getSatellite(0)->getChipSequenceLength() - max_delta;

    if (DEBUG_MODE) {
        std::cout << "Threshold: " << threshold << std::endl;
    }

    // iterate over all satellites
    for (int i = 0; i < num_satellites; ++i) {
        Satellite *sat = getSatellite(i);
        CorrelationResult result = sat->getLastCorrelationResult();
        if (abs(result.correlationValue) > threshold) {
            satellitesWithHighestCorrelation.push_back(sat);

        }
    }

    return satellitesWithHighestCorrelation;
}

