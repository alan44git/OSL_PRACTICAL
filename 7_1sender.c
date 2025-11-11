#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct msg
{
    long msg_type;
    char msg_text[100];
};

int main()
{
    key_t key = ftok(".", 65); // generates a unique key
    int msgid = msgget(key, 0666 | IPC_CREAT);  //  creates a message queue

    struct msg message;
    printf("Enter message to send: ");
    fgets(message.msg_text, sizeof(message.msg_text), stdin);

    message.msg_type = 1; // type = 1 for all messages

    msgsnd(msgid, &message, sizeof(message.msg_text), 0);   //  sends message
    printf("Message sent to queue.\n");

    return 0;
}