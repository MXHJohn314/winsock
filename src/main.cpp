// STL Headers
#include <iostream>

// C Headers
#include <cstdio>

// Project headers
#include "assist_network.h"

using Assist::Network::WinSockController;

int main()
{
    bool isWinSockInitialized;
    std::pair<short, short> wsVersion;
    WinSockController *wsController;

    wsController = WinSockController::getInstance();
    wsController->startWinSock();
    isWinSockInitialized = wsController->isInitialized();
    
    if (isWinSockInitialized)
    {
        printf("WinSock initialization success.\n");
        wsVersion = wsController->getWinSockVersion();
        printf("WinSock version: %d.%d\n", wsVersion.first, wsVersion.second);
    }
    else {
        printf("WinSock failed to initialize.\n");
    }

    wsController->stopWinSock();
    printf("WinSock stopped.\n");

    return 0;
}