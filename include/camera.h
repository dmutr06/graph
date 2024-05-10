#ifndef CAMERA_H_
#define CAMERA_H_

#include "shared.h"
#include "linmath.h"

void init_camera();

void get_vp(mat4x4 vp);
void reset_camera();
void move_camera(float dx, float dy);
const Point *camera_pos();
const Point *camera_scale();
float camera_zoom();
void zoom_camera(float dzoom);
void scale_camera(float scale_x, float scale_y);

#endif
