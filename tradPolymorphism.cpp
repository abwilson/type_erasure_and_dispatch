#include "reader.h"
#include "CallThroughBaseClass.h"

#include <stdexcept>
#include <sstream>

#include <chrono>

int main(const int argc, const char** argv)
{
    using Reader = ReaderT<CallThroughBaseClass, NullReader, MsgReader>;
    Reader underTest;
    return runner(underTest, argc, argv);
}
