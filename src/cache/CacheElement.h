#pragma once

#include <string>
#include <map>
#include <mutex>
#include <vector>
#include <sys/poll.h>
#include <shared_mutex>

class CacheElement {
public:
    CacheElement() {
        pthread_rwlock_init(&rwlock, nullptr);
        pthread_rwlock_init(&readerlock, nullptr);
    }

    ~CacheElement() {
        pthread_rwlock_destroy(&rwlock);
        pthread_rwlock_destroy(&readerlock);
    }


    bool isFinishReading(int sock_fd);

    void markFinished();

    bool isFinished() const;

    void initReader(int sock_fd);

    std::string readData(int sock_fd);

    void appendData(const std::string &new_data);

    void clearReader(int sock_fd);


    size_t getReadersCount();

    void makeReadersReadyToWrite(std::vector <pollfd> &fds);

private:
    std::map<int, ssize_t> userBufStates;
    pthread_rwlock_t rwlock{};
    pthread_rwlock_t readerlock{};
    std::string data;
    bool finished{};

};