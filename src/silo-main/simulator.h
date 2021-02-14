//
// Created by penta on 2021-02-14.
//

#ifndef SILO_GUI_SIMULATOR_H
#define SILO_GUI_SIMULATOR_H

#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <functional>
#include <atomic>

namespace simulator {
    typedef class WorkerThread {
    public:
        explicit WorkerThread(std::condition_variable* CVJobs, std::mutex* MJobs);
        ~WorkerThread();

        std::atomic<bool> run{};
        std::atomic<bool> stop{};

    private:
        void job();

        void worker();
        std::thread* t;

        std::condition_variable* CVJobs;
        std::mutex* MJobs;
    } WorkerThread;


    typedef class ThreadPool {
    public:
        explicit ThreadPool(size_t num_threads);
        ~ThreadPool();
        void start1();

    private:
        std::vector<WorkerThread*> VectorWorkerThreads;

        std::condition_variable* CVJobs;
        std::mutex* MJobs;
    } ThreadPool;
}

#endif //SILO_GUI_SIMULATOR_H
