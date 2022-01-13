#ifndef _H_SHADER_ 
#define _H_SHADER_ 
#include "glglfw.h"
#include <inttypes.h>

void tlg_read_file(char* path, char** dst);
void tlg_compile_shader(char* src, uint32_t SHADER_TYPE, uint32_t* dst);
void tlg_create_programvfs(uint32_t vertexID, uint32_t fragmentID, uint32_t* dst);
void tlg_create_vfshader_from_files(char* pathVertex, char* pathFragment, uint32_t* dst);

#endif
