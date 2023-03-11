### Build Instructions:

 1. Clone the repo: 
 `git clone https://github.com/cjens00/winsock winsock-app`
 2. Change directory into the cloned repo and configure the project with CMake (3.13+):
 `cd winsock-app`
 `cmake .`
 3. Build the project with CMake:
 `cd build`
 `cmake --build ..`

Zero external dependencies, will eventually depend on OpenSSL.
Tested using mingw64/UCRT - gcc 12.2.0 on Windows 11 for amd64.
