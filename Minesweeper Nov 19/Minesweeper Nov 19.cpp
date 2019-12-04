#include <SFML/Graphics.hpp>
#include <time.h>

#include <iostream>
#include <ostream>
#include <string>
#include <sstream>

using std::cout;
using std::endl;
using std::ostream;

void floodfill(int mX, int mY, int gShown[12][12], int gReal[12][12])
{
	cout << "Beginning floodfill on tile " << mX << ", " << mY << endl;
	gShown[mX + 1][mY] = gReal[mX + 1][mY];
	gShown[mX][mY + 1] = gReal[mX][mY + 1];
	gShown[mX - 1][mY] = gReal[mX - 1][mY];
	gShown[mX][mY - 1] = gReal[mX][mY - 1];

	//recursive calls
	if (gReal[mX + 1][mY] == 0 && gShown[mX + 1][mY] != 0) floodfill(mX + 1, mY, gShown, gReal);
	if (gReal[mX][mY + 1] == 0 && gShown[mX][mY + 1] != 0) floodfill(mX, mY + 1, gShown, gReal);
	if (gReal[mX - 1][mY] == 0 && gShown[mX - 1][mY] != 0) floodfill(mX - 1, mY, gShown, gReal);
	if (gReal[mX][mY - 1] == 0 && gShown[mX][mY - 1] != 0) floodfill(mX, mY - 1, gShown, gReal);
}

int main()
{
	srand(time(0));

	sf::RenderWindow app(sf::VideoMode(400, 400), "Minesweeper!");


	int imgSize = 32;
	int grid[12][12];
	int showGrid[12][12]; //for showing tiles underneath
	int charTile[12][12];

	sf::Texture texture;
	texture.loadFromFile("tiles2.jpg");
	sf::Sprite sprite(texture);

	//add column to grid
	for (int col = 1; col <= 10; col++)
		//add row to grid
		for (int row = 1; row <= 10; row++)
		{

			//set sprite to 11 in tiles.png
			charTile[col][row] = 11;

			//set to 10 in tiles.png
			showGrid[col][row] = 10;
			//# of bombs
			if (rand() % 5 == 0)  grid[col][row] = 9;
			else grid[col][row] = 0;
		}

	//set tiles to row
	for (int row = 1; row <= 10; row++)
		//set tiles for column
		for (int col = 1; col <= 10; col++)
		{
			int n = 0;
			if (grid[row][col] == 9) continue;
			if (grid[row + 1][col] == 9) n++;
			if (grid[row][col + 1] == 9) n++;
			if (grid[row - 1][col] == 9) n++;
			if (grid[row][col - 1] == 9) n++;
			if (grid[row + 1][col + 1] == 9) n++;
			if (grid[row - 1][col - 1] == 9) n++;
			if (grid[row - 1][col + 1] == 9) n++;
			if (grid[row + 1][col - 1] == 9) n++;
			grid[row][col] = n;
		}

	//set starting hp
	int hp = 3;
	//cout << "Starting hp is: " << hp << endl;

	//sets up font and checks font file
	sf::Font font;
	if (!font.loadFromFile("arial.ttf")) {
		cout << "can't open font" << endl;
	}
	//creates text and sets font
	sf::Text hpText;
	hpText.setFont(font);
	//sets size and color, along with placement and what is written
	hpText.setCharacterSize(20);
	hpText.setFillColor(sf::Color::Black);
	hpText.setPosition(30.f, 355.f);
	hpText.setStyle(sf::Text::Bold);
	hpText.setString(" Starting HP is: 3. ");

	std::ostringstream os;



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

			/*if (event.type == sf::Event::MouseButtonPressed && showGrid[mouseX][mouseY] == 12)
			{
				cout << "Treasure Chest Looted, hp is " << hp << endl;
				hp++;
			}*/

			if (event.type == sf::Event::MouseButtonPressed && grid[mouseX][mouseY] == 0)
			{
				if (event.key.code == sf::Mouse::Left)
				{
					//Floodfill
					floodfill(mouseX, mouseY, showGrid, grid);
				}
			}

			//register if a monster has been clicked on and deincrement hp
			if (event.type == sf::Event::MouseButtonPressed && grid[mouseX][mouseY] == 9)
			{
				if (event.key.code == sf::Mouse::Left)
				{
					hp--;
					hp--;
					
					os.clear();
					os.str("");
					if (hp < 0) {
						os << "failstate reached, hp is " << hp << ". ";
					}
					else {
						os << "Monster Encountered, hp is now: " << hp << ". ";
					}
					hpText.setString(os.str());
				}
			}

			//defeat a monster and replace it with a chest
			if (event.type == sf::Event::MouseButtonPressed && grid[mouseX][mouseY] == 9)
			{
				if (event.key.code == sf::Mouse::Right)
				{
					os.clear();
					os.str("");
					grid[mouseX][mouseY] = 12;
					os << " Monster Defeated. ";
					hpText.setString(os.str());
				}
			}

			//loot a chest, increment hp and replace it with a flag 
			if (event.type == sf::Event::MouseButtonPressed && grid[mouseX][mouseY] == 12)
			{
				if (event.key.code == sf::Mouse::Left)
				{
					hp++;
					os.clear();
					os.str(". ");
					os << "Chest Looted, hp is now: " << hp << ". ";
					hpText.setString(os.str());

					grid[mouseX][mouseY] = 11;
					showGrid[mouseX][mouseY] = 11;
				}
			}
		}

		//color of background
		app.clear(sf::Color::White);
		
		//draws text for HP
		app.draw(hpText);

		//add column to showGrid
		for (int col = 1; col <= 10; col++)
			//add row to showGrid
			for (int row = 1; row <= 10; row++)
			{
				//show tiles if bomb tile is pressed
				/*if (showGrid[mouseX][mouseY] == 9)
				{
					cout << "Bomb Detected, hp is " << hp << endl;
					if (event.key.code == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
					{
						hp = hp - 1;
						cout << "left mouse click on bomb detected, hp is now " << hp << endl;
					}
				}*/
					
				if (hp <= 0)
				{
					//cout << "failstate reached, hp is " << hp << endl;
					showGrid[col][row] = grid[col][row];
				}

				sprite.setTextureRect(sf::IntRect(showGrid[col][row] * imgSize, 0, imgSize, imgSize));
				sprite.setPosition(col * imgSize, row * imgSize);


			/*	movingSprite.setTextureRect(sf::IntRect(charTile[col][row] * imgSize, 0, imgSize, imgSize));
				movingSprite.setPosition(32*10,32);
				if (event.key.code == sf::Mouse::Left) {
					movingSprite.move(sf::Vector2f(-32.f, 0.f));
				}
				app.draw(movingSprite);*/

				app.draw(sprite);

			}

		app.display();
	}

	return 0;
}
