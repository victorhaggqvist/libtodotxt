#include <iostream>
#include <string>
#include "todotxt.h"
#include "todoitem.h"
#include <todotxtmanager.h>

//using namespace std;
using namespace Snilius;

int main() {
  std::string BASE_PATH = ".";

  TodotxtManager *todotxt = new Todotxt(BASE_PATH);
  std::vector<TodoItem> myList = todotxt->getTodoList();
  std::cout <<"made it"<<std::endl;
  TodoItem item = myList.at(0);
  std::cout << item.GetTodo()<<std::endl;

  TodoItem tim = myList.at(1);
  std::cout <<tim.IsDone() << " "<< tim.GetTodo() << std::endl;


  TodoItem ny("yolo");
  todotxt->newItem(ny);
//  delete todotxt;

//  Snilius::Todotxt tdt(BASE_PATH);

//  string line = "x (A) is done @ss @YOLO @phones lslsls @at";
//  cout << line <<endl;

//  Snilius::TodoItem item(line);
//  cout << item.IsDone()<<endl;
//  item.GetContexts();

  return 0;
}
