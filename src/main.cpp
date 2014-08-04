#include <iostream>
#include <string>
#include "todotxt.h"
#include "todoitem.h"

using namespace std;

int main() {
  string BASE_PATH = "/home/victor/QtCreator/tdtxt/";

  Todotxt tdt(BASE_PATH);

  string line = "x (A) is done @ss @YOLO @phones lslsls @at";
  cout << line <<endl;

  TodoItem item(line);
  cout << item.IsDone()<<endl;
  item.GetContexts();

  return 0;
}
