#pragma once

#include "game/renderer/shader.h"
#include <memory>

class Model {
  // Methods
public:
  Model();
  Model(const char *vertexFile);
  Model(const char *vertexShaderFile, const char *fragmentShaderFile);
  Model(const char *vertexFile, const char *vertexShaderFile,
        const char *fragmentShaderFile);
  Shader getShader() const { return shader; };

private:
  // Member variables
public:
private:
  Shader shader;
};
