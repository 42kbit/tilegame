#include "tlg_shader.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>

void tlg_read_file(char* path, char** dst)
{
	FILE* pFile;
	if(!(pFile = fopen(path, "r"))){
		printf("Failed to read file: %s\n", path);
		return;
	}
	fseek(pFile, 0, SEEK_END);
	*dst = (char*)malloc(ftell(pFile) * sizeof(char));
	fseek(pFile, 0, SEEK_SET);
	uint32_t dstTop = 0;
	char c;
	while((c = fgetc(pFile)) != EOF)
		(*dst)[dstTop++] = c;
	fclose(pFile);
	(*dst)[dstTop++] = '\0';
}

void tlg_compile_shader(char* src, uint32_t SHADER_TYPE, uint32_t* dst){
	*dst = glCreateShader(SHADER_TYPE);
	int32_t len = (int32_t)(strlen(src) + 1);
	glShaderSource(*dst, 1, (const char* const*)&src, &len);
	glCompileShader(*dst);
	int32_t log;
	glGetShaderiv(*dst, GL_COMPILE_STATUS, &log);
	if(log != GL_TRUE){
		char* szErrstr = NULL;
		glGetShaderiv(*dst, GL_INFO_LOG_LENGTH, &log);
		szErrstr = (char*)malloc(log * sizeof(char));
		glGetShaderInfoLog(*dst, log, NULL, szErrstr);
		printf("%s\n", szErrstr);
		free(szErrstr);
	}
}

void tlg_create_programvfs(uint32_t vertexID, uint32_t fragmentID, uint32_t* dst){
	*dst = glCreateProgram();
	glAttachShader(*dst, vertexID);
	glAttachShader(*dst, fragmentID);
	glLinkProgram(*dst);
	glDetachShader(*dst, vertexID);
	glDetachShader(*dst, fragmentID);
	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);

	int32_t log;
	glGetProgramiv(*dst, GL_LINK_STATUS, &log);
	if(log != GL_TRUE){
		char* szErrstr = NULL;
		glGetProgramiv(*dst, GL_INFO_LOG_LENGTH, &log);
	        szErrstr = (char*)malloc(log * sizeof(char));
		glGetProgramInfoLog(*dst, log, NULL, szErrstr);
		printf("%s\n", szErrstr);
		free(szErrstr);	
	}
}

static void sfree(void* trg){
	void** ptr = (void**)trg;
	if(!*ptr) return;
	free(*ptr);
	*ptr = NULL;
}

void tlg_create_vfshader_from_files(char* pathVertex, char* pathFragment, uint32_t* dst){
	char* szVertexShader; 
	char* szFragmentShader;
       	tlg_read_file(pathVertex, &szVertexShader);
       	tlg_read_file(pathFragment, &szFragmentShader);
	if(!szVertexShader || !szFragmentShader) return;
	uint32_t vertexID;
	uint32_t fragmentID;
	tlg_compile_shader(szVertexShader, GL_VERTEX_SHADER, &vertexID);
       	tlg_compile_shader(szFragmentShader, GL_FRAGMENT_SHADER, &fragmentID);
	tlg_create_programvfs(vertexID, fragmentID, dst);
	sfree(&szVertexShader);
	sfree(&szFragmentShader);	
}
