#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <stdlib.h>
int main()
{
  key_t key=ftok("shmfile",65);
int shmid=shmget(key,1024,0666|IPC_CREAT);
char*str=(char*)shmat(shmid,(void*)0,0);
printf("write data:");
fgets(str,1024,stdin);
printf("Data Written in Memory:%s\n",str);
shmdt(str);
str=(char*)shmat(shmid,(void*)0,0);
printf("Data read from memory:%s\n",str);
shmdt(str);
shmctl(shmid,IPC_RMID,NULL);
return 0;
}
