#include "Project.h"

#include <algorithm>

void Project::addTask(const std::string& name, const std::string& assignee, int priority)
{
    tasks.emplace_back(std::move(std::make_unique<Task>(name, assignee, priority)));
}

bool Project::finishTask(const std::string& name)
{
    auto it = std::find_if(tasks.begin(), tasks.end(), 
        [&name](const std::unique_ptr<Task>& task) { return task->getName() == name; });

    if (it != tasks.end())
    {
        (*it)->completeTask();
        return true;
    }
    return false;
}

int Project::programmerAnalysis(const std::string& name)
{
    auto it = std::count_if(tasks.begin(), tasks.end(), 
        [&name](const std::unique_ptr<Task>& task) { return task->getAssignee() == name && !task->isTaskFinished(); });

    return it;
}

void Project::deleteCompletedTasks()
{
    tasks.erase
    (
        std::remove_if(tasks.begin(), tasks.end(), [](const std::unique_ptr<Task>& task)
        {
            return task->isTaskFinished();
        }), 
        tasks.end()
    );
}

void Project::sortTasks()
{
    std::sort(tasks.begin(), tasks.end(), 
        [](const std::unique_ptr<Task>& task1, const std::unique_ptr<Task>& task2)
        {
            if (task1->getPriority() == task2->getPriority())
            {
                return task1->getName() < task2->getName();
            }
            
            return task1->getPriority() < task2->getPriority();
        });
}

void Project::printTasks() const
{
    for (const auto& task : tasks)
    {
        task->print();
    }
}