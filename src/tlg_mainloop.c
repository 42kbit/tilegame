#include "tlg_mainloop.h"
#include <stddef.h>
#include <stdlib.h>

GLFWwindow* pGlfwwindow = NULL;

void tlg_onload(void) {
	if(!glfwInit())
		exit(-1);

	pGlfwwindow = glfwCreateWindow(640, 480, "TileGame", NULL, NULL);
   	if(!pGlfwwindow){
		glfwTerminate();
		exit(-1);
	}
	glfwMakeContextCurrent(pGlfwwindow);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		glfwTerminate();
		exit(-1);
	}	
	glClearColor( 0.4f, 0.3f, 0.4f, 0.0f );
}

void tlg_onupdate(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(pGlfwwindow);
	glfwPollEvents();	
}

void tlg_onterminate(void){
	glfwTerminate();
}
