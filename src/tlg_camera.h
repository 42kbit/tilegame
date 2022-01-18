#ifndef _H_CAMERA_H
#define _H_CAMERA_H
#include "cglm/struct/vec3.h"
#include "cglm/struct/mat4.h"

typedef struct
{
    float fov;

    mat4 rotation;
    vec3 position;

    vec3 forward;
    vec3 up;
    vec3 right;
} tlg_camera_t;

void tlg_init_camera_data(float radFov, vec3 position, tlg_camera_t* dst);
void tlg_move_camera(tlg_camera_t* target, vec3 dv);
void tlg_set_camera_position(tlg_camera_t* target, vec3 newpos);
void tlg_set_camera_rotation(tlg_camera_t* target, float aspectRaito, float x, float y, float z);
void tlg_update_camera_dir_vectors(tlg_camera_t* target);
void tlg_get_camera_view_mat(tlg_camera_t* target, mat4 outView);
void tlg_get_camera_projection(tlg_camera_t* target, float aspectRaito, mat4 outProj);

#endif 

