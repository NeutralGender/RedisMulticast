#ifndef _REDIS_COMMAND
#define _REDIS_COMMAND

#include <string>
#include <array>
#include <map>

#include "hiredis.h"

class RedisConnection;

class RedisCommand
{
private:
    redisReply* reply;
    std::map<std::string,std::string> key_value;

public:
    RedisCommand();
    ~RedisCommand();

    /*
    void Write(RedisConnection* rconnection,
              std::string_view key,
              std::string_view value);
              */

    void Write(RedisConnection* rconnection,
               std::array<char,512>arr);

    void Read(RedisConnection* rconnection,
              std::string_view key);

    void PipelineWrite(RedisConnection* rconnection);
    
    void GetAllData(RedisConnection* rconnection);

};

#endif