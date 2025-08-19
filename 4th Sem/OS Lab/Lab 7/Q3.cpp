#include <iostream>
#include <thread>
#include <semaphore>
#include <chrono>
#include <random>

#define NUM_PHILOSOPHERS 5

class DiningPhilosophers {
private:
    std::binary_semaphore* forks[NUM_PHILOSOPHERS];  // Array of semaphore pointers

public:
    DiningPhilosophers() {
        // Initialize each binary semaphore with value 1
        for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
            forks[i] = new std::binary_semaphore(1);
        }
    }

    ~DiningPhilosophers() {
        // Clean up dynamically allocated semaphores
        for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
            delete forks[i];
        }
    }

    void wantToEat(int philosopherId) {
        int leftFork = philosopherId;
        int rightFork = (philosopherId + 1) % NUM_PHILOSOPHERS;

        // Acquire forks in consistent order to avoid deadlock
        if (philosopherId % 2 == 0) {
            forks[leftFork]->acquire();
            forks[rightFork]->acquire();
        } else {
            forks[rightFork]->acquire();
            forks[leftFork]->acquire();
        }

        std::cout << "Philosopher " << philosopherId << " is eating.\n";
        std::this_thread::sleep_for(std::chrono::seconds(rand() % 3 + 1));
    }

    void doneEating(int philosopherId) {
        int leftFork = philosopherId;
        int rightFork = (philosopherId + 1) % NUM_PHILOSOPHERS;

        forks[leftFork]->release();
        forks[rightFork]->release();

        std::cout << "Philosopher " << philosopherId << " finished eating and put down forks.\n";
    }
};

// Function for philosopher thread simulation
void philosopherTask(DiningPhilosophers& dp, int philosopherId) {
    while (true) {
        std::cout << "Philosopher " << philosopherId << " is thinking.\n";
        std::this_thread::sleep_for(std::chrono::seconds(rand() % 3 + 1));

        dp.wantToEat(philosopherId);
        dp.doneEating(philosopherId);
    }
}

int main() {
    DiningPhilosophers dp;

    // Create philosopher threads
    std::thread philosophers[NUM_PHILOSOPHERS];
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosophers[i] = std::thread(philosopherTask, std::ref(dp), i);
    }

    // Wait for all threads to complete (infinite loop simulation)
    for (auto& philosopher : philosophers) {
        philosopher.join();
    }

    return 0;
}
