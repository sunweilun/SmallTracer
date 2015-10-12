//
//  ObjParser.hpp
//  SmallTracer
//
//  Created by Weilun Sun on 10/10/15.
//  Copyright © 2015 UC Berkeley. All rights reserved.
//

#ifndef ObjParser_hpp
#define ObjParser_hpp

#include <stdio.h>
#include <glm/glm.hpp>
#include <string>
#include <string.h>
#include <vector>

class ObjParser
{
protected:
    virtual void process_vertex(void* args, const glm::vec3& v) {}
    virtual void process_normal(void* args, const glm::vec3& n) {}
    virtual void process_texture(void* args, const glm::vec3& t) {}
    virtual void process_group(void* args, const std::string& name) {}
    virtual void process_triangleFan(void* args, const std::vector<glm::uvec3> vtn_list) {}
public:
    void parse(void* args, std::string& path);
};

#endif /* ObjParser_hpp */
