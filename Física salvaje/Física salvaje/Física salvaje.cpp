#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// Clase para representar una pelota
class Ball {
public:
    Ball(const sf::Texture& texture, const sf::Vector2u& windowSize)
        : velocity(0.0f) {
        sprite.setTexture(texture);

        // Escalar la pelota al 50% del tamaño original
        sprite.setScale(0.5f, 0.5f);

        // Posición aleatoria en la parte superior de la pantalla
        float startX = static_cast<float>(std::rand() % (windowSize.x - texture.getSize().x));
        sprite.setPosition(startX, 0.0f);
    }

    void update(float gravity, const sf::Vector2u& windowSize) {
        // Aplicar gravedad y mover la pelota
        velocity += gravity;
        sprite.move(0, velocity);
    }

    bool isOutOfBounds(const sf::Vector2u& windowSize) const {
        // Si la pelota toca el suelo, se considera fuera de la pantalla
        return sprite.getPosition().y + sprite.getGlobalBounds().height >= windowSize.y;
    }

    bool isClicked(const sf::Vector2f& mousePos) const {
        // Verificar si la pelota fue clickeada
        return sprite.getGlobalBounds().contains(mousePos);
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(sprite);
    }

private:
    sf::Sprite sprite;
    float velocity;
    friend class Game; // Permitir acceso directo al sprite desde la clase Game
};

// Clase para gestionar el juego
class Game {
public:
    Game() : score(0) {
        // Cargar textura para las pelotas
        if (!texture.loadFromFile("C:/SFML/imagenes/rcircle.png")) { // Ruta de la imagen
            std::cerr << "Error al cargar la textura\n";
            exit(-1);
        }

        // Inicializar la ventana
        window.create(sf::VideoMode(WIDTH, HEIGHT), "Juego de Pelotas");
        window.setFramerateLimit(60);

        // Inicializar el generador de números aleatorios
        std::srand(static_cast<unsigned>(std::time(nullptr)));
    }

    void run() {
        while (window.isOpen()) {
            processEvents();
            update();
            render();
        }
    }

private:
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;
    const float gravity = 0.25f;

    sf::RenderWindow window;
    sf::Texture texture;
    std::vector<Ball> balls;
    sf::Clock spawnClock;
    int score;

    void processEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    handleMouseClick(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                }
            }
        }
    }

    void update() {
        // Crear una nueva pelota cada 1.5 segundos
        if (spawnClock.getElapsedTime().asSeconds() > 1.5f) {
            balls.emplace_back(texture, sf::Vector2u(WIDTH, HEIGHT));
            spawnClock.restart();
        }

        // Actualizar pelotas
        for (auto it = balls.begin(); it != balls.end();) {
            it->update(gravity, sf::Vector2u(WIDTH, HEIGHT));

            // Eliminar pelotas que tocan el suelo
            if (it->isOutOfBounds(sf::Vector2u(WIDTH, HEIGHT))) {
                score -= 5; // Penalización
                std::cout << "¡Pelota tocó el suelo! -5 puntos. Puntuación: " << score << std::endl;
                it = balls.erase(it);
            }
            else {
                ++it;
            }
        }
    }

    void render() {
        window.clear(sf::Color::Black);

        // Dibujar pelotas
        for (const auto& ball : balls) {
            ball.draw(window);
        }

        // Dibujar puntuación
        drawScore();

        window.display();
    }

    void handleMouseClick(const sf::Vector2f& mousePos) {
        for (auto it = balls.begin(); it != balls.end();) {
            if (it->isClicked(mousePos)) {
                score += 10;
                it = balls.erase(it);
            }
            else {
                ++it;
            }
        }
    }

    void drawScore() {
        sf::Font font;
        if (!font.loadFromFile("tipografia/Space 3D Project.otf")) {
            std::cerr << "Error al cargar la fuente\n";
            exit(-1);
        }

        sf::Text text;
        text.setFont(font);
        text.setString("puntaje: " + std::to_string(score));
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        text.setPosition(10, 10);

        window.draw(text);
    }
};

int main() {
    Game game;
    game.run();
    return 0;
}
