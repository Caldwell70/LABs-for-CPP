#include "Student.h"
#include <cmath>
#include <cstdlib>

Student::Student(const std::string& name) : name(name) {}

std::string Student::getName() const {
    return name;
}

Student::~Student() {}

GoodStudent::GoodStudent(const std::string& name) : Student(name) {}

Solution GoodStudent::solve(const QuadraticEquation& eq) {
    Solution s{};
    double D = eq.b * eq.b - 4 * eq.a * eq.c;

    if (D > 0) {
        s.rootsCount = 2;
        s.x1 = (-eq.b + std::sqrt(D)) / (2 * eq.a);
        s.x2 = (-eq.b - std::sqrt(D)) / (2 * eq.a);
    }
    else if (D == 0) {
        s.rootsCount = 1;
        s.x1 = -eq.b / (2 * eq.a);
    }
    else {
        s.rootsCount = 0;
    }

    return s;
}

AverageStudent::AverageStudent(const std::string& name) : Student(name) {}

Solution AverageStudent::solve(const QuadraticEquation& eq) {
    if (std::rand() % 100 < 70) {
        GoodStudent helper(name);
        return helper.solve(eq);
    }
    else {
        Solution s{};
        s.rootsCount = 1;
        s.x1 = std::rand() % 10;
        return s;
    }
}

BadStudent::BadStudent(const std::string& name) : Student(name) {}

Solution BadStudent::solve(const QuadraticEquation&) {
    Solution s{};
    s.rootsCount = 1;
    s.x1 = 0;
    return s;
}