// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

const int canvasSize = 400;

#include <shader.hpp>
#include <camera.hpp>
#include <model.hpp>

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void Do_Movement();

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

std::vector<Drawable*> toDraw;

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
  }

  virtual void Draw(Shader shader)
  {
    for(std::vector<Model*>::iterator i = leds.begin();i != leds.end();i++) {
      Model *m = *i;
      m->Draw(shader);
    }
  }
  void addStrip(int start, int end, int divisions) {
    Model *ball;
    for(int i = 0;i < divisions;i++) {
      glm::vec3 posDelta = (vertexes[end] - vertexes[start])* (1.0f/divisions)*float(i) + vertexes[start];
      glm::vec2 texDelta = (vtertexes[end] - vtertexes[start])* (1.0f/divisions)*float(i) + vtertexes[start];
      
      ball = new Model("../models/ball.obj", texture, texDelta);
      ball->position = glm::translate(ball->position, posDelta );
      leds.push_back(ball);
    }
  }
private:
  Texture texture;
  vector<glm::vec3> vertexes;
  vector<glm::vec2> vtertexes;
};
int main( int argc, char** argv )
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( 800, 800, "Dome Lights", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

  // Set the required callback functions
  glfwSetKeyCallback(window, key_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);

  int width;
  int height;
  glfwGetWindowSize(window, &width, &height);

  // Ensure we can capture the escape key being pressed below
  //glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
  // Options
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  // Initialize GLEW
  glewExperimental = GL_TRUE; // Needed for core profile
  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to initialize GLEW\n");
    getchar();
    glfwTerminate();
    return -1;
  }

  // Setup some OpenGL options
  glEnable(GL_DEPTH_TEST);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);


  Shader pattern("../shaders/pattern.frag", argv[1]);
  // Setup and compile our shaders
  Shader shader("../shaders/model_loading.vs", "../shaders/model_loading.frag");  
  // Load models
  Model dome("../models/dome.obj");
  toDraw.push_back(&dome);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

  
	static const GLfloat g_vertex_buffer_data[] = { 
    // Coordinates
		 - 1.0, - 1.0,
       1.0, - 1.0,
     - 1.0,   1.0,

		   1.0, - 1.0,
       1.0,   1.0,
     - 1.0,   1.0,

	};
	
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);


  GLuint time_id = glGetUniformLocation(pattern.Program, "time");
  GLuint resolution_id = glGetUniformLocation(pattern.Program, "resolution");
  GLuint mouse_id = glGetUniformLocation(pattern.Program, "mouse");

  double lastTime = glfwGetTime(); int nbFrames = 0;


  /******* Framebuffer ******/

  // The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
  GLuint FramebufferName = 0;
  glGenFramebuffers(1, &FramebufferName);
  glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

  // The texture we're going to render to
  GLuint renderedTexture;
  glGenTextures(1, &renderedTexture);
  glBindTexture(GL_TEXTURE_2D, renderedTexture);
  glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, canvasSize, canvasSize, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);

  // Poor filtering
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
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
  /**************************/
  
  
  Texture texture;
  texture.id = renderedTexture;
  texture.type = "texture_diffuse";
  texture.path = "something";

  dome.meshes[1].textures.push_back(texture);  
  

  LedCluster *domeLeds = new LedCluster(texture);
  toDraw.push_back(domeLeds);


  domeLeds->addStrip( 2,  0, 72);
  domeLeds->addStrip( 2, 22, 82);
  domeLeds->addStrip( 2, 28, 84);
  domeLeds->addStrip( 2,  3, 84);

  domeLeds->addStrip( 1,  0, 72);
  domeLeds->addStrip( 1,  2, 82);
  domeLeds->addStrip( 1,  3, 84);
  domeLeds->addStrip( 1, 11, 84);

  domeLeds->addStrip(10,  0, 72);
  domeLeds->addStrip(10,  1, 82);
  domeLeds->addStrip(10, 11, 84);
  domeLeds->addStrip(10, 17, 84);

  domeLeds->addStrip(16,  0, 72);
  domeLeds->addStrip(16, 10, 82);
  domeLeds->addStrip(16, 17, 84);
  domeLeds->addStrip(16, 23, 84);

  domeLeds->addStrip(22,  0, 72);
  domeLeds->addStrip(22, 16, 82);
  domeLeds->addStrip(22, 23, 84);
  domeLeds->addStrip(22, 28, 84);
  

  domeLeds->addStrip( 4, 28, 82);
  domeLeds->addStrip( 4,  2, 84);
  domeLeds->addStrip( 4,  3, 82);
  
  domeLeds->addStrip( 5,  3, 82);
  domeLeds->addStrip( 5,  1, 84);
  domeLeds->addStrip( 5, 11, 82);
  
  domeLeds->addStrip(12, 11, 82);
  domeLeds->addStrip(12, 10, 84);
  domeLeds->addStrip(12, 17, 82);

  domeLeds->addStrip(18, 17, 82);
  domeLeds->addStrip(18, 16, 84);
  domeLeds->addStrip(18, 23, 82);

  domeLeds->addStrip(24, 23, 82);
  domeLeds->addStrip(24, 22, 84);
  domeLeds->addStrip(24, 28, 82);
  



  Model *ball = new Model("../models/ball.obj");
  toDraw.push_back(ball);
  
  while(!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    Do_Movement();

    // Measure speed
    double currentTime = glfwGetTime();
    nbFrames++;
    if ( currentTime - lastTime >= 1.0 ){ // If last prinf() was more than 1 sec ago
       // printf and reset timer
       printf("%2.4f ms/frame\n", 1000.0/double(nbFrames));
       nbFrames = 0;
       lastTime = currentTime;
    }

    // Set frame time
    GLfloat currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;


    /******** Render pattern to framebuffer **********/
    glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
    glViewport(0,0,canvasSize,canvasSize); // Render on the whole framebuffer, complete from the lower left corner to the upper right

    //   // Use our shader
    pattern.Use();
    glUniform1f(time_id, glfwGetTime());
    glUniform2f(resolution_id, canvasSize, canvasSize);
    glUniform2f(mouse_id, canvasSize/2, canvasSize/2);

		// // Clear the screen
		 glClear( GL_COLOR_BUFFER_BIT );

		// 1rst attribute buffer : vertices

    glBindVertexArray(VertexArrayID);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			2,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, 6); // 3 indices starting at 0 -> 1 triangle

		glDisableVertexAttribArray(0);
    
     glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0,0,width,height);

    /*************************************************/
    // Clear the colorbuffer
    glClearColor(0.05f, 0.15f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /***** Render to the screen *****/

    /*********** Draw Model ****************/
    shader.Use();   // <-- Don't forget this one!

    // Transformation matrices
    glm::mat4 projection = glm::perspective(camera.Zoom, (float)800/(float)800, 0.1f, 100.0f);
    glm::mat4 view = camera.GetViewMatrix();
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

    for(std::vector<Drawable*>::iterator i = toDraw.begin();i != toDraw.end();i++) {
      Drawable* m = *i;
      m->Draw(shader);
    }

    /***************************/

		// Swap buffers
		glfwSwapBuffers(window);
    //sleep(1);
	}
	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}


#pragma region "User input"

// Moves/alters the camera positions based on user input
void Do_Movement()
{
    // Camera controls
    if(keys[GLFW_KEY_W])
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if(keys[GLFW_KEY_S])
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if(keys[GLFW_KEY_A])
        camera.ProcessKeyboard(LEFT, deltaTime);
    if(keys[GLFW_KEY_D])
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    if(action == GLFW_PRESS)
        keys[key] = true;
    else if(action == GLFW_RELEASE)
        keys[key] = false;  
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos; 
    
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
} 

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

#pragma endregion
