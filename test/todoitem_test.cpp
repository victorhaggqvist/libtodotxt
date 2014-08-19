#include "gtest/gtest.h"
#include "todoitem.h"
#include <string>
#include <vector>

using namespace std;
using namespace Snilius;

/**
 * Tests for todo.txt items
 * Some cases are straight from Ginas spec
 * https://github.com/ginatrapani/todo.txt-cli/wiki/The-Todo.txt-Format
 * @brief TEST
 */

TEST(TodoItem, isDone){
  EXPECT_TRUE(TodoItem::init("x a task").IsDone());
  EXPECT_TRUE(TodoItem::init("x (A) a task").IsDone());
}

TEST(TodoItem, notDone){
  EXPECT_FALSE(TodoItem::init("a task").IsDone());
  EXPECT_FALSE(TodoItem::init("xa task").IsDone());
  EXPECT_FALSE(TodoItem::init("X a task").IsDone());
  EXPECT_FALSE(TodoItem::init("Xa task").IsDone());
  EXPECT_FALSE(TodoItem::init("x").IsDone());
  EXPECT_FALSE(TodoItem::init("xylophone lesson").IsDone());
  EXPECT_FALSE(TodoItem::init("X 2012-01-01 Make resolutions").IsDone());
  EXPECT_FALSE(TodoItem::init("(A) x Find ticket prices").IsDone());
}

TEST(TodoItem, hasPriority){
  EXPECT_EQ("A", TodoItem::init("(A) a task").GetPriority());
  EXPECT_EQ("B", TodoItem::init("x (B) a task").GetPriority());
  EXPECT_EQ("K", TodoItem::init("x (K) a task").GetPriority());
}

TEST(TodoItem, noPriority){
  EXPECT_EQ("", TodoItem::init("(a) a task").GetPriority());
  EXPECT_EQ("", TodoItem::init("x(b) a task").GetPriority());
  EXPECT_EQ("", TodoItem::init("(A)x a task").GetPriority());
  EXPECT_EQ("", TodoItem::init("Really gotta call Mom (A) @phone @someday").GetPriority());
  EXPECT_EQ("", TodoItem::init("(b) Get back to the boss").GetPriority());
  EXPECT_EQ("", TodoItem::init("(B)->Submit TPS report").GetPriority());
}

TEST(TodoItem, hasDateCreation){
  EXPECT_EQ("2011-03-02", TodoItem::init("2011-03-02 Document +TodoTxt task format").GetDateCreation());
  EXPECT_EQ("2011-03-02", TodoItem::init("(A) 2011-03-02 Call Mom").GetDateCreation());
  EXPECT_EQ("2011-03-02", TodoItem::init("x (A) 2011-05-21 2011-03-02 Call Mom").GetDateCreation());
}

TEST(TodoItem, noDateCreation){
  EXPECT_EQ("", TodoItem::init("(A) Call Mom 2011-03-02").GetDateCreation());
  EXPECT_EQ("", TodoItem::init("(A)2011-03-02 Call Mom").GetDateCreation());
  EXPECT_EQ("", TodoItem::init("2011-03-02(A) Call Mom").GetDateCreation());
  EXPECT_EQ("", TodoItem::init("x2011-03-02(A) Call Mom").GetDateCreation());
  EXPECT_EQ("", TodoItem::init("x (A)2011-03-02 Call Mom").GetDateCreation());
  EXPECT_EQ("", TodoItem::init("x (A)2011-3-2 Call Mom").GetDateCreation());
  EXPECT_EQ("", TodoItem::init("x (A)2011-03-2 Call Mom").GetDateCreation());
  EXPECT_EQ("", TodoItem::init("x (A)2011-3-02 Call Mom").GetDateCreation());
  EXPECT_EQ("", TodoItem::init("x (A)20110302 Call Mom").GetDateCreation());
}

TEST(TodoItem, hasContext){
  vector<string> expects;
  expects.push_back("@iphone");
  expects.push_back("@phone");
  EXPECT_EQ(expects, TodoItem::init("(A) Call Mom +Family +PeaceLoveAndHappiness @iphone @phone").GetContexts());

  vector<string> expects2;
  expects2.push_back("@woop");
  EXPECT_EQ(expects2, TodoItem::init("x (A) Call @woop").GetContexts());

  vector<string> expects3;
  expects3.push_back("@woop");
  EXPECT_EQ(expects3, TodoItem::init("x (A) Call @woop pony").GetContexts());
}

TEST(TodoItem, noContext){
  vector<string> expected;
  EXPECT_EQ(expected, TodoItem::init("Email SoAndSo at soandso@example.com").GetContexts());
  EXPECT_EQ(expected, TodoItem::init("Email SoAndSo at").GetContexts());
}

TEST(TodoItem, hasProject){
  vector<string> expects = {"+Family", "+PeaceLoveAndHappiness"};
  EXPECT_EQ(expects, TodoItem::init("(A) Call Mom +Family +PeaceLoveAndHappiness @iphone @phone").GetProjects());

  vector<string> expects2 = {"+woop"};
  EXPECT_EQ(expects2, TodoItem::init("x (A) Call +woop").GetProjects());
}

TEST(TodoItem, noProject){
  vector<string> expected;
  EXPECT_EQ(expected, TodoItem::init("Learn how to add 2+2").GetProjects());
  EXPECT_EQ(expected, TodoItem::init("Email SoAndSo at").GetProjects());
}

TEST(TodoItem, hasDateDone){
  EXPECT_EQ("2011-03-02", TodoItem::init("x 2011-03-02 2011-03-01 Review +TodoTxtTouch @github").GetDateDone());
  EXPECT_EQ("2014-08-06", TodoItem::init("x 2014-08-06 this is done").GetDateDone());
  EXPECT_EQ("2014-08-06", TodoItem::init("x (A) 2014-08-06 this is done").GetDateDone());
}

TEST(TodoItem, noDateDone){
  EXPECT_EQ("", TodoItem::init("x2011-03-02 2011-03-01 Review +TodoTxtTouch @github").GetDateDone());
  EXPECT_EQ("", TodoItem::init("2014-08-06 this is done").GetDateDone());
  EXPECT_EQ("", TodoItem::init("x  2014-08-06 this is done").GetDateDone());
  EXPECT_EQ("", TodoItem::init("x (A) 2014-08-06this is done").GetDateDone());
}

TEST(TodoItem, getTodo){
  EXPECT_EQ("Call Mom +Family +PeaceLoveAndHappiness @iphone @phone",
    TodoItem::init("(A) Call Mom +Family +PeaceLoveAndHappiness @iphone @phone").GetTodo());

  EXPECT_EQ("A +random thing to do @work", TodoItem::init("x (C) A +random thing to do @work").GetTodo());
}

TEST(TodoItem, decodeLine){
  TodoItem item = TodoItem::init("(A) Call Mom +Family +PeaceLoveAndHappiness @iphone @phone");

  EXPECT_EQ("A", item._priority);

  EXPECT_FALSE(item._done);

  vector<string> contexts = {"@iphone", "@phone"};
  EXPECT_EQ(contexts, item._contexts);

  vector<string> projects = {"+Family", "+PeaceLoveAndHappiness"};
  EXPECT_EQ(projects, item._projects);

  EXPECT_EQ("Call Mom +Family +PeaceLoveAndHappiness @iphone @phone", item._todo);


  TodoItem item2 = TodoItem::init("x (A) 2014-08-06 Call Mom +Family +PeaceLoveAndHappiness @iphone @phone");
  EXPECT_TRUE(item2.IsDone());
  EXPECT_EQ("2014-08-06", item2.GetDateDone());
  EXPECT_EQ("", item2.GetDateCreation());

  TodoItem item3 = TodoItem::init("x (A) 2014-08-06 2014-08-02 Really gotta call Mom +Family @phone");
  EXPECT_EQ("2014-08-06", item3.GetDateDone());
  EXPECT_EQ("2014-08-02", item3.GetDateCreation());
  EXPECT_EQ("Really gotta call Mom +Family @phone", item3.GetTodo());
}

TEST(TodoItem, getKeyValuePairs){
  vector<TodoItem::ItemKVPair_t> pairs;
  TodoItem item = TodoItem::init("x Really gotta call:Mom");
  pairs = item.GetKeyValuePairs();
  EXPECT_EQ("call", pairs.back().key);
  EXPECT_EQ("Mom", pairs.back().value);

  TodoItem item2 = TodoItem::init("(A) 2014-08-06 2014-08-02 Really yolo:we gotta call Mom +Family @phone due:1234");
  pairs = item2.GetKeyValuePairs();
  EXPECT_EQ("yolo", pairs.back().key);
  EXPECT_EQ("we", pairs.back().value);
  pairs.pop_back();
  EXPECT_EQ("due", pairs.back().key);
  EXPECT_EQ("1234", pairs.back().value);

  TodoItem item3 = TodoItem::init("(A) 2014-08-06 2014-08-02 Really much:wow yolo:we gotta call Mom +Family @phone due:1234");
  pairs = item3.GetKeyValuePairs();
  EXPECT_EQ("much", pairs.back().key);
  EXPECT_EQ("wow", pairs.back().value);
  pairs.pop_back();
  EXPECT_EQ("yolo", pairs.back().key);
  EXPECT_EQ("we", pairs.back().value);
  pairs.pop_back();
  EXPECT_EQ("due", pairs.back().key);
  EXPECT_EQ("1234", pairs.back().value);
}

TEST(TodoItem, getKeyValuePairsIsEmpty){
  EXPECT_EQ(0, TodoItem::init("random todo").GetKeyValuePairs().size());
  EXPECT_EQ(0, TodoItem::init("x done random todo").GetKeyValuePairs().size());
  EXPECT_EQ(0, TodoItem::init("x (A) random todo").GetKeyValuePairs().size());
}

TEST(TodoItem, getKeyValue){
  EXPECT_EQ("wow", TodoItem::init("random much:wow").GetKeyValue("much"));

  TodoItem item2 = TodoItem::init("random much:wow de:kde");
  EXPECT_EQ("wow", item2.GetKeyValue("much"));
  EXPECT_EQ("kde", item2.GetKeyValue("de"));
}

TEST(TodoItem, getKeyValueIsEmpty){
  TodoItem item("random");
  EXPECT_EQ("", item.GetKeyValue("much"));

  TodoItem item2("random much:");
  EXPECT_EQ("", item2.GetKeyValue("much"));

  TodoItem item3("random :much");
  EXPECT_EQ("", item3.GetKeyValue("much"));
}

TEST(TodoItem, bakeTodo){
  string expected = "x 2011-03-02 2011-03-01 Review Tim's pull request +TodoTxtTouch @github";
  EXPECT_EQ(expected, TodoItem::init(expected).AssembleTodo());

  string expected2 = "a todo";
  EXPECT_EQ(expected2, TodoItem::init(expected2).AssembleTodo());

  string expected3 = "complete +libtodotxt and stuff @hax";
  EXPECT_EQ(expected3, TodoItem::init(expected3).AssembleTodo());

  string expected4 = "complete +libtodotxt @gh and stuff @hax";
  EXPECT_EQ(expected4, TodoItem::init(expected4).AssembleTodo());
}

TEST(TodoItem, setDoneTrue){
  TodoItem item = TodoItem::init("do stuff");
  item.SetDone(true);
  EXPECT_EQ("x do stuff", item.AssembleTodo());

  TodoItem item2 = TodoItem::init("x do stuff");
  item2.SetDone(true);
  EXPECT_EQ("x do stuff", item2.AssembleTodo());
}

TEST(TodoItem, setDoneFalse){
  TodoItem item = TodoItem::init("x do stuff");
  item.SetDone(false);
  EXPECT_EQ("do stuff", item.AssembleTodo());

  TodoItem item2 = TodoItem::init("do stuff");
  item2.SetDone(false);
  EXPECT_EQ("do stuff", item2.AssembleTodo());
}

TEST(TodoItem, setPriority){
  TodoItem item = TodoItem::init("do stuff");
  item.SetPriority("A");
  EXPECT_EQ("(A) do stuff", item.AssembleTodo());

  TodoItem item2 = TodoItem::init("x do stuff");
  item2.SetPriority("B");
  EXPECT_EQ("x (B) do stuff", item2.AssembleTodo());
}

TEST(TodoItem, unsetPriority){
  TodoItem item = TodoItem::init("(A) do stuff");
  item.SetPriority("");
  EXPECT_EQ("do stuff", item.AssembleTodo());

  TodoItem item2 = TodoItem::init("x (B) do stuff");
  item2.SetPriority("");
  EXPECT_EQ("x do stuff", item2.AssembleTodo());
}

TEST(TodoItem, setDateCreation){
  TodoItem item = TodoItem::init("do stuff");
  item.SetDateCreation("2014-08-07");
  EXPECT_EQ("2014-08-07 do stuff", item.AssembleTodo());

  TodoItem item2 = TodoItem::init("x 2014-08-10 do stuff");
  item2.SetDateCreation("2014-08-07");
  EXPECT_EQ("x 2014-08-10 2014-08-07 do stuff", item2.AssembleTodo());

  TodoItem item3 = TodoItem::init("x 2014-08-10 do stuff");
  ASSERT_THROW(item3.SetDateCreation("2014-08-7"), std::invalid_argument);
}

TEST(TodoItem, unsetDateCreation){
  TodoItem item = TodoItem::init("2014-08-07 do stuff");
  item.SetDateCreation("");
  EXPECT_EQ("do stuff", item.AssembleTodo());

  TodoItem item2 = TodoItem::init("x 2014-08-10 2014-08-07 do stuff");
  item2.SetDateCreation("");
  EXPECT_EQ("x 2014-08-10 do stuff", item2.AssembleTodo());
}

TEST(TodoItem, setDateDone){
  TodoItem item = TodoItem::init("x do stuff");
  item.SetDateDone("2014-08-07");
  EXPECT_EQ("x 2014-08-07 do stuff", item.AssembleTodo());

  TodoItem item2 = TodoItem::init("2014-08-07 do stuff");
  item2.SetDateDone("2014-08-10");
  item2.SetDone(true);
  EXPECT_EQ("x 2014-08-10 2014-08-07 do stuff", item2.AssembleTodo());

  TodoItem item3 = TodoItem::init("x 2014-08-10 do stuff");
  ASSERT_THROW(item3.SetDateDone("2014-08-7"), std::invalid_argument);
}

TEST(TodoItem, unsetDateDone){
  TodoItem item = TodoItem::init("x 2014-08-07 do stuff");
  item.SetDateDone("");
  EXPECT_EQ("x do stuff", item.AssembleTodo());

  TodoItem item2 = TodoItem::init("x (F) 2014-08-07 do stuff");
  item2.SetDateDone("");
  EXPECT_EQ("x (F) do stuff", item2.AssembleTodo());
}

TEST(TodoItem, setTodo){
  TodoItem item = TodoItem::init("stuff n stuff");
  item.SetTodo("stuff n other stuff");
  EXPECT_EQ("stuff n other stuff", item.AssembleTodo());
}
