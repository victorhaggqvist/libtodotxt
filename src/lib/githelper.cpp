#include "githelper.h"
#include "git2.h"
#include <stdio.h>

GitHelper::GitHelper()
{
}

/**
 * Helper for commit creation
 * @ref https://stackoverflow.com/questions/15711444/how-to-commit-to-a-git-repository-using-libgit2
 * @brief gitAddCommit
 * @param repo
 * @param message commit message
 * @param filePath full path to file, ths is for creating a file blob
 * @param file filename for tree
 * @return
 */
bool GitHelper::gitAddCommit(git_repository *repo,
                                    std::string message,
                                    std::string filePath,
                                    std::string file)
{
  int rc;
  git_oid oid_blob;    /* the SHA1 for our blob in the tree */
  git_oid oid_tree;    /* the SHA1 for our tree in the commit */
  git_oid oid_commit;  /* the SHA1 for our initial commit */
  git_oid oid_head;
  git_blob *blob;      /* our blob in the tree */
  git_tree *tree_cmt;  /* our tree in the commit */
  git_treebuilder *tree_bld = NULL;  /* tree builder */
  git_commit* parent_commit = NULL;
  git_signature *sign;
  bool success = false;

  // use users default git name & email
  git_signature_default(&sign, repo);

  //
  // Chech if there is previous commit that should go as parent
  //
  if (git_reference_name_to_id(&oid_head, repo, "HEAD") == 0) {

//    printf("There is parent commit\n");

    git_commit *prev_commit;
    rc = git_commit_lookup(&prev_commit, repo, &oid_head);

    if (rc == 0)
      parent_commit = prev_commit;
    else
      printGitError(rc);

  }else {
//    printf("No parent commit\n");
  }

  //
  // Open tree if exists
  //
  git_object *obj;
  rc = git_revparse_single(&obj, repo, "HEAD^{tree}");
  if (rc == 0){
    git_tree *tree = (git_tree *) obj;
    rc = git_treebuilder_create(&tree_bld, tree);

  }
  printGitError(rc);

  //
  // Create a blob for our file
  //
  rc = git_blob_create_fromdisk(&oid_blob, repo, filePath.c_str());

  if (rc == 0) { /* blob created */
//    printf("blob created\n");

    rc = git_blob_lookup(&blob, repo, &oid_blob);

    if (rc == 0) { /* blob created and found */
//      printf("blob created and found\n");

      if (tree_bld == NULL) // do we have a tree
        rc = git_treebuilder_create(&tree_bld, NULL);

      if (rc == 0) { /* a new tree builder created */
//        printf("a new tree builder created\n");

        rc = git_treebuilder_insert(
               NULL,
               tree_bld,
               file.c_str(),
               &oid_blob,
               GIT_FILEMODE_BLOB);

        if (rc == 0) { /* blob inserted in tree */
//          printf("blob inserted in tree\n");

          rc = git_treebuilder_write(&oid_tree, repo, tree_bld);

          if (rc == 0) { /* the tree was written to the database */
//            printf("the tree was written to the database\n");

            rc = git_tree_lookup(&tree_cmt, repo, &oid_tree);

            if (rc == 0) { /* we've got the tree pointer */
//              printf("we've got the tree pointer\n");

              if (parent_commit != NULL){
                const git_commit *parents[] = {parent_commit};
                rc = git_commit_create(
                      &oid_commit, repo, "HEAD",
                      sign, sign,         // same author and commiter
                      NULL,               // default UTF-8 encoding
                      message.c_str(),
                      tree_cmt,
                      1,                  // there will always be one parent commit
                      parents);
//                printf("Commit with parent\n");
              }else {
                rc = git_commit_create(
                      &oid_commit, repo, "HEAD",
                      sign, sign, /* same author and commiter */
                      NULL, /* default UTF-8 encoding */
                      message.c_str(),
                      tree_cmt, 0, NULL);
//                printf("First commit ie no parent\n");
              }
              if (rc == 0) {
//                printf("committed\n");
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

/**
 * Commit multiple files, separete for now
 * @brief GitHelper::gitAddCommit
 * @param repo
 * @param message
 * @param filePath
 * @param file
 * @return
 */
bool GitHelper::gitAddCommit(git_repository *repo,
                             std::string message,
                             std::vector<std::string> filePaths,
                             std::vector<std::string> files)
{
  int rc;
  std::vector<git_oid> oid_blobs;    /* the SHA1 for our blob in the tree */
  git_oid oid_tree;    /* the SHA1 for our tree in the commit */
  git_oid oid_commit;  /* the SHA1 for our initial commit */
  git_oid oid_head;
  std::vector<git_blob *> blobs;      /* our blob in the tree */
  git_tree *tree_cmt;  /* our tree in the commit */
  git_treebuilder *tree_bld = NULL;  /* tree builder */
  git_commit* parent_commit = NULL;
  git_signature *sign;
  bool success = false;

  // use users default git name & email
  git_signature_default(&sign, repo);

  //
  // Chech if there is previous commit that should go as parent
  //
  if (git_reference_name_to_id(&oid_head, repo, "HEAD") == 0) {

//    printf("There is parent commit\n");

    git_commit *prev_commit;
    rc = git_commit_lookup(&prev_commit, repo, &oid_head);

    if (rc == 0)
      parent_commit = prev_commit;
    else
      printGitError(rc);

  }else {
//    printf("No parent commit\n");
  }

  //
  // Open tree if exists
  //
  git_object *obj;
  rc = git_revparse_single(&obj, repo, "HEAD^{tree}");
  if (rc == 0){
    git_tree *tree = (git_tree *) obj;
    rc = git_treebuilder_create(&tree_bld, tree);

  }
  printGitError(rc);

  //
  // Create a blob for our file
  //

  for (std::string fp:filePaths){
    git_oid oid_blob;
    rc = git_blob_create_fromdisk(&oid_blob, repo, fp.c_str());
    if (rc == 0)
      oid_blobs.push_back(oid_blob);
  }
  printGitError(rc);


  if (rc == 0) { /* blob created */
//    printf("blob created\n");

    for (git_oid oid_blob:oid_blobs){
      git_blob *blob;
      rc = git_blob_lookup(&blob, repo, &oid_blob);
      if (rc == 0)
        blobs.push_back(blob);
    }

    if (rc == 0) { /* blob created and found */
//      printf("blob created and found\n");

      if (tree_bld == NULL) // do we have a tree
        rc = git_treebuilder_create(&tree_bld, NULL);

      if (rc == 0) { /* a new tree builder created */
//        printf("a new tree builder created\n");

        for (int i = 0; i < files.size(); ++i){
          git_oid oid = oid_blobs.at(i);
          std::string file = files.at(i);

          rc = git_treebuilder_insert(
                 NULL,
                 tree_bld,
                 file.c_str(),
                 &oid,
                 GIT_FILEMODE_BLOB);

        }

        if (rc == 0) { /* blob inserted in tree */
//          printf("blob inserted in tree\n");

          rc = git_treebuilder_write(&oid_tree, repo, tree_bld);

          if (rc == 0) { /* the tree was written to the database */
//            printf("the tree was written to the database\n");

            rc = git_tree_lookup(&tree_cmt, repo, &oid_tree);

            if (rc == 0) { /* we've got the tree pointer */
//              printf("we've got the tree pointer\n");

              if (parent_commit != NULL){
                const git_commit *parents[] = {parent_commit};
                rc = git_commit_create(
                      &oid_commit, repo, "HEAD",
                      sign, sign,         // same author and commiter
                      NULL,               // default UTF-8 encoding
                      message.c_str(),
                      tree_cmt,
                      1,                  // there will always be one parent commit
                      parents);
//                printf("Commit with parent\n");
              }else {
                rc = git_commit_create(
                      &oid_commit, repo, "HEAD",
                      sign, sign, /* same author and commiter */
                      NULL, /* default UTF-8 encoding */
                      message.c_str(),
                      tree_cmt, 0, NULL);
//                printf("First commit ie no parent\n");
              }
              if (rc == 0) {
//                printf("committed\n");
                success = true;
              }
              git_tree_free(tree_cmt);
            }
          }
        }
        git_treebuilder_free(tree_bld);
      }
      for (git_blob *blob:blobs)
        git_blob_free(blob);
    }
  }
  printGitError(rc);
  return success;
}

void GitHelper::printGitError(int error) {
  if (error < 0){
    const git_error *e = giterr_last();
    printf("Error %d/%d: %s\n", error, e->klass, e->message);
  }
}

bool GitHelper::gitAddFile(git_repository *repo, std::string file){
  // Open the repo index
  git_index *idx;
  int rc = git_repository_index(&idx, repo);

  if (rc  == 0){
    // add file to index
    rc = git_index_add_bypath(idx, file.c_str());

    if (rc == 0){
      // write index changes to disk
      git_index_write(idx);
      git_index_free(idx);
    }
  }
  printGitError(rc);

  if (rc == 0){
    printf("File %s added to index\n", file.c_str());
    return true;
  }else
    return false;
}
