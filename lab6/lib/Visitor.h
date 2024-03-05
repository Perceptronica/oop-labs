#pragma once

#include "NPC.h"

class RK;
class Druid;
class Elf;

class IVisitor {
public:
    virtual bool visit(const RK& rk) = 0;
    virtual bool visit(const Druid& druid) = 0;
    virtual bool visit(const Elf& elf) = 0;

};


class RKVisitor : public IVisitor {
public:
    bool visit(const RK& rk) override { return false; }
    bool visit(const Druid& druid) override { return false; }
    bool visit(const Elf& elf) override { return true; }
};


class DruidVisitor : public IVisitor {
public:
    bool visit(const RK& rk) override { return false; }
    bool visit(const Druid& druid) override { return true; }
    bool visit(const Elf& elf) override { return false; }
};


class ElfVisitor : public IVisitor {
public:
    bool visit(const RK& rk) override { return true; }
    bool visit(const Druid& druid) override { return true; }
    bool visit(const Elf& elf) override { return false; }
};