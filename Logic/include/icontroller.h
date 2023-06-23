#ifndef ICONTROLLER_H
#define ICONTROLLER_H

#include <QString>

class IController
{
public:
    virtual void recordStart() = 0;
    virtual QString recordStop() = 0;
    virtual ~IController() {}
};

#endif // ICONTROLLER_H
