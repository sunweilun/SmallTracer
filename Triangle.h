//
//  Triangle.h
//  SmallTracer
//
//  Created by Weilun Sun on 10/10/15.
//  Copyright © 2015 UC Berkeley. All rights reserved.
//

#ifndef Triangle_h
#define Triangle_h

#include <glm/glm.hpp>
#include "Ray.h"
#include "HitInfo.h"

class Triangle
{
public:
    glm::vec3 v[3];
    glm::vec3 n[3];
    glm::vec3 t[3];
    glm::vec3 getLowerBound() const
    {
        return glm::min(glm::min(v[0], v[1]), v[2]);
    }
    glm::vec3 getUpperBound() const
    {
        return glm::max(glm::max(v[0], v[1]), v[2]);
    }
    HitInfo intersect(const Ray& ray) const;
};

#endif /* Triangle_h */
