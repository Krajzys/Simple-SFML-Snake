#pragma once
class FruitC
{
public:
	struct fruit
	{
		int x;
		int y;
		int type;
	} fruit;
	int **spawnArray;
	int counter;
	int size;
	sf::Sprite fruitS;
	sf::Texture fruitTx;

	FruitC(int N, int M, SnakeC &player);
	~FruitC();
	void loadTexture(sf::Texture fruitTx);
	sf::Sprite getSprite();
	void spawnFruit(int N, int M, SnakeC &player);
	void canSpawn(int N, int M, SnakeC &player);
};

