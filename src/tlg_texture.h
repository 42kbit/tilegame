#ifndef _H_TEXTURE_H
#define _H_TEXTURE_H

#include "glglfw.h"
#include <inttypes.h>

#define TLG_STB_FLIPONLOAD 0b1

void tlg_load_texture_from_file(
		char*     fp,  // path to image in filesystem
		uint8_t   rdprm, // read params (how to process image load)
		uint8_t** bufd,   // buffer destination
		int32_t*  wxd,    // width destination
		int32_t*  wyd,    // height destenation
		int32_t*  cnlsd // cnls = channels
		);

void tlg_gl_gen_texture2D_from_memory(
		uint8_t*  pix,      
		uint32_t  sx,
		uint32_t  sy,
		uint32_t  cnls,    
		uint32_t  minmagm, // minmagfilter mode
		uint32_t  wrpm,    // wrapmode
		uint32_t* glidd    // glID destination
		);

void tlg_gl_gen_texture2D_from_file(
		char* fp,
		uint8_t rdprm, 
		uint32_t minmagm,
		uint32_t wrpm, 
		uint32_t* glidd
		);
#endif
