//
//  PointLight.h
//  SmallTracer
//
//  Created by Weilun Sun on 10/10/15.
//  Copyright © 2015 UC Berkeley. All rights reserved.
//

#ifndef PointLight_h
#define PointLight_h

#include "Light.h"

class PointLight : public Light
{
protected:
    glm::vec3 position;
    glm::vec3 radiance;
public:
    void setPosition(const glm::vec3& pos) { position = pos; }
    void setRadiance(const glm::vec3& rad) { radiance = rad; }
    virtual Ray sample() const
    {
        Ray ray;
        ray.origin = position;
        ray.radiance = radiance;
        return ray;
    }
};

#endif /* PointLight_h */
