#ifndef _textbox_h_
#define _textbox_h_

#include <SFML/Graphics.hpp>
#include "View.h"

struct TextBox : View {
    sf::String text;
    sf::Color color;
    sf::Font font;
    unsigned int size=16;

    sf::Text _renderText;

    void setText (sf::String newText) {
        text = newText;
        renderText();
    }
    void setColor (sf::Color newColor) {color = newColor; renderText();}
    void setFont (sf::Font newFont) {font=newFont; renderText();}
    void setSize (unsigned int newSize) {size=newSize; renderText();}

    void renderText() {
        _renderText.setString(text);
        _renderText.setFont(font);
        _renderText.setCharacterSize(size);
        _renderText.setFillColor(color);
    }

    void draw(sf::RenderTarget *canvas, int xAbs, int yAbs) {
        _renderText.setPosition(xAbs, yAbs);
        canvas->draw(_renderText);
    }
    
    // For implementers
    virtual void onKeyPressed (sf::Event::KeyEvent ev) {}
    virtual void onKeyReleased (sf::Event::KeyEvent ev) {}
    virtual void onClosed() {}
    virtual void onMousePressed(sf::Mouse::Button btn, int xRel, int yRel) {}
    virtual void onMouseReleased(sf::Mouse::Button btn, int xRel, int yRel) {}

};

#endif