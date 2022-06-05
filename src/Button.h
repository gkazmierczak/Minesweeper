//
// Created by Gabriel on 05.06.2022.
//

#ifndef MINESWEEPER_BUTTON_H
#define MINESWEEPER_BUTTON_H


class Button {

public:
    Button(const char* txt){
        box=sf::RectangleShape(sf::Vector2f(200.f, 50.f));
        text=sf::Text();
        text.setString(txt);
        box.setPosition(300,150);
        box.setFillColor(sf::Color(32,32,32));
        box.setOutlineColor(sf::Color(190,190,190));
        box.setOutlineThickness(3);
        text.setFont(font);
        text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
        text.setCharacterSize(36);
    }
    void setPosition(float x, float y){
        text.setPosition(x,y);
        box.setPosition(x,y);
    }
    void setString(const char* txt){
        text.setString(txt);
    }
    void draw(){
        window->draw(box);
        window->draw(text);
    }
    sf::RenderWindow *window;
    sf::RectangleShape box;
    sf::Text text;
    sf::Font font;

};


#endif //MINESWEEPER_BUTTON_H
