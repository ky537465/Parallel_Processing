#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

// Chapter 1 Example: Dining Philosophers.
using namespace std;

mutex chopsticks[5];
int n = 6;

void philosopher(int id) {
    int left = id;
    int right = ((id + 1) % n);

    cout << "Right: " << right << " Left: " << left << "\n";

    for (int i = 0; i < 3; i++) {
        cout << "Philosopher " << id << " is thinking...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        // Lock the chopsticks
        lock_guard<mutex> left_lock(chopsticks[left]);
        lock_guard<mutex> right_lock(chopsticks[right]);
        cout << "Philosopher " << id << " is eating...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        cout << "Philosopher " << id << " has finished eating...\n";
    }
}

int main() {
    vector<thread> philosophers;
    
    for (int i = 0; i < n; i++) {
        philosophers.emplace_back(philosopher, i);
    }

    for (auto& p : philosophers) {
        p.join();
    }
    return 0;
}