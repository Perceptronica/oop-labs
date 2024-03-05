#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <set>
#include "NPCFabric.h"
#include "DeathAgregator.h"
#include "Visitor.h"

enum NPCType {RKType = 1, DruidType = 2, ElfType = 3};

#define WIDTH 500
#define HIGHT 500

void NPCGenerator(std::vector<INPC*>& NPCArray, size_t NPCCount) {
    srand(time(nullptr));
    for (size_t i {0}; i < NPCCount; ++i) {
        INPC* npc {nullptr};
        int randomNumber {std::rand() % 3 + 1};
        double x {static_cast<double>(std::rand() % WIDTH)};
        double y {static_cast<double>(std::rand() % HIGHT)};
        switch (randomNumber) {
            case RKType:
                {
                    RKFabric RKFabric;
                    npc = RKFabric.createNPC(x, y);
                }
                break;
            case DruidType:
                {
                    DruidFabric DruidFabric;
                    npc = DruidFabric.createNPC(x, y);
                }
                break;
            case ElfType:
                {
                    ElfFabric ElfFabric;
                    npc = ElfFabric.createNPC(x, y);
                }
            default:
                break;
        }
        NPCArray.emplace_back(npc);
    }
}

void SaveNPCArrayToFile(const std::vector<INPC*>& NPCArray
                        , const std::string& filename) {
    std::ofstream file(filename);
    try {
        if (!file.is_open()) {
            throw std::logic_error("File opening error");
        } else {
            for (auto & npc : NPCArray) {
                file << npc->getName() << ' ' << npc->getCoords().first << ' ' << npc->getCoords().second << std::endl;
            }
        }
        file.close();
    } catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
}

INPC* NPCFromName(const std::string& name, double x, double y) {
    if (name == "RK") {
        RKFabric RKFabric;
        return RKFabric.createNPC(x, y);
    } else if (name == "Druid") {
        DruidFabric DruidFabric;
        return DruidFabric.createNPC(x, y);
    } else if (name == "Elf") {
        ElfFabric ElfFabric;
        return ElfFabric.createNPC(x, y);
    } else {
        throw std::logic_error("Wrong NPC name");
    }
}

std::vector<INPC*> LoadNPCArrayFromFile(const std::string& filename) {
    std::vector<INPC*> npcArray;
    std::ifstream file(filename);
    try {
        if (!file.is_open()) {
            throw std::logic_error("File opening error");
        } else {
            std::string npcName;
            double x, y;
            while (file >> npcName >> x >> y) {
                npcArray.emplace_back(NPCFromName(npcName, x, y));
            }
            file.close();
        }
    } catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }

    return npcArray;
}

void MakeFight(std::vector<INPC*>& NPCArray) {
    std::set<INPC*> deadNote;

    DeathAgregator deathAgregator;
    ObserverFileOutput fileObserver;
    ObserverConsoleOutput consoleObserver;
    deathAgregator.attach(&fileObserver);
    deathAgregator.attach(&consoleObserver);

    RKVisitor rkVisitor;
    DruidVisitor druidVisitor;
    ElfVisitor elfVisitor;


    for (const auto & attacker : NPCArray) {
        for (const auto & defender : NPCArray) {
            if (attacker != defender && attacker->isClose(defender, 10)) {
                bool fightStatus;
                if (attacker->getName() == "RK") {
                    fightStatus = defender->accept(rkVisitor);
                } else if (attacker->getName() == "Druid") {
                    fightStatus = defender->accept(druidVisitor);
                } else {
                    fightStatus = defender->accept(elfVisitor);
                }
                if (fightStatus) {
                    deadNote.insert(defender);
                }
            }
        }
    }

    for (const auto & death : deadNote) {
        deathAgregator.notify(death);
    }

    deathAgregator.detach(&consoleObserver);
    deathAgregator.detach(&fileObserver);
}