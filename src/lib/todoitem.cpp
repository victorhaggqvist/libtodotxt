#include "todoitem.h"
#include <string>
#include <iostream>
#include <regex>

using namespace std;

TodoItem::TodoItem(string todo_line) {
  raw_line = todo_line;
  DecodeLine();
}

void TodoItem::DecodeLine() {
  done = IsDone();
  if (GetPriority().length() > 0) priority = GetPriority();
  if (GetDateCreation().length() > 0) date_creation = GetDateCreation();
}

bool TodoItem::IsDone(){
  if (raw_line.substr(0,2) == "x ")
    return true;
  else
    return false;
}
/**
 * Get the priorty of the task
 * @brief TodoItem::GetPriority
 * @return string proirity
 */
string TodoItem::GetPriority() {
  int priority_start = 0;

  if (done) priority_start = 2;

  if (raw_line.substr(priority_start, 1) == "(" &&
      raw_line.substr(priority_start + 2, 1) == ")" &&
      raw_line.substr(priority_start + 3, 1) == " " &&
      isupper(raw_line.substr(priority_start + 1, 1)[0])) {

    return raw_line.substr(priority_start + 1, 1);
  } else {

    return "";
  }
}

string TodoItem::GetDateCreation() {
  int start_pos = 0;

  if (done) start_pos += 2;
  if (priority.length() > 0) start_pos += 4;

  string possible_date = raw_line.substr(start_pos, 10);
  if (regex_match(possible_date, regex("[0-9]{4}-[0-9]{2}-[0-9]{2}")))
    return possible_date;
  else
    return "";
}

vector<string> TodoItem::GetContexts()
{
  int cut_pos = 0;

  if (done) cut_pos += 2;
  if (priority.length() > 0) cut_pos += 4;
  if (date_creation.length() > 0) cut_pos += 10;

  string search_string = raw_line.substr(cut_pos, raw_line.length());

  regex_iterator<string::iterator> rit(search_string.begin(), search_string.end(), regex("\\s(@\\w+)"));
  regex_iterator<string::iterator> rend;
  while (rit != rend) {
    cout << rit->str() << endl;
    ++rit;
  }

}
