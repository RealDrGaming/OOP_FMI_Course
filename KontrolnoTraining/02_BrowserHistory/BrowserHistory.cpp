#include "BrowserHistory.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>

void BrowserHistory::freeMemory()
{
    PageNode* current = this->head;
    
    while (current != nullptr)
    {
        PageNode* nextNode = current->next;
        
        delete[] current->url;
        delete current;
        
        current = nextNode;
    }
    this->head = nullptr;
}

void BrowserHistory::copyFrom(const BrowserHistory& other)
{
    this->count = other.count;
    
    // Базов случай: ако другият списък е празен
    if (other.head == nullptr) {
        this->head = nullptr;
        return;
    }

    // 1. Копираме първия елемент (head)
    this->head = new PageNode;
    this->head->url = new char[std::strlen(other.head->url) + 1];
    std::strcpy(this->head->url, other.head->url);
    this->head->next = nullptr;

    // 2. Подготвяме указатели за обхождането
    PageNode* currentOther = other.head->next; // Откъде четем
    PageNode* currentThis = this->head;        // Къде закачаме (опашката на новия списък)

    // 3. Обхождаме и копираме останалите елементи
    while (currentOther != nullptr)
    {
        // Създаваме новия възел и го закачаме за опашката
        currentThis->next = new PageNode;
        currentThis = currentThis->next; // Преместваме опашката напред
        
        // Копираме данните (дълбоко копие на url)
        currentThis->url = new char[std::strlen(currentOther->url) + 1];
        std::strcpy(currentThis->url, currentOther->url);
        currentThis->next = nullptr; // Затваряме списъка

        // Продължаваме напред в оригиналния списък
        currentOther = currentOther->next;
    }
}

void BrowserHistory::moveFrom(BrowserHistory&& other)
{
    this->head = other.head;
    this->count = other.count;
    
    other.head = nullptr;
    other.count = 0;
}

BrowserHistory::~BrowserHistory()
{
    freeMemory();
}

BrowserHistory::BrowserHistory(const BrowserHistory& other)
{
    copyFrom(other);
}

BrowserHistory& BrowserHistory::operator=(const BrowserHistory& other)
{
    if (this != &other)
    {
        freeMemory();
        copyFrom(other);
    }
    return *this;
}

BrowserHistory::BrowserHistory(BrowserHistory&& other) noexcept
{
    moveFrom(std::move(other));
}

BrowserHistory& BrowserHistory::operator=(BrowserHistory&& other) noexcept
{
    if (this != &other)
    {
        freeMemory();
        moveFrom(std::move(other));
    }
    return *this;
}

BrowserHistory::BrowserHistory() : head(nullptr), count(0) { }

void BrowserHistory::visit(const char* url)
{
    PageNode* newNode = new PageNode();
    
    newNode->url = new char[strlen(url) + 1];
    strcpy(newNode->url,url);
    
    newNode->next = this->head;
    this->head = newNode;
    
    this->count++;
}

void BrowserHistory::printHistory() const
{
    PageNode* current = head;
    
    while (current != nullptr)
    {
        std::cout << current->url << std::endl;
        current = current->next;
    }
}