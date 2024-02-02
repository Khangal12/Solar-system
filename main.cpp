#include "Universe.h"
#include <unistd.h>
#include <thread> // Add this include for the sleep_for function
#include <chrono> // Add this include for chrono::seconds
int main() {
    // Read data file "nbody.txt"
    Universe universe("nbody.txt");

    // Repeat forever
    while (true) {
        // Display bodies
        universe.displayBodies();

        // Update position of bodies
        universe.updateBodies(0.01); 
;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

    }

    return 0;
}
