#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <sstream>
#include "SatelliteNetwork.h"
#include "globals.h"

int main(int argc, char *argv[]) {
    // Setup Satellite Network
    SatelliteNetwork network = SatelliteNetwork();

    if (DEBUG_MODE) {
        for (int i = 0; i < network.getNumSatellites(); i++) {
            std::cout << "Satellite "
                      << std::setw(2)    // Set the width to 2 characters
                      << std::setfill(' ') // Fill with ' ' if the number has less than 2 characters
                      << i + 1 << " = ";
            SatelliteNetwork::getSatellite(i)->printRegistersPositions();
            std::cout << "\t";
            SatelliteNetwork::getSatellite(i)->printChipSequence();
            std::cout << std::endl;
        }
    }

    // read commandline arguments
    if (argc < 2) {
        std::cerr << "Error: No file specified. Please provide a file path as an argument." << std::endl;
        return 1; // Return an error code
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

    if (DEBUG_MODE) {
        //get length of receivedData

        // print parsed receivedData
        std::cout << "Parsed receivedData[" << receivedData.size() << "]:" << std::endl;
        for (int i = 0; i < receivedData.size(); i++) {
            std::cout << receivedData[i] << " ";
        }
        std::cout << std::endl;
    }


    return 0;
}
