//
//  HitInfo.h
//  SmallTracer
//
//  Created by Weilun Sun on 10/10/15.
//  Copyright © 2015 UC Berkeley. All rights reserved.
//

#ifndef HitInfo_h
#define HitInfo_h
#include "Material.h"
#include <stdlib.h>
#include <limits>

class Material;

class HitInfo
{
public:
    unsigned index;
    float dist;
    glm::vec3 normal;
    glm::vec3 texCoord;
    Material* material;
    
    bool hit() const { return dist != std::numeric_limits<float>::infinity(); }
    
    HitInfo()
    {
        dist = std::numeric_limits<float>::infinity();
    }
    
    float getDist() const { return dist; }
    unsigned getIndex() const { return index; }
    void setIndex(unsigned index) { this->index = index; }
};

#endif /* HitInfo_h */
