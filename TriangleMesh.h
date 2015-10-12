//
//  TriangleMesh.h
//  SmallTracer
//
//  Created by Weilun Sun on 10/10/15.
//  Copyright © 2015 UC Berkeley. All rights reserved.
//

#ifndef TriangleMesh_h
#define TriangleMesh_h

#include "GeometryObject.h"
#include "Triangle.h"
#include "KDTree.h"
#include <vector>

class TriangleMesh : public GeometryObject
{
protected:
    KDTree<Triangle> tree;
public:
    std::vector<Triangle> triangles;
    virtual void build() { tree.build(triangles); }
    glm::vec3 getLowerBound() const
    {
        return tree.getLowerBound();
    }
    glm::vec3 getUpperBound() const
    {
        return tree.getUpperBound();
    }
    HitInfo intersect(const Ray& ray) const
    {
        HitInfo info = tree.intersect<Ray, HitInfo>(ray);
        info.material = &*material;
        return info;
    }
};

#endif /* TriangleMesh_h */
