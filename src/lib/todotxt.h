#ifndef TODOTXT_H
#define TODOTXT_H

#include <string>
#include <deque>
#include "todotxtmanager.h"
#include "todoitem.h"

namespace Snilius {

class Todotxt : public TodotxtManager{
//class Todotxt {
  public:
    Todotxt(std::string path);
    ~Todotxt(){}
    const std::string TODO_FILE = "todo.txt";
    const std::string TODO_FILE_W_SEPARATOR = "/" + TODO_FILE;
    const std::string ARCHIVE_FILE = "archive.txt";
    const std::string ARCHIVE_FILE_W_SEPARATOR = "/" + ARCHIVE_FILE;
    std::deque<TodoItem> getTodoList();
    void updateItem(int index, TodoItem& item);
    void newItem(TodoItem& item);
    void removeItem(int index);
    void removeItem(TodoItem& item);
    void archiveDoneItems();
    void archiveItem(int index);
    void archiveItem(TodoItem& item);
    void setEnableLogging(bool enableLogging);

  private:
    std::deque<TodoItem> todoList_;
    std::string path_;
    bool enableLogging_ = false;
    void loadFile();
    void saveToFile();
    void log(const std::string msg);
    void findDoneItems(std::deque<TodoItem> *doneItems, std::deque<TodoItem> *leftItems);
    void archiveItems(const std::deque<TodoItem> &items);
};

}

#endif // TODOTXT_H
