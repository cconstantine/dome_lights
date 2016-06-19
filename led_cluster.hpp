#pragma once

#include <vector>

#include <mesh.hpp>
#include <shader.hpp>
#include <model.hpp>

#include <pixelpusher/pixel_pusher.hpp>

class LedCluster {
public:
  // Draws the model, and thus all its meshes
  LedCluster(const Texture& texture);

  void update(std::vector<uint8_t> &frameBuffer);

  void addStrip(std::string &mac, int strip, int strip_offset, int start, int end, int divisions);
  void addStrip(int start, int end, int divisions);

  Model balls;
  Model plane;

private:
  const aiScene* model;

  DiscoveryService ds;

  class Strip {
  public:
    Strip();
    Strip(int strip, int offset, int size);
    Strip(const Strip& copy);

    int strip, offset;
    size_t size;
  };

  std::map<std::string, std::vector<Strip>> strip_mappings;

  size_t buffer_size;
};