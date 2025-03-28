#include <thread>
#include <vector>
#include <algorithm>
#include <iostream>
#include <mutex>
using namespace std;

class Animal {
public:
    string name, fact, k, p, c, o, f, g, s;

    Animal(string name, string fact, string k, string p, string c, string o, string f, string g, string s)
        : name(name), fact(fact), k(k), p(p), c(c), o(o), f(f), g(g), s(s) {}

    string get_kingdom() const { return k; }
    string get_phylum() const { return p; }
    string get_class() const { return c; }
    string get_order() const { return o; }
    string get_family() const { return f; }
    string get_genus() const { return g; }
    string get_species() const { return s; }

    void print_animal() const {
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

    // Compares animals by alphabetical order.
    static bool compare_animals(const Animal& a, const Animal& b) {
        if (a.get_kingdom() != b.get_kingdom()) return a.get_kingdom() < b.get_kingdom();
        if (a.get_phylum() != b.get_phylum()) return a.get_phylum() < b.get_phylum();
        if (a.get_class() != b.get_class()) return a.get_class() < b.get_class();
        if (a.get_order() != b.get_order()) return a.get_order() < b.get_order();
        if (a.get_family() != b.get_family()) return a.get_family() < b.get_family();
        if (a.get_genus() != b.get_genus()) return a.get_genus() < b.get_genus();
        return a.get_species() < b.get_species();
    }

    static void sort_chunk(vector<Animal>& animals, size_t start, size_t end) {
        sort(animals.begin() + start, animals.begin() + end, compare_animals);
    }

    static void merge_chunks(vector<Animal>& animals, size_t start1, size_t end1, size_t start2, size_t end2) {
        inplace_merge(animals.begin() + start1, animals.begin() + end1, animals.begin() + end2, compare_animals);
    }

    // My created threading sorting function.
    static void threading_sort(vector<Animal>& animals, int num_threads) {
        if (animals.empty() || num_threads <= 0) return;

        // Divides animals evenly into the number of allocated threads.
        size_t chunk_size = animals.size() / num_threads;
        vector<thread> threads;

        // Calculates each chunk and the animals inside the chunk.
        for (size_t i = 0; i < num_threads; i++) {
            size_t start = i * chunk_size;
            size_t end = (i == num_threads - 1) ? animals.size() : start + chunk_size;
            threads.emplace_back(sort_chunk, ref(animals), start, end);
        }

        // Joins threads once complete for merging.
        for (auto& t : threads) {
            t.join();
        }

        // Merges animal chunks like in merge sort.
        for (size_t merge_size = chunk_size; merge_size < animals.size(); merge_size *= 2) {
            for (size_t start1 = 0; start1 < animals.size(); start1 += 2 * merge_size) {
                size_t end1 = min(start1 + merge_size, animals.size());
                size_t start2 = end1;
                size_t end2 = min(start2 + merge_size, animals.size());
                merge_chunks(animals, start1, end1, start2, end2);
            }
        }
    }

    // Non-Threading sort function, built-in function.
    static void sort_animals(vector<Animal>& animals) {
        sort(animals.begin(), animals.end(), compare_animals);
    }
};