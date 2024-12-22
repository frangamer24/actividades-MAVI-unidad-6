#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

using namespace sf;

int main()
{
    //parametros para la ventana
    const int width = 800;
    const int weight = 600;

    //parametros de movimiento
    Vector2f velocidad(0.0f, 0.0f);  //velocidad inicial
    Vector2f aceleracion(0.0f, 0.0f); //aceleracion inicial
    const float aceleracionmaxima = 10.0f; //velocidad maxima
    const float tazadeaceleracion = 0.2f; //cambio de aceleracion
    const float friccion = 0.05f; //friccion para desacelerar
   
    //creacion de la ventana
    RenderWindow window(VideoMode(width, weight), "acelerar");
    window.setFramerateLimit(60);

    //cargar textura
    Texture textura;
    textura.loadFromFile("imagen/rcircle.png");

    //crear el sprite
    Sprite sprite;
    sprite.setTexture(textura);
    sprite.setPosition(width / 2, weight / 2); //pocicion inicial

    //bucle principal
    while (window.isOpen())
    {
        Event evento;
        while (window.pollEvent(evento))
        {
            if (evento.type == Event::Closed)
                window.close();
        }

        //input del teclado
        if (Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            aceleracion.x = tazadeaceleracion; //aceleracion para la derecha
        }
        else if (Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            aceleracion.x = -tazadeaceleracion;//aceleracion para la izquierda
        }
        else
        {
            aceleracion.x = 0.0f; //sin aceleracion en X
        }
        if (Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            aceleracion.y = -tazadeaceleracion;//aceleracion para arriba
        }
        else if (Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            aceleracion.y = tazadeaceleracion;//aceleracion para abajo
        }
        else
        {
            aceleracion.y = 0.0f; //sin aceleracion en Y
        }

        //aplicar velocidad a la aceleracion
        velocidad += aceleracion;

        //limitar la velocidad maxima
        if (velocidad.x > aceleracionmaxima)velocidad.x = aceleracionmaxima;
        if (velocidad.x < -aceleracionmaxima)velocidad.x = -aceleracionmaxima;
        if (velocidad.y > aceleracionmaxima)velocidad.y = aceleracionmaxima;
        if (velocidad.y < -aceleracionmaxima)velocidad.y = -aceleracionmaxima;

        //aplicar friccion cuando no ahi aceleracion
        if (aceleracion.x == 0.0f)velocidad.x *= (1.0f - friccion);
        if (aceleracion.y == 0.0f)velocidad.y *= (1.0f - friccion);

        //mover el sprite
        sprite.move(velocidad);

        //evitar que salga de la ventana
        Vector2f posicion = sprite.getPosition();
        if (posicion.x < 0)sprite.setPosition(0, posicion.y);
        if (posicion.x > width - textura.getSize().x)sprite.setPosition(width - textura.getSize().x, posicion.y);
        if (posicion.y < 0)sprite.setPosition(posicion.x, 0);
        if (posicion.y > weight - textura.getSize().y)sprite.setPosition(posicion.x, weight - textura.getSize().y);

        //dibujar
        window.clear(); //limpiar
        window.draw(sprite); //dibujar
        window.display(); //mostrar
    }


    return 0;
}