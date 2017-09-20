#pragma once

#include "EOBILayouts.h"
#ifdef CONTIGUOUS_TIDS
#  include "ContiguousTIDs.h"
#endif
#include "HandlerHolder.h"
#include "MsgReader.h"

template<template<typename, int> class Handler>
struct BigOrribleSwitch: HandlerHolder<Handler>
{
    using Base = HandlerHolder<Handler>;
    const char* handle(
        int i,
        const char* msg,
        const MessageHeaderCompT& header,
        uint32_t& seqNo) const
    {
        switch(i)
        {
        case TID_ADD_COMPLEX_INSTRUMENT:  return Base::addComplexInstrument(  msg, header, seqNo); // 13400
        case TID_AUCTION_BBO:             return Base::auctionBBO(            msg, header, seqNo); // 13500
        case TID_AUCTION_CLEARING_PRICE:  return Base::auctionClearingPrice(  msg, header, seqNo); // 13501
        case TID_CROSS_REQUEST:           return Base::crossRequest(          msg, header, seqNo); // 13502
        case TID_EXECUTION_SUMMARY:       return Base::executionSummary(      msg, header, seqNo); // 13202
        case TID_FULL_ORDER_EXECUTION:    return Base::fullOrderExecution(    msg, header, seqNo); // 13104
        case TID_HEARTBEAT:               return Base::heartbeat(             msg, header, seqNo); // 13001
        case TID_INSTRUMENT_STATE_CHANGE: return Base::instrumentStateChange( msg, header, seqNo); // 13301
        case TID_INSTRUMENT_SUMMARY:      return Base::instrumentSummary(     msg, header, seqNo); // 13601
        case TID_ORDER_ADD:               return Base::orderAdd(              msg, header, seqNo); // 13100
        case TID_ORDER_DELETE:            return Base::orderDelete(           msg, header, seqNo); // 13102
        case TID_ORDER_MASS_DELETE:       return Base::orderMassDelete(       msg, header, seqNo); // 13103
        case TID_ORDER_MODIFY:            return Base::orderModify(           msg, header, seqNo); // 13101
        case TID_ORDER_MODIFY_SAME_PRIO:  return Base::orderModifySamePrio(   msg, header, seqNo); // 13106
        case TID_PACKET_HEADER:           return Base::packetHeader(          msg, header, seqNo); // 13002
        case TID_PARTIAL_ORDER_EXECUTION: return Base::partialOrderExecution( msg, header, seqNo); // 13105
        case TID_PRODUCT_STATE_CHANGE:    return Base::productStateChange(    msg, header, seqNo); // 13300
        case TID_PRODUCT_SUMMARY:         return Base::productSummary(        msg, header, seqNo); // 13600
        case TID_QUOTE_REQUEST:           return Base::quoteRequest(          msg, header, seqNo); // 13503
        case TID_SNAPSHOT_ORDER:          return Base::snapshotOrder(         msg, header, seqNo); // 13602
        case TID_TOP_OF_BOOK:             return Base::topOfBook(             msg, header, seqNo); // 13504
        case TID_TRADE_REPORT:            return Base::tradeReport(           msg, header, seqNo); // 13201
        case TID_TRADE_REVERSAL:          return Base::tradeReversal(         msg, header, seqNo); // 13200
        default:                          return Base::defaultHandler(        msg, header, seqNo);
        }
    }    
};
