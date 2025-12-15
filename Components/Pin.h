#ifndef _PIN_H
#define _PIN_H

#include "..\Defs.h"

class Pin
{
protected:
    STATUS m_Status;    // Status of the Pin

public:
    Pin();
    void setStatus(STATUS r_Status);
    STATUS getStatus();

    // Pure virtual functions for pin coordinates
    virtual int getX() const = 0;
    virtual int getY() const = 0;
};

#endif