/*
 * Team Members:
 * Drew Baine
 * Gab Borja
 * Hunter McGraw
 * 3/2/25
 */

#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <sstream>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <iomanip>
#include "Location.hpp"
#include "item.hpp"
#include "npc.hpp"

class Game {
    private:
        std::map<std::string, void(Game::*)(std::vector<std::string>) > commands;
        std::vector<Item> items;
        float weight;
        std::vector<Location> locations;
        Location curr_location;
        int calories_needed;
        bool game_in_progress;

    public:
        Game() {
            this->commands = setup_commands();
            create_world();
            this->weight = 0;
            this->calories_needed = 500;
            this->game_in_progress = true;
            this->curr_location = random_location();
        }

    void create_world() {

        // AI generated items, NPCs, NPC messages, and locations
        std::vector<std::string> lebronMessages = {
            "I am the King!",
            "Always nice to meet a fan!",
            "Have you seen Bronny?",
            "I'm NEVER retiring!"
        };

        std::vector<std::string> bronnyMessages = {
            "I'm working hard to make it to the league!",
            "My dad gives me the best advice on and off the court.",
            "You think I can dunk like him?",
            "I'm just focused on improving every day."
        };

        std::vector<std::string> wadeMessages = {
            "Flash never slows down!",
            "LeBron and I made history in Miami.",
            "You ever seen the alley-oop from the 2010 playoffs?",
            "Retirement is great, but I still got buckets!"
        };

        std::vector<std::string> davisMessages = {
            "Defense wins championships.",
            "If I stay healthy, nobody can stop me.",
            "LeBron always calls me ‘The Brow’!",
            "I need to ice my knees after every game."
        };

        std::vector<std::string> kyrieMessages = {
            "Basketball is an art form.",
            "That 2016 Finals shot? Legendary.",
            "LeBron and I had our ups and downs, but we made history.",
            "Have you ever thought about the shape of the Earth?"
        };

        Item basketball("Basketball", "Lebron's favorite ball", 40, 4);
        Item proteinShake("Protein Shake", "A delicious protein shake", 150, 7);
        Item championshipRing("Championship Ring", "A shimmering ring symbolizing one of LeBron's NBA titles. It glows with a legendary aura.", 225, 2);
        Item sneakers("Nike LeBron Sneakers", "A pair of iconic Nike LeBron 20s. Wearing them might help you move faster on and off the court.", 70, 14);
        Item jersey("Official Jersey", "An official Los Angeles Lakers #23 jersey.", 0, 12);
        Item rookieCard("Rookie Card", "A rare 2003 rookie card, highly valuable among collectors.", 0, 3.1);
        Item headband("Headband", "A white headband, reminiscent of an early career look.", 0, 6);
        Item playbook("Playbook", "A notebook filled with high-IQ basketball strategies.", 90, 11.5);
        Item actionFigure("Action Figure", "A detailed collectible figure in a dunking pose.", 110, 8);
        Item mvpStatue("MVP Trophy", "A miniature replica of the NBA MVP trophy.", 200, 30);

        NPC lebron("LeBron James", "A legendary basketball player", lebronMessages);
        NPC bronny("Bronny James", "A young and talented basketball player following in his father's footsteps.", bronnyMessages);
        NPC wade("Dwyane Wade", "A retired NBA superstar and close friend of LeBron, known for their Miami Heat days.", wadeMessages);
        NPC davis("Anthony Davis", "A dominant big man and LeBron's teammate, known for his elite defense and versatility.", davisMessages);
        NPC kyrie("Kyrie Irving", "A skilled point guard and former teammate of LeBron, known for his clutch plays.", kyrieMessages);

        Location court("Basketball Court", "A bright hardwood court, buzzing with the sound of sneakers and bouncing balls.");
        Location kingSuite("King's Suite", "A luxurious VIP suite overlooking the court, where LeBron watches the game in style.");
        Location lockers("Locker Room", "A space filled with the scent of sweat and cologne, as players prepare for the game.");
        Location akronHometown("Akron Hometown", "The streets where LeBron grew up, inspiring millions with his rise to greatness.");
        Location championshipRoom("Championship Room", "A trophy room showcasing LeBron's four NBA championship rings and memorable moments.");
        Location lebronHouse("LeBron's House", "A lavish mansion in Los Angeles, where LeBron relaxes and spends time with family.");
        Location philanthropyCenter("Philanthropy Center", "LeBron's charitable headquarters, where he leads initiatives to help underserved communities.");
        Location spaceJamStudio("Space Jam Studio", "The set where LeBron filmed his iconic role in *Space Jam: A New Legacy*, blending basketball with Hollywood.");

        locations.push_back(court);//0
        locations.push_back(kingSuite);//01
        locations.push_back(philanthropyCenter);//02
        locations.push_back(lockers);//03
        locations.push_back(lebronHouse);//04
        locations.push_back(spaceJamStudio);//05
        locations.push_back(akronHometown);//06
        locations.push_back(championshipRoom);//07

        locations[0].add_npc(lebron);
        locations[0].add_item(basketball);
        court.add_npc(lebron);
        court.add_item(basketball);

        locations[1].add_npc(davis);
        locations[1].add_item(playbook);
        kingSuite.add_npc(davis);
        kingSuite.add_item(playbook);

        locations[2].add_item(mvpStatue);
        philanthropyCenter.add_item(mvpStatue);

        locations[3].add_npc(kyrie);
        locations[3].add_item(proteinShake);
        lockers.add_npc(kyrie);
        lockers.add_item(proteinShake);

        locations[4].add_npc(bronny);
        locations[4].add_item(jersey);
        lebronHouse.add_item(sneakers);
        lebronHouse.add_npc(bronny);
        lebronHouse.add_item(jersey);
        lebronHouse.add_item(sneakers);

        locations[5].add_item(headband);
        spaceJamStudio.add_item(headband);

        locations[6].add_item(actionFigure);
        locations[6].add_item(rookieCard);
        akronHometown.add_item(actionFigure);
        akronHometown.add_item(rookieCard);

        locations[7].add_npc(wade);
        locations[7].add_item(championshipRing);
        championshipRoom.add_npc(wade);
        championshipRoom.add_item(championshipRing);

        locations[0].add_location("East",locations[3]);
        locations[0].add_location("South",locations[1]);
        court.add_location("East", lockers);
        court.add_location("South", kingSuite);

        locations[1].add_location("East",locations[4]);
        locations[1].add_location("South",locations[2]);
        locations[1].add_location("North",locations[0]);
        kingSuite.add_location("East", lebronHouse);
        kingSuite.add_location("South", philanthropyCenter);
        kingSuite.add_location("North", court);

        locations[2].add_location("East",locations[5]);
        locations[2].add_location("North",locations[1]);
        philanthropyCenter.add_location("East", spaceJamStudio);
        philanthropyCenter.add_location("North", kingSuite);

        locations[3].add_location("East",locations[6]);
        locations[3].add_location("South",locations[4]);
        locations[3].add_location("West",locations[0]);
        lockers.add_location("East", akronHometown);
        lockers.add_location("South", lebronHouse);
        lockers.add_location("West", court);

        locations[4].add_location("North",locations[3]);
        locations[4].add_location("East",locations[7]);
        locations[4].add_location("South",locations[5]);
        locations[4].add_location("West",locations[1]);
        lebronHouse.add_location("North", lockers);
        lebronHouse.add_location("East", championshipRoom);
        lebronHouse.add_location("South", spaceJamStudio);
        lebronHouse.add_location("West", kingSuite);

        locations[5].add_location("North",locations[4]);
        locations[5].add_location("West",locations[2]);
        spaceJamStudio.add_location("North", lebronHouse);
        spaceJamStudio.add_location("West", philanthropyCenter);

        locations[6].add_location("South",locations[7]);
        locations[6].add_location("West",locations[3]);
        akronHometown.add_location("South", championshipRoom);
        akronHometown.add_location("West", lockers);

        locations[7].add_location("West",locations[4]);
        locations[7].add_location("North",locations[6]);
        championshipRoom.add_location("West", lebronHouse);
        championshipRoom.add_location("North", akronHometown);

        
    }

    std::map<std::string, void(Game::*)(std::vector<std::string>)> setup_commands() {
        std::map<std::string, void(Game::*)(std::vector<std::string>)> commands;
        commands["quit"] = &Game::quit;
        commands["q"] = &Game::quit;
        commands["help"] = &Game::show_help;
        commands["items"] = &Game::show_items;
        commands["look"] = &Game::look;
        commands["meet"] = &Game::meet;
        commands["talk"] = &Game::talk;
        commands["take"] = &Game::take;
        commands["give"] = &Game::give;
        commands["go"] = &Game::go;
        commands["speak"] = &Game::talk;
        commands["interact"] = &Game::meet;
        commands["dream"] = &Game::dream;
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
            std::cout << '\n';
            std::cout << "Enter a command: ";
            std::string command;
            std::getline(std::cin, command); // how do we get rid of blank line
            std::vector<std::string> tokens;
            std::istringstream iss(command); // Copilot
            std::string word;
            while (iss >> word) {
                tokens.push_back(word);
            }
            if (tokens[0] == "show") {
                tokens.erase(tokens.begin());
            }
            command = tokens[0];
            tokens.erase(tokens.begin());

            if (tokens[0] == "to" or tokens[0] == "with" or tokens[0] == "the") {
                tokens.erase(tokens.begin());
            }

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
        if (calories_needed) {
            std::cout << "You lose!" << std::endl;
        } else {
            std::cout << "You win!" << std::endl;
        }
    }

    void show_help(std::vector<std::string> target) {
        // Date and time helped by Copilot
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        std::tm* now_tm = localtime(&now_c);
        std::cout << "Date and Time: " << std::put_time(now_tm, "%m-%d-%Y - %H:%M:%S") << '\n' << std::endl;

        std::cout << "Available Commands:" << std::endl;
        std::cout << "(show) help -> lists all commands." << std::endl;
        std::cout << "quit -> quits the program." << std::endl;
        std::cout << "(show) items -> lists items in inventory." << std::endl;
        std::cout << "meet -> gives name and description of NPC." << std::endl;
        std::cout << "talk (to) -> gets a message from the NPC." << std::endl;
        std::cout << "look -> looks in the current location and what's in it." << std::endl;
        std::cout << "go -> goes to a neighboring location." << std::endl;
        std::cout << "take -> takes item from current location." << std::endl;
        std::cout << "give -> puts item in current location or gives to LeBron if in the court." << std::endl;

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
            items.push_back(item_vector[i]);
            weight += item_vector[i].getWeight();
            std::cout << "Took " << item_name << "!" << std::endl;
            curr_location.remove_item(item_vector[i]);
            for (auto it = locations.begin(); it != locations.end(); ++it) {
                if (it->get_name() == curr_location.get_name()) {
                    std::cout << "Done!" << std::endl;
                    it->remove_item(item_vector[i]);
                }
            }
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
            std::cout << "Gave " << item_name << "!" << std::endl;

            curr_location.add_item(items[i]);
            for (auto it = locations.begin(); it != locations.end(); ++it) {
                if (it->get_name() == curr_location.get_name()) {
                    std::cout << "Done!" << std::endl;
                    it->add_item(items[i]);
                }
            }
            weight -= items[i].getWeight();

            if (curr_location.get_name() == "Basketball Court") {
                if (items[i].getCalories()) {
                    calories_needed -= items[i].getCalories();
                } else {
                    curr_location = random_location();
                }
                if (calories_needed <= 0) {
                    calories_needed = 0;
                    game_in_progress = false;
                }
                std::cout << "LeBron James needs: " << calories_needed << " more calorie(s)!" << std::endl;
            }
            items.erase(std::remove(this->items.begin(), this->items.end(), items[i]));

        } else {
            std::cout << "Item not in inventory!" << std::endl;
        }
    }

    void go(std::vector<std::string> target) {
        if (target.empty()) {
             std::cout << "Specify a direction to go." << std::endl;
            return;
        }

        std::string direction = target[0];

        if (weight > 30) {
            std::cout << "Too heavy! Can't move." << std::endl;
            return;
        }
        
        const auto& neighbors = curr_location.get_locations();
        auto it = neighbors.find(direction);
        if (it != neighbors.end()) {
            curr_location = it->second.get();
            it->second.get().set_visited();
            std::cout << "You moved to: " << curr_location.get_name() << std::endl;
            } else {
                std::cout << "You can't go that way." << std::endl;
    }
        }
    }

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
        if (NPCs.size() > 0) {
            std::cout << "\nYou see the following NPCs:" << std::endl;
            for(auto it = NPCs.begin(); it != NPCs.end(); ++it){
                std::cout << " - "<< *it << std::endl;
            }
        } else {
            std::cout << "\nYou are alone." << std::endl;
        }
        if (items.size() > 0) {
            std::cout << "\nYou see the following items:" << std::endl;
            for(auto it = items.begin(); it != items.end(); ++it){
                std::cout << " - "<< *it << std::endl;
            }
        } else {
            std::cout << "There are no items." << std::endl;
        }

        std::map<std::string, std::reference_wrapper<Location>> neighbors = curr_location.get_locations();
        std::cout << "\nYou can go in the following directions:" << std::endl;
        for (const auto& [key, ref] : neighbors) { // ChatGPT
            Location& loc = ref.get();
            if (loc.get_visited()) {
                std::cout << " - " << key << " - " << loc.get_name() << std::endl;
            } else {
                std::cout << " - " << key << " - Unknown" << std::endl;
            }
        }
    }

    void quit(std::vector<std::string> target) {
        std::cout << "Quit Game." << std::endl;
        this->game_in_progress = false;
    }

    // Add two additional commands here
    void dream(std::vector<std::string> target){
        std::cout << "Remember. Enter Mamba Mentality - Kobe Bryant" << std::endl;
    }
};

#endif //GAME_HPP