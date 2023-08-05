#include "MultilayerPerceptron.h"

float MultilayerPerceptron::sigmoid_function(bool derivative, float z)
{
    float sig = 1 / (1 + exp(-z));

    // Return the sigmoid value or its derivative
    return derivative ? sig * (1 - sig) : sig;
}

std::vector<float> MultilayerPerceptron::forward_propagation(const std::vector<float> &input)
{
    // Add the inputs to the input layer (layer 0)
    mlp[0] = input;

    // For the rest of the layers
    for (int i = 0; i < weights.size(); i++)
    {
        for (int j = 0; j < weights[i].size(); j++)
        {
            mlp[i + 1][j] = 0;

            // Weighted sum calculation
            for (int k = 0; k < weights[i][j].size(); k++)
            {
                // Multiply the inputs by the corresponding weights
                mlp[i + 1][j] += mlp[i][k] * weights[i][j][k];
            }

            // Apply the activation function
            mlp[i + 1][j] = sigmoid_function(0, mlp[i + 1][j]);
        }
    }

    return mlp.back();
}

void MultilayerPerceptron::back_propagation(const std::vector<float> &outputs)
{
    // Backwards because Backpropagation
    for (int i = mlp.size() - 1; 0 < i; i--)
    {
        for (int j = 0; j < mlp[i].size(); j++)
        {
            // Calculate the error for the output layer
            if (i == mlp.size() - 1)
            {
                errors[i - 1][j] = pow(mlp[i][j] - outputs[j], 3);
            }
            else // Errors for hidden layers
            {
                errors[i - 1][j] = 0;
                for (int k = 0; k < mlp[i + 1].size(); k++)
                {
                    errors[i - 1][j] += errors[i][k] * weights[i][k][j];
                }
            }

            float z = 0;

            for (int k = 0; k < weights[i-1][j].size(); k++)
            {
                // Recalculate the weighted sum
                z += mlp[i - 1][k] * weights[i - 1][j][k];
            }

            for (int k = 0; k < mlp[i-1].size(); k++)
            {
                // Update weights using the derivative of the activation function
                weights[i - 1][j][k] -= learning_rate * errors[i - 1][j] * mlp[i - 1][k] * sigmoid_function(1, z);
            }
        }
    }
}