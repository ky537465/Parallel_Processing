#include <thread>
#include <mutex>
#include <atomic>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Animal {
    private:
        string name, fact, k, p, c, o, f, g, s;
    public:
        Animal(string name, string fact, string k, string p, string c, string o, string f, string g, string s)
            : name(name), fact(fact), k(k), p(p), c(c), o(o), f(f), g(g), s(s) {}

        string get_name() const { return name; }
        string get_fact() const { return fact; }
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

        // Uses built-in sort function that runs in 0(n log n) time.
        static void sort_chunk(vector<Animal>& animals, size_t start, size_t end) {
            sort(animals.begin() + start, animals.begin() + end, [](const Animal& a, const Animal& b) {
                if (a.get_kingdom() != b.get_kingdom()) return a.get_kingdom() < b.get_kingdom();
                if (a.get_phylum() != b.get_phylum()) return a.get_phylum() < b.get_phylum();
                if (a.get_class() != b.get_class()) return a.get_class() < b.get_class();
                if (a.get_order() != b.get_order()) return a.get_order() < b.get_order();
                if (a.get_family() != b.get_family()) return a.get_family() < b.get_family();
                if (a.get_genus() != b.get_genus()) return a.get_genus() < b.get_genus();
                return a.get_species() < b.get_species();
            });
        }

        // Merges the two sorted chunks together.
        static void merge_chunks(vector<Animal>& animals, size_t start1, size_t end1, size_t start2, size_t end2) {
            vector<Animal> merged;
            size_t i = start1, j = start2;

            while (i < end1 && j < end2) {
                if (compare_animals(animals[i], animals[j])) {
                    merged.push_back(animals[i++]);
                } else {
                    merged.push_back(animals[j++]);
                }
            }

            while (i < end1) merged.push_back(animals[i++]);
            while (j < end2) merged.push_back(animals[j++]);

            for (size_t k = 0; k < merged.size(); ++k) {
                animals[start1 + k] = merged[k];
            }
        }

        static bool compare_animals(const Animal& a, const Animal& b) {
            if (a.get_kingdom() != b.get_kingdom()) return a.get_kingdom() < b.get_kingdom();
            if (a.get_phylum() != b.get_phylum()) return a.get_phylum() < b.get_phylum();
            if (a.get_class() != b.get_class()) return a.get_class() < b.get_class();
            if (a.get_order() != b.get_order()) return a.get_order() < b.get_order();
            if (a.get_family() != b.get_family()) return a.get_family() < b.get_family();
            if (a.get_genus() != b.get_genus()) return a.get_genus() < b.get_genus();
            return a.get_species() < b.get_species();
        }

        // Using threading to sort the animals by kingdom.
        static void kingdom_sort(vector<Animal>& animals, int num_threads) {
            size_t chunk_size = animals.size() / num_threads;
            vector<thread> threads;

            // Chunking and Sorting animals with threads.
            for (size_t i = 0; i < num_threads; i++) {
                size_t start = i + chunk_size;
                size_t end = (i == num_threads - 1) ? animals.size() : start + chunk_size;
                threads.emplace_back(sort_chunk, ref(animals), start, end);
            }

            // Joining threads once finished.
            for (auto& t : threads) {
                t.join();
            }

            // Merging the chunks and keeping sortedness.
            for (size_t i = 1; i < num_threads; i++) {
                size_t start1 = 0;
                size_t end1 = i * chunk_size;
                size_t start2 = i * chunk_size;
                size_t end2 = (i == num_threads - 1) ? animals.size() : start2 + chunk_size;
                merge_chunks(animals, start1, end1, start2, end2);
            }
        }
};
