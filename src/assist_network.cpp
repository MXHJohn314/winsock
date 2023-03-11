#include "assist_network.h"

using namespace Assist::Network;

// =============================================================
// WinSockController Singleton
// =============================================================
// This class provides a singleton interface for initializing and cleaning up the WinSock API.
class WinSockController {
public:
    // Constructor - initializes the WinSockController instance
    WinSockController() : isInitialized_(false), version(0, 0) {}

    // Returns the WinSockController singleton.
    // On first invocation, this function also initializes it.
    static WinSockController* getInstance() {
        // Use a lock to ensure that only one thread can create the singleton instance at a time
        std::lock_guard<std::mutex> lock(mutexWinSockController);

        if (pWinSockControllerInstance == nullptr) {
            // Create a new instance if one doesn't already exist
            pWinSockControllerInstance = new WinSockController();
        }
        return pWinSockControllerInstance;
    }

    // Returns true if the WinSock API has been initialized, false otherwise.
    bool isInitialized() const {
        return this->isInitialized_;
    }

    // Initializes the WinSock API. Attempts to use version 2.2 if available.
    void startWinSock() {
        WinSockController *pWinSockController = WinSockController::getInstance();
        // Use the WSAStartup function to initialize the WinSock API
        int status = WSAStartup(MAKEWORD(2, 2), &pWinSockController->wsaData);

        if (!status) {
            // Set the isInitialized_ flag and version number if initialization succeeds
            WinSockController::getInstance()->isInitialized_ = true;
            WinSockController::getInstance()->version = {
                LOBYTE(pWinSockController->wsaData.wVersion),
                HIBYTE(pWinSockController->wsaData.wVersion)};
        }
    }

    // Cleans up the WinSock API.
    void stopWinSock() {
        // Use the WSACleanup function to release any resources used by the WinSock API
        WSACleanup();
        // Reset the isInitialized_ flag and version number
        WinSockController::getInstance()->isInitialized_ = false;
        WinSockController::getInstance()->version = {0, 0};
    }

    // Returns the WinSock version as a pair of integers representing the major and minor version numbers.
    static std::pair<short, short> getWinSockVersion() {
        return WinSockController::getInstance()->version;
    }

std::pair<short, short> WinSockController::getWinSockVersion() const
{
    return WinSockController::getInstance()->version;
}

private:
    // Private member variables
    bool isInitialized_;        // Flag indicating whether the WinSock API has been initialized
    std::pair<short, short> version;  // The WinSock version as a pair of integers

    // Private constructor and copy constructor to prevent multiple instances
    WinSockController(const WinSockController&) = delete;
    WinSockController& operator=(const WinSockController&) = delete;

    // Private static member variables
    static WinSockController* pWinSockControllerInstance; // The singleton instance of the WinSockController class
    static std::mutex mutexWinSockController;             // A mutex to synchronize access to the singleton instance
};

// Initialize the static member variables
WinSockController* WinSockController::pWinSockControllerInstance = nullptr;
std::mutex WinSockController::mutexWinSockController;


// This code is likely part of a larger network-related project and provides a convenient interface for initializing and cleaning up the WinSock API.
// =============================================================
