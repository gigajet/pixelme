#ifndef _mapeditorview_cpp_
#define _mapeditorview_cpp_

#include "../platform-v2/View.h"
#include "../platform-v2/TextBox.h"
#include "../platform-v2/ImageView.h"
#include "MapView.h"
#include <fstream>
#include <memory>
#include <Windows.h>

struct MapEditorView : View {
    MapBoard m;
    MapView mv;
    char cLeftMouse=MapBoard::BLANK_TARGET, 
        cRightMouse=MapBoard::BLOCKED;

    const int x_mv = 265, y_mv = 20,
        x_tbLeftMouse = 20+15, y_tbLeftMouse = 20,
        x_imLeftMouse = 140+15, y_imLeftMouse = 20,
        x_tbRightMouse=20+15, y_tbRightMouse=40,
        x_imRightMouse=140+15, y_imRightMouse=40,
        x_tbLegend=40+15, y_tbLegend=60+20+10,
        x_tblBlank=20+15, y_tblBlank=80+20+20,
        x_tblBlankTarget=20+15, y_tblBlankTarget=100+20+20,
        x_tblStickTarget=20+15, y_tblStickTarget=120+20+20,
        x_tblBlocked=20+15, y_tblBlocked=140+20+20,
        x_tblOccupiedRed=20+15, y_tblOccupiedRed=160+20+20,
        x_tblOccupiedBlue=20+15, y_tblOccupiedBlue=180+20+20,
        x_tblOccupiedGreen=20+15, y_tblOccupiedGreen=200+20+20,
        x_tblSave=20+15, y_tblSave=220+20+20,
        x_tblUndo=20+15, y_tblUndo=240+20+20,
        x_tblOpen=20+15, y_tblOpen=260+20+20;
    sf::String tx_tbLeftMouse="Left mouse: ",
        tx_tbRightMouse="Right mouse: ",
        tx_tbLegend="Legend (hotkey)",
        tx_tblBlank="Blank (1/Q)",
        tx_tblBlankTarget="Blank Target (2/W)",
        tx_tblStickTarget="Stick Target (3/E)", 
        tx_tblBlocked="Blocked Tile (4/R)", 
        tx_tblOccupiedRed="Occupied Red (5/T)", 
        tx_tblOccupiedBlue="Occupied Blue (6/Y)", 
        tx_tblOccupiedGreen="Occupied Green (7/U)",
        tx_tblSave="Save (Ctrl-S)", 
        tx_tblUndo="Undo (Ctrl-Z)", 
        tx_tblOpen="Open (Ctrl-O)";
    sf::Sprite spBlank, spBlankTarget, spStickTarget, spBlocked,
        spOccupiedRed, spOccupiedBlue, spOccupiedGreen;

    TextBox tbLeftMouse, tbRightMouse;
    TextBox tbLegend, tblBlank,
        tblBlankTarget, tblStickTarget, 
        tblBlocked, tblOccupiedRed, tblOccupiedBlue, 
        tblOccupiedGreen;
    TextBox tblSave, tblUndo, tblOpen;
    ImageView imLeftMouse, imRightMouse;

    sf::Sprite getSprite (char type) {
        switch (type) {
            case MapBoard::BLANK: return spBlank;
            case MapBoard::BLANK_TARGET:return spBlankTarget;
            case MapBoard::BLANK_STICK_TARGET:return spStickTarget;
            case MapBoard::BLOCKED:return spBlocked;
            case MapBoard::OCCUPIED_RED:return spOccupiedRed;
            case MapBoard::OCCUPIED_BLUE:return spOccupiedBlue;
            case MapBoard::OCCUPIED_GREEN:return spOccupiedGreen;
            default: return spBlank;
        }
    }

    MapEditorView(sf::Font mainFont,
    std::vector<sf::Sprite> &blank,
    std::vector<sf::Sprite> &target,
    std::vector<sf::Sprite> &stickTarget,
    std::vector<sf::Sprite> &blocked,
    std::vector<sf::Sprite> &occupiedRed,
    std::vector<sf::Sprite> &occupiedBlue,
    std::vector<sf::Sprite> &occupiedGreen) : 
        mv(&m, blank, target, stickTarget, blocked, 
            occupiedRed,occupiedBlue,occupiedGreen) {
        mv.setPosition(x_mv, y_mv);
        this->addChild(&mv);

        spBlank = blank[0],
        spBlankTarget = target[0],
        spStickTarget = stickTarget[0],
        spBlocked = blocked[0],
        spOccupiedRed = occupiedRed[0],
        spOccupiedBlue = occupiedBlue[0],
        spOccupiedGreen = occupiedGreen[0];

        tbLeftMouse.setSize(16);
        tbRightMouse.setSize(16);
        tbLegend.setSize(16);
        tblBlank.setSize(16);
        tblBlankTarget.setSize(16);
        tblStickTarget.setSize(16);
        tblBlocked.setSize(16);
        tblOccupiedRed.setSize(16);
        tblOccupiedBlue.setSize(16);
        tblOccupiedGreen.setSize(16);
        tblSave.setSize(16);
        tblUndo.setSize(16);
        tblOpen.setSize(16);

        tbLeftMouse.setFont(mainFont);
        tbRightMouse.setFont(mainFont);
        tbLegend.setFont(mainFont);
        tblBlank.setFont(mainFont);
        tblBlankTarget.setFont(mainFont);
        tblStickTarget.setFont(mainFont);
        tblBlocked.setFont(mainFont);
        tblOccupiedRed.setFont(mainFont);
        tblOccupiedBlue.setFont(mainFont);
        tblOccupiedGreen.setFont(mainFont);
        tblSave.setFont(mainFont);
        tblUndo.setFont(mainFont);
        tblOpen.setFont(mainFont);

        tbLeftMouse.setColor(sf::Color::White);
        tbRightMouse.setColor(sf::Color::White);
        tbLegend.setColor(sf::Color::Yellow);
        tblBlank.setColor(sf::Color::White);
        tblBlankTarget.setColor(sf::Color::White);
        tblStickTarget.setColor(sf::Color::White);
        tblBlocked.setColor(sf::Color::White);
        tblOccupiedRed.setColor(sf::Color::White);
        tblOccupiedBlue.setColor(sf::Color::White);
        tblOccupiedGreen.setColor(sf::Color::White);
        tblSave.setColor(sf::Color::White);
        tblUndo.setColor(sf::Color::White);
        tblOpen.setColor(sf::Color::White);

        
        tbLeftMouse.setText(tx_tbLeftMouse);
        tbRightMouse.setText(tx_tbRightMouse);
        tbLegend.setText(tx_tbLegend);
        tblBlank.setText(tx_tblBlank);
        tblBlankTarget.setText(tx_tblBlankTarget);
        tblStickTarget.setText(tx_tblStickTarget);
        tblBlocked.setText(tx_tblBlocked);
        tblOccupiedRed.setText(tx_tblOccupiedRed);
        tblOccupiedBlue.setText(tx_tblOccupiedBlue);
        tblOccupiedGreen.setText(tx_tblOccupiedGreen);
        tblSave.setText(tx_tblSave);
        tblUndo.setText(tx_tblUndo);
        tblOpen.setText(tx_tblOpen);

        tbLeftMouse.setPosition(x_tbLeftMouse,y_tbLeftMouse); 
        tbRightMouse.setPosition(x_tbRightMouse,y_tbRightMouse);
        tbLegend.setPosition(x_tbLegend,y_tbLegend); 
        tblBlank.setPosition(x_tblBlank,y_tblBlank);
        tblBlankTarget.setPosition(x_tblBlankTarget,y_tblBlankTarget);
        tblStickTarget.setPosition(x_tblStickTarget,y_tblStickTarget);
        tblBlocked.setPosition(x_tblBlocked,y_tblBlocked); 
        tblOccupiedRed.setPosition(x_tblOccupiedRed,y_tblOccupiedRed); 
        tblOccupiedBlue.setPosition(x_tblOccupiedBlue,y_tblOccupiedBlue);
        tblOccupiedGreen.setPosition(x_tblOccupiedGreen,y_tblOccupiedGreen);
        tblSave.setPosition(x_tblSave,y_tblSave); 
        tblUndo.setPosition(x_tblUndo,y_tblUndo); 
        tblOpen.setPosition(x_tblOpen,y_tblOpen);
        imLeftMouse.setPosition(x_imLeftMouse,y_imLeftMouse); 
        imRightMouse.setPosition(x_imRightMouse,y_imRightMouse);

        this->addChild(&tbLeftMouse); 
        this->addChild(&tbRightMouse);
        this->addChild(&tbLegend); 
        this->addChild(&tblBlank);
        this->addChild(&tblBlankTarget); 
        this->addChild(&tblStickTarget); 
        this->addChild(&tblBlocked); 
        this->addChild(&tblOccupiedRed); 
        this->addChild(&tblOccupiedBlue);
        this->addChild(&tblOccupiedGreen);
        this->addChild(&tblSave); 
        this->addChild(&tblUndo); 
        this->addChild(&tblOpen);
        this->addChild(&imLeftMouse); 
        this->addChild(&imRightMouse);
    }
    
    virtual void draw(sf::RenderTarget *canvas, int xAbs, int yAbs) {
        imLeftMouse.setImage(getSprite(cLeftMouse));
        imRightMouse.setImage(getSprite(cRightMouse));
    }
    virtual void onKeyPressed (sf::Event::KeyEvent ev) {}
    virtual void onKeyReleased (sf::Event::KeyEvent ev) {
        switch (ev.code) {
            case sf::Keyboard::Num1:cLeftMouse=MapBoard::BLANK; break;
            case sf::Keyboard::Num2:cLeftMouse=MapBoard::BLANK_TARGET; break;
            case sf::Keyboard::Num3:cLeftMouse=MapBoard::BLANK_STICK_TARGET; break;
            case sf::Keyboard::Num4:cLeftMouse=MapBoard::BLOCKED; break;
            case sf::Keyboard::Num5:cLeftMouse=MapBoard::OCCUPIED_RED; break;
            case sf::Keyboard::Num6:cLeftMouse=MapBoard::OCCUPIED_BLUE; break;
            case sf::Keyboard::Num7:cLeftMouse=MapBoard::OCCUPIED_GREEN; break;
            case sf::Keyboard::Q:cRightMouse=MapBoard::BLANK; break;
            case sf::Keyboard::W:cRightMouse=MapBoard::BLANK_TARGET; break;
            case sf::Keyboard::E:cRightMouse=MapBoard::BLANK_STICK_TARGET; break;
            case sf::Keyboard::R:cRightMouse=MapBoard::BLOCKED; break;
            case sf::Keyboard::T:cRightMouse=MapBoard::OCCUPIED_RED; break;
            case sf::Keyboard::Y:cRightMouse=MapBoard::OCCUPIED_BLUE; break;
            case sf::Keyboard::U:cRightMouse=MapBoard::OCCUPIED_GREEN; break;
            case sf::Keyboard::S:
                if (ev.control) {
                    OPENFILENAME ofn;
                    ZeroMemory(&ofn, sizeof(ofn));
                    ofn.lStructSize = sizeof(OPENFILENAME);
                    ofn.hwndOwner = NULL;
                    ofn.lpstrFilter = "All Files\0*.*\0\0";
                    ofn.lpstrCustomFilter = NULL;
                    char bFileName[MAX_PATH];
                    bFileName[0]='\0';
                    ofn.lpstrFile = bFileName;
                    ofn.nMaxFile = MAX_PATH;
                    char bFileTitle[MAX_PATH];
                    ofn.lpstrFileTitle = bFileTitle;
                    ofn.nMaxFileTitle = MAX_PATH;
                    ofn.lpstrInitialDir = NULL;
                    ofn.lpstrTitle = "Save map as";
                    ofn.Flags = OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST
                        | OFN_NOCHANGEDIR;
                    if (GetSaveFileName(&ofn)) {
                        std::ofstream cout(bFileName);
                        cout<<m;
                        cout.close();
                    }
                }
                break;
            case sf::Keyboard::O:
                if (ev.control) {
                    OPENFILENAME ofn;
                    ZeroMemory(&ofn, sizeof(ofn));
                    ofn.lStructSize = sizeof(OPENFILENAME);
                    ofn.hwndOwner = NULL;
                    ofn.lpstrFilter = "All Files\0*.*\0\0";
                    ofn.lpstrCustomFilter = NULL;
                    char bFileName[MAX_PATH];
                    bFileName[0]='\0';
                    ofn.lpstrFile = bFileName;
                    ofn.nMaxFile = MAX_PATH;
                    char bFileTitle[MAX_PATH];
                    ofn.lpstrFileTitle = bFileTitle;
                    ofn.nMaxFileTitle = MAX_PATH;
                    ofn.lpstrInitialDir = NULL;
                    ofn.lpstrTitle = "Select map file to open...";
                    ofn.Flags = OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
                    if (GetOpenFileName(&ofn)) {
                        std::ifstream cin(bFileName);
                        cin>>m;
                        cin.close();
                    }
                }
                break;
            case sf::Keyboard::Z:
                if (ev.control) {
                    m.undo();
                }
        }
    }
    virtual void onClosed() {}
    virtual void onMousePressed(sf::Mouse::Button btn, int xRel, int yRel) {
        if (x_mv<=xRel && xRel<x_mv+MapBoard::MAP_SIZE*MapView::PX_PIXEL
            && y_mv<=yRel && yRel<y_mv+MapBoard::MAP_SIZE*MapView::PX_PIXEL) {
                // Inside the board.
                int c=(xRel-x_mv)/MapView::PX_PIXEL,
                    r=(yRel-y_mv)/MapView::PX_PIXEL;
                if (btn == sf::Mouse::Left) {
                    m.setCell(r,c,cLeftMouse);
                }
                else if (btn == sf::Mouse::Right) {
                    m.setCell(r,c,cRightMouse);
                }
            }
    }
    virtual void onMouseReleased(sf::Mouse::Button btn, int xRel, int yRel) {}
};

#endif