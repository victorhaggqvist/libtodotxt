#include <iostream>
#include <string>
#include "todotxt.h"
#include "todoitem.h"
#include <todotxtmanager.h>

using namespace std;
using namespace Snilius;

int main() {
  system("bash -c 'echo a_item > ./todo.txt'");
  Todotxt *todo = new Todotxt(".");
  vector<TodoItem> list = todo->getTodoList();

  int getIndex = 0;
  TodoItem item = list[getIndex];
  item.SetDone(true);
  todo->updateItem(0, item);
  vector<TodoItem> olist = todo->getTodoList();

  TodoItem kl = TodoItem::init("x wodo");
  todo->newItem(kl);
  TodoItem kdl = TodoItem::init("muuuu");
  todo->newItem(kdl);
  TodoItem kdld = TodoItem::init("muuuu");
  todo->newItem(kdld);
  todo->removeItem(1);
  vector<TodoItem> olistd = todo->getTodoList();
  cout<<  "";
//  item.NotifyChange();

//  TodoItem qw = list.at(0);
//  cout << qw.IsDone() << endl;



//  std::string BASE_PATH = ".";

//  TodotxtManager *todotxt = new Todotxt(BASE_PATH);
//  std::vector<TodoItem> myList = todotxt->getTodoList();
//  std::cout <<"made it"<<std::endl;
//  TodoItem item = myList.at(0);
//  std::cout << item.GetTodo()<<std::endl;

//  TodoItem tim = myList.at(1);
//  std::cout <<tim.IsDone() << " "<< tim.GetTodo() << std::endl;


//  TodoItem ny("yolo");
//  todotxt->newItem(ny);
//  delete todotxt;

//  Snilius::Todotxt tdt(BASE_PATH);

//  string line = "x (A) is done @ss @YOLO @phones lslsls @at";
//  cout << line <<endl;

//  Snilius::TodoItem item(line);
//  cout << item.IsDone()<<endl;
//  item.GetContexts();

  return 0;
}
