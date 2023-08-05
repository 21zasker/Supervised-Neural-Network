# Supervised-Neural-Network

My final project for the Supervised Neural Networks course. This project is an implementation of a multilayer neural network using the SFML library in C++. 
It's main purpose is to allow the user to draw points on a canvas and then train the neural network to predict the corresponding RGB colors 
based on the coordinates of these points. 
By visualizing this process graphically, the project demonstrates how a neural network can learn non-linear decision boundaries, enabling it to classify data 
that cannot be separated linearly in a feature space.

## User Interface

The program provides a graphical interface where users can draw on a canvas by clicking to add points with different colors. 
These points serve as training data for the neural network. 
The user has the option to assign a color (red, green, or blue) to each point based on their preferences.

Once enough training points have been added, the user can initiate the training process by clicking a button. 
During training, the neural network is utilized to predict the colors of the points on the canvas. 
These predicted colors are displayed on the canvas and updated in real-time as the neural network undergoes training.

<img src="https://github.com/21zasker/Supervised-Neural-Network/blob/main/Screenshots/Interface.jpg" width="70%" alt="User-Interface">

## The neural network

The system is a multilayer perceptron consisting of an input layer, two hidden layers, and an output layer. 
The input layer receives the 'x' and 'y' coordinates along with a constant bias value set to 1. 
Each hidden layer is composed of three neurons, and the output layer consists of three neurons representing the outputs of 
the red (R), green (G), and blue (B) color channels in the RGB model.

<img src="https://github.com/21zasker/Supervised-Neural-Network/blob/main/Screenshots/neural-network.jpg" width="70%" alt="Neural-Network">


Since there are three "labels" representing the corresponding colors, the following notation was used:
- {1, 0, 0} for red
- {0, 1, 0} for green
- {0, 0, 1} for blue

This notation aligns with the RGB model, allowing the color values to be obtained on the scale of 0 to 255 by simply multiplying each component by 255.

Example:

<img src="https://github.com/21zasker/Supervised-Neural-Network/blob/main/Screenshots/example-neural-network.jpg" width="70%" alt="Example-Neural-Network">

## Results

<img src="https://github.com/21zasker/Supervised-Neural-Network/blob/main/Screenshots/Results-1.jpg" width="60%" alt="Results-1">
<img src="https://github.com/21zasker/Supervised-Neural-Network/blob/main/Screenshots/Results-2.jpg" width="60%" alt="Results-2">
<img src="https://github.com/21zasker/Supervised-Neural-Network/blob/main/Screenshots/Results-3.jpg" width="60%" alt="Results-3">
