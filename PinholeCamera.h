//
//  PinholeCamera.h
//  SmallTracer
//
//  Created by Weilun Sun on 10/10/15.
//  Copyright © 2015 UC Berkeley. All rights reserved.
//

#ifndef PinholeCamera_h
#define PinholeCamera_h

#include "Camera.h"
#include <vector>

class PinholeCamera : public Camera
{
protected:
    glm::vec3 origin, focus, up;
    float fovy;
public:
    void setView(const glm::vec3& origin, const glm::vec3& focus, const glm::vec3& up)
    {
        this->origin = origin;
        this->focus = focus;
        this->up = up;
    }
    
    void set_fovy(float fovy) { this->fovy = fovy; }
    virtual std::vector<Ray> generateViewRays(const glm::uvec2& filmSize) const;
};

#endif /* PinholeCamera_h */
