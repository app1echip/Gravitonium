#include "Widget.h"
#include "../Resource/ResourceManager/FontManager.h"
#include "../Resource/ResourceManager/TextureManager.h"

Widget::Widget(const sf::Vector2f &pPos, const sf::Vector2f &pSize, const std::string &fontFace, int fontSize,
               const std::string &message, int pCall) : position(pPos), size(pSize), call(pCall) {
    auto &fontManager = FontManager::getInstance();
    text.setFont(fontManager.getFont(fontFace));
    text.setCharacterSize(fontSize);
    text.setString(message);
    text.setPosition(position);
    text.setFillColor(sf::Color::White);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(1.f);

    auto &textureManager = TextureManager::getInstance();
    sprite.setPosition(position);
    sprite.setTexture(textureManager.getTexture("SelectBackground"));
    sprite.setColor(sf::Color::White);
    sprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
}

void Widget::draw(sf::RenderTarget &target, sf::RenderStates) const {
    if (boxVisible) { target.draw(sprite); }
    target.draw(text);
}

bool Widget::contain(const sf::Vector2i &pos) {
    return pos.x > position.x && pos.y > position.y && pos.x < position.x + size.x &&
           pos.y < position.y + size.y;
}

void Widget::setMessage(const std::string &msg) { text.setString(msg); }

std::string Widget::getMessage() { return text.getString(); }

void Widget::setTexture(const std::string &pName) {
    auto &textureManager = TextureManager::getInstance();
    sprite.setTexture(textureManager.getTexture(pName));
    sprite.setScale(2.f / 3.f, 2.f / 3.f);
}