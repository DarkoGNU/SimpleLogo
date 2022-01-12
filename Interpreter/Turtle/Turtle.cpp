/**
 * @copyright
 * Copyright 2021 The SimpleLogo Authors.
 * Licensed under GPL-3.0-or-later
 */

#define _USE_MATH_DEFINES

#include "Turtle.hpp"

#include <cmath>

Turtle::Turtle(TileMap &tileMap)
    : tileMap(tileMap), x((tileMap.getSize() / 2) + 0.5),
      y((tileMap.getSize() / 2) + 0.5), angle(0) {
    left(90);
}

Turtle::Turtle(TileMap &tileMap, double startX, double startY,
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
    // Length check
    if (length <= 0)
        return length != 0 ? back(-length) : void();

    double intpart;
    double fractpart = std::modf(length, &intpart);

    double angleCos = std::cos(angle);
    double angleSin = std::sin(angle);

    for (std::size_t i = 1; i <= static_cast<std::size_t>(intpart); i++) {
        x += angleCos;
        y += angleSin;

        tileMap.step(static_cast<std::size_t>(x), static_cast<std::size_t>(y));
    }

    // The remainder
    x += fractpart * angleCos;
    y += fractpart * angleSin;

    tileMap.step(static_cast<std::size_t>(x), static_cast<std::size_t>(y));
}

void Turtle::back(double length) {
    // Length check
    if (length <= 0)
        return length != 0 ? forward(-length) : void();

    double intpart;
    double fractpart = std::modf(length, &intpart);

    double angleCos = std::cos(angle);
    double angleSin = std::sin(angle);

    for (std::size_t i = 1; i <= static_cast<std::size_t>(intpart); i++) {
        x -= angleCos;
        y -= angleSin;

        tileMap.step(static_cast<std::size_t>(x), static_cast<std::size_t>(y));
    }

    // The remainder
    x -= fractpart * angleCos;
    y -= fractpart * angleSin;

    tileMap.step(static_cast<std::size_t>(x), static_cast<std::size_t>(y));
}
