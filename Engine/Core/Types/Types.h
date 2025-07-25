#ifndef TYPES_H
#define TYPES_H

#include <cstdint>

typedef struct  _win_size_ {
    uint32_t width, height;

    _win_size_(uint32_t _width, uint32_t _height) :
        width(_width), height(_height) {
    }

} WinSize;

typedef struct _Mouse_s {
    double x, y;
    double dx, dy;
    bool cursorLocked, cursorStarted;

    _Mouse_s(double _x, double _y, double _dx, double _dy, bool _cursorLocked, bool _cursorStarted) :
        x(_x), y(_y), dx(_dx), dy(_dy), cursorLocked(_cursorLocked), cursorStarted(_cursorStarted) {
    }

} Mouse;


#endif // TYPES_H
