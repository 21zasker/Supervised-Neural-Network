# Supervised Neural Network
## Overview
My final project for the Supervised Neural Networks course. This C++ project implements a neural network using a multilayer perceptron (MLP). The MLP is designed to learn and predict RGB colors based on pixel coordinates (x, y) on a canvas.

## Features
- Interactive drawing interface using SFML graphics.
- Training the MLP based on user-drawn inputs.
- Real-time prediction of colors for canvas coordinates.
- Visual representation of drawn points and predicted colors.

## MLP Architecture
1. **Input Layer:**
   - Input neurons represent the pixel coordinates (x, y) of the drawn points on the canvas and a bias value of 1.
2. **Hidden Layer:**
   - Two hidden layers each with 3 neurons (bias, coordinates).
3. **Output Layer:**
   - Three outputs representing RGB colors (Red, Green, Blue).

<img src="https://github.com/21zasker/Supervised-Neural-Network/blob/main/Screenshots/neural-network.jpg" width="60%" alt="Neural-Network">

## Showcase
<img src="https://github.com/21zasker/Supervised-Neural-Network/blob/main/Screenshots/showcase.gif" width="60%" alt="Showcase">

## Note
The program is designed for demonstration purposes and may require further optimization for practical use cases.
