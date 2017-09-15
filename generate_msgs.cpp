#include "EOBILayouts.h"
#include "IndexedBases.h"

#include <iostream>
#include <random>

template<typename...> using void_t = void;

template<typename T, typename U = void>
struct Pop
{
    void populate(T& msg)
    {
    }
};

template<typename T>
struct Pop<T, void_t<decltype(T::OrderDetails)>>
{
    void populate(T& msg)
    {
        msg.OrderDetails.DisplayQty = 2;
    }
};

template<typename Msg, int tid>
struct MsgGenerator
{
    static constexpr int id = tid;
    auto& operator()(std::ostream& os, uint32_t& seqNo) const
    {
        Msg msg;
        msg.MessageHeader = { sizeof(Msg), id, seqNo++ };
        Pop<Msg>().populate(msg);
        return os.write(reinterpret_cast<char*>(&msg), sizeof(Msg));
    }
};

struct NullGenerator
{
    auto& operator()(std::ostream& os, uint32_t& seqNo) const
    {
        return os;
    }
};

using Generator = IndexedBases<
    std::ostream& (std::ostream&, uint32_t&),
    NullGenerator,
    MsgGenerator<AddComplexInstrumentT,  13400>, // TID_ADD_COMPLEX_INSTRUMENT
    MsgGenerator<AuctionBBOT,            13500>, // TID_AUCTION_BBO
    MsgGenerator<AuctionClearingPriceT,  13501>, // TID_AUCTION_CLEARING_PRICE
    MsgGenerator<CrossRequestT,          13502>, // TID_CROSS_REQUEST
    MsgGenerator<ExecutionSummaryT,      13202>, // TID_EXECUTION_SUMMARY
    MsgGenerator<FullOrderExecutionT,    13104>, // TID_FULL_ORDER_EXECUTION
    MsgGenerator<HeartbeatT,             13001>, // TID_HEARTBEAT
    MsgGenerator<InstrumentStateChangeT, 13301>, // TID_INSTRUMENT_STATE_CHANGE
    MsgGenerator<InstrumentSummaryT,     13601>, // TID_INSTRUMENT_SUMMARY
    MsgGenerator<OrderAddT,              13100>, // TID_ORDER_ADD
    MsgGenerator<OrderDeleteT,           13102>, // TID_ORDER_DELETE
    MsgGenerator<OrderMassDeleteT,       13103>, // TID_ORDER_MASS_DELETE
    MsgGenerator<OrderModifyT,           13101>, // TID_ORDER_MODIFY
    MsgGenerator<OrderModifySamePrioT,   13106>, // TID_ORDER_MODIFY_SAME_PRIO
    MsgGenerator<PacketHeaderT,          13002>, // TID_PACKET_HEADER
    MsgGenerator<PartialOrderExecutionT, 13105>, // TID_PARTIAL_ORDER_EXECUTION
    MsgGenerator<ProductStateChangeT,    13300>, // TID_PRODUCT_STATE_CHANGE
    MsgGenerator<ProductSummaryT,        13600>, // TID_PRODUCT_SUMMARY
    MsgGenerator<QuoteRequestT,          13503>,  // TID_QUOTE_REQUEST
    MsgGenerator<SnapshotOrderT,         13602>,  // TID_SNAPSHOT_ORDER
    MsgGenerator<TopOfBookT,             13504>,  // TID_TOP_OF_BOOK
    MsgGenerator<TradeReportT,           13201>,  // TID_TRADE_REPORT
    MsgGenerator<TradeReversalT,         13200>>; // TID_TRADE_REVERSAL

Generator g;

int main(const int argc, const char** argv)
{
    if(argc != 2)
    {
        return -1;
    }
    auto size = std::atoi(argv[1]);
    
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(Generator::minId, Generator::maxId);
    int dice_roll = distribution(generator);
    auto dice = std::bind(distribution, generator);

    uint32_t seqNo{0};

    for(; seqNo < size;)
    {
        g.handle( dice(), std::cout, seqNo);
    }
}
