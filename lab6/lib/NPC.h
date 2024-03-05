#pragma once

#include <iostream>
#include <cmath>
#include "Visitor.h"

enum state {DEAD, ALIVE};

class INPC {
    protected:
        std::string NPCname;
        bool state;
        std::pair<double, double> coords;
    
    public:
        INPC(std::string name) : NPCname(std::move(name)), state(ALIVE) {}
        virtual bool accept(IVisitor& visitor) = 0;
        
        bool getState() const { 
            return state; 
        }

        std::string getName() const {
            return NPCname;
        }
        
        std::pair<double, double> getCoords() const {
            return coords;
        }
        
        bool isClose(INPC* obj, double dist) const {
            std::pair<double, double> coordAttacker = this->getCoords();
            std::pair<double, double> coordDefender = obj->getCoords();
            double x {coordAttacker.first - coordDefender.first};
            double y {coordAttacker.second - coordDefender.second};
            double distance = std::sqrt(x * x + y * y);
            return dist >= distance;
        }

        virtual ~INPC() = default;
};

class RK : public INPC {
public:
    RK() = delete;
    RK(double x, double y) : INPC("RK") {
        coords = std::make_pair(x, y);
        std::cout << "RK was created :(" << x << ", " << y << ")\n";
    }
    
    bool accept(IVisitor& visitor) override { 
        return visitor.visit(*this); 
    }
};


class Druid : public INPC {
public:
    Druid() = delete;
    Druid(double x, double y) : INPC("Druid") {
        coords = std::make_pair(x, y);
        std::cout << "Druid was created :(" << x << ", " << y << ")\n";
    }
    bool accept(IVisitor& visitor) override { 
        return visitor.visit(*this); 
    }
};


class Elf : public INPC {
public:
    Elf() = delete;
    Elf(double x, double y) : INPC("Elf") {
        coords = std::make_pair(x, y);
        std::cout << "Elf was created :(" << x << ", " << y << ")\n";
    }
    bool accept(IVisitor& visitor) override { 
        return visitor.visit(*this); 
    }
};