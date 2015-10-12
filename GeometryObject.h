//
//  GeometryObject.hpp
//  SmallTracer
//
//  Created by Weilun Sun on 10/10/15.
//  Copyright © 2015 UC Berkeley. All rights reserved.
//

#ifndef GeometryObject_hpp
#define GeometryObject_hpp

#include <stdio.h>
#include <glm/glm.hpp>
#include "Ray.h"
#include "HitInfo.h"
#include "Material.h"

#ifdef linux
#include <tr1/memory>
namespace std{ using namespace std::tr1; }
#endif

class GeometryObject
{
public:
    std::shared_ptr<Material> material;
    virtual void build() {}
    virtual glm::vec3 getLowerBound() const { return glm::vec3(); }
    virtual glm::vec3 getUpperBound() const { return glm::vec3(); }
    virtual HitInfo intersect(const Ray& ray) const { return HitInfo(); }
};

#endif /* GeometryObject_hpp */
