#ifndef TODOTXTMANAGER_H
#define TODOTXTMANAGER_H

#include <vector>
#include <todoitem.h>

namespace Snilius {

class TodotxtManager {
  public:
    virtual ~TodotxtManager() {}
    virtual std::vector<TodoItem> getTodoList() = 0;
    virtual void updateItem(int index, TodoItem& item) = 0;
    virtual void newItem(TodoItem& item) = 0;
    virtual void removeItem(int index) = 0;
    virtual void removeItem(TodoItem& item) = 0;
    virtual void archiveItem(int index) = 0;
    virtual void archiveItem(TodoItem& item) = 0;
};

}

#endif // TODOTXTMANAGER_H
