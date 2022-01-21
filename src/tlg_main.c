#include "glglfw.h"
#include "tlg_main_loop.h"

#include <stdlib.h>
int main(void){
	tlg_onload();
	while(!glfwWindowShouldClose(pGlfwwindow)){
		tlg_onupdate();
	}
	tlg_onterminate();
	exit(0);
}
