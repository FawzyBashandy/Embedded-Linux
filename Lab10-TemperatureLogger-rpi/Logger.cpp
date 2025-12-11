#include "Logger.hpp"

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

Logger::Logger(std::string filePath)
    : logFile_{open(filePath.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644)} {
  if (logFile_ == -1) {
    std::perror("File Couldn't be opened");
  }
}
void Logger::logTemperature(std::weak_ptr<TemperatureData> receivedTemp) {
  std::shared_ptr<TemperatureData> data;
  if(!receivedTemp.expired())
  {
    data = receivedTemp.lock();
  }
  else
  {
    std::perror("No Temperature Received");
    return;
  }
  std::string temperatureString = std::to_string(data->getTimeStamp()) + " : " +
                                  std::to_string(data->getTemperature()) +
                                  " °C\n";

  if (write(logFile_, temperatureString.c_str(), temperatureString.size()) ==
      -1) {
    std::perror("Write Operation On logfile Failed");
  } else {
  }
}

void Logger::changeLogFile(std::string filePath) {

  int newFD = open(filePath.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644);
  if (newFD == -1) {
    std::perror("File Couldn't be opened");
    return;
  }

  close(logFile_);
  logFile_ = newFD;
}

Logger::~Logger() {
  if (logFile_ != -1)
    close(logFile_);
}