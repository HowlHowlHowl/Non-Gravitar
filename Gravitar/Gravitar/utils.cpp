#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>


#define PI 3.14159265359f
using namespace sf;

//ritorna value ma compreso tra min e max
float clamp(float value, float min, float max) {
	if (value < min) {
		return min;
	}
	if (value > max) {
		return max;
	}

	return value;
}

//ritorna un carattere alfanumerico random
char randAlphanum()
{
	char alphanum[] ="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	return alphanum[rand() % (sizeof(alphanum) - 1)];
}

//ritorna un numero random tra 0 e 1
float randf01()
{
	return (float)((double)rand() / (double)RAND_MAX);
}

//Da radianti a gradi
float radToDeg(float rad) {
	return rad * 180.f / PI;
}

//Distanza tra 2 punti
float distance(Vector2f a, Vector2f b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}


//Area di un triangolo
float area(Vector2f a, Vector2f b, Vector2f c) {
	return abs( (a.x*(b.y - c.y) + b.x*(c.y - a.y) + c.x*(a.y - b.y))/2);
}