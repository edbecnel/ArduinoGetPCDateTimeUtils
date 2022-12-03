#include <ctype.h>
#include <stdlib.h>
#include "ArduinoGetPCDateTimeUtils.h"

using namespace ArduinoGetPCDateTimeUtils;

bool Utils::strncmpi(const char* a, const char* b, int count)
{
    int la = sizeof(a) / sizeof(char);
    int lb = sizeof(b) / sizeof(char);
    if (la < count || lb < count)
        return false;
    for (lb = 0; lb < la && lb < count; lb++)
    {
        if (toupper(a[lb]) != toupper(b[lb]))
            return false;
    }
    return true;
}

int Utils::convertMonthToInt(const char* month)
{
    int iMonth = -1;
    if (month == nullptr || sizeof(month) / sizeof(char) < 3)
        return iMonth;
    if (strncmpi(month, "JAN", 3))
        iMonth = 1;
    else if (strncmpi(month, "FEB", 3))
        iMonth = 2;
    else if (strncmpi(month, "MAR", 3))
        iMonth = 3;
    else if (strncmpi(month, "APR", 3))
        iMonth = 4;
    else if (strncmpi(month, "MAY", 3))
        iMonth = 5;
    else if (strncmpi(month, "JUN", 3))
        iMonth = 6;
    else if (strncmpi(month, "JUL", 3))
        iMonth = 7;
    else if (strncmpi(month, "AUG", 3))
        iMonth = 8;
    else if (strncmpi(month, "SEP", 3))
        iMonth = 9;
    else if (strncmpi(month, "OCT", 3))
        iMonth = 10;
    else if (strncmpi(month, "NOV", 3))
        iMonth = 11;
    else if (strncmpi(month, "DEC", 3))
        iMonth = 12;

    return iMonth;
}

int Utils::convertCharToInt(const char* str, int strLen)
{
    int firstCharPos = 0;
    for (int i = 0; i < strLen; i++)
    {
        if (str[i] != ' ')
        {
            firstCharPos = i;
            break;
        }
    }
    return atoi(&str[firstCharPos]);
}
