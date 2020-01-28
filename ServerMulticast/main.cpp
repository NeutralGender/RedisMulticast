#include <iostream>

#include "Include/MulticastServer.h"
#include "Include/ReceiveSocket.h"
#include "Include/SendSocket.h"
#include "Include/RedisDriver.h"

int main()
{
    // DB object
    RedisDriver redis("127.0.0.1", 6379);

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
    
    MulticastServer m;
    m.ConnectToDb(&redis);

    while(true)
    {
        m.ReceiveMsg(&receive);
        //m.GetAllData(&redis);
        //m.PipelineWrite(&redis);
        m.WriteToDB(&redis);
        m.SendMsg(&send);
        //m.ReadFromDB(&redis);
        //m.GetAllData(&redis);
    }

    return 0;
}

// g++ -std=c++17 main.cpp -I Include/ 
// -I /root/Downloads/hiredis-0.14.0/ 
// Src/*.cpp
// -lhiredis 
// -o main