#ifndef _DRIVER
#define _DRIVER

#include <array>

// Abstract Class for DBs
class Driver
{
public:
    virtual void Connect() = 0;
    virtual void Read() = 0;
    virtual void GetAllData() = 0;
    virtual void PipelineWrite() = 0;
    virtual void Write(std::array<char,512>) = 0; 
};

#endif