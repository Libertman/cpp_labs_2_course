#pragma once
#ifndef TEACHER_H
#define TEACHER_H

#include <string>
#include <queue>
#include <map>
#include "Equation.h"

struct Email
{
    Equation eq;
    Solution studentSolution;
    std::string studentName;
};

class Teacher
{
private:
    std::queue<Email> mailbox;
    std::map<std::string, int> grade_table;

public:
    void receive_email(const Email& email);
    void check_all_emails();
    void publish_grades() const;
};

#endif
