#include "graphic_engine.h"

bool GraphicEngine::OnUserCreate()
{
    pDepthBuffer = new float[ScreenWidth() * ScreenHeight()];


    if (showBox)
    {
        meshCube.tris_ = {
            // SOUTH
            { geo::vec4{0.0f, 0.0f, 0.0f, 1.0f},    geo::vec4{0.0f, 1.0f, 0.0f, 1.0f},    geo::vec4{1.0f, 1.0f, 0.0f, 1.0f},  geo::vec2{0.0f, 1.0f}, geo::vec2{0.0f, 0.0f}, geo::vec2{1.0f, 0.0f} },
            { geo::vec4{0.0f, 0.0f, 0.0f, 1.0f},    geo::vec4{1.0f, 1.0f, 0.0f, 1.0f},    geo::vec4{1.0f, 0.0f, 0.0f, 1.0f},  geo::vec2{0.0f, 1.0f}, geo::vec2{1.0f, 0.0f}, geo::vec2{1.0f, 1.0f} },
            //EAST                                                                                                                                                        
            { geo::vec4{1.0f, 0.0f, 0.0f, 1.0f},    geo::vec4{1.0f, 1.0f, 0.0f, 1.0f},    geo::vec4{1.0f, 1.0f, 1.0f, 1.0f},  geo::vec2{0.0f, 1.0f}, geo::vec2{0.0f, 0.0f}, geo::vec2{1.0f, 0.0f} },
            { geo::vec4{1.0f, 0.0f, 0.0f, 1.0f},    geo::vec4{1.0f, 1.0f, 1.0f, 1.0f},    geo::vec4{1.0f, 0.0f, 1.0f, 1.0f},  geo::vec2{0.0f, 1.0f}, geo::vec2{1.0f, 0.0f}, geo::vec2{1.0f, 1.0f} },
            //NORTH                                                                                                                                                       
            { geo::vec4{1.0f, 0.0f, 1.0f, 1.0f},    geo::vec4{1.0f, 1.0f, 1.0f, 1.0f},    geo::vec4{0.0f, 1.0f, 1.0f, 1.0f},  geo::vec2{0.0f, 1.0f}, geo::vec2{0.0f, 0.0f}, geo::vec2{1.0f, 0.0f} },
            { geo::vec4{1.0f, 0.0f, 1.0f, 1.0f},    geo::vec4{0.0f, 1.0f, 1.0f, 1.0f},    geo::vec4{0.0f, 0.0f, 1.0f, 1.0f},  geo::vec2{0.0f, 1.0f}, geo::vec2{1.0f, 0.0f}, geo::vec2{1.0f, 1.0f} },
            //WEST                                                                                                                                                        
            { geo::vec4{0.0f, 0.0f, 1.0f, 1.0f},    geo::vec4{0.0f, 1.0f, 1.0f, 1.0f},    geo::vec4{0.0f, 1.0f, 0.0f, 1.0f},  geo::vec2{0.0f, 1.0f}, geo::vec2{0.0f, 0.0f}, geo::vec2{1.0f, 0.0f} },
            { geo::vec4{0.0f, 0.0f, 1.0f, 1.0f},    geo::vec4{0.0f, 1.0f, 0.0f, 1.0f},    geo::vec4{0.0f, 0.0f, 0.0f, 1.0f},  geo::vec2{0.0f, 1.0f}, geo::vec2{1.0f, 0.0f}, geo::vec2{1.0f, 1.0f} },
            //TOP                                                                                                                                                         
            { geo::vec4{0.0f, 1.0f, 0.0f, 1.0f},    geo::vec4{0.0f, 1.0f, 1.0f, 1.0f},    geo::vec4{1.0f, 1.0f, 1.0f, 1.0f},  geo::vec2{0.0f, 1.0f}, geo::vec2{0.0f, 0.0f}, geo::vec2{1.0f, 0.0f} },
            { geo::vec4{0.0f, 1.0f, 0.0f, 1.0f},    geo::vec4{1.0f, 1.0f, 1.0f, 1.0f},    geo::vec4{1.0f, 1.0f, 0.0f, 1.0f},  geo::vec2{0.0f, 1.0f}, geo::vec2{1.0f, 0.0f}, geo::vec2{1.0f, 1.0f} },
            //BOTTOM                                                                                                                                                      
            { geo::vec4{1.0f, 0.0f, 1.0f, 1.0f},    geo::vec4{0.0f, 0.0f, 1.0f, 1.0f},    geo::vec4{0.0f, 0.0f, 0.0f, 1.0f},  geo::vec2{0.0f, 1.0f}, geo::vec2{0.0f, 0.0f}, geo::vec2{1.0f, 0.0f} },
            { geo::vec4{1.0f, 0.0f, 1.0f, 1.0f},    geo::vec4{0.0f, 0.0f, 0.0f, 1.0f},    geo::vec4{1.0f, 0.0f, 0.0f, 1.0f},  geo::vec2{0.0f, 1.0f}, geo::vec2{1.0f, 0.0f}, geo::vec2{1.0f, 1.0f} },
        };

        sprTex1 = new Sprite(L"./obj/leveljario.spr");
    }
    else
    {
        meshCube.LoadFromObjectFile(objFile, true, true);
    }




    float fNear = 0.1f;
    float fFar = 1000.0f;
    float fFovy = 90.0f;

    projection = geo::perspective_RH_NO_OpenGL(geo::radians(fFovy), (float)ScreenWidth() / (float)ScreenHeight(), fNear, fFar);

    return true;
}

bool GraphicEngine::OnUserUpdate(float fElapsedTime)
{

    Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, FG_BLACK);
    // Clear Depth Buffer
    for (int i = 0; i < ScreenWidth() * ScreenHeight(); i++)
        pDepthBuffer[i] = 0.0f;

    processInput(fElapsedTime);

    fTheta += 1.0f * fElapsedTime;

    model_transform = geo::mat4::identity();
    //model_transform = geo::rotate(model_transform, fTheta, geo::vec3(0.0f, 0.0f, 1.0f));
    //model_transform = geo::rotate(model_transform, fTheta, geo::vec3(1.0f, 0.0f, 0.0f));

    view = geo::viewMatrix_LH(vCamera, vCamera + front, geo::vec3(0.0f, 1.0f, 0.0f));

    std::vector<Triangle> vecTrianglesToRaster;


    //Draw Triangles
    for (auto tri : meshCube.tris_) //获取每一个三角形
    {
        //先缩放, 再旋转, 最后位移 -- <Unity Shader入门精要>
        Triangle triProjected, triTransformed;

        triTransformed = tri;
        triTransformed[0] = (model_transform * tri[0]);
        triTransformed[1] = (model_transform * tri[1]);
        triTransformed[2] = (model_transform * tri[2]);

        geo::vec3 normal, line1, line2;
        line1 = triTransformed[1] - triTransformed[0];
        line2 = triTransformed[2] - triTransformed[0];
        normal = geo::cross(line1, line2).normalize();

        //normal = triTransformed.normal[0];

        geo::vec3 viewDir = vCamera - triTransformed[0];
        if (geo::dot(normal, viewDir) > 0.0f)
        {
            //Illumination
            geo::vec3 lightDir = { -1.0f, -1.0f, 1.0f };
            lightDir = lightDir.normalize();

            float dp = geo::dot(normal, lightDir);
            dp = geo::clamp(dp, 0.2f, 1.0f);    //模拟ambient
            CHAR_INFO c = GetColor(dp); //获得灰度值
            triTransformed.col = c.Attributes;
            triTransformed.sym = c.Char.UnicodeChar;

            triTransformed[0] = view * triTransformed[0];
            triTransformed[1] = view * triTransformed[1];
            triTransformed[2] = view * triTransformed[2];

            //Clip Triangle with zNear plane
            int nClippedTriangles = 0;
            Triangle clipped[2];
            nClippedTriangles = triangleClipAgainstPlane({ 0.0f, 0.0f, 0.1f }, { 0.0f, 0.0f, 1.0f }, triTransformed, clipped[0], clipped[1]);

            for (int i = 0; i < nClippedTriangles; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    triProjected[j] = projection * clipped[i][j];
                    triProjected[j].x = triProjected[j].x / triProjected[j].w;
                    triProjected[j].y = triProjected[j].y / triProjected[j].w;
                    triProjected[j].z = triProjected[j].z / triProjected[j].w;

                    triProjected.texture[j] = clipped[i].texture[j];
                    triProjected.normal[j] = clipped[i].normal[j];

                    triProjected[j].x += 1.0f; triProjected[j].y += 1.0f;

                    triProjected[j].x *= 0.5f * (float)ScreenWidth();
                    triProjected[j].y *= 0.5f * (float)ScreenHeight();
                }

                triProjected.col = clipped[i].col;
                triProjected.sym = clipped[i].sym;
                vecTrianglesToRaster.push_back(triProjected);
            }
        }
    }

    // Sort triangles from back to front
    for (auto& triToRaster : vecTrianglesToRaster)
    {
        // Clip triangle against all four screen edges
        Triangle clipped[2];
        std::list<Triangle> listTriangles;
        listTriangles.push_back(triToRaster);
        int nNewTriangles = 1;

        //分别测试该三角形与上下左右四个面是否有重叠, 并裁剪
        for (int p = 0; p < 4; p++)
        {
            int nTrisToAdd = 0;
            while (nNewTriangles > 0)
            {
                Triangle test = listTriangles.front();
                listTriangles.pop_front();
                nNewTriangles--;

                switch (p)
                {
                    //bottom
                case 0:
                    nTrisToAdd = triangleClipAgainstPlane({ 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, test, clipped[0], clipped[1]);
                    break;
                    //top
                case 1:
                    nTrisToAdd = triangleClipAgainstPlane({ 0.0f, (float)ScreenHeight() - 1, 0.0f }, { 0.0f, -1.0f, 0.0f }, test, clipped[0], clipped[1]);
                    break;
                    //left
                case 2:
                    nTrisToAdd = triangleClipAgainstPlane({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, test, clipped[0], clipped[1]);
                    break;
                    //right
                case 3:
                    nTrisToAdd = triangleClipAgainstPlane({ (float)ScreenWidth() - 1, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }, test, clipped[0], clipped[1]);
                    break;
                default:
                    break;
                }

                for (int i = 0; i < nTrisToAdd; i++)
                {
                    //再测试新生成的三角形有没有和其他面产生重叠.
                    listTriangles.push_back(clipped[i]);
                }
            }
            nNewTriangles = listTriangles.size();
        }

        for (auto& t : listTriangles)
        {

            if (showBox)
            {
                TexturedTriangle(t, sprTex1);
            }
            else
            {
                TexturedTriangle(t);

                if (showLine)
                {
                    DrawTriangle(t[0].x, t[0].y, t[1].x, t[1].y, t[2].x, t[2].y, PIXEL_SOLID, FG_WHITE);
                }
            }

        }
    };

    return true;
}

void GraphicEngine::TexturedTriangle(Triangle& tris, Sprite* tex)
{
    std::vector<geo::vec2> screenPos{
                {tris[0].x, tris[0].y},
                {tris[1].x, tris[1].y},
                {tris[2].x, tris[2].y}
    };

    geo::vec3 screenDepth{ tris[0].z, tris[1].z, tris[2].z };

    std::vector<geo::vec2> textures
    {
        {tris.texture[0].u, tris.texture[0].v},
        {tris.texture[1].u, tris.texture[1].v},
        {tris.texture[2].u, tris.texture[2].v}
    };

    BoundingBox bbox = createBoundingBox(screenPos);

    for (int x = bbox.min_x; x <= bbox.max_x; x++)
    {
        for (int y = bbox.min_y; y <= bbox.max_y; y++)
        {
            geo::vec2 point{ (float)x + 0.5f, (float)y + 0.5f };
            geo::vec3 weights = calculateWeights(screenPos, point);
            if (weights[0] < 0.0f || weights[1] < 0.0f || weights[2] < 0.0f)
            {
                continue;
            }
            geo::vec2 texture = interpolateTexture(textures, weights);
            float depth = interpolateDepth(screenDepth, weights);
            //std::cout << texture << std::endl;
            //std::cout.flush();
            int index = y * ScreenWidth() + x;
            if (depth >= pDepthBuffer[index])
            {
                Draw(x, y, PIXEL_SOLID, tex->GetColour(texture.u * tex->nWidth, texture.v * tex->nHeight));
                pDepthBuffer[index] = depth;
            }
        }
    }

}

void GraphicEngine::TexturedTriangle(Triangle& tris)
{
    std::vector<geo::vec2> screenPos{
        {tris[0].x, tris[0].y},
        {tris[1].x, tris[1].y},
        {tris[2].x, tris[2].y}
    };

    std::vector<geo::vec3> normals{ tris.normal[0], tris.normal[1], tris.normal[2] };
    std::vector<geo::vec2> textures
    {
        {tris.texture[0].x, tris.texture[0].y},
        {tris.texture[1].x, tris.texture[1].y},
        {tris.texture[2].x, tris.texture[2].y}
    };
    geo::vec3 screenDepth{ tris[0].z, tris[1].z, tris[2].z };

    BoundingBox bbox = createBoundingBox(screenPos);

    for (int x = bbox.min_x; x <= bbox.max_x; x++)
    {
        for (int y = bbox.min_y; y <= bbox.max_y; y++)
        {
            geo::vec2 point{ (float)x + 0.5f, (float)y + 0.5f };
            geo::vec3 weights = calculateWeights(screenPos, point);
            if (weights[0] < 0.0f || weights[1] < 0.0f || weights[2] < 0.0f)
            {
                continue;
            }
            geo::vec2 texture = interpolateTexture(textures, weights);
            geo::vec3 normal = interpolateNormal(normals, weights);
            float depth = interpolateDepth(screenDepth, weights);

            int index = y * ScreenWidth() + x;
            if (depth >= pDepthBuffer[index])
            {
                Draw(x, y, PIXEL_SOLID, tris.col);
                pDepthBuffer[index] = depth;
            }
        }
    }

}

BoundingBox GraphicEngine::createBoundingBox(const std::vector<geo::vec2>& tri)
{
    geo::vec2 min = geo::vec2_min(geo::vec2_min(tri[0], tri[1]), tri[2]);
    geo::vec2 max = geo::vec2_max(geo::vec2_max(tri[0], tri[1]), tri[2]);
    BoundingBox bbox;
    bbox.min_x = std::max((int)std::floor(min.x), 0);
    bbox.min_y = std::max((int)std::floor(min.y), 0);
    bbox.max_x = std::min((int)std::ceil(max.x), ScreenWidth() - 1);
    bbox.max_y = std::min((int)std::ceil(max.y), ScreenHeight() - 1);
    return bbox;
}

geo::vec3 GraphicEngine::calculateWeights(const std::vector<geo::vec2>& tri, const geo::vec2& p)

{
    geo::vec2 a = tri[0];
    geo::vec2 b = tri[1];
    geo::vec2 c = tri[2];
    geo::vec2 ab = b - a;
    geo::vec2 ac = c - a;
    geo::vec2 ap = p - a;

    float factor = 1 / (ab.x * ac.y - ab.y * ac.x);
    float s = (ac.y * ap.x - ac.x * ap.y) * factor;
    float t = (ab.x * ap.y - ab.y * ap.x) * factor;

    return { 1 - s - t, s, t };
}

float GraphicEngine::interpolateDepth(const geo::vec3& screenDepth, const geo::vec3& weights)
{
    float depth = 0;
    for (size_t i = 0; i < 3; i++)
    {
        depth += screenDepth[i] * weights[i];
    }
    return depth;
}

geo::vec2 GraphicEngine::interpolateTexture(const std::vector<geo::vec2>& textures, const geo::vec3& weights)
{
    auto u = textures[0].u * weights[0] + textures[1].u * weights[1] + textures[2].u * weights[2];
    auto v = textures[0].v * weights[0] + textures[1].v * weights[1] + textures[2].v * weights[2];

    return { u, v };
}

geo::vec3 GraphicEngine::interpolateNormal(const std::vector<geo::vec3>& normals, const geo::vec3& weights)
{
    return { normals[0] * weights[0] + normals[1] * weights[1] + normals[2] * weights[2] };
}

short GraphicEngine::getColorFromTexture(unsigned char* texture, float u, float v)
{
    static int i = 0;
    static int count = 0;
    u = u * width;
    v = v * height;     //获得贴图对应像素位置;
    int index = (v * width + u) * channel;
    unsigned char* pixel = &texture[index];
    unsigned char R = pixel[0];
    unsigned char G = pixel[1];
    unsigned char B = pixel[2];
    short color;
    color = R;

    return color;
}

void GraphicEngine::processInput(float fElapsedTime)
{
    float cameraSpeed = 30.0f;

    /* Right turn right */
    if (GetKey(VK_RIGHT).bHeld)
    {
        yaw += cameraSpeed * fElapsedTime;
    }

    /* Left turn left */
    if (GetKey(VK_LEFT).bHeld)
    {
        yaw -= cameraSpeed * fElapsedTime;
    }


    /* Up turn up */
    if (GetKey(VK_UP).bHeld)
    {
        pitch += cameraSpeed * fElapsedTime;
    }

    /* Down turn down */
    if (GetKey(VK_DOWN).bHeld)
    {
        pitch -= cameraSpeed * fElapsedTime;
    }

    pitch = geo::clamp(pitch, -89.0f, 89.0f);

    front.x = std::cos(geo::radians(pitch)) * std::cos(geo::radians(yaw));
    front.y = std::sin(geo::radians(pitch));
    front.z = std::cos(geo::radians(pitch)) * std::sin(geo::radians(yaw));
    front = front.normalize();
    right = geo::cross(front, geo::vec3(0.0f, 1.0f, 0.0f)).normalize();
    up = geo::cross(front, right).normalize();

    //在观察空间中, 是右手系.
    /*
        * VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
        * 0x3A - 0x40 : unassigned
        * VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
        */

    float speed = 8.0f;
    float velocity = speed * fElapsedTime;
    /* E up */
    if (GetKey(0x45).bHeld)
    {
        vCamera = vCamera - up * velocity;
    }

    /* Q down*/
    if (GetKey(0x51).bHeld)
    {
        vCamera = vCamera + up * velocity;
    }



    /* D right */
    if (GetKey(0x44).bHeld)
    {
        vCamera = vCamera + right * velocity;
    }

    /* A left */
    if (GetKey(0x41).bHeld)
    {
        vCamera = vCamera - right * velocity;
    }

    /* W front */
    //右手系中, 前进时, z值减小
    if (GetKey(0x57).bHeld)
    {
        vCamera = vCamera + front * velocity;
    }

    /* S back */
    //右手系中, 后退时, z值增大
    if (GetKey(0x53).bHeld)
    {
        vCamera = vCamera - front * velocity;
    }


}

CHAR_INFO GraphicEngine::GetColor(float lum)
{
    short bg_col, fg_col;
    wchar_t sym;
    int pixel_bw = (int)(13.0f * lum);
    switch (pixel_bw)
    {
    case 0: bg_col = BG_BLACK; fg_col = FG_BLACK; sym = PIXEL_SOLID; break;

    case 1: bg_col = BG_BLACK; fg_col = FG_DARK_GREY; sym = PIXEL_QUARTER; break;
    case 2: bg_col = BG_BLACK; fg_col = FG_DARK_GREY; sym = PIXEL_HALF; break;
    case 3: bg_col = BG_BLACK; fg_col = FG_DARK_GREY; sym = PIXEL_THREEQUARTERS; break;
    case 4: bg_col = BG_BLACK; fg_col = FG_DARK_GREY; sym = PIXEL_SOLID; break;

    case 5: bg_col = BG_DARK_GREY; fg_col = FG_GREY; sym = PIXEL_QUARTER; break;
    case 6: bg_col = BG_DARK_GREY; fg_col = FG_GREY; sym = PIXEL_HALF; break;
    case 7: bg_col = BG_DARK_GREY; fg_col = FG_GREY; sym = PIXEL_THREEQUARTERS; break;
    case 8: bg_col = BG_DARK_GREY; fg_col = FG_GREY; sym = PIXEL_SOLID; break;

    case 9:  bg_col = BG_GREY; fg_col = FG_WHITE; sym = PIXEL_QUARTER; break;
    case 10: bg_col = BG_GREY; fg_col = FG_WHITE; sym = PIXEL_HALF; break;
    case 11: bg_col = BG_GREY; fg_col = FG_WHITE; sym = PIXEL_THREEQUARTERS; break;
    case 12: bg_col = BG_GREY; fg_col = FG_WHITE; sym = PIXEL_SOLID; break;
    default:
        bg_col = BG_BLACK; fg_col = FG_BLACK; sym = PIXEL_SOLID;
    }

    CHAR_INFO c;
    c.Attributes = bg_col | fg_col;
    c.Char.UnicodeChar = sym;
    return c;
}

geo::vec4 GraphicEngine::vectorIntersectPlane(geo::vec3& plane_p, geo::vec3& plane_n, const geo::vec3& lineStart, const geo::vec3& lineEnd, float& t)
{
    plane_n = plane_n.normalize();
    float plane_d = -geo::dot(plane_n, plane_p);
    float ad = geo::dot(lineStart, plane_n);
    float bd = geo::dot(lineEnd, plane_n);
    t = (-plane_d - ad) / (bd - ad);
    geo::vec3 lineStartToEnd = lineEnd - lineStart;
    geo::vec3 lineToIntersect = lineStartToEnd * t;
    return { lineStart + lineToIntersect, 1.0 };
}

int GraphicEngine::triangleClipAgainstPlane(geo::vec3 plane_p, geo::vec3 plane_n, Triangle& in_tri, Triangle& out_tri1, Triangle& out_tri2)
{
    plane_n = plane_n.normalize();

    // Return signed shortest distance from point to plane
    auto dist = [&](geo::vec4& p)
    {
        //geo::vec3 n = p.normalize();
        return (plane_n.x * p.x + plane_n.y * p.y + plane_n.z * p.z -
            geo::dot(plane_n, plane_p));
    };

    //Create two temporary storage arrays to classify points either side of plane

    geo::vec4* inside_points[3]; int nInsidePointCount = 0;
    geo::vec4* outside_points[3]; int nOutsidePointCount = 0;
    geo::vec2* inside_tex[3]; int nInsideTexCount = 0;
    geo::vec2* outside_tex[3]; int nOutsideTexCount = 0;
    geo::vec3* inside_normal[3]; int nInsideNormalCount = 0;
    geo::vec3* outside_normal[3]; int nOutsideNormalCount = 0;


    //Get signed distance of each point in triangle to plane
    float d0 = dist(in_tri[0]);
    float d1 = dist(in_tri[1]);
    float d2 = dist(in_tri[2]);

    if (d0 >= 0) { 
        inside_points[nInsidePointCount++] = &in_tri[0]; 
        inside_tex[nInsideTexCount++] = &in_tri.texture[0]; 
        inside_normal[nInsideNormalCount++] = &in_tri.normal[0]; 
    }
    else { 
        outside_points[nOutsidePointCount++] = &in_tri[0]; 
        outside_tex[nOutsideTexCount++] = &in_tri.texture[0]; 
        outside_normal[nOutsideNormalCount++] = &in_tri.normal[0]; 
    }

    if (d1 >= 0) { 
        inside_points[nInsidePointCount++] = &in_tri[1]; 
        inside_tex[nInsideTexCount++] = &in_tri.texture[1]; 
        inside_normal[nInsideNormalCount++] = &in_tri.normal[1];
    }
    else { 
        outside_points[nOutsidePointCount++] = &in_tri[1]; 
        outside_tex[nOutsideTexCount++] = &in_tri.texture[1]; 
        outside_normal[nOutsideNormalCount++] = &in_tri.normal[1];
    }

    if (d2 >= 0) { 
        inside_points[nInsidePointCount++] = &in_tri[2]; 
        inside_tex[nInsideTexCount++] = &in_tri.texture[2]; 
        inside_normal[nInsideNormalCount++] = &in_tri.normal[2];
    }
    else { 
        outside_points[nOutsidePointCount++] = &in_tri[2]; 
        outside_tex[nOutsideTexCount++] = &in_tri.texture[2]; 
        outside_normal[nOutsideNormalCount++] = &in_tri.normal[2];
    }


    //Classify the triangle
    //There are four possible triangle
    switch (nInsidePointCount)
    {
    case 0:
        return 0;
    case 3:
        out_tri1 = in_tri;
        return 1;   //return the origin triangle
    case 1:
        if (nOutsidePointCount == 2)
        {
            // Only expose one triangle
            out_tri1.col = in_tri.col;//FG_BLUE; //
            out_tri1.sym = in_tri.sym;

            out_tri1[0] = *inside_points[0];
            out_tri1.texture[0] = *inside_tex[0];
            out_tri1.normal[0] = *inside_normal[0];

            float t;
            out_tri1[1] = vectorIntersectPlane(plane_p, plane_n, *inside_points[0], *outside_points[0], t);
            out_tri1.texture[1].u = t * (outside_tex[0]->u - inside_tex[0]->u) + inside_tex[0]->u;
            out_tri1.texture[1].v = t * (outside_tex[0]->v - inside_tex[0]->v) + inside_tex[0]->v;
            out_tri1.normal[1].x = t * (outside_normal[0]->x - inside_normal[0]->x) + inside_normal[0]->x;
            out_tri1.normal[1].y = t * (outside_normal[0]->y - inside_normal[0]->y) + inside_normal[0]->y;
            out_tri1.normal[1].z = t * (outside_normal[0]->z - inside_normal[0]->z) + inside_normal[0]->z;


            out_tri1[2] = vectorIntersectPlane(plane_p, plane_n, *inside_points[0], *outside_points[1], t);
            out_tri1.texture[2].u = t * (outside_tex[1]->u - inside_tex[0]->u) + inside_tex[0]->u;
            out_tri1.texture[2].v = t * (outside_tex[1]->v - inside_tex[0]->v) + inside_tex[0]->v;
            out_tri1.normal[2].x = t * (outside_normal[1]->x - inside_normal[0]->x) + inside_normal[0]->x;
            out_tri1.normal[2].y = t * (outside_normal[1]->y - inside_normal[0]->y) + inside_normal[0]->y;
            out_tri1.normal[2].z = t * (outside_normal[1]->z - inside_normal[0]->z) + inside_normal[0]->z;

        }
        return 1;
    case 2:
        if (nOutsidePointCount == 1)
        {
            //expose two triangles;
            out_tri1.col = in_tri.col; //FG_GREEN; //
            out_tri1.sym = in_tri.sym;

            out_tri2.col = in_tri.col;//FG_RED; // 
            out_tri2.sym = in_tri.sym;

            out_tri1[0] = *inside_points[0];
            out_tri1[1] = *inside_points[1];
            out_tri1.texture[0] = *inside_tex[0];
            out_tri1.texture[1] = *inside_tex[1];
            out_tri1.normal[0] = *inside_normal[0];
            out_tri1.normal[1] = *inside_normal[1];

            float t;
            out_tri1[2] = vectorIntersectPlane(plane_p, plane_n, *inside_points[0], *outside_points[0], t);
            out_tri1.texture[2].u = t * (outside_tex[0]->u - inside_tex[0]->u) + inside_tex[0]->u;
            out_tri1.texture[2].v = t * (outside_tex[0]->v - inside_tex[0]->v) + inside_tex[0]->v;
            out_tri1.normal[2].x = t * (outside_normal[0]->x - inside_normal[0]->x) + inside_normal[0]->x;
            out_tri1.normal[2].y = t * (outside_normal[0]->y - inside_normal[0]->y) + inside_normal[0]->y;
            out_tri1.normal[2].z = t * (outside_normal[0]->z - inside_normal[0]->z) + inside_normal[0]->z;

            out_tri2[0] = *inside_points[1];
            out_tri2.texture[0] = *inside_tex[1];
            out_tri2.normal[0] = *inside_normal[1];

            out_tri2[1] = out_tri1[2];  //Second point of First Triangle
            out_tri2.texture[1] = out_tri1.texture[2];
            out_tri2.normal[1] = out_tri1.normal[2];

            out_tri2[2] = vectorIntersectPlane(plane_p, plane_n, *inside_points[1], *outside_points[0], t);
            out_tri2.texture[2].u = t * (outside_tex[0]->u - inside_tex[1]->u) + inside_tex[1]->u;
            out_tri2.texture[2].v = t * (outside_tex[0]->v - inside_tex[1]->v) + inside_tex[1]->v;
            out_tri2.normal[2].x = t * (outside_normal[0]->x - inside_normal[1]->x) + inside_normal[1]->x;
            out_tri2.normal[2].y = t * (outside_normal[0]->y - inside_normal[1]->y) + inside_normal[1]->y;
            out_tri2.normal[2].z = t * (outside_normal[0]->z - inside_normal[1]->z) + inside_normal[1]->z;

            return 2;
        }
    default:
        break;
    }
}
