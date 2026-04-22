#pragma once
#include <memory>
#include <vector>

#include "../20_Task/Task.h"

class Project
{
private:
    std::vector<std::unique_ptr<Task>> tasks;
    
public:
    void addTask(const std::string& name, const std::string& assignee, int priority);
    bool finishTask(const std::string& name);
    int programmerAnalysis(const std::string& name);
    void deleteCompletedTasks();
    void sortTasks();
    void printTasks() const;
};