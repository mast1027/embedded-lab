//
// Created by stefan on 05.04.24.
//

#ifndef EMBEDDED_LAB_SATELLITENETWORK_H
#define EMBEDDED_LAB_SATELLITENETWORK_H


#include "Satellite.h"

class SatelliteNetwork {
private:
    static const int num_satellites = 24;
    static Satellite satellite_array[num_satellites];

public:
    // Constructor
    SatelliteNetwork();

    static void initializeSatellites();

    static Satellite *getSatellite(size_t n);

    int getNumSatellites() const;
};


#endif //EMBEDDED_LAB_SATELLITENETWORK_H
