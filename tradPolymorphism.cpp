#include "TradPolymorphism.h"
#include "reader.h"

int main(const int argc, const char** argv)
{
    using Reader = ReaderT<TradPolymorphism, NullReader, MsgReader>;
    Reader underTest;
    return runner("TradPolymorphism", underTest, argc, argv);
}
