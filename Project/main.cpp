#include <thread>
#include <mutex>
#include <atomic>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>

#include "animal.hpp"

using namespace std;

void read_animals(ifstream& inputFile) {
    string line, name, fact, k, p, c, o, f, g, s;
    vector<vector<string>> animals_list;
    int num_animals;

    if (getline(inputFile, line)) {num_animals = stoi(line);}

    for (int i = 0; i < num_animals; i++) {
        if (getline(inputFile, line)) {name = line;}
        if (getline(inputFile, line)) {fact = line;}
        if (getline(inputFile, line)) {k = line;}
        if (getline(inputFile, line)) {p = line;}
        if (getline(inputFile, line)) {c = line;}
        if (getline(inputFile, line)) {o = line;}
        if (getline(inputFile, line)) {f = line;}
        if (getline(inputFile, line)) {g = line;}
        if (getline(inputFile, line)) {s = line;}
        Animal animal(name, fact, k, p, c, o, f, g, s);
        animal.print_animal();
    }
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

// +=====================================================+
//                      For File Input.
// +=====================================================+

/*
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
}*/

// +=====================================================+
//                     For NO File Input.
// +=====================================================+

int main() {
    vector<Animal> animals = {
        {"Lion", "King of the Jungle", "Animalia", "Chordata", "Mammalia", "Carnivora", "Felidae", "Panthera", "P. leo"},
        {"Shark", "Has multiple rows of teeth", "Animalia", "Chordata", "Chondrichthyes", "Selachimorpha", "Carcharhinidae", "Carcharhinus", "C. carcharias"},
        {"Eagle", "Has powerful vision", "Animalia", "Chordata", "Aves", "Accipitriformes", "Accipitridae", "Aquila", "A. chrysaetos"},
        {"Frog", "Can jump long distances", "Random", "Chordata", "Amphibia", "Anura", "Ranidae", "Rana", "R. temporaria"},
        {"Octopus", "Has eight arms", "Animalia", "Chordata", "Cephalopoda", "Octopoda", "Octopodidae", "Octopus", "O. vulgaris"}
    };

    int num_threads = 2;
    Animal::kingdom_sort(animals, num_threads);

    //cout << "Sorted Animals by Kingdom:\n";
    //for (const auto& animal : animals) {
    //    animal.print_animal();
    //    cout << "----------------------\n";
    //}

    TaxonomyNode* root = new TaxonomyNode("Root");      // TODO: change root to animal name.
    for (const auto& animal : animals) {
        cout << animal.name << " Fact: " << animal.fact << endl;
        insert_into_tree(root, animal);
    }

    cout << "\nTaxonomy Tree:\n";
    print_tree(root);
    return 0;
}