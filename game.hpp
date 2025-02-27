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

    private:
        std::map<std::string, void(Game::*)(std::vector<std::string>)> commands;
        std::vector<Item> items;
        int weight;
        std::vector<Location> locations;
        Location curr_location;
        int calories_needed;
        bool game_in_progress;

    public:
        Game() {
            // I don't think we initialize items or locations here.
            // I think we initialize them in create_world
            //this->commands = setup_commands();
            create_world();
            this->weight = 0;
            this->calories_needed = 500;
            this->game_in_progress = true;
            this->curr_location = random_location();
        }

    

    void create_world() {
        // Create all locations, items, and npcs
        // Add all items and npcs to the rooms in which they belong.
        // Add each location to the neighbors which it needs to connect.

        std::vector<std::string> lebronMessages = {
            "I am the King!",
            "Always nice to meet a fan!",
            "Have you seen Bronny?",
            "I'm NEVER retiring!"
        };

        // AI generated items and NPC's
        Item basketball("Basketball", "Lebron's favorite ball", 40, 2.f);
        Item proteinShake("Protein Shake", "A delicious chocolate bar", 250, 0.2f);
        Item championshipRing("Championship Ring", "A shimmering ring symbolizing one of LeBron's NBA titles. It glows with a legendary aura.", 0, 0.1);
        Item sneakers("Nike LeBron Sneakers", "A pair of iconic Nike LeBron 20s. Wearing them might help you move faster on and off the court.", 0, 0.5f);


        NPC lebron("LeBron James", "A legendary basketball player", lebronMessages);
        Location court("Basketball Court", "Generic Description");
        Location lockers("Locker Room", "Generic Description2");

        court.add_npc(lebron);
        court.add_item(basketball);
        //court.add_location("North", lockers);


        locations.push_back(court);
        locations.push_back(lockers);
        locations[0].add_location("North", locations[1]);
        locations[1].add_location("North", locations[0]);
    }
/*
    std::map<std::string, void(Game::*)(std::vector<std::string>)> setup_commands() {
        std::map<std::string, void(Game::*)(std::vector<std::string>)> commands;
        commands["quit"] = &Game::quit;
        commands["q"] = &Game::quit;
        commands["help"] = &Game::show_help;
        commands["talk to"] = &Game::meet;
        commands["speak to"] = &Game::meet;
        commands["interact with"] = &Game::meet;
        return commands;
    }*/

    Location random_location(){
        this->locations[0].set_visited();
        return this->locations[0];

    }

    void play() {
        while (game_in_progress) {
            std::cout << "Enter a command: ";
            std::string command;
            std::cin >> command;

        }
    }

    void show_help(std::vector<std::string> target) {
        std::cout << "Available Commands:" << std::endl;
    }

    // Speaks to NPC
    void meet(std::vector<std::string> target);

    void take(std::vector<std::string> target);

    void give(std::vector<std::string> target);

    void go(std::vector<std::string> target){
       // std::map<std::string, std::reference_wrapper<Location>> neighbors = curr_location.get_locations();
        //this->curr_location = neighbors[target[0]].get();
        //this->curr_location.set_visited();
    }

    void show_items(std::vector<std::string> target);

    void look(std::vector<std::string> target){
        std::cout << this->curr_location << std::endl;
        
        std::vector<Item> items = this->curr_location.get_items();
        std::vector<NPC> NPCs = this->curr_location.get_NPCs();
        for(auto it = items.begin(); it != items.end(); ++it){
            std::cout << *it << std::endl;
        }
        for(auto it = NPCs.begin(); it != NPCs.end(); ++it){
            std::cout << *it << std::endl;
        }
    }

    void quit(std::vector<std::string> target) {
        std::cout << "Game Quit" << std::endl;
        this->game_in_progress = false;
    }

    // Add two additional commands here

};

#endif //GAME_HPP
