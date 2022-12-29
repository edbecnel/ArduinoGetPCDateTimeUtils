#include <ctype.h>
#include <stdlib.h>
#include "ArduinoGetPCDateTimeUtils.h"
#include <string.h>

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
    int iMonth = 0;
    if (strcmp(month, "Jan") == 0)
        iMonth = 1;
    else if (strcmp(month, "Feb") == 0)
        iMonth = 2;
    else if (strcmp(month, "Mar") == 0)
        iMonth = 3;
    else if (strcmp(month, "Apr") == 0)
        iMonth = 4;
    else if (strcmp(month, "May") == 0)
        iMonth = 5;
    else if (strcmp(month, "Jun") == 0)
        iMonth = 6;
    else if (strcmp(month, "Jul") == 0)
        iMonth = 7;
    else if (strcmp(month, "Aug") == 0)
        iMonth = 8;
    else if (strcmp(month, "Sep") == 0)
        iMonth = 9;
    else if (strcmp(month, "Oct") == 0)
        iMonth = 10;
    else if (strcmp(month, "Nov") == 0)
        iMonth = 11;
    else if (strcmp(month, "Dec") == 0)
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
