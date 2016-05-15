// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>

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
#include <led_cluster.hpp>
#include <renderer.hpp>

#include <opc_client.h>

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void Do_Movement();

// Camera
IsoCamera camera(glm::vec3(0.0f, 1.0f, 2.8f));

bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

std::vector<Model*> toDraw;
std::vector<Model*> toDrawFb;
OPCClient opc_client;

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


  Shader pattern("../shaders/pattern.frag", argv[1]);

  PatternRender pattern_render(canvasSize, canvasSize);
  Texture texture = pattern_render.getTexture();

  LedCluster domeLeds(texture);
  toDraw.push_back(&domeLeds.balls);
  toDrawFb.push_back(&domeLeds.plane);

  std::vector<uint8_t> frameBuffer;
  opc_client.resolve("stardome.local");
  int frameBytes =1000*10 * 3;
  frameBuffer.resize(sizeof(OPCClient::Header) + frameBytes);

  OPCClient::Header::view(frameBuffer).init(0, opc_client.SET_PIXEL_COLORS, frameBytes);

  //FrameBufferRender fb_screen(3, domeLeds.balls.numInstances());
  FrameBufferRender fb_screen(1000, 10);

  Texture fb_texture = fb_screen.getTexture();

  // Load models
  Model screen("../models/screen.obj", texture);
  screen.addInstance(glm::vec3(), glm::vec2(1.0, 1.0));
  toDraw.push_back(&screen);

  //Model panel("../models/panel.obj", fb_texture);
  //panel.addInstance(glm::vec3(), glm::vec2(0.0, 0.0));
  //toDraw.push_back(&panel);

  OrthoCamera stripCamera(0.0f, 1000.0f, 0.0f, 10.0f);
  ScreenRender scene(window);


  double lastTime = glfwGetTime(); int nbFrames = 0;
  while(!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    Do_Movement();

    // Measure speed
    double currentTime = glfwGetTime();
    nbFrames++;
    if ( currentTime - lastTime >= 1.0 ){
       //printf("%2.4f ms/frame\n", 1000.0/double(nbFrames));
       nbFrames = 0;
       lastTime = currentTime;
    }

    // Set frame time
    GLfloat currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    pattern_render.render(pattern);

    fb_screen.render(stripCamera, toDrawFb, OPCClient::Header::view(frameBuffer).data());
    
    opc_client.write(frameBuffer);
    scene.render(camera, toDraw);

		// Swap buffers
		glfwSwapBuffers(window);
    //sleep(1);
	}

  memset(OPCClient::Header::view(frameBuffer).data(), 0, frameBytes);
  opc_client.write(frameBuffer);

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
