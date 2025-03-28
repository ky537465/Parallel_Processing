#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include "animal.hpp"
using namespace std;
int num_animals = 0;

using namespace std;

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

    // Warning in case the number of animals is not correct.
    if (animals_list.size() != num_animals) {
        cerr << "Warning: Number of animals does not match total. \n" << animals_list.size();
    }

    return animals_list;
}

// Structure to represent taxonomy tree as a binary tree.
struct TaxonomyNode {
    string name;
    map<string, TaxonomyNode*> children;
    vector<Animal> animals;

    TaxonomyNode(string name) : name(name) {}
};

// Inserts animal into tree.
void insert_into_tree(TaxonomyNode* root, const Animal& animal) {
    TaxonomyNode* current = root;

    vector<string> levels = {animal.k, animal.p, animal.c, animal.o, animal.f, animal.g, animal.s};

    for (const string& level : levels) {
        if (current->children.find(level) == current->children.end()) {
            current->children[level] = new TaxonomyNode(level);
        }
        current = current->children[level];
    }

    // Stores the animal at the species level.
    current->animals.push_back(animal);
}

// Generates DOT representation.
void write_dot(TaxonomyNode* node, ofstream& file) {
    for (auto& child : node->children) {
        file << "\"" << node->name << "\" -> \"" << child.second->name << "\";\n";
        write_dot(child.second, file);
    }

    // Adds animal to correct species level.
    for (const auto& animal : node->animals) {
        file << "\"" << node->name << "\" -> \"" << animal.name << " (" << animal.fact << ")\" [color=blue];\n";
    }
}

// Generates the DOT file
void generate_dot_file(TaxonomyNode* root, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not create DOT file.\n";
        return;
    }

    file << "digraph TaxonomyTree {\n";
    file << "node [shape=ellipse, style=filled, fillcolor=lightgray];\n";
    write_dot(root, file);
    file << "}\n";

    file.close();
    cout << "DOT file generated: " << filename << endl;
}

// Main
int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Error: No file provided.\n";
        return 1;
    }

    ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open file: " << argv[1] << endl;
        return 1;
    }

    vector<Animal> animals = read_animals(inputFile);
    inputFile.close();

    TaxonomyNode* root = new TaxonomyNode("Life");

    for (const auto& animal : animals) {
        insert_into_tree(root, animal);
    }

    // Generates the DOT file
    generate_dot_file(root, "taxonomy_tree.dot");

    // Suggests the correct command to generate the tree next:
    cout << "To generate an image, use Graphviz: dot -Tpng taxonomy_tree.dot -o taxonomy_tree.png\n";

    return 0;
}