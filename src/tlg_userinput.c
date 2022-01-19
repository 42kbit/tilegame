#include "tlg_userinput.h"
#include <string.h>
#define TLG_KEYS_ARRAY_SIZE GLFW_KEY_LAST

struct tlg_userinput_s{
	int8_t kpressed[TLG_KEYS_ARRAY_SIZE];
	int8_t kheld[TLG_KEYS_ARRAY_SIZE];
};
typedef struct tlg_userinput_s tlg_userinput_t;
tlg_userinput_t tlg_userinput;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if(action == GLFW_PRESS){
		tlg_userinput.kpressed[key] = 1;
		tlg_userinput.kheld[key] = 1;
	}
	if(action == GLFW_RELEASE){
		tlg_userinput.kpressed[key] = 0;
		tlg_userinput.kheld[key] = 0;
	}
}

void tlg_init_userinput(tlg_userinput_t* target, GLFWwindow* win){
	memset(target->kpressed, 0, sizeof(*target->kpressed) * TLG_KEYS_ARRAY_SIZE);
	memset(target->kheld, 0, sizeof(*target->kpressed) * TLG_KEYS_ARRAY_SIZE);
	glfwSetKeyCallback(win, key_callback);
}

void tlg_get_key_held(tlg_userinput_t* target, int32_t keycode, int8_t* dst){
	*dst = target->kheld[keycode];	
}
void tlg_get_key_pressed(tlg_userinput_t* target, int32_t keycode, int8_t* dst){
	*dst = target->kpressed[keycode];	
	target->kpressed[keycode] = 0;	
}
