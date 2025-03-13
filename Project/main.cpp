#include <thread>
#include <mutex>
#include <atomic>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
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
        num_animals = stoi(num); // Convert the string to an integer
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
        cerr << "Warning: Number of animals does not match total.\n";
    }

    return animals_list;
}

struct TaxonomyNode {
    string name;
    map<string, TaxonomyNode*> children;

    TaxonomyNode(string name) : name(name) {}
};

void insert_into_tree(TaxonomyNode* root, const Animal& animal) {
    TaxonomyNode* current = root;

    // Inserting Kingdom
    if (current->children.find(animal.k) == current->children.end()) {
        current->children[animal.k] = new TaxonomyNode(animal.k);
    }
    current = current->children[animal.k];

    // Inserting Phylum
    if (current->children.find(animal.p) == current->children.end()) {
        current->children[animal.p] = new TaxonomyNode(animal.p);
    }
    current = current->children[animal.p];

    // Inserting Class
    if (current->children.find(animal.c) == current->children.end()) {
        current->children[animal.c] = new TaxonomyNode(animal.c);
    }
    current = current->children[animal.c];

    // Inserting Order
    if (current->children.find(animal.o) == current->children.end()) {
        current->children[animal.o] = new TaxonomyNode(animal.o);
    }
    current = current->children[animal.o];

    // Inserting Family
    if (current->children.find(animal.f) == current->children.end()) {
        current->children[animal.f] = new TaxonomyNode(animal.f);
    }
    current = current->children[animal.f];

    // Inserting Genus
    if (current->children.find(animal.g) == current->children.end()) {
        current->children[animal.g] = new TaxonomyNode(animal.g);
    }
    current = current->children[animal.g];

    // Inserting Species
    if (current->children.find(animal.s) == current->children.end()) {
        current->children[animal.s] = new TaxonomyNode(animal.s);
    }
}

void print_tree(TaxonomyNode* root, int dept = 0) {
    cout << "|--";
    // TODO: print out animal name and fact.
    for (int i = 0; i < dept; ++i) {
        cout << "  ";
    }
    cout << root->name << endl;

    for (auto& child : root->children) {
        print_tree(child.second, dept + 1);
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

    // Variables and functions
    vector<Animal> animals = read_animals(inputFile);
    vector<Animal> animalsCopy;     // this is for the 2nd sorting function.
    animalsCopy = animals;

    // Time threading
    auto start_thread = chrono::high_resolution_clock::now();
    Animal::threading_sort(animals, num_animals);
    auto end_thread = chrono::high_resolution_clock::now();
    chrono::duration<double> thread_total = end_thread - start_thread;

    // Time non-threading
    auto start_non_thread = chrono::high_resolution_clock::now();
    Animal::sort_animals(animalsCopy);
    auto end_non_thread = chrono::high_resolution_clock::now();
    chrono::duration<double> non_thread_total = end_non_thread - start_non_thread;

    for (const auto& animal : animalsCopy) {
        animal.print_animal();
    }

    cout << "Total time for threading: " << thread_total.count() << " seconds\n";
    cout << "Total time for non-threading: " << non_thread_total.count() << " seconds\n";
}