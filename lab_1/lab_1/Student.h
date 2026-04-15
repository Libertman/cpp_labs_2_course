#pragma once
#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include "Equation.h"

enum class StudentType { GOOD, AVERAGE, BAD };

struct Student
{
    std::string name;
    StudentType type;

    Solution solve(const Equation& eq) const;
};

#endif
