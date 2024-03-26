#pragma once
#include <SFML/Graphics.hpp>

class Canvas
{
public:
    Canvas()
    {
        initCanvas();
        initUI();
    }

    // Canvas for rendering colors
    sf::Image outputs_image;
    sf::Texture outputs_texture;
    sf::Sprite outputs_sprite;

    // Start training text button
    sf::Text start_text;

    // Render function
    void drawCanvas(sf::RenderWindow &window);

private:
    // User interface
    sf::Texture texture_keys;
    sf::Texture texture_wheel;
    sf::Sprite sprite_wheel;
    sf::Sprite sprite_keys;

    sf::Font font;

    sf::Text title;
    sf::Text instr;
    sf::Text instr1;
    sf::Text instr2;
    sf::Text instr3;

    // Create canvas
    void initCanvas();

    // Create UI
    void initUI();

    // Create text
    void initText(sf::Text &text, const std::string &string, int size, const sf::Color &color, float x, float y);
    void initSprite(sf::Sprite &sprite, sf::Texture &texture, const std::string &filename, float posX, float posY, float scaleX, float scaleY);
};