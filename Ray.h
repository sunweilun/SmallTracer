//
//  Ray.h
//  SmallTracer
//
//  Created by Weilun Sun on 10/10/15.
//  Copyright © 2015 UC Berkeley. All rights reserved.
//

#ifndef Ray_h
#define Ray_h

#include <glm/glm.hpp>

class Ray
{
public:
    glm::vec3 origin;
    glm::vec3 direction;
    glm::vec3 radiance;
    glm::vec3 getOrig() const { return origin; }
    glm::vec3 getDir() const { return direction; }
};

#endif /* Ray_h */
