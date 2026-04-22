#pragma once
#include <string>

class Task
{
private:
    std::string name;
    std::string assignee;
    int priority;
    bool isFinished;
    
public:
    Task(const std::string& name, const std::string& asignee, int priority);
    
    std::string getName();
    std::string getAssignee();
    int getPriority();
    bool isTaskFinished();
    
    void completeTask();
    void print() const;
};
