#include "gtest/gtest.h"
#include "todoitem.h"
#include <string>
#include <vector>

using namespace std;

/**
 * Tests for todo.txt items
 * Some cases are straight from Ginas spec https://github.com/ginatrapani/todo.txt-cli/wiki/The-Todo.txt-Format
 * @brief TEST
 */

TEST(TodoItem, isDone){
  vector<string> lines;
  lines.push_back("x a task");
  lines.push_back("x (A) a task");
  for (int i=0; i<lines.size();++i){
    TodoItem item(lines.back());
    lines.pop_back();
    EXPECT_TRUE(item.IsDone());
  }
}

TEST(TodoItem, notDone){
  vector<string> lines;
  lines.push_back("a task");
  lines.push_back("xa task");
  lines.push_back("X a task");
  lines.push_back("Xa task");
  lines.push_back("x");
  for (int i=0; i<lines.size();++i){
    TodoItem item(lines.back());
    lines.pop_back();
    EXPECT_FALSE(item.IsDone());
  }
}

TEST(TodoItem, hasPriority){
  struct testItem {
    string todo;
    string expected;
  };
  vector<testItem> lines;
  lines.push_back({"(A) a task", "A"});
  lines.push_back({"x (B) a task", "B"});
  lines.push_back({"x (K) a task", "K"});
  for (int i = 0; i < lines.size(); ++i) {
    TodoItem item(lines.back().todo);
    EXPECT_EQ(lines.back().expected, item.GetPriority());
    lines.pop_back();
  }
}

TEST(TodoItem, noPriority){
  vector<string> lines;
  lines.push_back("(a) a task");
  lines.push_back("x(b) a task");
  lines.push_back("(A)x a task");
  lines.push_back("Really gotta call Mom (A) @phone @someday");
  lines.push_back("(b) Get back to the boss");
  lines.push_back("(B)->Submit TPS report");
  for (int i=0; i<lines.size();++i){
    TodoItem item(lines.back());
    lines.pop_back();
    EXPECT_EQ("", item.GetPriority());
  }
}

TEST(TodoItem, hasDateCreation){
  struct testItem {
    string todo;
    string expected;
  };

  vector<testItem> lines;
  lines.push_back({"x (A) 2014-08-04 a task", "2014-08-04"});
  lines.push_back({"2011-03-02 Document +TodoTxt task format", "2011-03-02"});
  lines.push_back({"(A) 2011-03-02 Call Mom", "2011-03-02"});
  for (int i=0; i<lines.size();++i){
    TodoItem item(lines.back().todo);
    EXPECT_EQ(lines.back().expected, item.GetDateCreation());
    lines.pop_back();
  }
}

TEST(TodoItem, noDateCreation){
  vector<string> lines;
  lines.push_back("(A) Call Mom 2011-03-02");
  lines.push_back("(A)2011-03-02 Call Mom");
  lines.push_back("2011-03-02(A) Call Mom");
  lines.push_back("x2011-03-02(A) Call Mom");
  lines.push_back("x (A)2011-03-02 Call Mom");
  lines.push_back("x (A)2011-3-2 Call Mom");
  lines.push_back("x (A)2011-03-2 Call Mom");
  lines.push_back("x (A)2011-3-02 Call Mom");
  for (int i=0; i<lines.size();++i){
    TodoItem item(lines.back());
    EXPECT_EQ("", item.GetDateCreation());
    lines.pop_back();
  }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
