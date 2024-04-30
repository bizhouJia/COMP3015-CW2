#pragma once

#include "trianglemesh.h"
#include <glad/glad.h>

class Cup : public TriangleMesh
{
public:
    Cup(float topRadius, float bottomRadius, float height, unsigned int segments);
};
