#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <cmath>
#include <ctime>


struct Solution
{
    int numRoots;
    double x1, x2;

    bool equals(const Solution& other) const
    {
        if (numRoots != other.numRoots) return false;
        if (numRoots == 0) return true;
        if (numRoots == 1) return std::abs(x1 - other.x1) < 1e-6;
        return (std::abs(x1 - other.x1) < 1e-6 && std::abs(x2 - other.x2) < 1e-6) || (std::abs(x1 - other.x2) < 1e-6 && std::abs(x2 - other.x1) < 1e-6);
    }
};

struct Equation {
    double a, b, c;

    Solution get_correct_solution() const
    {
        double disc = b * b - 4 * a * c;
        if (disc < 0) return { 0, 0, 0 };
        if (std::abs(disc) < 1e-9) return { 1, -b / (2 * a), 0 };
        return { 2, (-b + std::sqrt(disc)) / (2 * a), (-b - std::sqrt(disc)) / (2 * a) };
    }
};


enum StudentType { GOOD, AVERAGE, BAD };

struct Student
{
    std::string name;
    StudentType type;

    Solution solve(Equation eq)
    {
        if (type == GOOD) return eq.get_correct_solution();
        if (type == BAD) return { 1, 0, 0 };

        if (std::rand() % 2 == 0) return eq.get_correct_solution(); // рандомно определяем решит или нет
        return { 0, 999, 999 }; // глушилка
    }
};

struct Email {
    Equation eq;
    Solution student_solution;
    std::string student_name;
};

class Teacher
{
private:
    std::queue<Email> mailbox;
    std::map<std::string, int> grade_table;

public:
    void receive_email(const Email& email)
    {
        mailbox.push(email);
    }

    void check_all_emails()
    {
        while (!mailbox.empty())
        {
            Email mail = mailbox.front();
            mailbox.pop();

            Solution correct = mail.eq.get_correct_solution();
            if (mail.student_solution.equals(correct))
            {
                grade_table[mail.student_name]++;
            }
            else if (grade_table.find(mail.student_name) == grade_table.end())
            {
                grade_table[mail.student_name] = 0;
            }
        }
    }

    void publish_grades()
    {
        std::cout << "\n--- Progress table ---\n";
        for (const auto& entry : grade_table)
        {
            std::cout << "Student: " << entry.first << " | Solved tasks: " << entry.second << "\n";
        }
    }
};


std::vector<Equation> load_equations(std::string filename)
{
    std::vector<Equation> eqs;
    std::ifstream file(filename);
    double a, b, c;
    while (file >> a >> b >> c)
    {
        eqs.push_back({ a, b, c });
    }
    return eqs;
}

int main()
{
    std::srand(std::time(0));
    Teacher teacher;

    std::vector<Student> students = {
        {"Sam Altman (Good student)", GOOD},
        {"Ilon Musk (Average student)", AVERAGE},
        {"Cristiano Ronaldo (Bad student)", BAD},
        {"Homelander (Average Student)", AVERAGE},
        {"Lenya Voronin (Good student)", GOOD}
    };

    std::vector<Equation> equations = load_equations("data/equations.txt");
    if (equations.empty())
    {
        std::cout << "equations.txt is not found or is not exist. Using default: x^2 - 3x + 2 = 0\n";
        equations.push_back({ 1, -3, 2 });
    }

    for (auto& student : students)
    {
        for (const auto& eq : equations)
        {
            teacher.receive_email({ eq, student.solve(eq), student.name });
        }
    }

    std::cout << "teacher is checking student's emails..\n";
    teacher.check_all_emails();

    teacher.publish_grades();

    return 0;
}