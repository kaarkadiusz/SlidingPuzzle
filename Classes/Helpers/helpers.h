#ifndef HELPERS_H
#define HELPERS_H

#include <string>
#include <iomanip>
class Helpers
{
public:
    static void delay( int millisecondsToWait );
    static std::string intToTimeString(int s);
};

#endif // HELPERS_H
