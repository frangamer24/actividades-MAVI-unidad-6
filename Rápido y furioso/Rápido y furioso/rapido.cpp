#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

int main()
{
    using namespace sf;

    //tamaño de la ventana
    const int WIDTH = 800;
    const int HEIGHT = 600;

    //movimientos
    float velocidad = 5.0f;
    float velocidadfinal = 30.0f;
    float velocidadyincremento = 2.0f;

    //creacion de la ventana
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "incremento de velocidad");
    window.setFramerateLimit(60);

    //carga de la textura
    Texture textura;
    textura.loadFromFile("imagen/rcircle.png");

    //verificar el tamaño de la textura
    textura.getSize().x == 0 || textura.getSize().y == 0;

    //creacion del sprite
    Sprite sprite;
    sprite.setTexture(textura);
    sprite.setPosition(-static_cast<int>(textura.getSize().x), HEIGHT / 2 - static_cast<int>(textura.getSize().y) / 2);

    //bucle principal
    while (window.isOpen())
    {
        Event evento;
        while (window.pollEvent(evento))
        {
            if (evento.type == Event::Closed);
        }

        //movimiento horizontal del sprite
        sprite.move(velocidad, 0);

        // Si el sprite sale de la pantalla, reinicia posición y aumenta velocidad
        if (sprite.getPosition().x > WIDTH) {
            sprite.setPosition(-static_cast<int>(textura.getSize().x), HEIGHT / 2 - static_cast<int>(textura.getSize().y) / 2);
            velocidad = std::min(velocidad + velocidadyincremento, velocidadfinal);
            std::cout << "Velocidad actual: " << velocidad << std::endl;
        }

        //dibujar
        window.clear();//limpiar
        window.draw(sprite);//dibujar
        window.display(); //mostrar en pantalla
    }

    return 0;
}
