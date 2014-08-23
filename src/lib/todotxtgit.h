#ifndef TODOTXTGIT_H
#define TODOTXTGIT_H

#include <memory>
#include "todotxtmanager.h"
#include "todotxt.h"
#include "todoitem.h"
#include "git2.h"
//#include "git2/repository.h"
//#include "git2/errors.h"
//#include "git2/signature.h"

namespace Snilius {

class Todotxtgit : public TodotxtManager {
  public:
    Todotxtgit(std::string path);
    ~Todotxtgit(){}
    const std::string TODO_FILE = "todo.txt";
    const std::string TODO_FILE_W_SEPARATOR = "/" + TODO_FILE;
    const std::string ARCHIVE_FILE = "archive.txt";
    const std::string ARCHIVE_FILE_W_SEPARATOR = "/" + ARCHIVE_FILE;
    std::deque<TodoItem> getTodoList();
    void updateItem(int index, TodoItem& item);
    void newItem(TodoItem &item);
    void removeItem(int index);
    void removeItem(TodoItem& item);
    void archiveDoneItems();
    void archiveItem(int index);
    void archiveItem(TodoItem& item);
    void setEnableLogging(bool enableLogging);

  private:
    const std::string path_;
    std::shared_ptr<Todotxt> todotxt_;
    git_repository *repo_ = NULL;
    bool enableLogging_ = false;
    void log(std::string msg);
    void commitTodoFile(TodoItem &item, std::string commitKeyword);
};

}
#endif // TODOTXTGIT_H
