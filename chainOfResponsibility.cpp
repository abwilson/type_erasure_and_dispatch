#include "reader.h"
#include "EOBIWrap.h"
#include "MsgReader.h"
#include "FindByIdT.h"

#include <memory>
#include <array>

struct HandlerI
{
    virtual ~HandlerI() = default;
    virtual const char* operator()(
        const char* buffer,
        const MessageHeaderCompT& header,
        uint32_t& seqNo) const = 0;
};

template<int id, typename Impl>
struct HandlerT: HandlerI
{
    Impl impl;

    const char* operator()(
        const char* buffer,
        const MessageHeaderCompT& header,
        uint32_t& seqNo) const override
    {
        if(header.TemplateID == id)
        {
            return impl(buffer, header, seqNo);
        }
        return 0;
    }
};

template<typename Signature, typename Default, typename... Bases >
struct ChainOfResponsibility;

template<typename Result, typename... Args, typename Default, typename... Bases >
struct ChainOfResponsibility<Result(Args...), Default, Bases...>: Default
{
    using Handler = std::unique_ptr<HandlerI>;
    using Handlers = std::array< Handler, sizeof...(Bases)>;

    const Handlers handlers{ std::make_unique<HandlerT<Bases::id, Bases>>()... };

    Result handle( int i, Args... args ) const
    {
        for(const auto& h: handlers)
        {
            auto result = (*h)(std::forward<Args>(args)...);
            if(result)
            {
                return result;
            }
        }
        return Default::operator()(std::forward<Args>(args)...);
    }
};


int main(const int argc, const char** argv)
{
    using Reader = ReaderT<ChainOfResponsibility, NullReader, MsgReader>;
    Reader underTest;
    return runner("ChainOfResponsibility", underTest, argc, argv);
}
