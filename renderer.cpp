#include <renderer.hpp>

#include <glm/gtx/string_cast.hpp>

ScreenRender::ScreenRender(GLFWwindow* window) : shader("../shaders/model_loading.vs", "../shaders/model_loading.frag"), window(window) {
  glfwGetWindowSize(window, &width, &height);
}

void ScreenRender::render(Camera& camera, std::vector<Model*>& models) {
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glViewport(0,0,width,height);

  // Clear the colorbuffer
  glClearColor(0.00f, 0.00f, 0.00f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  shader.Use(); 
  // Transformation matrices
  glm::mat4 projection = camera.GetProjectionMatrix();
  glm::mat4 view = camera.GetViewMatrix();

  glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
  glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

  for(std::vector<Model*>::iterator i = models.begin();i != models.end();i++) {
    Drawable* m = *i;
    m->Draw(shader);
  }
}
FrameBufferRender::FrameBufferRender(int width, int height) : shader("../shaders/model_loading.vs", "../shaders/model_loading.frag"), width(width), height(height) {
  // The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
  glGenFramebuffers(1, &FramebufferName);
  glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

  // The texture we're going to render to
  glGenTextures(1, &renderedTexture);
  glBindTexture(GL_TEXTURE_2D, renderedTexture);
  glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);

  // Poor filtering
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT); 

  // Set "renderedTexture" as our colour attachement #0
  glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);

  // Set the list of draw buffers.
  GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
  glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

  // Always check that our framebuffer is ok
  if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    fprintf(stderr, "Failed to init GL_FRAMEBUFFER\n");
    exit(1);
  }
}

void FrameBufferRender::render(Camera& camera, std::vector<Model*>& models) {

  glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
  glViewport(0,0,width, height); // Render on the whole framebuffer, complete from the lower left corner to the upper right

  // Clear the colorbuffer
  glClearColor(0.00f, 0.00f, 0.00f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  shader.Use();

  // Transformation matrices
  glm::mat4 projection = camera.GetProjectionMatrix();
  glm::mat4 view = camera.GetViewMatrix();
  glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
  glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

  for(std::vector<Model*>::iterator i = models.begin();i != models.end();i++) {
    Drawable* m = *i;
    m->Draw(shader);
  }
}

Texture FrameBufferRender::getTexture() {
  Texture t;
  t.id = renderedTexture;
  t.target = GL_TEXTURE_2D;
  return t;
}

PatternRender::PatternRender(int width, int height) : width(width), height(height) {
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);

  
  static const GLfloat g_vertex_buffer_data[] = { 
  // Coordinates
   - 1.0, - 1.0,
     1.0, - 1.0,
   - 1.0,   1.0,

     1.0,   1.0,
     1.0, - 1.0,
   - 1.0,   1.0,
  };
  
  glGenBuffers(1, &vertexbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

  // The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
  glGenFramebuffers(1, &FramebufferName);
  glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

  // The texture we're going to render to
  glGenTextures(1, &renderedTexture);
  glBindTexture(GL_TEXTURE_2D, renderedTexture);
  glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);

  // Poor filtering
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  // Set "renderedTexture" as our colour attachement #0
  glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);

  // Set the list of draw buffers.
  GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
  glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

  // Always check that our framebuffer is ok
  if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    fprintf(stderr, "Failed to init GL_FRAMEBUFFER\n");
    exit(1);
  }  
}

Texture PatternRender::getTexture() {
  Texture t;
  t.id = renderedTexture;
  t.target = GL_TEXTURE_2D;
  return t;
}

void PatternRender::render(Shader& pattern) {
  GLuint time_id = glGetUniformLocation(pattern.Program, "time");
  GLuint resolution_id = glGetUniformLocation(pattern.Program, "resolution");
  GLuint mouse_id = glGetUniformLocation(pattern.Program, "mouse");

  glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
  glViewport(0,0,width, height); // Render on the whole framebuffer, complete from the lower left corner to the upper right
  
  // Use our shader
  pattern.Use();
  glUniform1f(time_id, glfwGetTime() );
  glUniform2f(resolution_id, width, height);
  glUniform2f(mouse_id, width/2, height/2);

  // // Clear the screen
  glClear( GL_COLOR_BUFFER_BIT );

  // 1rst attribute buffer : vertices

  glBindVertexArray(VertexArrayID);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

  // Draw the triangle !
  glDrawArrays(GL_TRIANGLES, 0, 6); // 3 indices starting at 0 -> 1 triangle

  glDisableVertexAttribArray(0);

}


