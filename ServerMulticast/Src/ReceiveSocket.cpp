#include "../Include/ReceiveSocket.h"

ReceiveSocket::ReceiveSocket(const std::string local_addr_,
                             const std::string group_addr_,
                             const int& port_)
                          :  local_addr(local_addr_),
                             group_addr(group_addr_),
                             port(port_)
{
}

ReceiveSocket::~ReceiveSocket()
{
    close(sockfd);
}

void ReceiveSocket::Create_Socket()
{
    try
    {
        if( ( sockfd = socket(AF_INET,SOCK_DGRAM,0) ) < 0 )
            throw std::runtime_error("Cannot Create Socket");
        
        bzero(&local,sizeof(local));
        local.sin_family = AF_INET;
        local.sin_port = htons(port);
        local.sin_addr.s_addr = INADDR_ANY;

    }
    catch(const std::runtime_error& r)
    {
        std::cerr << r.what() << ": " << errno << '\n';
    }
}

void ReceiveSocket::SetReuseAddr()
{
    try
    {
        int reuse = 1;
        if( ( setsockopt(sockfd,
                         SOL_SOCKET,
                         SO_REUSEADDR,
                         static_cast<void*>(&reuse),
                         sizeof(reuse)
                         )  ) < 0 )
            throw std::runtime_error("Cannot set REUSEADDR setsockopt()");
    }
    catch(const std::runtime_error& r)
    {
        std::cerr << r.what() << ": " << errno << '\n';
        close(sockfd);
    }
}

void ReceiveSocket::Bind()
{
    try
    {
        if( bind(sockfd, 
                (struct sockaddr*)&local,
                 sizeof(local)
                )  < 0 )
            throw std::runtime_error("Cannot Bind Socket");
    }
    catch(const std::runtime_error& r)
    {
        std::cerr << r.what() << ": " << errno << '\n';
        close(sockfd);
    }
}

void ReceiveSocket::JoinToGroup()
{
    try
    {
        // multicast group interface
        group.imr_multiaddr.s_addr = inet_addr(group_addr.c_str());

        // local interface
        group.imr_interface.s_addr = htonl(INADDR_ANY);

        if( ( setsockopt(sockfd,
                         IPPROTO_IP,
                         IP_ADD_MEMBERSHIP,
                         static_cast<void*>(&group),
                         sizeof(group)
                        ) 
            ) < 0 )
            throw std::runtime_error("Cannot JoinToGroup");
    }
    catch(const std::runtime_error& r)
    {
        std::cout << r.what() << ": " << errno << '\n';
        close(sockfd);
    }
}