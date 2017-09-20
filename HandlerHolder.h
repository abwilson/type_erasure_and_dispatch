#pragma once

#include "EOBILayouts.h"
#ifdef CONTIGUOUS_TIDS
#  include "ContiguousTIDs.h"
#endif
#include "MsgReader.h"

template<template<typename, int> class Handler>
struct HandlerHolder
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
};
