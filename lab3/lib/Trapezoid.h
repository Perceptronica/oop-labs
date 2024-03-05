#pragma once

#include "Figure.h"

class Trapezoid : public Figure {
protected:
    vector<Point> points;
    double area;
    Point center;
public:
    Trapezoid() = default;
    Trapezoid(vector<Point>& _points);
    Trapezoid(const Trapezoid& other);
    Trapezoid(Trapezoid&& other);
    
    ~Trapezoid() {};

    void normalizePoints() override;
    void calculateArea() override;
    void calculateCenter() override;
    
    vector<Point> getPoints() const { return points; };
    Point getCenter() const { return center; };
    double getArea() const { return area; };
};

Trapezoid::Trapezoid(vector<Point>& _points) : Trapezoid(){
    points.reserve(_points.size());
    points = _points;
    normalizePoints();
    TrapezoidValidator::validate(points);
    calculateCenter();
    calculateArea();
}

Trapezoid::Trapezoid(const Trapezoid& other) : Trapezoid(){
    points.reserve(other.points.size());
    points = other.points;
    center = other.center;
    area = other.area;
}

Trapezoid::Trapezoid(Trapezoid&& other) : Trapezoid(){
    points.reserve(other.points.size());
    points = other.points;
    center = other.center;
    area = other.area;
    delete& other;
}

void Trapezoid::normalizePoints() {
    sort(points.begin(), points.end(), [&](const Point& p1, const Point& p2) {
        double angle1 {angle(center, p1)};
        double angle2 {angle(center, p2)};
        return angle1 < angle2;
    });
}

void Trapezoid::calculateArea() {
    Segment s1(points[0], points[1]);
    Segment s2(points[1], points[2]);
    Segment s3(points[2], points[3]);
    Segment s4(points[3], points[0]);
    double a, b, h;
    if (s1 || s3) {
        a = s1.length();
        b = s3.length();
        h = std::abs((points[0] - points[2]).getY());
    } else {
        a = s2.length();
        b = s4.length();
        h = std::abs((points[1] - points[3]).getY());
    }
    area = (a + b) * h / 2;
}

void Trapezoid::calculateCenter() {
    int n = points.size();
    if (n >= 3) {
        double sumX {0.0};
        double sumY {0.0};
        for (Point p: points) {
            sumX += p.getX();
            sumY += p.getY();
        }
        center = {sumX / n, sumY / n};
    } else {
        center = {-1e8, -1e8};
    }
}

