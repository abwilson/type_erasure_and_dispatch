#include "reader.h"

#include "reader.h"
#include "BigOrribleSwitch.h"

int main(const int argc, const char** argv)
{
    using BigOrribleSwitchInline = BigOrribleSwitch<MsgReader>;
    BigOrribleSwitchInline underTest;
    return runner(underTest, argc, argv);
}
