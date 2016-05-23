#pragma once
#include <vector>

#include <GL/glew.h>
#include <glfw3.h>

#include <shader.hpp>
#include <model.hpp>
#include <camera.hpp>
#include <AntTweakBar.h>



class SceneRender {
public:
  std::vector<Model*> models;
protected:
  SceneRender();
  Shader shader;
  void setupLights(IsoCamera& perspective);
};

class ScreenRender : public SceneRender {

public:
  ScreenRender(GLFWwindow* window);

  void render(IsoCamera& perspective);

  GLFWwindow* window;
  int width, height;
};

class FrameBufferRender : public SceneRender {

public:
  FrameBufferRender(int width, int height, uint8_t * dest);

  void render(IsoCamera& perspective);

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

class Scene {
public:
  Scene(ScreenRender* screen, FrameBufferRender* fb_render);

  void render();

  void Do_Movement();
  IsoCamera perspective;
private:

  ScreenRender* screen;
  FrameBufferRender* fb_render;
  
  GLfloat deltaTime;
  GLfloat lastFrame;

  double lastTime;
  int nbFrames;

  double time, dt;// Current time and enlapsed time
  double turn;    // Model turn counter
  double speed; // Model rotation speed
  int wire = 0;       // Draw model in wireframe?
  float bgColor[3];         // Background color 
  unsigned char cubeColor[3]; // Model color (32bits RGBA)
  TwBar *bar;         // Pointer to a tweak bar
};