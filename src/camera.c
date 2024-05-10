#include <stdbool.h>
#include "camera.h"
#include "window.h"

#define INIT_ZOOM 0.25
#define MIN_ZOOM 0.1
#define MAX_ZOOM 2.0
#define MAX_SCALE 5.0

static struct {
  mat4x4 projection;
  float ratio;
  float zoom;
  Point pos;
  Point scale;
} camera;


static void update_camera_ratio(bool force) {
  float ratio = window_ratio();
  if (camera.ratio == ratio && !force) return;

  camera.ratio = ratio;
  mat4x4_ortho(camera.projection, -ratio * camera.scale.x, ratio * camera.scale.x, -camera.scale.y, camera.scale.y, 1.0, -1.0);
}

void init_camera() {
  camera.pos.x = 0.0;
  camera.pos.y = 0.0;
  camera.scale.x = 1.0;
  camera.scale.y = 1.0;
  camera.zoom = INIT_ZOOM;
    
  update_camera_ratio(true);
}


void get_vp(mat4x4 vp) {
  update_camera_ratio(false); 

  mat4x4_identity(vp);
  mat4x4_translate(vp, -camera.pos.x * camera.zoom, -camera.pos.y * camera.zoom, 0.0);
  mat4x4_scale_aniso(vp, vp, camera.zoom, camera.zoom, camera.zoom);
  mat4x4_mul(vp, camera.projection, vp);
}

void reset_camera() {
  camera.pos.x = 0.0;
  camera.pos.y = 0.0;
  camera.scale.x = 1.0;
  camera.scale.y = 1.0;
  camera.zoom = INIT_ZOOM;

  update_camera_ratio(true);
}

void move_camera(float dx, float dy) {
  camera.pos.x += dx / camera.zoom * camera.scale.x;
  camera.pos.y += dy / camera.zoom * camera.scale.y;
}

void zoom_camera(float dzoom) {
  camera.zoom += dzoom * camera.zoom;

  if (camera.zoom < MIN_ZOOM) camera.zoom = MIN_ZOOM;
  if (camera.zoom > MAX_ZOOM) camera.zoom = MAX_ZOOM;
}

const Point *camera_pos() {
  return &camera.pos;
}

const Point *camera_scale() {
  return &camera.scale;
}

float camera_zoom() {
  return camera.zoom;
}

void scale_camera(float scale_x, float scale_y) {
  camera.scale.x += scale_x * camera.scale.x;
  camera.scale.y += scale_y * camera.scale.y;

  if (camera.scale.x < 1.0) camera.scale.x = 1.0;
  if (camera.scale.y < 1.0) camera.scale.y = 1.0;
  if (camera.scale.x > MAX_SCALE) camera.scale.x = MAX_SCALE;
  if (camera.scale.y > MAX_SCALE) camera.scale.y = MAX_SCALE;

  update_camera_ratio(true);
}
