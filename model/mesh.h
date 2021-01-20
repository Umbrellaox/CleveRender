#pragma once

#ifndef __MESH__H
#define __MESH__H

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "../geometry/geometry.h"

struct Triangle
{

    geo::vec4 point[3];
    geo::vec2 texture[3];
    geo::vec3 normal[3];

    Triangle()
    {}

    Triangle(const geo::vec4& point1, const geo::vec4& point2, const geo::vec4& point3)
        : point{ point1, point2, point3 }
    {}

    Triangle(const geo::vec4& point1, const geo::vec4& point2, const geo::vec4& point3,
        const geo::vec2 texture1, const geo::vec2& texture2, const geo::vec2& texture3)
        : point{ point1, point2, point3 },
        texture{ texture1, texture2, texture3 }
    {}

    Triangle(const geo::vec4& point1, const geo::vec4& point2, const geo::vec4& point3,
        const geo::vec2 texture1, const geo::vec2& texture2, const geo::vec2& texture3,
        const geo::vec3 normal1, const geo::vec3& normal2, const geo::vec3&normal3)
        : point{ point1, point2, point3 },
        texture{ texture1, texture2, texture3 },
        normal{ normal1, normal2, normal3 }
    {}

    geo::vec4& operator[](int i)
    {
        return point[i];
    }

    wchar_t sym;
    short col;
};

struct mesh
{
    std::vector<Triangle> tris_;

    bool LoadFromObjectFile(const std::string& filename, bool bHasTexture = false, bool bHasNormal = false)
    {
        std::ifstream file(filename);
        if (!file.is_open()) return false;

        std::vector<geo::vec4> verts;
        std::vector<geo::vec2> texs;
        std::vector<geo::vec3> normals;
        while (!file.eof())
        {
            std::string line;
            std::getline(file, line);
            std::istringstream ss(line);

            char trash;

            if (line[0] == 'v')
            {
                if (line[1] == 't')
                {
                    geo::vec2 vt;
                    ss >> trash >> trash >> vt.u >> vt.v;
                    texs.push_back(vt);
                }
                else if (line[1] == 'n')
                {
                    geo::vec3 vn;
                    ss >> trash >> trash >> vn.x >> vn.y >> vn.z;
                    normals.push_back(vn);
                }
                else
                {
                    geo::vec4 v;
                    ss >> trash >> v.x >> v.y >> v.z;
                    v.w = 1.0f;
                    verts.push_back(v);
                }
            }

            if (!bHasTexture && !bHasNormal)
            {
                if (line[0] == 'f')
                {
                    int f[3];
                    ss >> trash >> f[0] >> f[1] >> f[2];
                    tris_.push_back({ verts[f[0] - 1], verts[f[1] - 1], verts[f[2] - 1] });
                }
            }
            else
            {
                if (line[0] == 'f')
                {
                    ss >> trash;

                    std::string tokens[9];
                    int nTokenCount = -1;

                    while (!ss.eof() && nTokenCount < 9)
                    {
                        char c = ss.get();
                        if (c == ' ' || c == '/')
                            nTokenCount++;
                        else
                            tokens[nTokenCount].append(1, c);
                    }

                    //tokens[nTokenCount].pop_back();

                    tris_.push_back({ 
                        verts[stoi(tokens[0]) - 1], verts[stoi(tokens[3]) - 1], verts[stoi(tokens[6]) - 1],
                        texs[stoi(tokens[1]) - 1], texs[stoi(tokens[4]) - 1], texs[stoi(tokens[7]) - 1],
                        normals[stoi(tokens[2]) - 1], normals[stoi(tokens[5]) - 1], normals[stoi(tokens[8]) - 1]});
                }
            }
        }
        return true;
    }
};




#endif