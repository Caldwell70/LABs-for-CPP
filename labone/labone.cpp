#include <iostream>
#include <string>
#include <cmath>
#include <ctime>

class QuadraticEquation {
private:
    double a, b, c;

public:
    QuadraticEquation(double a = 1, double b = 0, double c = 0) {
        this->a = a;
        this->b = b;
        this->c = c;
    }

    void solve(double& x1, double& x2) const {
        double D = b * b - 4 * a * c;

        if (D < 0) {
            x1 = x2 = NAN;
        }
        else if (D == 0) {
            x1 = x2 = -b / (2 * a);
        }
        else {
            x1 = (-b + std::sqrt(D)) / (2 * a);
            x2 = (-b - std::sqrt(D)) / (2 * a);
        }
    }
};

struct Solution {
    double x1;
    double x2;
};

struct Submission {
    std::string name;
    QuadraticEquation eq;
    Solution sol;

    Submission() : name(""), eq(), sol() {}
};

class Student {
protected:
    std::string name;

public:
    Student(std::string n) { name = n; }
    virtual ~Student() {}

    std::string getName() { return name; }

    virtual Solution solve(const QuadraticEquation& eq) = 0;
};

class GoodStudent : public Student {
public:
    GoodStudent(std::string n) : Student(n) {}

    Solution solve(const QuadraticEquation& eq) {
        Solution s;
        eq.solve(s.x1, s.x2);
        return s;
    }
};

class AverageStudent : public Student {
public:
    AverageStudent(std::string n) : Student(n) {}

    Solution solve(const QuadraticEquation& eq) {
        Solution s;

        if (std::rand() % 2 == 0) {
            eq.solve(s.x1, s.x2);
        }
        else {
            s.x1 = std::rand() % 10;
            s.x2 = std::rand() % 10;
        }

        return s;
    }
};

class BadStudent : public Student {
public:
    BadStudent(std::string n) : Student(n) {}

    Solution solve(const QuadraticEquation& eq) {
        Solution s;
        s.x1 = 0;
        s.x2 = 0;
        return s;
    }
};

class SubmissionQueue {
private:
    Submission arr[100];
    int front, rear;

public:
    SubmissionQueue() {
        front = 0;
        rear = 0;
    }

    void push(Submission s) {
        arr[rear++] = s;
    }

    bool empty() {
        return front == rear;
    }

    Submission pop() {
        return arr[front++];
    }
};

class Teacher {
private:
    SubmissionQueue queue;

    std::string names[100];
    int scores[100];
    int count;

    bool check(const Submission& s) {
        double x1, x2;
        s.eq.solve(x1, x2);

        double eps = 1e-6;

        return (std::fabs(x1 - s.sol.x1) < eps && std::fabs(x2 - s.sol.x2) < eps) || (std::fabs(x1 - s.sol.x2) < eps && std::fabs(x2 - s.sol.x1) < eps);
    }

    int findStudent(std::string name) {
        for (int i = 0; i < count; i++) {
            if (names[i] == name)
                return i;
        }
        return -1;
    }

public:
    Teacher() {
        count = 0;
        for (int i = 0; i < 100; i++) {
            scores[i] = 0;
        }
    }

    void receive(Submission s) {
        queue.push(s);
    }

    void checkAll() {
        while (!queue.empty()) {
            Submission s = queue.pop();

            int idx = findStudent(s.name);

            if (idx == -1) {
                names[count] = s.name;
                scores[count] = 0;
                idx = count;
                count++;
            }

            if (check(s)) {
                scores[idx]++;
            }
        }
    }

    void printResults() {
        std::cout << "\n Таблица успеваемости \n";
        for (int i = 0; i < count; i++) {
            std::cout << names[i] << ": " << scores[i] << std::endl;
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    std::srand(std::time(0));

    QuadraticEquation eqs[10] = {
        QuadraticEquation(1, -3, 2),
        QuadraticEquation(1, 2, 1),
        QuadraticEquation(1, -5, 6),
        QuadraticEquation(2, -4, 2),
        QuadraticEquation(1, 0, -4),
        QuadraticEquation(3, -6, 3),
        QuadraticEquation(1, -1, -6),
        QuadraticEquation(2, 5, -3),
        QuadraticEquation(1, -7, 10),
        QuadraticEquation(1, 4, 4)
    };

    Student* students[6];
    students[0] = new GoodStudent("Иван");
    students[1] = new GoodStudent("София");
    students[2] = new AverageStudent("Петр");
    students[3] = new AverageStudent("Вера");
    students[4] = new BadStudent("Лев");
    students[5] = new BadStudent("Павел");

    Teacher teacher;

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 6; j++) {
            Submission s;
            s.name = students[j]->getName();
            s.eq = eqs[i];
            s.sol = students[j]->solve(eqs[i]);

            teacher.receive(s);
        }
    }

    teacher.checkAll();
    teacher.printResults();

    for (int i = 0; i < 6; i++) {
        delete students[i];
    }

    return 0;
}