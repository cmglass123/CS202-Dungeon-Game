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
	texture.loadFromFile("tiles2.jpg");
	sf::Sprite sprite(texture);

	for (int col = 1; col <= 10; col++)
		for (int row = 1; row <= 10; row++)
		{

			showGrid[col][row] = 10;
			if (rand() % 5 == 0)  grid[col][row] = 9;
			else grid[col][row] = 0;
		}

	for (int col = 1; col <= 10; col++)
		for (int row = 1; row <= 10; row++)
		{
			int n = 0;
			if (grid[col][row] == 9) continue;
			if (grid[col + 1][row] == 9) n++;
			if (grid[col][row + 1] == 9) n++;
			if (grid[col - 1][row] == 9) n++;
			if (grid[col][row - 1] == 9) n++;
			if (grid[col + 1][row + 1] == 9) n++;
			if (grid[col - 1][row - 1] == 9) n++;
			if (grid[col - 1][row + 1] == 9) n++;
			if (grid[col + 1][row - 1] == 9) n++;
			grid[col][row] = n;
		}

	while (app.isOpen())
	{
		sf::Vector2i pos = sf::Mouse::getPosition(app);
		int mouseX = pos.x / imgSize;
		int mouseY = pos.y / imgSize;

		sf::Event event;
		while (app.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				app.close();

			if (event.type == sf::Event::MouseButtonPressed)
				if (event.key.code == sf::Mouse::Left) showGrid[mouseX][mouseY] = grid[mouseX][mouseY];
				else if (event.key.code == sf::Mouse::Right) showGrid[mouseX][mouseY] = 12;
		}

		//color of background
		app.clear(sf::Color::White);

		//add column to grid
		for (int col = 1; col <= 10; col++)
			//add row to grid
			for (int row = 1; row <= 10; row++)
			{
				//show tiles if bomb tile is pressed
				if (showGrid[mouseX][mouseY] == 9) showGrid[col][row] = grid[col][row];

				sprite.setTextureRect(sf::IntRect(showGrid[col][row] * imgSize, 0, imgSize, imgSize));
				sprite.setPosition(col * imgSize, row * imgSize);
				app.draw(sprite);
			}

		app.display();
	}

	return 0;
}