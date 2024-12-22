#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int main()
{
    // Dimensiones de la ventana
    const int width = 800;
    const int weight = 600;

    //gravedad y rebote
    const float gravedad = 0.5f;
    const float rebotar = 0.7f;

    //creacion de la ventana
    RenderWindow window(VideoMode(width, weight), "velocidad con la caida de la bola");
    window.setFramerateLimit(60);

    //asignar la textura
    Texture textura;
    textura.loadFromFile("imagen/rcircle.png");

    //crear el sprite
    Sprite sprite;
    sprite.setTexture(textura);
    sprite.setPosition(width / 2 - textura.getSize().x / 2, 0);
    
    //variables del movimiento
    float velocidad = 0.0f; //velocidad inicial en Y

    //bucle principal
    while(window.isOpen())
    {
        Event evento;
        while (window.pollEvent(evento)) 
        {
            if (evento.type == Event::Closed);
        }

        //aplicar gravedad
        velocidad += gravedad;

        //mover el sprite
        sprite.move(0, velocidad);

        //detectar colicion con el suelo
        if(sprite.getPosition().y+textura.getSize().y>=weight)
        {
            //ajustar colicion para que no se hunda
            sprite.setPosition(sprite.getPosition().x, weight - textura.getSize().y);
            
            //usar porsentaje de velocidad de impacto para el rebote
            velocidad *= -rebotar;

            // Si la velocidad es muy baja, detener el movimiento (simulación de fricción)
            if(abs(velocidad)<1.0f)
            {
                velocidad = 0.0f;
            }
        }

        //dibujar
        window.clear();//limpiar ventana
        window.draw(sprite);//dibujar 
        window.display();//mostrar en pantalla
    }
    return 0;
}