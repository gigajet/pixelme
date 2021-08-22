#ifndef _mapboard_h_
#define _mapboard_h_

#include <string>
#include <tuple>
#include <stack>

struct MapBoard
{
    const static char
        BLANK = '0',
        BLANK_TARGET = '?',
        BLANK_STICK_TARGET = 'S',
        BLOCKED = 'X',
        OCCUPIED_RED = '-',
        OCCUPIED_BLUE = '+',
        OCCUPIED_GREEN = '~';
    const static int MAP_SIZE = 16;
    char map[MAP_SIZE][MAP_SIZE];
    std::vector<std::string> crap;

    MapBoard() {
        for (int i=0; i<MAP_SIZE; ++i)
            for (int j=0; j<MAP_SIZE; ++j)
                map[i][j] = BLANK;
    }

    char getCell(int r, int c) {return map[r][c];}

    std::stack<std::tuple<int, int, char> > undoStack;

    MapBoard& setCell(int r, int c, char cell) {
        if (map[r][c]!=cell) {
            undoStack.emplace(r,c,map[r][c]);
            map[r][c] = cell;
        }
        return *this;
    }

    void undo() {
        if (!undoStack.empty()) {
            int r,c; char ch;
            std::tie(r,c,ch) = undoStack.top();
            undoStack.pop();
            map[r][c]=ch;
        }
    }

    friend std::ostream& operator << (std::ostream& cout, const MapBoard& m);
    friend std::istream& operator >> (std::istream& cin, MapBoard& m);
};

std::istream& operator >> (std::istream& cin, MapBoard& m) {
    int row = 0;
    std::string str;
    do {
        std::getline(cin, str, '\n');
        if (cin.eof()) break;
        if (str[0]=='#') {
            m.crap.push_back(str);
        }
        else {
            for (int i=0; i<MapBoard::MAP_SIZE; ++i)
                m.map[row][i] = str[i];
            if (++row == MapBoard::MAP_SIZE) break;
        }
    } while (!cin.eof());
    return cin;
}

std::ostream& operator << (std::ostream& cout, const MapBoard& m) {
    if (!m.crap.empty()) {
        for (std::string str : m.crap)
            cout<<str<<"\n";
    }
    else {
        cout<<"#data#\n";
    }
    for (int i=0; i<MapBoard::MAP_SIZE; ++i) {
        for (int j=0; j<MapBoard::MAP_SIZE; ++j)
            cout<<m.map[i][j];
        cout<<"\n";
    }
    return cout;
}

#endif