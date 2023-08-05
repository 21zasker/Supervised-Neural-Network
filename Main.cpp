#include <SFML/Graphics.hpp>
#include <iostream>
#include "MultilayerPerceptron.h"

int main()
{
	bool train = 0;
	std::vector<std::vector<float>> X; // Inputs: Pixel coordinates (x, y)
	std::vector<std::vector<float>> y; // Desired outputs: RGB colors

	int input_neurons = 3;	// 1 bias and 2 inputs (x, y) for coordinates
	int hidden_neurons = 2; // 2 hidden layers with 2 neurons each
	int output_neurons = 3; // 3 outputs (r, g, b) for RGB colors

	// ----------------- NEURAL NETWORK -------------------
	MultilayerPerceptron perceptron(input_neurons, hidden_neurons, output_neurons);

	// ------------------------- WINDOW -------------------------
	sf::RenderWindow window(sf::VideoMode(2 * 512, 512), "Final Project - Neural Networks", sf::Style::Close);

	// Mouse
	sf::CircleShape cursor(10);
	cursor.setFillColor(sf::Color::Transparent);
	cursor.setOrigin(cursor.getRadius(), cursor.getRadius());

	// Dot shapes
	sf::CircleShape dot_shape(5);
	dot_shape.setOrigin(dot_shape.getRadius(), dot_shape.getRadius());
	dot_shape.setOutlineColor(sf::Color(0, 0, 0));
	dot_shape.setOutlineThickness(1);

	// ----------------------- Canvas for inputs ---------------------
	sf::Image outputs_image;
	outputs_image.create(64, 64);

	sf::Texture outputs_texture;
	outputs_texture.loadFromImage(outputs_image);

	sf::Sprite outputs_sprite;
	outputs_sprite.setPosition(512, 0);
	outputs_sprite.setScale(512 / 64, 512 / 64);
	outputs_sprite.setTexture(outputs_texture);

	// ---------------------- User Interface ----------------------
	// Title
	sf::Font font;
	font.loadFromFile("Sources/PressStart2P.ttf");
	sf::Text title("Neural Networks", font, 24);
	title.setFillColor(sf::Color::Black);
	title.setPosition(20, 30);

	// Color wheel
	sf::Texture texture_wheel;
	texture_wheel.loadFromFile("Sources/color_wheel.png");
	sf::Sprite sprite_wheel(texture_wheel);
	sprite_wheel.setPosition(390, 50);
	sprite_wheel.setScale(0.1f, 0.1f);

	// Instructions
	sf::Text instr("Press the key:", font, 21);
	instr.setFillColor(sf::Color::Black);
	instr.setPosition(20, 130);

	sf::Texture texture_keys;
	texture_keys.loadFromFile("Sources/rgb_keys.png");
	sf::Sprite sprite_keys(texture_keys);
	sprite_keys.setPosition(20, 180);
	sprite_keys.setScale(0.8f, 0.8f);

	sf::Text instr1("for Red", font, 19);
	instr1.setFillColor(sf::Color::Red);
	instr1.setPosition(90, 205);

	sf::Text instr2("for Green", font, 19);
	instr2.setFillColor(sf::Color(0, 188, 0));
	instr2.setPosition(90, 265);

	sf::Text instr3("for Blue", font, 19);
	instr3.setFillColor(sf::Color::Blue);
	instr3.setPosition(90, 330);

	sf::Text start("> Start", font, 21);
	start.setFillColor(sf::Color::Black);
	start.setPosition(320, 430);

	// -------------------- MAIN PROGRAM ------------------
	while (1 == window.isOpen())
	{
		// ------------- EVENTS --------------
		sf::Event event;
		while (1 == window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
			{
				window.close();

				break;
			}
			// Change the cursor color based on the pressed key
			case sf::Event::KeyPressed:
			{
				switch (event.key.code)
				{
				case sf::Keyboard::R:
				{
					cursor.setFillColor(sf::Color::Red);
					break;
				}
				case sf::Keyboard::G:
				{
					cursor.setFillColor(sf::Color::Green);
					break;
				}
				case sf::Keyboard::B:
				{
					cursor.setFillColor(sf::Color::Blue);
					break;
				}
				}
			// Add inputs for 'X' and outputs for 'y' based on mouse coordinates and cursor color
			case sf::Event::MouseButtonPressed:
			{
				switch (event.mouseButton.button)
				{
				case sf::Mouse::Left:
				{
					// Mouse position
					sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

					// Canvas bounds (outputs_sprite)
					sf::FloatRect spriteBounds = outputs_sprite.getGlobalBounds();

					// Check if the 'click' is inside the canvas
					if (spriteBounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
					{
						float mouseX = (mousePosition.x - 1 * 512) / static_cast<float>(1 * 512);
						float mouseY = mousePosition.y / static_cast<float>(1 * 512);

						// 'X' contains a bias of 1 and the 'x', 'y' coordinates
						// 'y' contains the color values as output

						if (cursor.getFillColor() == sf::Color::Red)
						{
							X.push_back({1, mouseX, mouseY});
							y.push_back({1, 0, 0}); // Red
						}
						else if (cursor.getFillColor() == sf::Color::Green)
						{
							X.push_back({1, mouseX, mouseY});
							y.push_back({0, 1, 0}); // Green
						}
						else if (cursor.getFillColor() == sf::Color::Blue)
						{
							X.push_back({1, mouseX, mouseY});
							y.push_back({0, 0, 1}); // Blue
						}
					}
				}
				}
			}
			}
			}
			// -------------- LOOP EXECUTION ---------------

			// Cursor follows the mouse position
			sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
			cursor.setPosition(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

			// Event Handler to start the multilayer perceptron
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && start.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
			{
				train = true;
				cursor.setFillColor(sf::Color::Transparent);
			}

			// Start training the multilayer perceptron
			if (train)
			{
				for (int i = 0; i < 1024; i++)
				{
					// Randomly select an index from 'X'
					unsigned input_index = rand() % X.size();

					// Call the Forward and Back Propagation functions
					perceptron.forward_propagation(X[input_index]);
					perceptron.back_propagation(y[input_index]);
				}
			}

			// ------------------- SCREEN RENDERING -----------------

			window.clear(sf::Color::White);

			// Loop through the canvas and add coordinates to the neural network for testing
			for (unsigned short i = 0; i < 64; i++)
			{
				for (unsigned short j = 0; j < 64; j++)
				{
					float input_1 = i / static_cast<float>(64);
					float input_2 = j / static_cast<float>(64);

					// Save the output obtained from the neural network
					std::vector<float> output_color = perceptron.forward_propagation({1, input_1, input_2});

					// Update the canvas color with the obtained output (color)
					outputs_image.setPixel(i, j, sf::Color(round(255 * output_color[0]), round(255 * output_color[1]), round(255 * output_color[2])));
				}
			}

			outputs_texture.update(outputs_image);
			window.draw(outputs_sprite);

			window.draw(title);
			window.draw(sprite_wheel);
			window.draw(instr);
			window.draw(instr1);
			window.draw(instr2);
			window.draw(instr3);
			window.draw(start);
			window.draw(sprite_keys);
			window.draw(cursor);

			// Render dots on the canvas
			for (unsigned a = 0; a < X.size(); a++)
			{
				dot_shape.setFillColor(sf::Color(round(255 * y[a][0]), round(255 * y[a][1]), round(255 * y[a][2])));
				dot_shape.setPosition(512 * (1 + X[a][1]), 512 * X[a][2]);

				window.draw(dot_shape);
			}

			window.display();
		}
	}
	return 0;
}