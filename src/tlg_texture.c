#include "tlg_texture.h"
#include <stddef.h>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void tlg_load_texture_from_file(
		char*     fp, 
		uint8_t   rdprm, 
		uint8_t** bufd, 
		int32_t*  wxd, 
		int32_t*  wyd,
		int32_t*  cnlsd)
{
	stbi_set_flip_vertically_on_load(rdprm & TLG_STB_FLIPONLOAD);
	*bufd = stbi_load(fp, wxd, wyd, cnlsd, 0);
}

void tlg_gl_gen_texture2D_from_memory(
		uint8_t*  pix,      
		uint32_t  sx,
		uint32_t  sy,
		uint32_t  cnls,    
		uint32_t  minmagm, 
		uint32_t  wrpm,    
		uint32_t* glidd    
		)
{
	glCreateTextures(GL_TEXTURE_2D, 1, glidd);
	glBindTexture(GL_TEXTURE_2D, *glidd);
	glTextureParameteri(*glidd, GL_TEXTURE_MIN_FILTER, minmagm);
	glTextureParameteri(*glidd, GL_TEXTURE_MAG_FILTER, minmagm);
	glTextureParameteri(*glidd, GL_TEXTURE_WRAP_T, wrpm); 
	glTextureParameteri(*glidd, GL_TEXTURE_WRAP_S, wrpm); 

	glTextureStorage2D(*glidd, 1, cnls == 4? GL_RGBA8 : GL_RGB8, sx, sy);
	glTextureSubImage2D(*glidd, 0, 0, 0, sx, sy, cnls == 4? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, pix);
	glGenerateTextureMipmap(*glidd);
}

void tlg_gl_gen_texture2D_from_file(
		char* fp,
		uint8_t rdprm,
		uint32_t minmagm,
		uint32_t wrpm, 
		uint32_t* glidd
		)
{
	uint8_t* pixb;
	int32_t wx, wy, c;
	tlg_load_texture_from_file(fp, rdprm, &pixb, &wx, &wy, &c);
	if(!pixb){
		printf("Error while readind texture. Likely %s is incorrect path.\n", fp);
		return;
	}
	tlg_gl_gen_texture2D_from_memory(pixb, wx, wy, c, minmagm, wrpm, glidd);
}
