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
        pthread_rwlock_init(&readerLock, nullptr);
    }

    ~CacheElement() {
        pthread_rwlock_destroy(&rwlock);
        pthread_rwlock_destroy(&readerLock);
    }


    bool isFinishReading(ssize_t offset);

    void markFinished();

    bool isFinished() const;

    void initReader(int sock_fd, ssize_t offset);

    std::string readData(ssize_t offset);

    void appendData(const std::string &new_data);

    void clearReader(int sock_fd);


    size_t getReadersCount();

    void makeReadersReadyToWrite(const std::string &uri);

private:
    std::map<int, ssize_t> userBufStates;
    pthread_rwlock_t rwlock{};
    pthread_rwlock_t readerLock{};
    std::string data;
    bool finished{};
};
