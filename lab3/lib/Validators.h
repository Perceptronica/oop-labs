#pragma once

#include "Figure.h"
#include <vector>

class Validator {
public:
    static void validate(const vector<Point>& _points);
};

class RectangleValidator : public Validator {
public:
    static void validate(const vector<Point>& _points);
};

class SquareValidator : public Validator {
public:
    static void validate(const vector<Point>& _points);
};

class TrapezoidValidator : public Validator {
public:
    static void validate(const vector<Point>& _points);
};

const double PI {3.14159265}; 

bool PointsCoincide(const vector<Point>& _points) {
    for (int i {1}; i < _points.size(); ++i) {
        if (_points[i] == _points[i - 1]) return true;
    }
    return false;
}

bool isRectangle(const vector<Point>& _points) {
    vector<Segment> s;
    int n = _points.size();
    for (int i {0}; i < n; ++i) {
        s.push_back(Segment(_points[i], 
                              _points[(i + 1) % n]));
    }
    return (s[0] % s[1]) && (s[1] % s[2]) &&
           (s[2] % s[3]) && (s[3] % s[0]);
}

bool isSquare(const vector<Point>& _points) {
    vector<Segment> s;
    int n = _points.size();
    for (int i {0}; i < n; ++i) {
        s.push_back(Segment(_points[i], 
                              _points[(i + 1) % n]));
    } 
    return isRectangle(_points) &&
           s[0].length() == s[1].length() &&
           s[1].length() == s[2].length();
}

int getOrientation(const Point& p1, const Point& p2, const Point& p3) {
    double orientation = (p2.getY() - p1.getY()) * 
                         (p3.getX() - p2.getX()) - 
                         (p3.getY() - p2.getY()) * 
                         (p2.getX() - p1.getX());
    
    if (orientation > 0) {
        return 1; // Против часовой стрелки
    } else if (orientation < 0) {
        return -1; // По часовой стрелке
    } else {
        return 0; // Вырожденный случай
    }
}

bool isConvex(const vector<Point>& _points) {
    if (_points.size() < 3) {
        return false;
    }

    int numPoints = _points.size();
    int orientation = 0; // Ориентация фигуры: 0 - не определена, 1 - против часовой стрелки, -1 - по часовой стрелке

    for (int i = 0; i < numPoints; i++) {
        int currentOrientation = getOrientation(_points[i], _points[(i + 1) % numPoints], _points[(i + 2) % numPoints]);
        if (currentOrientation == 0) {
            continue; // Пропускаем вырожденные случаи
        }
        if (orientation == 0) {
            orientation = currentOrientation;
        }
        if (orientation != currentOrientation) {
            return false;
        }
    }
    return true;
}

void Validator::validate(const vector<Point>& _points) {
    if (!(isConvex(_points))) {
        throw logic_error("The figure is not convex!");
    } else if (_points.size() != 4) {
        throw logic_error("Task requires a four-point figure!");
    } else if (PointsCoincide(_points)) {
        throw logic_error("Points coincide => not a 4-point figure!");
    }
}

void RectangleValidator::validate(const vector<Point>& _points) {
    if(!(isRectangle(_points))) {
        throw logic_error("The figure is convex but not a rectangle.");
    }
}

void SquareValidator::validate(const vector<Point>& _points) {
    if (!(isRectangle(_points))) {
        throw logic_error("The figure is convex but \
                           not a rectangle/square.");
    } else {
        if (!isSquare(_points)) {
            throw logic_error("THe figure is a rectangle, not a square.");
        }
    }
}

void TrapezoidValidator::validate(const vector<Point>& _points) {
    // противолежащие углы не равны:
    Segment s1(_points[0], _points[1]);
    Segment s2(_points[1], _points[2]);
    Segment s3(_points[2], _points[3]);
    Segment s4(_points[3], _points[0]);
    double angle1 = acos((s1 * s2)/(s1.length() * s2.length()) * 180 / PI);
    double angle2 = acos((s3 * s4)/(s3.length() * s4.length()) * 180 / PI);
    if (abs(angle1 - angle2) < EPS) {
        throw logic_error("The figure is either a rombus, or\
        parallelogram");
    }
}