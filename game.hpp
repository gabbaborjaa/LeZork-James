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
            // I don't think we initialize items or locations here.
            // I think we initialize them in create_world
            this->commands = setup_commands();
            create_world();
            this->weight = 0;
            this->calories_needed = 500;
            this->game_in_progress = true;
            this->curr_location = random_location();
        }

    private:
        std::map<std::string, void(*)(std::vector<std::string>)> commands;
        std::vector<Item> items;
        int weight;
        std::vector<Location> locations;
        Location curr_location;
        int calories_needed;
        bool game_in_progress;



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
