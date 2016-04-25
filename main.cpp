// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

const int canvasSize = 400;
#include <shader.hpp>

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

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile

	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	GLuint programID = LoadShaders( argv[1]);//"../SimpleFragmentShader.fragmentshader" );

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);


	static const GLfloat g_vertex_buffer_data[] = { 
		 - 1.0, - 1.0, 1.0, 
		 - 1.0, - 1.0, 1.0,
		   1.0, - 1.0, 1.0,
		   1.0, - 1.0, 1.0
	};
	
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

  GLuint time_id = glGetUniformLocation(programID, "time");
  GLuint resolution_id = glGetUniformLocation(programID, "resolution");
  GLuint mouse_id = glGetUniformLocation(programID, "mouse");

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


  // Create and compile our GLSL program from the shaders
  GLuint quad_programID = LoadShaders( "../Passthrough.vertexshader", "../WobblyTexture.fragmentshader" );
  GLuint texID = glGetUniformLocation(quad_programID, "renderedTexture");
  GLuint timeID = glGetUniformLocation(quad_programID, "time");
    
	do{
    // Measure speed
    double currentTime = glfwGetTime();
    nbFrames++;
    if ( currentTime - lastTime >= 1.0 ){ // If last prinf() was more than 1 sec ago
       // printf and reset timer
       printf("%f ms/frame\n", 1000.0/double(nbFrames));
       nbFrames = 0;
       lastTime = currentTime;
    }
    int width;
    int height;
    glfwGetWindowSize(window, &width, &height);

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    // Render to our framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
    glViewport(0,0,canvasSize,canvasSize); // Render on the whole framebuffer, complete from the lower left corner to the upper right

    // Use our shader
    glUseProgram(programID);
    glUniform1f(time_id, glfwGetTime());
    glUniform2f(resolution_id, canvasSize, canvasSize);
    glUniform2f(mouse_id, xpos/canvasSize, ypos/canvasSize);
		// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT );


		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
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



    // Render to the screen
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    int size = width > height ? width : height;
        // Render on the whole framebuffer, complete from the lower left corner to the upper right
    glViewport((width - size)/2,(height - size) / 2,size,size);

    // Clear the screen
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use our shader
    glUseProgram(quad_programID);

    // Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, renderedTexture);
    // Set our "renderedTexture" sampler to user Texture Unit 0
    glUniform1i(texID, GL_TEXTURE0);

    glUniform1f(timeID, (float)(glfwGetTime()*10.0f) );

    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
      0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
      2,                  // size
      GL_FLOAT,           // type
      GL_FALSE,           // normalized?
      0,                  // stride
      (void*)0            // array buffer offset
    );

    // Draw the triangles !
    glDrawArrays(GL_TRIANGLES, 0, 6); // 2*3 indices starting at 0 -> 2 triangles

    glDisableVertexAttribArray(0);


		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

