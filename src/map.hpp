#ifndef __Map__
#define __Map__

#include "common.hpp"
#include "object.hpp"

namespace Mario
{
    struct Map
    {
        Map() {}

        std::list<Object*> objs;
    };
}

#endif

