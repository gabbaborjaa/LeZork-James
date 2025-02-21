#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "Location.hpp"
#include "item.hpp"
#include "npc.hpp"

class Game {
    public:
        Game() {
            // set commands map equal to the return call from setup_commands function
            // call create_world() method
            // set default values for all other variables
            // set current location to random location from random_location() method
        }

    void create_world();

    std::map<std::string, void(*)(std::vector<std::string>)> setup_commands();

    Location random_location();

    void play();

    void show_help();

    void talk(std::vector<std::string> target);

    void meet(std::vector<std::string> target);

    void take(std::vector<std::string> target);

    void give(std::vector<std::string> target);

    void go(std::vector<std::string> target);

    void show_items(std::vector<std::string> target);

    void look(std::vector<std::string> target);

    void quit(std::vector<std::string> target);

    // Add two additional commands here

};

#endif //GAME_HPP
