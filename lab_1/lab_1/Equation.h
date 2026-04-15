#pragma once
#ifndef EQUATION_H
#define EQUATION_H

struct Solution
{
    int numRoots;
    double x1, x2;

    bool equals(const Solution& other) const;
};

struct Equation
{
    double a, b, c;

    Solution get_correct_solution() const;
};

#endif
