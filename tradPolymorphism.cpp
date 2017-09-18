#include "reader.h"
#include "TradPolymorphism.h"

#include <stdexcept>
#include <sstream>

#include <chrono>

int main(const int argc, const char** argv)
{
    using Reader = ReaderT<TradPolymorphism, NullReader, MsgReader>;
    Reader underTest;
    return runner("TradPolymorphism", underTest, argc, argv);
}
