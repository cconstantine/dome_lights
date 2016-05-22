#include <led_cluster.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

LedCluster::LedCluster(const Texture& texture)
: balls("../models/ball.obj",  texture),
  plane("../models/plane.obj", texture) {

  Assimp::Importer importer;

  model = importer.ReadFile("../models/dome.obj", aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

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
  glm::vec3 vertex_start = glm::vec3(
    model->mMeshes[0]->mVertices[start].x,
    model->mMeshes[0]->mVertices[start].y,
    model->mMeshes[0]->mVertices[start].z);
  glm::vec3 vertex_end = glm::vec3(
    model->mMeshes[0]->mVertices[end].x,
    model->mMeshes[0]->mVertices[end].y,
    model->mMeshes[0]->mVertices[end].z);
  glm::vec3 vertex_delta = vertex_end - vertex_start;


  glm::vec2 texture_start = glm::vec2(
    model->mMeshes[0]->mTextureCoords[0][start].x,
    model->mMeshes[0]->mTextureCoords[0][start].y);
  glm::vec2 texture_end   = glm::vec2(
    model->mMeshes[0]->mTextureCoords[0][end].x,
    model->mMeshes[0]->mTextureCoords[0][end].y);

  glm::vec2 texture_delta = texture_end - texture_start;


  for(int i = 0;i < divisions;i++) {
    glm::vec3 ballPosDelta = vertex_start  + vertex_delta  * (1.0f/divisions)*float(i);
    glm::vec2 texDelta     = texture_start + texture_delta * (1.0f/divisions)*float(i);
    
    int count = plane.numInstances();
    int x = count % 1000;
    int y = count / 1000;
    glm::vec3 planePosDelta((float)x, (float)y, 0.0f);

    balls.addInstance(ballPosDelta, texDelta, ballPosDelta);
    plane.addInstance(planePosDelta, texDelta, ballPosDelta);
  }
}

