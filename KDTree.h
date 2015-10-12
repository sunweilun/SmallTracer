//
//  KDTree.h
//  RayTracer
//
//  Created by Weilun Sun on 2/26/15.
//  Copyright (c) 2015 UC Berkeley. All rights reserved.
//

#ifndef RayTracer_KDTree_h
#define RayTracer_KDTree_h

#include <glm/glm.hpp>
#include <vector>
#include <algorithm>

#ifdef linux
#include <tr1/memory>
namespace std{ using namespace std::tr1; }
#endif

/*
Define your classes as below.
 
class HitInfo
{
public:
    float getDist() const;
    unsigned getIndex() const;
    void setIndex(unsigned index) const;
};

class Ray
{
public:
    glm::vec3 getOrig() const;
    glm::vec3 getDir() const;
};

class Geo
{
public:
    glm::vec3 getLowerBound() const;
    glm::vec3 getUpperBound() const;
    HitInfo intersect(const Ray& ray) const;
};
 */

template<typename T>
struct ptr
{
    static T* get(const T& obj) { return (T*)&obj; }
};

template<typename T>
struct ptr<T*>
{
    static T* get(T* obj) { return obj; }
};

template<typename T>
struct ptr<std::shared_ptr<T> >
{
    static T* get(std::shared_ptr<T> obj) { return (T*)&*obj; }
};


inline void mergeBounds(glm::vec3* b, const glm::vec3* b1, const glm::vec3* b2)
{
    b[0].x = b1[0].x < b2[0].x ? b1[0].x : b2[0].x;
    b[0].y = b1[0].y < b2[0].y ? b1[0].y : b2[0].y;
    b[0].z = b1[0].z < b2[0].z ? b1[0].z : b2[0].z;
    b[1].x = b1[1].x > b2[1].x ? b1[1].x : b2[1].x;
    b[1].y = b1[1].y > b2[1].y ? b1[1].y : b2[1].y;
    b[1].z = b1[1].z > b2[1].z ? b1[1].z : b2[1].z;
}

template<typename Geo> class KDTree
{
protected:
    struct KDTreeNode
    {
        glm::vec3 bounds[2];
        KDTreeNode* leftChild;
        KDTreeNode* rightChild;
        unsigned startIndex;
        unsigned num;
        
        KDTreeNode()
        {
            leftChild = rightChild = NULL;
        }
    };
    KDTreeNode* root;
    std::vector<Geo>* geoList;
    unsigned maxLeafElemNum;
    
    void nodeMergeBounds(KDTreeNode* node, const glm::vec3* b1, const glm::vec3* b2)
    {
        mergeBounds((glm::vec3*)node->bounds, b1, b2);
    }
    
    void fillBounds(KDTreeNode* node)
    {
        node->bounds[0] = ptr<Geo>::get((*geoList)[node->startIndex])->getLowerBound();
        node->bounds[1] = ptr<Geo>::get((*geoList)[node->startIndex])->getUpperBound();
        for(unsigned i=node->startIndex+1; i<node->startIndex+node->num; i++)
        {
            glm::vec3 lb = ptr<Geo>::get((*geoList)[i])->getLowerBound();
            glm::vec3 ub = ptr<Geo>::get((*geoList)[i])->getUpperBound();
            node->bounds[0].x = node->bounds[0].x < lb.x ? node->bounds[0].x : lb.x;
            node->bounds[0].y = node->bounds[0].y < lb.y ? node->bounds[0].y : lb.y;
            node->bounds[0].z = node->bounds[0].z < lb.z ? node->bounds[0].z : lb.z;
            node->bounds[1].x = node->bounds[1].x > ub.x ? node->bounds[1].x : ub.x;
            node->bounds[1].y = node->bounds[1].y > ub.y ? node->bounds[1].y : ub.y;
            node->bounds[1].z = node->bounds[1].z > ub.z ? node->bounds[1].z : ub.z;
        }
    }
    
    static bool compareX(const Geo& g1, const Geo& g2)
    {
        float x1 = ptr<Geo>::get(g1)->getLowerBound().x+ptr<Geo>::get(g1)->getUpperBound().x;
        float x2 = ptr<Geo>::get(g2)->getLowerBound().x+ptr<Geo>::get(g2)->getUpperBound().x;
        return x1 < x2;
    }
    
    static bool compareY(const Geo& g1, const Geo& g2)
    {
        float y1 = ptr<Geo>::get(g1)->getLowerBound().y+ptr<Geo>::get(g1)->getUpperBound().y;
        float y2 = ptr<Geo>::get(g2)->getLowerBound().y+ptr<Geo>::get(g2)->getUpperBound().y;
        return y1 < y2;
    }
    
    static bool compareZ(const Geo& g1, const Geo& g2)
    {
        float z1 = ptr<Geo>::get(g1)->getLowerBound().z+ptr<Geo>::get(g1)->getUpperBound().z;
        float z2 = ptr<Geo>::get(g2)->getLowerBound().z+ptr<Geo>::get(g2)->getUpperBound().z;
        return z1 < z2;
    }
    
    void splitNode(KDTreeNode* node, int dim)
    {
        if(node->num <= maxLeafElemNum)
        {
            fillBounds(node);
            return;
        }
        
        switch (dim) {
            case 1:
                std::nth_element(geoList->begin()+node->startIndex,
                                 geoList->begin()+node->startIndex+node->num/2,
                                 geoList->begin()+node->startIndex+node->num, compareY);
                break;
            case 2:
                std::nth_element(geoList->begin()+node->startIndex,
                                 geoList->begin()+node->startIndex+node->num/2,
                                 geoList->begin()+node->startIndex+node->num, compareZ);
                break;
            default:
                std::nth_element(geoList->begin()+node->startIndex,
                                 geoList->begin()+node->startIndex+node->num/2,
                                 geoList->begin()+node->startIndex+node->num, compareX);
                break;
        }
        node->leftChild = new KDTreeNode;
        node->leftChild->startIndex = node->startIndex;
        node->leftChild->num = node->num/2;
        
        node->rightChild = new KDTreeNode;
        node->rightChild->startIndex = node->startIndex + node->num/2;
        node->rightChild->num = node->num - node->num/2;
        
        splitNode(node->leftChild, (dim+1)%3);
        splitNode(node->rightChild, (dim+1)%3);
        
        nodeMergeBounds(node, node->leftChild->bounds, node->rightChild->bounds);
    }
    
    template<typename Ray> inline bool intersectBB(const Ray& ray, glm::vec3 bounds[2]) const
    {
        glm::vec3 invdir = 1.0f / ray.getDir();
        
        int s0 = invdir.x < 0;
        int s1 = invdir.y < 0;
        int s2 = invdir.z < 0;
        
        float tmin, tmax, tymin, tymax, tzmin, tzmax;
        tmin = (bounds[s0].x - ray.getOrig().x) * invdir.x;
        tmax = (bounds[1-s0].x - ray.getOrig().x) * invdir.x;
        tymin = (bounds[s1].y - ray.getOrig().y) * invdir.y;
        tymax = (bounds[1-s1].y - ray.getOrig().y) * invdir.y;
        if ((tmin > tymax) || (tymin > tmax))
            return false;
        if (tymin > tmin)
            tmin = tymin;
        if (tymax < tmax)
            tmax = tymax;
        tzmin = (bounds[s2].z - ray.getOrig().z) * invdir.z;
        tzmax = (bounds[1-s2].z - ray.getOrig().z) * invdir.z;
        if ((tmin > tzmax) || (tzmin > tmax))
            return false;
        if (tzmin > tmin)
            tmin = tzmin;
        if (tzmax < tmax)
            tmax = tzmax;
        
        if(tmax < 0)
            return false;
        
        return true;
    }
    
    void clearNode(KDTreeNode* node)
    {
        if(!node)
            return;
        if(node->leftChild)
            clearNode(node->leftChild);
        if(node->rightChild)
            clearNode(node->rightChild);
        delete node;
    }
    
    template<typename Ray, typename HitInfo> HitInfo intersectNode(KDTreeNode* node, const Ray& ray) const
    {
        if(!intersectBB<Ray>(ray, node->bounds))
            return HitInfo();
        if(node->leftChild == NULL)
        {
            HitInfo info;
            for(unsigned i=node->startIndex; i<node->startIndex+node->num; i++)
            {
                HitInfo newInfo = ptr<Geo>::get((*geoList)[i])->intersect(ray);
                if(newInfo.getDist() < info.getDist())
                {
                    info = newInfo;
                    info.setIndex(i);
                }
            }
            return info;
        }
        HitInfo lInfo = intersectNode<Ray, HitInfo>(node->leftChild, ray);
        HitInfo rInfo = intersectNode<Ray, HitInfo>(node->rightChild, ray);
        if(lInfo.getDist() < rInfo.getDist())
            return lInfo;
        return rInfo;
    }
    
    inline bool sphereOverlapBB(const glm::vec3& center, float r, glm::vec3 bounds[2])
    {
        if(center.x+r < bounds[0].x)
            return false;
        if(center.y+r < bounds[0].y)
            return false;
        if(center.z+r < bounds[0].z)
            return false;
        if(center.x-r > bounds[1].x)
            return false;
        if(center.y-r > bounds[1].y)
            return false;
        if(center.z-r > bounds[1].z)
            return false;
        return true;
    }
    
    std::vector<unsigned> queryInSphereNode(KDTreeNode* node, const glm::vec3& center, float r)
    {
        std::vector<unsigned> indices;
        if(!sphereOverlapBB(center, r, node->bounds))
            return indices;
        if(node->leftChild == NULL)
        {
            for(unsigned i=node->startIndex; i<node->startIndex+node->num; i++)
            {
                glm::vec3 bounds[2];
                bounds[0] = ptr<Geo>::get((*geoList)[i])->getLowerBound();
                bounds[1] = ptr<Geo>::get((*geoList)[i])->getUpperBound();
                if(glm::length(center - bounds[0]) < r)
                    indices.push_back(i);
            }
            return indices;
        }
        std::vector<unsigned> lIndices = queryInSphereNode(node->leftChild, center, r);
        std::vector<unsigned> rIndices = queryInSphereNode(node->rightChild, center, r);
        lIndices.insert(lIndices.end(), rIndices.begin(), rIndices.end());
        return lIndices;
    }
public:
    void clear()
    {
        geoList = NULL;
        clearNode(root);
        root = NULL;
    }
    glm::vec3 getLowerBound() const { return root ? root->bounds[0] : glm::vec3(); }
    glm::vec3 getUpperBound() const { return root ? root->bounds[1] : glm::vec3(); }
    KDTree()
    {
        root = NULL;
        maxLeafElemNum = 1;
        clear();
    }
    void build(std::vector<Geo>& geoList, unsigned maxLeafElemNum = 1)
    {
        clear();
        this->geoList = &geoList;
        this->maxLeafElemNum = maxLeafElemNum;
        root = new KDTreeNode;
        root->startIndex = 0;
        root->num = unsigned(geoList.size());
        splitNode(root, 0);
    }
    
    std::vector<unsigned> queryInSphere(const glm::vec3& center, float r)
    {
        return queryInSphereNode(root, center, r);
    }
    
    template<typename Ray, typename HitInfo> HitInfo intersect(const Ray& ray) const
    {
        return intersectNode<Ray, HitInfo>(root, ray);
    }
    ~KDTree() { clear(); }
};

#endif
