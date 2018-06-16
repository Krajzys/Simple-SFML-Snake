#pragma once
class SnakeC
{
public:
	struct Snake
	{
		int x, y;
	} *snake;
	int length = 4, size = 16;
	sf::Sprite snakeS;
	sf::Texture snakeHeadLeftTx, snakeHeadRightTx, snakeHeadUpTx, snakeHeadDownTx, snakeTailTx;

	SnakeC(int startLength, int maxLength);
	~SnakeC();
	void moveTail();
	sf::Sprite getSprite(int dir, int number);
	void loadTextures(sf::Texture snakeHeadLeftTx, sf::Texture snakeHeadRightTx, sf::Texture snakeHeadUpTx, sf::Texture snakeHeadDownTx, sf::Texture snakeTailTx);
	void moveHead(int dir, int N, int M);
	void move(int dir, int N, int M);
	bool hasLost();
};

