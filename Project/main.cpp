#include <thread>
#include <mutex>
#include <atomic>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Animal {
    private:
        string name, fact, k, p, c, o, f, g, s;
    public:
        Animal(string name, string fact, string k, string p, string c, string o, string f, string g, string s) {
            name = name;
            fact = fact;
            k = k;
            p = p;
            c = c;
            o = o;
            f = f;
            g = g;
            s = s;
        }

        string get_name() {
            return name;
        }
        string get_fact() {
            return fact;
        }
        string get_kingdom() {
            return k;
        }
        string get_phylum() {
            return p;
        }
        string get_class() {
            return c;
        }
        string get_order() {
            return o;
        }
        string get_family() {
            return f;
        }
        string get_genus() {
            return g;
        }
        string get_species() {
            return s;
        }

        void print_animal() {
            cout << name << "\n";
            cout << fact << "\n";
            cout << "Kingdom: " << k << "\n";
            cout << "Phylum: " << p << "\n";
            cout << "Class: " << c << "\n";
            cout << "Order: " << o << "\n";
            cout << "Family: " << f << "\n";
            cout << "Genus: " << g << "\n";
            cout << "Species: " << s << "\n";
        }
};

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