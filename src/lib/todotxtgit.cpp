#include "todotxtgit.h"
#include "todotxt.h"
#include "todoitem.h"
#include "git2.h"
#include <iostream>
#include <string>
//#include "git2/commit.h"
//#include "git2/repository.h"
//#include "git2/errors.h"
//#include "git2/index.h"
//#include "git2/blob.h"
//#include "git2/tree.h"
//#include "git2/signature.h"

using namespace Snilius;

Todotxtgit::Todotxtgit(std::string path) :
  path_(path), todotxt_(new Todotxt(path))
{
  // if there is no repo
  if (git_repository_open_ext(
        &repo_, path_.c_str(), GIT_REPOSITORY_OPEN_NO_SEARCH, NULL) != 0) {
    // init a new repo
    int error = git_repository_init(&repo_, path_.c_str(), false);
    printGitError(error);
  }

  // open index
  git_repository_index(&idx_, repo_);

  // use users default git name & email
  git_signature_default(&sign_, repo_);

}

std::deque<TodoItem> Todotxtgit::getTodoList() {
  return todotxt_->getTodoList();
}

void Todotxtgit::updateItem(int index, TodoItem &item) {
  todotxt_->updateItem(index, item);

  // add file to git
  std::string pathToAdd = path_ + TODO_FILE_W_SEPARATOR;
//  log("git add: "+pathToAdd);
//  int error = git_index_add_bypath(idx_, pathToAdd.c_str());
//  printGitError(error);

  // create commit
  std::string assLine = item.AssembleTodo();
  std::string elipsedLine = assLine.length()>40 ? assLine.substr(0, 40) + "..." : assLine;
  std::string commitMsg = "Updated: " + elipsedLine;
  if(addGitCommit(repo_, sign_, commitMsg, pathToAdd)){
//    const git_error *e = giterr_last();
//    printf("Error %d/%d: %s\n", error, e->klass, e->message);
  }
}

void Todotxtgit::newItem(TodoItem &item){

}

void Todotxtgit::removeItem(int index){

}

void Todotxtgit::removeItem(TodoItem &item){

}

void Todotxtgit::archiveDoneItems(){

}

void Todotxtgit::archiveItem(int index){

}

void Todotxtgit::archiveItem(TodoItem &item){

}

std::string ellipsisLine(std::string line){
  return "";
}

void Todotxtgit::printGitError(int error) {
  if (error < 0){
    const git_error *e = giterr_last();
    printf("Error %d/%d: %s\n", error, e->klass, e->message);
  }
}

/**
 * Helper for commit creation
 * @ref https://stackoverflow.com/questions/15711444/how-to-commit-to-a-git-repository-using-libgit2
 * @brief addGitCommit
 * @param repo
 * @param sign
 * @param content
 * @param content_sz
 * @param message
 * @return
 */
bool Todotxtgit::addGitCommit (git_repository * repo,
                   git_signature * sign,
                   std::string message,
                   std::string file)
{
  int rc;              /* return code for git_ functions */
  git_oid oid_blob;    /* the SHA1 for our blob in the tree */
  git_oid oid_tree;    /* the SHA1 for our tree in the commit */
  git_oid oid_commit;  /* the SHA1 for our initial commit */
  git_blob *blob;      /* our blob in the tree */
  git_tree *tree_cmt;  /* our tree in the commit */
  git_treebuilder *tree_bld;  /* tree builder */
  bool success = false;
  bool hasPrevCommit = false;

  // Check if there is previous commits
  git_oid oid;
  rc = git_reference_name_to_id(&oid, repo, "HEAD");

  std::vector<git_commit*> vCommits;
  if (rc == 0){ // there is prevcommit
    git_commit *prev_commit;
    rc = git_commit_lookup(&prev_commit, repo_, &oid);

    unsigned int count = git_commit_parentcount(prev_commit);
    for (unsigned int i=0; i<count; i++) {
//      git_oid *nth_parent_id = git_commit_parent_id(commit);

      git_commit *nth_parent = NULL;
      int error = git_commit_parent(&nth_parent, vCommits[i-1], i);

      vCommits.push_back(nth_parent);
    }
  }

  // make array of parent commits
  if(vCommits.size()>0){
    git_commit **prev_commits = &vCommits[0];
  }

  if (rc == 0)
    hasPrevCommit = true;

  /* create a blob from our buffer */
  rc = git_blob_create_fromworkdir(&oid_blob, repo, file.c_str());

  if (rc == 0) { /* blob created */
    log("blob created");

    rc = git_blob_lookup( &blob, repo, &oid_blob );
    if (rc == 0) { /* blob created and found */
      log("blob created and found");
      rc = git_treebuilder_create(&tree_bld, NULL );
      if (rc == 0) { /* a new tree builder created */
        log("a new tree builder created");
        rc = git_treebuilder_insert(
              NULL,
              tree_bld,
              "todo.txt",
              &oid_blob,
              GIT_FILEMODE_BLOB );

        if (rc == 0) { /* blob inserted in tree */
          log("blob inserted in tree");
          rc = git_treebuilder_write(&oid_tree, repo, tree_bld);
          if (rc == 0) { /* the tree was written to the database */
            log("the tree was written to the database");
            rc = git_tree_lookup(&tree_cmt, repo, &oid_tree);
            if (rc == 0) { /* we've got the tree pointer */
              log("we've got the tree pointer");

              if (hasPrevCommit) {
                rc = git_commit_create(
                      &oid_commit, repo, "HEAD",
                      sign, sign, /* same author and commiter */
                      NULL, /* default UTF-8 encoding */
                      message.c_str(),
                      tree_cmt, 0, NULL);
              } else {
                rc = git_commit_create(
                      &oid_commit, repo, "HEAD",
                      sign, sign, /* same author and commiter */
                      NULL, /* default UTF-8 encoding */
                      message.c_str(),
                      tree_cmt, 0, NULL);
              }

              if (rc == 0) {
                log("committed");
                success = true;
              }
              git_tree_free(tree_cmt);

            }
          }
        }
        git_treebuilder_free(tree_bld);
      }
      git_blob_free(blob);
    }
  }

  printGitError(rc);

  return success;
}

void Todotxtgit::log(std::string msg){
  std::cout << msg << std::endl;
}
