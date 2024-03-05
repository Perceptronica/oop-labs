#pragma once

#include "NPC.h"
#include <fstream>

class INPC;

class IObserver {
    public:
        virtual void update(INPC* npc) const noexcept = 0;
};

std::ostream & operator<< (std::ostream &out
                          , const std::pair<double, double>& p) {
    out << "(" << p.first << ", " << p.second << ")";
    return out;
}

class ObserverConsoleOutput : public IObserver {
    public:
        void update(INPC* npc) const noexcept override {
            std::cout << "Killed: " << npc->getName() << std::endl;
            std::cout << "Coordinates: " << npc->getCoords() << std::endl;
    }
};

class ObserverFileOutput : public IObserver {
    public:
        void update(INPC* npc) const noexcept override;
};

void ObserverFileOutput::update(INPC* npc) const noexcept {
    const std::string path = "logs/log.txt";
    std::ofstream logs(path, std::ofstream::app);
    try {
        if (logs.is_open()) {
            logs << "Killed: " << npc->getName() << '\n';
            logs << "Coordinates: " << "(" <<
                npc->getCoords().first << ", " <<  npc->getCoords().second << ")\n";
        } else {
            throw std::logic_error("File opening error");
        }
        logs.close();
    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
    }
}