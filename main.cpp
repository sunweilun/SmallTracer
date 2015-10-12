//
//  main.cpp
//  SmallTracer
//
//  Created by Weilun Sun on 10/10/15.
//  Copyright © 2015 UC Berkeley. All rights reserved.
//
#include "PinholeCamera.h"
#include "TriangleMesh.h"
#include "PointLight.h"
#include "PhongMaterial.h"
#include "Tracer.h"
#include <opencv2/opencv.hpp>

int main(int argc, const char * argv[]) {
    std::string path = "/Users/weilunsun/Documents/Data/obj/toyplane.obj";
    
    Tracer tracer;
    std::shared_ptr<Scene> scene(new Scene);
    scene->loadObj(path);
    
    std::shared_ptr<PhongMaterial> grey(new PhongMaterial);
    grey->setDiffuseColor(glm::vec3(0.8, 0.8, 0.8));
    
    scene->geometryObjects.back()->material = grey;
    
    std::shared_ptr<TriangleMesh> mesh(new TriangleMesh);
    Triangle t;
    t.v[0] = glm::vec3(-100, -20, -100);
    t.v[1] = glm::vec3(100, -20, -100);
    t.v[2] = glm::vec3(100, -20, 100);
    t.n[0] = t.n[1] = t.n[2] = glm::vec3(0, 1, 0);
    mesh->triangles.push_back(t);
    
    t.v[0] = glm::vec3(-100, -20, -100);
    t.v[1] = glm::vec3(100, -20, 100);
    t.v[2] = glm::vec3(-100, -20, 100);
    t.n[0] = t.n[1] = t.n[2] = glm::vec3(0, 1, 0);
    mesh->triangles.push_back(t);
    
    scene->geometryObjects.push_back(mesh);
    
    scene->geometryObjects.back()->material = grey;
    
    scene->build();
    std::shared_ptr<PinholeCamera> camera(new PinholeCamera);
    camera->set_fovy(90*M_PI / 180);
    camera->setView(glm::vec3(20, 20, 20), glm::vec3(0, -10, 0), glm::vec3(0, 1, 0));
    glm::uvec2 filmSize = glm::uvec2(1024, 768);
    
    int n = 1;
    for(int i=0; i < n; i++)
    {
        for(int j=0; j < n; j++)
        {
            std::shared_ptr<PointLight> light(new PointLight);
            light->setPosition(glm::vec3(30+i/float(n)*5, 100, 30+j/float(n)*5));
            light->setRadiance(glm::vec3(2.5/n/n));
            scene->lights.push_back(light);
        }
    }
    
    std::vector<glm::vec3> film = tracer.trace(scene, camera, filmSize);
    cv::Mat image(filmSize[1], filmSize[0], CV_8UC3);
    for(unsigned i=0; i<filmSize[1]; i++)
    {
        for(unsigned j=0; j<filmSize[0]; j++)
        {
            glm::vec3 color = 255.0f*film[i*filmSize[0]+j];
            color = glm::min(color, glm::vec3(255.0));
            image.at<glm::u8vec3>(i, j) = glm::u8vec3(color[2], color[1], color[0]);
        }
    }
    cv::namedWindow("Tracer");
    cv::imshow("Tracer", image);
    cv::waitKey(0);
    return 0;
}