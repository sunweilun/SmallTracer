//
//  PinholeCamera.cpp
//  SmallTracer
//
//  Created by Weilun Sun on 10/10/15.
//  Copyright © 2015 UC Berkeley. All rights reserved.
//

#include <stdio.h>
#include "PinholeCamera.h"

std::vector<Ray> PinholeCamera::generateViewRays(const glm::uvec2 &filmSize) const
{
    glm::vec3 front = glm::normalize(focus - origin);
    glm::vec3 right = glm::normalize(glm::cross(front, up));
    glm::vec3 rectUp = glm::cross(right, front);
    glm::mat3 transMat;
    transMat[0] = right;
    transMat[1] = rectUp;
    transMat[2] = front;
    
    std::vector<Ray> rays(filmSize[0] * filmSize[1]);
    for(unsigned i = 0; i < filmSize[1]; i++)
    {
        for(unsigned j = 0; j < filmSize[0]; j++)
        {
            Ray& ray = rays[i*filmSize[0]+j];
            ray.origin = origin;
            glm::vec3 local_dir;
            local_dir.x = j+0.5-filmSize[0]*0.5;
            local_dir.y = filmSize[1]*0.5-i-0.5;
            local_dir.z = filmSize[1]*0.5/tan(fovy*0.5);
            ray.direction = glm::normalize(transMat * local_dir);
        }
    }
    return rays;
}