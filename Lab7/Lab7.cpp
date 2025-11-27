#include <fcntl.h>
#include <initializer_list>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <utility>

class CapsLock {
private:
  std::string path;
  int fd;

public:
  CapsLock() {
    path = "/home/fawzybashandy/fooz.txt";
    fd = open(path.c_str(), O_WRONLY);
  }
  CapsLock(std::string path) {
    this->path = path;
    fd = open(path.c_str(), O_WRONLY);
  }
  void CapsLockOn() { write(fd, "1", 1); }
  ~CapsLock() { close(fd); }
};

int main() {
  std::string s1 = "/home/fawzybashandy/fooz.txt";
  CapsLock fooz(s1);
  fooz.CapsLockOn();
}
