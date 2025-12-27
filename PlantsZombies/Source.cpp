#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;
int main()
{
	RenderWindow window(VideoMode(800, 600), "Plants vs Zombies");
	sleep(seconds(2));
	window.close();
	return 0;
}