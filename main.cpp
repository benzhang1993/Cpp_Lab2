#include <iostream>
#include <random>
#include <iomanip>
#include <fstream>
#include <array>

using std:: cout;
using std:: endl;

struct pair {
    int integer;
    double decimal;
};

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
        cout << v.at(i).integer << " " << std::setprecision(3)<< std::fixed << v.at(i).decimal << endl;
    }

    return v;
}

void createFile(std::vector<pair> list) {
    std::ofstream myFile;
    myFile.open("Readings.txt");
    for (int i = 0; i <= list.size() - 1; i++) {
        myFile << list[i].integer << " " << std::setprecision(3)<< std::fixed << list[i].decimal << endl;
    }
    myFile << list[list.size() - 1].integer << " " << std::setprecision(3)<< std::fixed << list[list.size() - 1].decimal;
}

void readFile(std::string name) {
    std::ifstream file(name);
    std::istringstream iss;
    std::string line;
    int total = 0;
    int integer, aveInt = 0, highInt = 0, lowInt = 1025, medianInt;
    double decimal, aveDec = 0, highDec = 0, lowDec = 91.000, medDec;

    while(getline(file, line)) {

        // clears and sets stream
        iss.clear();
        iss.str(line);

        // calculates total
        total++;

        // brings in integer and sets initial values
        iss >> integer;

        // adds to total for calculating average later.
        aveInt += integer;

        // sets highest integer
        if(integer > highInt) {
            highInt = integer;
        }

        // set lowest integer
        if (integer < lowInt) {
            lowInt = integer;
        }

        // brings in double and sets initial values
        iss >> decimal;

        // adds to total for calculating average later.
        aveDec += decimal;

        // sets highest integer
        if(decimal > highDec) {
            highDec = decimal;
        }

        // set lowest integer
        if (decimal < lowDec) {
            lowDec = decimal;
        }
    }

    aveInt = aveInt / total;
    aveDec = aveDec / total;

    cout << "There are " << total - 1 << " readings in the file." << endl;
    cout << "The average reading is " << aveInt << ", " << aveDec << "." << endl;
    cout << "The highest reading is " << highInt << ", " << highDec << "." << endl;
    cout << "The lowest reading is " << lowInt << ", " << lowDec << "." << endl;
}

int main() {
    createFile(createList());
    readFile("Readings.txt");
    return 0;
}
