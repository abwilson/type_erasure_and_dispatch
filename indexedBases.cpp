#include "reader.h"

#include "IndexedBases.h"

#include <stdexcept>
#include <sstream>

#include <chrono>

int main(const int argc, const char** argv)
{
    using Reader = ReaderT<IndexedBases, NullReader, MsgReader>;
    Reader underTest;
    return runner(underTest, argc, argv);
}
