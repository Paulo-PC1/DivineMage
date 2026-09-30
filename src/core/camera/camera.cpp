#include "camera.hpp"

// Função que inicializa a camera
GameCamera::GameCamera(Vector2 target, Vector2 offset, float rotation, float zoom){
    
    _camera = { 0 }; // Inicializa a camera com o valor padrao 0
    _camera.target = target; // Define o ponto do mundo que a camera aponta
    _camera.offset = offset; // define onde o ponto do mundo que a camera aponta vai ser renderizado na tela
    _camera.rotation = rotation; // define a rocatção da camera
    _camera.zoom = zoom; // define o zoom da camera 
}

// função que atualiza a posição da camera para seguir o jogador
void GameCamera::follow (Vector2 target){
    
    _camera.target = target; // atualiza o ponto do mundo que a camera aponta para o ponto do jogador
    
}

Camera2D GameCamera::get() const{
    return _camera; // retorna a camera "crua" do raylib
}