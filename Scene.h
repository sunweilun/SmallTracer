//
//  Scene.hpp
//  SmallTracer
//
//  Created by Weilun Sun on 10/10/15.
//  Copyright © 2015 UC Berkeley. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include "Light.h"
#include "Ray.h"
#include "HitInfo.h"
#include "KDTree.h"
#include "GeometryObject.h"
#include <glm/glm.hpp>
#include <vector>
#include "ObjParser.hpp"

class Scene : public ObjParser
{
protected:
    KDTree<std::shared_ptr<GeometryObject> > tree;
    virtual void process_vertex(void* args, const glm::vec3& v);
    virtual void process_normal(void* args, const glm::vec3& n);
    virtual void process_texture(void* args, const glm::vec3& t);
    virtual void process_group(void* args, const std::string& name) {}
    virtual void process_triangleFan(void* args, const std::vector<glm::uvec3> vtn_list);
public:
    void loadObj(std::string& path);
    void build()
    {
        for(unsigned i=0; i<geometryObjects.size(); i++)
            geometryObjects[i]->build();
        tree.build(geometryObjects);
    }
    std::vector<std::shared_ptr<Light> > lights;
    std::vector<std::shared_ptr<GeometryObject> > geometryObjects;
    HitInfo intersect(const Ray& ray) const
    {
        return tree.intersect<Ray, HitInfo>(ray);
    }
};

#endif /* Scene_hpp */
