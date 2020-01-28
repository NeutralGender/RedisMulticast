#include "../Include/MulticastServer.h"
#include "../Include/Driver.h"
#include "../Include/SendSocket.h"
#include "../Include/ReceiveSocket.h"

MulticastServer::MulticastServer()
{

}

MulticastServer::~MulticastServer()
{

}

void MulticastServer::ReceiveMsg(ReceiveSocket* receive)
{
    try
    {
        int valid = 0;
        if( ( valid = read( receive->sockfd, arr.data(), arr.size() ) ) < 0 )
            throw std::runtime_error("Cannot Read Socket");

        std::cout << arr.data() << std::endl;
    }
    catch(const std::runtime_error& r)
    {
        std::cerr << r.what() << ": " << errno << '\n';
    }
}

void MulticastServer::SendMsg(SendSocket* send)
{
    try
    {
        int valid = 0;
        if( ( valid = sendto( send->sockfd,
                      arr.data(),
                      arr.size(),
                      0,
                      (struct sockaddr*)&send->group,
                      sizeof(send->group) 
                    ) 
            ) < 0 )
            throw std::runtime_error("Cannot Write Socket");

        //std::cout << "Valid Send: " << valid << std::endl;

        arr.fill(0);
    }
    catch(const std::runtime_error& r)
    {
        std::cerr << r.what() << ": " << errno << '\n';
    }
}

void MulticastServer::WriteToDB(Driver *db_driver)
{
    db_driver->Write(arr);
}

void MulticastServer::ConnectToDb(Driver *db_driver)
{
    db_driver->Connect();
}

void MulticastServer::ReadFromDB(Driver *db_driver)
{
    db_driver->Read();
}

void MulticastServer::GetAllData(Driver *db_driver)
{
    db_driver->GetAllData();
}

void MulticastServer::PipelineWrite(Driver *db_driver)
{
    db_driver->PipelineWrite();
}