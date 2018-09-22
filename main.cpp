#include <iostream>
#include <random>
#include <iomanip>
#include <fstream>
#include <array>
#include <algorithm>

using std:: cout;
using std:: endl;

/**
 * A pair containing an integer and a decimal.
 */
struct pair {
    int integer;
    double decimal;
};

/**
 * Creates a list of randomly generated pairs of integer and double of size 512 to 1024, the integers are in ascending order,
 * the doubles are randomly chosen from 50 to 90.
 *
 * return: vector<pair>: returns the list of pairs as a vector.
 */
std::vector<pair> createList() {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> lengthDistribution(512, 1024);
    std::uniform_real_distribution<> doubDistribution(50, 90);
    int length = lengthDistribution(generator);

    std::vector<pair> v;

    for (int i = 0; i <= length; i++) {
        double randomDouble = doubDistribution(generator);
        pair temp = {i, randomDouble};
        v.push_back(temp);
    }

    return v;
}

/**
 * Takes a vector of pairs and enter the value in a file.
 * @param list A vector of pairs of integer and double.
 */
void createFile(std::vector<pair> list) {
    std::ofstream myFile;
    myFile.open("Readings.txt");
    for (int i = 0; i <= list.size() - 1; i++) {
        myFile << list[i].integer << " " << std::setprecision(3)<< std::fixed << list[i].decimal << endl;
    }
    myFile << list[list.size() - 1].integer << " " << std::setprecision(3)<< std::fixed << list[list.size() - 1].decimal;
}

/**
 * Reads a file and print out the number of lines, average, highest, lowest, and median of the doubles in the list.
 * @param name Name of the file to be read from.
 */
void readFile(std::string name) {
    std::ifstream file(name);
    std::istringstream iss;
    std::string line;
    int total = 0;
    double decimal, aveDec = 0;
    std::vector<double> declist;

    // reads file line by line
    while(getline(file, line)) {

        // clears and sets stream
        iss.clear();
        iss.str(line);
        int temp;
        iss >> temp;

        // calculates total
        total++;

        // brings in decimal from the line
        iss >> decimal;

        // adds to total for calculating average later
        aveDec += decimal;

        // adds the double to the list
        declist.push_back(decimal);
        // sorts the list
        std::sort(declist.begin(), declist.end());
    }

    // calculating average
    aveDec = aveDec / total;

    // printing output
    cout << "There are " << total - 1 << " readings in the file." << endl;
    cout << "The average reading is " << aveDec << "." << endl;
    cout << "The highest reading is " << declist.at(declist.size() - 1) << "." << endl;
    cout << "The lowest reading is " << declist.at(0) << "." << endl;
    cout << "The median reading is " << declist.at((declist.size()-1)/2) << "." << endl;
}

int main() {
    createFile(createList());
    readFile("Readings.txt");
    return 0;
}
