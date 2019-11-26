#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int main()
{
	srand(time(0));

	RenderWindow app(VideoMode(400, 400), "Minesweeper!");

	int w = 32;
	int grid[12][12];
	int showGrid[22][22]; //for showing

	Texture t;
	t.loadFromFile("tiles2.jpg");
	Sprite s(t);
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
		Vector2i pos = Mouse::getPosition(app);
		int mouseXPos = pos.x / w;
		int mouseYPos = pos.y / w;

		Event somethingHasHappened;
		while (app.pollEvent(somethingHasHappened))
		{
			if (somethingHasHappened.type == Event::Closed)
				app.close();

			if (somethingHasHappened.type == Event::MouseButtonPressed)
			{
				if (somethingHasHappened.key.code == Mouse::Left)
				{
					showGrid[mouseXPos][mouseYPos] = grid[mouseXPos][mouseYPos];
				}
				else if (somethingHasHappened.key.code == Mouse::Right) showGrid[mouseXPos][mouseYPos] = 12;
			}
		}

		app.clear(Color::White);
		for (int i = 1; i <= 10; i++)
			for (int j = 1; j <= 10; j++)
			{
				if (showGrid[mouseXPos][mouseYPos] == 9) showGrid[i][j] = grid[i][j];
				s.setTextureRect(IntRect(showGrid[i][j] * w, 0, w, w));
				s.setPosition(i * w, j * w);
				app.draw(s);
			}

		app.display();
	}

	return 0;
}