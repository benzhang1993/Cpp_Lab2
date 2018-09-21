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
    for (int i = 0; i <= list.size(); i++) {
        myFile << list[i].integer << " " << std::setprecision(3)<< std::fixed << list[i].decimal << endl;
    }
}

int main() {
    createFile(createList());
    return 0;
}
