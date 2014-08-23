#ifndef GITHELPER_H
#define GITHELPER_H

#include "git2.h"
#include <string>
#include <vector>

class GitHelper
{
  public:
    GitHelper();
    bool static gitAddCommit(git_repository *repo,
                             std::string message,
                             std::string filePath,
                             std::string file);
    bool static gitAddCommit(git_repository *repo,
                             std::string message,
                             std::vector<std::string> filePaths,
                             std::vector<std::string> files);
    void static printGitError(int error);
    bool static gitAddFile(git_repository *repo, std::string file);
};

#endif // GITHELPER_H
