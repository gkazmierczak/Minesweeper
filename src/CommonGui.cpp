#include "CommonGui.h"

void initButton(sf::RectangleShape *rectangleShape,sf::Text *text, float rectX, float rectY, float textX,float textY,const sf::String &str, const sf::Color &fillColor,const sf::Color &outlineColor, const sf::Font &font) {
    rectangleShape->setPosition(rectX,rectY);
    rectangleShape->setFillColor(fillColor);
    rectangleShape->setOutlineColor(outlineColor);
    rectangleShape->setOutlineThickness(3);
    text->setString(str);
    text->setFont(font);
    text->setOrigin(text->getLocalBounds().width / 2, text->getLocalBounds().height / 2);
    text->setPosition(textX,textY);
    text->setCharacterSize(36);
}
bool buttonHover(sf::Event *event, sf::RectangleShape *box, sf::Text *text){
    if (box->getGlobalBounds().contains(event->mouseMove.x, event->mouseMove.y)) {
        text->setFillColor(sf::Color(255, 0, 0));
        return true;
    }
    return false;
}
