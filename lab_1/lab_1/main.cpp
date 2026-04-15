#include <iostream>
#include <fstream>
#include <vector>
#include "Student.h"
#include "Teacher.h"


std::vector<Equation> load_equations(const std::string& filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        throw std::runtime_error("couldnt open the file: " + filename);
    }

    std::vector<Equation> eqs;
    double a, b, c;
    while (file >> a >> b >> c)
    {
        eqs.push_back({ a, b, c });
    }
    return eqs;
}

int main()
{
    Teacher teacher;

    std::vector<Student> students = {
        {"Sam Altman (Good student)", StudentType::GOOD},
        {"Ilon Musk (Average student)", StudentType::AVERAGE},
        {"Cristiano Ronaldo (Bad student)", StudentType::BAD},
        {"Homelander (Average Student)", StudentType::AVERAGE},
        {"Lenya Voronin (Good student)", StudentType::GOOD}
    };

    std::vector<Equation> equations;

    try
    {
        equations = load_equations("data/equations.txt");
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cout << "Using default:\n1) x^2 - 3x + 2 = 0\n2) x^2 + 2x + 1 = 0\n3) x^2 - 4x = 0\n4) x^2 - 4x + 2 = 0\n";
        equations.push_back({ 1, -3, 2 });
        equations.push_back({ 1, 2, 1 });
        equations.push_back({ 1, 0, -4 });
        equations.push_back({ 2, -4, 2 });
    }

    for (const auto& student : students)
    {
        for (const auto& eq : equations)
        {
            teacher.receive_email({ eq, student.solve(eq), student.name });
        }
    }

    teacher.check_all_emails();
    teacher.publish_grades();

    return 0;
}
