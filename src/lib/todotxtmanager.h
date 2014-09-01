#ifndef TODOTXTMANAGER_H
#define TODOTXTMANAGER_H

#include <deque>
#include <vector>
#include <string>
#include <todoitem.h>

namespace Snilius {

class TodotxtManager {
  public:
    virtual ~TodotxtManager() {}
    const std::string TODO_FILE = "todo.txt";
    const std::string TODO_FILE_W_SEPARATOR = "/" + TODO_FILE;
    const std::string ARCHIVE_FILE = "archive.txt";
    const std::string ARCHIVE_FILE_W_SEPARATOR = "/" + ARCHIVE_FILE;
    virtual std::deque<TodoItem> getTodoList() = 0;
    virtual void updateItem(int index, TodoItem& item) = 0;
    virtual void newItem(TodoItem& item) = 0;
    virtual void removeItem(int index) = 0;
    virtual void removeItem(TodoItem& item) = 0;
    virtual void archiveDoneItems() = 0;
    virtual void archiveItem(int index) = 0;
    virtual void archiveItem(TodoItem& item) = 0;
    virtual void setEnableLogging(bool enableLogging) = 0;
    virtual std::vector<std::string> getProjects() = 0;
    virtual std::vector<std::string> getContexts() const = 0;
};

}

#endif // TODOTXTMANAGER_H
