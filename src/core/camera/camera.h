#pragma once
#include "raylib.h"

Camera2D initCamera (Vector2 target, Vector2 offset, float rotation, float zoom);
void updateCameraFollow(Camera2D &camera, Vector2 target);