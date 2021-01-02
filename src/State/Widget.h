#ifndef GRAVITONIUM_WIDGET_H
#define GRAVITONIUM_WIDGET_H

#include <string>
#include <SFML/Graphics.hpp>

class Widget : public sf::Drawable {
public:
    Widget(const sf::Vector2f &pPos, const sf::Vector2f &pSize, const std::string &fontFace, int fontSize,
           const std::string &message, int pCall);

    const int call;

    bool contain(const sf::Vector2i &);

    void setMessage(const std::string &);

    void setTexture(const std::string &);

    std::string getMessage();

    bool boxVisible = false;

private:
    sf::Text text;
    sf::Sprite sprite;

    const sf::Vector2f position, size;

    void draw(sf::RenderTarget &, sf::RenderStates) const;
};

#endif //GRAVITONIUM_WIDGET_H