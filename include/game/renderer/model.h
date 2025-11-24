#pragma once

#include "game/renderer/shader.h"
#include <memory>
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <assimp/scene.h>

struct Vertex {
  glm::vec3 Position;
  glm::vec3 Normal;
  glm::vec2 TexCoords;
};

struct Texture {
  unsigned int id;
  std::string type;
  std::string path;
};

class Mesh {
public:
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  std::vector<Texture> textures;
  
  Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
  void Draw(Shader &shader);
  
private:
  unsigned int VAO, VBO, EBO;
  void setupMesh();
};

class Model {
  // Methods
public:
  Model();
  Model(const char *path);
  Model(const char *path, const char *vertexShaderFile, const char *fragmentShaderFile);
  
  void Draw();
  
  // Transform accessors
  void setPosition(const glm::vec3 &pos) { position = pos; }
  void setRotation(const glm::vec3 &rot) { rotation = rot; }
  void setScale(const glm::vec3 &scl) { scale = scl; }
  
  glm::vec3 getPosition() const { return position; }
  glm::vec3 getRotation() const { return rotation; }
  glm::vec3 getScale() const { return scale; }
  
  glm::mat4 getModelMatrix() const;
  
  Shader& getShader() { return shader; }
  const Shader& getShader() const { return shader; }

private:
  void loadModel(const std::string &path);
  void processNode(aiNode *node, const aiScene *scene);
  Mesh processMesh(aiMesh *mesh, const aiScene *scene);
  std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
  
  // Member variables
  std::vector<Mesh> meshes;
  std::string directory;
  std::vector<Texture> textures_loaded;
  
  // Transform
  glm::vec3 position;
  glm::vec3 rotation;
  glm::vec3 scale;
  
  // Shader
  Shader shader;
};
