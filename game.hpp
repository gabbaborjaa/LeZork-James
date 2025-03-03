#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <random>
#include "Location.hpp"
#include "item.hpp"
#include "npc.hpp"

class Game {
    private:
        std::map<std::string, void(Game::*)(std::vector<std::string>) > commands;
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
            this->commands = setup_commands();
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
        court.add_location("North", lockers);


        locations.push_back(court);
        locations.push_back(lockers);
    }

    std::map<std::string, void(Game::*)(std::vector<std::string>)> setup_commands() {
        std::map<std::string, void(Game::*)(std::vector<std::string>)> commands;
        commands["quit"] = &Game::quit;
        commands["q"] = &Game::quit;
        commands["help"] = &Game::show_help;
        commands["talk to"] = &Game::meet;
        commands["speak to"] = &Game::meet;
        commands["interact with"] = &Game::meet;
        commands["show items"] = &Game::show_help;
        return commands;
    }

    Location random_location(){
        if (locations.empty()) {
            throw std::runtime_error("No locations available");
        }
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, locations.size() - 1);
        return locations[dis(gen)];
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
        std::cout << "quit, q - Quit the game" << std::endl;
        std::cout << "help - Show this help message" << std::endl;
        std::cout << "talk to, speak to, interact with - Interact with an NPC" << std::endl;
        std::cout << "give [item] -- Removes item from inventory and places it in Location's inventory" << std::endl;
        std::cout << "take" << std::endl;
        std::cout << "go" << std::endl;
        std::cout << "show_items" << std::endl;
        std::cout << "look" << std::endl;

    }

    // Speaks to NPC
    void meet(std::vector<std::string> target);

    void take(std::vector<std::string> target){
        if (target.empty()) {
            std::cout << "What item do you want to take>" << std::endl;
            return;
        }

        std::string itemName = target[0];
        bool itemFound = false;

        for (auto it = curr_location.get_items().begin(); it != curr_location.get_items().end(); ++it){
            if(it->itemName == itemName) {
                items.push_back(*it);
                weight += it->getWeight();
                curr_location.get_items().erase(it);
                itemFound = true;
                std::cout << "You picked up " << itemName << "." << std::endl;
                break;
            }
        }

        if (!itemFound) {
            std::cout << "Item is not here." << std::endl;
        }
    }

    void give(std::vector<std::string> target);

    void go(std::vector<std::string> target){
        if (target.empty()) {
            std::cout << "You can't go there" << std::endl;
            return;
        }

        std::string direction = target[0];
        curr_location.set_visited();

        if (weight > 30){
            std::cout << "You are carrying too much stuff that you can't move." << std::endl;
            return;
        }

        // if (curr_location.has_neighbor(direction)) {
        //     curr_location = curr_location.get_neighbor(direction);
        //     std::cout << "You moved to: " << curr_location.getName() << std::endl;
        // }
    }
    void show_items(std::vector<std::string> target){      
        std::cout << "Your items" << std::endl;
        for (auto it = items.begin(); it != items.end(); ++it) {
            std::cout << *it << std::endl;
        }
        std::cout << "Your weight: " << weight << " lbs" << std::endl;
    }
       
    void look(std::vector<std::string> target);

    void quit(std::vector<std::string> target) {
        std::cout << "Game Quit" << std::endl;
        this->game_in_progress = false;
    }

    // Add two additional commands here

};

#endif //GAME_HPP
