#include <fcntl.h>
#include <initializer_list>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

#include "FileActions.hpp"
// Constructor
FileActions::FileActions(const std::string &path)
    : fd(new int(-1)), fdRef_(fd),
      actions_() // reference MUST be initialized here
{
  *fd = open(path.c_str(), O_RDWR | O_CREAT, 0644);
  if (*fd == -1) {
    std::cout << "ERROR: File Cann't be Opened!"
              << "\n";
  }
}

FileActions::FileActions(const FileActions &other)
    : fd(new int(*(other.fd))), fdRef_(fd),
      actions_(other.actions_) // copy actions list
{}

// Register actions
void FileActions::registerActions(
    std::initializer_list<std::pair<std::string, int>> list) {
  actions_.assign(list.begin(), list.end()); // COPY into vector
}

void FileActions::executeActions() {
  char buffer[256];

  for (auto &action : actions_) {
    const std::string &cmd = action.first;
    int param = action.second;

    if (cmd == "Read") {
      lseek(*fd, 0, SEEK_SET); // RESET POSITION
      int r = read(*fd, buffer, param);
      if (r > 0) {
        buffer[r] = '\0'; // null-terminate
        std::cout << buffer;
        std::cout << "\n";
      }
    } else if (cmd == "Write") {
      std::string msg(param, 'X'); // write param number of 'X'
      write(*fd, msg.c_str(), msg.size());
    } else if (cmd == "Close") {
      close(*fd);
    }
  }
}

FileActions::~FileActions() {
  delete fd;
  fd = nullptr;
}
