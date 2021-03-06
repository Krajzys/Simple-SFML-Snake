#include "stdafx.h"

// Symuluje jeden tick czasu w grze
void Tick(SnakeC &player, FruitC &point, bool &hasLost, int &dir, int N, int M, int size)
{
	player.move(dir, N, M);
	point.canSpawn(N, M, player);
	point.spawnFruit(N, M, player);
	hasLost = player.hasLost();
}

// Ładuje wszystkie wymagane textury
void loadTextures(sf::Texture &snakeHeadLeftTx,
	sf::Texture &snakeHeadRightTx,
	sf::Texture &snakeHeadUpTx,
	sf::Texture &snakeHeadDownTx,
	sf::Texture &snakeTailTx,
	sf::Texture &fruitTx,
	sf::Texture &gameBgTx,
	sf::Texture &sideBarTx)
{
	snakeHeadLeftTx.loadFromFile("images\\greenHeadLeft.png");
	snakeHeadRightTx.loadFromFile("images\\greenHeadRight.png");
	snakeHeadUpTx.loadFromFile("images\\greenHeadUp.png");
	snakeHeadDownTx.loadFromFile("images\\greenHeadDown.png");
	snakeTailTx.loadFromFile("images\\greenTail.png");
	fruitTx.loadFromFile("images\\red2.png");
	gameBgTx.loadFromFile("images\\gameArea.png");
	sideBarTx.loadFromFile("images\\simpleSideBar.png");
}

int main()
{
	srand(time(0));
	// Ustawienie flag i wartości
	bool inMenu = true;
	bool hasLost = false;
	bool notStopped = true;
	//bool hasWon = false;
	bool changeM = false;
	bool hasPlayed = false;
	int N = 16, M = 16;
	int size = 16;
	int best = -1;
	int w = size * N;
	int h = size * M;
	int dir = 0;
	int menuChoice = 0;

	std::fstream saveFile;
	SnakeC player(4, N*M);
	FruitC point(N, M, player);

	sf::RenderWindow window(sf::VideoMode(w + 64, h), "Snake by Chris");
	int x = 3;
	window.setSize(sf::Vector2u(x * w + 2*x, x * h));

	// Tutaj bardzo długi ciąg ładujący i ustawiający napisy
	sf::Font font;
	font.loadFromFile("cour.ttf");

	sf::Text score, scoreN, winScreen, message, help, help2, highscore, highscoreN;
	score.setFont(font); score.setCharacterSize(14); score.setOutlineColor(sf::Color::Black);
	score.setFillColor(sf::Color::White); score.setPosition(w + 6, 4);
	score.setString("SCORE:"); score.setStyle(sf::Text::Bold); score.setOutlineThickness(1);

	scoreN.setFont(font); scoreN.setCharacterSize(14); scoreN.setOutlineColor(sf::Color::Black);
	scoreN.setFillColor(sf::Color::White); scoreN.setPosition(w + 6, 18); scoreN.setOutlineThickness(1);
	scoreN.setString(std::to_string(player.length)); scoreN.setStyle(sf::Text::Bold);

	highscore.setFont(font); highscore.setCharacterSize(14); highscore.setOutlineColor(sf::Color::Black);
	highscore.setFillColor(sf::Color::White); highscore.setPosition(w + 6, 220);
	highscore.setString("Best:"); highscore.setStyle(sf::Text::Bold); highscore.setOutlineThickness(1);

	highscoreN.setFont(font); highscoreN.setCharacterSize(14); highscoreN.setOutlineColor(sf::Color::Black);
	highscoreN.setFillColor(sf::Color::White); highscoreN.setPosition(w + 6, 234); highscoreN.setOutlineThickness(1);
	highscoreN.setString(std::to_string(best)); highscoreN.setStyle(sf::Text::Bold);

	winScreen.setFont(font); winScreen.setCharacterSize(30); winScreen.setOrigin(80, 30);
	winScreen.setFillColor(sf::Color::Yellow); winScreen.setPosition((w+64)/2 , 98);
	winScreen.setStyle(sf::Text::Bold);

	message.setFont(font); message.setCharacterSize(30);
	message.setFillColor(sf::Color::Black); message.setPosition(size / 2 * (N - 9), size / 2 * (M - 9));
	message.setStyle(sf::Text::Bold); message.setOutlineColor(sf::Color::White); message.setOutlineThickness(3);

	help.setFont(font); help.setCharacterSize(8);
	help.setFillColor(sf::Color::White); help.setPosition(w + 8, 40); help.setOutlineColor(sf::Color::Black);
	help.setStyle(sf::Text::Bold); help.setString("Move:\nWSAD\nMenu:\nESC\nRestart:\nr\nPause:\np\n\nTry to\ncollect\nas many\nfruits\nas you\ncan but\ndont bite\nyour tail");
	help.setOutlineThickness(1);
	
	help2.setFont(font); help2.setCharacterSize(14);
	help2.setFillColor(sf::Color::White); help2.setPosition(9, 54); help2.setOutlineColor(sf::Color::Black);
	help2.setStyle(sf::Text::Bold); help2.setString("W - up   S - down   Space - Select");
	help2.setOutlineThickness(1);

	sf::Texture snakeHeadLeftTx, snakeHeadRightTx, snakeHeadUpTx, snakeHeadDownTx, snakeTailTx, fruitTx, gameBgTx, sideBarTx;
	sf::Texture menuTx, playTx, continueTx, rankingTx, playHTx, continueHTx, rankingHTx;
	loadTextures(snakeHeadLeftTx, snakeHeadRightTx, snakeHeadUpTx, snakeHeadDownTx, snakeTailTx, fruitTx, gameBgTx, sideBarTx);
	menuTx.loadFromFile("images\\menu.png");
	playTx.loadFromFile("images\\playNH.png");
	continueTx.loadFromFile("images\\continueNH.png");
	rankingTx.loadFromFile("images\\rankingNH.png");
	playHTx.loadFromFile("images\\playH.png");
	continueHTx.loadFromFile("images\\continueH.png");
	rankingHTx.loadFromFile("images\\rankingH.png");

	sf::Sprite snake(snakeTailTx), fruit(fruitTx), gameBg(gameBgTx), sideBar(sideBarTx);
	sf::Sprite playButton, continueButton, rankingButton, menu(menuTx);
	playButton.setOrigin(64, 26); playButton.setPosition((w + 64) / 2, 100);
	continueButton.setOrigin(64, 26); continueButton.setPosition((w + 64) / 2, 160);
	rankingButton.setOrigin(64, 26); rankingButton.setPosition((w + 64) / 2, 220);

	menu.setPosition(0, 0);
	player.loadTextures(snakeHeadLeftTx, snakeHeadRightTx, snakeHeadUpTx, snakeHeadDownTx, snakeTailTx);
	point.loadTexture(fruitTx);
	sideBar.setPosition(w, 0);

	sf::Clock clock, clock2;
	float timer = 0, delay = 0.15, delayMenu = 0.2, timerMenu = 0;

	int change = 0;

	while (window.isOpen())
	{
		int i = 0; // Inicjalizacja iteratora i czasu
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				if (!hasLost && hasPlayed) // Przy wyjściu zapisz jeżeli gracz nie przegrał
				{
					saveFile.open("savefile.txt", std::ios::out);
					if (player.length >= best) saveFile << player.length << std::endl;
					else saveFile << best << std::endl;
					saveFile << point.fruit.x << " " << point.fruit.y << std::endl;
					saveFile << player.length << std::endl;
					for (i = 0; i < player.length; i++) // zapisuje od głowy do ogona
					{
						saveFile << player.snake[i].x << " " << player.snake[i].y << std::endl;
					}
					saveFile << dir;
					saveFile.close();
					std::cout << "Zapis!" << std::endl;
				}
				else if (player.length >= best) // Zapis samego BEST scora
				{
					std::cout << "Zapis2!" << std::endl; // Początek tworzenie kopii zapisu
					saveFile.open("savefile.txt", std::ios::in);
					int fruitx, fruity, plength, dircopy, oldbest;
					int **lengthArray;
					saveFile >> oldbest >> fruitx >> fruity >> plength;
					lengthArray = new int *[plength];
					for (int i = 0; i < plength; i++)
					{
						lengthArray[i] = new int[2];
						saveFile >> lengthArray[i][0] >> lengthArray[i][1];
					}
					saveFile >> dircopy;
					saveFile.close(); // koniec tworzenia kopii danych
					saveFile.open("savefile.txt", std::ios::out | std::ios::trunc); // odtwórz stary plik z nowym bestem
					saveFile << best << std::endl;
					saveFile << fruitx << " " << fruity << std::endl;
					saveFile << plength << std::endl;
					for (int i = 0; i < plength; i++)
						saveFile << lengthArray[i][0] << " " << lengthArray[i][1] << std::endl;
					saveFile << dircopy << std::endl;
					saveFile.close();
					for (int i = 0; i < plength; i++) delete[] lengthArray[i];
					delete[] lengthArray;
				}
				window.close();
				break;
			case sf::Event::TextEntered:
				// Pause - pauzuje
				if (event.text.unicode == 'p' && notStopped == true)
				{
					notStopped = false;
					message.setString("PAUSED (p)");
				}// Unpause - odpauzowuje
				else if (event.text.unicode == 'p' && notStopped == false)
				{
					notStopped = true;
				}// Restart - ustaw co trzeba
				else if (event.text.unicode == 'r') 
				{
					player.length = 4;
					hasLost = false;
					score.setPosition(w + 6, 4);
					scoreN.setPosition(w + 6, 18);
				}// Poruszanie się po menu
				else if (event.text.unicode == 'w' && inMenu) // Góra w Menu
					menuChoice--;
				else if (event.text.unicode == 's' && inMenu) // Dół w Menu
					menuChoice++;
				else if (event.text.unicode == 0x1B) // Wróć do menu
				{
					if (!hasLost && hasPlayed) // Jeżeli gracz nie przegrał zapisz grę
					{
						saveFile.open("savefile.txt", std::ios::out);
						if (player.length >= best) saveFile << player.length << std::endl;
						else saveFile << best << std::endl;
						saveFile << point.fruit.x << " " << point.fruit.y << std::endl;
						saveFile << player.length << std::endl;
						for (i = 0; i < player.length; i++) // zapisuje od głowy do ogona
						{
							saveFile << player.snake[i].x << " " << player.snake[i].y << std::endl;
						}
						saveFile << dir;
						saveFile.close();
						std::cout << "Zapis!" << std::endl;
					}
					inMenu = true;
				}
				break;
			}
		}


		// Kontrola kierunku priorytet mają kierunki boczne
		if (change == 0 && !inMenu && notStopped)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && dir != 2)
			{
				change = (dir == 1 ? 0 : 1);
				dir = 1;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && dir != 1)
			{
				change = (dir == 2 ? 0 : 1);
				dir = 2;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && dir != 0)
			{
				change = (dir == 3 ? 0 : 1);
				dir = 3;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && dir != 3)
			{
				change = (dir == 0 ? 0 : 1);
				dir = 0;
			}
		}

		// Wykonanie tick po upływie określonego czasy tutaj 0.15 s
		if (timer > delay && notStopped && !hasLost && !inMenu)
		{
			timer = 0;
			Tick(player, point, hasLost, dir, N, M, size);
			change = 0;
		}

		window.clear();

		// Rysowanie Menu
		if (inMenu)
		{
			int uk = 0;
			window.draw(menu);
			if (menuChoice > 2) menuChoice = 0;
			if (menuChoice < 0) menuChoice = 2;
			playButton.setTexture(playTx);
			continueButton.setTexture(continueTx);
			rankingButton.setTexture(rankingTx);
			window.draw(help2);
			switch (menuChoice)
			{
			case 0: // Wybrano play
				playButton.setTexture(playHTx);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) // Ustaw wszystkie potrzebne zmienne
				{
					saveFile.open("savefile.txt", std::ios::in);
					int best2 = 0;
					saveFile >> best2;
					saveFile.close();
					if (best2 > best) best = best2;
					hasPlayed = true;
					player.length = 4;
					score.setPosition(w + 6, 4);
					scoreN.setPosition(w + 6, 18);
					highscore.setPosition(w + 6, 220);
					highscoreN.setPosition(w + 6, 234);
					for (int u = 0; u < player.length; u++)
					{
						player.snake[u].x = 0;
						player.snake[u].y = player.length - u - 1;
					}
					dir = 0;
					point.canSpawn(N, M, player);
					point.spawnFruit(N, M, player);
					hasLost = false;
					inMenu = false;
				}
				break;
			case 1: // Wybrano Continue
				continueButton.setTexture(continueHTx);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) // Zatwierdzenie
				{
					if (!saveFile.seekg(0, std::ios_base::end) && !hasLost) // Odczytaj zapis jeżeli nie jest pusty i gracz nie przegrał
					{
						std::cout << "Odczyt" << std::endl;
						hasPlayed = true;
						int best2 = 0;
						saveFile.open("savefile.txt", std::ios::in);
						saveFile >> best2;
						if (best2 > best) best = best2;
						saveFile >> point.fruit.x >> point.fruit.y;
						saveFile >> player.length;
						for (uk = 0; uk < player.length; uk++)
						{
							saveFile >> player.snake[uk].x >> player.snake[uk].y;
						}
						saveFile >> dir;
						saveFile.close();
						inMenu = false;
						notStopped = false;
						message.setString("PAUSED (p)");
					}
					else // Jeżeli przegrał po prostu wyjdź z menu
						inMenu = false;
				}
				break;
			case 2: // Wybrano Exit
				rankingButton.setTexture(rankingHTx);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
				{
					if (!hasLost && hasPlayed) // zapisz jeżeli gracz nie przegrał i rozpoczął nową grę
					{
						saveFile.open("savefile.txt", std::ios::out);
						if (player.length >= best) saveFile << player.length << std::endl;
						else saveFile << best << std::endl;
						saveFile << point.fruit.x << " " << point.fruit.y << std::endl;
						saveFile << player.length << std::endl;
						for (i = 0; i < player.length; i++) // zapis współrzędnych weża od głowy do ogona
						{
							saveFile << player.snake[i].x << " " << player.snake[i].y << std::endl;
						}
						saveFile << dir;
						saveFile.close();
						std::cout << "Zapis!" << std::endl;
					}
					else if (player.length >= best && hasPlayed) // Jeżeli przegrał zapisz sam best score
					{
						std::cout << "Zapis2!" << std::endl;
						saveFile.open("savefile.txt", std::ios::in);
						int fruitx, fruity, plength, dircopy, oldbest;
						int **lengthArray;
						saveFile >> oldbest >> fruitx >> fruity >> plength;
						lengthArray = new int *[plength];
						for (int i = 0; i < plength; i++)
						{
							lengthArray[i] = new int[2];
							saveFile >> lengthArray[i][0] >> lengthArray[i][1];
						}
						saveFile >> dircopy;
						saveFile.close();
						saveFile.open("savefile.txt", std::ios::out | std::ios::trunc);
						saveFile << best << std::endl;
						saveFile << fruitx << " " << fruity << std::endl;
						saveFile << plength << std::endl;
						for (int i = 0; i < plength; i++)
							saveFile << lengthArray[i][0] << " " << lengthArray[i][1] << std::endl;
						saveFile << dircopy << std::endl;
						saveFile.close();
						for (int i = 0; i < plength; i++) delete[] lengthArray[i];
						delete[] lengthArray;
					}
					window.close();
				}
				break;
			}
			window.draw(playButton);
			window.draw(continueButton);
			window.draw(rankingButton);
		}

		// Rysuj ekran końcowy
		if (hasLost && !inMenu)
		{
			winScreen.setString("GAME OVER\n Press r\nto try again");
			window.draw(winScreen);
			score.setPosition(w / 2, 30);
			scoreN.setPosition(w / 2, 50);
			scoreN.setString(std::to_string(player.length));
			window.draw(score);
			window.draw(scoreN);
		}

		if (!hasLost && !inMenu)
		{
			// Rysuj obszar gry
			for (int i = 0; i < N; i++)
				for (int j = 0; j < M; j++)
				{
					gameBg.setPosition(i*size, j*size);
					window.draw(gameBg);
				}
			window.draw(sideBar);

			// Rysuj głowę węża
			if (player.length < 100) window.draw(player.getSprite(dir, 0));
			// Rysuj resztę węża
			for (int i = 1; i < player.length && player.length < 100; i++)
			{
				window.draw(player.getSprite(dir, i));
			}

			// Rysuj owoc
			window.draw(point.getSprite());

			// Rysuj wynik i ekran pomocy
			scoreN.setString(std::to_string(player.length));
			if (player.length > best) best = player.length;
			highscoreN.setString(std::to_string(best));
			window.draw(score);
			window.draw(scoreN);
			window.draw(highscore);
			window.draw(highscoreN);
			window.draw(help);
			if (!notStopped)
			{
				window.draw(message);
			}
		}
		window.display();
	}

	return 0;
}