#include <fstream>
#include <deque>
#include <iostream>
#include <cstring>
#include "todotxt.h"
#include <todoitem.h>

using namespace Snilius;


Todotxt::Todotxt(std::string path) :
  path_(path)
{
  loadFile();
}

const char *Todotxt::todoFile() {
  const std::string foo = "todo.txt";
  return foo.c_str();
}

/**
 * Load todo-items from todo.txt file
 * @brief Todotxt::loadFile
 */
void Todotxt::loadFile() {
  std::string pathToFile = path_ + TODO_FILE_W_SEPARATOR;

  std::ifstream todoFile(pathToFile.c_str());
  std::string curline;
  if (todoFile.is_open()) {
    while (getline(todoFile, curline)) {
      if (curline.length()<1){
        std::cout<<"empty"<<std::endl;
        return;
      }
      TodoItem item = TodoItem::init(curline);
      todoList_.push_back(item);
    }
    todoFile.close();
  } else {
    log("Could not open " + pathToFile);
    std::ofstream newFile;
    newFile.open(pathToFile.c_str(), std::ofstream::out);
    newFile.close();
    log("A new todo.txt created at " + pathToFile);
  }
}

/**
 * Save current list to file
 * @brief Todotxt::saveToFile
 */
void Todotxt::saveToFile() {
  std::string pathToFile = path_ + TODO_FILE_W_SEPARATOR;

  std::ofstream todoFile(pathToFile.c_str());
  if (todoFile.is_open()){
    for (int i = 0; i < todoList_.size(); ++i){
      TodoItem item = todoList_[i];
      std::string raw = item.AssembleTodo();
      todoFile << raw << std::endl;
    }
    todoFile.close();
    log("Saved to file");
  }else {
    log("Failed save to file");
  }
}

void Todotxt::setEnableLogging(bool enableLogging) {
  enableLogging_ = enableLogging;
}

std::vector<std::string> Todotxt::getProjects() {
  std::vector<std::string> projects;
  for (TodoItem item:todoList_){
    if (item.projects_.size()>0)
      for (std::string p:item.projects_)
        projects.push_back(p);
  }

  return projects;
}

std::vector<std::string> Todotxt::getContexts() const {
  std::cout << "wee" << std::endl;
//  contexts_.clear();
//  for (TodoItem item:todoList_) {
//    if (item.contexts_.size()>0)
//      for (std::string c:item.contexts_)
//        contexts_.push_back(c);
//  }
  std::cout << "wee" << std::endl;
  return contexts_;
}

/**
 * Logg stuff
 * @brief Todotxt::log
 * @param msg
 */
void Todotxt::log(const std::string msg){
  if (enableLogging_)
    std::cout << msg << std::endl;
}

/**
 * Separate done items from non-done
 * @brief Todotxt::findDoneItems
 * @param doneItems
 * @param leftItems
 */
void Todotxt::findDoneItems(std::deque<TodoItem> *doneItems, std::deque<TodoItem> *leftItems) {
  for (int i = 0; i < todoList_.size(); ++i){
    TodoItem item = todoList_[i];
    if (item.done_)
      doneItems->push_back(item);
    else
      leftItems->push_back(item);
  }
}

/**
 * Get list of todos
 * @brief Todotxt::getTodoList
 * @return
 */
std::deque<TodoItem> Todotxt::getTodoList(){
  return todoList_;
}
/**
 * Update item at index
 * @brief Todotxt::updateItem
 * @param index
 * @param item
 */
void Todotxt::updateItem(int index, TodoItem &item){

  // this is to redecode all members incase somthing in the todo_ was changed
  TodoItem updatedItem = TodoItem::init(item.AssembleTodo());

  todoList_[index] = updatedItem;
  log("Item updated");
  saveToFile();
}

/**
 * Add a new item to the list
 * @brief Todotxt::newItem
 * @param item
 */
void Todotxt::newItem(TodoItem& item){
  todoList_.push_back(item);
  saveToFile();
}

/**
* Remove an item, NOT to be confused with ticking an item of as done
* This will remove the item from the list
* @brief Todotxt::removeItem
* @param index
*/
void Todotxt::removeItem(int index){
  todoList_.erase(todoList_.begin()+index);
  saveToFile();
  log("Item removed");
}

void Todotxt::removeItem(TodoItem& item) {
  for (int i = 0; i < todoList_.size(); ++i){
    if (todoList_[i] == item){
      removeItem(i);
      return;
    }
  }
}

/**
 * Mova done items to a archive.txt file
 * @brief Todotxt::archiveDoneItems
 */
void Todotxt::archiveDoneItems() {
  std::deque<TodoItem> done;
  std::deque<TodoItem> left;
  findDoneItems(&done, &left);
  todoList_ = left;
  archiveItems(done);
  saveToFile();
}

void Todotxt::archiveItem(int index) {
  TodoItem item = todoList_[index];
  std::string archiveFile = path_ + ARCHIVE_FILE_W_SEPARATOR;

  std::ofstream file;
  file.open(archiveFile, std::ofstream::app);
  if (file.is_open()){
    file << item.AssembleTodo() << std ::endl;
    file.close();
    todoList_.erase(todoList_.begin()+index);
    log("Items archived");
  }else{
    log("Failed to open archive.txt for writing");
  }
  saveToFile();
}

/**
 * Append done items to archive.txt file
 * @brief Todotxt::archiveItems
 * @param items
 */
void Todotxt::archiveItems(const std::deque<TodoItem> &items) {
  std::string archiveFile = path_ + ARCHIVE_FILE_W_SEPARATOR;

  std::ofstream file;
  file.open(archiveFile, std::ofstream::app);
  if (file.is_open()){
    for (TodoItem item:items){
      file << item.AssembleTodo() << std ::endl;
    }
    file.close();
    log("Items archived");
  }else{
    log("Failed to open archive.txt for writing");
  }
}

char Todotxt::dirSeparator() {
  #ifdef _WIN32
    return '\\';
  #else
    return '/';
  #endif
}

void Todotxt::archiveItem(TodoItem &item) {
  for (int i = 0; i < todoList_.size(); ++i){
    if (todoList_[i] == item){
      archiveItem(i);
      return;
    }
  }
}
