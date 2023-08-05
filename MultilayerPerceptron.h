#include <vector>
#include <random>
#include <cmath>

class MultilayerPerceptron
{
public:
    MultilayerPerceptron(int input_neurons, int hidden_neurons, int output_neurons)
        : input_neurons(input_neurons), hidden_neurons(hidden_neurons), output_neurons(output_neurons)
    {
        // ----------------- MULTILAYER PERCEPTRON (MLP) -------------------
        // Resize the mlp vector to hold the layers: input, hidden, and output
        mlp.resize(2 + hidden_neurons);
        mlp[0].resize(input_neurons, 0);
        mlp.back().resize(output_neurons, 0);

        for (auto &layer : mlp)
        {
            if (&layer != &mlp[0] && &layer != &mlp.back())
            {
                layer.resize(hidden_neurons + 1, 0); // Resize the hidden layers to include biases (hidden_neurons + 1)
            }
        }

        // Visual representation of the neural network structure: (Initialized with zeros)
        // 0 0 0 --> input layer (bias, x, y)
        // 0 0 0 --> hidden layer
        // 0 0 0 --> hidden layer
        // 0 0 0 --> output layer (r, g, b)

        // ------------------------ WEIGHTS -----------------------
        // Resize the weights vector to hold the weight matrices between layers
        weights.resize(mlp.size() - 1);

        // Random device to initialize the weights randomly for each layer
        std::random_device rd;
        std::mt19937 random_engine(rd());
        std::uniform_real_distribution<float> value_distribution(-1, std::nextafter(1, 1 + 1));

        for (std::size_t i = 0; i < weights.size(); ++i)
        {
            const std::size_t size = mlp[i + 1].size();
            weights[i].resize(size);

            for (auto &neuron_weights : weights[i])
            {
                neuron_weights.resize(mlp[i].size());

                for (auto &weight : neuron_weights)
                {
                    weight = value_distribution(random_engine);
                }
            }
        }

        // --------------------- ERRORS ------------------------
        // Reserve memory for the errors vector based on the weight matrices
        errors.reserve(weights.size());
        for (const auto &layer : weights)
        {
            errors.emplace_back(layer.size(), 0);
        }
        // Visual representation of the errors matrix:
        // 0 0 0 --> error for the hidden layer
        // 0 0 0 --> error for the hidden layer
        // 0 0 0 --> error for the output layer
    }

    // Forward propagation function
    std::vector<float> forward_propagation(const std::vector<float> &input);

    // Backpropagation function
    void back_propagation(const std::vector<float> &outputs);

private:

    const float learning_rate = 0.1;
    std::vector<std::vector<float>> mlp;
    std::vector<std::vector<std::vector<float>>> weights;
    std::vector<std::vector<float>> errors;

    int input_neurons;
    int hidden_neurons;
    int output_neurons;

    // Sigmoid activation function
    float sigmoid_function(bool derivative, float z);
};