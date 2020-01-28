#include "../Include/RedisCommand.h"
#include "../Include/RedisConnection.h" // Must be included, because of incomplete class
                                        // (class in another file)

RedisCommand::RedisCommand()
{

}

RedisCommand::~RedisCommand()
{
    freeReplyObject(reply);
}

void RedisCommand::PipelineWrite(RedisConnection* rconnection)
{
    // REDIS_OK = 0;
    // REDIS_ERR = -1;
    int appednState = -1;

    // Filling UP the output buffer
    for(auto it = key_value.cbegin(); it != key_value.cend(); it++ )
    {
        appednState = (redisAppendCommand(rconnection->rconnect,
                                          "SET %s %s", 
                                          it->first.data(), 
                                          it->second.data()
                                         )
                      );
    }

    // Retrieve the reply
    for(auto it = key_value.cbegin(); it != key_value.cend(); it++ )
    {
        appednState = redisGetReply(rconnection->rconnect,
                                    reinterpret_cast<void**>(&reply)
                                   );

        if(appednState == REDIS_ERR)
            std::cout << "Error: " << it->first << std::endl;
        
        freeReplyObject(reply);
    }

}

void RedisCommand::Write(RedisConnection* rconnection, 
                     std::array<char ,512> arr)
{
    try
    {
        reply = static_cast<redisReply*>(redisCommand(rconnection->rconnect,
                                                      arr.data()
                                                     )
                                        );
        
        std::cout << reply->str << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

}

void RedisCommand::Read(RedisConnection* rconnection, 
                        std::string_view key)
{
    try
    {
        reply = static_cast<redisReply*>(redisCommand(rconnection->rconnect,
                                                      "GET key0",
                                                      key.data()
                                                     )
                                        );
        std::cout << "ReadData: " << reply->str << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

}

void RedisCommand::GetAllData(RedisConnection* rconnection)
{
    try
    {
        reply = static_cast<redisReply*>(redisCommand(rconnection->rconnect,
                                                      "KEYS *"));
        redisReply *temp;
        for( size_t i = 0; i < reply->elements; i++ )
        {
            temp = static_cast<redisReply*>(redisCommand(rconnection->rconnect,
                                                         "GET %s",reply->element[i]->str));

            key_value.try_emplace(reply->element[i]->str,temp->str);
            //std::cout << reply->element[i]->str << " -> " << temp->str << std::endl;
            freeReplyObject(temp);
        }  
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}