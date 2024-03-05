#pragma once

#include "Figure.h"

class Rectangle : public Figure {
protected:
    vector<Point> points;
    double area;
    Point center;
public:
    Rectangle() = default;
    Rectangle(vector<Point>& _points);
    Rectangle(const Rectangle& other);
    Rectangle(Rectangle&& other);

    ~Rectangle() {};
    
    void normalizePoints() override;
    void calculateArea() override;
    void calculateCenter() override;
    
    vector<Point> getPoints() const { return points; };
    Point getCenter() const { return center; };
    double getArea() const { return area; };
};

Rectangle::Rectangle(vector<Point>& _points) : Rectangle(){
    points.reserve(_points.size());
    points = _points;
    normalizePoints();
    RectangleValidator::validate(points);
    calculateCenter();
    calculateArea();
}

Rectangle::Rectangle(const Rectangle& other) : Rectangle(){
    points.reserve(other.points.size());
    points = other.points;
    center = other.center;
    area = other.area;
}

Rectangle::Rectangle(Rectangle&& other) : Rectangle(){
    points.reserve(other.points.size());
    points = other.points;
    center = other.center;
    area = other.area;
    delete& other;
}

void Rectangle::normalizePoints() {
    sort(points.begin(), points.end(), [&](const Point& p1, const Point& p2) {
        double angle1 {angle(center, p1)};
        double angle2 {angle(center, p2)};
        return angle1 < angle2;
    });
}

void Rectangle::calculateArea() {
    Segment s1(points[0], points[1]);
    Segment s2(points[1], points[2]);
    area = s1.length() * s2.length();
}

void Rectangle::calculateCenter() {
    center = {(points[0].getX() + points[2].getX()) / 2
              , (points[0].getY() + points[2].getY()) / 2};
}