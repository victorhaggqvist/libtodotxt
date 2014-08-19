#include "gtest/gtest.h"
#include "todoitem.h"
#include "todotxt.h"

#include <string>
#include <vector>
#include <fstream>

using namespace std;
using namespace Snilius;

/**
 * Tests for todo.txt items
 * Some cases are straight from Ginas spec
 * https://github.com/ginatrapani/todo.txt-cli/wiki/The-Todo.txt-Format
 * @brief TEST
 */

TEST(Todotxt, createObject) {
  string base = ".";
  Todotxt *todo = new Todotxt(base);
}

TEST(Todotxt, createObjectWithExistingTodofile) {
  system("bash -c 'touch ./todo.txt'");
  Todotxt *todo = new Todotxt(".");
  vector<TodoItem> list = todo->getTodoList();
  ASSERT_TRUE(list.size()>=0);
}

TEST(Todotxt, createObjectWithNoTodofile){
  system("bash -c 'rm ./todo.txt'");
  Todotxt *todo = new Todotxt(".");
  ifstream fooFile("./todo.txt");
  ASSERT_TRUE(fooFile.is_open());
}

TEST(Todotxt, newItem){
  system("bash -c 'echo a_item > ./todo.txt'");
  Todotxt *todo = new Todotxt(".");
  TodoItem item = TodoItem::init("next do");
  todo->newItem(item);
  vector<TodoItem> list = todo->getTodoList();
  ASSERT_TRUE(list.size()==2);
}

TEST(Todotxt, updateItem){
  system("bash -c 'echo a_item > ./todo.txt'");
  Todotxt *todo = new Todotxt(".");
  vector<TodoItem> list = todo->getTodoList();

  int getIndex = 0;
  TodoItem item = list.at(getIndex);
  item.SetDone(true);
  todo->updateItem(getIndex, item);

  list = todo->getTodoList();
  TodoItem expect = list.at(getIndex);
  ASSERT_TRUE(expect.done_);
}

TEST(Todotxt, updateItem2){
  system("bash -c 'echo a_item > ./todo.txt'");
  Todotxt *todo = new Todotxt(".");
  vector<TodoItem> list = todo->getTodoList();

  int getIndex = 0;
  TodoItem item = list[getIndex];
  item.SetTodo("a_item @myplace");
  todo->updateItem(getIndex, item);

  list = todo->getTodoList();
  TodoItem actualItem = list[getIndex];
  std::string con = actualItem.contexts_[0];
  ASSERT_EQ("@myplace", actualItem.contexts_[0]);
}


TEST(Todotxt, removeItemIndex){
  system("bash -c 'echo a_item > ./todo.txt'");
  system("bash -c 'echo pony >> ./todo.txt'");
  system("bash -c 'echo a_item_2 >> ./todo.txt'");
  system("bash -c 'echo unicorn >> ./todo.txt'");

  Todotxt *todo = new Todotxt(".");
  todo->removeItem(1);

  vector<TodoItem> list = todo->getTodoList();
  TodoItem item = list[0];
  ASSERT_EQ("a_item_2", item.todo_);
}

//TEST(Todotxt, removeItemObject){
//  FAIL();
//}

//TEST(Todotxt, archiveItemIndex){
//  FAIL();
//}

//TEST(Todotxt, archiveItemObject){
//  FAIL();
//}

