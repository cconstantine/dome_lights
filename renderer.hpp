#pragma once
#include <vector>

#include <GL/glew.h>
#include <glfw3.h>

#include <shader.hpp>
#include <model.hpp>
#include <camera.hpp>

class SceneRender {

public:
  SceneRender(GLFWwindow* window);

  void render(Camera& camera, std::vector<Drawable*>& models);

private:
  Shader shader;
  GLFWwindow* window;

  int width, height;
};

class PatternRender {
public:
  PatternRender(int canvasSize);

  void render(Shader& pattern);

  Texture getTexture();
private:
  GLuint VertexArrayID;
  GLuint vertexbuffer;

  GLuint FramebufferName;
  GLuint renderedTexture;
  int canvasSize;

};