// clang-format off
#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define TINYGLTF_NOEXCEPTION
#include "game/renderer/model.h"
//clang-format on

Model::Model()
    : Model("", "res/shaders/default.vert", "res/shaders/default.frag") {}

Model::Model(const char *vertexFile)
    : Model(vertexFile, "res/shaders/default.vert",
            "res/shaders/default.frag") {}

Model::Model(const char *vertexFile, const char *vertexShaderFile,
             const char *fragmentShaderFile)
    : shader(vertexShaderFile, fragmentShaderFile) {}
