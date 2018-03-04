#ifndef BLOCK_DELAY_HPP
#define BLOCK_DELAY_HPP

#include "cfe.h"
#include <math/Vector10F.hpp>

namespace delay
{

class BlockDelay10FLEN10
{
private:
    static const int LEN = 10;
    uint8 m_Index;
    int m_Delay;
    math::Vector10F m_Storage[LEN];
    

public:
    BlockDelay10FLEN10();
    ~BlockDelay10FLEN10();
    math::Vector10F Update(const math::Vector10F &input);
    void Initialize(void);
    math::Vector10F Get(uint8 delay);

protected:

};


class BlockDelayUINT64LEN10
{
private:
    static const int LEN = 10;
    uint8 m_Index;
    int m_Delay;
    uint64 m_Storage[LEN];
    

public:
    BlockDelayUINT64LEN10();
    ~BlockDelayUINT64LEN10();
    uint64 Update(const uint64 &input);
    void Initialize(void);
    uint64 Get(uint8 delay);

protected:

};

}

#endif
