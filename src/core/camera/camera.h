#pragma once
#include "raylib.h"

Camera2D initCamera (Vector2 target, Vector2 offset, float rotation, float zoom); // função que inicializa a camera
void updateCameraFollow(Camera2D &camera, Vector2 target); // função que atualiza a posição da camera para seguir o jogador