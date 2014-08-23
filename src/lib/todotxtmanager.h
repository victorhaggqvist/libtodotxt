#ifndef TODOTXTMANAGER_H
#define TODOTXTMANAGER_H

#include <deque>
#include <todoitem.h>

namespace Snilius {

class TodotxtManager {
  public:
    virtual ~TodotxtManager() {}
    virtual std::deque<TodoItem> getTodoList() = 0;
    virtual void updateItem(int index, TodoItem& item) = 0;
    virtual void newItem(TodoItem& item) = 0;
    virtual void removeItem(int index) = 0;
    virtual void removeItem(TodoItem& item) = 0;
    virtual void archiveDoneItems() = 0;
    virtual void archiveItem(int index) = 0;
    virtual void archiveItem(TodoItem& item) = 0;
    virtual void setEnableLogging(bool enableLogging) = 0;
};

}

#endif // TODOTXTMANAGER_H
