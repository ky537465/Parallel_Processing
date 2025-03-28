#include <thread>
#include <mutex>
#include <atomic>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

#include "animal.hpp"
using namespace std;
int num_animals = 0;

// Reads the animals from the file.
vector<Animal> read_animals(ifstream& inputFile) {
    string line, name, fact, k, p, c, o, f, g, s;
    string num;
    vector<Animal> animals_list;

    if (!getline(inputFile, num)) {
        cerr << "Error: Input file is empty or invalid.\n";
        return animals_list;
    }

    try {
        num_animals = stoi(num);
    } catch (const invalid_argument& e) {
        cerr << "Error: Invalid number of animals.\n";
        return animals_list;
    }


    for (int i = 0; i < num_animals; i++) {
        if (!getline(inputFile, name)) break;
        if (!getline(inputFile, fact)) break;
        if (!getline(inputFile, k)) break;
        if (!getline(inputFile, p)) break;
        if (!getline(inputFile, c)) break;
        if (!getline(inputFile, o)) break;
        if (!getline(inputFile, f)) break;
        if (!getline(inputFile, g)) break;
        if (!getline(inputFile, s)) break;

        Animal animal(name, fact, k, p, c, o, f, g, s);
        animals_list.push_back(animal);
    }

    if (animals_list.size() != num_animals) {
        cerr << "Warning: Number of animals does not match total. \n" << animals_list.size();
    }

    return animals_list;
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

    // Variables and functions
    vector<Animal> animals = read_animals(inputFile);
    vector<Animal> animalsCopy;     // this is for the 2nd sorting function.
    animalsCopy = animals;

    // Time threading
    auto start_thread = chrono::high_resolution_clock::now();
    Animal::threading_sort(animals, thread::hardware_concurrency());
    auto end_thread = chrono::high_resolution_clock::now();
    chrono::duration<double> thread_total = end_thread - start_thread;

    // Time non-threading
    auto start_non_thread = chrono::high_resolution_clock::now();
    Animal::sort_animals(animalsCopy);
    auto end_non_thread = chrono::high_resolution_clock::now();
    chrono::duration<double> non_thread_total = end_non_thread - start_non_thread;

    cout << "Total time for threading: " << thread_total.count() << " seconds\n";
    cout << "Total time for non-threading: " << non_thread_total.count() << " seconds\n";
}