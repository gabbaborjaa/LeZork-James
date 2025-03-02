#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <sstream>
#include <numeric>
#include <algorithm>
#include "Location.hpp"
#include "item.hpp"
#include "npc.hpp"

class Game {
    private:
        std::map<std::string, void(Game::*)(std::vector<std::string>)> commands;
        std::vector<Item> items;
        float weight;
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

        lockers.add_npc(lebron);
        court.add_npc(lebron); // remove one of these
        lockers.add_item(basketball);
        court.add_item(basketball);  // remove one of these
        court.add_location("North", lockers);

        locations.push_back(court);
        locations.push_back(lockers);
    }

    std::map<std::string, void(Game::*)(std::vector<std::string>)> setup_commands() {
        std::map<std::string, void(Game::*)(std::vector<std::string>)> commands;
        commands["quit"] = &Game::quit;
        commands["q"] = &Game::quit;
        commands["help"] = &Game::show_help;
        commands["show help"] = &Game::show_help;
        commands["items"] = &Game::show_items;
        commands["look"] = &Game::look;
        commands["meet"] = &Game::meet;
        commands["talk"] = &Game::talk;
        commands["take"] = &Game::take;
        commands["give"] = &Game::give;
        /*commands["speak to"] = &Game::meet;
        commands["interact with"] = &Game::meet;*/
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
        while (this->game_in_progress) {
            std::cout << "Enter a command: ";
            std::string command;
            std::getline(std::cin, command); // how do we get rid of blank line
            std::vector<std::string> tokens;
            std::istringstream iss(command); // Copilot
            std::string word;
            while (iss >> word) {
                tokens.push_back(word);
            }
            command = tokens[0];
            tokens.erase(tokens.begin());

            std::ostringstream oss;
            for (int i = 0; i < tokens.size(); ++i) {
                if (i > 0) oss << " "; // used ChatGPT to find out how to add spaces between words
                oss << tokens[i];
            }
            std::string target = oss.str();

            // The code inside this if statement was helped by ChatGPT
            if (commands.find(command) != commands.end()) {
                void(Game::*func)(std::vector<std::string>) = commands[command];
                (this->*func)({target});
            }
        }

    }

    void show_help(std::vector<std::string> target) {
        std::cout << "Available Commands:" << std::endl;
    }

    void talk(std::vector<std::string> target) {
            std::vector<NPC>& npcs = curr_location.get_NPCs();

            // ChatGPT helped with iter
            auto iter = std::find_if(npcs.begin(), npcs.end(), [target](NPC& npc) {
                return npc.getName() == target[0];
            });

            if (iter != npcs.end()) {
                int i = std::distance(npcs.begin(), iter);
                std::string npc_message = npcs[i].getMessage();
                std::cout << npc_message << std::endl;
            } else {
                std::cout << "NPC not found!" << std::endl;
            }
        }

    void meet(std::vector<std::string> target) {
        std::vector<NPC>& npcs = curr_location.get_NPCs();

        // ChatGPT helped with iter
        auto iter = std::find_if(npcs.begin(), npcs.end(), [target](NPC& npc) {
            return npc.getName() == target[0];
        });

        if (iter != npcs.end()) {
            int i = std::distance(npcs.begin(), iter);
            std::string npc_name = npcs[i].getName();
            std::cout << npc_name << std::endl;
            std::string npc_message = npcs[i].getDescription();
            std::cout << npc_message << std::endl;
        } else {
            std::cout << "NPC not found!" << std::endl;
        }
    }
 
    void take(std::vector<std::string> target) {
        std::vector<Item>& item_vector = curr_location.get_items();

        auto iter = std::find_if(item_vector.begin(), item_vector.end(), [target](Item& item) {
            return item.getName() == target[0];
        });

        if (iter != item_vector.end()) {
            int i = std::distance(item_vector.begin(), iter);
            std::string item_name = item_vector[i].getName();
            std::cout << item_name << std::endl;

            items.push_back(item_vector[i]);
            weight += item_vector[i].getWeight();

            std::cout << weight << std::endl;
            std::cout << items[0] << std::endl;

            curr_location.remove_item(item_vector[i]);

        } else {
            std::cout << "Item not found!" << std::endl;
        }
    }

    void give(std::vector<std::string> target) {

        auto iter = std::find_if(items.begin(), items.end(), [target](Item& item) {
            return item.getName() == target[0];
        });

        if (iter != items.end()) {
            int i = std::distance(items.begin(), iter);
            std::string item_name = items[i].getName();
            std::cout << item_name << std::endl;

            curr_location.add_item(items[i]);
            weight -= items[i].getWeight();

            items.erase(std::remove(this->items.begin(), this->items.end(), items[i]));

        } else {
            std::cout << "Item not in inventory!" << std::endl;
        }
    }


    void go(std::vector<std::string> target);

    void show_items(std::vector<std::string> target) {
        std::cout << "Your items" << std::endl;
        for (auto it = items.begin(); it != items.end(); ++it) {
            std::cout << *it << std::endl;
        }
        std::cout << "Your weight: " << weight << " lbs" << std::endl;
    }

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
