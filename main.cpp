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
  Model ourModel("../models/simple_dome.obj");
  //Model ourModel("../models/nanosuit/nanosuit.obj");

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
  for(unsigned int i = 0;i < ourModel.meshes.size();++i) {
        ourModel.meshes[i].textures.resize(1);

    ourModel.meshes[i].textures.push_back(texture);
  }



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

    // Draw the loaded model
    glm::mat4 model;
    //model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // Translate it down a bit so it's at the center of the scene
    //model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f)); // It's a bit too big for our scene, so scale it down
    glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
    ourModel.Draw(shader);

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
