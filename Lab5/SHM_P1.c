#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

#define KEY 6
#define BufferSize 100
#define SHMGETFLAG IPC_CREAT
#define SHMATFLAG 0 // R/W

int main()
{
    int shmid = -1;
    void *SHM_Buffer = NULL;
    char String[100] = {0};

    shmid = shmget(KEY, BufferSize, SHMGETFLAG);
    if (shmid == -1)
    {
        printf("Error While Creating Shared Memory ! \n");
        return 0;
    }
    else
    {
        SHM_Buffer = shmat(shmid, NULL, SHMATFLAG);

        while (strcmp("exit", String) != 0)
        {
            printf("Enter Your Message(P1) | exit: ");
            fgets(String, sizeof(String), stdin);
            String[strcspn(String, "\n")] = '\0'; // remove newline
            strcpy((char *)SHM_Buffer, String);
        }
        shmdt(SHM_Buffer); // Deattach after finishing to free the shared memory
    }
}