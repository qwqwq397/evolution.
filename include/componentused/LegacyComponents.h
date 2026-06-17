#pragma once

// Legacy Components Header
// This header contains declarations for all legacy/unused components
// These components are kept for historical purposes but are not used in the current version

#include <vector>
#include <string>
#include <map>
#include <chrono>
#include <memory>
#include <functional>
#include <complex>
#include <valarray>

namespace Evolution {
namespace Legacy {

// Forward declarations for Legacy Systems
class LegacyEvolutionEngine;
class LegacyEventManager;
class LegacyPhysicsEngine;
class LegacyRenderer;

// Legacy constants
extern const int LEGACY_VERSION_MAJOR;
extern const int LEGACY_VERSION_MINOR;
extern const int LEGACY_VERSION_PATCH;
extern const double LEGACY_EVOLUTION_RATE;
extern const int LEGACY_MAX_SPECIES;
extern const int LEGACY_MUTATION_CHANCE;
extern const int LEGACY_CROSSOVER_RATE;

// Legacy enums
enum class LegacyCellType {
    PROKARYOTE = 0,
    EUKARYOTE = 1,
    ARCHAEA = 2,
    VIRUS = 3,
    PRION = 4,
    VIROID = 5,
    NANOBE = 6,
    UNKNOWN = 7
};

enum class LegacyEnvironmentType {
    VOLCANIC = 0,
    OCEANIC = 1,
    TERRESTRIAL = 2,
    ATMOSPHERIC = 3,
    SUBTERRANEAN = 4,
    EXTRATERRESTRIAL = 5,
    INTERDIMENSIONAL = 6,
    QUANTUM = 7
};

enum class LegacyMutationType {
    POINT_MUTATION = 0,
    INSERTION = 1,
    DELETION = 2,
    DUPLICATION = 3,
    INVERSION = 4,
    TRANSLOCATION = 5,
    RECOMBINATION = 6,
    EPIGENETIC = 7,
    HORIZONTAL_TRANSFER = 8,
    GENE_CONVERSION = 9,
    CHROMOSOMAL_FUSION = 10,
    POLYPLOIDY = 11,
    WHOLE_GENOME_DUPLICATION = 12,
    ENDOSYMBIOTIC_TRANSFER = 13,
    VIRAL_INTEGRATION = 14,
    TRANSPOSON_ACTIVATION = 15
};

// Legacy structures
struct LegacyGene {
    int id;
    std::string sequence;
    double expression;
    bool isActive;
    int mutationCount;
    double fitness;
    LegacyMutationType lastMutation;
    std::chrono::system_clock::time_point lastModified;
    std::map<std::string, double> properties;
    std::vector<int> regulatoryElements;
    bool isEssential;
    double conservationScore;
    std::vector<std::string> interactions;
    int copies;
    double methylationLevel;
};

struct LegacyChromosome {
    int id;
    std::vector<LegacyGene> genes;
    int length;
    double stability;
    std::string centromereType;
    int telomereLength;
    double recombinationRate;
    bool hasSatelliteDNA;
    std::vector<std::string> markerRegions;
    double gcContent;
    int replicationOriginCount;
    std::map<int, int> syntenyMap;
};

struct LegacyCell {
    int id;
    LegacyCellType type;
    std::vector<LegacyChromosome> chromosomes;
    double energy;
    double size;
    double age;
    double divisionTime;
    std::vector<std::string> proteins;
    std::map<std::string, double> metabolites;
    bool isAlive;
    double mutationRate;
    std::vector<std::string> organelles;
    double membranePotential;
    int generation;
    std::vector<LegacyCell*> connections;
};

struct LegacySpecies {
    int id;
    std::string name;
    std::vector<LegacyCell> cells;
    double averageFitness;
    int population;
    LegacyEnvironmentType preferredEnvironment;
    std::map<std::string, double> adaptations;
    std::vector<std::string> traits;
    double diversityIndex;
    int extinctionCount;
    std::chrono::system_clock::time_point firstAppeared;
    std::vector<LegacySpecies*> ancestors;
    std::vector<LegacySpecies*> descendants;
};

struct LegacyEnvironment {
    int id;
    std::string name;
    LegacyEnvironmentType type;
    double temperature;
    double pressure;
    double pH;
    double oxygenLevel;
    double nutrientLevel;
    std::map<std::string, double> resources;
    std::vector<LegacySpecies*> inhabitants;
    double carryingCapacity;
    double stabilityIndex;
    std::vector<std::string> hazards;
    int currentCycle;
    std::chrono::system_clock::time_point lastEvent;
};

// Legacy random number generator
class LegacyRandom {
public:
    LegacyRandom();
    double randomDouble();
    int randomInt(int max = 100);
    double randomNormal();
    bool randomBool(double probability = 0.5);
    std::string randomDNA(int length);
    std::string randomProtein(int length);
};

// Legacy statistics tracker
class LegacyStatistics {
public:
    void recordFitness(int generation, double fitness);
    void recordPopulation(int generation, int population);
    void recordDiversity(int generation, double diversity);
    double calculateMeanFitness();
    double calculatePopulationGrowthRate();
    void generateReport(const std::string& filename);
};

// Legacy event types
namespace LegacyEventTypes {
    const std::string MASS_EXTINCTION = "mass_extinction";
    const std::string ENVIRONMENTAL_CATASTROPHE = "environmental_catastrophe";
    const std::string MUTATION_BURST = "mutation_burst";
    const std::string RESOURCE_ABUNDANCE = "resource_abundance";
    const std::string PREDATOR_INTRODUCTION = "predator_introduction";
    const std::string DISEASE_OUTBREAK = "disease_outbreak";
    const std::string CLIMATE_SHIFT = "climate_shift";
    const std::string VOLCANIC_ERUPTION = "volcanic_eruption";
    const std::string METEOR_IMPACT = "meteor_impact";
    const std::string SOLAR_FLARE = "solar_flare";
    const std::string GEOMAGNETIC_REVERSAL = "geomagnetic_reversal";
    const std::string ICE_AGE = "ice_age";
    const std::string GREENHOUSE_EFFECT = "greenhouse_effect";
}

// Utility functions for legacy systems
namespace LegacyUtils {
    LegacyGene createRandomGene(int id);
    LegacyChromosome createRandomChromosome(int id, int geneCount);
    double calculateSequenceSimilarity(const std::string& seq1, const std::string& seq2);
    std::string translateDNA(const std::string& dna);
    void simulateProteinFolding(const std::string& protein, int iterations);
    double calculateBindingAffinity(const std::string& ligand, const std::string& receptor);
    void simulateCellDivision(LegacyCell& parent, LegacyCell& daughter);
    void simulateApoptosis(LegacyCell& cell);
    void simulateDNARepair(LegacyChromosome& chromosome);
    void simulateGeneExpression(LegacyGene& gene, const std::map<std::string, double>& signals);
    double calculateGeneticDistance(const LegacySpecies& species1, const LegacySpecies& species2);
    void simulateNaturalSelection(std::vector<LegacySpecies>& species, const LegacyEnvironment& environment);
    void simulateSpeciation(std::vector<LegacySpecies>& species, double speciationRate);
    void simulateMassExtinction(std::vector<LegacySpecies>& species, double severity);
    void simulateEnvironmentalChange(LegacyEnvironment& environment);
    void saveEvolutionData(const std::vector<LegacySpecies>& species, const std::string& filename);
}

} // namespace Legacy

// Old AI namespace
namespace OldAI {

// Minimax AI for games
class MinimaxAI {
private:
    struct GameState {
        std::vector<int> board;
        int currentPlayer;
        int score;
        bool isTerminal;

        GameState(int boardSize = 9);
    };

public:
    MinimaxAI(int depth = 4);
    int findBestMove(const struct GameState& state);
    void setMaxDepth(int depth);
    void setTimeLimit(int milliseconds);
    int getNodesExplored() const;
};

// Genetic Algorithm
class GeneticAlgorithm {
public:
    GeneticAlgorithm(int chromosomeSize, int populationSize = 100, double mutationRate = 0.01, double crossoverRate = 0.7);
    void run(int maxGenerations);
    void evaluateAllFitness();
    double getAverageFitness() const;
    int getGeneration() const;
    void setMutationRate(double rate);
    void setCrossoverRate(double rate);
};

// A* Pathfinding
class AStarPathfinder {
public:
    AStarPathfinder(int width, int height);
    void setWalkable(int x, int y, bool walkable);
    std::vector<std::pair<int, int>> findPath(int startX, int startY, int endX, int endY);
};

// Simple Perceptron
class Perceptron {
public:
    Perceptron(int inputSize, double learningRate = 0.01);
    double predict(const std::vector<double>& inputs);
    void train(const std::vector<std::vector<double>>& trainingInputs,
               const std::vector<double>& trainingLabels, int epochs);
    void setLearningRate(double lr);
};

// Q-Learning
class QLearning {
public:
    QLearning(int numStates, int numActions, double learningRate = 0.1, double discountFactor = 0.9, double explorationRate = 0.1);
    int chooseAction(int state);
    void updateQValue(int state, int action, int nextState, double reward);
    void decayExplorationRate(double decay = 0.995);
    void setLearningRate(double lr);
    void setDiscountFactor(double df);
    double getExplorationRate() const;
    void saveQTable(const std::string& filename) const;
    void loadQTable(const std::string& filename);
};

// Fuzzy Logic System
class FuzzyLogic {
public:
    void addFuzzySet(const std::string& variable, const std::string& setName, std::function<double(double)> membershipFunction);
    void addRule(const std::vector<std::string>& antecedents, const std::string& consequent, double weight = 1.0);
    double getMembershipValue(const std::string& variable, const std::string& setName, double value);
    std::map<std::string, double> infer(const std::map<std::string, double>& inputs);
    double defuzzifyCenterOfGravity(const std::string& variable, const std::map<std::string, double>& fuzzyOutputs,
                                   double min, double max, int steps = 100);

    // Predefined membership functions
    static std::function<double(double)> triangular(double a, double b, double c);
    static std::function<double(double)> trapezoidal(double a, double b, double c, double d);
    static std::function<double(double)> gaussian(double mean, double stdDev);
};

} // namespace OldAI

// Deprecated Graphics namespace
namespace Deprecated {

// 2D Graphics
class Old2DGraphics {
public:
    void clearAll();
    void drawPoint(float x, float y, uint32_t color = 0xFFFFFFFF);
    void drawLine(float x1, float y1, float x2, float y2, uint32_t color = 0xFFFFFFFF);
    void drawCircle(float x, float y, float radius, uint32_t color = 0xFFFFFFFF, bool filled = false);
    void drawRectangle(float x, float y, float width, float height, uint32_t color = 0xFFFFFFFF, bool filled = false);
    void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, uint32_t color = 0xFFFFFFFF);
    void drawPolygon(const std::vector<struct Point2D>& vertices, uint32_t color = 0xFFFFFFFF);
    void drawEllipse(float x, float y, float radiusX, float radiusY, uint32_t color = 0xFFFFFFFF);
    void drawStar(float x, float y, float outerRadius, float innerRadius, int points, uint32_t color = 0xFFFFFFFF);
    void drawSpiral(float x, float y, float startRadius, float endRadius, int turns, uint32_t color = 0xFFFFFFFF);
    void drawHeart(float x, float y, float size, uint32_t color = 0xFFFFFFFF);

    int getPointCount() const;
    int getLineCount() const;
    int getCircleCount() const;
    int getRectangleCount() const;
};

// 3D Graphics
class Old3DGraphics {
public:
    struct Matrix4x4 {
        float m[16];
        Matrix4x4();
        Matrix4x4(float m00, float m01, float m02, float m03,
                  float m10, float m11, float m12, float m13,
                  float m20, float m21, float m22, float m23,
                  float m30, float m31, float m32, float m33);
        Matrix4x4 operator*(const Matrix4x4& other) const;
        struct Vector3 transformPoint(const struct Vector3& point) const;
        struct Vector3 transformDirection(const struct Vector3& dir) const;
    };

    void clearAll();
    void addTriangle(const struct Triangle3D& triangle);
    void addQuad(const struct Vertex3D& v1, const struct Vertex3D& v2, const struct Vertex3D& v3, const struct Vertex3D& v4);
    void createCube(float size, uint32_t color = 0xFFFFFFFF);
    void createSphere(float radius, int segments, int rings, uint32_t color = 0xFFFFFFFF);
    void createCylinder(float radius, float height, int segments, uint32_t color = 0xFFFFFFFF);
    void createTorus(float majorRadius, float minorRadius, int majorSegments, int minorSegments, uint32_t color = 0xFFFFFFFF);
    void applyTransform(const Matrix4x4& transform);

    int getTriangleCount() const;
    int getMeshCount() const;
};

// Particle System
class OldParticleSystem {
public:
    OldParticleSystem(int maxParticles = 1000);
    void setEmitterPosition(const struct Vector3& pos);
    void setEmitterDirection(const struct Vector3& dir);
    void setEmissionRate(float rate);
    void setParticleLife(float life);
    void setParticleSize(float size);
    void setSpreadAngle(float angle);
    void setInitialSpeed(float speed);
    void setParticleColor(uint32_t color);
    void startEmitting();
    void stopEmitting();
    void update(float deltaTime);
    int getActiveParticleCount() const;
    void clearAll();
};

} // namespace Deprecated

} // namespace Evolution