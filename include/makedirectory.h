#ifndef MAKEDIRECTORY_H
#define MAKEDIRECTORY_H

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

namespace xiaohai
{
  void GenerateDirectory(const char *resultDirectory)
  {
    mkdir(resultDirectory, 0751);
  }
}

#endif /* MAKEDIRECTORY_H */
