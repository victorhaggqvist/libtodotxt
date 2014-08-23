#include "todotxtgit.h"
#include "todotxt.h"
#include "todoitem.h"
#include "git2.h"
#include <iostream>
#include <string>
#include "githelper.h"

using namespace Snilius;

Todotxtgit::Todotxtgit(std::string path) :
  path_(path), todotxt_(new Todotxt(path))
{
  // if there is no repo
  if (git_repository_open_ext(
        &repo_, path_.c_str(), GIT_REPOSITORY_OPEN_NO_SEARCH, NULL) != 0) {
    // init a new repo
    int rc = git_repository_init(&repo_, path_.c_str(), false);
    GitHelper::printGitError(rc);
  }
}

std::deque<TodoItem> Todotxtgit::getTodoList() {
  return todotxt_->getTodoList();
}

void Todotxtgit::updateItem(int index, TodoItem &item) {
  todotxt_->updateItem(index, item);
  commitTodoFile(item, "Update");

//  // add file to git
//  std::string pathToAdd = path_ + TODO_FILE_W_SEPARATOR;
//  GitHelper::gitAddFile(repo_, TODO_FILE);

//  // create commit
//  std::string assLine = item.AssembleTodo();
//  std::string elipsedLine = assLine.length()>40 ? assLine.substr(0, 40) + "..." : assLine;
//  std::string commitMsg = "Updated: " + elipsedLine;
//  GitHelper::gitAddCommit(repo_, commitMsg, pathToAdd, TODO_FILE);
}

void Todotxtgit::newItem(TodoItem &item){
  todotxt_->newItem(item);
  commitTodoFile(item, "New");
}

void Todotxtgit::removeItem(int index){
  todotxt_->removeItem(index);
  TodoItem item = todotxt_->getTodoList()[index];
  commitTodoFile(item, "Remove");
}

void Todotxtgit::removeItem(TodoItem &item){
  todotxt_->removeItem(item);
  commitTodoFile(item, "Remove");
}

void Todotxtgit::archiveDoneItems(){
  todotxt_->archiveDoneItems();

  std::string pathTodo = path_ + TODO_FILE_W_SEPARATOR;
  std::string pathArchive = path_ + ARCHIVE_FILE_W_SEPARATOR;

//  GitHelper::gitAddFile(repo_, TODO_FILE);
//  GitHelper::gitAddFile(repo_, ARCHIVE_FILE);
  // TODO commit this stuff
}

void Todotxtgit::archiveItem(int index){
  todotxt_->archiveItem(index);
}

void Todotxtgit::archiveItem(TodoItem &item){
  todotxt_->archiveItem(item);
}

void Todotxtgit::setEnableLogging(bool enableLogging) {
  enableLogging_ = enableLogging;
  todotxt_->setEnableLogging(enableLogging_);
  std::cout << "Is logging enabled: " << enableLogging_ << std::endl;
}

void Todotxtgit::log(std::string msg){
  if (enableLogging_)
    std::cout << msg << std::endl;
}

void Todotxtgit::commitTodoFile(TodoItem &item, std::string commitKeyword) {
  // add file to git
  std::string pathToAdd = path_ + TODO_FILE_W_SEPARATOR;
  GitHelper::gitAddFile(repo_, TODO_FILE);

  // create commit
  std::string assLine = item.AssembleTodo();
  std::string elipsedLine = assLine.length()>40 ? assLine.substr(0, 40) + "..." : assLine;
  std::string commitMsg = commitKeyword+": " + elipsedLine;
  GitHelper::gitAddCommit(repo_, commitMsg, pathToAdd, TODO_FILE);
}
