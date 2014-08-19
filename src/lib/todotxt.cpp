#include <fstream>

#include <iostream>
#include <cstring>
#include "todotxt.h"
#include <todoitem.h>

using namespace Snilius;

void Todotxt::load_file() {
  std::string pathToFile = path + TODO_FILE_W_SEPARATOR;

  std::ifstream todoFile(pathToFile.c_str());
  std::string curline;
  if (todoFile.is_open()) {
    while (getline(todoFile, curline)) {
      if (curline.length()<1){
        std::cout<<"empty"<<std::endl;
        return;
      }
      TodoItem item = TodoItem::init(curline);
      todoList.push_back(item);
    }
    todoFile.close();
  } else {
    std::cout << "Could not open " << pathToFile << std::endl;
    std::ofstream newFile;
    newFile.open(pathToFile.c_str(), std::ofstream::out);
    newFile.close();
    std::cout << "A new todo.txt created at "<< pathToFile << std::endl;
  }
}

bool Todotxt::fileExists(std::string& name) {
  if (FILE *file = std::fopen(name.c_str(), "r")) {
      fclose(file);
      return true;
  } else {
      return false;
  }
}

void Todotxt::saveToFile() {
  std::string pathToFile = path + TODO_FILE_W_SEPARATOR;

  std::ofstream todoFile(pathToFile.c_str());
  if (todoFile.is_open()){
    for (int i = 0; i < todoList.size(); ++i){
      TodoItem item = todoList.at(i);
      std::string raw = item.AssembleTodo();
      todoFile << raw << std::endl;
    }
    todoFile.close();
    std::cout << "Saved to file"<< std::endl;
  }else {
    std::cout << "Failed save to file" << std::endl;
  }
}

Todotxt::Todotxt(std::string path) {
  std::string file = path+TODO_FILE_W_SEPARATOR;
//  if (!fileExists(file))
//    throw("No todo.txt exists");
  this->path = path;

  load_file();
}

std::vector<TodoItem> Todotxt::getTodoList(){
  return todoList;
}

void Todotxt::updateItem(int index, TodoItem *item){
//  std::vector<TodoItem>::iterator it = todoList.begin();
//  it += index;
//  TodoItem *toReplace = &(*it);
//  TodoItem tmp(item->AssembleTodo());
//  toReplace = &tmp;
//  const std::string &assLine = item->AssembleTodo();
  todoList[index] = TodoItem::init(item->AssembleTodo());
//  TodoItem* tmp = item;
//  todoList.assign(index, (const TodoItem item));
//  todoList[index] = item;
}

void Todotxt::newItem(TodoItem& item){
  todoList.push_back(item);
  saveToFile();
}

void Todotxt::removeItem(int index)
{

}

void Todotxt::removeItem(TodoItem& item)
{

}

void Todotxt::archiveItem(int index)
{

}

void Todotxt::archiveItem(TodoItem& item)
{

}
