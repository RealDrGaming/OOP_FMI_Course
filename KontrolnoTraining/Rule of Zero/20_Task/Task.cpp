#include "Task.h"

#include <iostream>
#include <ostream>

Task::Task(const std::string& name, const std::string& asignee, int priority)
    : name(name), assignee(asignee), priority(priority), isFinished(false) { }

std::string Task::getName()
{
    return name;
}

std::string Task::getAssignee()
{
    return assignee;
}

int Task::getPriority()
{
    return priority;
}

bool Task::isTaskFinished()
{
    return isFinished;
}

void Task::completeTask()
{
    isFinished = true;
}

void Task::print() const
{
    std::cout << (isFinished ? "[DONE] " : "[TODO] ") << name << 
        " - Assigned to: " << assignee << "(Priority: " << priority << ")" << std::endl;
}