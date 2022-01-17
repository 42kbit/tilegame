#include "tlg_mainloop.h"
#include <stddef.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>
#include "tlg_shader.h"
#include "tlg_texture.h"
#include "tlg_camera.h"

GLFWwindow* pGlfwwindow = NULL;
static uint32_t programID = 0;
static uint32_t txTux = 0;
static float vertices[] = {
	0.f, 0.f, 0.f, 0.f,
	1.f, 0.f, 1.f, 0.f,
	1.f, 1.f, 1.f, 1.f,
	0.f, 1.f, 0.f, 1.f
};
static uint32_t indecies[] = 
{
	0,1,2,2,3,0
};	
static uint32_t vbo;
static uint32_t ibo;
static uint32_t ubo;
static tlg_camera_t camera;

static void tlg_create_glbuffer(void* data, size_t size, uint32_t DRAW_HINT, uint32_t* dst){
	glCreateBuffers(1, dst);
	glNamedBufferData(*dst, size, data, DRAW_HINT);
}

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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	tlg_create_glbuffer(vertices, sizeof(vertices), GL_STATIC_DRAW, &vbo);	
	tlg_create_glbuffer(indecies, sizeof(indecies), GL_STATIC_DRAW, &ibo);
	tlg_create_glbuffer(NULL, sizeof(mat4) * 2, GL_DYNAMIC_DRAW, &ubo);

	tlg_create_vfshader_from_files(
			"res/shaders/default_vertex.glsl",
		       	"res/shaders/default_fragment.glsl",
		       	&programID);	

	tlg_gl_gen_texture2D_from_file(
			"res/textures/tux.png",
			TLG_STB_FLIPONLOAD, 
			GL_LINEAR, 
			GL_CLAMP_TO_EDGE,
			&txTux);
	vec3 cp = {0.f, 0.f, 3.f};
	tlg_init_camera_data(glm_rad(40.f), cp, &camera); 
	}


void tlg_onupdate(void){
	glClear(GL_COLOR_BUFFER_BIT);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	
	glVertexAttribPointer(
			0,
			2,
			GL_FLOAT,
			GL_FALSE,
			sizeof(float) * 4,
			(const void*)0);
	glVertexAttribPointer(
			1,
			2,
			GL_FLOAT,
			GL_FALSE,
			sizeof(float) * 4,
			(const void*)8);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glUseProgram(programID);

	int32_t wx, wy;
	glfwGetWindowSize(pGlfwwindow, &wx, &wy);
	float aspectRaito = (float)wx / (float)wy;

	vec3 camrotrd = {0.f, 0.f, 0.f};
	tlg_set_camera_rotation(&camera, aspectRaito, camrotrd[0], camrotrd[1], camrotrd[2]); 
	int32_t loc;
	mat4 mod;
	glm_mat4_identity(mod);

	mat4 proj; tlg_get_camera_projection(&camera, aspectRaito, proj); 
	mat4 view; tlg_get_camera_view_mat(&camera, view);
	glNamedBufferSubData(ubo, 0, sizeof(mat4), proj); 
	glNamedBufferSubData(ubo, sizeof(mat4), sizeof(mat4), view); 
	
	loc = glGetUniformLocation(programID, "u_Texture");
	if(loc != -1)
		glUniform1i(loc, 0);
	// model
	loc = glGetUniformLocation(programID, "u_Model");
	if(loc != -1)
		glUniformMatrix4fv(loc, 1, GL_FALSE, (const float*) mod);
	//block binding
	uint8_t camBlockInd = 0;
	glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	glBindBufferRange(
			GL_UNIFORM_BUFFER, 
			camBlockInd,
			ubo,
			0,
			sizeof(mat4) * 2);
	loc = glGetUniformBlockIndex(programID, "ub_ProjView");
	if(loc != GL_INVALID_INDEX)
		glUniformBlockBinding(programID, loc, camBlockInd);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

	glfwSwapBuffers(pGlfwwindow);
	glfwPollEvents();	
}

void tlg_onterminate(void){
	glDeleteBuffers(1, &vbo);	
	glDeleteBuffers(1, &ibo);	
	glDeleteBuffers(1, &ubo);	
	glfwDestroyWindow(pGlfwwindow);
	glfwTerminate();
}
