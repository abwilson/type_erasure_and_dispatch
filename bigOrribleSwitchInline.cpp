#include "BigOrribleSwitch.h"
#include "reader.h"

int main(const int argc, const char** argv)
{
    using BigOrribleSwitchInline = BigOrribleSwitch<MsgReader>;
    BigOrribleSwitchInline underTest;
    return runner("BigOrribleSwitch", underTest, argc, argv);
}
