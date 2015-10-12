//
//  Camera.h
//  SmallTracer
//
//  Created by Weilun Sun on 10/10/15.
//  Copyright © 2015 UC Berkeley. All rights reserved.
//

#ifndef Camera_h
#define Camera_h

#include "Ray.h"
#include <vector>

class Camera
{
public:
    virtual std::vector<Ray> generateViewRays(const glm::uvec2& filmSize) const { return std::vector<Ray>(); }
};

#endif /* Camera_h */
