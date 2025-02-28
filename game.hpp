#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <sstream>
#include <numeric>
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
        commands["show help"] = &Game::show_help;
        commands["items"] = &Game::show_items;
        commands["look"] = &Game::look;
        commands["meet"] = &Game::meet;

        /*commands["talk to"] = &Game::meet;
        commands["speak to"] = &Game::meet;
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
            //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, command); // how do we get rid of blank line
            std::vector<std::string> tokens;
            std::istringstream iss(command); // Copilot
            std::string word;
            while (iss >> word) {
                tokens.push_back(word);
            }
            command = tokens[0];
            tokens.erase(tokens.begin());

            std::string target = std::accumulate(tokens.begin(), tokens.end(), std::string(""));

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

    // Speaks to NPC
    void meet(std::vector<std::string> target) {
        std::vector<NPC>& npcs = curr_location.get_NPCs();
        // check if target is in npcs
        // then maybe set index i = target index in npcs
        std::string npc_name = npcs[0].getName();
        std::cout << npc_name << std::endl;
        std::string npc_message = npcs[0].getMessage();
        std::cout << npc_message << std::endl;
    }

    void take(std::vector<std::string> target);

    void give(std::vector<std::string> target);

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
