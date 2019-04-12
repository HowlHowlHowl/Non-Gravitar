#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

using namespace sf;

#define PI 3.14159265359f
float randf01();
float radToDeg(float rad);
float degToRad(float deg);
float distance(Vector2f a, Vector2f b);
float area(Vector2f a, Vector2f b, Vector2f c);
float clamp(float value, float min, float max);
char randAlphanum();