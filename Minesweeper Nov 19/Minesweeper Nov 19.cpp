#include <SFML/Graphics.hpp>
#include <time.h>

int main()
{
	srand(time(0));

	sf::RenderWindow app(sf::VideoMode(400, 400), "Minesweeper!");

	
	int imgSize = 32;
	int grid[12][12];
	int showGrid[12][12]; //for showing blank tiles

	sf::Texture texture;
	texture.loadFromFile("tiles.jpg");
	sf::Sprite sprite(texture);

	for (int i = 1; i <= 10; i++)
		for (int j = 1; j <= 10; j++)
		{
			
			showGrid[i][j] = 10;
			if (rand() % 5 == 0)  grid[i][j] = 9;
			else grid[i][j] = 0;
		}

	for (int i = 1; i <= 10; i++)
		for (int j = 1; j <= 10; j++)
		{
			int n = 0;
			if (grid[i][j] == 9) continue;
			if (grid[i + 1][j] == 9) n++;
			if (grid[i][j + 1] == 9) n++;
			if (grid[i - 1][j] == 9) n++;
			if (grid[i][j - 1] == 9) n++;
			if (grid[i + 1][j + 1] == 9) n++;
			if (grid[i - 1][j - 1] == 9) n++;
			if (grid[i - 1][j + 1] == 9) n++;
			if (grid[i + 1][j - 1] == 9) n++;
			grid[i][j] = n;
		}

	while (app.isOpen())
	{
		sf::Vector2i pos = sf::Mouse::getPosition(app);
		int x = pos.x / imgSize;
		int y = pos.y / imgSize;

		sf::Event event;
		while (app.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				app.close();

			if (event.type == sf::Event::MouseButtonPressed)
				if (event.key.code == sf::Mouse::Left) showGrid[x][y] = grid[x][y];
				else if (event.key.code == sf::Mouse::Right) showGrid[x][y] = 11;
		}

		//color of background
		app.clear(sf::Color::White);
		//add column to grid
		for (int i = 1; i <= 10; i++)
			//add row to grid
			for (int j = 1; j <= 10; j++)
			{
				if (showGrid[x][y] == 9) showGrid[i][j] = grid[i][j];
				sprite.setTextureRect(sf::IntRect(showGrid[i][j] * imgSize, 0, imgSize, imgSize));
				sprite.setPosition(i * imgSize, j * imgSize);
				app.draw(sprite);
			}

		app.display();
	}

	return 0;
}