#include <iostream>

#include "Include/MulticastClient.h"
#include "Include/ReceiveSocket.h"
#include "Include/SendSocket.h"

int main()
{
    // ReceiveSocket receive( "local", "group", port );
    ReceiveSocket receive("9.5.1.1", "225.1.1.1", 8000);
    receive.Create_Socket();
    receive.SetReuseAddr();
    receive.Bind();
    receive.JoinToGroup();

    // SendSocket send( "local", "group", port );
    SendSocket send( "9.5.1.1", "225.1.1.1", 8000 );
    send.Create_Socket();
    send.SetSockLoop();
    send.SetOutInterface();
    
    MulticastClient m;
    while(true)
    {
        m.Sendto(&send);
        m.ReceiveFrom(&receive);
    }

    return 0;
}

// g++ -std=c++17 main.cpp -I Include/ 
// -I /root/Downloads/hiredis-0.14.0/ 
// Src/*.cpp
// -lhiredis 
// -o main