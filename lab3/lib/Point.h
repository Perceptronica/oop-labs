
#pragma once

#include <iostream>
#include <cmath>

using namespace std;

const long double EPS = 1e-6;

class Point {
private:
    double x;
    double y;

public:
    Point(): x(0.0), y(0.0) {};
    Point(double x_, double y_): x(x_), y(y_) {};
    
    Point(const Point& other): x(other.x), y(other.y) {};
    Point(Point&& other) noexcept; 
    Point& operator=(const Point& other);
    Point& operator=(Point&& other) noexcept;

    ~Point() = default;

    double getX() const { return x; }
    double getY() const { return y; }
    double length() const; // так как точка ≃ радиус-вектор

    Point operator+(const Point& other) const;
    Point operator-(const Point& other) const;

    bool operator==(const Point& other) const;

    void setX(double x_) { this->x = x_; }
    void setY(double y_) { this->y = y_; }

    friend istream& operator>>(istream& in, Point& r);
    friend ostream& operator<<(ostream& out, const Point& r);
};

Point::Point(Point&& other) noexcept {
    x = other.x;
    y = other.y;
    other.x = 0;
    other.y = 0;
}

Point& Point::operator=(const Point& other) {
    if (this == &other) return *this;
    x = other.x;
    y = other.y;
    return *this;
}

Point& Point::operator=(Point&& other) noexcept {
    if (this == &other) return *this;
    x = other.x;
    y = other.y;
    other.x = 0;
    other.y = 0;
    return *this;
}

double Point::length() const {
    return sqrt(getX() * getX() + getY() * getY());
}

Point Point::operator+(const Point& other) const {
    return {x + other.x, y + other.y};
}

Point Point::operator-(const Point& other) const {
    return {x - other.x, y - other.y};
}

bool Point::operator==(const Point& other) const {
    return abs(x - other.x) < EPS && 
           abs(y - other.y) < EPS;
}

istream& operator>>(istream& in, Point& r) {
    double x_, y_;
    in >> x_ >> y_;
    r.setX(x_);
    r.setY(y_);
    return in;
}

ostream& operator<<(ostream& out, const Point& r) {
    out << "(" << r.getX() << ", " << r.getY() << ")";
    return out;
}

double operator*(const Point& r1, const Point& r2) {
    return r1.getX() * r2.getX() + r1.getY() * r2.getY();
}

double operator^(const Point& r1, const Point& r2) {
    return r1.getX() * r2.getY() - r1.getY() * r2.getX();
}


/*
- конструктор по умолчанию
- конструктор с параметрами
- конструктор копирования (1)
- конструктор перемещения (2)
- оператор присваивания копированием (3)
- оператор присваивания перемещением (4)
- деструктор (5)
*/