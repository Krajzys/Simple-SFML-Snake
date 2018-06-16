#include "stdafx.h"
#include "SnakeC.h"


SnakeC::SnakeC(int startLength, int maxLength)
{
	this->length = startLength;
	this->snake = new struct Snake[maxLength];
	for (int i = 0; i < maxLength; i++)
	{
		if (i < startLength)
		{
			snake[i].x = 0;
			snake[i].y = length - i;
		}
		else
		{
			snake[i].x = -1;
			snake[i].y = -1;
		}
	}
}

SnakeC::~SnakeC()
{
	delete[] snake;
	std::cout << "Snake Destroyed!" << std::endl;
}

void SnakeC::moveTail()
{
	for (int i = this->length; i > 0; i--)
	{
		snake[i].x = snake[i - 1].x;
		snake[i].y = snake[i - 1].y;
	}
}

void SnakeC::moveHead(int dir, int N, int M)
{
	if (dir == 0) snake[0].y += 1;
	if (dir == 1) snake[0].x -= 1;
	if (dir == 2) snake[0].x += 1;
	if (dir == 3) snake[0].y -= 1;

	if (snake[0].x >= N) snake[0].x = 0;
	if (snake[0].x < 0) snake[0].x = N - 1;
	if (snake[0].y >= M) snake[0].y = 0;
	if (snake[0].y < 0) snake[0].y = M - 1;
}

void SnakeC::move(int dir, int N, int M)
{
	moveTail();
	moveHead(dir, N, M);
}

void SnakeC::loadTextures(sf::Texture snakeHeadLeftTx, sf::Texture snakeHeadRightTx, sf::Texture snakeHeadUpTx, sf::Texture snakeHeadDownTx, sf::Texture snakeTailTx)
{
	this->snakeHeadLeftTx = snakeHeadLeftTx;
	this->snakeHeadRightTx = snakeHeadRightTx;
	this->snakeHeadDownTx = snakeHeadDownTx;
	this->snakeHeadUpTx = snakeHeadUpTx;
	this->snakeTailTx = snakeTailTx;
}

sf::Sprite SnakeC::getSprite(int dir, int number)
{
	if (number == 0)
	{
		snakeS.setPosition(snake[number].x * size, snake[number].y * size);
		switch (dir)
		{
		case 1:
			snakeS.setTexture(snakeHeadLeftTx);
			break;
		case 2:
			snakeS.setTexture(snakeHeadRightTx);
			break;
		case 3:
			snakeS.setTexture(snakeHeadUpTx);
			break;
		case 0:
			snakeS.setTexture(snakeHeadDownTx);
			break;
		}
		return snakeS;
	}
	else
	{
		snakeS.setTexture(snakeTailTx);
		snakeS.setPosition(snake[number].x*size, snake[number].y*size);
		return snakeS;
	}
}

bool SnakeC::hasLost()
{
	bool hasLost = false;
	for (int i = 1; i < this->length; i++)
		if (this->snake[0].x == this->snake[i].x && this->snake[0].y == this->snake[i].y)
		{
			hasLost = true;
		}
	return hasLost;
}