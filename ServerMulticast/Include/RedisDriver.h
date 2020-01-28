#ifndef _REDIS_DRIVER
#define _REDIS_DRIVER

#include "Driver.h"
#include "RedisConnection.h"
#include "RedisCommand.h"

#include <array>

class Driver;

class RedisDriver : public Driver
{
private:
    RedisConnection rconnection;
    RedisCommand r_read;

public:
    RedisDriver(const std::string& hostname,
                const int& port);
    ~RedisDriver();

    virtual void Connect() override;
    virtual void Read() override;
    virtual void GetAllData() override;
    virtual void PipelineWrite() override;
    virtual void Write(std::array<char,512>) override;
};

#endif