#ifndef TODOITEM_H
#define TODOITEM_H

#include <string>
#include <vector>

using namespace std;

class TodoItem {
  private:
    string raw_line;
    bool done;
    string todo, context, project, date_creation, date_done, priority;

    void DecodeLine();

  public:
    TodoItem(string todoLine);
    bool IsDone();
    string GetPriority();
    string GetDateCreation();
    vector<string> GetContexts();
};

#endif // TODOITEM_H
