#include "VoidStarFPtrs.h"
#include "reader.h"
#include "MsgReader.h"

int main(const int argc, const char** argv)
{
    using Reader = ReaderT<VoidStarFPtrs, NullReader, MsgReader>;
    Reader underTest;
    return runner("VoidStarFPtrs", underTest, argc, argv);
}
