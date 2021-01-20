#pragma once

#ifndef GRAPHIC_ENGINE_H
#define GRAPHIC_ENGINE_H

#define EPSILON 1e-5f

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <list>

#include "../geometry/geometry.h"
#include "../geometry/matrix_transformation.h"
#include "../model/mesh.h"


#include "ConsoleGameEngine.h"

struct BoundingBox
{
    int min_x, min_y;
    int max_x, max_y;
};

class GraphicEngine : public ConsoleGameEngine
{
public:

    GraphicEngine()
    {
        m_sAppName = L"CleveRender";
    }

public:
    // Inherited via olcConsoleGameEngine
    bool OnUserCreate() override;
    
    bool OnUserUpdate(float fElapsedTime) override;
    
    void TexturedTriangle(Triangle& tris, Sprite* tex);
    
    void TexturedTriangle(Triangle& tris);

    void loadObj(const char* filename)
    {
        objFile = filename;
    }

    void ShowLine(bool show)
    {
        showLine = show;
    }

    void ShowBox(bool show)
    {
        showBox = show;
    }
    
protected:
    BoundingBox createBoundingBox(const std::vector<geo::vec2>& tri);

    geo::vec3 calculateWeights(const std::vector<geo::vec2>& tri, const geo::vec2& p);

    float interpolateDepth(const geo::vec3& screenDepth, const geo::vec3& weights);

    geo::vec2 interpolateTexture(const std::vector<geo::vec2>& textures, const geo::vec3& weights);

    geo::vec3 interpolateNormal(const std::vector<geo::vec3>& normals, const geo::vec3& weights);

    //Color from black to white represented by 0x0000 to 0x00F0 
    short getColorFromTexture(unsigned char* texture, float u, float v);

private:
    void processInput(float fElapsedTime);
    
    CHAR_INFO GetColor(float lum);

    /*
    * @param plane_p : point on the line
    * @param plane_n : normal on the line
    * @param lintStart : starting Point of the line
    * @param lintEnd : ending Point of the line
    */
    geo::vec4 vectorIntersectPlane(geo::vec3& plane_p, geo::vec3& plane_n,
        const geo::vec3& lineStart, const geo::vec3& lineEnd, float& t);

    int triangleClipAgainstPlane(geo::vec3 plane_p, geo::vec3 plane_n, Triangle& in_tri, Triangle& out_tri1, Triangle& out_tri2);
    
private:
    mesh meshCube;
    geo::mat4 projection;
    geo::mat4 model_transform;
    geo::mat4 view;
    geo::vec3 vCamera{ 0.0f, 0.0f, 8.0f };

    geo::vec3 front{ 0.0f, 0.0f, -1.0f };
    geo::vec3 right{ 1.0f, 0.0f, 0.0f };
    geo::vec3 up{ 0.0f, 1.0f, 0.0f };


    float fTheta = 0.f;

    float pitch = 0.0f; //rotate around X axis
    float yaw = -90.0f; //rotate around Y axis  

    Sprite* sprTex1;

    float* pDepthBuffer = nullptr;

    unsigned char* texture = nullptr;


    bool showLine = false;
    bool showBox = false;

    const char* objFile = "./obj/body.obj";

    //deprecated, the console can't show RGB image
    int width, height, channel;
};


#endif // !GRAPHIC_ENGINE_H
