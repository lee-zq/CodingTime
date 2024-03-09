#include <condition_variable>
#include <mutex>
#include <thread>
#include <vector>
#include <random>
#include <queue>
#include <time.h>
#include <chrono>
#include <unistd.h>
#include "stdio.h"

class Task{
public:
    Task(int a, int b){
        a_ = a;
        b_ = b;
    }
    int sum(int thread_idx){
        int c = a_ + b_;
        usleep(1000*100);
        printf("%d + %d = %d, computed with thread:%d\n", a_, b_, c, thread_idx);
        return 0;
    }
private:
    int a_;
    int b_;
};

class ThreadPool
{
private:
    int thread_num_;
    bool stop_;
    std::vector<std::thread> workers_;
    std::mutex mutex_;
    std::condition_variable cond_;
    std::queue<Task> task_queue_;

public:
    ThreadPool(int thread_num)
    {
        thread_num_ = thread_num;
        stop_ = false;
        for (int idx = 0; idx < thread_num_; idx++)
        {
            workers_.emplace_back([this, idx] {
                Task task(0,0);
                while (1)
                {
                    {
                        std::unique_lock<std::mutex> lock(this->mutex_);
                        cond_.wait(lock, [this]() { return this->stop_ || this->task_queue_.size() > 0; });
                        if (this->stop_ && this->task_queue_.size()==0)
                            return;
                        task = std::move(task_queue_.front());
                        task_queue_.pop();
                    }
                    task.sum(idx);
                }
            });
        }
    }

    void submit(Task task)
    {
        std::unique_lock<std::mutex> lock(this->mutex_);
        task_queue_.push(task);
        cond_.notify_all();
    }

    ~ThreadPool(){
        {
            std::unique_lock<std::mutex> lock(this->mutex_);
            stop_ = true;
        }
        for (auto& it : workers_){
            if (it.joinable())
                it.join();
        }
    }
};


int main(){
    srand(2023);
    ThreadPool pool(4);
    while(1){
        int a = rand() % 100;
        int b = rand() % 100;
        pool.submit(Task(a, b));
    }
    return 0;
}