#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

using namespace sf;
//ritorna un numero tra 0 e 1
float randf01()
{		
	return (float)((double)rand() / (double)RAND_MAX);
}

#define PI 3.14159265359f

float radToDeg(float rad) {
	return rad * 180.f / PI;
}

float distance(Vector2f a, Vector2f b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}