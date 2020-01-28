
#ifndef _MulticastClient
#define _MulticastClient

#include <iostream>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#include <string.h>
#include <array>

///
#include <fstream>
#include <vector>
///

class Driver;
class ReceiveSocket;
class SendSocket;

class MulticastClient
{
private:
    std::array<char,512> arr;
public:
    MulticastClient();
    ~MulticastClient();

    void ReceiveFrom(ReceiveSocket* receive);
    void Sendto(SendSocket* send);
};




#endif