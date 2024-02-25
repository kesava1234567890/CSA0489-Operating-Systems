#include <iostream>
#include <pthread.h>
#include <unistd.h>

// (i) Create Threads
void *printMessage(void *arg) {
    const char *message = static_cast<const char*>(arg);
    std::cout << message << std::endl;
    pthread_exit(NULL);
}

// (ii) Join Threads
void *printNumbers(void *arg) {
    for (int i = 1; i <= 5; ++i) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    pthread_exit(NULL);
}

// (iii) Equal Threads
void *printThreadId(void *arg) {
    std::cout << "Thread ID: " << pthread_self() << std::endl;
    pthread_exit(NULL);
}

// (iv) Exit Threads
void *printThreadIdAndExit(void *arg) {
    std::cout << "Thread ID: " << pthread_self() << std::endl;
    pthread_exit(NULL);
}

int main() {
    // (i) Create Threads
    pthread_t thread1;
    const char *message = "Hello from the thread!";
    pthread_create(&thread1, NULL, printMessage, static_cast<void*>(const_cast<char*>(message)));
    pthread_join(thread1, NULL);

    std::cout << "Main thread continues..." << std::endl << std::endl;

    // (ii) Join Threads
    pthread_t thread2;
    pthread_create(&thread2, NULL, printNumbers, NULL);
    pthread_join(thread2, NULL);

    std::cout << "Main thread continues..." << std::endl << std::endl;

    // (iii) Equal Threads
    pthread_t thread3, thread4;
    pthread_create(&thread3, NULL, printThreadId, NULL);
    pthread_create(&thread4, NULL, printThreadId, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);

    std::cout << "Main thread continues..." << std::endl << std::endl;

    // (iv) Exit Threads
    pthread_t thread5;
    pthread_create(&thread5, NULL, printThreadIdAndExit, NULL);
    pthread_join(thread5, NULL);

    std::cout << "Main thread continues..." << std::endl;

    return 0;
}

