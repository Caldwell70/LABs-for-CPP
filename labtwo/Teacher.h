#pragma once

#include "Structures.h"
#include <queue>
#include <map>
#include <string>

class Teacher {
private:
    std::queue<Submission> submissions;
    std::map<std::string, int> results;
    bool checkSolution(const Submission& sub);

public:
    void receive(const Submission& sub);
    void registerStudent(const std::string& name);
    void checkAll();
    void printResults() const;
};