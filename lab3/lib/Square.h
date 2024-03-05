#pragma once

#include "Rectangle.h"

class Square : public Rectangle {
protected:
    vector<Point> points;
    double area;
    Point center;
public:
    Square() = default;
    Square(vector<Point>& _points);
    Square(const Square& other);
    Square(Square&& other);

    ~Square() {};

    void normalizePoints() override;
    void calculateArea() override;
    void calculateCenter() override;
    
    vector<Point> getPoints() const { return points; };
    Point getCenter() const { return center; };
    double getArea() const { return area; };
};

Square::Square(vector<Point>& _points) : Square(){
    points.reserve(_points.size());
    points = _points;
    normalizePoints();
    SquareValidator::validate(points);
    calculateCenter();
    calculateArea();
}

Square::Square(const Square& other) : Square(){
    points.reserve(other.points.size());
    points = other.points;
    center = other.center;
    area = other.area;
}

Square::Square(Square&& other) : Square(){
    points.reserve(other.points.size());
    points = other.points;
    center = other.center;
    area = other.area;
    delete& other;
}

void Square::normalizePoints() {
    sort(points.begin(), points.end(), [&](const Point& p1, const Point& p2) {
        double angle1 {angle(center, p1)};
        double angle2 {angle(center, p2)};
        return angle1 < angle2;
    });
}

void Square::calculateArea() {
    Segment s(points[0], points[1]);
    area = s.length() * s.length();
}

void Square::calculateCenter() {
    center = {(points[0].getX() + points[2].getX()) / 2
              , (points[0].getY() + points[2].getY()) / 2};
}