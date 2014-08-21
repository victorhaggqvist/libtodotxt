#include "gtest/gtest.h"
#include "todoitem.h"
#include "todotxt.h"

#include <string>
#include <deque>
#include <fstream>
#include <memory>

using namespace Snilius;

/**
 * Tests for todo.txt items
 * Some cases are straight from Ginas spec
 * https://github.com/ginatrapani/todo.txt-cli/wiki/The-Todo.txt-Format
 * @brief TEST
 */

TEST(Todotxt, createObject) {
  std::shared_ptr<Todotxt>todo(new Todotxt("."));
}

TEST(Todotxt, createObjectWithExistingTodofile) {
  system("bash -c 'touch ./todo.txt'");
  std::shared_ptr<Todotxt>todo(new Todotxt("."));
  std::deque<TodoItem> list = todo->getTodoList();
  ASSERT_TRUE(list.size()>=0);
}

TEST(Todotxt, createObjectWithNoTodofile){
  system("bash -c 'rm ./todo.txt'");
  std::shared_ptr<Todotxt>todo(new Todotxt("."));
  std::ifstream fooFile("./todo.txt");
  ASSERT_TRUE(fooFile.is_open());
}

TEST(Todotxt, newItem){
  system("bash -c 'echo a_item > ./todo.txt'");
  std::shared_ptr<Todotxt>todo(new Todotxt("."));
  TodoItem item = TodoItem::init("next do");
  todo->newItem(item);
  std::deque<TodoItem> list = todo->getTodoList();
  ASSERT_TRUE(list.size()==2);
}

TEST(Todotxt, updateItem){
  system("bash -c 'echo a_item > ./todo.txt'");
  std::shared_ptr<Todotxt>todo(new Todotxt("."));
  std::deque<TodoItem> list = todo->getTodoList();

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
  std::shared_ptr<Todotxt>todo(new Todotxt("."));
  std::deque<TodoItem> list = todo->getTodoList();

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

  std::shared_ptr<Todotxt>todo(new Todotxt("."));
  todo->removeItem(1);

  std::deque<TodoItem> list = todo->getTodoList();
  TodoItem item = list[1];
  ASSERT_EQ("a_item_2", item.todo_);
}

TEST(Todotxt, removeItemObject){
  system("bash -c 'echo a_item > ./todo.txt'");
  system("bash -c 'echo pony >> ./todo.txt'");
  system("bash -c 'echo a_item_2 >> ./todo.txt'");
  system("bash -c 'echo unicorn >> ./todo.txt'");

  std::shared_ptr<Todotxt>todo(new Todotxt("."));
  TodoItem toRemove = todo->getTodoList()[1];
  todo->removeItem(toRemove);

  std::deque<TodoItem> list = todo->getTodoList();
  TodoItem item = list[1];
  ASSERT_EQ("a_item_2", item.todo_);
}

TEST(Todotxt, archiveDoneItems){
  system("bash -c 'rm ./archive.txt'");
  system("bash -c 'echo a_item > ./todo.txt'");
  system("bash -c 'echo x pony >> ./todo.txt'");
  system("bash -c 'echo a_item_2 >> ./todo.txt'");
  system("bash -c 'echo unicorn >> ./todo.txt'");

  std::shared_ptr<Todotxt>todo(new Todotxt("."));
  todo->archiveDoneItems();

  std::deque<TodoItem> nonDone = todo->getTodoList();
  ASSERT_EQ(3, nonDone.size());

  std::ifstream arfile("./archive.txt");
  std::string line;
  getline(arfile, line);
  ASSERT_EQ("x pony", line);
}

TEST(Todotxt, archiveItemIndex){
  system("bash -c 'rm ./archive.txt'");
  system("bash -c 'echo a_item > ./todo.txt'");
  system("bash -c 'echo x pony >> ./todo.txt'");
  system("bash -c 'echo a_item_2 >> ./todo.txt'");
  system("bash -c 'echo unicorn >> ./todo.txt'");

  std::shared_ptr<Todotxt>todo(new Todotxt("."));
  todo->archiveItem(1);

  std::deque<TodoItem> nonDone = todo->getTodoList();
  ASSERT_EQ(3, nonDone.size());

  std::ifstream arfile("./archive.txt");
  std::string line;
  getline(arfile, line);
  ASSERT_EQ("x pony", line);
}

TEST(Todotxt, archiveItemObject){
  system("bash -c 'rm ./archive.txt'");
  system("bash -c 'echo a_item > ./todo.txt'");
  system("bash -c 'echo x pony >> ./todo.txt'");
  system("bash -c 'echo a_item_2 >> ./todo.txt'");
  system("bash -c 'echo unicorn >> ./todo.txt'");

  std::shared_ptr<Todotxt>todo(new Todotxt("."));
  TodoItem toArchive = todo->getTodoList()[2];
  todo->archiveItem(toArchive);

  std::deque<TodoItem> nonDone = todo->getTodoList();
  ASSERT_EQ(3, nonDone.size());

  std::ifstream arfile("./archive.txt");
  std::string line;
  getline(arfile, line);
  ASSERT_EQ("a_item_2", line);
}

