#pragma once
#include "UI.h"

struct Menu {
    static void Start();
};

void Menu::Start() {
    int npcCounter = 0;
    std::vector<INPC*> npcArray;
    std::cout << "Enter an amount of NPCs: ";
    std::cin >> npcCounter;

    std::cout << "Creating NPCs..." << std::endl;
    NPCGenerator(npcArray, npcCounter);
    std::cout << "Creating done!" << std::endl << std::endl;

    std::cout << "Writing an NPC array in file..." << std::endl;
    const std::string fileName = "logs/npc.txt";
    SaveNPCArrayToFile(npcArray, fileName);
    std::cout << "Done!" << std::endl << std::endl;

    std::cout << "Reading NPCs from file..." << std::endl;
    std::vector<INPC*> loadedArray = LoadNPCArrayFromFile(fileName);
    std::cout << "Done!" << std::endl << std::endl;

    while (true) {
        std::string inputFromUser = "";
        std::cout << "Enter 'go' to start battle or 'exit': ";
        std::cin >> inputFromUser;
        if (inputFromUser == "go") {
            MakeFight(loadedArray);
            break;
        } else if (inputFromUser == "exit") {
            return;
        } else {
            std::cout << "enter something right!" << std::endl;
        }
    }
}