#pragma once


class LedCluster: public Drawable {
public:
  std::vector<Model*> leds;
  // Draws the model, and thus all its meshes
  LedCluster(const Texture& texture) {
    this->texture = texture;
    vertexes.push_back(glm::vec3(0.000000,2.728441,0.000000));
    vertexes.push_back(glm::vec3(1.086628, 2.526190, 0.353067));
    vertexes.push_back(glm::vec3(0.000000, 2.526190, 1.142548));
    vertexes.push_back(glm::vec3(1.187625, 2.044982, 1.634626));
    vertexes.push_back(glm::vec3(0.000000, 1.820057, 2.285096));
    vertexes.push_back(glm::vec3(2.173256, 1.820057, 0.706133));
    vertexes.push_back(glm::vec3(1.086628, 1.113923, 2.638163));
    vertexes.push_back(glm::vec3(0.000000, 0.888580, 2.976958));
    vertexes.push_back(glm::vec3(2.173256, 1.113923, 1.848681));
    vertexes.push_back(glm::vec3(2.831255, 0.888580, 0.919931));
    vertexes.push_back(glm::vec3(0.671573, 2.526190, -0.924341));
    vertexes.push_back(glm::vec3(1.921618, 2.044982, -0.624372));
    vertexes.push_back(glm::vec3(1.343146, 1.820057, -1.848682));
    vertexes.push_back(glm::vec3(2.844828, 1.113923, -0.218207));
    vertexes.push_back(glm::vec3(2.429773, 1.113923, -1.495615));
    vertexes.push_back(glm::vec3(1.749812, 0.888580, -2.408410));
    vertexes.push_back(glm::vec3(-0.671573, 2.526190, -0.924341));
    vertexes.push_back(glm::vec3(0.000000, 2.044981, -2.020509));
    vertexes.push_back(glm::vec3(-1.343146, 1.820057, -1.848682));
    vertexes.push_back(glm::vec3(0.671573, 1.113923, -2.773022));
    vertexes.push_back(glm::vec3(-0.671573, 1.113923, -2.773022));
    vertexes.push_back(glm::vec3(-1.749812, 0.888580, -2.408410));
    vertexes.push_back(glm::vec3(-1.086628, 2.526190, 0.353067));
    vertexes.push_back(glm::vec3(-1.921618, 2.044981, -0.624372));
    vertexes.push_back(glm::vec3(-2.173256, 1.820057, 0.706133));
    vertexes.push_back(glm::vec3(-2.429774, 1.113923, -1.495615));
    vertexes.push_back(glm::vec3(-2.844828, 1.113923, -0.218207));
    vertexes.push_back(glm::vec3(-2.831255, 0.888580, 0.919931));
    vertexes.push_back(glm::vec3(-1.187625, 2.044982, 1.634626));
    vertexes.push_back(glm::vec3(-2.173255, 1.113923, 1.848681));
    vertexes.push_back(glm::vec3(-1.086628, 1.113923, 2.638163));
    vertexes.push_back(glm::vec3(0.671573, -0.028625, 3.209437));
    vertexes.push_back(glm::vec3(1.921618, 0.024473, 2.644881));
    vertexes.push_back(glm::vec3(2.844828, -0.028625, 1.630474));
    vertexes.push_back(glm::vec3(3.259883, -0.028625, 0.353067));
    vertexes.push_back(glm::vec3(3.109243, 0.024473, -1.010255));
    vertexes.push_back(glm::vec3(2.429774, -0.028625, -2.201748));
    vertexes.push_back(glm::vec3(1.343146, -0.028625, -2.991230));
    vertexes.push_back(glm::vec3(0.000000, 0.024473, -3.269252));
    vertexes.push_back(glm::vec3(-1.343146, -0.028625, -2.991230));
    vertexes.push_back(glm::vec3(-2.429774, -0.028625, -2.201748));
    vertexes.push_back(glm::vec3(-3.109244, 0.024473, -1.010254));
    vertexes.push_back(glm::vec3(-3.259883, -0.028625, 0.353067));
    vertexes.push_back(glm::vec3(-2.844828, -0.028625, 1.630474));
    vertexes.push_back(glm::vec3(-1.921618, 0.024473, 2.644881));
    vertexes.push_back(glm::vec3(-0.671573, -0.028625, 3.209437));
    vtertexes.push_back(glm::vec2(0.5000, 0.4967));
    vtertexes.push_back(glm::vec2(0.5999, 0.5292));
    vtertexes.push_back(glm::vec2(0.5000, 0.6017));
    vtertexes.push_back(glm::vec2(0.6181, 0.6593));
    vtertexes.push_back(glm::vec2(0.5000, 0.7329));
    vtertexes.push_back(glm::vec2(0.7247, 0.5697));
    vtertexes.push_back(glm::vec2(0.6285, 0.8085));
    vtertexes.push_back(glm::vec2(0.5000, 0.8643));
    vtertexes.push_back(glm::vec2(0.7569, 0.7152));
    vtertexes.push_back(glm::vec2(0.8496, 0.6103));
    vtertexes.push_back(glm::vec2(0.5617, 0.4117));
    vtertexes.push_back(glm::vec2(0.6912, 0.4346));
    vtertexes.push_back(glm::vec2(0.6389, 0.3056));
    vtertexes.push_back(glm::vec2(0.8362, 0.4709));
    vtertexes.push_back(glm::vec2(0.7872, 0.3200));
    vtertexes.push_back(glm::vec2(0.7161, 0.1993));
    vtertexes.push_back(glm::vec2(0.4383, 0.4117));
    vtertexes.push_back(glm::vec2(0.5000, 0.2957));
    vtertexes.push_back(glm::vec2(0.3611, 0.3056));
    vtertexes.push_back(glm::vec2(0.5793, 0.1689));
    vtertexes.push_back(glm::vec2(0.4207, 0.1689));
    vtertexes.push_back(glm::vec2(0.2839, 0.1993));
    vtertexes.push_back(glm::vec2(0.4001, 0.5292));
    vtertexes.push_back(glm::vec2(0.3088, 0.4346));
    vtertexes.push_back(glm::vec2(0.2753, 0.5697));
    vtertexes.push_back(glm::vec2(0.2128, 0.3200));
    vtertexes.push_back(glm::vec2(0.1638, 0.4709));
    vtertexes.push_back(glm::vec2(0.1504, 0.6103));
    vtertexes.push_back(glm::vec2(0.3819, 0.6593));
    vtertexes.push_back(glm::vec2(0.2431, 0.7152));
    vtertexes.push_back(glm::vec2(0.3715, 0.8085));
    vtertexes.push_back(glm::vec2(0.6026, 0.9890));
    vtertexes.push_back(glm::vec2(0.7919, 0.8985));
    vtertexes.push_back(glm::vec2(0.9365, 0.7464));
    vtertexes.push_back(glm::vec2(0.9999, 0.5513));
    vtertexes.push_back(glm::vec2(0.9723, 0.3432));
    vtertexes.push_back(glm::vec2(0.8724, 0.1587));
    vtertexes.push_back(glm::vec2(0.7064, 0.0381));
    vtertexes.push_back(glm::vec2(0.5000, 0.0001));
    vtertexes.push_back(glm::vec2(0.2936, 0.0381));
    vtertexes.push_back(glm::vec2(0.1276, 0.1587));
    vtertexes.push_back(glm::vec2(0.0277, 0.3432));
    vtertexes.push_back(glm::vec2(0.0001, 0.5513));
    vtertexes.push_back(glm::vec2(0.0635, 0.7464));
    vtertexes.push_back(glm::vec2(0.2081, 0.8985));
    vtertexes.push_back(glm::vec2(0.3974, 0.9890));

    ball = new Model("../models/ball.obj", texture, glm::vec2());
  }

  virtual void Draw(Shader shader)
  {
    ball->Draw(shader);
  }
  void addStrip(int start, int end, int divisions) {
    for(int i = 0;i < divisions;i++) {
      glm::vec3 posDelta = (vertexes[end] - vertexes[start])* (1.0f/divisions)*float(i) + vertexes[start];
      glm::vec2 texDelta = (vtertexes[end] - vtertexes[start])* (1.0f/divisions)*float(i) + vtertexes[start];
      

      ball->addInstance(posDelta, texDelta);
    }
  }
private:
  Model *ball;
  Texture texture;
  vector<glm::vec3> vertexes;
  vector<glm::vec2> vtertexes;
};