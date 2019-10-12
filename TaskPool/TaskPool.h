#pragma once

#include <functional>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <thread>
#include <atomic>

struct TaskPool{
private:
    // NOTE(hugo): task is executed by the worker thread
    //             on_complete can be executed by the main thread when task is done using ExecuteClosures
    struct Task{
        std::function<void()> task;
        std::function<void()> closure;
    };

public:

    TaskPool(int nthreads);
    ~TaskPool();

    // NOTE(hugo): closure = std::function<void()>() can be used to enqueue an empty function
    void EnqueueTask(std::function<void()> task, std::function<void()> closure = nullptr);

    bool isTasksEmpty();
    bool isClosuresEmpty();

    int CountTasks();
    int CountClosures();

    void SynchronizeTasks();
    void ExecuteClosures();

private:

    void EnqueueTask(Task& task);

    std::mutex tasks_mutex;
    std::queue<Task> tasks;

    std::mutex closures_mutex;
    std::queue<std::function<void()>> closures;

    std::condition_variable workers_cv;
    std::vector<std::thread> workers;

    std::condition_variable synctask_cv;

    std::atomic<bool> terminate;
    std::atomic<int> working_threads;
};
