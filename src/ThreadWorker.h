#pragma once


#include <thread>
#include <vector>
#include <sys/poll.h>
#include "cache/Storage.h"
#include "helpers/HttpParser.h"
#include "ClientInfo.h"

class ThreadWorker {
public:
    explicit ThreadWorker(Storage &storage);

    void addPipe(int writeEnd);
    void transferInfo(ClientInfo *info);

private:
    std::vector<pollfd> fds;
    std::thread thread;
    Storage &storage;


    int addPipeFd[2]{};
    int transferPipeFd[2]{};

    void worker();

    std::map<int, std::string> serverSocketsURI;
    std::map<int, ClientInfo*> clientInfo;
    std::map<int, std::string> clientBuffersMap;

    bool handleClientConnection(pollfd &pfd);

    bool handleReadDataFromServer(pollfd &pfd);


    bool handleClientInput(pollfd &pfd);

    bool handleClientReceivingResource(pollfd &pfd);

    void readClientInput(int fd);


    void handlePipeMessages();

    void storeClientConnection(int fd, short int events);

    ssize_t eraseFDByIndex(ssize_t &i);



    void storeInfo(ClientInfo* info);

    void cleanClientInfo(const pollfd &pfd);
};