//
// Created by penta on 2021-02-14.
//

#include "simulator.h"

simulator::ThreadPool::ThreadPool(size_t numthreads) {
    CVJobs = new std::condition_variable();
    MJobs = new std::mutex();
    VectorWorkerThreads.reserve(numthreads);
    for (size_t i = 0; i < numthreads; ++i)
        VectorWorkerThreads.emplace_back(new WorkerThread(CVJobs, MJobs));
}

void simulator::ThreadPool::start1() {
    for (auto t : VectorWorkerThreads) {
        t->run.store(true);
    }
    CVJobs->notify_all();
}

simulator::ThreadPool::~ThreadPool() {
    for (auto t : VectorWorkerThreads) {
        t->stop.store(true);
        t->run.store(false);
    }
    CVJobs->notify_all();
    for (auto t : VectorWorkerThreads) {
        delete t;
    }
    delete CVJobs;
    delete MJobs;
}

simulator::WorkerThread::WorkerThread(std::condition_variable* _CVJobs, std::mutex* _MJobs)
: CVJobs(_CVJobs), MJobs(_MJobs) {
    run.store(false);
    stop.store(false);
    t = new std::thread([this]() { this->worker(); });
}

simulator::WorkerThread::~WorkerThread() {
    stop.store(true);
    t->join();
    delete t;
}

void simulator::WorkerThread::job() { //TODO: Real Action in HERE

}

void simulator::WorkerThread::worker() {
    while (true) {
        std::unique_lock<std::mutex> lock(*MJobs);
        CVJobs->wait(lock, [this]() { return run || stop; });
        if (stop) return;

        job();

        run.store(false);
    }
}

