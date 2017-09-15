#pragma once

template<template<typename, int> class Handler>
struct BigOrribleSwitch
{
    Handler<AddComplexInstrumentT,  TID_ADD_COMPLEX_INSTRUMENT  > addComplexInstrument;  // 13400
    Handler<AuctionBBOT,            TID_AUCTION_BBO             > auctionBBO;            // 13500
    Handler<AuctionClearingPriceT,  TID_AUCTION_CLEARING_PRICE  > auctionClearingPrice;  // 13501
    Handler<CrossRequestT,          TID_CROSS_REQUEST           > crossRequest;          // 13502
    Handler<ExecutionSummaryT,      TID_EXECUTION_SUMMARY       > executionSummary;      // 13202
    Handler<FullOrderExecutionT,    TID_FULL_ORDER_EXECUTION    > fullOrderExecution;    // 13104
    Handler<HeartbeatT,             TID_HEARTBEAT               > heartbeat;             // 13001
    Handler<InstrumentStateChangeT, TID_INSTRUMENT_STATE_CHANGE > instrumentStateChange; // 13301
    Handler<InstrumentSummaryT,     TID_INSTRUMENT_SUMMARY      > instrumentSummary;     // 13601
    Handler<OrderAddT,              TID_ORDER_ADD               > orderAdd;              // 13100
    Handler<OrderDeleteT,           TID_ORDER_DELETE            > orderDelete;           // 13102
    Handler<OrderMassDeleteT,       TID_ORDER_MASS_DELETE       > orderMassDelete;       // 13103
    Handler<OrderModifyT,           TID_ORDER_MODIFY            > orderModify;           // 13101
    Handler<OrderModifySamePrioT,   TID_ORDER_MODIFY_SAME_PRIO  > orderModifySamePrio;   // 13106
    Handler<PacketHeaderT,          TID_PACKET_HEADER           > packetHeader;          // 13002
    Handler<PartialOrderExecutionT, TID_PARTIAL_ORDER_EXECUTION > partialOrderExecution; // 13105
    Handler<ProductStateChangeT,    TID_PRODUCT_STATE_CHANGE    > productStateChange;    // 13300
    Handler<ProductSummaryT,        TID_PRODUCT_SUMMARY         > productSummary;        // 13600
    Handler<QuoteRequestT,          TID_QUOTE_REQUEST           > quoteRequest;          // 13503
    Handler<SnapshotOrderT,         TID_SNAPSHOT_ORDER          > snapshotOrder;         // 13602
    Handler<TopOfBookT,             TID_TOP_OF_BOOK             > topOfBook;             // 13504
    Handler<TradeReportT,           TID_TRADE_REPORT            > tradeReport;           // 13201
    Handler<TradeReversalT,         TID_TRADE_REVERSAL          > tradeReversal;         // 13200
    NullReader                                                    defaultHandler;
    
    const char* handle(
        int i,
        const char* msg,
        const MessageHeaderCompT& header,
        uint32_t& seqNo) const
    {
        switch(i)
        {
        case TID_ADD_COMPLEX_INSTRUMENT:  return addComplexInstrument(  msg, header, seqNo); // 13400
        case TID_AUCTION_BBO:             return auctionBBO(            msg, header, seqNo); // 13500
        case TID_AUCTION_CLEARING_PRICE:  return auctionClearingPrice(  msg, header, seqNo); // 13501
        case TID_CROSS_REQUEST:           return crossRequest(          msg, header, seqNo); // 13502
        case TID_EXECUTION_SUMMARY:       return executionSummary(      msg, header, seqNo); // 13202
        case TID_FULL_ORDER_EXECUTION:    return fullOrderExecution(    msg, header, seqNo); // 13104
        case TID_HEARTBEAT:               return heartbeat(             msg, header, seqNo); // 13001
        case TID_INSTRUMENT_STATE_CHANGE: return instrumentStateChange( msg, header, seqNo); // 13301
        case TID_INSTRUMENT_SUMMARY:      return instrumentSummary(     msg, header, seqNo); // 13601
        case TID_ORDER_ADD:               return orderAdd(              msg, header, seqNo); // 13100
        case TID_ORDER_DELETE:            return orderDelete(           msg, header, seqNo); // 13102
        case TID_ORDER_MASS_DELETE:       return orderMassDelete(       msg, header, seqNo); // 13103
        case TID_ORDER_MODIFY:            return orderModify(           msg, header, seqNo); // 13101
        case TID_ORDER_MODIFY_SAME_PRIO:  return orderModifySamePrio(   msg, header, seqNo); // 13106
        case TID_PACKET_HEADER:           return packetHeader(          msg, header, seqNo); // 13002
        case TID_PARTIAL_ORDER_EXECUTION: return partialOrderExecution( msg, header, seqNo); // 13105
        case TID_PRODUCT_STATE_CHANGE:    return productStateChange(    msg, header, seqNo); // 13300
        case TID_PRODUCT_SUMMARY:         return productSummary(        msg, header, seqNo); // 13600
        case TID_QUOTE_REQUEST:           return quoteRequest(          msg, header, seqNo); // 13503
        case TID_SNAPSHOT_ORDER:          return snapshotOrder(         msg, header, seqNo); // 13602
        case TID_TOP_OF_BOOK:             return topOfBook(             msg, header, seqNo); // 13504
        case TID_TRADE_REPORT:            return tradeReport(           msg, header, seqNo); // 13201
        case TID_TRADE_REVERSAL:          return tradeReversal(         msg, header, seqNo); // 13200
        default:                          return defaultHandler(        msg, header, seqNo);
        }
    }    
};
