#include "MsgReader.h"

#include <iostream>

void msgLengthError(uint64_t bodyLen, uint64_t msgLen)
{
    std::cerr << "Length mismatch: " << bodyLen
              << " != " << msgLen
              << std::endl;

    throw std::runtime_error("buggered");
}
