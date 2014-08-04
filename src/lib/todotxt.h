#ifndef TODOTXT_H
#define TODOTXT_H

#include <string>
#include <vector>
#include "todoitem.h"

using namespace std;

class Todotxt {
  private:
    typedef vector<TodoItem> TodoList;
    TodoList list;
    string path;
    void load_file();

  public:
    Todotxt(string path);
    TodoList getTodoList();
};

#endif // TODOTXT_H
