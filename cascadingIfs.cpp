#include "reader.h"
#include "HandlerHolder.h"

template<template<typename, int> class Handler>
struct CascadingIfs: HandlerHolder<Handler>
{
    using Base = HandlerHolder<Handler>;
    const char* handle(
        int i,
        const char* msg,
        const MessageHeaderCompT& header,
        uint32_t& seqNo) const
    {
        if(i == TID_ADD_COMPLEX_INSTRUMENT)  return Base::addComplexInstrument(  msg, header, seqNo); // 13400
        if(i == TID_AUCTION_BBO)             return Base::auctionBBO(            msg, header, seqNo); // 13500
        if(i == TID_AUCTION_CLEARING_PRICE)  return Base::auctionClearingPrice(  msg, header, seqNo); // 13501
        if(i == TID_CROSS_REQUEST)           return Base::crossRequest(          msg, header, seqNo); // 13502
        if(i == TID_EXECUTION_SUMMARY)       return Base::executionSummary(      msg, header, seqNo); // 13202
        if(i == TID_FULL_ORDER_EXECUTION)    return Base::fullOrderExecution(    msg, header, seqNo); // 13104
        if(i == TID_HEARTBEAT)               return Base::heartbeat(             msg, header, seqNo); // 13001
        if(i == TID_INSTRUMENT_STATE_CHANGE) return Base::instrumentStateChange( msg, header, seqNo); // 13301
        if(i == TID_INSTRUMENT_SUMMARY)      return Base::instrumentSummary(     msg, header, seqNo); // 13601
        if(i == TID_ORDER_ADD)               return Base::orderAdd(              msg, header, seqNo); // 13100
        if(i == TID_ORDER_DELETE)            return Base::orderDelete(           msg, header, seqNo); // 13102
        if(i == TID_ORDER_MASS_DELETE)       return Base::orderMassDelete(       msg, header, seqNo); // 13103
        if(i == TID_ORDER_MODIFY)            return Base::orderModify(           msg, header, seqNo); // 13101
        if(i == TID_ORDER_MODIFY_SAME_PRIO)  return Base::orderModifySamePrio(   msg, header, seqNo); // 13106
        if(i == TID_PACKET_HEADER)           return Base::packetHeader(          msg, header, seqNo); // 13002
        if(i == TID_PARTIAL_ORDER_EXECUTION) return Base::partialOrderExecution( msg, header, seqNo); // 13105
        if(i == TID_PRODUCT_STATE_CHANGE)    return Base::productStateChange(    msg, header, seqNo); // 13300
        if(i == TID_PRODUCT_SUMMARY)         return Base::productSummary(        msg, header, seqNo); // 13600
        if(i == TID_QUOTE_REQUEST)           return Base::quoteRequest(          msg, header, seqNo); // 13503
        if(i == TID_SNAPSHOT_ORDER)          return Base::snapshotOrder(         msg, header, seqNo); // 13602
        if(i == TID_TOP_OF_BOOK)             return Base::topOfBook(             msg, header, seqNo); // 13504
        if(i == TID_TRADE_REPORT)            return Base::tradeReport(           msg, header, seqNo); // 13201
        if(i == TID_TRADE_REVERSAL)          return Base::tradeReversal(         msg, header, seqNo); // 13200
                                             return Base::defaultHandler(        msg, header, seqNo);
    }    
};

int main(const int argc, const char** argv)
{
    using CascadingIfs = CascadingIfs<MsgReader>;
    CascadingIfs underTest;
    return runner("CascadingIfs", underTest, argc, argv);
}
