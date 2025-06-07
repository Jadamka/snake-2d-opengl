#ifndef QUAD_RENDERER_H
#define QUAD_RENDERER_H

#include <glad/glad.h>

class QuadRenderer
{
public:
    static QuadRenderer *GetInstance();
    ~QuadRenderer();
    void Render();
    void Destroy();
private:
    void init();
    unsigned int m_vao;
    static QuadRenderer *qr;
    QuadRenderer() {}
    QuadRenderer(const QuadRenderer&) = delete;
    QuadRenderer& operator=(const QuadRenderer&) = delete;
};

#endif // QUAD_RENDERER_H
