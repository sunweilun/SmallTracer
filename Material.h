//
//  Material.h
//  SmallTracer
//
//  Created by Weilun Sun on 10/10/15.
//  Copyright © 2015 UC Berkeley. All rights reserved.
//

#ifndef Material_h
#define Material_h

#include "Ray.h"
#include "HitInfo.h"

class HitInfo;

class Material
{
public:
    virtual glm::vec3 getBSDF(const glm::vec3 &inDir, const glm::vec3 &outDir, const HitInfo& hitInfo) const { return glm::vec3(); }
};

#endif /* Material_h */
