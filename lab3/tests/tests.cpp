#include <gtest/gtest.h>
#include "../lib/Figure.h"
#include "../lib/Rectangle.h"
#include "../lib/Square.h"
#include "../lib/Trapezoid.h"
#include "../lib/Validators.h"

vector <Point> r1 = {Point(0, 0), Point(1, 0), Point(1, 5), Point(0, 5)};
vector <Point> sq1 = {Point(0, 0), Point(1, 1), Point(1, 0), Point(0, 1)};
vector <Point> sq2 = {Point(0, -2), Point(0, 2), Point(2, 0), Point(-2, 0)};
vector <Point> tp1 = {Point(-1, 3), Point(3, 3), Point(-3, 1), Point(4, 1)};


vector<Point> vnc1 = {Point(2, 3), Point(1, -1), Point(2, -2), Point(-2, -2)};
vector<Point> vnc2 = {Point(0, -100)};
vector<Point> vnc3 = {Point(0, 1), Point(1, 1)};
vector<Point> vnc4 = {Point(0, 0), Point(0, 1), Point(1, 1), Point(-1, 2)};

// обработка исключений для фигуры в общем
class FigureExceptionHandling : public testing::TestWithParam<Figure> {};
class FigureConvexityCheck : public FigureExceptionHandling {};
class FigureNonConvexityCheck : public testing::TestWithParam<vector<Point>> {};

// выпуклость фигуры в общем:
TEST_P(FigureConvexityCheck, Convexity) {
    Figure f {GetParam()};
    bool convexity = isConvex(f.getPoints());
    ASSERT_TRUE(convexity);
}

INSTANTIATE_TEST_CASE_P(
    Convexity,
    FigureConvexityCheck,
    testing::Values(Figure(r1), Figure(sq1), Figure(sq2), Figure(tp1))
);

TEST_P(FigureNonConvexityCheck, NonConvexity) {
    vector <Point> v{GetParam()};
    ASSERT_THROW(Validator::validate(v), std::logic_error);
}

INSTANTIATE_TEST_CASE_P(
    NonConvexity,
    FigureNonConvexityCheck,
    testing::Values(vnc1, vnc2, vnc3, vnc4)
);

TEST(Area, RectangleArea) {
    Figure f(r1);
    Rectangle r(r1);
    double f_area = f.getArea();
    double r_area = r.getArea();
    EXPECT_EQ(f_area, r_area);
}

TEST(Area, SquareArea) {
    Figure f(sq1);
    Square s(sq1);
    double f_area = f.getArea();
    double s_area = s.getArea();
    EXPECT_EQ(f_area, s_area);
}

TEST(Area, TrapezoidArea) {
    Figure f(tp1);
    Trapezoid tp(tp1);
    double f_area = f.getArea();
    double tp_area = tp.getArea();
    EXPECT_EQ(f_area, tp_area);
}