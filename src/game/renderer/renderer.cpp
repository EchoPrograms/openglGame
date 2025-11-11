/* File: renderer.cpp
 * Author: Brogan
 */

// clang-format off
#include "game/renderer/renderer.h"
#include "constants.h"
#include "game/renderer/shader.h"
#include "stb/stb_image.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
// clang-format on

using namespace Constants::Renderer;

Renderer::Renderer() {

  if (!glfwInit()) {
    m_status = GLFWInitFailed;
    return;
  }

  m_window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE,
                              nullptr, nullptr);

  if (!m_window) {
    glfwTerminate();
    m_status = WindowInitFailed;
    return;
  }

  glfwMakeContextCurrent(m_window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    m_status = GLADInitFailed;
    return;
  }
}
void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void Renderer::init() {

  stbi_set_flip_vertically_on_load(true);
  glViewport(0, 0, 800, 600);
  glfwSetFramebufferSizeCallback(getGLFWWindow(), framebufferSizeCallback);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  shader = new Shader("res/shaders/default.vert", "res/shaders/default.frag");
  shader->use();
  // clang-format off
  float vertices[] = {
     0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f, 
    0.5f,-0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
  };
  unsigned int indices[] = {
    0, 1, 2, // first triangle
    2, 3, 0, // second triangle
  };
  // clang-format on

  int width, height, nrChannels;
  unsigned char *data =
      stbi_load("res/textures/brick.jpg", &width, &height, &nrChannels, 0);

  unsigned int texture;
  glGenTextures(1, &texture);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
  stbi_image_free(data);
  shader->setInt("u_Texture1", 0);

  data = stbi_load("res/textures/arch.png", &width, &height, &nrChannels, 0);

  glGenTextures(1, &texture);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
  stbi_image_free(data);
  shader->setInt("u_Texture2", 1);

  unsigned int VAO;
  unsigned int VBO;
  unsigned int EBO;

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
                        (void *)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  return;
}

void Renderer::renderLoop() {
  float time = glfwGetTime();

  glm::mat4 model = glm::mat4(1.0f);
  model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
  model =
      glm::rotate(model, glm::radians(time) * 50, glm::vec3(0.0f, 0.0f, 1.0f));

  glm::mat4 view = glm::mat4(1.0f);
  view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

  glm::mat4 projection;
  projection = glm::perspective(glm::radians(45.0f),
                                (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT,
                                0.1f, 100.0f);

  int modelLoc = glGetUniformLocation(shader->ID, "u_Model");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

  int viewLoc = glGetUniformLocation(shader->ID, "u_View");
  glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

  int projectionLoc = glGetUniformLocation(shader->ID, "u_Projection");
  glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

  glClear(GL_COLOR_BUFFER_BIT);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glfwSwapBuffers(getGLFWWindow());

  glfwPollEvents();
}

bool Renderer::windowOpen() { return !glfwWindowShouldClose(m_window); }

Renderer::~Renderer() {
  glfwDestroyWindow(m_window);
  glfwTerminate();
  delete shader;
}
