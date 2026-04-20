#pragma once

#include <string>

struct QuadraticEquation {
    double a, b, c;
};

struct Solution {
    int rootsCount;
    double x1, x2;
};

struct Submission {
    QuadraticEquation eq;
    Solution sol;
    std::string studentName;
};
