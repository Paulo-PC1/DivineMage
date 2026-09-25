#include "camera.h"

Camera2D initCamera (Vector2 target, Vector2 offset, float rotation, float zoom){
    
    Camera2D camera = { 0 };
    camera.target = target;
    camera.offset = offset;
    camera.rotation = rotation;
    camera.zoom = zoom;
    
    return camera;
}

void updateCameraFollow (Camera2D &camera, Vector2 target){
    
    camera.target = target;
    
}