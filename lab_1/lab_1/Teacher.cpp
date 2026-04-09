#include "Teacher.h"
#include <iostream>

void Teacher::receive_email(const Email& email)
{
    mailbox.push(email);
}

void Teacher::check_all_emails()
{
    while (!mailbox.empty())
    {
        const Email& mail = mailbox.front();

        Solution correct = mail.eq.get_correct_solution();
        if (mail.studentSolution.equals(correct))
        {
            grade_table[mail.studentName]++;
        }
        else if (grade_table.find(mail.studentName) == grade_table.end())
        {
            grade_table[mail.studentName] = 0;
        }

        mailbox.pop();
    }
}

void Teacher::publish_grades() const
{
    std::cout << "--- Progress table ---\n";
    for (const auto& entry : grade_table)
    {
        std::cout << "Student: " << entry.first << " | Solved tasks: " << entry.second << "\n";
    }
}
