#ifndef _ArduinoGetPCDateTimeUtils_
#define _ArduinoGetPCDateTimeUtils_ 1

#include "DateAndTime.h"

namespace ArduinoGetPCDateTimeUtils
{
    class Utils
    {
    public:
        static bool strncmpi(const char*, const char*, int);
        static int convertMonthToInt(const char*);
        static int convertCharToInt(const char*, int);
    };
}

#endif  // _ArduinoGenUtils_
