#pragma once

#include "Structures.h"
#include <string>

class Student {
protected:
    std::string name;
public:
    Student(const std::string& name);
    virtual Solution solve(const QuadraticEquation& eq) = 0;
    std::string getName() const;
    virtual ~Student();
};

class GoodStudent : public Student {
public:
    GoodStudent(const std::string& name);
    Solution solve(const QuadraticEquation& eq) override;
};

class AverageStudent : public Student {
public:
    AverageStudent(const std::string& name);
    Solution solve(const QuadraticEquation& eq) override;
};

class BadStudent : public Student {
public:
    BadStudent(const std::string& name);
    Solution solve(const QuadraticEquation& eq) override;
};