#include "assist_network.h"

using namespace Assist::Network;

// =============================================================
// WinSockController Singleton
// =============================================================

WinSockController::WinSockController() : isInitialized_(false), version(0, 0)
{
}

// Returns the WinSockController singleton.
// On first invocation, this member function also initializes it.
WinSockController *WinSockController::getInstance()
{
    std::lock_guard<std::mutex> lock(mutexWinSockController);
    if (pWinSockControllerInstance == nullptr)
    {
        pWinSockControllerInstance = new WinSockController();
    }
    return pWinSockControllerInstance;
}

bool WinSockController::isInitialized() const
{
    return this->isInitialized_;
}

// Start WinSock. Attempts to use version 2.2 if available.
void WinSockController::startWinSock()
{
    WinSockController *pWinSockController = WinSockController::getInstance();
    int status = WSAStartup(MAKEWORD(2, 2), &pWinSockController->wsaData);
    if (!status)
    {
        WinSockController::getInstance()->isInitialized_ = true;
        WinSockController::getInstance()->version = {
            LOBYTE(pWinSockController->wsaData.wVersion),
            HIBYTE(pWinSockController->wsaData.wVersion)};
    }
}

void WinSockController::stopWinSock()
{
    WSACleanup();
    WinSockController::getInstance()->isInitialized_ = false;
    WinSockController::getInstance()->version = {0, 0};
}

std::pair<short, short> WinSockController::getWinSockVersion() const
{
    return WinSockController::getInstance()->version;
}

// =============================================================