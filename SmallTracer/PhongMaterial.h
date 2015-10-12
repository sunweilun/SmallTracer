//
//  PhongMaterial.h
//  SmallTracer
//
//  Created by Weilun Sun on 10/10/15.
//  Copyright © 2015 UC Berkeley. All rights reserved.
//

#ifndef PhongMaterial_h
#define PhongMaterial_h

#include "Material.h"

class PhongMaterial : public Material
{
protected:
    glm::vec3 diffuseColor;
public:
    void setDiffuseColor(const glm::vec3& color) { diffuseColor = color; }
    glm::vec3 getBSDF(const glm::vec3 &inDir, const glm::vec3 &outDir, const HitInfo& hitInfo) const
    {
        return diffuseColor * (1.0f / float(M_PI));
    }
};

#endif /* PhongMaterial_h */
