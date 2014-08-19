#ifndef TODOITEM_H
#define TODOITEM_H

#include <string>
#include <vector>
#include <deque>

namespace Snilius {

  class TodoItem {
    private:
      std::string raw_line;
      const std::string REGEX_DATE = "[0-9]{4}-[0-9]{2}-[0-9]{2}";
      const std::string REGEX_CONTEXT = "\\s(@\\w+)";
      const std::string REGEX_PROJECT = "\\s(\\+\\w+)";
      const std::string REGEX_KEYVALUE = "\\s\\w+:\\S+";
      const int PADDING_PRIORITY = 4;
      const int PADDING_DATE = 11;
      const int PADDING_DONE = 2;

      void DecodeLine();
      std::deque<std::string> RegexFind(std::string pattern);

    public:
      TodoItem(const std::string &todoLine);
      TodoItem &operator=(const TodoItem &obj);
      bool _done;
      std::string _todo, _dateCreation, _dateDone, _priority;
      std::vector<std::string> _contexts, _projects;
      struct ItemKVPair_t{
          std::string key;
          std::string value;
      };

      bool IsDone();
      std::string GetPriority();
      std::string GetDateCreation();
      std::string GetDateDone();
      std::vector<std::string> GetContexts();
      std::vector<std::string> GetProjects();
      std::string GetTodo();
      std::vector<ItemKVPair_t> GetKeyValuePairs();
      std::string GetKeyValue(std::string key);
      std::string AssembleTodo() const;
      void SetDone(bool isDone);
      void SetPriority(std::string priority);
      void SetDateCreation(std::string creationDate);
      void SetDateDone(std::string doneDate);
      void SetTodo(std::string todoLine);
      void NotifyChange();
      TodoItem static init(const std::string &todoLine);
  };

}

#endif // TODOITEM_H
