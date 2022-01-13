#include "tlg_mainloop.h"
#include <stddef.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>
#include "tlg_shader.h"

GLFWwindow* pGlfwwindow = NULL;
uint32_t programID = 0;
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
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	glClearColor( 0.4f, 0.3f, 0.4f, 0.0f );
	tlg_create_vfshader_from_files(
			"res/shaders/default_vertex.glsl",
		       	"res/shaders/default_fragment.glsl",
		       	&programID);	
}

void tlg_create_glbuffer(void* data, size_t size, uint32_t DRAW_HINT, uint32_t* dst){
	glCreateBuffers(1, dst);
	glNamedBufferData(*dst, size, data, DRAW_HINT);
}

void tlg_onupdate(void){
	glClear(GL_COLOR_BUFFER_BIT);

	float vertices[] = {
		0.f, 0.f,
		1.f, 0.f,
		1.f, 1.f,
		0.f, 1.f
	};
	uint32_t indecies[] = 
	{
		0,1,2,2,3,0
	};	
	uint32_t vbo;
	tlg_create_glbuffer(vertices, sizeof(vertices), GL_STATIC_DRAW, &vbo);	
	uint32_t ibo;
	tlg_create_glbuffer(indecies, sizeof(indecies), GL_STATIC_DRAW, &ibo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glVertexAttribPointer(
			0,
			2,
			GL_FLOAT,
			GL_FALSE,
			sizeof(float) * 2,
			(const void*)0);
	glEnableVertexAttribArray(0);
	glUseProgram(programID);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

	glfwSwapBuffers(pGlfwwindow);
	glfwPollEvents();	
}

void tlg_onterminate(void){
	glfwDestroyWindow(pGlfwwindow);
	glfwTerminate();
}
