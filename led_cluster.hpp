#pragma once

#include <vector>

#include <mesh.hpp>
#include <shader.hpp>
#include <model.hpp>

class LedCluster: public Model {
public:
  std::vector<Model*> leds;
  // Draws the model, and thus all its meshes
  LedCluster(const Texture& texture);

  void addStrip(int start, int end, int divisions);
private:
  vector<glm::vec3> vertexes;
  vector<glm::vec2> vtertexes;
};