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

TEST(Todotxt, createObject){
  string base = ".";
  Todotxt *todo = new Todotxt(base);
}

//TEST(Todotxt, createObjectWithExistingTodofile){
//  system("bash -c 'touch ./todo.txt'");
//  Todotxt *todo = new Todotxt(".");
//  vector<TodoItem> list = todo->getTodoList();
//  ASSERT_TRUE(list.size()>=0);
//}

//TEST(Todotxt, createObjectWithNoTodofile){
//  system("bash -c 'rm ./todo.txt'");
//  Todotxt *todo = new Todotxt(".");
//  ifstream fooFile("./todo.txt");
//  ASSERT_TRUE(fooFile.is_open());
//}

//TEST(Todotxt, newItem){
//  system("bash -c 'echo a_item > ./todo.txt'");
//  Todotxt *todo = new Todotxt(".");
//  TodoItem tItem("next do");
//  todo->newItem(tItem);
//  vector<TodoItem> list = todo->getTodoList();
//  ASSERT_TRUE(list.size()==2);
//}

//TEST(Todotxt, updateItem){
//  system("bash -c 'echo a_item > ./todo.txt'");
//  Todotxt *todo = new Todotxt(".");
//  vector<TodoItem> list = todo->getTodoList();

//  int getIndex = 0;
//  TodoItem item = list.at(getIndex);
//  item.SetDone(true);
//  todo->updateItem(getIndex, item);

//  list = todo->getTodoList();
//  TodoItem expect = list.at(getIndex);

//  ASSERT_TRUE(expect.IsDone());
//}

TEST(Todotxt, removeItemIndex){
  FAIL();
}

TEST(Todotxt, removeItemObject){
  FAIL();
}

TEST(Todotxt, archiveItemIndex){
  FAIL();
}

TEST(Todotxt, archiveItemObject){
  FAIL();
}
