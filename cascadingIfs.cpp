#include "CascadingIfs.h"
#include "reader.h"

int main(const int argc, const char** argv)
{
    using CascadingIfs = CascadingIfs<MsgReader>;
    CascadingIfs underTest;
    return runner("CascadingIfs", underTest, argc, argv);
}
