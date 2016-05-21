#pragma once
#include <vector>

#include <GL/glew.h>
#include <glfw3.h>

#include <shader.hpp>
#include <model.hpp>
#include <camera.hpp>

class SceneRender {
protected:
  SceneRender();
  Shader shader;
  void setupLights(IsoCamera& perspective);
};

class ScreenRender : public SceneRender {

public:
  ScreenRender(GLFWwindow* window);

  void render(IsoCamera& perspective, std::vector<Model*>& models);

private:

  GLFWwindow* window;
  int width, height;
};

class FrameBufferRender : public SceneRender {

public:
  FrameBufferRender(OrthoCamera& camera, int width, int height, uint8_t * dest);

  void render(IsoCamera& perspective, std::vector<Model*>& models);

  Texture getTexture();

private:
  unsigned char *dest;
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