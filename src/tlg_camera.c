#include "tlg_camera.h"
#include "cglm/cam.h"
#include "cglm/affine.h"
#include <string.h>

void tlg_init_camera_data(float radFov, vec3 position, tlg_camera_t* dst)
{
    dst->fov = radFov;
    memcpy(dst->position, position, sizeof(vec3));
} 

void tlg_camera_move(tlg_camera_t* target, vec3 dv)
{
    glm_vec3_add(target->position, dv, target->position);
}

void tlg_set_camera_rotation(tlg_camera_t* target, float aspectRaito, float x, float y, float z)
{
    glm_mat4_identity(target->rotation);

    vec3 ox = {1, 0, 0};
    vec3 oy = {0, 1, 0};
    vec3 oz = {0, 0, 1};

    glm_rotate(target->rotation, z, oz);
    glm_rotate(target->rotation, y, oy);
    glm_rotate(target->rotation, x, ox);

    tlg_update_camera_dir_vectors(target);
}

void tlg_update_camera_dir_vectors(tlg_camera_t* target)
{
    vec4 fw = {0, 0, -1, 1};
    vec4 rg = {1, 0,  0, 1};
    vec4 up = {0, 1,  0, 1};
    vec4 fres, rres, ures;

    glm_mat4_mulv(target->rotation, fw, fres);
    glm_mat4_mulv(target->rotation, rg, rres);
    glm_mat4_mulv(target->rotation, up, ures);
    glm_vec3(fres, target->forward);
    glm_vec3(rres, target->right);
    glm_vec3(ures, target->up);
}

void tlg_get_camera_view_mat(tlg_camera_t* target, mat4 outView)
{
    vec3 v; glm_vec3_add(target->position, target->forward, v);
    glm_lookat(target->position, v, target->up, outView);
}

void tlg_get_camera_projection(tlg_camera_t* target, float aspectRaito, mat4 outProj)
{
    glm_perspective(target->fov, aspectRaito, 0.1, 1000, outProj);
}
