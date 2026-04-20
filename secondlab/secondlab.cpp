#include <iostream>
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>

#include "Student.h"
#include "Teacher.h"

int main() {
    setlocale(LC_ALL, "Russian");
    std::srand(std::time(nullptr));

    std::vector<std::unique_ptr<Student>> students;
    students.push_back(std::make_unique<GoodStudent>("Алиса"));
    students.push_back(std::make_unique<GoodStudent>("Роман"));
    students.push_back(std::make_unique<AverageStudent>("Павел"));
    students.push_back(std::make_unique<AverageStudent>("Александр"));
    students.push_back(std::make_unique<AverageStudent>("Евгения"));
    students.push_back(std::make_unique<BadStudent>("Фёдор"));
    students.push_back(std::make_unique<BadStudent>("Олеся"));

    Teacher teacher;

    for (const auto& st : students) {
        teacher.registerStudent(st->getName());
    }

    std::vector<QuadraticEquation> tasks = {
        {3, 6, 3}, {1, -1, -6}, {2, 4, 2}, {1, 5, 6}, {1, -4, 4}
    };

    for (const auto& eq : tasks) {
        for (const auto& st : students) {
            Submission sub;
            sub.eq = eq;
            sub.sol = st->solve(eq);
            sub.studentName = st->getName();

            teacher.receive(sub);
        }
    }

    teacher.checkAll();
    teacher.printResults();

    return 0;
}