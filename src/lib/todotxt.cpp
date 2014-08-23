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
 * Append done items to archive.txt file
 * @brief Todotxt::archiveItems
 * @param items
 */
void Todotxt::archiveItems(const std::deque<TodoItem> &items) {
  std::string archiveFile = path_ + ARCHIVE_FILE_W_SEPARATOR;

  std::ofstream file;
  file.open(archiveFile.c_str(), std::ofstream::out);
  if (file.is_open()){
    for (TodoItem item:items){
      file << item.AssembleTodo();
    }
    file.close();
    log("Items archived");
  }else{
    log("Failed to open archive.txt for writing");
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
}

void Todotxt::archiveItem(int index) {
  TodoItem item = todoList_[index];
  std::string archiveFile = path_ + ARCHIVE_FILE_W_SEPARATOR;

  std::ofstream file;
  file.open(archiveFile.c_str(), std::ofstream::out);
  if (file.is_open()){
    file << item.AssembleTodo();
    file.close();
    todoList_.erase(todoList_.begin()+index);
    log("Items archived");
  }else{
    log("Failed to open archive.txt for writing");
  }
}

void Todotxt::archiveItem(TodoItem &item) {
  for (int i = 0; i < todoList_.size(); ++i){
    if (todoList_[i] == item){
      archiveItem(i);
      return;
    }
  }
}
