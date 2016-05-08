#pragma once
// Std. Includes
#include <string>
#include <vector>

using namespace std;
// GL Includes
#include <glm/glm.hpp>
#include <assimp/scene.h>

#include <shader.hpp>
struct Vertex {
  // Position
  glm::vec3 Position;
  // Normal
  glm::vec3 Normal;
  // TexCoords
  glm::vec2 TexCoords;
};

struct Texture {
  GLuint id;
  GLenum target;
};

class Mesh {
public:
  /*  Mesh Data  */
  vector<Vertex> vertices;
  vector<GLuint> indices;
  vector<Texture> textures;

  vector<glm::mat4> instancePositionOffset;
  vector<glm::vec2> instanceTextureOffset;
  vector<float>     instanceIndex;

  /*  Functions  */
  // Constructor
  Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures);

  // Render the mesh
  void Draw(Shader shader);

private:
  /*  Render data  */
  GLuint VAO, VBO, EBO, POS, TPOS;

  /*  Functions    */
  // Initializes all the buffer objects/arrays
  void setupMesh();
};
