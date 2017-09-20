#include "EOBIWrap.h"
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
    MsgGenerator<AddComplexInstrumentT,  TID_ADD_COMPLEX_INSTRUMENT>,
    MsgGenerator<AuctionBBOT,            TID_AUCTION_BBO>,
    MsgGenerator<AuctionClearingPriceT,  TID_AUCTION_CLEARING_PRICE>,
    MsgGenerator<CrossRequestT,          TID_CROSS_REQUEST>,
    MsgGenerator<ExecutionSummaryT,      TID_EXECUTION_SUMMARY>,
    MsgGenerator<FullOrderExecutionT,    TID_FULL_ORDER_EXECUTION>,
    MsgGenerator<HeartbeatT,             TID_HEARTBEAT>,
    MsgGenerator<InstrumentStateChangeT, TID_INSTRUMENT_STATE_CHANGE>,
    MsgGenerator<InstrumentSummaryT,     TID_INSTRUMENT_SUMMARY>,
    MsgGenerator<OrderAddT,              TID_ORDER_ADD>,
    MsgGenerator<OrderDeleteT,           TID_ORDER_DELETE>,
    MsgGenerator<OrderMassDeleteT,       TID_ORDER_MASS_DELETE>,
    MsgGenerator<OrderModifyT,           TID_ORDER_MODIFY>,
    MsgGenerator<OrderModifySamePrioT,   TID_ORDER_MODIFY_SAME_PRIO>,
    MsgGenerator<PacketHeaderT,          TID_PACKET_HEADER>,
    MsgGenerator<PartialOrderExecutionT, TID_PARTIAL_ORDER_EXECUTION>,
    MsgGenerator<ProductStateChangeT,    TID_PRODUCT_STATE_CHANGE>,
    MsgGenerator<ProductSummaryT,        TID_PRODUCT_SUMMARY>,
    MsgGenerator<QuoteRequestT,          TID_QUOTE_REQUEST>,
    MsgGenerator<SnapshotOrderT,         TID_SNAPSHOT_ORDER>,
    MsgGenerator<TopOfBookT,             TID_TOP_OF_BOOK>,
    MsgGenerator<TradeReportT,           TID_TRADE_REPORT>,
    MsgGenerator<TradeReversalT,         TID_TRADE_REVERSAL>>;

Generator g;

int main(const int argc, const char** argv)
{
    if(argc != 2)
    {
        return -1;
    }
    auto log2size = std::atoi(argv[1]);
    uint64_t size = 1ull << log2size;
    
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
