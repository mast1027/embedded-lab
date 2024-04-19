#include <iostream>
#include <iomanip>
#include <fstream>
#include "SatelliteNetwork.h"
#include "globals.h"
#include "timer.h"

int main(int argc, char *argv[]) {
     // Setup Satellite Network
    SatelliteNetwork network = SatelliteNetwork();

    // print satellite network
    if (DEBUG_MODE) {
        std::cout << "############ Satellite Infos ###########" << std::endl;
        for (int i = 0; i < network.getNumSatellites(); i++) {
            std::cout << "Satellite "
                      << std::setw(2)    // Set the width to 2 characters
                      << std::setfill(' ') // Fill with ' ' if the number has less than 2 characters
                      << network.getSatellite(i)->getSatelliteId() + 1 << " = ";
            network.getSatellite(i)->printRegistersPositions();
            std::cout << "\t";
            network.getSatellite(i)->printChipSequence();
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }


    // parse file
    Timer parseFile = Timer("parseFile");
    int receivedData[RECEIVED_DATA_LENGTH * 2] = {0}; // Array to store receivedData
    for (int i = 0; i < RECEIVED_DATA_LENGTH; i++) {
        receivedData[i] = INIT_DATA[i];
        receivedData[i + RECEIVED_DATA_LENGTH] = i;
    }
    parseFile.~Timer(); // Stop the timer

    // print received data
    if (DEBUG_MODE) {
        std::cout << "############ Received Data ###########" << std::endl;
        for (int i: receivedData) {
            std::cout << i << " ";
        }
        std::cout << std::endl << std::endl;
    }


    if (DEBUG_MODE) {
        std::cout << "############ Correlation Results ###########" << std::endl;
    }
    Timer crossCorrelate = Timer("crossCorrelate");
    // cross-correlate all satellites
    for (int i = 0; i < network.getNumSatellites(); i++) {
        network.getSatellite(i)->crossCorrelate(receivedData);
        if (DEBUG_MODE) {
            std::cout << "Satellite " << i + 1 << " correlation result: ";
            std::cout << " Correlation: "
                      << network.getSatellite(i)->getLastCorrelationResult().correlationValue
                      << " Delta: " << network.getSatellite(i)->getLastCorrelationResult().delta << std::endl;
        }
    }
    crossCorrelate.~Timer(); // Stop the timer
    if (DEBUG_MODE) {
        std::cout << std::endl;
    }

    // get satellites with the highest correlation
    Satellite *bestSatellites = network.getSatellitesWithHighestCorrelation();
    for (int i = 0; i < 4; i++) {
        auto bestSatellite = &bestSatellites[i];
        std::cout << "Satellite "
                  << std::setw(2)
                  << std::setfill(' ')
                  << bestSatellite->getSatelliteId() + 1 << " ";

        if (bestSatellite->getLastCorrelationResult().correlationValue > 0) {
            std::cout << " has sent bit 1 (delta = " << bestSatellite->getLastCorrelationResult().delta
                      << ")";
        } else if (bestSatellite->getLastCorrelationResult().correlationValue < 0) {
            std::cout << " has sent bit 0 (delta = " << bestSatellite->getLastCorrelationResult().delta
                      << ")";
        } else {
            std::cout << "No correlation found." << std::endl;
        }
        if (DEBUG_MODE) {
            std::cout << "\tCorrelation Value = " << bestSatellite->getLastCorrelationResult().correlationValue;
        }
        std::cout << std::endl;
    }
    return 0;
}
