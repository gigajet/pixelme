#ifndef _imageview_h_
#define _imageview_h_

#include "View.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>

struct ImageView : View {

    // For implementers
    virtual void onKeyPressed (sf::Event::KeyEvent ev) {}
    virtual void onKeyReleased (sf::Event::KeyEvent ev) {}
    virtual void onClosed() {}
    virtual void onMousePressed(sf::Mouse::Button btn, int xRel, int yRel) {}
    virtual void onMouseReleased(sf::Mouse::Button btn, int xRel, int yRel) {}
    
    int w=0, h=0;
    sf::Sprite img;
    void setDimension (int width, int height) {
        w=width; h=height;
    }
    void setImage (sf::Sprite image) {
        img=image;
    }
    
    virtual void draw(sf::RenderTarget *canvas, int xAbs, int yAbs) {
        img.setPosition(xAbs, yAbs);
        if (w==0 || h==0) {
        }
        else {
            // Scale the picture to fit into desired width and height
            auto rect = img.getGlobalBounds();
            img.scale(1.0*w / rect.width, 1.0*h / rect.height);
        }
        canvas->draw(img);
    }

};

#endif