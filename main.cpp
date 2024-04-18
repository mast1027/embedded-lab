#include <iostream>
#include <iomanip>
#include <fstream>
#include "SatelliteNetwork.h"
#include "globals.h"
#include "timer.h"

int main(int argc, char *argv[]) {
    Timer timer("main");
    // read commandline arguments
    if (argc < 2) {
        std::cerr << "Error: No file specified. Please provide a file path as an argument." << std::endl;
        return 1; // Return an error code
    }

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

    // open file
    std::ifstream file(argv[1]); // Open the file specified by the command line
    if (!file) {
        std::cerr << "Error: File cannot be opened." << std::endl;
        return 1; // Return an error code
    }

    // parse file
    Timer parseFile = Timer("parseFile");
    int receivedData[RECEIVED_DATA_LENGTH * 2] = {0}; // Array to store receivedData
    int number;
    int i = 0;
    while (file >> number) { // Read receivedData from the file
        receivedData[i] = number; // Store the receivedData in the array
        receivedData[i + RECEIVED_DATA_LENGTH] = number;
        i++;
    }
    file.close(); // Close the file
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
        //ToDo: optimize this part by parallelizeing the for loop on n cores
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
