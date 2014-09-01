#ifndef TODOTXT_H
#define TODOTXT_H

#include <string>
#include <deque>
#include <vector>
#include "todotxtmanager.h"
#include "todoitem.h"

namespace Snilius {

class Todotxt : public TodotxtManager{
//class Todotxt {
  public:
    Todotxt(std::string path);
    ~Todotxt(){}
    static const char* todoFile();
//    const std::string& TodoFileWSeparator();
    const std::string TODO_FILE = "todo.txt";
    const std::string TODO_FILE_W_SEPARATOR = Todotxt::dirSeparator() + TODO_FILE;
    const std::string ARCHIVE_FILE = "archive.txt";
    const std::string ARCHIVE_FILE_W_SEPARATOR = dirSeparator() + ARCHIVE_FILE;
    std::deque<TodoItem> getTodoList();
    void updateItem(int index, TodoItem& item);
    void newItem(TodoItem& item);
    void removeItem(int index);
    void removeItem(TodoItem& item);
    void archiveDoneItems();
    void archiveItem(int index);
    void archiveItem(TodoItem& item);
    void setEnableLogging(bool enableLogging);
    std::vector<std::string> getProjects();
    std::vector<std::string> getContexts() const;

  private:
    std::deque<TodoItem> todoList_;
    std::vector<std::string> contexts_;
    std::string path_;
    bool enableLogging_ = false;
    void loadFile();
    void saveToFile();
    void log(const std::string msg);
    void findDoneItems(std::deque<TodoItem> *doneItems, std::deque<TodoItem> *leftItems);
    void archiveItems(const std::deque<TodoItem> &items);
    static char dirSeparator();
};

}

#endif // TODOTXT_H
