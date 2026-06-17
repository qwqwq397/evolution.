// Old AI System - Obsolete implementation
// This file contains deprecated AI algorithms that are no longer used

#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <chrono>
#include <thread>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <functional>
#include <limits>

namespace Evolution {
namespace OldAI {

// Minimax algorithm with alpha-beta pruning (unused)
class MinimaxAI {
private:
    struct GameState {
        std::vector<int> board;
        int currentPlayer;
        int score;
        bool isTerminal;

        GameState(int boardSize = 9) : board(boardSize, 0), currentPlayer(1), score(0), isTerminal(false) {}
    };

    int maxDepth;
    int nodesExplored;
    std::chrono::milliseconds timeLimit;

public:
    MinimaxAI(int depth = 4) : maxDepth(depth), nodesExplored(0), timeLimit(5000) {}

    int evaluatePosition(const GameState& state) {
        // Simple evaluation function
        int score = 0;

        // Check rows
        for(int i = 0; i < 3; ++i) {
            int count = 0;
            for(int j = 0; j < 3; ++j) {
                if(state.board[i * 3 + j] == state.currentPlayer) count++;
                else if(state.board[i * 3 + j] != 0) count--;
            }
            score += count * count;
        }

        // Check columns
        for(int j = 0; j < 3; ++j) {
            int count = 0;
            for(int i = 0; i < 3; ++i) {
                if(state.board[i * 3 + j] == state.currentPlayer) count++;
                else if(state.board[i * 3 + j] != 0) count--;
            }
            score += count * count;
        }

        // Check diagonals
        int count1 = 0, count2 = 0;
        for(int i = 0; i < 3; ++i) {
            if(state.board[i * 3 + i] == state.currentPlayer) count1++;
            else if(state.board[i * 3 + i] != 0) count1--;

            if(state.board[i * 3 + (2 - i)] == state.currentPlayer) count2++;
            else if(state.board[i * 3 + (2 - i)] != 0) count2--;
        }
        score += count1 * count1 + count2 * count2;

        return score;
    }

    std::vector<int> getValidMoves(const GameState& state) {
        std::vector<int> moves;
        for(int i = 0; i < state.board.size(); ++i) {
            if(state.board[i] == 0) {
                moves.push_back(i);
            }
        }
        return moves;
    }

    GameState makeMove(const GameState& state, int move) {
        GameState newState = state;
        newState.board[move] = state.currentPlayer;
        newState.currentPlayer = -state.currentPlayer;

        // Check if terminal
        bool isFull = true;
        for(int cell : newState.board) {
            if(cell == 0) {
                isFull = false;
                break;
            }
        }
        newState.isTerminal = isFull || checkWin(newState);

        return newState;
    }

    bool checkWin(const GameState& state) {
        // Check rows
        for(int i = 0; i < 3; ++i) {
            if(state.board[i * 3] != 0 &&
               state.board[i * 3] == state.board[i * 3 + 1] &&
               state.board[i * 3 + 1] == state.board[i * 3 + 2]) {
                return true;
            }
        }

        // Check columns
        for(int j = 0; j < 3; ++j) {
            if(state.board[j] != 0 &&
               state.board[j] == state.board[j + 3] &&
               state.board[j + 3] == state.board[j + 6]) {
                return true;
            }
        }

        // Check diagonals
        if(state.board[0] != 0 &&
           state.board[0] == state.board[4] &&
           state.board[4] == state.board[8]) {
            return true;
        }

        if(state.board[2] != 0 &&
           state.board[2] == state.board[4] &&
           state.board[4] == state.board[6]) {
            return true;
        }

        return false;
    }

    int minimax(GameState state, int depth, int alpha, int beta, bool isMaximizing) {
        nodesExplored++;

        if(depth == 0 || state.isTerminal) {
            return evaluatePosition(state);
        }

        if(isMaximizing) {
            int maxEval = -999999;
            for(int move : getValidMoves(state)) {
                int eval = minimax(makeMove(state, move), depth - 1, alpha, beta, false);
                maxEval = std::max(maxEval, eval);
                alpha = std::max(alpha, eval);
                if(beta <= alpha) {
                    break; // Alpha-beta pruning
                }
            }
            return maxEval;
        } else {
            int minEval = 999999;
            for(int move : getValidMoves(state)) {
                int eval = minimax(makeMove(state, move), depth - 1, alpha, beta, true);
                minEval = std::min(minEval, eval);
                beta = std::min(beta, eval);
                if(beta <= alpha) {
                    break; // Alpha-beta pruning
                }
            }
            return minEval;
        }
    }

    int findBestMove(const GameState& state) {
        nodesExplored = 0;
        auto startTime = std::chrono::steady_clock::now();

        int bestMove = -1;
        int bestValue = -999999;

        for(int move : getValidMoves(state)) {
            int value = minimax(makeMove(state, move), maxDepth, -999999, 999999, false);

            auto currentTime = std::chrono::steady_clock::now();
            auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime);
            if(elapsedTime > timeLimit) {
                break;
            }

            if(value > bestValue) {
                bestValue = value;
                bestMove = move;
            }
        }

        return bestMove;
    }

    void setMaxDepth(int depth) { maxDepth = depth; }
    void setTimeLimit(int milliseconds) { timeLimit = std::chrono::milliseconds(milliseconds); }
    int getNodesExplored() const { return nodesExplored; }
};

// Genetic Algorithm (unused)
class GeneticAlgorithm {
private:
    struct Chromosome {
        std::vector<double> genes;
        double fitness;

        Chromosome(int size) : genes(size), fitness(0) {
            for(auto& gene : genes) {
                gene = (rand() % 200 - 100) / 100.0;
            }
        }
    };

    std::vector<Chromosome> population;
    int chromosomeSize;
    int populationSize;
    double mutationRate;
    double crossoverRate;
    int generation;

    std::mt19937 rng;

public:
    GeneticAlgorithm(int chromSize, int popSize = 100, double mutRate = 0.01, double crossRate = 0.7)
        : chromosomeSize(chromSize), populationSize(popSize), mutationRate(mutRate), crossoverRate(crossRate), generation(0) {
        rng.seed(std::random_device{}());
        initializePopulation();
    }

    void initializePopulation() {
        population.clear();
        for(int i = 0; i < populationSize; ++i) {
            population.emplace_back(chromosomeSize);
        }
    }

    double evaluateFitness(const Chromosome& chrom) {
        // Example fitness function - can be customized
        double sum = 0;
        for(double gene : chrom.genes) {
            sum += gene * gene;
        }
        return 1.0 / (1.0 + sum); // Lower values get higher fitness
    }

    void evaluateAllFitness() {
        for(auto& chrom : population) {
            chrom.fitness = evaluateFitness(chrom);
        }
    }

    Chromosome tournamentSelection(int tournamentSize = 3) {
        std::uniform_int_distribution<int> dist(0, populationSize - 1);

        Chromosome best = population[dist(rng)];

        for(int i = 1; i < tournamentSize; ++i) {
            Chromosome candidate = population[dist(rng)];
            if(candidate.fitness > best.fitness) {
                best = candidate;
            }
        }

        return best;
    }

    Chromosome crossover(const Chromosome& parent1, const Chromosome& parent2) {
        Chromosome child(chromosomeSize);

        if(rand() % 100 < crossoverRate * 100) {
            std::uniform_int_distribution<int> dist(1, chromosomeSize - 1);
            int crossoverPoint = dist(rng);

            for(int i = 0; i < crossoverPoint; ++i) {
                child.genes[i] = parent1.genes[i];
            }
            for(int i = crossoverPoint; i < chromosomeSize; ++i) {
                child.genes[i] = parent2.genes[i];
            }
        } else {
            child = parent1;
        }

        return child;
    }

    void mutate(Chromosome& chrom) {
        std::normal_distribution<double> dist(0, 0.1);

        for(auto& gene : chrom.genes) {
            if(rand() % 100 < mutationRate * 100) {
                gene += dist(rng);
                // Clamp values
                gene = std::max(-1.0, std::min(1.0, gene));
            }
        }
    }

    void evolveGeneration() {
        std::vector<Chromosome> newPopulation;

        // Elitism - keep best chromosome
        auto bestIt = std::max_element(population.begin(), population.end(),
            [](const Chromosome& a, const Chromosome& b) { return a.fitness < b.fitness; });
        newPopulation.push_back(*bestIt);

        while(newPopulation.size() < populationSize) {
            Chromosome parent1 = tournamentSelection();
            Chromosome parent2 = tournamentSelection();

            Chromosome child = crossover(parent1, parent2);
            mutate(child);

            newPopulation.push_back(child);
        }

        population = newPopulation;
        generation++;
    }

    void run(int maxGenerations) {
        for(int i = 0; i < maxGenerations; ++i) {
            evaluateAllFitness();
            evolveGeneration();
        }
    }

    Chromosome getBestChromosome() const {
        auto bestIt = std::max_element(population.begin(), population.end(),
            [](const Chromosome& a, const Chromosome& b) { return a.fitness < b.fitness; });
        return *bestIt;
    }

    double getAverageFitness() const {
        double sum = 0;
        for(const auto& chrom : population) {
            sum += chrom.fitness;
        }
        return sum / population.size();
    }

    int getGeneration() const { return generation; }
    void setMutationRate(double rate) { mutationRate = rate; }
    void setCrossoverRate(double rate) { crossoverRate = rate; }
};

// A* Pathfinding (unused)
class AStarPathfinder {
private:
    struct Node {
        int x, y;
        double g, h, f;
        Node* parent;
        bool isWalkable;

        Node(int x = 0, int y = 0) : x(x), y(y), g(0), h(0), f(0), parent(nullptr), isWalkable(true) {}

        bool operator<(const Node& other) const {
            return f > other.f; // Reverse for priority queue (min-heap)
        }
    };

    struct NodeHash {
        size_t operator()(const Node* node) const {
            return std::hash<int>()(node->x) ^ std::hash<int>()(node->y);
        }
    };

    struct NodeEqual {
        bool operator()(const Node* a, const Node* b) const {
            return a->x == b->x && a->y == b->y;
        }
    };

    std::vector<std::vector<Node>> grid;
    int width, height;

public:
    AStarPathfinder(int w, int h) : width(w), height(h) {
        grid.resize(height);
        for(int y = 0; y < height; ++y) {
            grid[y].resize(width);
            for(int x = 0; x < width; ++x) {
                grid[y][x] = Node(x, y);
            }
        }
    }

    void setWalkable(int x, int y, bool walkable) {
        if(x >= 0 && x < width && y >= 0 && y < height) {
            grid[y][x].isWalkable = walkable;
        }
    }

    double heuristic(int x1, int y1, int x2, int y2) {
        // Manhattan distance
        return abs(x1 - x2) + abs(y1 - y2);
    }

    std::vector<std::pair<int, int>> findPath(int startX, int startY, int endX, int endY) {
        std::priority_queue<Node> openList;
        std::unordered_set<Node*, NodeHash, NodeEqual> closedSet;
        std::unordered_map<Node*, Node*, NodeHash, NodeEqual> cameFrom;

        Node* start = &grid[startY][startX];
        Node* end = &grid[endY][endX];

        if(!start->isWalkable || !end->isWalkable) {
            return {};
        }

        start->g = 0;
        start->h = heuristic(startX, startY, endX, endY);
        start->f = start->g + start->h;
        openList.push(*start);

        while(!openList.empty()) {
            Node current = openList.top();
            openList.pop();
            Node* currentPtr = &grid[current.y][current.x];

            if(currentPtr == end) {
                // Reconstruct path
                std::vector<std::pair<int, int>> path;
                Node* node = end;
                while(node != nullptr) {
                    path.emplace_back(node->x, node->y);
                    node = node->parent;
                }
                std::reverse(path.begin(), path.end());
                return path;
            }

            closedSet.insert(currentPtr);

            // Check neighbors
            int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

            for(auto& dir : directions) {
                int nx = current.x + dir[0];
                int ny = current.y + dir[1];

                if(nx < 0 || nx >= width || ny < 0 || ny >= height) {
                    continue;
                }

                Node* neighbor = &grid[ny][nx];

                if(!neighbor->isWalkable || closedSet.find(neighbor) != closedSet.end()) {
                    continue;
                }

                double tentativeG = current.g + 1;

                // For this unused code, we'll simplify by not checking for duplicates in openList
                neighbor->parent = currentPtr;
                neighbor->g = tentativeG;
                neighbor->h = heuristic(nx, ny, endX, endY);
                neighbor->f = neighbor->g + neighbor->h;

                // Always push to open list (simplified approach for unused code)
                openList.push(*neighbor);
            }
        }

        return {}; // No path found
    }
};

// Neural Network - Simple Perceptron (unused)
class Perceptron {
private:
    std::vector<double> weights;
    double bias;
    double learningRate;

public:
    Perceptron(int inputSize, double lr = 0.01) : bias(0), learningRate(lr) {
        weights.resize(inputSize);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(-1.0, 1.0);

        for(auto& w : weights) {
            w = dis(gen);
        }
    }

    double activation(double x) {
        return x >= 0 ? 1 : -1; // Step activation
    }

    double predict(const std::vector<double>& inputs) {
        if(inputs.size() != weights.size()) {
            throw std::invalid_argument("Input size mismatch");
        }

        double sum = bias;
        for(size_t i = 0; i < inputs.size(); ++i) {
            sum += weights[i] * inputs[i];
        }

        return activation(sum);
    }

    void train(const std::vector<std::vector<double>>& trainingInputs,
               const std::vector<double>& trainingLabels,
               int epochs) {
        if(trainingInputs.size() != trainingLabels.size()) {
            throw std::invalid_argument("Training data size mismatch");
        }

        for(int epoch = 0; epoch < epochs; ++epoch) {
            for(size_t i = 0; i < trainingInputs.size(); ++i) {
                double prediction = predict(trainingInputs[i]);
                double error = trainingLabels[i] - prediction;

                // Update weights
                for(size_t j = 0; j < weights.size(); ++j) {
                    weights[j] += learningRate * error * trainingInputs[i][j];
                }

                // Update bias
                bias += learningRate * error;
            }
        }
    }

    std::vector<double> getWeights() const { return weights; }
    double getBias() const { return bias; }
    void setLearningRate(double lr) { learningRate = lr; }
};

// Q-Learning Algorithm (unused)
class QLearning {
private:
    struct StateAction {
        int state;
        int action;

        bool operator==(const StateAction& other) const {
            return state == other.state && action == other.action;
        }
    };

    struct StateActionHash {
        size_t operator()(const StateAction& sa) const {
            return std::hash<int>()(sa.state) ^ (std::hash<int>()(sa.action) << 1);
        }
    };

    std::unordered_map<StateAction, double, StateActionHash> qTable;
    double learningRate;
    double discountFactor;
    double explorationRate;
    int numStates;
    int numActions;

    std::mt19937 rng;

public:
    QLearning(int states, int actions, double lr = 0.1, double df = 0.9, double er = 0.1)
        : learningRate(lr), discountFactor(df), explorationRate(er), numStates(states), numActions(actions) {
        rng.seed(std::random_device{}());
    }

    int chooseAction(int state) {
        std::uniform_real_distribution<> dist(0.0, 1.0);

        if(dist(rng) < explorationRate) {
            // Explore: choose random action
            std::uniform_int_distribution<> actionDist(0, numActions - 1);
            return actionDist(rng);
        } else {
            // Exploit: choose best action
            return getBestAction(state);
        }
    }

    int getBestAction(int state) {
        int bestAction = 0;
        double bestValue = -std::numeric_limits<double>::infinity();

        for(int action = 0; action < numActions; ++action) {
            StateAction sa{state, action};
            auto it = qTable.find(sa);
            double value = (it != qTable.end()) ? it->second : 0.0;

            if(value > bestValue) {
                bestValue = value;
                bestAction = action;
            }
        }

        return bestAction;
    }

    void updateQValue(int state, int action, int nextState, double reward) {
        StateAction currentSA{state, action};

        double currentQ = qTable[currentSA];
        double maxNextQ = 0;

        // Find maximum Q-value for next state
        for(int nextAction = 0; nextAction < numActions; ++nextAction) {
            StateAction nextSA{nextState, nextAction};
            auto it = qTable.find(nextSA);
            double value = (it != qTable.end()) ? it->second : 0.0;
            maxNextQ = std::max(maxNextQ, value);
        }

        // Q-learning update rule
        double newQ = currentQ + learningRate * (reward + discountFactor * maxNextQ - currentQ);
        qTable[currentSA] = newQ;
    }

    void decayExplorationRate(double decay = 0.995) {
        explorationRate = std::max(0.01, explorationRate * decay);
    }

    void setLearningRate(double lr) { learningRate = lr; }
    void setDiscountFactor(double df) { discountFactor = df; }
    double getExplorationRate() const { return explorationRate; }

    void saveQTable(const std::string& filename) const {
        std::ofstream file(filename);
        for(const auto& pair : qTable) {
            file << pair.first.state << " " << pair.first.action << " " << pair.second << "\n";
        }
        file.close();
    }

    void loadQTable(const std::string& filename) {
        std::ifstream file(filename);
        int state, action;
        double value;

        while(file >> state >> action >> value) {
            StateAction sa{state, action};
            qTable[sa] = value;
        }

        file.close();
    }
};

// Fuzzy Logic System (unused)
class FuzzyLogic {
private:
    struct FuzzySet {
        std::string name;
        std::function<double(double)> membershipFunction;

        FuzzySet(const std::string& n, std::function<double(double)> mf)
            : name(n), membershipFunction(mf) {}
    };

    struct FuzzyRule {
        std::vector<std::string> antecedents;
        std::string consequent;
        double weight;

        FuzzyRule(const std::vector<std::string>& ant, const std::string& cons, double w = 1.0)
            : antecedents(ant), consequent(cons), weight(w) {}
    };

    std::map<std::string, std::vector<FuzzySet>> variables;
    std::vector<FuzzyRule> rules;

public:
    void addFuzzySet(const std::string& variable, const std::string& setName,
                     std::function<double(double)> membershipFunction) {
        variables[variable].emplace_back(setName, membershipFunction);
    }

    void addRule(const std::vector<std::string>& antecedents, const std::string& consequent, double weight = 1.0) {
        rules.emplace_back(antecedents, consequent, weight);
    }

    double getMembershipValue(const std::string& variable, const std::string& setName, double value) {
        auto it = variables.find(variable);
        if(it != variables.end()) {
            for(const auto& set : it->second) {
                if(set.name == setName) {
                    return set.membershipFunction(value);
                }
            }
        }
        return 0.0;
    }

    // Example membership functions
    static std::function<double(double)> triangular(double a, double b, double c) {
        return [a, b, c](double x) {
            if(x <= a || x >= c) return 0.0;
            if(x == b) return 1.0;
            if(x < b) return (x - a) / (b - a);
            return (c - x) / (c - b);
        };
    }

    static std::function<double(double)> trapezoidal(double a, double b, double c, double d) {
        return [a, b, c, d](double x) {
            if(x <= a || x >= d) return 0.0;
            if(x >= b && x <= c) return 1.0;
            if(x < b) return (x - a) / (b - a);
            return (d - x) / (d - c);
        };
    }

    static std::function<double(double)> gaussian(double mean, double stdDev) {
        return [mean, stdDev](double x) {
            return exp(-0.5 * pow((x - mean) / stdDev, 2));
        };
    }

    double evaluateRule(const FuzzyRule& rule, const std::map<std::string, double>& inputs) {
        double minMembership = 1.0;

        for(const auto& antecedent : rule.antecedents) {
            // Parse antecedent (e.g., "temperature:hot")
            size_t colon = antecedent.find(':');
            if(colon != std::string::npos) {
                std::string variable = antecedent.substr(0, colon);
                std::string setName = antecedent.substr(colon + 1);

                auto inputIt = inputs.find(variable);
                if(inputIt != inputs.end()) {
                    double membership = getMembershipValue(variable, setName, inputIt->second);
                    minMembership = std::min(minMembership, membership);
                } else {
                    minMembership = 0.0;
                    break;
                }
            }
        }

        return minMembership * rule.weight;
    }

    std::map<std::string, double> infer(const std::map<std::string, double>& inputs) {
        std::map<std::string, double> outputs;

        for(const auto& rule : rules) {
            double strength = evaluateRule(rule, inputs);

            // Accumulate strength for each consequent
            auto it = outputs.find(rule.consequent);
            if(it != outputs.end()) {
                it->second = std::max(it->second, strength);
            } else {
                outputs[rule.consequent] = strength;
            }
        }

        return outputs;
    }

    double defuzzifyCenterOfGravity(const std::string& variable, const std::map<std::string, double>& fuzzyOutputs,
                                    double min, double max, int steps = 100) {
        double sum = 0;
        double weightedSum = 0;
        double stepSize = (max - min) / steps;

        for(int i = 0; i <= steps; ++i) {
            double x = min + i * stepSize;
            double membership = 0;

            // Calculate membership at point x
            auto it = variables.find(variable);
            if(it != variables.end()) {
                for(const auto& set : it->second) {
                    auto fuzzyIt = fuzzyOutputs.find(set.name);
                    if(fuzzyIt != fuzzyOutputs.end()) {
                        membership = std::max(membership,
                                            std::min(set.membershipFunction(x), fuzzyIt->second));
                    }
                }
            }

            sum += membership;
            weightedSum += x * membership;
        }

        return sum > 0 ? weightedSum / sum : (min + max) / 2;
    }
};

} // namespace OldAI
} // namespace Evolution