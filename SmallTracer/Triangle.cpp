//
//  Triangle.cpp
//  SmallTracer
//
//  Created by Weilun Sun on 10/10/15.
//  Copyright © 2015 UC Berkeley. All rights reserved.
//

#include <stdio.h>
#include "Triangle.h"

HitInfo Triangle::intersect(const Ray& ray) const
{
    HitInfo info;
    glm::mat3 mat;
    mat[0] = -ray.direction;
    mat[1] = v[1] - v[0];
    mat[2] = v[2] - v[0];
    glm::vec3 tuv = glm::inverse(mat) * (ray.origin - v[0]);
    if(tuv[1] < 0 || tuv[1] > 1)
        return info;
    if(tuv[2] < 0 || tuv[2] > 1)
        return info;
    if(tuv[1] + tuv[2] > 1)
        return info;
    info.dist = tuv[0];
    info.normal = n[0]*(1-tuv[1]-tuv[2])+n[1]*tuv[1]+n[2]*tuv[2];
    info.normal = glm::normalize(info.normal);
    info.texCoord = t[0]*(1-tuv[1]-tuv[2])+t[1]*tuv[1]+t[2]*tuv[2];
    return info;
}