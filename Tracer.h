//
//  Tracer.h
//  SmallTracer
//
//  Created by Weilun Sun on 10/10/15.
//  Copyright © 2015 UC Berkeley. All rights reserved.
//

#ifndef Tracer_h
#define Tracer_h

#include "Camera.h"
#include "Scene.h"
#ifdef linux
#include <omp.h>
#endif

#define EPSILON 1e-5f

class Tracer
{
public:
    virtual std::vector<glm::vec3> trace(const std::shared_ptr<Scene> scene,
                                         const std::shared_ptr<Camera> camera,
                                         const glm::uvec2& filmSize) const
    {
        std::vector<Ray> rays = camera->generateViewRays(filmSize);
        std::vector<glm::vec3> pixels(rays.size());
#ifdef linux
#pragma omp parallel for
#endif
        for(int i=0; i<pixels.size(); i++)
        {
            HitInfo info = scene->intersect(rays[i]);
            if(info.hit())
            {
                for(unsigned k=0; k<scene->lights.size(); k++)
                {
                    Ray lightRay = scene->lights[k]->sample();
                    Ray shadowRay;
                    shadowRay.origin = lightRay.origin;
                    glm::vec3 hitPoint = rays[i].origin + rays[i].direction * info.dist;
                    shadowRay.direction = hitPoint - lightRay.origin;
                    float dist = glm::length(shadowRay.direction);
                    shadowRay.direction = glm::normalize(shadowRay.direction);
                    HitInfo shadowInfo = scene->intersect(shadowRay);
                    if(shadowInfo.hit() && shadowInfo.dist < dist*(1-EPSILON))
                        continue;
                    glm::vec3 radiance = lightRay.radiance * info.material->getBSDF(rays[i].direction, shadowRay.direction, info);
                    radiance *= fabs(glm::dot(shadowRay.direction, info.normal));
                    pixels[i] += radiance;
                }
            }
        }
        return pixels;
    }
};

#endif /* Tracer_h */
