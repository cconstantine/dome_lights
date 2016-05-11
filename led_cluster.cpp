#include <led_cluster.hpp>

LedCluster::LedCluster(const Texture& texture)
: balls("../models/ball.obj",  texture),
  plane("../models/plane.obj", texture) {

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


  addStrip( 2,  0, 72);
  addStrip( 2, 22, 82);
  addStrip( 2, 28, 84);
  addStrip( 2,  3, 84);

  addStrip( 1,  0, 72);
  addStrip( 1,  2, 82);
  addStrip( 1,  3, 84);
  addStrip( 1, 11, 84);

  addStrip(10,  0, 72);
  addStrip(10,  1, 82);
  addStrip(10, 11, 84);
  addStrip(10, 17, 84);

  addStrip(16,  0, 72);
  addStrip(16, 10, 82);
  addStrip(16, 17, 84);
  addStrip(16, 23, 84);

  addStrip(22,  0, 72);
  addStrip(22, 16, 82);
  addStrip(22, 23, 84);
  addStrip(22, 28, 84);
  

  addStrip( 3,  4, 84);
  addStrip( 3,  6, 84);
  addStrip( 3,  8, 84);
  addStrip( 3,  5, 84);

  addStrip( 5,  1, 82);
  addStrip( 5,  8, 84);
  addStrip( 5,  9, 82);
  addStrip( 5, 13, 82);
  
  addStrip(11,  5, 82);
  addStrip(11, 13, 84);
  addStrip(11, 14, 82);
  addStrip(11, 12, 82);

  addStrip(12, 10, 82);
  addStrip(12, 14, 84);
  addStrip(12, 15, 82);
  addStrip(12, 19, 82);

  addStrip(17, 12, 82);
  addStrip(17, 19, 84);
  addStrip(17, 20, 82);
  addStrip(17, 18, 82);
  
  addStrip(18, 16, 82);
  addStrip(18, 21, 84);
  addStrip(18, 20, 82);
  addStrip(18, 25, 82);
  
  addStrip(23, 18, 82);
  addStrip(23, 25, 84);
  addStrip(23, 26, 82);
  addStrip(23, 24, 82);
  
  addStrip(24, 22, 82);
  addStrip(24, 26, 84);
  addStrip(24, 27, 82);
  addStrip(24, 29, 82);
  
  addStrip(28, 24, 82);
  addStrip(28, 29, 84);
  addStrip(28, 30, 82);
  addStrip(28,  4, 82);
  
  addStrip( 4,  2, 82);
  addStrip( 4, 30, 84);
  addStrip( 4,  7, 82);
  addStrip( 4,  6, 82);



  addStrip( 7, 45, 72);
  addStrip( 7, 31, 72);
  addStrip( 7,  6, 72);

  addStrip( 6, 31, 82);
  addStrip( 6, 32, 84);
  addStrip( 6,  8, 82);

  addStrip( 8, 32, 84);
  addStrip( 8, 33, 82);
  addStrip( 8,  9, 72);


  addStrip( 9, 33, 72);
  addStrip( 9, 34, 72);
  addStrip( 9, 13, 72);

  addStrip(13, 34, 82);
  addStrip(13, 35, 84);
  addStrip(13, 14, 82);

  addStrip(14, 35, 84);
  addStrip(14, 36, 82);
  addStrip(14, 15, 72);


  addStrip(15, 36, 72);
  addStrip(15, 37, 72);
  addStrip(15, 19, 72);

  addStrip(19, 37, 82);
  addStrip(19, 38, 84);
  addStrip(19, 20, 82);

  addStrip(20, 38, 84);
  addStrip(20, 39, 82);
  addStrip(20, 21, 72);


  addStrip(21, 39, 72);
  addStrip(21, 40, 72);
  addStrip(21, 25, 72);

  addStrip(25, 40, 82);
  addStrip(25, 41, 84);
  addStrip(25, 26, 82);

  addStrip(26, 41, 84);
  addStrip(26, 42, 82);
  addStrip(26, 27, 72);


  addStrip(27, 42, 72);
  addStrip(27, 43, 72);
  addStrip(27, 29, 72);

  addStrip(29, 43, 82);
  addStrip(29, 44, 84);
  addStrip(29, 30, 82);

  addStrip(30, 44, 84);
  addStrip(30, 45, 82);
  addStrip(30,  7, 72);
}

void LedCluster::addStrip(int start, int end, int divisions) {
  for(int i = 0;i < divisions;i++) {
    glm::vec3 ballPosDelta = (vertexes[end] - vertexes[start])* (1.0f/divisions)*float(i) + vertexes[start];
    glm::vec2 texDelta = (vtertexes[end] - vtertexes[start])* (1.0f/divisions)*float(i) + vtertexes[start];
    
    int count = plane.numInstances();
    int x = count % 1000;
    int y = count / 1000;
    glm::vec3 planePosDelta((float)x, (float)y, 0.0f);

    balls.addInstance(ballPosDelta, texDelta);
    plane.addInstance(planePosDelta, texDelta);
  }
}

