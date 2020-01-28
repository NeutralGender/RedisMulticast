
#ifndef _MulticastServer
#define _MulticastServer

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#include <string.h>
#include <array>

class Driver;
class ReceiveSocket;
class SendSocket;

class MulticastServer
{
private:
    std::array<char,512> arr;
public:
    MulticastServer();
    ~MulticastServer();

    void ReceiveMsg(ReceiveSocket* receive);
    void SendMsg(SendSocket* send);
    void ConnectToDb(Driver *db_driver);
    void WriteToDB(Driver *db_driver);
    void GetAllData(Driver *db_driver);
    void PipelineWrite(Driver *db_driver);
    void ReadFromDB(Driver *db_driver);
};




#endif