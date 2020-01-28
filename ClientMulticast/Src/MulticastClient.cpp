#include "../Include/MulticastClient.h"
#include "../Include/SendSocket.h"
#include "../Include/ReceiveSocket.h"

MulticastClient::MulticastClient()
{

}

MulticastClient::~MulticastClient()
{
    
}

void MulticastClient::Sendto(SendSocket *send)
{
    try
    {
        std::cin.getline(arr.data(),512);
        
        int valid = 0;
        if( ( valid = sendto( send->sockfd,
                      arr.data(),
                      arr.size(),
                      0,
                      (struct sockaddr*)&send->group,
                      sizeof(send->group) 
                    ) 
            ) < 0 )
            throw std::runtime_error("Cannot Read Socket");

    }
    catch(const std::runtime_error& r)
    {
        std::cerr << r.what() << ": " << errno << '\n';
    }
}

void MulticastClient::ReceiveFrom(ReceiveSocket *receive)
{
    try
    {
        int valid = 0;
        std::string str = "";
        if( ( valid = read( receive->sockfd, arr.data(), arr.size() ) ) < 0 )
            throw std::runtime_error("Cannot Read Socket");

        //std::cout << "ValidR: " << valid << std::endl;
        std::cout << "Received:" << arr.data() << std::endl;
    }
    catch(const std::runtime_error& r)
    {
        std::cerr << r.what() << ": " << errno << '\n';
    }
}