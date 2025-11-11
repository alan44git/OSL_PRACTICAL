#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <ctype.h>
#include <string.h>

struct msg
{
    long msg_type;
    char msg_text[100];
};

int main()
{
    key_t key = ftok(".", 65);
    int msgid = msgget(key, 0666);

    struct msg message;
    msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0);    //  receives message

    // Convert to uppercase
    for (int i = 0; message.msg_text[i] != '\0'; i++)
        message.msg_text[i] = toupper(message.msg_text[i]);

    printf("Received Message (Uppercase): %s\n", message.msg_text);

    msgctl(msgid, IPC_RMID, NULL); // deletes message queue
    return 0;
}