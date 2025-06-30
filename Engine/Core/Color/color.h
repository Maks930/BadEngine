#ifndef COLOR_H
#define COLOR_H

#include <Types/Types.h>

class Color {
public:
    uint8_t red{};
    uint8_t green{};
    uint8_t blue{};
    uint8_t alpha{255};

    constexpr Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) :
        red(r), green(g), blue(b), alpha(a)
    {}


    constexpr explicit Color(uint32_t color) :
        red(static_cast<uint8_t>((color & 0xFF'00'00'00) >> 24)),
        green(static_cast<uint8_t>((color & 0x00'FF'00'00) >> 16)),
        blue(static_cast<uint8_t>((color & 0x00'00'FF'00) >> 8)),
        alpha(static_cast<uint8_t>((color & 0x00'00'00'FF) >> 0))
    {}

    constexpr uint32_t toInteger() const {
        return static_cast<uint32_t>((red << 24) | (green << 16) | (blue << 8) | alpha);
    }



    operator int() const {
        return static_cast<int>(toInteger());
    }
};

constexpr bool operator==(Color l, Color r) {
    return (l.red == r.red) && (l.green == r.green) && (l.blue == r.blue) && (l.alpha == r.alpha);
}

constexpr bool operator!=(Color l, Color r) {
    return !(l==r);
}

constexpr Color operator+(Color l, Color r) {
    const auto c_add = [](uint8_t lhs,uint8_t rhs)
    {
        const int isResult = int{lhs} + int{rhs};
        return static_cast<uint8_t>((isResult>255) ? 255 : isResult);
    };

    return {
        c_add(l.red, r.red),
        c_add(l.green, r.green),
        c_add(l.blue, r.blue),
        c_add(l.alpha, r.alpha),
    };
}

constexpr Color operator-(Color l, Color r) {
    const auto c_sub = [](uint8_t lhs,uint8_t rhs)
    {
        const int isResult = int{lhs} - int{rhs};
        return static_cast<uint8_t>((isResult<0) ? 0 : isResult);
    };

    return {
        c_sub(l.red, r.red),
        c_sub(l.green, r.green),
        c_sub(l.blue, r.blue),
        c_sub(l.alpha, r.alpha),
    };
}

#endif // COLOR_H
