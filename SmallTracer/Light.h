
//
//  Light.h
//  SmallTracer
//
//  Created by Weilun Sun on 10/10/15.
//  Copyright © 2015 UC Berkeley. All rights reserved.
//

#ifndef Light_h
#define Light_h

#include "Ray.h"

class Light
{
public:
    virtual Ray sample() const { return Ray(); }
};

#endif /* Light_h */
