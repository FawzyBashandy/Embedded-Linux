#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <strings.h>

int main(int argc, char *argv[])
{
       int createdFD = 0;
       char buffer[12] = {0};
       ssize_t characterRead = 0;
       char flag = 0;                            // 0 -> Capacity , 1 -> Status
       if (strcasecmp("Capacity", argv[1]) == 0) // Equal
       {
              createdFD = open("/sys/class/power_supply/BAT0/capacity", O_RDONLY);
              flag = 0;
       }
       else if (strcasecmp("Status", argv[1]) == 0)
       {
              createdFD = open("/sys/class/power_supply/BAT0/status", O_RDONLY);
              flag = 1;
       }
       else
       {
              printf("Please Enter Correct Argument !");
              return 0;
       }

       if (createdFD == -1)
       {
              printf("Error while creating the file descriptor !"); // This will be output to fd 1
       }
       else
       {
              characterRead = read(createdFD, buffer, sizeof(buffer));
              if (flag == 0)
              {

                     printf("The Battery Percentage is : %s\n", buffer);
              }
              else
              {
                     printf("The Battery Status is : %s\n", buffer);
              }

              sleep(20);

              close(createdFD);
       }
}
