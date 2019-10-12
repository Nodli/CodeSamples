#include "TaskPool.h"

TaskPool::TaskPool(int nthreads)
:terminate(false), working_threads(0){

    // NOTE(hugo): The mutex is locked while the condition variable predicate is checked
    auto workers_cv_wait = [this](){
        return !tasks.empty() || terminate;
    };
    auto thread_spin = [this, workers_cv_wait](){
        while(true){
            Task task;

            {
                std::unique_lock worker_lock(tasks_mutex);
                workers_cv.wait(worker_lock, workers_cv_wait);

                // NOTE(hugo): The termination only happens after all the enqueued tasks have been executed
                if(terminate && tasks.empty()){
                    return;
                }

                ++working_threads;
                task = std::move(tasks.front());
                tasks.pop();
            }

            task.task();
            --working_threads;
            synctask_cv.notify_all();

            if(task.closure){
                std::scoped_lock closure_lock(closures_mutex);
                closures.push(task.closure);
            }
        }
    };

    for(int ithread = 0; ithread != nthreads; ++ithread){
        workers.emplace_back(thread_spin);
    }
}

TaskPool::~TaskPool(){
    terminate = true;
    workers_cv.notify_all();
    for(int ithread = 0; ithread != workers.size(); ++ithread){
        workers[ithread].join();
    }
    ExecuteClosures();
}

void TaskPool::EnqueueTask(std::function<void()> task, std::function<void()> closure){
    tasks_mutex.lock();
    tasks.push({task, closure});
    tasks_mutex.unlock();

    workers_cv.notify_one();
}

int TaskPool::CountTasks(){
    std::scoped_lock tasks_lock(tasks_mutex);
    return tasks.size();
}

int TaskPool::CountClosures(){
    std::scoped_lock closures_lock(closures_mutex);
    return closures.size();
}

void TaskPool::SynchronizeTasks(){
    auto synchronize_cv_wait = [this](){
        return tasks.empty() && working_threads == 0;
    };

    std::unique_lock synctask_lock(tasks_mutex);
    synctask_cv.wait(synctask_lock, synchronize_cv_wait);
}

void TaskPool::ExecuteClosures(){
    closures_mutex.lock();
    while(!closures.empty()){
        std::function<void()> closure = std::move(closures.front());
        closures.pop();
        closures_mutex.unlock();

        closure();

        closures_mutex.lock();
    }
    closures_mutex.unlock();
}
