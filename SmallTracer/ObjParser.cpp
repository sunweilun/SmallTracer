//
//  ObjParser.cpp
//  SmallTracer
//
//  Created by Weilun Sun on 10/10/15.
//  Copyright © 2015 UC Berkeley. All rights reserved.
//

#include "ObjParser.hpp"
#include <sstream>
#include <iostream>

void ObjParser::parse(void* args, std::string& path)
{
    FILE* file = fopen(path.c_str(), "r");
    char line[1024];
    std::string cmd;
    std::string arg;
    
    while(fgets(line, 1024, file))
    {
        std::istringstream iss(line);
        iss >> cmd;
        if(cmd == "g")
        {
            iss >> arg;
            process_group(args, arg);
        }
        if(cmd == "v")
        {
            glm::vec3 v;
            iss >> v.x >> v.y >> v.z;
            process_vertex(args, v);
        }
        if(cmd == "vt")
        {
            glm::vec3 t;
            iss >> t.x >> t.y >> t.z;
            process_texture(args, t);
        }
        if(cmd == "vn")
        {
            glm::vec3 n;
            iss >> n.x >> n.y >> n.z;
            process_normal(args, n);
        }
        if(cmd == "f")
        {
            std::vector<glm::uvec3> vtn_list;
            while(iss >> arg)
            {
                glm::uvec3 vtn;
                if(sscanf(arg.c_str(), "%u/%u/%u", &vtn[0], &vtn[1], &vtn[2]) == 3 ||
                   sscanf(arg.c_str(), "%u/%u", &vtn[0], &vtn[1]) == 2 ||
                   sscanf(arg.c_str(), "%u//%u", &vtn[0], &vtn[2]) == 2 ||
                   sscanf(arg.c_str(), "%u", &vtn[0]) == 1)
                    vtn_list.push_back(vtn);
            }
            process_triangleFan(args, vtn_list);
        }
    }
    
    fclose(file);
}