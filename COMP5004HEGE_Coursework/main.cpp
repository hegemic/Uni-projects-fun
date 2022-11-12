#include <iostream>
#include <iomanip>
#include <memory>
#include <iterator>
#include <vector>
#include <forward_list>
#include <list>
#include <fstream>
#include "Room.h"
#include "wordwrap.h"
#include "State.h"
#include "strings.h"
#include "GameObject.h"


using std::string;
using std::unique_ptr;

string commandBuffer;
State *currentState;

/**
 * Print out the command prompt then read a command into the provided string buffer.
 * @param buffer Pointer to the string buffer to use.
 */
void inputCommand(string *buffer) {
    buffer->clear();
    std::cout << "> ";
    std::getline(std::cin, *buffer);
}

/**
 * Sets up the map.
 */
void initRooms() {
    auto * r5 = new Room(&r5name, &r5desc);
    auto * r4 = new Room(&r4name, &r4desc);
    auto * r3 = new Room(&r3name, &r3desc);
    auto * r2 = new Room(&r2name, &r2desc);
    auto * r1 = new Room(&r1name, &r1desc);
    Room::addRoom(r1);
    Room::addRoom(r2);
    Room::addRoom(r3);
    Room::addRoom(r4);
    Room::addRoom(r5);
    r1->setWest(r2);
    r2->setSouth(r3);
    r3->setWest(r4);
    r4->setNorth(r5);

    auto item_1 = GameObject(new string("stick"), new string("it's brown"), new string("st"));
    auto item_2 = GameObject(new string("candy"), new string("it's sweet"), new string("c"));
    auto item_3 = GameObject(new string("pig"), new string("it looks like a dog"), new string("p"));
    auto item_4 = GameObject(new string("sword"), new string("it's sharp"), new string("sw"));
    auto item_5 = GameObject(new string("rock"), new string("it can be used to break things"), new string("r"));
    auto item_6 = GameObject(new string("key"), new string("what does this key open?"), new string("k"));
    auto item_7 = GameObject(new string("apple"), new string("it's a red apple"), new string("a"));

    r1->addItem(item_1);
    r1->addItem(item_2);
    r1->addItem(item_3);
    r2->addItem(item_4);
    r3->addItem(item_5);
    r4->addItem(item_6);
    r5->addItem(item_7);
}

/**
 * Sets up the game state.
 */
void initState() {
    currentState = new State(Room::rooms.front());
}

void lookItemsInRoom() {
    if (currentState->getCurrentRoom()->getItems().empty()){
        wrapOut(new string("No items in this room"));
    } else {
        wrapOut(new string("The items in this room are: \n"));
        for (auto item: currentState->getCurrentRoom()->getItems()){
            wrapOut(item.getKeyword());
            wrapOut(new string(":"));
            wrapOut(item.getName());
            wrapOut(new string("\n"));
        }
    }
    wrapEndPara();
}

void get(string sWord) {
    for(auto item: currentState->getCurrentRoom()->getItems()){
        //object with keyword equal to secondWord
        if(sWord == *item.getKeyword()){
            //move object from the current room list to inventory
            wrapOut(new string(sWord + " added to inventory"));
            currentState->addItem(item);
            currentState->getCurrentRoom()->removeItem(item);
            break;
        }
    }
    wrapEndPara();
}

void drop(string sWord) {
    for(auto item: currentState->getInventory()){
        //object with keyword equal to secondWord
        if(sWord == *item.getKeyword()){
            //move object from the inventory to current room list
            wrapOut(new string(sWord + " removed from inventory"));
            currentState->removeItem(item);
            currentState->getCurrentRoom()->addItem(item);
            break;
        } else {
            wrapOut(new string("Item doesn't exist in inventory"));
        }
    }
    wrapEndPara();
}

void inventory() {
    //print out short names of all objects in inventory
    if(currentState->getInventory().empty()){
        wrapOut(new string("Inventory is empty!"));
    } else {
        for (auto item: currentState->getInventory()) {
            wrapOut(item.getName());
        }
    }
    wrapEndPara();
}

void examine(string kWord) {
    //print long description of secondWord
    for(auto item: currentState->getCurrentRoom()->getItems()){
        if(kWord == *item.getKeyword()) {
            wrapOut(item.getDescription());
            break;
        }
    }
    wrapEndPara();
}

/*
 * What i want to be saved in game:
 * current room
 * inventory
 * where objects are (which room they are in)
 *
 * File will look like this:
 * Current room (e.g. Room 3)
 * Items in inventory (e.g. pig stick)
 * Room, objects in room (e.g. Room 2 key)
 * etc
 *
 * Example file:
 * Room 2
 * pig stick
 * Room 2 key
 * Room 2 sword
 * Room 3 rock
 * Room 4 candy
 * Room 5 apple
 *
 */

//Save into file
bool saveCurrentRoom(string filename){
    std::ofstream file(filename);
    file<<*currentState->getCurrentRoom()->getRoomName()<<std::endl;
    std::cout<<*currentState->getCurrentRoom()->getRoomName();
    bool success = file.good();
    file.close();
    wrapEndPara();
    return success;
}

bool saveInventory(string filename){
    std::ofstream file(filename, std::ios::app);
    for (auto itemInInventory: currentState->getInventory()) {
        //wrapOut(itemInInventory.getName());
        file<<*itemInInventory.getName()<<std::endl;
    }
    bool success = file.good();
    file.close();
    wrapEndPara();
    return success;
}

bool saveItemPlacement(string filename){
    std::ofstream file(filename, std::ios::app);
    for(auto roomsExists: Room::rooms){
        for(auto itemsInRoom: roomsExists->getItems()){
            file<<*roomsExists->getRoomName()<<" "<<*itemsInRoom.getName()<<std::endl;
        }
    }
    bool success = file.good();
    file.close();
    wrapEndPara();
    return success;
}

//Read from file
/*
 * Need to:
 * Delete state, inventory and where items are in rooms
 * Create new current room (which is the current room the player saved in text file)
 * Create new inventory with items in second line of text file (split on " " between items)
 * Place items in rooms told in textfile (get room from first word and item in second word)
 *
 */
bool read(string filename){
    std::ifstream file(filename);
    if(!file.good()){
        return false;
    }

    std::vector<std::string> lines;

    while(!file.eof()){
        string line;
        getline(file, line);
        if(line.size()==0){
            continue;
        }

        lines.push_back(line);

        /*
        State test;
        std::stringstream s(line);
        s >> test;

        if(!s.fail()){
            lines.push_back(test);
        }
        else{
            file.close();
            return false;
        }*/
    }
    for(std::string theLines : lines) {
        std::cout<<theLines<<std::endl;
    }

    string cRoom = lines[0];
    string inventory = lines[1];

    //for(auto item: currentState->getInventory()){
    //    drop(item);
    //}
    //add to inventory lines[1] split up on " "

    file.close();
    return true;
}


/**
 * The main game loop.
 */
void gameLoop() {
    bool gameOver=false;
    Room* direction = nullptr;
    while (!gameOver) {
        direction = nullptr;
        /* Ask for a command. */
        bool commandOk = false;
        inputCommand(&commandBuffer);
        /* The first word of a command would normally be the verb. The first word is the text before the first
         * space, or if there is no space, the whole string. */

        auto endOfVerb = commandBuffer.find(static_cast<uint8_t>(commandBuffer.find(' ')));
        auto endOfWord = commandBuffer.find(static_cast<uint8_t>(commandBuffer.find('\n')));

        auto firstWord = commandBuffer.substr(0,static_cast<uint8_t>(commandBuffer.find(' ')));
        //auto secondWord = commandBuffer.substr(endOfVerb + 1, endOfWord);

        //std::cout<<secondWord<<std::endl;

        /* We could copy the verb to another string but there's no reason to, we'll just compare it in place. */
        /* Command to go north. */
        if ((commandBuffer.compare(0,endOfVerb,"north") == 0) || (commandBuffer.compare(0,endOfVerb,"n") == 0)) {
            commandOk = true; /* Confirm command has been handled */
            /* See if there's a north exit */
            direction = currentState->getCurrentRoom()->getNorth();
            if (direction == nullptr) {
                wrapOut(&badExit);
                wrapEndPara();
            } else {
                currentState->goTo(direction);
            }

        } else if ((commandBuffer.compare(0,endOfVerb,"south") == 0) || (commandBuffer.compare(0,endOfVerb,"s") == 0)) {
            // Command to go south.
            commandOk = true;
            direction = currentState->getCurrentRoom()->getSouth();
            if (direction == nullptr) {
                wrapOut(&badExit);
                wrapEndPara();
            } else {
                currentState->goTo(direction);
            }
        } else if ((commandBuffer.compare(0,endOfVerb,"east") == 0) || (commandBuffer.compare(0,endOfVerb,"e") == 0)) {
            // Command to go east.
            direction = currentState->getCurrentRoom()->getEast();
            commandOk = true;
            if (direction == nullptr) {
                wrapOut(&badExit);
                wrapEndPara();
            } else {
                currentState->goTo(direction);
            }
        } else if ((commandBuffer.compare(0,endOfVerb,"west") == 0) || (commandBuffer.compare(0,endOfVerb,"w") == 0)) {
            //Command to go west.
            commandOk = true;
            direction = currentState->getCurrentRoom()->getWest();
            if (direction == nullptr) {
                wrapOut(&badExit);
                wrapEndPara();
            } else {
                currentState->goTo(direction);
            }
        } else if (firstWord == "look"){
            //get items in current room
            commandOk = true;
            lookItemsInRoom();
        } else if(firstWord == "inventory"){
            //get items in inventory
            commandOk = true;
            inventory();
        } else if(firstWord == "get"){
            //getitem()
            try {
                auto secondWord = commandBuffer.substr(static_cast<uint8_t>(commandBuffer.find(' ')) + 1,
                                                       static_cast<uint8_t>(commandBuffer.find('\n')));
                commandOk = true;
                get(secondWord);
            } catch (std::out_of_range e) {
                wrapOut(new string("second word is missing"));
            }

        } else if(firstWord == "drop") {
            //drop()
            try {
                auto secondWord = commandBuffer.substr(static_cast<uint8_t>(commandBuffer.find(' ')) + 1,
                                                       static_cast<uint8_t>(commandBuffer.find('\n')));
                commandOk = true;
                drop(secondWord);
            } catch (std::out_of_range e) {
                wrapOut(new string("second word is missing"));
            }

            //} else if(firstWord == "examine"){
        } else if(firstWord == "examine"){
            //examine()
            try {
                auto secondWord = commandBuffer.substr(static_cast<uint8_t>(commandBuffer.find(' ')) + 1,
                                                       static_cast<uint8_t>(commandBuffer.find('\n')));
                commandOk = true;
                examine(secondWord);
            } catch (std::out_of_range e) {
                wrapOut(new string("second word is missing"));
            }

        }

        if (firstWord == "save") {
            try {
                commandOk = true;
                //auto firstWord = commandBuffer.substr(0,static_cast<uint8_t>(commandBuffer.find(' ')));
                auto secondWord = commandBuffer.substr(static_cast<uint8_t>(commandBuffer.find(' ')) + 1,
                                                       static_cast<uint8_t>(commandBuffer.find('\n')));
                string filename = secondWord;

                //std::cout<<filename;

                saveCurrentRoom(filename);
                saveInventory(filename);
                saveItemPlacement(filename);
            } catch (std::out_of_range e) {
                wrapOut(new string("filename is missing, command is: save filename"));
            }
        }

        if (firstWord == "read") {
            try {
                commandOk = true;
                //auto firstWord = commandBuffer.substr(0,static_cast<uint8_t>(commandBuffer.find(' ')));
                auto secondWord = commandBuffer.substr(static_cast<uint8_t>(commandBuffer.find(' ')) + 1,
                                                       static_cast<uint8_t>(commandBuffer.find('\n')));
                string filename = secondWord;

                //read(filename);
                bool successRead = read(filename);
                if(!successRead){
                    wrapOut(new string("Could not read file"));
                    wrapEndPara();
                } else {
                    wrapOut(new string("Read file OK"));
                    wrapOut(new string(" Loading game..."));
                    wrapEndPara();
                }

            } catch (std::out_of_range e) {
                wrapOut(new string("filename is missing, command is: save filename"));
            }
        }

        /* Quit command */
        if ((commandBuffer.compare(0,endOfVerb,"quit") == 0)) {
            commandOk = true;
            gameOver = true;
        }

        /* If commandOk hasn't been set, command wasn't understood, display error message */
        if(!commandOk) {
            wrapOut(&badCommand);
            wrapEndPara();
        }

    }

}

int main() {
    initWordWrap();
    initRooms();
    initState();
    currentState->announceLoc();
    gameLoop();
    return 0;
}

