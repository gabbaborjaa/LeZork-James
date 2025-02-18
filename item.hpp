#ifndef __item_hpp_
#define __item_hpp_

#include <string>
#include <stdexcept>
#include <iostream>

class Item {
    public: 
        // Helped by Copilot
        Item(std::string name, std::string description, int calories, float weight) {
            if (name.empty()) {
            throw std::invalid_argument("Name cannot be blank");
            } else {
                this->name = name;
            }
            if (description.empty()){
            throw std::invalid_argument("Description cannot be blank");
            } else {
                this->description = description;
            }
            if (calories < 0 || calories > 1000){
            throw std::invalid_argument("Calories must be more than 0 and less than 1000");
            } else{
                this->calories = calories;
            }
            if (weight < 0.0f || weight > 500.0f){
            throw std::invalid_argument("Weight must weight more than 0 and less than 500");
            } else{ 
                this->weight = weight;
            }
        }
        // Helped by Copilot
        friend std::ostream& operator<<(std::ostream& os, const Item& item) {
            os << item.name << " (" << item.calories << " calories) - " << item.weight << " lb - " << item.description;
            return os;
        }
    private:
        std::string name;
        std::string description;
        int calories;
        float weight;
};

#endif

