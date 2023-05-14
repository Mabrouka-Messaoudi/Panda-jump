#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>
#include<sstream>
using namespace sf;
struct Point {
	int x, y;
};

int main()
{

	srand(time(0));
	RenderWindow app(VideoMode(400, 533), "miniGame");
	app.setFramerateLimit(60);
	// music
	Music music;
	music.openFromFile("audio/Beat-Thee.ogg");
	music.setVolume(100);
	music.play();
	music.setLoop(true);
	Music Gmusic;
	Gmusic.openFromFile("audio/Arcade-Retro-game-Over-Sound-Effect-Royalty-free.ogg");
	Gmusic.setVolume(100);
	Music gmusic;
	gmusic.openFromFile("audio/CONGRATULATIONS.ogg");
	gmusic.setVolume(100);
	//score
	Font font;
	font.loadFromFile("font/RoughenCorner.ttf");
	Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(40);
	scoreText.setFillColor(sf::Color::Black);
	//les objets
	Texture t1, t2, t3, t4, t5, t6;
	t1.loadFromFile("images/background.png");
	t2.loadFromFile("images/bamboo.png");
	t3.loadFromFile("images/panda.png");
	t4.loadFromFile("images/snake.png");
	t5.loadFromFile("images/gameover.png");
	t6.loadFromFile("images/gagner.png");

	Sprite sBackground(t1), sPlat(t2), sPers(t3), ssnake(t4), Sgameover(t5), sGagner(t6);
	ssnake.setPosition(5.0f, 235.0f);
	sPlat.scale(0.05f, 0.05f);
	sPers.scale(0.08f, 0.08f);
	ssnake.scale(0.05f, 0.05f);


	Sgameover.scale(0.32f, 0.3f);
	sGagner.scale(0.13f, 0.25f);
	//initialisation des bombou
	Point plat[20];
	for (int i = 0; i < 10; i++)
	{
		plat[i].x = rand() % 400;
		plat[i].y = rand() % 533;
	}

	int x = 100, y = 100, h = 200;//position du panda
	float dx = 0, dy = 0;
	bool gameover = false;
	bool gagner = false;
	int score = 0;

	while (app.isOpen())
	{
		// Gestion des événements
		Event event;
		while (app.pollEvent(event))
		{
			if (event.type == Event::Closed)
				app.close();

		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
			x += 3;
		if (Keyboard::isKeyPressed(Keyboard::Left))
			x -= 3;
		//mise à jour et affichage  du score
		if (y == h)
		{
			score += 1;
			scoreText.setString("Score: " + std::to_string(score));
		}
		//panda's jump
		dy += 0.2;
		y += dy;
		if (y > 500)
			dy = -10;
		// mise à jour des bombou
		if (y < h)
			for (int i = 0; i < 10; i++)
			{
				y = h;
				plat[i].y = plat[i].y - dy;
				if (plat[i].y > 533)
				{
					plat[i].y = 0;
					plat[i].x = rand() % 400;
				}
			}
		// detect jump on the bombou
		for (int i = 0; i < 10; i++)
		{
			if ((x + 50 > plat[i].x) && (x + 20 < plat[i].y + 68) && (y + 70 > plat[i].y) && (y + 70 < plat[i].y + 14) && (dy > 0))  dy = -10;
		}
		// mouvement du serpent
		if (ssnake.getPosition().x < 350)
			ssnake.setPosition(ssnake.getPosition().x + 0.5, ssnake.getPosition().y);
		else
			ssnake.setPosition(5, ssnake.getPosition().y);

		sPers.setPosition(x, y);

		app.draw(sBackground);
		app.draw(sPers);
		// set and draw platforms
		for (int i = 0; i < 10; i++)
		{
			sPlat.setPosition(plat[i].x, plat[i].y);
			app.draw(sPlat);

		}
		app.draw(scoreText);
		app.draw(ssnake);
		//gameover
		if (ssnake.getPosition().x == sPers.getPosition().x)
		{
			music.stop();
			Gmusic.play();
			goto gameover;

		}
		//gagner

		if (score == 1000)
		{

			music.stop();
			gmusic.play();
			goto gagner;
		}

		app.display();

	}
gameover:
	while (app.isOpen())
	{
		sf::Event event;
		while (app.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				app.close();
		}

		app.draw(Sgameover);
		app.draw(scoreText);
		app.display();
	}
gagner:
	while (app.isOpen())
	{
		sf::Event event;
		while (app.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				app.close();
		}

		app.draw(sGagner);
		app.display();
	}

	return 0;
}
