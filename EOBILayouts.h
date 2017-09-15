/*******************************************************************************
 * Permission to use this/these file(s) is subject to the Terms of Use set
 * forth in the file Terms_of_Use.txt accompanying this file.
 *******************************************************************************
 *
 *  FILE NAME: EOBILayouts.h
 *
 *  INTERFACE VERSION:   6.0
 *
 *  BUILD NUMBER:        6.0.359.ga-6000351-2
 *
 *  DESCRIPTION:
 *
 *    This header file documents the binary message format of EOBI.
 *    - All integers are in little endian byte order.
 *    - Padding bytes in following structures (char PadX[...]) are not required to be initialized.
 *
 *    DISCLAIMER:
 *
 *      Supported on Linux/x64 platforms with GNU C/C++ version 4.1 and 4.4.
 *
 *      This header file is meant to be compatible (but not supported) with any C/C++
 *      compiler/architecture that defines C99 compliant integer types in stdint.h and
 *      corresponds with the following alignment and padding requirements:
 *
 *    Padding:
 *      The compiler does not add implicit padding bytes between any of the following
 *      structure members. All padding bytes required for the alignment rules below are
 *      already explicitly contained in the structures.
 *
 *    Alignment rules:
 *      1 byte alignment for  int8_t and  uint8_t types
 *      2 byte alignment for int16_t and uint16_t types
 *      4 byte alignment for int32_t and uint32_t types
 *      8 byte alignment for int64_t and uint64_t types
 *
 *******************************************************************************/

#ifndef __EOBI_EOBI_LAYOUTS__
#define __EOBI_EOBI_LAYOUTS__

#include <stdint.h>

#if defined(__cplusplus) || defined(c_plusplus)
extern "C"
{
#endif

#define EOBI_INTERFACE_VERSION "6.0"
#define EOBI_BUILD_NUMBER      "6.0.359.ga-6000351-2"

/*
 * No Value defines
 */
#define NO_VALUE_SLONG                                   ((int64_t) 0x8000000000000000L)
#define NO_VALUE_ULONG                                   ((uint64_t) 0xffffffffffffffffUL)
#define NO_VALUE_SINT                                    ((int32_t) 0x80000000)
#define NO_VALUE_UINT                                    ((uint32_t) 0xffffffff)
#define NO_VALUE_SSHORT                                  ((int16_t) 0x8000)
#define NO_VALUE_USHORT                                  ((uint16_t) 0xffff)
#define NO_VALUE_SCHAR                                   ((int8_t) 0x80)
#define NO_VALUE_UCHAR                                   ((uint8_t) 0xff)
#define NO_VALUE_STR                                     0
#define NO_VALUE_DATA_16                                 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}

/*
 * Template IDs defines
 */
#define	TID_ADD_COMPLEX_INSTRUMENT                       13400		// < AddComplexInstrument (Add Complex Instrument)
#define	TID_AUCTION_BBO                                  13500		// < AuctionBBO (Auction Best Bid/Offer)
#define	TID_AUCTION_CLEARING_PRICE                       13501		// < AuctionClearingPrice (Auction Clearing Price)
#define	TID_CROSS_REQUEST                                13502		// < CrossRequest (Cross Request)
#define	TID_EXECUTION_SUMMARY                            13202		// < ExecutionSummary (Execution Summary)
#define	TID_FULL_ORDER_EXECUTION                         13104		// < FullOrderExecution (Full Order Execution)
#define	TID_HEARTBEAT                                    13001		// < Heartbeat (Heartbeat)
#define	TID_INSTRUMENT_STATE_CHANGE                      13301		// < InstrumentStateChange (Instrument State Change)
#define	TID_INSTRUMENT_SUMMARY                           13601		// < InstrumentSummary (Instrument Summary)
#define	TID_ORDER_ADD                                    13100		// < OrderAdd (Order Add)
#define	TID_ORDER_DELETE                                 13102		// < OrderDelete (Order Delete)
#define	TID_ORDER_MASS_DELETE                            13103		// < OrderMassDelete (Order Mass Delete)
#define	TID_ORDER_MODIFY                                 13101		// < OrderModify (Order Modify)
#define	TID_ORDER_MODIFY_SAME_PRIO                       13106		// < OrderModifySamePrio (Order Modify Same Priority)
#define	TID_PACKET_HEADER                                13002		// < PacketHeader (Packet Header)
#define	TID_PARTIAL_ORDER_EXECUTION                      13105		// < PartialOrderExecution (Partial Order Execution)
#define	TID_PRODUCT_STATE_CHANGE                         13300		// < ProductStateChange (Product State Change)
#define	TID_PRODUCT_SUMMARY                              13600		// < ProductSummary (Product Summary)
#define	TID_QUOTE_REQUEST                                13503		// < QuoteRequest (Quote Request)
#define	TID_SNAPSHOT_ORDER                               13602		// < SnapshotOrder (Snapshot Order)
#define	TID_TOP_OF_BOOK                                  13504		// < TopOfBook (Top of Book)
#define	TID_TRADE_REPORT                                 13201		// < TradeReport (Trade Report)
#define	TID_TRADE_REVERSAL                               13200		// < TradeReversal (Trade Reversal)

const int EOBI_EOBI_TID_MIN = 13001;  // lowest assigned template ID
const int EOBI_EOBI_TID_MAX = 13602;  // highest assigned template ID

/*
 * Max defines for sequences defines
 */
#define MAX_ADD_COMPLEX_INSTRUMENT_INSTRMT_LEG_GRP      	20
#define MAX_INSTRUMENT_SUMMARY_MD_INSTRUMENT_ENTRY_GRP  	15
#define MAX_TRADE_REVERSAL_MD_TRADE_ENTRY_GRP           	15

/*
 * Data Type defines
 */

// DataType AggressorSide
#define ENUM_AGGRESSOR_SIDE_BUY                          1
#define ENUM_AGGRESSOR_SIDE_SELL                         2

// DataType AlgorithmicTradeIndicator
#define ENUM_ALGORITHMIC_TRADE_INDICATOR_ALGORITHMIC_TRADE 1

// DataType ApplSeqResetIndicator
#define ENUM_APPL_SEQ_RESET_INDICATOR_NO_RESET           0
#define ENUM_APPL_SEQ_RESET_INDICATOR_RESET              1

// DataType CompletionIndicator
#define ENUM_COMPLETION_INDICATOR_INCOMPLETE             0
#define ENUM_COMPLETION_INDICATOR_COMPLETE               1

// DataType FastMarketIndicator
#define ENUM_FAST_MARKET_INDICATOR_NO                    0
#define ENUM_FAST_MARKET_INDICATOR_YES                   1

// DataType FuncCategory
#define LEN_FUNC_CATEGORY                                100
#define ENUM_FUNC_CATEGORY_GENERAL                       "General                                                                                             "
#define ENUM_FUNC_CATEGORY_ORDER_DATA                    "Order Data                                                                                          "
#define ENUM_FUNC_CATEGORY_TRADE_DATA                    "Trade Data                                                                                          "
#define ENUM_FUNC_CATEGORY_STATE_CHANGE                  "State Change                                                                                        "
#define ENUM_FUNC_CATEGORY_REFERENCE_DATA                "Reference Data                                                                                      "
#define ENUM_FUNC_CATEGORY_SNAPSHOT                      "Snapshot                                                                                            "

// DataType ImpliedMarketIndicator
#define ENUM_IMPLIED_MARKET_INDICATOR_NOT_IMPLIED        0
#define ENUM_IMPLIED_MARKET_INDICATOR_IMPLIED_IN_OUT     3

// DataType LegSecurityIDSource
#define LEN_LEG_SECURITY_ID_SOURCE                       1
#define ENUM_LEG_SECURITY_ID_SOURCE_MARKETPLACE          "M"
#define ENUM_LEG_SECURITY_ID_SOURCE_MARKETPLACE_CHAR     'M'

// DataType LegSide
#define ENUM_LEG_SIDE_BUY                                1
#define ENUM_LEG_SIDE_SELL                               2

// DataType MDEntryType
#define ENUM_MD_ENTRY_TYPE_TRADE                         2
#define ENUM_MD_ENTRY_TYPE_OPENING_PRICE                 4
#define ENUM_MD_ENTRY_TYPE_CLOSING_PRICE                 5
#define ENUM_MD_ENTRY_TYPE_HIGH_PRICE                    7
#define ENUM_MD_ENTRY_TYPE_LOW_PRICE                     8
#define ENUM_MD_ENTRY_TYPE_TRADE_VOLUME                  66
#define ENUM_MD_ENTRY_TYPE_PREVIOUS_CLOSING_PRICE        101
#define ENUM_MD_ENTRY_TYPE_OPENING_AUCTION               200
#define ENUM_MD_ENTRY_TYPE_INTRADAY_AUCTION              201
#define ENUM_MD_ENTRY_TYPE_CIRCUIT_BREAKER_AUCTION       202
#define ENUM_MD_ENTRY_TYPE_CLOSING_AUCTION               203
#define ENUM_MD_ENTRY_TYPE_IPO_AUCTION                   204

// DataType MDReportEvent
#define ENUM_MD_REPORT_EVENT_SCOPE_DEFINITION            0

// DataType MDUpdateAction
#define ENUM_MD_UPDATE_ACTION_NEW                        0
#define ENUM_MD_UPDATE_ACTION_CHANGE                     1
#define ENUM_MD_UPDATE_ACTION_DELETE                     2
#define ENUM_MD_UPDATE_ACTION_OVERLAY                    5

// DataType MarketCondition
#define ENUM_MARKET_CONDITION_NORMAL                     0
#define ENUM_MARKET_CONDITION_STRESSED                   1

// DataType MarketDataType
#define ENUM_MARKET_DATA_TYPE_ORDER_BOOK_MAINTENANCE     1
#define ENUM_MARKET_DATA_TYPE_ORDER_BOOK_EXECUTION       2
#define ENUM_MARKET_DATA_TYPE_TRADE_REVERSAL             3
#define ENUM_MARKET_DATA_TYPE_TRADE_REPORT               4
#define ENUM_MARKET_DATA_TYPE_AUCTION_BBO                5
#define ENUM_MARKET_DATA_TYPE_AUCTION_CLEARING_PRICE     6
#define ENUM_MARKET_DATA_TYPE_CROSS_TRADE_ANNOUNCEMENT   7
#define ENUM_MARKET_DATA_TYPE_QUOTE_REQUEST              8
#define ENUM_MARKET_DATA_TYPE_MARKET_SEGMENT_SNAPSHOT    9
#define ENUM_MARKET_DATA_TYPE_SINGLE_INSTRUMENT_SNAPSHOT 10
#define ENUM_MARKET_DATA_TYPE_ORDER_BOOK_SNAPSHOT        11
#define ENUM_MARKET_DATA_TYPE_MATCH_EVENT                12
#define ENUM_MARKET_DATA_TYPE_TOP_OF_BOOK                13

// DataType MatchSubType
#define ENUM_MATCH_SUB_TYPE_OPENING_AUCTION              1
#define ENUM_MATCH_SUB_TYPE_CLOSING_AUCTION              2
#define ENUM_MATCH_SUB_TYPE_INTRADAY_AUCTION             3
#define ENUM_MATCH_SUB_TYPE_CIRCUIT_BREAKER_AUCTION      4
#define ENUM_MATCH_SUB_TYPE_IPO_AUCTION                  5

// DataType MatchType
#define ENUM_MATCH_TYPE_CONFIRMED_TRADE_REPORT           3
#define ENUM_MATCH_TYPE_CROSS_AUCTION                    5
#define ENUM_MATCH_TYPE_CALL_AUCTION                     7

// DataType MsgType
#define LEN_MSG_TYPE                                     3
#define ENUM_MSG_TYPE_MARKET_DATA_REPORT                 "U20"
#define ENUM_MSG_TYPE_HEARTBEAT                          "0  "
#define ENUM_MSG_TYPE_MARKET_DATA_ORDER                  "U21"
#define ENUM_MSG_TYPE_MARKET_DATA_TRADE                  "U22"
#define ENUM_MSG_TYPE_TRADING_SESSION_STATUS             "h  "
#define ENUM_MSG_TYPE_SECURITY_STATUS                    "f  "
#define ENUM_MSG_TYPE_SECURITY_DEFINITION_UPDATE_REPORT  "BP "
#define ENUM_MSG_TYPE_MARKET_DATA_INSTRUMENT             "U23"

// DataType NoMarketSegments
#define ENUM_NO_MARKET_SEGMENTS_ONE                      1

// DataType OrdType
#define ENUM_ORD_TYPE_MARKET                             1

// DataType Pad1
#define LEN_PAD1                                         1

// DataType Pad2
#define LEN_PAD2                                         2

// DataType Pad3
#define LEN_PAD3                                         3

// DataType Pad4
#define LEN_PAD4                                         4

// DataType Pad5
#define LEN_PAD5                                         5

// DataType Pad6
#define LEN_PAD6                                         6

// DataType Pad7
#define LEN_PAD7                                         7

// DataType PotentialSecurityTradingEvent
#define ENUM_POTENTIAL_SECURITY_TRADING_EVENT_NONE       0
#define ENUM_POTENTIAL_SECURITY_TRADING_EVENT_PRICE_VOLATILITY_AUCTION_IS_EXTENDED 10

// DataType ProductComplex
#define ENUM_PRODUCT_COMPLEX_STANDARD_OPTION_STRATEGY    2
#define ENUM_PRODUCT_COMPLEX_NON_STANDARD_OPTION_STRATEGY 3
#define ENUM_PRODUCT_COMPLEX_VOLATILITY_STRATEGY         4
#define ENUM_PRODUCT_COMPLEX_FUTURES_SPREAD              5
#define ENUM_PRODUCT_COMPLEX_INTER_PRODUCT_SPREAD        6
#define ENUM_PRODUCT_COMPLEX_STANDARD_FUTURES_STRATEGY   7
#define ENUM_PRODUCT_COMPLEX_PACK_AND_BUNDLE             8
#define ENUM_PRODUCT_COMPLEX_STRIP                       9

// DataType SecurityIDSource
#define LEN_SECURITY_ID_SOURCE                           1
#define ENUM_SECURITY_ID_SOURCE_MARKETPLACE              "M"
#define ENUM_SECURITY_ID_SOURCE_MARKETPLACE_CHAR         'M'

// DataType SecurityStatus
#define ENUM_SECURITY_STATUS_ACTIVE                      1
#define ENUM_SECURITY_STATUS_INACTIVE                    2
#define ENUM_SECURITY_STATUS_EXPIRED                     4
#define ENUM_SECURITY_STATUS_SUSPENDED                   9

// DataType SecurityTradingEvent
#define ENUM_SECURITY_TRADING_EVENT_PRICE_VOLATILITY_AUCTION_IS_EXTENDED 10
#define ENUM_SECURITY_TRADING_EVENT_PRICE_VOLATILITY_AUCTION_IS_EXTENDED_AGAIN 11

// DataType SecurityTradingStatus
#define ENUM_SECURITY_TRADING_STATUS_TRADING_HALT        2
#define ENUM_SECURITY_TRADING_STATUS_MARKET_IMBALANCE_BUY 7
#define ENUM_SECURITY_TRADING_STATUS_MARKET_IMBALANCE_SELL 8
#define ENUM_SECURITY_TRADING_STATUS_CLOSED              200
#define ENUM_SECURITY_TRADING_STATUS_RESTRICTED          201
#define ENUM_SECURITY_TRADING_STATUS_BOOK                202
#define ENUM_SECURITY_TRADING_STATUS_CONTINUOUS          203
#define ENUM_SECURITY_TRADING_STATUS_OPENING_AUCTION     204
#define ENUM_SECURITY_TRADING_STATUS_OPENING_AUCTION_FREEZE 205
#define ENUM_SECURITY_TRADING_STATUS_INTRADAY_AUCTION    206
#define ENUM_SECURITY_TRADING_STATUS_INTRADAY_AUCTION_FREEZE 207
#define ENUM_SECURITY_TRADING_STATUS_CIRCUIT_BREAKER_AUCTION 208
#define ENUM_SECURITY_TRADING_STATUS_CIRCUIT_BREAKER_AUCTION_FREEZE 209
#define ENUM_SECURITY_TRADING_STATUS_CLOSING_AUCTION     210
#define ENUM_SECURITY_TRADING_STATUS_CLOSING_AUCTION_FREEZE 211
#define ENUM_SECURITY_TRADING_STATUS_IPO_AUCTION         212
#define ENUM_SECURITY_TRADING_STATUS_IPO_AUCTION_FREEZE  213

// DataType SecurityType
#define LEN_SECURITY_TYPE                                4
#define ENUM_SECURITY_TYPE_OPTION                        "OPT "
#define ENUM_SECURITY_TYPE_FUTURE                        "FUT "
#define ENUM_SECURITY_TYPE_MULTI_LEG                     "MLEG"

// DataType SecurityUpdateAction
#define LEN_SECURITY_UPDATE_ACTION                       1
#define ENUM_SECURITY_UPDATE_ACTION_ADD                  "A"
#define ENUM_SECURITY_UPDATE_ACTION_ADD_CHAR             'A'

// DataType Side
#define ENUM_SIDE_BUY                                    1
#define ENUM_SIDE_SELL                                   2

// DataType TradSesEvent
#define ENUM_TRAD_SES_EVENT_TBD                          0
#define ENUM_TRAD_SES_EVENT_STATUS_CHANGE                3

// DataType TradSesStatus
#define ENUM_TRAD_SES_STATUS_HALTED                      1
#define ENUM_TRAD_SES_STATUS_OPEN                        2
#define ENUM_TRAD_SES_STATUS_CLOSED                      3

// DataType TradeCondition
#define ENUM_TRADE_CONDITION_IMPLIED_TRADE               1
#define ENUM_TRADE_CONDITION_SYSTEMATIC_INTERNALIZER     153
#define ENUM_TRADE_CONDITION_MIDPOINT_PRICE              155

// DataType TradingSessionID
#define ENUM_TRADING_SESSIONID_DAY                       1
#define ENUM_TRADING_SESSIONID_MORNING                   3
#define ENUM_TRADING_SESSIONID_EVENING                   5
#define ENUM_TRADING_SESSIONID_AFTER_HOURS               6
#define ENUM_TRADING_SESSIONID_HOLIDAY                   7

// DataType TradingSessionSubID
#define ENUM_TRADING_SESSION_SUBID_PRE_TRADING           1
#define ENUM_TRADING_SESSION_SUBID_CONTINUOUS            3
#define ENUM_TRADING_SESSION_SUBID_CLOSING               4
#define ENUM_TRADING_SESSION_SUBID_POST_TRADING          5
#define ENUM_TRADING_SESSION_SUBID_QUIESCENT             7

/*
 * Structure defines for components and sequences
 */

// Structure: InstrmtLegGrp
typedef struct
{
    int32_t LegSymbol;
    char Pad4[LEN_PAD4];
    int64_t LegSecurityID;
    int32_t LegRatioQty;
    uint8_t LegSide;
    char Pad3[LEN_PAD3];
} InstrmtLegGrpSeqT;

// Structure: MDInstrumentEntryGrp
typedef struct
{
    int64_t MDEntryPx;
    int32_t MDEntrySize;
    uint8_t MDEntryType;
    uint8_t TradeCondition;
    char Pad2[LEN_PAD2];
} MDInstrumentEntryGrpSeqT;

// Structure: MDTradeEntryGrp
typedef struct
{
    int64_t MDEntryPx;
    int32_t MDEntrySize;
    uint8_t MDEntryType;
    char Pad3[LEN_PAD3];
} MDTradeEntryGrpSeqT;

// Structure: MessageHeader
typedef struct
{
    uint16_t BodyLen;
    uint16_t TemplateID;
    uint32_t MsgSeqNum;
} MessageHeaderCompT;

// Structure: OrderDetails
typedef struct
{
    uint64_t TrdRegTSTimePriority;
    int32_t DisplayQty;
    uint8_t Side;
    uint8_t OrdType;
    char Pad2[LEN_PAD2];
    int64_t Price;
} OrderDetailsCompT;

/*
 * Structure defines for messages
 */

// Message:	    AddComplexInstrument
// TemplateID:  13400
// Alias:       Add Complex Instrument
// FIX MsgType: SecurityDefinitionUpdateReport = "BP"
typedef struct
{
    MessageHeaderCompT MessageHeader;
    int64_t SecurityID;
    uint64_t TransactTime;
    int32_t SecuritySubType;
    uint8_t ProductComplex;
    uint8_t ImpliedMarketIndicator;
    uint8_t NoLegs;
    char Pad1[LEN_PAD1];
    InstrmtLegGrpSeqT InstrmtLegGrp[MAX_ADD_COMPLEX_INSTRUMENT_INSTRMT_LEG_GRP];
} AddComplexInstrumentT;

// Message:	    AuctionBBO
// TemplateID:  13500
// Alias:       Auction Best Bid/Offer
// FIX MsgType: MarketDataInstrument = "U23"
typedef struct
{
    MessageHeaderCompT MessageHeader;
    uint64_t TransactTime;
    int64_t SecurityID;
    int64_t BidPx;
    int64_t OfferPx;
    int32_t BidSize;
    int32_t OfferSize;
    uint8_t PotentialSecurityTradingEvent;
    char Pad7[LEN_PAD7];
} AuctionBBOT;

// Message:	    AuctionClearingPrice
// TemplateID:  13501
// Alias:       Auction Clearing Price
// FIX MsgType: MarketDataInstrument = "U23"
typedef struct
{
    MessageHeaderCompT MessageHeader;
    uint64_t TransactTime;
    int64_t SecurityID;
    int64_t LastPx;
    int32_t LastQty;
    int32_t ImbalanceQty;
    uint8_t SecurityTradingStatus;
    uint8_t PotentialSecurityTradingEvent;
    char Pad6[LEN_PAD6];
} AuctionClearingPriceT;

// Message:	    CrossRequest
// TemplateID:  13502
// Alias:       Cross Request
// FIX MsgType: MarketDataInstrument = "U23"
typedef struct
{
    MessageHeaderCompT MessageHeader;
    int64_t SecurityID;
    int32_t LastQty;
    char Pad4[LEN_PAD4];
    uint64_t TransactTime;
} CrossRequestT;

// Message:	    ExecutionSummary
// TemplateID:  13202
// Alias:       Execution Summary
// FIX MsgType: MarketDataTrade = "U22"
typedef struct
{
    MessageHeaderCompT MessageHeader;
    int64_t SecurityID;
    uint64_t AggressorTime;
    uint64_t RequestTime;
    uint64_t ExecID;
    int32_t LastQty;
    uint8_t AggressorSide;
    uint8_t TradeCondition;
    char Pad2[LEN_PAD2];
    int64_t LastPx;
    int32_t RestingHiddenQty;
    int32_t RestingCxlQty;
} ExecutionSummaryT;

// Message:	    FullOrderExecution
// TemplateID:  13104
// Alias:       Full Order Execution
// FIX MsgType: MarketDataOrder = "U21"
typedef struct
{
    MessageHeaderCompT MessageHeader;
    uint8_t Side;
    uint8_t OrdType;
    uint8_t AlgorithmicTradeIndicator;
    char Pad5[LEN_PAD5];
    int64_t Price;
    uint64_t TrdRegTSTimePriority;
    int64_t SecurityID;
    uint32_t TrdMatchID;
    int32_t LastQty;
    int64_t LastPx;
} FullOrderExecutionT;

// Message:	    Heartbeat
// TemplateID:  13001
// Alias:       Heartbeat
// FIX MsgType: Heartbeat = "0"
typedef struct
{
    MessageHeaderCompT MessageHeader;
    uint32_t LastMsgSeqNumProcessed;
    char Pad4[LEN_PAD4];
} HeartbeatT;

// Message:	    InstrumentStateChange
// TemplateID:  13301
// Alias:       Instrument State Change
// FIX MsgType: SecurityStatus = "f"
typedef struct
{
    MessageHeaderCompT MessageHeader;
    int64_t SecurityID;
    uint8_t SecurityStatus;
    uint8_t SecurityTradingStatus;
    uint8_t MarketCondition;
    uint8_t FastMarketIndicator;
    uint8_t SecurityTradingEvent;
    char Pad3[LEN_PAD3];
    uint64_t TransactTime;
} InstrumentStateChangeT;

// Message:	    InstrumentSummary
// TemplateID:  13601
// Alias:       Instrument Summary
// FIX MsgType: MarketDataInstrument = "U23"
typedef struct
{
    MessageHeaderCompT MessageHeader;
    int64_t SecurityID;
    uint64_t LastUpdateTime;
    uint64_t TrdRegTSExecutionTime;
    uint16_t TotNoOrders;
    uint8_t SecurityStatus;
    uint8_t SecurityTradingStatus;
    uint8_t MarketCondition;
    uint8_t FastMarketIndicator;
    uint8_t SecurityTradingEvent;
    uint8_t NoMDEntries;
    MDInstrumentEntryGrpSeqT MDInstrumentEntryGrp[MAX_INSTRUMENT_SUMMARY_MD_INSTRUMENT_ENTRY_GRP];
} InstrumentSummaryT;

// Message:	    OrderAdd
// TemplateID:  13100
// Alias:       Order Add
// FIX MsgType: MarketDataOrder = "U21"
typedef struct
{
    MessageHeaderCompT MessageHeader;
    uint64_t TrdRegTSTimeIn;
    int64_t SecurityID;
    OrderDetailsCompT OrderDetails;
} OrderAddT;

// Message:	    OrderDelete
// TemplateID:  13102
// Alias:       Order Delete
// FIX MsgType: MarketDataOrder = "U21"
typedef struct
{
    MessageHeaderCompT MessageHeader;
    uint64_t TrdRegTSTimeIn;
    uint64_t TransactTime;
    int64_t SecurityID;
    OrderDetailsCompT OrderDetails;
} OrderDeleteT;

// Message:	    OrderMassDelete
// TemplateID:  13103
// Alias:       Order Mass Delete
// FIX MsgType: MarketDataOrder = "U21"
typedef struct
{
    MessageHeaderCompT MessageHeader;
    int64_t SecurityID;
    uint64_t TransactTime;
} OrderMassDeleteT;

// Message:	    OrderModify
// TemplateID:  13101
// Alias:       Order Modify
// FIX MsgType: MarketDataOrder = "U21"
typedef struct
{
    MessageHeaderCompT MessageHeader;
    uint64_t TrdRegTSTimeIn;
    uint64_t TrdRegTSPrevTimePriority;
    int64_t PrevPrice;
    int32_t PrevDisplayQty;
    char Pad4[LEN_PAD4];
    int64_t SecurityID;
    OrderDetailsCompT OrderDetails;
} OrderModifyT;

// Message:	    OrderModifySamePrio
// TemplateID:  13106
// Alias:       Order Modify Same Priority
// FIX MsgType: MarketDataOrder = "U21"
typedef struct
{
    MessageHeaderCompT MessageHeader;
    uint64_t TrdRegTSTimeIn;
    uint64_t TransactTime;
    int32_t PrevDisplayQty;
    char Pad4[LEN_PAD4];
    int64_t SecurityID;
    OrderDetailsCompT OrderDetails;
} OrderModifySamePrioT;

// Message:	    PacketHeader
// TemplateID:  13002
// Alias:       Packet Header
// FIX MsgType: MarketDataReport = "U20"
typedef struct
{
    MessageHeaderCompT MessageHeader;
    uint32_t ApplSeqNum;
    int32_t MarketSegmentID;
    uint8_t PartitionID;
    uint8_t CompletionIndicator;
    uint8_t ApplSeqResetIndicator;
    char Pad5[LEN_PAD5];
    uint64_t TransactTime;
} PacketHeaderT;

// Message:	    PartialOrderExecution
// TemplateID:  13105
// Alias:       Partial Order Execution
// FIX MsgType: MarketDataOrder = "U21"
typedef struct
{
    MessageHeaderCompT MessageHeader;
    uint8_t Side;
    uint8_t OrdType;
    uint8_t AlgorithmicTradeIndicator;
    char Pad5[LEN_PAD5];
    int64_t Price;
    uint64_t TrdRegTSTimePriority;
    int64_t SecurityID;
    uint32_t TrdMatchID;
    int32_t LastQty;
    int64_t LastPx;
} PartialOrderExecutionT;

// Message:	    ProductStateChange
// TemplateID:  13300
// Alias:       Product State Change
// FIX MsgType: TradingSessionStatus = "h"
typedef struct
{
    MessageHeaderCompT MessageHeader;
    uint8_t TradingSessionID;
    uint8_t TradingSessionSubID;
    uint8_t TradSesStatus;
    uint8_t MarketCondition;
    uint8_t FastMarketIndicator;
    char Pad3[LEN_PAD3];
    uint64_t TransactTime;
} ProductStateChangeT;

// Message:	    ProductSummary
// TemplateID:  13600
// Alias:       Product Summary
// FIX MsgType: MarketDataInstrument = "U23"
typedef struct
{
    MessageHeaderCompT MessageHeader;
    uint32_t LastMsgSeqNumProcessed;
    uint8_t TradingSessionID;
    uint8_t TradingSessionSubID;
    uint8_t TradSesStatus;
    uint8_t MarketCondition;
    uint8_t FastMarketIndicator;
    char Pad7[LEN_PAD7];
} ProductSummaryT;

// Message:	    QuoteRequest
// TemplateID:  13503
// Alias:       Quote Request
// FIX MsgType: MarketDataInstrument = "U23"
typedef struct
{
    MessageHeaderCompT MessageHeader;
    int64_t SecurityID;
    int32_t LastQty;
    uint8_t Side;
    char Pad3[LEN_PAD3];
    uint64_t TransactTime;
} QuoteRequestT;

// Message:	    SnapshotOrder
// TemplateID:  13602
// Alias:       Snapshot Order
// FIX MsgType: MarketDataOrder = "U21"
typedef struct
{
    MessageHeaderCompT MessageHeader;
    OrderDetailsCompT OrderDetails;
} SnapshotOrderT;

// Message:	    TopOfBook
// TemplateID:  13504
// Alias:       Top of Book
// FIX MsgType: MarketDataInstrument = "U23"
typedef struct
{
    MessageHeaderCompT MessageHeader;
    uint64_t TransactTime;
    int64_t SecurityID;
    int64_t BidPx;
    int64_t OfferPx;
} TopOfBookT;

// Message:	    TradeReport
// TemplateID:  13201
// Alias:       Trade Report
// FIX MsgType: MarketDataTrade = "U22"
typedef struct
{
    MessageHeaderCompT MessageHeader;
    int64_t SecurityID;
    uint64_t TransactTime;
    uint32_t TrdMatchID;
    int32_t LastQty;
    int64_t LastPx;
    uint8_t MatchType;
    uint8_t MatchSubType;
    uint8_t AlgorithmicTradeIndicator;
    uint8_t TradeCondition;
    char Pad4[LEN_PAD4];
} TradeReportT;

// Message:	    TradeReversal
// TemplateID:  13200
// Alias:       Trade Reversal
// FIX MsgType: MarketDataTrade = "U22"
typedef struct
{
    MessageHeaderCompT MessageHeader;
    int64_t SecurityID;
    uint64_t TransactTime;
    uint32_t TrdMatchID;
    int32_t LastQty;
    int64_t LastPx;
    uint64_t TrdRegTSExecutionTime;
    uint8_t TradeCondition;
    char Pad6[LEN_PAD6];
    uint8_t NoMDEntries;
    MDTradeEntryGrpSeqT MDTradeEntryGrp[MAX_TRADE_REVERSAL_MD_TRADE_ENTRY_GRP];
} TradeReversalT;

/*
 * Begin of DEPRECATED defines
 */

#define BYTE_ARRAY_OF_0_16 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}

#define	TID_ADDCOMPLEXINSTRUMENT                         13400		// < AddComplexInstrument (Add Complex Instrument)
#define	TID_AUCTIONBBO                                   13500		// < AuctionBBO (Auction Best Bid/Offer)
#define	TID_AUCTIONCLEARINGPRICE                         13501		// < AuctionClearingPrice (Auction Clearing Price)
#define	TID_CROSSREQUEST                                 13502		// < CrossRequest (Cross Request)
#define	TID_EXECUTIONSUMMARY                             13202		// < ExecutionSummary (Execution Summary)
#define	TID_FULLORDEREXECUTION                           13104		// < FullOrderExecution (Full Order Execution)
#define	TID_HEARTBEAT                                    13001		// < Heartbeat (Heartbeat)
#define	TID_INSTRUMENTSTATECHANGE                        13301		// < InstrumentStateChange (Instrument State Change)
#define	TID_INSTRUMENTSUMMARY                            13601		// < InstrumentSummary (Instrument Summary)
#define	TID_ORDERADD                                     13100		// < OrderAdd (Order Add)
#define	TID_ORDERDELETE                                  13102		// < OrderDelete (Order Delete)
#define	TID_ORDERMASSDELETE                              13103		// < OrderMassDelete (Order Mass Delete)
#define	TID_ORDERMODIFY                                  13101		// < OrderModify (Order Modify)
#define	TID_ORDERMODIFYSAMEPRIO                          13106		// < OrderModifySamePrio (Order Modify Same Priority)
#define	TID_PACKETHEADER                                 13002		// < PacketHeader (Packet Header)
#define	TID_PARTIALORDEREXECUTION                        13105		// < PartialOrderExecution (Partial Order Execution)
#define	TID_PRODUCTSTATECHANGE                           13300		// < ProductStateChange (Product State Change)
#define	TID_PRODUCTSUMMARY                               13600		// < ProductSummary (Product Summary)
#define	TID_QUOTEREQUEST                                 13503		// < QuoteRequest (Quote Request)
#define	TID_SNAPSHOTORDER                                13602		// < SnapshotOrder (Snapshot Order)
#define	TID_TOPOFBOOK                                    13504		// < TopOfBook (Top of Book)
#define	TID_TRADEREPORT                                  13201		// < TradeReport (Trade Report)
#define	TID_TRADEREVERSAL                                13200		// < TradeReversal (Trade Reversal)

#define MAX_ADDCOMPLEXINSTRUMENT_INSTRMTLEGGRP          	20
#define MAX_INSTRUMENTSUMMARY_MDINSTRUMENTENTRYGRP      	15
#define MAX_TRADEREVERSAL_MDTRADEENTRYGRP               	15

#define ENUM_AGGRESSORSIDE_BUY                           1
#define ENUM_AGGRESSORSIDE_SELL                          2
#define ENUM_ALGORITHMICTRADEINDICATOR_ALGORITHMICTRADE  1
#define ENUM_APPLSEQRESETINDICATOR_NORESET               0
#define ENUM_APPLSEQRESETINDICATOR_RESET                 1
#define ENUM_COMPLETIONINDICATOR_INCOMPLETE              0
#define ENUM_COMPLETIONINDICATOR_COMPLETE                1
#define ENUM_FASTMARKETINDICATOR_NO                      0
#define ENUM_FASTMARKETINDICATOR_YES                     1
#define LEN_FUNCCATEGORY                                 100
#define ENUM_FUNCCATEGORY_GENERAL                        "General                                                                                             "
#define ENUM_FUNCCATEGORY_ORDERDATA                      "Order Data                                                                                          "
#define ENUM_FUNCCATEGORY_TRADEDATA                      "Trade Data                                                                                          "
#define ENUM_FUNCCATEGORY_STATECHANGE                    "State Change                                                                                        "
#define ENUM_FUNCCATEGORY_REFERENCEDATA                  "Reference Data                                                                                      "
#define ENUM_FUNCCATEGORY_SNAPSHOT                       "Snapshot                                                                                            "
#define ENUM_IMPLIEDMARKETINDICATOR_NOTIMPLIED           0
#define ENUM_IMPLIEDMARKETINDICATOR_IMPLIEDINOUT         3
#define LEN_LEGSECURITYIDSOURCE                          1
#define ENUM_LEGSECURITYIDSOURCE_MARKETPLACE             "M"
#define ENUM_LEGSIDE_BUY                                 1
#define ENUM_LEGSIDE_SELL                                2
#define ENUM_MDENTRYTYPE_TRADE                           2
#define ENUM_MDENTRYTYPE_OPENINGPRICE                    4
#define ENUM_MDENTRYTYPE_CLOSINGPRICE                    5
#define ENUM_MDENTRYTYPE_HIGHPRICE                       7
#define ENUM_MDENTRYTYPE_LOWPRICE                        8
#define ENUM_MDENTRYTYPE_TRADEVOLUME                     66
#define ENUM_MDENTRYTYPE_PREVIOUSCLOSINGPRICE            101
#define ENUM_MDENTRYTYPE_OPENINGAUCTION                  200
#define ENUM_MDENTRYTYPE_INTRADAYAUCTION                 201
#define ENUM_MDENTRYTYPE_CIRCUITBREAKERAUCTION           202
#define ENUM_MDENTRYTYPE_CLOSINGAUCTION                  203
#define ENUM_MDENTRYTYPE_IPOAUCTION                      204
#define ENUM_MDREPORTEVENT_SCOPEDEFINITION               0
#define ENUM_MDUPDATEACTION_NEW                          0
#define ENUM_MDUPDATEACTION_CHANGE                       1
#define ENUM_MDUPDATEACTION_DELETE                       2
#define ENUM_MDUPDATEACTION_OVERLAY                      5
#define ENUM_MARKETCONDITION_NORMAL                      0
#define ENUM_MARKETCONDITION_STRESSED                    1
#define ENUM_MARKETDATATYPE_ORDERBOOKMAINTENANCE         1
#define ENUM_MARKETDATATYPE_ORDERBOOKEXECUTION           2
#define ENUM_MARKETDATATYPE_TRADEREVERSAL                3
#define ENUM_MARKETDATATYPE_TRADEREPORT                  4
#define ENUM_MARKETDATATYPE_AUCTIONBBO                   5
#define ENUM_MARKETDATATYPE_AUCTIONCLEARINGPRICE         6
#define ENUM_MARKETDATATYPE_CROSSTRADEANNOUNCEMENT       7
#define ENUM_MARKETDATATYPE_QUOTEREQUEST                 8
#define ENUM_MARKETDATATYPE_MARKETSEGMENTSNAPSHOT        9
#define ENUM_MARKETDATATYPE_SINGLEINSTRUMENTSNAPSHOT     10
#define ENUM_MARKETDATATYPE_ORDERBOOKSNAPSHOT            11
#define ENUM_MARKETDATATYPE_MATCHEVENT                   12
#define ENUM_MARKETDATATYPE_TOPOFBOOK                    13
#define ENUM_MATCHSUBTYPE_OPENINGAUCTION                 1
#define ENUM_MATCHSUBTYPE_CLOSINGAUCTION                 2
#define ENUM_MATCHSUBTYPE_INTRADAYAUCTION                3
#define ENUM_MATCHSUBTYPE_CIRCUITBREAKERAUCTION          4
#define ENUM_MATCHSUBTYPE_IPOAUCTION                     5
#define ENUM_MATCHTYPE_CONFIRMEDTRADEREPORT              3
#define ENUM_MATCHTYPE_CROSSAUCTION                      5
#define ENUM_MATCHTYPE_CALLAUCTION                       7
#define LEN_MSGTYPE                                      3
#define ENUM_MSGTYPE_MARKETDATAREPORT                    "U20"
#define ENUM_MSGTYPE_HEARTBEAT                           "0  "
#define ENUM_MSGTYPE_MARKETDATAORDER                     "U21"
#define ENUM_MSGTYPE_MARKETDATATRADE                     "U22"
#define ENUM_MSGTYPE_TRADINGSESSIONSTATUS                "h  "
#define ENUM_MSGTYPE_SECURITYSTATUS                      "f  "
#define ENUM_MSGTYPE_SECURITYDEFINITIONUPDATEREPORT      "BP "
#define ENUM_MSGTYPE_MARKETDATAINSTRUMENT                "U23"
#define ENUM_NOMARKETSEGMENTS_ONE                        1
#define ENUM_ORDTYPE_MARKET                              1
#define LEN_PAD1                                         1
#define LEN_PAD2                                         2
#define LEN_PAD3                                         3
#define LEN_PAD4                                         4
#define LEN_PAD5                                         5
#define LEN_PAD6                                         6
#define LEN_PAD7                                         7
#define ENUM_POTENTIALSECURITYTRADINGEVENT_NONE          0
#define ENUM_POTENTIALSECURITYTRADINGEVENT_PRICEVOLATILITYAUCTIONISEXTENDED 10
#define ENUM_PRODUCTCOMPLEX_STANDARDOPTIONSTRATEGY       2
#define ENUM_PRODUCTCOMPLEX_NONSTANDARDOPTIONSTRATEGY    3
#define ENUM_PRODUCTCOMPLEX_VOLATILITYSTRATEGY           4
#define ENUM_PRODUCTCOMPLEX_FUTURESSPREAD                5
#define ENUM_PRODUCTCOMPLEX_INTERPRODUCTSPREAD           6
#define ENUM_PRODUCTCOMPLEX_STANDARDFUTURESSTRATEGY      7
#define ENUM_PRODUCTCOMPLEX_PACKANDBUNDLE                8
#define ENUM_PRODUCTCOMPLEX_STRIP                        9
#define LEN_SECURITYIDSOURCE                             1
#define ENUM_SECURITYIDSOURCE_MARKETPLACE                "M"
#define ENUM_SECURITYSTATUS_ACTIVE                       1
#define ENUM_SECURITYSTATUS_INACTIVE                     2
#define ENUM_SECURITYSTATUS_EXPIRED                      4
#define ENUM_SECURITYSTATUS_SUSPENDED                    9
#define ENUM_SECURITYTRADINGEVENT_PRICEVOLATILITYAUCTIONISEXTENDED 10
#define ENUM_SECURITYTRADINGEVENT_PRICEVOLATILITYAUCTIONISEXTENDEDAGAIN 11
#define ENUM_SECURITYTRADINGSTATUS_TRADINGHALT           2
#define ENUM_SECURITYTRADINGSTATUS_MARKETIMBALANCEBUY    7
#define ENUM_SECURITYTRADINGSTATUS_MARKETIMBALANCESELL   8
#define ENUM_SECURITYTRADINGSTATUS_CLOSED                200
#define ENUM_SECURITYTRADINGSTATUS_RESTRICTED            201
#define ENUM_SECURITYTRADINGSTATUS_BOOK                  202
#define ENUM_SECURITYTRADINGSTATUS_CONTINUOUS            203
#define ENUM_SECURITYTRADINGSTATUS_OPENINGAUCTION        204
#define ENUM_SECURITYTRADINGSTATUS_OPENINGAUCTIONFREEZE  205
#define ENUM_SECURITYTRADINGSTATUS_INTRADAYAUCTION       206
#define ENUM_SECURITYTRADINGSTATUS_INTRADAYAUCTIONFREEZE 207
#define ENUM_SECURITYTRADINGSTATUS_CIRCUITBREAKERAUCTION 208
#define ENUM_SECURITYTRADINGSTATUS_CIRCUITBREAKERAUCTIONFREEZE 209
#define ENUM_SECURITYTRADINGSTATUS_CLOSINGAUCTION        210
#define ENUM_SECURITYTRADINGSTATUS_CLOSINGAUCTIONFREEZE  211
#define ENUM_SECURITYTRADINGSTATUS_IPOAUCTION            212
#define ENUM_SECURITYTRADINGSTATUS_IPOAUCTIONFREEZE      213
#define LEN_SECURITYTYPE                                 4
#define ENUM_SECURITYTYPE_OPTION                         "OPT "
#define ENUM_SECURITYTYPE_FUTURE                         "FUT "
#define ENUM_SECURITYTYPE_MULTILEG                       "MLEG"
#define LEN_SECURITYUPDATEACTION                         1
#define ENUM_SECURITYUPDATEACTION_ADD                    "A"
#define ENUM_SIDE_BUY                                    1
#define ENUM_SIDE_SELL                                   2
#define ENUM_TRADSESEVENT_TBD                            0
#define ENUM_TRADSESEVENT_STATUSCHANGE                   3
#define ENUM_TRADSESSTATUS_HALTED                        1
#define ENUM_TRADSESSTATUS_OPEN                          2
#define ENUM_TRADSESSTATUS_CLOSED                        3
#define ENUM_TRADECONDITION_IMPLIEDTRADE                 1
#define ENUM_TRADECONDITION_SYSTEMATICINTERNALIZER       153
#define ENUM_TRADECONDITION_MIDPOINTPRICE                155
#define ENUM_TRADINGSESSIONID_DAY                        1
#define ENUM_TRADINGSESSIONID_MORNING                    3
#define ENUM_TRADINGSESSIONID_EVENING                    5
#define ENUM_TRADINGSESSIONID_AFTERHOURS                 6
#define ENUM_TRADINGSESSIONID_HOLIDAY                    7
#define ENUM_TRADINGSESSIONSUBID_PRETRADING              1
#define ENUM_TRADINGSESSIONSUBID_CONTINUOUS              3
#define ENUM_TRADINGSESSIONSUBID_CLOSING                 4
#define ENUM_TRADINGSESSIONSUBID_POSTTRADING             5
#define ENUM_TRADINGSESSIONSUBID_QUIESCENT               7

/*
 * End of DEPRECATED defines
 */

#if defined(__cplusplus) || defined(c_plusplus)
} /* close scope of 'extern "C"' declaration. */
#endif

#endif
