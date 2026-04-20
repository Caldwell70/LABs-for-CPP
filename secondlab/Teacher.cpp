#include "Teacher.h"
#include "Student.h"
#include <cmath>
#include <iostream>

void Teacher::receive(const Submission& sub) {
    submissions.push(sub);
}

void Teacher::registerStudent(const std::string& name) {
    results[name] = 0;
}

bool Teacher::checkSolution(const Submission& sub) {
    GoodStudent checker("checker");
    Solution correct = checker.solve(sub.eq);

    if (correct.rootsCount != sub.sol.rootsCount)
        return false;

    if (correct.rootsCount == 0)
        return true;

    if (correct.rootsCount == 1)
        return std::abs(correct.x1 - sub.sol.x1) < 1e-6;

    return (std::abs(correct.x1 - sub.sol.x1) < 1e-6 && std::abs(correct.x2 - sub.sol.x2) < 1e-6);
}

void Teacher::checkAll() {
    while (!submissions.empty()) {
        Submission sub = submissions.front();
        submissions.pop();
        if (checkSolution(sub)) {
            results[sub.studentName]++;
        }
    }
}

void Teacher::printResults() const {
    std::cout << "“аблица успеваемости:\n";
    for (const auto& pair : results) {
        std::cout << pair.first << ": " << pair.second << " правильных задач\n";
    }
}