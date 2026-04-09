#include "Student.h"
#include <cmath>
#include <random>


bool Solution::equals(const Solution& other) const
{
    if (numRoots != other.numRoots) return false;
    if (numRoots == 0) return true;
    if (numRoots == 1) return std::abs(x1 - other.x1) < 1e-6;
    return (std::abs(x1 - other.x1) < 1e-6 && std::abs(x2 - other.x2) < 1e-6) || (std::abs(x1 - other.x2) < 1e-6 && std::abs(x2 - other.x1) < 1e-6);
}

Solution Equation::get_correct_solution() const
{
    if (std::abs(a) < 1e-9)
    {
        if (std::abs(b) < 1e-9) return { 0, 0, 0 };
        return { 1, -c / b, 0 };
    }
    double disc = b * b - 4 * a * c;
    if (disc < 0) return { 0, 0, 0 };
    if (std::abs(disc) < 1e-9) return { 1, -b / (2 * a), 0 };
    return { 2, (-b + std::sqrt(disc)) / (2 * a), (-b - std::sqrt(disc)) / (2 * a) };
}

Solution Student::solve(const Equation& eq) const
{
    if (type == StudentType::GOOD) return eq.get_correct_solution();
    if (type == StudentType::BAD) return { 1, 0, 0 };

    static std::random_device dev;
    static std::mt19937 rng(dev());
    std::uniform_int_distribution<int> dist(0, 1);

    if (std::rand() % 2 == 0) return eq.get_correct_solution();
    return { 0, 999, 999 };
}
