#pragma once
#include <vector>

#include <GL/glew.h>
#include <glfw3.h>

#include <shader.hpp>
#include <model.hpp>
#include <camera.hpp>

class ScreenRender {

public:
  ScreenRender(GLFWwindow* window);

  void render(IsoCamera& perspective, std::vector<Model*>& models);

private:
  Shader shader;

  GLFWwindow* window;
  int width, height;
};

class FrameBufferRender {

public:
  FrameBufferRender(OrthoCamera& camera, int width, int heightFrameBufferRender);

  void render(IsoCamera& perspective, std::vector<Model*>& models, unsigned char *dest);

  Texture getTexture();
private:
  Shader shader;

  GLuint FramebufferName;
  GLuint renderedTexture;
  int width, height;

  GLuint pbos[2];
  GLuint active_pbo;
  OrthoCamera camera;
};

class PatternRender {
public:
  PatternRender(int width, int height);

  void render(Shader& pattern);

  Texture getTexture();
private:
  GLuint VertexArrayID;
  GLuint vertexbuffer;

  GLuint FramebufferName;
  GLuint renderedTexture;
  int width, height;

};