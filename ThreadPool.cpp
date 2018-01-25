#include <unistd.h>
#include "ThreadPool.h"

/**
 * Constructor.
 * @param threadsNum The number of threads.
 */
ThreadPool::ThreadPool(int threadsNum) : threadsNum(threadsNum), stopped(false) {
    //create array of threads.
    threads = new pthread_t[threadsNum];
    //loop of the threads.
    for (int i = 0; i < threadsNum; i++) {
        //create thread.
        pthread_create(threads + i, NULL, execute, this);
    }
    pthread_mutex_init(&lock, NULL);
}

void *ThreadPool::execute(void *arg) {
    ThreadPool *pool = (ThreadPool *) arg;
    pool->executeTasks();
}

int ThreadPool::getThreadsNum() {
    return threadsNum;
}

void ThreadPool::addTask(Task *task) {
    tasksQueue.push(task);
}

void ThreadPool::executeTasks() {
    //while loop not stopped.
    while (!stopped) {
        pthread_mutex_lock(&lock);
        //check the queue is not empty.
        if (!tasksQueue.empty()) {
            //get task.
            Task *task = tasksQueue.front();
            //remove the tasks from queue.
            tasksQueue.pop();
            pthread_mutex_unlock(&lock);
            //execute the task.
            task->execute();
        } else {
            //sleep for 1 sec and check for new task.
            pthread_mutex_unlock(&lock);
            sleep(1);
        }
    }
}

/**
 * Stop the loop of threads.
 */
void ThreadPool::terminate() {
    pthread_mutex_destroy(&lock);
    stopped = true;
}

/**
 * Destructor.
 */
ThreadPool::~ThreadPool() {
    delete[] threads;
}