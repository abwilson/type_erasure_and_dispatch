#include "IndexedMembers.h"
#include "reader.h"
#include "MsgReader.h"

int main(const int argc, const char** argv)
{
    using Reader = ReaderT<IndexedMembers, NullReader, MsgReader>;
    Reader underTest;
    return runner("IndexedLambdas", underTest, argc, argv);
}
