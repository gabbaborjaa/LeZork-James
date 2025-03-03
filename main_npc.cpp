#include "item.hpp"
#include "npc.hpp"
#include "game.hpp"
#include <vector>
#include <iostream>

int main(int argc, char** argv) {
    Item basketball("Basketball", "Lebron's favorite ball", 40, 2.f);
    Item proteinShake("Protein Shake", "A delicious chocolate bar", 250, 0.2f);
    Item championshipRing("Championship Ring", "A shimmering ring symbolizing one of LeBron's NBA titles. It glows with a legendary aura.", 0, 0.1);
    Item sneakers("Nike LeBron Sneakers", "A pair of iconic Nike LeBron 20s. Wearing them might help you move faster on and off the court.", 0, 0.5f);

    std::vector<std::string> lebronMessages = {
        "I am the King!",
        "I got that ring.",
        "Where is Bronny?",
        "I will be taking talents to south beach."
    };

    // std::vector<std::string> lebronMessages(std::initializer_list<std::string>{
    //     "I am the King!",
    //     "Strive for greatness.",
    //     "Witness greatness.",
    //     "I am just a kid from Akron."
    // });

    NPC lebron("LeBron James", "A legendary basketball player", lebronMessages);

    std::cout << basketball << std::endl;
    std::cout << proteinShake << std::endl;
    std::cout << championshipRing << std::endl;
    std::cout << sneakers << std::endl;

    std::cout << lebron << std::endl;
    std::cout << lebron.getMessage() << std::endl;
    std::cout << lebron.getMessage() << std::endl;
    std::cout << lebron.getMessage() << std::endl;
    std::cout << lebron.getMessage() << std::endl;
    std::cout << lebron.getMessage() << std::endl; // This should loop back to the first message

    std::cout << lebron.getMessage() << std::endl;

    Game game;
    game.play();

    return 0;
}