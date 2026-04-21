#pragma once

class BrowserHistory
{
private:
    struct PageNode
    {
        char* url;
        PageNode* next;
    };
    
    PageNode* head;
    size_t count;
    
    void freeMemory();
    void copyFrom(const BrowserHistory& other);
    void moveFrom(BrowserHistory&& other);
    
public:
    ~BrowserHistory();
    BrowserHistory(const BrowserHistory& other);
    BrowserHistory& operator=(const BrowserHistory& other);
    BrowserHistory(BrowserHistory&& other) noexcept;
    BrowserHistory& operator=(BrowserHistory&& other) noexcept;
    
    BrowserHistory();
    void visit(const char* url);
    void printHistory() const;
};