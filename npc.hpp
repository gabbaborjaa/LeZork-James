#ifndef NPC_HPP
#define NPC_HPP

#include <string>
#include <vector>
#include <iostream>

class NPC {
    public:
        NPC(std::string name, std::string description, std::vector<std::string> messages)
            : name(name), description(description), messages(messages), messageNumber(0) {
            if (name.empty()){
                throw std::invalid_argument("Name cannot be blank");
            } else {
                this->name = name;
            }
            if (description.empty()){
                throw std::invalid_argument("Description cannot be blank");
            } else {
                this->description = description;
            }
            if (messages.empty()){
                throw std::invalid_argument("Messages cannot be empty");
            } else {
                this->messages = messages;
            }
        }
        std::string getName(){
            return name;
        }

        std::string getDescription(){
            return description;
        }

        std::string getMessage(){
            if (messages.empty()) {
                throw std::runtime_error("No messages available");
            }
            std::string currentMessage = messages[messageNumber];
            messageNumber = (messageNumber + 1) % messages.size();
            return currentMessage;
        }

        friend std::ostream& operator<<(std::ostream& os, const NPC& npc){
            os << npc.name;
            return os;
        }
    private:
        std::string name;
        std::string description;
        std::vector<std::string> messages;
        int messageNumber;
};

#endif