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

        // Need function to sort chunks.

        // Need function to merge two sorted chunks.

        // Using threading to sort the animals by kingdom.
        static void kingdom_sort(vector<Animal>& animals, int num_threads) {
            size_t chunk_size = animals.size() / num_threads;
            vector<thread> threads;

            // Chunking and Sorting animals with threads.
            for (size_t i = 0; i < num_threads; i++) {
                size_t start = i + chunk_size;
                size_t end = (i == num_threads - 1) ? animals.size() : start + chunk_size;
                //threads.emplace_back(sort_chunk, ref(animals), start, end);
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
                //merge_chunks(animals, start1, end1, start2, end2);
            }
        }
};
