#include "stdafx.h"
#include "FruitC.h"


FruitC::FruitC(int N, int M, SnakeC &player)
{
	this->fruit.type = 0;
	this->fruitTx = fruitTx;
	this->canSpawn(N, M, player);
	this->spawnFruit(N, M, player);
	this->size = 16;
}

void FruitC::loadTexture(sf::Texture fruitTx)
{
	this->fruitTx = fruitTx;
}

FruitC::~FruitC()
{
	std::cout << "Fruit Destroyed!" << std::endl;
}

sf::Sprite FruitC::getSprite()
{
	fruitS.setPosition(fruit.x*size, fruit.y*size);
	fruitS.setTexture(fruitTx);
	return fruitS;
}

void FruitC::spawnFruit(int N, int M, SnakeC &player)
{
	// Eating and spawning a fruit
	if ((player.snake[0].x == fruit.x) && (player.snake[0].y == fruit.y) && player.length < 100)
	{
		player.length++;
		int randomInt = rand() % counter;
		fruit.x = spawnArray[randomInt][0];
		fruit.y = spawnArray[randomInt][1];
	}
	for (int i = 0; i < N*M; i++)
		delete[] spawnArray[i];
	delete[] spawnArray;
}

void FruitC::canSpawn(int N, int M, SnakeC &player)
{
	int counter = 0;
	spawnArray = new int*[N*M];
	for (int i = 0; i < N*M; i++)
		spawnArray[i] = new int[2];
	bool isSnake = false;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
		{
			for (int k = 0; k < player.length; k++)
			{
				if (player.snake[k].x == j && player.snake[k].y == i) // if (player.snake[k].x == j && player.snake[k].y == i)
				{
					isSnake = true;
					break;
				}
			}

			if (!isSnake)
			{
				spawnArray[counter][0] = j;
				spawnArray[counter++][1] = i;
			}
			isSnake = false;
		}
	this->counter = counter;
}