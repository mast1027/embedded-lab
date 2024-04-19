const int RECEIVED_DATA_LENGTH = 1023;
const extern int INIT_DATA[];


#include <iostream>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <fstream>

struct CorrelationResult {
    int delta;
    int correlationValue;
};

class Satellite {
private:
    unsigned short regPos_1;
    unsigned short regPos_2;
    short satellite_id;
    static const int register_length = 10;
    static const int chip_sequence_length = 1023;
    unsigned short shift_register_1[register_length];
    unsigned short shift_register_2[register_length];
    unsigned short chip_sequence[chip_sequence_length];

    unsigned short advanceShiftRegister_1();   // advance shift register 1 by one step

    unsigned short advanceShiftRegister_2();   // advance shift register 2 by one step

    short getNextChipSequenceValue();  // get next chip sequence value (gold-code generator)

    void initializeChipSequence();      // initialize chip sequence

    CorrelationResult lastCorrelationResult; // last correlation result


public:
    // Constructors
    Satellite();

    Satellite(short satellite_id, unsigned short regPos_1, unsigned short regPos_2);

    static int getRegisterLength(); // get register length

    static int getChipSequenceLength(); // get chip sequence length

    void printRegistersPositions() const; // print register positions for gold-code generator

    short getSatelliteId() const; // get satellite id number

    void printShiftRegisters() const; // print shift registers for gold-code generator

    void printChipSequence() const;

    void crossCorrelate(const int receivedData[RECEIVED_DATA_LENGTH]); // cross-correlate satellite with received data

    CorrelationResult getLastCorrelationResult(); // get last correlation result

};

class SatelliteNetwork {
private:
    static const int num_satellites = 24;
    static const int satellites_to_search = 4;
    Satellite satellite_array[num_satellites];
    double threshold;

public:
    // Constructor
    SatelliteNetwork();

    void initializeSatellites();

    Satellite *getSatellite(size_t n);

    [[nodiscard]] static int getNumSatellites();

    // cross-correlate all satellites and return the satellite with the highest correlation
    Satellite *getSatellitesWithHighestCorrelation();
};


const int INIT_DATA[] = {-2, -2, 2, 0, 2, 2, 0, 4, 0, -2, 2, 0, 0, 2, 0, -2, 0, -2, -4, -2, 0, 4, 2, 2, 2, -4, 2, 2, 2,
                         2, -4, -2, 2, 0, -2, -2, 0, 0, 2, -2, 0, 2, 0, 2, 0, -2, 4, 0, 0, 0, -2, -4, 0, -2, 0, -4, 0,
                         2, 0, 0, -2, -2, -2, 2, -2, 0, -2, 2, -2, -2, 2, 2, 2, 2, 0, -2, -4, 4, -2, -2, 0, 0, 2, 0, 0,
                         2, 0, -2, -4, 0, 0, -4, 2, 0, -2, 2, -2, 0, 2, 0, -4, -2, 0, -4, 0, 2, 0, 2, 2, -2, 4, 2, -2,
                         -2, 4, 0, 2, 0, 0, -2, 2, -2, 0, -4, 2, -4, -4, 0, 4, 2, -2, -2, 0, 0, -4, 0, 2, -2, 0, 2, 0,
                         0, -2, 2, 0, -2, 2, 0, 2, -2, 0, 0, -2, 0, -2, -2, -2, -4, -2, -4, 2, 0, 2, -2, 2, 4, 2, 0, 0,
                         2, 2, 0, 2, -2, 4, 2, 2, -2, 0, 2, 4, 0, 2, 0, 0, -2, 2, -2, -2, 0, 0, 0, 0, 4, -2, -2, -2, -4,
                         0, 2, 0, 0, -2, 2, 0, -2, 4, 0, 0, 0, 0, -4, 0, -4, 0, -2, 0, 0, 0, 4, 0, 2, 0, 0, 2, -2, 2, 2,
                         2, -2, 4, -2, -2, 0, 0, 2, -2, 2, 0, 0, -2, -2, -2, -4, 0, 0, -2, 4, -4, -2, 2, 0, 0, 2, 0, 2,
                         -2, -2, 2, -2, 0, -4, 2, 0, 2, -2, -2, 2, 0, 0, 0, 2, 0, 4, 0, 0, 2, 0, 2, 0, 2, 2, -2, 2, 2,
                         2, 2, 2, 2, 2, 4, -2, 4, 0, 2, -2, 2, -2, -2, 2, -2, 0, 0, -4, 4, -2, -2, 2, 2, 0, -2, 0, 0, 2,
                         2, 2, -2, 2, -2, 2, 2, -2, 0, -2, 0, 2, 2, -2, 0, 2, 0, 0, -2, 2, 0, 4, 2, 2, 0, 2, 0, 0, -2,
                         4, 0, -2, 0, 0, -2, 0, 2, 4, 0, 2, 2, 2, -2, 2, 2, -4, -2, -2, -4, 0, 0, 0, -2, 0, 2, 0, -2, 0,
                         2, -2, 0, -2, 2, 4, -2, -2, -2, 2, 0, 0, 2, 0, -2, -2, 2, 0, 0, 2, 0, 4, 0, -2, -2, 2, -2, 0,
                         -2, 0, 2, 0, -2, 0, -4, -2, -2, -4, -2, -2, 0, 2, 2, 2, -2, -2, 2, -2, 2, -2, -4, -2, 2, -2, 2,
                         0, 0, 0, -2, 0, 0, 2, 0, 2, -2, -4, 0, 0, 0, 4, -2, 4, 0, 0, -2, 0, 0, 0, 0, 2, 0, 0, 2, -4, 2,
                         -2, 0, -2, 2, -2, 0, -2, -2, -2, -2, 0, 0, -2, 0, -2, 4, 0, -2, 0, 0, 2, 0, -2, 0, 0, 0, 2, 0,
                         4, 2, -2, 0, -2, 2, 0, 2, 0, -2, 0, 0, -2, -2, 0, -2, -4, -2, -4, 0, 0, 0, 2, 2, 0, -2, 0, 0,
                         0, 0, -2, 0, 2, 2, -2, 0, -2, 4, 0, 0, 4, 0, -2, -2, 0, 2, 2, 2, 0, 2, 2, 2, 0, -2, -2, 0, 0,
                         4, -4, 2, 0, 0, 2, -2, 2, 0, 0, -2, 2, 0, 0, 2, 0, -2, 0, -4, 0, 2, 0, 2, 0, 0, -2, 2, 2, 2,
                         -2, 0, 4, 2, -4, 2, 0, -2, -2, 4, 0, 4, -2, 0, 0, 4, 0, 0, 0, 0, 4, 0, 2, 0, -2, 0, -2, 2, 2,
                         0, -2, 0, 0, 0, -2, -2, 0, 0, -2, 4, 0, 4, 4, 0, 2, -2, 2, 2, 2, 0, -4, 0, -2, -4, -2, 2, 4, 0,
                         0, 0, -2, -2, 0, 0, 4, 2, 2, -2, 0, 0, -2, 0, 2, 2, 0, 0, 0, -2, 0, -2, -2, 2, -2, 4, 2, -2,
                         -2, 0, -2, -4, 0, 0, 0, -2, 2, 4, -2, 0, -2, 2, 2, 0, 2, 2, -4, 2, -2, 2, 4, 2, 0, 2, 0, -2, 4,
                         4, -2, 0, -2, 0, 0, 2, 0, -2, 4, -2, 0, -2, 0, 0, 0, 2, 0, 2, 2, 2, 2, 2, 0, -2, 0, 0, 0, 0, 4,
                         0, 0, -4, 2, -4, 0, -2, 2, 0, 0, -4, -4, 2, 2, 0, 0, 4, 0, 0, -2, -2, -2, -2, 0, 0, -2, -2, 0,
                         2, 0, 2, 0, 0, 0, -2, 4, 0, 2, 0, 4, -2, 0, 2, 2, 0, 4, -2, 0, 4, -2, -2, -4, 0, -2, 0, 2, 0,
                         0, 0, 0, 0, 0, -2, 0, 2, 0, 0, 0, 0, 4, -4, 0, 0, 2, 2, -2, -2, 2, 2, 0, 0, -2, -4, 0, -2, 0,
                         0, -2, 2, 2, 0, -2, 0, 0, -2, 2, 0, -2, 4, 2, 0, 0, 0, 2, 2, 2, 0, 0, 0, -2, 4, 4, 0, 0, 0, -4,
                         0, -2, -2, 2, -2, -2, -4, -2, 2, -2, -2, 2, -2, 2, 2, 0, 0, -2, 0, 0, -2, -4, 2, -2, -2, -2,
                         -4, 4, -2, -2, -2, 0, -2, 0, -4, 2, 0, 4, -2, -2, 2, -2, 0, 2, 0, 0, -2, 2, -2, -2, 0, 0, -2,
                         0, 0, 2, 2, 2, -2, 0, -4, -2, -2, 4, 0, 0, 0, -2, 0, 0, 0, 4, 0, 2, -2, 2, 0, 0, 0, 4, -2, 2,
                         2, 2, 0, 0, -2, 0, 2, 0, 2, -2, 0, 0, 0, 0, 2, 0, -4, 2, -2, 4, 2, -2, -2, -2, -4, 0, 0, -2,
                         -2, 4, -2, 0, 0, 4, -2, 2, 2, -4, 0, -2, 0, 0, 2, 2, -4, -2, 0, 0, 2, -2, 0, -2, 0, 0, 2, 2,
                         -2, -2, 2, 0, 0, 0, -2, 0, 0, 0, -2, -2, 0, 4, 2, 2, 0, -2, 2, 0, -2, -2, -4, 2, 2, 2, 0, 0, 0,
                         -2, 4, 2, 2, -2, 0, 0, -2, -2, -4, -2, 2, 0, 2, -4, 0, 0, 0, 2, -4, 4, 0, 0, 0,};

// Constructors
Satellite::Satellite() : regPos_1(0), regPos_2(0),
                         shift_register_1{1}, shift_register_2{1},
                         chip_sequence{0}, satellite_id(-1) {}

Satellite::Satellite(short id, unsigned short reg1, unsigned short reg2) : regPos_1(reg1), regPos_2(reg2),
                                                                           shift_register_1{1},
                                                                           shift_register_2{1},
                                                                           chip_sequence{0}, satellite_id(id) {
    initializeChipSequence();
}


// print register positions for gold-code generator
void Satellite::printRegistersPositions() const {
    std::cout << "["
              << std::setw(2) << std::setfill(' ') << regPos_1 + 1
              << ", "
              << std::setw(2) << std::setfill(' ') << regPos_2 + 1
              << "]";
}

// print shift registers for gold-code generator
void Satellite::printShiftRegisters() const {
    std::cout << "Shift Register 1: [";
    for (auto &i: this->shift_register_1) {
        std::cout << i;
    }
    std::cout << "]\t";

    std::cout << "Shift Register 2: [";
    for (auto &i: this->shift_register_2) {
        std::cout << i;
    }
    std::cout << "]";

}

// print chip sequence
void Satellite::printChipSequence() const {
    short tmp = 0;
    std::cout << "Chip Sequence: ";
    for (auto &i: chip_sequence) {
        tmp = i;
        if (tmp < 0) {
            tmp = 0;
        }
        std::cout << tmp;
    }
}

// advance shift register 1 by one step
unsigned short Satellite::advanceShiftRegister_1() {
    // XOR the 3rd and 10th bit
    unsigned short new_bit_sr1 = shift_register_1[2] ^ shift_register_1[9];
    // Shift all bits to the right
    for (unsigned long i = register_length - 1; i > 0; i--) {
        shift_register_1[i] = shift_register_1[i - 1];
    }
    // Set the first bit to the new bit
    shift_register_1[0] = new_bit_sr1;
    return new_bit_sr1;
}

// advance shift register 2 by one step
unsigned short Satellite::advanceShiftRegister_2() {
    // XOR the bits   2, 3, 6, 8, 9 and 10
    // array position 1, 2, 5, 7, 8 and 9
    unsigned short new_bit_sr2 = shift_register_2[1] ^ shift_register_2[2] ^ shift_register_2[5] ^ shift_register_2[7] ^
                                 shift_register_2[8] ^ shift_register_2[9];
    // Shift all bits to the right
    for (unsigned long i = register_length - 1; i > 0; i--) {
        shift_register_2[i] = shift_register_2[i - 1];
    }
    // Set the first bit to the new bit
    shift_register_2[0] = new_bit_sr2;
    return new_bit_sr2;
}

// get next chip sequence value (gold-code generator)
short Satellite::getNextChipSequenceValue() {
    //fetch last value from shift register 1
    unsigned short last_bit_sr1 = shift_register_1[9];
    //fetch regPos_1 value from shift register 2
    unsigned short regBit_1 = shift_register_2[regPos_1];
    //fetch regPos_2 value from shift register 2
    unsigned short regBit_2 = shift_register_2[regPos_2];

    // advance shift register 1
    advanceShiftRegister_1();
    // advance shift register 2
    advanceShiftRegister_2();

    // XOR the bits and return value
    return (regBit_1 ^ regBit_2) ^ last_bit_sr1;
}

// initialize chip sequence (gold-code generator)
void Satellite::initializeChipSequence() {
    unsigned short tmp = 0;
    for (unsigned short &i: chip_sequence) {
        tmp = getNextChipSequenceValue();
        if (tmp == 0) {
            i = -1;
        } else {
            i = tmp;
        }
    }
}

// cross-correlate satellite with received data
void Satellite::crossCorrelate(const int receivedData[RECEIVED_DATA_LENGTH]) {
    PROFILE_START("Satellite::crossCorrelate");
    int maxCorrelation = 0; // initial value for the maximum correlation
    int bestShift = 0;

    // iterate over the received data
    for (int shift = 0; shift < RECEIVED_DATA_LENGTH; ++shift) {
        int sum = 0; // sum for the current shift
        // iterate over the chip sequence
        for (int i = 0; i < register_length; ++i) {
            // use modulo to wrap around the received data
            int receivedIndex = shift + i;
            sum += receivedData[receivedIndex] * this->chip_sequence[i];
        }
        // check if the current shift has a higher correlation than the previous maximum
        if (abs(sum) > abs(maxCorrelation)) {
            maxCorrelation = sum;
            bestShift = shift;
        }
    }
    this->lastCorrelationResult = {bestShift, maxCorrelation};
    PROFILE_STOP("Satellite::crossCorrelate");
}

// get last correlation result
CorrelationResult Satellite::getLastCorrelationResult() {
    return lastCorrelationResult;
}

// get satellite id number
short Satellite::getSatelliteId() const {
    return this->satellite_id;
}

int Satellite::getRegisterLength() {
    return register_length;
}

int Satellite::getChipSequenceLength() {
    return chip_sequence_length;
}

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
    PROFILE_START("SatelliteNetwork::initializeSatellites");
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
    PROFILE_STOP("SatelliteNetwork::initializeSatellites");
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
    PROFILE_START("SatelliteNetwork::getSatellitesWithHighestCorrelation");
    static Satellite satellitesWithHighestCorrelation[satellites_to_search];  // Static to avoid returning a pointer to local stack memory.

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
    PROFILE_STOP("SatelliteNetwork::getSatellitesWithHighestCorrelation");
    return satellitesWithHighestCorrelation;
}


int main(int argc, char *argv[]) {
    // Setup Satellite Network
    SatelliteNetwork network = SatelliteNetwork();
    // parse file
    PROFILE_START("parseFile");
    int receivedData[RECEIVED_DATA_LENGTH * 2] = {0}; // Array to store receivedData
    for (int i = 0; i < RECEIVED_DATA_LENGTH; i++) {
        receivedData[i] = INIT_DATA[i];
        receivedData[i + RECEIVED_DATA_LENGTH] = i;
    }
    PROFILE_STOP("parseFile");

    PROFILE_START("cross correlate");
    // cross-correlate all satellites
    for (int i = 0; i < network.getNumSatellites(); i++) {
        network.getSatellite(i)->crossCorrelate(receivedData);
    }
    PROFILE_STOP("cross correlate");


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
        std::cout << std::endl;
    }
    return 0;
}

