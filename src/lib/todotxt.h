#ifndef TODOTXT_H
#define TODOTXT_H

#include <string>
#include <vector>
#include "todoitem.h"

namespace Snilius {

class Todotxt {
  private:
    typedef std::vector<TodoItem> todoList;
    todoList list;
    std::string path;
    void load_file();

  public:
    Todotxt(std::string path);
    todoList getTodoList();
};

}

#endif // TODOTXT_H
