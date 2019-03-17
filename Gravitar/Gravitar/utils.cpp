#include <SFML/Graphics.hpp>
#include <iostream>

//ritorna un numero tra -1 e 1
float randf()
{		
	return (double)rand() / (double)RAND_MAX;
}

//ritorna un numero tra 0 e 1
float randf01()
{
	return abs(randf());
}