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
    char String[BufferSize] = {0};
    char PrevString[BufferSize] = {0};

    shmid = shmget(KEY, BufferSize, SHMGETFLAG);
    if (shmid == -1)
    {
        printf("Error While Creating Shared Memory ! \n");
        return 0;
    }
    else
    {
        SHM_Buffer = shmat(shmid, NULL, SHMATFLAG);
        printf("Waiting for messages From (P1) ...\n");
        while (1)
        {
            strcpy(String, (char *)SHM_Buffer);

            if (strcmp(String, PrevString) != 0)
            {
                printf("(P1) is telling you (P2) : %s\n", String);
                strcpy(PrevString, String); // update previous message
                if (strcmp(String, "exit") == 0)
                    break;
            }
        }
        shmdt(SHM_Buffer); // Deattach after finishing to free the shared memory
    }
}