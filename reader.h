#pragma once

#include "EOBILayouts.h"
#ifdef CONTIGUOUS_TIDS
#  include "ContiguousTIDs.h"
#endif

#include "TickCounter.h"
#include "GatherStats.h"

#include <iostream>
#include <fstream>
#include <vector>

template<template<typename...> class Dispatcher,
         typename Default,
         template<typename, int> class Handler>
using ReaderT = Dispatcher<
    const char* (const char*,
                 const MessageHeaderCompT& header,
                 uint32_t& seqNo),
    Default,
    Handler<AddComplexInstrumentT,  TID_ADD_COMPLEX_INSTRUMENT>,  // 13400
    Handler<AuctionBBOT,            TID_AUCTION_BBO>,             // 13500
    Handler<AuctionClearingPriceT,  TID_AUCTION_CLEARING_PRICE>,  // 13501
    Handler<CrossRequestT,          TID_CROSS_REQUEST>,           // 13502
    Handler<ExecutionSummaryT,      TID_EXECUTION_SUMMARY>,       // 13202
    Handler<FullOrderExecutionT,    TID_FULL_ORDER_EXECUTION>,    // 13104
    Handler<HeartbeatT,             TID_HEARTBEAT>,               // 13001
    Handler<InstrumentStateChangeT, TID_INSTRUMENT_STATE_CHANGE>, // 13301
    Handler<InstrumentSummaryT,     TID_INSTRUMENT_SUMMARY>,      // 13601
    Handler<OrderAddT,              TID_ORDER_ADD>,               // 13100
    Handler<OrderDeleteT,           TID_ORDER_DELETE>,            // 13102
    Handler<OrderMassDeleteT,       TID_ORDER_MASS_DELETE>,       // 13103
    Handler<OrderModifyT,           TID_ORDER_MODIFY>,            // 13101
    Handler<OrderModifySamePrioT,   TID_ORDER_MODIFY_SAME_PRIO>,  // 13106
    Handler<PacketHeaderT,          TID_PACKET_HEADER>,           // 13002
    Handler<PartialOrderExecutionT, TID_PARTIAL_ORDER_EXECUTION>, // 13105
    Handler<ProductStateChangeT,    TID_PRODUCT_STATE_CHANGE>,    // 13300
    Handler<ProductSummaryT,        TID_PRODUCT_SUMMARY>,         // 13600
    Handler<QuoteRequestT,          TID_QUOTE_REQUEST>,           // 13503
    Handler<SnapshotOrderT,         TID_SNAPSHOT_ORDER>,          // 13602
    Handler<TopOfBookT,             TID_TOP_OF_BOOK>,             // 13504
    Handler<TradeReportT,           TID_TRADE_REPORT>,            // 13201
    Handler<TradeReversalT,         TID_TRADE_REVERSAL>>;         // 13200

inline std::string readTicks()
{
    std::string buffer;
    buffer.reserve(100 * 1000 *1000);

    buffer.assign(
        (std::istreambuf_iterator<char>(std::cin)),
        std::istreambuf_iterator<char>());

    std::cout << "bytes read: " << buffer.size()
              << std::endl;
    return buffer;
}

inline std::string readTicks(const char* filename)
{
    std::ifstream is(filename);
    is.seekg(0, std::ios_base::end);
    auto size = is.tellg();
    is.seekg(0, std::ios_base::beg);

    std::vector<char> buffer(size);
    is.read(buffer.data(), size);
    is.close();
    return std::string(buffer.begin(), buffer.end());
}

class Timer
{
    std::chrono::duration<double>& resultHolder;
    std::chrono::time_point<std::chrono::system_clock> start;
public:
    Timer(std::chrono::duration<double>& resultHolder):
        resultHolder(resultHolder),
        start(std::chrono::system_clock::now())
    {}

    ~Timer()
    {
        auto end = std::chrono::system_clock::now();
        resultHolder = end - start;
    }
};

inline std::ostream& dumpHeader(std::ostream& os,
                                const MessageHeaderCompT* header)
{
    return os << "len: " << header->BodyLen
              << ", tid: " << header->TemplateID
              << ", seq: " << header->MsgSeqNum;
}

template<typename UnderTest>
bool runTest(const char* name, UnderTest& underTest, const std::string& buffer, int count = 1)
{
    std::cout << "name,msgs,total time,usec/msg,total ticks,ticks/msg"
              << std::endl;

    for(; count; --count)
    {
        std::chrono::duration<double> elapsed_seconds{};
        uint64_t elapsedTicks{};
        uint32_t seqNo{};
        {
            TickCounter tickCounter(elapsedTicks);
            Timer timer(elapsed_seconds);

            for(auto p = buffer.data(); p < buffer.data() + buffer.size();)
            {
                auto header = reinterpret_cast<const MessageHeaderCompT*>(p);
                if(header->MsgSeqNum == seqNo )
                {
                    p = underTest.handle(header->TemplateID, p, *header, seqNo);
                    seqNo++;
                }
                else
                {
                    return false;
                }
            }
        }
        std::cout << name
                  << "," << seqNo
                  << "," << elapsed_seconds.count()
                  << "," << (elapsed_seconds.count() / seqNo) * 1000000
                  << "," << elapsedTicks
                  << "," << elapsedTicks / seqNo
                  << "," << StatsHolder::total << std::endl;
    }
    return true;
}

template<typename UnderTest>
int runner(const char* name, UnderTest& underTest, const int argc, const char** argv)
{
    switch(argc)
    {
    case 2:  return runTest(name, underTest, readTicks(argv[1])) ? 0 : 1;
    case 3:  return runTest(name, underTest, readTicks(argv[1]), atoi(argv[2])) ? 0 : 1;
    default: return -1;
    }
}
