/*
 * Team Members:
 * Drew Baine
 * Gab Borja
 * Hunter McGraw
 * 3/2/25
 */

#ifndef __HPP__LOCATION__
#define __HPP__LOCATION__

#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <stdexcept>
#include <functional>
#include "npc.hpp"
#include "item.hpp"

class Location{

    private:
        std::string name;
        std::string description;
        bool visited = false;
        std::map<std::string, std::reference_wrapper<Location> > neighbors; 
        std::vector<NPC> NPCs;
        std::vector<Item> items;

    public:
        Location(){
            //blank constructor
            this->name = "";
            this->description = "";
        }
        Location(std::string name, std::string description){
            this->name = name;
            this->description = description;
        }

        friend std::ostream& operator<<(std::ostream& os, const Location& obj){
            //printing
            os << obj.name << " - " << obj.description;
            return os;
        }
        // void add_location(std::string direction, std::reference_wrapper<Location> location) {
        void add_location(std::string direction,Location& location) {
            //adds location to neighbors. converts to reference wrapper of location first
            //used chatgpt for exception handling
            if (direction.empty()) {
                throw std::invalid_argument("Direction cannot be blank.");
            }
            if (neighbors.find(direction) != neighbors.end()) {
                throw std::invalid_argument("Key already exists in the map.");
            }
            //this->neighbors.insert(std::pair<std::string, std::reference_wrapper<Location>>(direction, std::ref(location)));
               //used CHATGPT
                this->neighbors.emplace(std::piecewise_construct,
                    std::forward_as_tuple(direction),
                    std::forward_as_tuple(std::ref(location)));
        }
        const std::map<std::string, std::reference_wrapper<Location> >& get_locations() const {
            //returns map of locations
            return this->neighbors;
        }
        void set_visited(){
            //sets visited to true. cannot be changed to false
            this->visited = true;
        }
        bool get_visited(){
            //returns if the locaiton is visited
            if(visited){
                return true;
            }
            return false;
         }
        void add_npc(NPC& npc){
            //adds an npc to list of npcs
            this->NPCs.push_back(npc);
        }

        void add_item(Item& item){
            //adds an item
            this->items.push_back(item);
        }

        void remove_item(Item& item){
            //removes an item
            this->items.erase(std::remove(this->items.begin(), this->items.end(), item));
        }

        std::vector<Item>& get_items(){
            //returns vector of items
            return this->items;
        }

        std::vector<NPC>& get_NPCs(){
            //returns vector of NPCs
            return this->NPCs;
        }

        std::string get_name(){
            //returns vector of names
            return this->name;
        }

 };

 #endif
