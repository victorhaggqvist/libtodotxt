#include <iostream>
#include <string>
#include <memory>
#include "todotxt.h"
#include "todoitem.h"
#include <todotxtmanager.h>
#include <deque>
#include "todotxtgit.h"

using namespace std;
using namespace Snilius;

int main() {
  system("bash -c 'echo a_item > ./todo.txt'");
  system("bash -c 'echo a_item2 >> ./todo.txt'");
  system("bash -c 'echo a_item3 >> ./todo.txt'");
  system("bash -c 'echo a_item4 >> ./todo.txt'");
  std::shared_ptr<Todotxtgit>todo(new Todotxtgit("."));
  todo->setEnableLogging(true);
  std::deque<TodoItem> list = todo->getTodoList();
  TodoItem item =  list[2];
  item.SetPriority("A");
  todo->updateItem(2, item);
  item.SetDone(true);
  todo->updateItem(2, item);
  TodoItem cat = TodoItem::init("cat");
  todo->newItem(cat);
  todo->removeItem(1);
  TodoItem unicorn = TodoItem::init("fluffy unicorns takes over the world kokokooooookkkkkkkkkkkkkkk");
  todo->newItem(unicorn);
  todo->archiveDoneItems();
  list = todo->getTodoList();
  TodoItem it5 = list[3];
  it5.SetDone(true);
  todo->updateItem(3, it5);
  todo->archiveItem(3);


//  int getIndex = 0;
//  TodoItem item = list[getIndex];
//  item.SetDone(true);
//  todo->updateItem(0, item);
//  vector<TodoItem> olist = todo->getTodoList();

//  TodoItem kl = TodoItem::init("x wodo");
//  todo->newItem(kl);
//  TodoItem kdl = TodoItem::init("muuuu");
//  todo->newItem(kdl);
//  TodoItem kdld = TodoItem::init("muuuu");
//  todo->newItem(kdld);
//  todo->removeItem(1);
//  vector<TodoItem> olistd = todo->getTodoList();
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
