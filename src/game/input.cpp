/* File: input.cpp
 * Author: Brogan Oberhaus
 */

#include "game/input.h"
#include <GLFW/glfw3.h>
#include <iostream>

void keyCallback(GLFWwindow *window, int key, int scancode, int action,
                 int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }

  if (key == GLFW_KEY_F && action == GLFW_PRESS) {
  }
}
void cursorPosCallback(GLFWwindow *window, double x, double y) {}

InputManager::InputManager(GLFWwindow *window) {
  glfwSetCursorPosCallback(window, cursorPosCallback);
  glfwSetKeyCallback(window, keyCallback);
}

InputManager::~InputManager() {}
