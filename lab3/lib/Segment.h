#pragma once

#include "Point.h"
#include <stdexcept>

class Segment {
private:
    Point r1;
    Point r2;
    Point dr; // отрезок-вектор от начала
              // координат
public:
    Segment(Point r1_, Point r2_);

    Segment(const Segment& other): r1(other.r1), r2(other.r2) {};
    Segment(Segment&& other) noexcept;
    Segment& operator=(const Segment& other);
    Segment& operator=(Segment&& other);

    ~Segment() = default;

    Point getR1() const { return r1; };
    Point getR2() const { return r2; };
    Point getDR() const { return dr; };
    
    bool operator||(const Segment& other) const; // parallel
    bool operator%(const Segment& other) const;  // 90 grad
    double length() const { return dr.length(); };
};

double operator*(const Segment& s1, const Segment& s2);
double operator^(const Segment& s1, const Segment& s2);

double angle(const Segment& s1, const Segment& s2);

Segment::Segment(Point r1_, Point r2_) {
    if (r1_ == r2_) {
        throw invalid_argument("Segment cannot be null!");
    }
    r1 = r1_;
    r2 = r2_;
    dr = r2 - r1;
}

Segment::Segment(Segment&& other) noexcept {
    r1 = other.r1;
    r2 = other.r2;
    other.r1 = {0, 0};
    other.r2 = {0, 0};
}

Segment& Segment::operator=(const Segment& other) {
    if (this == &other) return *this;
    r1 = other.r1;
    r2 = other.r2;
    return *this;
}
Segment& Segment::operator=(Segment&& other) {
    if (this == &other) return *this;
    r1 = other.r1;
    r2 = other.r2;
    other.r1 = {0, 0};
    other.r2 = {0, 0};
    return *this;
}

bool Segment::operator||(const Segment& other) const {
    return (getDR() ^ other.getDR()) < EPS;
}

bool Segment::operator%(const Segment& other) const {
    return (getDR() * other.getDR()) < EPS; 
}

double operator*(const Segment& s1, const Segment& s2) {
    return s1.getDR() * s2.getDR();
}

double operator^(const Segment& s1, const Segment& s2) {
    return s1.getDR() ^ s2.getDR();
}