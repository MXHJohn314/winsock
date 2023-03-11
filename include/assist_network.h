#pragma once

// To prevent WinSock ver 1.x / <WinSock.h> from being pulled in
#ifndef ASSIST_NETWORK_H
#define ASSIST_NETWORK_H

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN

// Windows/Win32 API
#include <Windows.h>

// Windows Sockets 2
#include <WinSock2.h>
#include <WS2tcpip.h>

// C++ STL Headers
#include <mutex>
#include <string>
#include <utility>

// C Headers
#include <cstdlib>
#include <cstdio>

// The classes and functions contained within Assist::Network are meant
// to provide a more accessible interface for Windows Socket programming.
// Includes helper functions to determine the initialization status of WinSock2,
// the version number, IPv6 support status, socket creation,
// and crypto/security function helpers using OpenSSL.
namespace Assist::Network
{
    class WinSockController;
    static std::mutex mutexWinSockController;
    static WinSockController *pWinSockControllerInstance = nullptr;

    class WinSockController
    {
    protected:
        bool isInitialized_;
        std::pair<short, short> version;
        WSADATA wsaData;
        WinSockController();

    public:
        WinSockController(WinSockController &other) = delete;
        void operator=(const WinSockController &) = delete;

        static WinSockController *getInstance();
        bool isInitialized() const;
        void startWinSock();
        void stopWinSock();
        std::pair<short, short> getWinSockVersion() const;
    };

    // Free Functions

}

#endif
#endif