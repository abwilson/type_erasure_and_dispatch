#pragma once

struct HandlerState
{
    std::size_t count;
    std::size_t size;
    std::size_t errors;
};

/*
#define	TID_ORDER_ADD              13100 // < OrderAdd (Order Add)
#define	TID_ORDER_DELETE           13102 // < OrderDelete (Order Delete)
#define	TID_ORDER_MASS_DELETE      13103 // < OrderMassDelete (Order Mass Delete)
#define	TID_ORDER_MODIFY           13101 // < OrderModify (Order Modify)
#define	TID_ORDER_MODIFY_SAME_PRIO 13106 // < OrderModifySamePrio (Order Modify Same Priority)
*/

template<typename Msg>
struct OrderHandler: HandlerState
{
    void handle(const char* buffer, std::size_t size)
    {
        if(size == sizeof(Msg))
        {
            ++count;
            auto msg = reinterpret_cast<const Msg*>(buffer);
            size += msg->OrderDetails.DisplayQty;
        }
        else
        {
            ++errors;
            return;
        }
    }
};

/*
#define	TID_EXECUTION_SUMMARY       13202 // < ExecutionSummary (Execution Summary)
#define	TID_FULL_ORDER_EXECUTION    13104 // < FullOrderExecution (Full Order Execution)
#define	TID_PARTIAL_ORDER_EXECUTION 13105 // < PartialOrderExecution (Partial Order Execution)
 */

template<typename Msg>
struct ExecutionHandler: HandlerState
{
    void handle(const char* buffer, std::size_t size)
    {
        if(size == sizeof(Msg))
        {
            ++count;
            auto msg = reinterpret_cast<const Msg*>(buffer);
            size += msg->LastQty;
        }
        else
        {
            ++errors;
            return;
        }
    }
};
