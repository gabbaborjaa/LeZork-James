#include "item.hpp"
#include <iostream>

int main() {
    try {
        Item basketball("Basketball", "Lebron's favorite ball", 40, 2.f);
        Item proteinShake("Protein Shake", "A delicious chocolate bar", 250, 0.2f);
        Item championshipRing("Championship Ring", "A shimmering ring symbolizing one of LeBron's NBA titles. It glows with a legendary aura.", 0, 0.1);
        Item sneakers("Nike LeBron Sneakers", "A pair of iconic Nike LeBron 20s. Wearing them might help you move faster on and off the court.", 0, 0.5f);

        std::cout << basketball << std::endl;
        std::cout << championshipRing << std::endl;
        std::cout << sneakers << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}