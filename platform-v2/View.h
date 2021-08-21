#ifndef _view_h_
#define _view_h_

#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>

/**
 * Any implementors should override these methods:
 * + draw: remember to use absolute position
 *          when drawing to canvas.
 * + on* : input handling
 * **/

struct View {

    // For implementers
    virtual void draw(sf::RenderTarget *canvas, int xAbs, int yAbs) {}
    virtual void onKeyPressed (sf::Event::KeyEvent ev) {}
    virtual void onKeyReleased (sf::Event::KeyEvent ev) {}
    virtual void onClosed() {}
    virtual void onMousePressed(sf::Mouse::Button btn, int xRel, int yRel) {}
    virtual void onMouseReleased(sf::Mouse::Button btn, int xRel, int yRel) {}

    std::vector<View*> children;
    int xRel=0, yRel=0; // Relative to its parent, if any
    View *parent=nullptr;

    View () {}
    View (View *parent, int xRel, int yRel): 
        xRel(xRel), yRel(yRel), parent(parent) {
        parent->addChild(this);
    }

    void dispatchDraw (sf::RenderTarget *canvas) {
        int xAbs, yAbs;
        std::tie(xAbs, yAbs) = this->calculateAbsolutePosition();
        this->draw(canvas, xAbs, yAbs);
        for (View* v : children) {
            v->dispatchDraw(canvas);
        }
    }

    void addChild (View *view) {
        view->parent = this;
        children.push_back(view);
    }

    void setPosition (int xRel, int yRel) {
        this->xRel=xRel; this->yRel=yRel;
    }

    std::pair<int,int> calculateAbsolutePosition () {
        if (this->parent) {
            auto parentAbs = parent->calculateAbsolutePosition();
            return {this->xRel + parentAbs.first,
                this->yRel + parentAbs.second};
        }
        else return {this->xRel, this->yRel};
    }

    // Handle input
    void handle (sf::Event ev) {
        switch (ev.type) {
            case sf::Event::Closed: this->onClosed(); break;
            case sf::Event::KeyPressed: this->onKeyPressed(ev.key); break;
            case sf::Event::KeyReleased: this->onKeyReleased(ev.key); break;
            case sf::Event::MouseButtonPressed:
            case sf::Event::MouseButtonReleased: {
                int xAbs, yAbs;
                std::tie(xAbs, yAbs) = this->calculateAbsolutePosition();
                sf::Mouse::Button button = ev.mouseButton.button;
                int xRel = ev.mouseButton.x - xAbs;
                int yRel = ev.mouseButton.y - yAbs;
                if (ev.type == sf::Event::MouseButtonPressed)
                    this->onMousePressed(button, xRel, yRel);
                else this->onMouseReleased(button, xRel, yRel);
            }
        }
    }

    void dispatchHandle (sf::Event ev) {
        this->handle(ev);
        for (View *v : this->children)
            v->dispatchHandle(ev);
    }

};

#endif