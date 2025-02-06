#include <thread>
#include <mutex>
#include <atomic>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "animal.hpp"

using namespace std;

void read_animals(ifstream& inputFile) {
    string line, name, fact, k, p, c, o, f, g, s;
    vector<vector<string>> animals_list;
    int num_animals;

    if (getline(inputFile, line)) {
        num_animals = stoi(line);
    }

    for (int i = 0; i < num_animals; i++) {
        if (getline(inputFile, line)) {
            name = line;
        }
        if (getline(inputFile, line)) {
            fact = line;
        }
        if (getline(inputFile, line)) {
            k = line;
        }
        if (getline(inputFile, line)) {
            p = line;
        }
        if (getline(inputFile, line)) {
            c = line;
        }
        if (getline(inputFile, line)) {
            o = line;
        }
        if (getline(inputFile, line)) {
            f = line;
        }
        if (getline(inputFile, line)) {
            g = line;
        }
        if (getline(inputFile, line)) {
            s = line;
        }
        Animal animal(name, fact, k, p, c, o, f, g, s);
        animal.print_animal();
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Error: No file provided.";
        return 0;
    }

    ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open file." << argv[1];
        return 0;
    }

    read_animals(inputFile);
}