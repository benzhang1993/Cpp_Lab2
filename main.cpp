#include <iostream>
#include <random>
#include <iomanip>
#include <fstream>
#include <array>
#include <algorithm>

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
    int integer, aveInt = 0;
    double decimal, aveDec = 0;
    std::vector<int> intlist;
    std::vector<double> declist;

    while(getline(file, line)) {

        // clears and sets stream
        iss.clear();
        iss.str(line);

        // calculates total
        total++;

        // brings in integer and decimal from the line
        iss >> integer;
        iss >> decimal;

        // adds to total for calculating average later
        aveInt += integer;
        aveDec += decimal;

        intlist.push_back(integer);
        declist.push_back(decimal);
        std::sort(intlist.begin(), intlist.end());
        std::sort(declist.begin(), declist.end());
    }

    aveInt = aveInt / total;
    aveDec = aveDec / total;

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
