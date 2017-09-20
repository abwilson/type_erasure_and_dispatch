#pragma once

#include "GatherStats.h"

#include "EOBIWrap.h"

#include <iostream>

void msgLengthError(uint64_t bodyLen, uint64_t msgLen);

template<typename Msg, int tid>
struct MsgReader
{
    static constexpr int id = tid;

    const char* operator()(
        const char* buffer,
        const MessageHeaderCompT& header,
        uint32_t& seqNo) const
    {
        if(header.BodyLen == sizeof(Msg))
        {
            const Msg* msg = reinterpret_cast<const Msg*>(buffer);
            StatsHolder()(msg);
            return buffer + sizeof(Msg);
        }            
        msgLengthError(header.BodyLen, sizeof(Msg));
        return nullptr;
    }
};

struct NullReader
{
    const char* operator()(
        const char* buffer,
        const MessageHeaderCompT& header,
        uint32_t& seqNo) const
    {
        std::cout << "Unknown" << std::endl;
        return buffer;
    }
};
