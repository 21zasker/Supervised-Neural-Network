#include "Canvas.h"

void Canvas::initCanvas()
{
    outputs_image.create(64, 64);
    outputs_texture.loadFromImage(outputs_image);
    outputs_sprite.setPosition(512, 0);
    outputs_sprite.setScale(512 / 64, 512 / 64);
    outputs_sprite.setTexture(outputs_texture);
}

void Canvas::initUI()
{
    initSprite(sprite_wheel, texture_wheel, "Sources/color_wheel.png", 390, 50, 0.1f, 0.1f);
    initSprite(sprite_keys, texture_keys, "Sources/rgb_keys.png", 20, 180, 0.8f, 0.8f);

    font.loadFromFile("Sources/PressStart2P.ttf");

    initText(title, "Neural Networks", 24, sf::Color::Black, 20, 30);
    initText(instr, "Press the key:", 21, sf::Color::Black, 20, 130);
    initText(instr1, "for Red", 19, sf::Color::Red, 90, 205);
    initText(instr2, "for Green", 19, sf::Color(0, 188, 0), 90, 265);
    initText(instr3, "for Blue", 19, sf::Color::Blue, 90, 330);
    initText(start_text, "> Start", 19, sf::Color::Black, 320, 430);
}

void Canvas::initText(sf::Text &text, const std::string &string, int size, const sf::Color &color, float x, float y)
{
    text.setFont(font);
    text.setCharacterSize(size);
    text.setString(string);
    text.setFillColor(color);
    text.setPosition(x, y);
}

void Canvas::initSprite(sf::Sprite &sprite, sf::Texture &texture, const std::string &filename, float posX, float posY, float scaleX, float scaleY)
{
    texture.loadFromFile(filename);
    sprite.setTexture(texture);
    sprite.setPosition(posX, posY);
    sprite.setScale(scaleX, scaleY);
}

void Canvas::drawCanvas(sf::RenderWindow &window)
{
    window.draw(outputs_sprite);
    window.draw(title);
    window.draw(sprite_wheel);
    window.draw(instr);
    window.draw(instr1);
    window.draw(instr2);
    window.draw(instr3);
    window.draw(start_text);
    window.draw(sprite_keys);
}