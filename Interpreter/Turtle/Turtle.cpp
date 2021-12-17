#include "Turtle.h"

#include <cmath>

Turtle::Turtle(TileMap &tileMap)
    : tileMap(tileMap), x(tileMap.getSize() / 2), y(tileMap.getSize() / 2),
      angle(0) {
    left(90);
}

Turtle::Turtle(TileMap &tileMap, unsigned int startX, unsigned int startY,
               double startAngle)
    : tileMap(tileMap), x(startX), y(startY), angle(startAngle) {}

void Turtle::right(double turnAngle) {
    angle += turnAngle * (M_PI / 180);

    while (angle >= M_PI * 2)
        angle -= M_PI * 2;
}

void Turtle::left(double turnAngle) {
    angle -= turnAngle * (M_PI / 180);

    while (angle < 0)
        angle += M_PI * 2;
}

void Turtle::forward(double length) {
    double intpart;
    double fractpart = std::modf(length, &intpart);

    for (int i = 1; i <= intpart; i++) {
        x += std::cos(angle);
        y += std::sin(angle);

        tileMap.step(x, y);
    }

    // The remainder
    x += fractpart * std::cos(angle);
    y += fractpart * std::sin(angle);

    tileMap.step(x, y);
}

void Turtle::back(double length) {
    double intpart;
    double fractpart = std::modf(length, &intpart);

    for (int i = 1; i <= intpart; i++) {
        x -= std::cos(angle);
        y -= std::sin(angle);

        tileMap.step(x, y);
    }

    // The remainder
    x -= fractpart * std::cos(angle);
    y -= fractpart * std::sin(angle);

    tileMap.step(x, y);
}
