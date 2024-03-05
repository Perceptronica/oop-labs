#pragma once

#include "NPC.h"

class INPCFabric {
protected:
    virtual INPC * createNPC(double x, double y) = 0;
    virtual ~INPCFabric() = default;
};

class RKFabric : public INPCFabric {
    public:
        INPC* createNPC(double x, double y) override {
            return new RK(x, y);
        }
};


class DruidFabric : public INPCFabric {
    public:
        INPC* createNPC(double x, double y) override {
            return new Druid(x, y);
        }
};


class ElfFabric : public INPCFabric {
    public:
        INPC* createNPC(double x, double y) override {
            return new Elf(x, y);
        }
};
