#ifndef TODOTXT_H
#define TODOTXT_H

#include <string>
#include <vector>
#include "todotxtmanager.h"
#include "todoitem.h"

namespace Snilius {

//class Todotxt : public TodotxtManager{
class Todotxt {
  public:
//    typedef std::vector<TodoItem> todoList;
    Todotxt(std::string path);
    ~Todotxt(){}
    std::vector<TodoItem> getTodoList();
    void updateItem(int index, TodoItem* item);
    void newItem(TodoItem& item);
    void removeItem(int index);
    void removeItem(TodoItem& item);
    void archiveItem(int index);
    void archiveItem(TodoItem& item);

  private:
    const std::string TODO_FILE = "todo.txt";
    const std::string TODO_FILE_W_SEPARATOR = "/todo.txt";
    std::vector<TodoItem> todoList;
    std::string path;
    void load_file();
    bool fileExists(std::string& file);
    void saveToFile();
};

}

#endif // TODOTXT_H
