#include "reader.h"
#include "IndexedMembers.h"

#include <stdexcept>
#include <sstream>

#include <chrono>


int main(const int argc, const char** argv)
{
    using Reader = ReaderT<IndexedMembers, NullReader, MsgReader>;
    Reader underTest;
    return runner(underTest, argc, argv);
//    return runTest(r, readTicks()) ? 0 : 1;
}
