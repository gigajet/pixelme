#ifndef _mapview_cpp_
#define _mapview_cpp_

#include "../platform-v2/View.h"
#include "../ds/MapBoard.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

struct MapView : View {
    char _m[MapBoard::MAP_SIZE][MapBoard::MAP_SIZE]; // Local copy to display
    MapBoard *m;
    sf::Sprite img[MapBoard::MAP_SIZE][MapBoard::MAP_SIZE];
    const static int PX_PIXEL = 22;
    std::vector<sf::Sprite> blank;
    std::vector<sf::Sprite> target;
    std::vector<sf::Sprite> stickTarget;
    std::vector<sf::Sprite> blocked;
    std::vector<sf::Sprite> occupiedRed;
    std::vector<sf::Sprite> occupiedBlue;
    std::vector<sf::Sprite> occupiedGreen;

    sf::Sprite randomSprite (std::vector<sf::Sprite>& sprites) {
        return sprites[rand()%(int)sprites.size()];
    }

    sf::Sprite getSprite (char type) {
        switch (type) {
            case MapBoard::BLANK: return randomSprite(blank);
            case MapBoard::BLANK_TARGET: return randomSprite(target);
            case MapBoard::BLANK_STICK_TARGET: return randomSprite(stickTarget);
            case MapBoard::BLOCKED: return randomSprite(blocked);
            case MapBoard::OCCUPIED_RED: return randomSprite(occupiedRed);
            case MapBoard::OCCUPIED_BLUE: return randomSprite(occupiedBlue);
            case MapBoard::OCCUPIED_GREEN: return randomSprite(occupiedGreen);
            default: return randomSprite(blank);
        }
    }

    void updateMapSprites() {
        for (int i=0; i<MapBoard::MAP_SIZE; ++i)
        for (int j=0; j<MapBoard::MAP_SIZE; ++j) {
            if (m->getCell(i,j) != _m[i][j]) {
                _m[i][j] = m->getCell(i,j);
                img[i][j] = getSprite(_m[i][j]);
            }
        }
    }

    MapView (MapBoard* m, 
    std::vector<sf::Sprite> &blank,
    std::vector<sf::Sprite> &target,
    std::vector<sf::Sprite> &stickTarget,
    std::vector<sf::Sprite> &blocked,
    std::vector<sf::Sprite> &occupiedRed,
    std::vector<sf::Sprite> &occupiedBlue,
    std::vector<sf::Sprite> &occupiedGreen): 
        m(m), blank(blank), target(target), 
        stickTarget(stickTarget), blocked(blocked),
        occupiedRed(occupiedRed), occupiedBlue(occupiedBlue),
        occupiedGreen(occupiedGreen) {
            for (int i=0; i<MapBoard::MAP_SIZE; ++i) 
            for (int j=0; j<MapBoard::MAP_SIZE; ++j) {
                _m[i][j] = m->getCell(i,j);
                img[i][j] = getSprite(_m[i][j]);
            }
        }

    virtual void draw(sf::RenderTarget *canvas, int xAbs, int yAbs) {
        updateMapSprites();
        for (int i=0; i<MapBoard::MAP_SIZE; ++i) 
        for (int j=0; j<MapBoard::MAP_SIZE; ++j) {
            img[i][j].setPosition(xAbs+j*PX_PIXEL, yAbs+i*PX_PIXEL);
            canvas->draw(img[i][j]);
        }
    }

    virtual void onKeyPressed (sf::Event::KeyEvent ev) {}
    virtual void onKeyReleased (sf::Event::KeyEvent ev) {}
    virtual void onClosed() {}
    virtual void onMousePressed(sf::Mouse::Button btn, int xRel, int yRel) {}
    virtual void onMouseReleased(sf::Mouse::Button btn, int xRel, int yRel) {}
    
};

#endif