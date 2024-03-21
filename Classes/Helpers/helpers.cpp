#include "helpers.h"

#include <QTime>
#include <QCoreApplication>

void Helpers::delay( int millisecondsToWait )
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}

std::string Helpers::intToTimeString(int s) {
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << s / 60 << ":" << std::setw(2) << s % 60;
    return oss.str();
}
