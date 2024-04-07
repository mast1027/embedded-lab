//
// Created by stefan on 05.04.24.
//

#ifndef EMBEDDED_LAB_SATELLITENETWORK_H
#define EMBEDDED_LAB_SATELLITENETWORK_H


#include "Satellite.h"
#include "globals.h"

class SatelliteNetwork {
private:
    static const int num_satellites = 24;
    Satellite satellite_array[num_satellites];

public:
    // Constructor
    SatelliteNetwork();

    void initializeSatellites();

    Satellite *getSatellite(size_t n);

    [[nodiscard]] static int getNumSatellites();

    // cross-correlate all satellites and return the satellite with the highest correlation
    std::vector<Satellite *> getSatellitesWithHighestCorrelation();
};


#endif //EMBEDDED_LAB_SATELLITENETWORK_H
