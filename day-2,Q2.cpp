#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MESSAGE_SIZE 256
#define MESSAGE_TYPE 1

// Structure for the message
struct Message {
    long messageType;
    char messageText[MESSAGE_SIZE];
};

// Function to send a message to the message queue
void sendMessage(int msqid, struct Message *msg) {
    if (msgsnd(msqid, msg, sizeof(struct Message) - sizeof(long), 0) == -1) {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }
}

// Function to receive a message from the message queue
void receiveMessage(int msqid, struct Message *msg) {
    if (msgrcv(msqid, msg, sizeof(struct Message) - sizeof(long), MESSAGE_TYPE, 0) == -1) {
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }
}

int main() {
    key_t key = ftok("message_queue_example", 65);  // Generate a key for the message queue

    // Create a message queue
    int msqid = msgget(key, IPC_CREAT | 0666);
    if (msqid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();  // Fork a new process

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        // Parent process (sender)
        struct Message message;
        message.messageType = MESSAGE_TYPE;

        printf("Enter a message to send to the child process: ");
        fgets(message.messageText, sizeof(message.messageText), stdin);

        // Send the message to the message queue
        sendMessage(msqid, &message);
    } else {
        // Child process (receiver)
        sleep(1);  // Wait for the message to be sent by the parent

        struct Message receivedMessage;

        // Receive the message from the message queue
        receiveMessage(msqid, &receivedMessage);

        // Display the received message
        printf("Message received in the child process: %s", receivedMessage.messageText);
    }

    // Remove the message queue
    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}

