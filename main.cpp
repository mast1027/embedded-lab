#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "SatelliteNetwork.h"
#include "globals.h"

int main(int argc, char *argv[]) {
    // read commandline arguments
    if (argc < 2) {
        std::cerr << "Error: No file specified. Please provide a file path as an argument." << std::endl;
        return 1; // Return an error code
    } else if (argc == 3) {
        std::string debugArg = argv[2];
        if (debugArg == "-d" || debugArg == "--debug" || debugArg == "-D" || debugArg == "--DEBUG") {
            DEBUG_MODE = true;
        }
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
    std::vector<int> receivedData; // Vector to store parsed receivedData
    int number;
    while (file >> number) { // Read receivedData from the file
        receivedData.push_back(number); // Add the number to the vector
    }
    file.close(); // Close the file

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
    if (DEBUG_MODE) {
        std::cout << std::endl;
    }

    // get satellites with highest correlation
    std::vector<Satellite *> bestSatellites = network.getSatellitesWithHighestCorrelation();
    // print results like in the assignment
    for (auto &bestSatellite: bestSatellites) {
        std::cout << "Satellite "
                  << std::setw(2)
                  << std::setfill(' ')
                  << bestSatellite->getSatelliteId() + 1 << " ";

        if (bestSatellite->getLastCorrelationResult().correlationValue > 0) {
            std::cout << " has sent bit 1 (delta = " << bestSatellite->getLastCorrelationResult().delta
                      << ")" << std::endl;
        } else if (bestSatellite->getLastCorrelationResult().correlationValue < 0) {
            std::cout << " has sent bit 0 (delta = " << bestSatellite->getLastCorrelationResult().delta
                      << ")" << std::endl;
        } else {
            std::cout << "No correlation found." << std::endl;
        }
    }


    return 0;
}
