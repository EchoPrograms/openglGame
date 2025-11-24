/* File: window.h
 * Author: Brogan
 */
#pragma once

#include "game/renderer/shader.h"
#include "game/renderer/model.h"
#include <memory>
#include <vector>
#include <glm/glm.hpp>

class Game;
class GLFWwindow;

enum Status { OK, WindowInitFailed, GLFWInitFailed, GLADInitFailed };

class Renderer {
  /* Methods */
public:
  Renderer();
  ~Renderer();

  GLFWwindow *getGLFWWindow() { return m_window; };
  Status getStatus() { return m_status; };
  bool windowOpen();
  void init();
  
  // Add models to the renderer
  void addModel(std::unique_ptr<Model> model);
  
  // Camera/view management
  void setViewMatrix(const glm::mat4 &view) { m_viewMatrix = view; }
  void setProjectionMatrix(const glm::mat4 &projection) { m_projectionMatrix = projection; }
  
  glm::mat4 getViewMatrix() const { return m_viewMatrix; }
  glm::mat4 getProjectionMatrix() const { return m_projectionMatrix; }

private:
  void renderLoop();

  /* Member Variables */
public:
private:
  Status m_status = OK;
  GLFWwindow *m_window;
  std::vector<std::unique_ptr<Model>> models;
  
  glm::mat4 m_viewMatrix;
  glm::mat4 m_projectionMatrix;

  friend Game;
};
