#include "type.h"

#include <ostream>

std::ostream& operator<<(std::ostream& os, const Type& type)
{
    if(type == Type::kStop)
    {
        os << "Stop";
    }
    else
    {
        os << "Start";
    }
    return os;
}
