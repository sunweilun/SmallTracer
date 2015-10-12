//
//  Scene.cpp
//  SmallTracer
//
//  Created by Weilun Sun on 10/10/15.
//  Copyright © 2015 UC Berkeley. All rights reserved.
//

#include "Scene.h"
#include "TriangleMesh.h"

struct TempData
{
    std::vector<glm::vec3> vList, tList, nList;
    std::vector<Triangle> triangles;
};

void Scene::process_vertex(void* args, const glm::vec3& v)
{
    TempData *tempData = (TempData*)args;
    tempData->vList.push_back(v);
}

void Scene::process_normal(void* args, const glm::vec3& n)
{
    TempData *tempData = (TempData*)args;
    tempData->nList.push_back(n);
}

void Scene::process_texture(void* args, const glm::vec3& t)
{
    TempData *tempData = (TempData*)args;
    tempData->tList.push_back(t);
}

void Scene::process_triangleFan(void* args, const std::vector<glm::uvec3> vtn_list)
{
    TempData *tempData = (TempData*)args;
    if(vtn_list.size() < 3)
        return;
    
    glm::uvec3 vtn[3];
    vtn[0] = vtn_list[0];
    vtn[1] = vtn_list[1];
    for(unsigned i=2; i<vtn_list.size(); i++)
    {
        vtn[2] = vtn_list[i];
        Triangle triangle;
        for(unsigned k=0; k<3; k++)
        {
            triangle.v[k] = tempData->vList[vtn[k][0]-1];
        }
        glm::vec3 backupNormal = glm::normalize(glm::cross(triangle.v[0]-triangle.v[1], triangle.v[2]-triangle.v[1]));
        glm::vec3 backupCoord;
        for(unsigned k=0; k<3; k++)
        {
            triangle.t[k] = vtn[k][1] > 0 ? tempData->tList[vtn[k][1]-1] : backupCoord;
            triangle.n[k] = vtn[k][2] > 0 ? tempData->nList[vtn[k][2]-1] : backupNormal;
        }
        tempData->triangles.push_back(triangle);
        vtn[1] = vtn_list[i];
    }
}

void Scene::loadObj(std::string& path)
{
    TempData tempData;
    parse(&tempData, path);
    std::shared_ptr<TriangleMesh> triangleMesh(new TriangleMesh);
    triangleMesh->triangles = tempData.triangles;
    geometryObjects.push_back(triangleMesh);
}