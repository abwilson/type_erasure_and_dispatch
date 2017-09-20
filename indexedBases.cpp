#include "IndexedBases.h"
#include "reader.h"
#include "MsgReader.h"

int main(const int argc, const char** argv)
{
    using Reader = ReaderT<IndexedBases, NullReader, MsgReader>;
    Reader underTest;
    return runner("IndexedBases", underTest, argc, argv);
}
