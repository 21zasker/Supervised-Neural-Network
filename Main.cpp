#include <SFML/Graphics.hpp>
#include <iostream>
#include "MultilayerPerceptron.h"
#include "Canvas.h"

int main()
{
	bool train = 0;
	std::vector<std::vector<float>> X; // Inputs: Pixel coordinates (x, y)
	std::vector<std::vector<float>> y; // Desired outputs: RGB colors

	int input_neurons = 3;	// 1 bias and 2 inputs (x, y) for coordinates
	int hidden_neurons = 2; // 2 hidden layers with 2 neurons each
	int output_neurons = 3; // 3 outputs (r, g, b) for RGB colors

	// Neural network
	MultilayerPerceptron perceptron(input_neurons, hidden_neurons, output_neurons);

	// Window
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

	// Canvas and UI
	Canvas canvas;

	while (1 == window.isOpen())
	{
		// Events
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
				case Keyboard::R:
					cursor.setFillColor(Color::Red);
					break;
				case Keyboard::G:
					cursor.setFillColor(Color::Green);
					break;
				case Keyboard::B:
					cursor.setFillColor(Color::Blue);
					break;
				}
			// Add inputs for 'X' and outputs for 'y' based on mouse coordinates and cursor color
			case sf::Event::MouseButtonPressed:
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					// Mouse position
					sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

					// Canvas bounds (outputs_sprite)
					sf::FloatRect spriteBounds = canvas.outputs_sprite.getGlobalBounds();

					// Start button bounds
					sf::FloatRect startBounds = canvas.start_text.getGlobalBounds();

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

					// Check if the 'click' is on the start button
					if (startBounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
					{
						train = true; // Start the perceptron
						cursor.setFillColor(sf::Color::Transparent);
					}
				}
			}
			}
			}

			// Cursor follows the mouse position
			cursor.setPosition(static_cast<float>(sf::Mouse::getPosition(window).x), static_cast<float>(sf::Mouse::getPosition(window).y));

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

			// Window render
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
					canvas.outputs_image.setPixel(i, j, sf::Color(round(255 * output_color[0]), round(255 * output_color[1]), round(255 * output_color[2])));
				}
			}

			canvas.outputs_texture.update(canvas.outputs_image);
			canvas.drawCanvas(window);
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
