//
// Created by stefan on 05.04.24.
//

#include <cassert>
#include "SatelliteNetwork.h"

SatelliteNetwork::SatelliteNetwork() {
    SatelliteNetwork::initializeSatellites();
    int n = getSatellite(0)->getRegisterLength();
    double exponent = (n + 2) / 2.0;
    double delta_one_satellite = pow(-2, exponent) - 1;
    double max_delta = delta_one_satellite * satellites_to_search;
    double tmp = getSatellite(0)->getChipSequenceLength() - max_delta;
    threshold = tmp;
}

// initialize all satellites, test some if DEBUG_MODE is enabled
void SatelliteNetwork::initializeSatellites() {
    Timer timer("SatelliteNetwork::initializeSatellites");
    satellite_array[0] = Satellite(0, 1, 5);
    satellite_array[1] = Satellite(1, 2, 6);
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
    satellite_array[23] = Satellite(23, 3, 5);

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
Satellite *SatelliteNetwork::getSatellitesWithHighestCorrelation() {
    Timer timer("SatelliteNetwork::getSatellitesWithHighestCorrelation");
    static Satellite satellitesWithHighestCorrelation[satellites_to_search];  // Static to avoid returning a pointer to local stack memory.
    if (DEBUG_MODE) {
        std::cout << "Threshold: " << threshold << std::endl;
    }

    int counter = 0;
    // iterate over all satellites
    for (int i = 0; i < num_satellites; ++i) {
        if (counter >= satellites_to_search) {
            break;
        }
        Satellite *sat = getSatellite(i);
        CorrelationResult result = sat->getLastCorrelationResult();
        if (abs(result.correlationValue) > threshold) {
            satellitesWithHighestCorrelation[counter] = *sat;
            counter++;
        }
    }

    return satellitesWithHighestCorrelation;
}

