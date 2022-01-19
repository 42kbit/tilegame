#ifndef _H_USERINPUT_H 
#define _H_USERINPUT_H 
/*
 WRAPPER OVER GLFW
*/
#include "GLFW/glfw3.h"
#include <inttypes.h>

struct tlg_userinput_s;
typedef struct tlg_userinput_s tlg_userinput_t;

extern tlg_userinput_t tlg_userinput;

void tlg_init_userinput(tlg_userinput_t* target, GLFWwindow* win); 
void tlg_get_key_held(tlg_userinput_t* target, int32_t keycode, int8_t* dst);
void tlg_get_key_pressed(tlg_userinput_t* target, int32_t keycode, int8_t* dst);

#endif 
