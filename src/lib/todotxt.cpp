#include <fstream>

#include <iostream>
#include <cstring>
#include "todotxt.h"
#include <todoitem.h>

using namespace Snilius;

void Todotxt::load_file() {

  const char *fileName = strcat(&path[0], TODO_FILE_W_SEPARATOR.c_str());

  std::ifstream todoFile(fileName);
  std::string curline;
  if (todoFile.is_open()) {
    while (getline(todoFile, curline)) {
      TodoItem item(curline);
      todoList.push_back(item);
//      std::cout << curline << '\n';
    }
    todoFile.close();
  } else {
    std::cout << "Couldn't open " << fileName << std::endl;
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
  const char *fileName = strcat(&path[0], TODO_FILE_W_SEPARATOR.c_str());

  std::ofstream todoFile(fileName);
  if (todoFile.is_open()){
    for (int i = todoList.size(); i > 0; --i){
      TodoItem item = todoList.at(i);
      std::string raw = item.AssembleTodo();
      todoFile << raw << std::endl;
    }
    std::cout << "saved"<< std::endl;
    todoFile.close();
  }else {
    std::cout << "failed save to file" << std::endl;
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

void Todotxt::updateItem(int index, TodoItem& item){

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
