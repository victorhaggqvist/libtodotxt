#include "todotxt.h"
#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;

void Todotxt::load_file() {

  const char *file_name = strcat(&path[0], "todo.txt");

  ifstream todo_file(file_name);
  string curline;
  if (todo_file.is_open()) {
    while (getline(todo_file, curline)) {
      TodoItem item(curline);
      list.push_back(item);
//      std::cout << curline << '\n';
    }
    todo_file.close();
  } else {
    cout << "Couldn't open " << file_name << endl;
  }
}

Todotxt::Todotxt(string path) { this->path = path; }
