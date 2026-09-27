#include "camera.h"

// Função que inicializa a camera
Camera2D initCamera (Vector2 target, Vector2 offset, float rotation, float zoom){
    
    Camera2D camera = { 0 }; // Inicializa a camera com o valor padrao 0
    camera.target = target; // Define o ponto do mundo que a camera aponta
    camera.offset = offset; // define onde o ponto do mundo que a camera aponta vai ser renderizado na tela
    camera.rotation = rotation; // define a rocatção da camera
    camera.zoom = zoom; // define o zoom da camera 
    
    return camera; // retorna a camera ja inicializada
}

// função que atualiza a posição da camera para seguir o jogador
void updateCameraFollow (Camera2D &camera, Vector2 target){
    
    camera.target = target; // atualiza o ponto do mundo que a camera aponta para o ponto do jogador
    
}