#include "../Include/RedisDriver.h"

RedisDriver::RedisDriver(const std::string& hostname_,
                           const int& port_) 
                         : rconnection(hostname_,port_)
{
}

RedisDriver::~RedisDriver()
{
}

void RedisDriver::Connect()
{
    rconnection.connect();
}

void RedisDriver::Write(std::array<char,512> arr)
{
    r_read.Write(&rconnection, arr);
}

void RedisDriver::Read()
{
    r_read.Read(&rconnection, "key");
}

void RedisDriver::GetAllData()
{
    r_read.GetAllData(&rconnection);
}

void RedisDriver::PipelineWrite()
{
    r_read.PipelineWrite(&rconnection);
}