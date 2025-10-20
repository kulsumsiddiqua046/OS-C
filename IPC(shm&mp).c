#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#define MAX 100
struct msg_buffer
{
  long msg_type;
char msg_text[MAX];
}
message;
int main()
{
  key_t key;
int msg_id;
key=ftok("prog file",65);
msg_id=msgget(key,0666/IPC_CREAT);
message.msg_type=1;
printf("Enter message:");
fgets(message.msg_text,MAX,stdin);
msgsnd(msg_id,&message,sizeof(mesaage),0);
printf("message sent:%s\n",message.msg_text);
msgrcv(msg_id,&message,sizeof(message),1,0);
printf("message recieved:%s\n",message.msg_text);
msgctl(msg_id,IPC_RMID,NULL);
return 0;
}