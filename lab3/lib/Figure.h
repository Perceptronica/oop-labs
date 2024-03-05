#pragma once

#include "Point.h"
#include "Segment.h"
#include "Validators.h"
#include <vector>
#include <algorithm>

class Figure {
protected:
    vector<Point> points;
    double area;
    Point center;

public:
    Figure() = default;
    Figure(vector<Point>& _points);
    Figure(const Figure& other);
    Figure(Figure&& other);
    Figure& operator=(const Figure& other);
    Figure& operator=(Figure&& other);

    virtual ~Figure() {};

    virtual void normalizePoints();
    virtual void calculateArea();
    virtual void calculateCenter();

    virtual vector<Point> getPoints() const { return points; };
    virtual Point getCenter() const { return center; };
    virtual double getArea() const { return area; };
};

double angle(Point center, Point p) {
    double dx {p.getX() - center.getX()};
    double dy {p.getY() - center.getY()};
    return atan2(dy, dx);
}

void Figure::normalizePoints() {
    sort(points.begin(), points.end(), [&](const Point& p1, const Point& p2) {
        double angle1 {angle(center, p1)};
        double angle2 {angle(center, p2)};
        return angle1 < angle2;
    });
}

void Figure::calculateArea() {
    int n = points.size();
    if (n >= 3) {
        double s = 0;
        for (int i = 0; i < n; ++i) {
            s += (points[i] ^ points[(i + 1) % n]);
        } 
        area = s / 2;
        area = abs(area);
    } else {
        area = 0.0;
    }
}

void Figure::calculateCenter() {
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

Figure::Figure(vector<Point>& _points) {
    points.reserve(_points.size());
    points = _points;
    normalizePoints();
    Validator::validate(points);
    calculateCenter();
    calculateArea();
}

Figure::Figure(const Figure& other) {
    points.reserve(other.points.size());
    points = other.points;
}

Figure::Figure(Figure&& other) {
    points.reserve(other.points.size());
    points = other.points;
    other.points.clear();
}

Figure& Figure::operator=(const Figure& other) {
    if (this == &other) return *this;
    points.reserve(other.points.size());
    points = other.points;
    return *this;
}

Figure& Figure::operator=(Figure&& other) {
    if (this == &other) return *this;
    points.reserve(other.points.size());
    points = other.points;
    other.points.clear();
    return *this;
}

ostream& operator<<(ostream& out, const Figure& f) {
    out << "Points: ";
    for (Point &p: f.getPoints()) {
        out << p << "; ";
    }
    out << "Center: " << f.getCenter() << ";" << endl;
    out << "Area: " << f.getArea() << ";" << endl;
    return out;
}