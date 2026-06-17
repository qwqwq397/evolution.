// Legacy Systems - These are no longer used in the current version
// Preserved for historical reference and potential future use

#include "../include/ui/Window.h"
#include <windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>
#include <cmath>
#include <ctime>
#include <map>

namespace Evolution {
namespace Legacy {

// Unused constants
const int LEGACY_VERSION_MAJOR = 1;
const int LEGACY_VERSION_MINOR = 0;
const int LEGACY_VERSION_PATCH = 0;
const double LEGACY_EVOLUTION_RATE = 0.42;
const int LEGACY_MAX_SPECIES = 256;
const int LEGACY_MUTATION_CHANCE = 1000;
const int LEGACY_CROSSOVER_RATE = 7000;
const int LEGACY_SELECTION_PRESSURE = 5;
const int LEGACY_ENVIRONMENTAL_STABILITY = 7500;
const int LEGACY_RESOURCE_ABUNDANCE = 6000;
const double LEGACY_TEMPERATURE_RANGE = 45.5;
const double LEGACY_PRESSURE_RANGE = 2.8;
const double LEGACY_PH_RANGE = 8.3;

// Unused enums
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

// Unused structures
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

// Unused classes
class LegacyRandom {
private:
    std::mt19937 generator;
    std::uniform_real_distribution<double> realDist;
    std::uniform_int_distribution<int> intDist;
    std::normal_distribution<double> normalDist;

public:
    LegacyRandom() : generator(std::random_device{}()), realDist(0.0, 1.0), intDist(0, 100), normalDist(0.0, 1.0) {}

    double randomDouble() { return realDist(generator); }
    int randomInt(int max = 100) { return intDist(generator) % max; }
    double randomNormal() { return normalDist(generator); }
    bool randomBool(double probability = 0.5) { return randomDouble() < probability; }

    std::string randomDNA(int length) {
        static const char bases[] = "ATCG";
        std::string result;
        for(int i = 0; i < length; ++i) {
            result += bases[randomInt(4)];
        }
        return result;
    }

    std::string randomProtein(int length) {
        static const char aminoAcids[] = "ACDEFGHIKLMNPQRSTVWY";
        std::string result;
        for(int i = 0; i < length; ++i) {
            result += aminoAcids[randomInt(20)];
        }
        return result;
    }
};

class LegacyStatistics {
private:
    std::map<int, double> fitnessHistory;
    std::map<int, int> populationHistory;
    std::map<int, double> diversityHistory;
    std::vector<double> mutationRates;

public:
    void recordFitness(int generation, double fitness) {
        fitnessHistory[generation] = fitness;
    }

    void recordPopulation(int generation, int population) {
        populationHistory[generation] = population;
    }

    void recordDiversity(int generation, double diversity) {
        diversityHistory[generation] = diversity;
    }

    double calculateMeanFitness() {
        double sum = 0;
        for(const auto& pair : fitnessHistory) {
            sum += pair.second;
        }
        return fitnessHistory.empty() ? 0 : sum / fitnessHistory.size();
    }

    double calculatePopulationGrowthRate() {
        if(populationHistory.size() < 2) return 0;
        auto it = populationHistory.rbegin();
        int current = it->second;
        ++it;
        int previous = it->second;
        return previous == 0 ? 0 : ((double)(current - previous) / previous) * 100;
    }

    void generateReport(const std::string& filename) {
        std::ofstream file(filename);
        file << "Legacy Statistics Report\n";
        file << "========================\n\n";
        file << "Mean Fitness: " << calculateMeanFitness() << "\n";
        file << "Population Growth Rate: " << calculatePopulationGrowthRate() << "%\n";
        file << "Total Generations: " << fitnessHistory.size() << "\n";
        file << "Total Species: " << diversityHistory.size() << "\n";
        file.close();
    }
};

class LegacyEvolutionEngine {
private:
    LegacyRandom random;
    LegacyStatistics statistics;
    std::vector<LegacySpecies> species;
    std::vector<LegacyEnvironment> environments;
    int currentGeneration;
    double globalMutationRate;
    bool isPaused;
    std::mutex evolutionMutex;

public:
    LegacyEvolutionEngine() : currentGeneration(0), globalMutationRate(0.01), isPaused(false) {}

    void initialize() {
        // Initialize with dummy species
        for(int i = 0; i < 10; ++i) {
            LegacySpecies s;
            s.id = i;
            s.name = "LegacySpecies_" + std::to_string(i);
            s.averageFitness = random.randomDouble();
            s.population = random.randomInt(1000);
            s.diversityIndex = random.randomDouble();
            species.push_back(s);
        }
    }

    void evolveGeneration() {
        std::lock_guard<std::mutex> lock(evolutionMutex);
        if(isPaused) return;

        for(auto& s : species) {
            if(random.randomBool(globalMutationRate)) {
                mutateSpecies(s);
            }
        }

        for(auto& s : species) {
            s.averageFitness = calculateFitness(s);
            s.population = calculatePopulation(s);
        }

        statistics.recordPopulation(currentGeneration, getTotalPopulation());
        statistics.recordFitness(currentGeneration, getAverageFitness());
        statistics.recordDiversity(currentGeneration, calculateDiversity());

        currentGeneration++;
    }

    void mutateSpecies(LegacySpecies& species) {
        // Dummy mutation logic
        species.averageFitness *= (0.9 + random.randomDouble() * 0.2);
        species.diversityIndex *= (0.95 + random.randomDouble() * 0.1);

        for(auto& trait : species.traits) {
            if(random.randomBool(0.1)) {
                // Mutate trait
            }
        }
    }

    double calculateFitness(const LegacySpecies& species) {
        return species.averageFitness * (1 + species.diversityIndex * 0.1);
    }

    int calculatePopulation(const LegacySpecies& species) {
        return (int)(species.population * species.averageFitness);
    }

    int getTotalPopulation() {
        int total = 0;
        for(const auto& s : species) {
            total += s.population;
        }
        return total;
    }

    double getAverageFitness() {
        double sum = 0;
        for(const auto& s : species) {
            sum += s.averageFitness;
        }
        return species.empty() ? 0 : sum / species.size();
    }

    double calculateDiversity() {
        double shannonIndex = 0;
        int total = getTotalPopulation();

        for(const auto& s : species) {
            if(s.population > 0) {
                double p = (double)s.population / total;
                shannonIndex -= p * log(p);
            }
        }

        return shannonIndex;
    }

    void pause() { isPaused = true; }
    void resume() { isPaused = false; }
    int getCurrentGeneration() const { return currentGeneration; }
};

// Unused functions
namespace LegacyUtils {

    LegacyGene createRandomGene(int id) {
        LegacyRandom random;
        LegacyGene gene;
        gene.id = id;
        gene.sequence = random.randomDNA(100 + random.randomInt(900));
        gene.expression = random.randomDouble();
        gene.isActive = random.randomBool(0.7);
        gene.mutationCount = 0;
        gene.fitness = random.randomDouble();
        gene.lastMutation = LegacyMutationType::POINT_MUTATION;
        gene.lastModified = std::chrono::system_clock::now();
        gene.isEssential = random.randomBool(0.1);
        gene.conservationScore = random.randomDouble();
        gene.copies = 1;
        gene.methylationLevel = random.randomDouble() * 100;

        // Add random properties
        for(int i = 0; i < random.randomInt(5); ++i) {
            gene.properties["property_" + std::to_string(i)] = random.randomDouble();
        }

        return gene;
    }

    LegacyChromosome createRandomChromosome(int id, int geneCount) {
        LegacyChromosome chromosome;
        chromosome.id = id;
        chromosome.length = geneCount * 1000;
        chromosome.stability = 0.5 + (rand() % 50) / 100.0;
        chromosome.centromereType = "metacentric";
        chromosome.telomereLength = 5000 + rand() % 10000;
        chromosome.recombinationRate = rand() % 100 / 100.0;
        chromosome.hasSatelliteDNA = rand() % 2;
        chromosome.gcContent = 30 + rand() % 40;
        chromosome.replicationOriginCount = 1 + rand() % 5;

        for(int i = 0; i < geneCount; ++i) {
            chromosome.genes.push_back(createRandomGene(i));
        }

        return chromosome;
    }

    double calculateSequenceSimilarity(const std::string& seq1, const std::string& seq2) {
        if(seq1.length() != seq2.length()) return 0;

        int matches = 0;
        for(size_t i = 0; i < seq1.length(); ++i) {
            if(seq1[i] == seq2[i]) matches++;
        }

        return (double)matches / seq1.length();
    }

    std::string translateDNA(const std::string& dna) {
        static std::map<std::string, char> codonTable = {
            {"TTT", 'F'}, {"TTC", 'F'}, {"TTA", 'L'}, {"TTG", 'L'},
            {"CTT", 'L'}, {"CTC", 'L'}, {"CTA", 'L'}, {"CTG", 'L'},
            {"ATT", 'I'}, {"ATC", 'I'}, {"ATA", 'I'}, {"ATG", 'M'},
            {"GTT", 'V'}, {"GTC", 'V'}, {"GTA", 'V'}, {"GTG", 'V'},
            // ... more codons would be added in a real implementation
        };

        std::string protein;
        for(size_t i = 0; i < dna.length() - 2; i += 3) {
            std::string codon = dna.substr(i, 3);
            auto it = codonTable.find(codon);
            protein += (it != codonTable.end()) ? it->second : 'X';
        }

        return protein;
    }

    void simulateProteinFolding(const std::string& protein, int iterations) {
        // Dummy protein folding simulation
        double energy = 1000.0;
        for(int i = 0; i < iterations; ++i) {
            energy *= 0.999;  // Gradually decrease energy
            // In a real implementation, this would involve complex physics calculations
        }
    }

    double calculateBindingAffinity(const std::string& ligand, const std::string& receptor) {
        // Simplified binding affinity calculation
        double affinity = 0;
        int minLen = std::min(ligand.length(), receptor.length());

        for(int i = 0; i < minLen; ++i) {
            if(ligand[i] == receptor[i]) {
                affinity += 1.0;
            }
        }

        return affinity / minLen;
    }

    void simulateCellDivision(LegacyCell& parent, LegacyCell& daughter) {
        // Dummy cell division simulation
        daughter.id = parent.id * 2;
        daughter.type = parent.type;
        daughter.energy = parent.energy / 2;
        daughter.size = parent.size * 0.9;
        daughter.age = 0;
        daughter.generation = parent.generation + 1;
        daughter.mutationRate = parent.mutationRate;
        daughter.isAlive = true;

        // Copy and potentially mutate chromosomes
        for(const auto& chromosome : parent.chromosomes) {
            LegacyChromosome newChromosome = chromosome;
            if(rand() % 100 < 5) {  // 5% mutation chance
                // Mutate some genes
                for(auto& gene : newChromosome.genes) {
                    if(rand() % 1000 < 1) {  // 0.1% per gene
                        gene.mutationCount++;
                        gene.lastModified = std::chrono::system_clock::now();
                    }
                }
            }
            daughter.chromosomes.push_back(newChromosome);
        }
    }

    void simulateApoptosis(LegacyCell& cell) {
        // Simulate programmed cell death
        cell.isAlive = false;
        cell.energy = 0;
        cell.membranePotential = 0;

        // Release apoptotic signals
        for(size_t i = 0; i < cell.connections.size(); ++i) {
            if(cell.connections[i] && cell.connections[i]->isAlive) {
                // Signal neighboring cells
            }
        }
    }

    void simulateDNARepair(LegacyChromosome& chromosome) {
        // Simplified DNA repair simulation
        int repairEfficiency = 70 + rand() % 30;

        for(auto& gene : chromosome.genes) {
            if(gene.mutationCount > 0 && rand() % 100 < repairEfficiency) {
                // Repair mutation
                gene.mutationCount = std::max(0, gene.mutationCount - 1);
                gene.fitness = std::min(1.0, gene.fitness + 0.01);
            }
        }
    }

    void simulateGeneExpression(LegacyGene& gene, const std::map<std::string, double>& signals) {
        // Simplified gene expression model
        double expressionLevel = gene.expression;

        // Check regulatory elements
        for(int element : gene.regulatoryElements) {
            auto it = signals.find("signal_" + std::to_string(element));
            if(it != signals.end()) {
                expressionLevel *= it->second;
            }
        }

        gene.expression = std::max(0.0, std::min(1.0, expressionLevel));
        gene.isActive = gene.expression > 0.1;
    }

    double calculateGeneticDistance(const LegacySpecies& species1, const LegacySpecies& species2) {
        // Simplified genetic distance calculation
        double distance = 0;

        // Compare traits
        std::set<std::string> traits1(species1.traits.begin(), species1.traits.end());
        std::set<std::string> traits2(species2.traits.begin(), species2.traits.end());

        std::set<std::string> unionTraits;
        std::set_union(traits1.begin(), traits1.end(),
                      traits2.begin(), traits2.end(),
                      std::inserter(unionTraits, unionTraits.begin()));

        std::set<std::string> intersectionTraits;
        std::set_intersection(traits1.begin(), traits1.end(),
                             traits2.begin(), traits2.end(),
                             std::inserter(intersectionTraits, intersectionTraits.begin()));

        distance = 1.0 - (double)intersectionTraits.size() / unionTraits.size();

        return distance;
    }

    void simulateNaturalSelection(std::vector<LegacySpecies>& species, const LegacyEnvironment& environment) {
        // Calculate fitness for each species
        std::vector<std::pair<double, int>> fitnessScores;

        for(size_t i = 0; i < species.size(); ++i) {
            double fitness = species[i].averageFitness;

            // Environmental adaptation bonus
            if(species[i].preferredEnvironment == environment.type) {
                fitness *= 1.2;
            }

            fitnessScores.push_back({fitness, i});
        }

        // Sort by fitness
        std::sort(fitnessScores.rbegin(), fitnessScores.rend());

        // Eliminate least fit species (bottom 20%)
        int eliminateCount = species.size() / 5;
        for(int i = species.size() - 1; i >= species.size() - eliminateCount; --i) {
            species[fitnessScores[i].second].population = 0;
        }
    }

    void simulateSpeciation(std::vector<LegacySpecies>& species, double speciationRate) {
        std::vector<LegacySpecies> newSpecies;

        for(const auto& s : species) {
            if(s.population > 100 && rand() % 10000 < speciationRate * 10000) {
                // Create new species through speciation
                LegacySpecies newSpec = s;
                newSpec.id = species.size() + newSpecies.size();
                newSpec.name = s.name + "_subspecies";
                newSpec.averageFitness *= (0.9 + (rand() % 20) / 100.0);
                newSpec.population = s.population / 10;
                newSpec.diversityIndex *= 0.5;

                // Add some trait variations
                for(auto& trait : newSpec.traits) {
                    if(rand() % 10 == 0) {
                        trait += "_modified";
                    }
                }

                newSpecies.push_back(newSpec);
            }
        }

        species.insert(species.end(), newSpecies.begin(), newSpecies.end());
    }

    void simulateMassExtinction(std::vector<LegacySpecies>& species, double severity) {
        // Simulate a mass extinction event
        for(auto& s : species) {
            if(rand() % 100 < severity * 100) {
                // Species goes extinct
                s.population = 0;
            } else {
                // Surviving species lose population
                s.population = (int)(s.population * (1 - severity * 0.5));
            }
        }

        // Remove extinct species
        species.erase(
            std::remove_if(species.begin(), species.end(),
                          [](const LegacySpecies& s) { return s.population == 0; }),
            species.end()
        );
    }

    void simulateEnvironmentalChange(LegacyEnvironment& environment) {
        // Gradually change environment parameters
        environment.temperature += (rand() % 100 - 50) / 100.0;
        environment.pressure += (rand() % 20 - 10) / 100.0;
        environment.pH += (rand() % 20 - 10) / 100.0;
        environment.oxygenLevel += (rand() % 10 - 5) / 100.0;

        // Keep within reasonable bounds
        environment.temperature = std::max(-50.0, std::min(100.0, environment.temperature));
        environment.pressure = std::max(0.1, std::min(10.0, environment.pressure));
        environment.pH = std::max(0.0, std::min(14.0, environment.pH));
        environment.oxygenLevel = std::max(0.0, std::min(1.0, environment.oxygenLevel));
    }

    void saveEvolutionData(const std::vector<LegacySpecies>& species, const std::string& filename) {
        std::ofstream file(filename);
        file << "Legacy Evolution Data Export\n";
        file << "===========================\n\n";

        for(const auto& s : species) {
            file << "Species ID: " << s.id << "\n";
            file << "Name: " << s.name << "\n";
            file << "Population: " << s.population << "\n";
            file << "Average Fitness: " << s.averageFitness << "\n";
            file << "Diversity Index: " << s.diversityIndex << "\n";
            file << "Traits: ";
            for(const auto& trait : s.traits) {
                file << trait << " ";
            }
            file << "\n\n";
        }

        file.close();
    }
}

// Legacy event system (unused)
class LegacyEventManager {
private:
    struct LegacyEvent {
        int id;
        std::string type;
        std::string description;
        double probability;
        std::chrono::system_clock::time_point scheduledTime;
        std::map<std::string, double> parameters;
    };

    std::vector<LegacyEvent> scheduledEvents;
    std::vector<LegacyEvent> pastEvents;

public:
    void scheduleEvent(const std::string& type, const std::string& description, double probability) {
        LegacyEvent event;
        event.id = scheduledEvents.size() + pastEvents.size();
        event.type = type;
        event.description = description;
        event.probability = probability;
        event.scheduledTime = std::chrono::system_clock::now() + std::chrono::hours(1 + rand() % 24);

        scheduledEvents.push_back(event);
    }

    void processEvents() {
        auto now = std::chrono::system_clock::now();

        for(auto it = scheduledEvents.begin(); it != scheduledEvents.end();) {
            if(now >= it->scheduledTime) {
                if(rand() % 100 < it->probability * 100) {
                    // Event occurs
                    pastEvents.push_back(*it);
                    it = scheduledEvents.erase(it);
                } else {
                    // Event doesn't occur
                    it = scheduledEvents.erase(it);
                }
            } else {
                ++it;
            }
        }
    }

    void scheduleMassExtinction() {
        scheduleEvent("mass_extinction", "Cataclysmic event causes mass extinction", 0.01);
    }

    void scheduleEnvironmentalCatastrophe() {
        scheduleEvent("environmental_catastrophe", "Drastic environmental change", 0.05);
    }

    void scheduleMutationBurst() {
        scheduleEvent("mutation_burst", "Increased mutation rate across all species", 0.1);
    }

    void scheduleResourceAbundance() {
        scheduleEvent("resource_abundance", "Unprecedented resource availability", 0.08);
    }

    void schedulePredatorIntroduction() {
        scheduleEvent("predator_introduction", "New predator species appears", 0.12);
    }

    void scheduleDiseaseOutbreak() {
        scheduleEvent("disease_outbreak", "Deadly disease spreads through population", 0.07);
    }

    void scheduleClimateShift() {
        scheduleEvent("climate_shift", "Gradual climate change affects ecosystem", 0.15);
    }

    void scheduleVolcanicEruption() {
        scheduleEvent("volcanic_eruption", "Volcanic activity alters environment", 0.03);
    }

    void scheduleMeteorImpact() {
        scheduleEvent("meteor_impact", "Meteor strike causes devastation", 0.005);
    }

    void scheduleSolarFlare() {
        scheduleEvent("solar_flare", "Solar radiation increases mutation rates", 0.09);
    }

    void scheduleGeomagneticReversal() {
        scheduleEvent("geomagnetic_reversal", "Earth's magnetic field reverses", 0.002);
    }

    void scheduleIceAge() {
        scheduleEvent("ice_age", "Global cooling begins", 0.01);
    }

    void scheduleGreenhouseEffect() {
        scheduleEvent("greenhouse_effect", "Rapid global warming", 0.02);
    }
};

// Legacy physics simulation (unused)
class LegacyPhysicsEngine {
private:
    struct Vector3 {
        double x, y, z;
        Vector3(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}

        Vector3 operator+(const Vector3& other) const {
            return Vector3(x + other.x, y + other.y, z + other.z);
        }

        Vector3 operator-(const Vector3& other) const {
            return Vector3(x - other.x, y - other.y, z - other.z);
        }

        Vector3 operator*(double scalar) const {
            return Vector3(x * scalar, y * scalar, z * scalar);
        }

        double magnitude() const {
            return sqrt(x*x + y*y + z*z);
        }

        Vector3 normalize() const {
            double mag = magnitude();
            return mag > 0 ? *this * (1.0 / mag) : Vector3();
        }
    };

    struct Particle {
        Vector3 position;
        Vector3 velocity;
        Vector3 acceleration;
        double mass;
        double radius;
        Vector3 color;
        bool isActive;
    };

    std::vector<Particle> particles;
    Vector3 gravity;
    double timeStep;
    double damping;

public:
    LegacyPhysicsEngine() : gravity(0, -9.81, 0), timeStep(0.016), damping(0.999) {}

    void addParticle(const Vector3& position, const Vector3& velocity, double mass, double radius) {
        Particle p;
        p.position = position;
        p.velocity = velocity;
        p.acceleration = Vector3(0, 0, 0);
        p.mass = mass;
        p.radius = radius;
        p.color = Vector3(
            rand() % 100 / 100.0,
            rand() % 100 / 100.0,
            rand() % 100 / 100.0
        );
        p.isActive = true;
        particles.push_back(p);
    }

    void update() {
        for(auto& p : particles) {
            if(!p.isActive) continue;

            // Apply gravity
            p.acceleration = p.acceleration + gravity;

            // Update velocity
            p.velocity = p.velocity + p.acceleration * timeStep;

            // Apply damping
            p.velocity = p.velocity * damping;

            // Update position
            p.position = p.position + p.velocity * timeStep;

            // Reset acceleration for next frame
            p.acceleration = Vector3(0, 0, 0);
        }

        // Check collisions
        checkCollisions();
    }

    void checkCollisions() {
        for(size_t i = 0; i < particles.size(); ++i) {
            for(size_t j = i + 1; j < particles.size(); ++j) {
                if(!particles[i].isActive || !particles[j].isActive) continue;

                Vector3 diff = particles[i].position - particles[j].position;
                double distance = diff.magnitude();
                double minDistance = particles[i].radius + particles[j].radius;

                if(distance < minDistance) {
                    // Collision detected
                    Vector3 normal = diff.normalize();

                    // Separate particles
                    double overlap = minDistance - distance;
                    Vector3 separation = normal * (overlap / 2);
                    particles[i].position = particles[i].position + separation;
                    particles[j].position = particles[j].position - separation;

                    // Calculate relative velocity
                    Vector3 relativeVelocity = particles[i].velocity - particles[j].velocity;
                    double velocityAlongNormal = relativeVelocity.x * normal.x +
                                                 relativeVelocity.y * normal.y +
                                                 relativeVelocity.z * normal.z;

                    if(velocityAlongNormal > 0) continue;

                    // Calculate restitution
                    double restitution = 0.8;
                    double impulse = 2 * velocityAlongNormal /
                                    (1/particles[i].mass + 1/particles[j].mass);

                    // Apply impulse
                    Vector3 impulseVector = normal * impulse * restitution;
                    particles[i].velocity = particles[i].velocity - impulseVector * (1/particles[i].mass);
                    particles[j].velocity = particles[j].velocity + impulseVector * (1/particles[j].mass);
                }
            }
        }
    }

    void applyForce(int particleIndex, const Vector3& force) {
        if(particleIndex >= 0 && particleIndex < particles.size()) {
            particles[particleIndex].acceleration = particles[particleIndex].acceleration +
                                                    force * (1.0 / particles[particleIndex].mass);
        }
    }

    Vector3 getParticlePosition(int index) const {
        if(index >= 0 && index < particles.size()) {
            return particles[index].position;
        }
        return Vector3(0, 0, 0);
    }

    int getParticleCount() const {
        return particles.size();
    }

    void clearParticles() {
        particles.clear();
    }
};

// Legacy neural network (unused)
class LegacyNeuralNetwork {
private:
    struct Neuron {
        std::vector<double> weights;
        double bias;
        double output;
        double delta;

        Neuron(int inputCount) : bias(0), output(0), delta(0) {
            weights.resize(inputCount);
            for(auto& w : weights) {
                w = (rand() % 200 - 100) / 100.0;
            }
        }
    };

    std::vector<std::vector<Neuron>> layers;
    double learningRate;

public:
    LegacyNeuralNetwork(const std::vector<int>& layerSizes, double lr = 0.01) : learningRate(lr) {
        for(size_t i = 1; i < layerSizes.size(); ++i) {
            std::vector<Neuron> layer;
            for(int j = 0; j < layerSizes[i]; ++j) {
                layer.emplace_back(layerSizes[i-1]);
            }
            layers.push_back(layer);
        }
    }

    double sigmoid(double x) const {
        return 1.0 / (1.0 + exp(-x));
    }

    double sigmoidDerivative(double x) const {
        double s = sigmoid(x);
        return s * (1 - s);
    }

    std::vector<double> forward(const std::vector<double>& inputs) {
        std::vector<double> currentInputs = inputs;

        for(auto& layer : layers) {
            std::vector<double> outputs;
            for(auto& neuron : layer) {
                double sum = neuron.bias;
                for(size_t i = 0; i < currentInputs.size(); ++i) {
                    sum += neuron.weights[i] * currentInputs[i];
                }
                neuron.output = sigmoid(sum);
                outputs.push_back(neuron.output);
            }
            currentInputs = outputs;
        }

        return currentInputs;
    }

    void backward(const std::vector<double>& inputs, const std::vector<double>& targets) {
        // Forward pass to get outputs
        forward(inputs);

        // Calculate output layer deltas
        auto& outputLayer = layers.back();
        for(size_t i = 0; i < outputLayer.size(); ++i) {
            double error = targets[i] - outputLayer[i].output;
            outputLayer[i].delta = error * sigmoidDerivative(outputLayer[i].output);
        }

        // Calculate hidden layer deltas
        for(int l = layers.size() - 2; l >= 0; --l) {
            auto& currentLayer = layers[l];
            auto& nextLayer = layers[l + 1];

            for(size_t i = 0; i < currentLayer.size(); ++i) {
                double sum = 0;
                for(const auto& neuron : nextLayer) {
                    sum += neuron.weights[i] * neuron.delta;
                }
                currentLayer[i].delta = sum * sigmoidDerivative(currentLayer[i].output);
            }
        }

        // Update weights
        std::vector<double> prevOutputs = inputs;
        for(size_t l = 0; l < layers.size(); ++l) {
            auto& currentLayer = layers[l];

            for(size_t i = 0; i < currentLayer.size(); ++i) {
                auto& neuron = currentLayer[i];

                // Update weights
                for(size_t j = 0; j < neuron.weights.size(); ++j) {
                    neuron.weights[j] += learningRate * neuron.delta * prevOutputs[j];
                }

                // Update bias
                neuron.bias += learningRate * neuron.delta;
            }

            // Prepare outputs for next layer
            if(l < layers.size() - 1) {
                prevOutputs.clear();
                for(const auto& neuron : currentLayer) {
                    prevOutputs.push_back(neuron.output);
                }
            }
        }
    }

    void train(const std::vector<std::vector<double>>& trainingInputs,
               const std::vector<std::vector<double>>& trainingTargets,
               int epochs) {
        for(int epoch = 0; epoch < epochs; ++epoch) {
            for(size_t i = 0; i < trainingInputs.size(); ++i) {
                backward(trainingInputs[i], trainingTargets[i]);
            }
        }
    }

    void save(const std::string& filename) const {
        std::ofstream file(filename);

        for(const auto& layer : layers) {
            for(const auto& neuron : layer) {
                file << neuron.bias << " ";
                for(double weight : neuron.weights) {
                    file << weight << " ";
                }
                file << "\n";
            }
        }

        file.close();
    }
};

// Legacy rendering system (unused)
class LegacyRenderer {
private:
    struct Color {
        double r, g, b, a;
        Color(double r = 0, double g = 0, double b = 0, double a = 1)
            : r(r), g(g), b(b), a(a) {}

        uint32_t toRGBA() const {
            return ((uint32_t)(a * 255) << 24) |
                   ((uint32_t)(r * 255) << 16) |
                   ((uint32_t)(g * 255) << 8) |
                   ((uint32_t)(b * 255));
        }
    };

    struct Vertex {
        double x, y, z;
        Color color;
        double u, v;

        Vertex(double x = 0, double y = 0, double z = 0)
            : x(x), y(y), z(z), color(1, 1, 1, 1), u(0), v(0) {}
    };

    struct Triangle {
        Vertex vertices[3];
        Color color;

        Triangle(const Vertex& v1, const Vertex& v2, const Vertex& v3)
            : color(1, 1, 1, 1) {
            vertices[0] = v1;
            vertices[1] = v2;
            vertices[2] = v3;
        }
    };

    std::vector<Triangle> triangles;
    Color backgroundColor;
    double fov;
    double nearPlane;
    double farPlane;

public:
    LegacyRenderer() : backgroundColor(0.1, 0.1, 0.2, 1), fov(60), nearPlane(0.1), farPlane(1000) {}

    void clear() {
        triangles.clear();
    }

    void addTriangle(const Triangle& triangle) {
        triangles.push_back(triangle);
    }

    void addCube(const Vertex& center, double size, const Color& color) {
        double s = size / 2;

        Vertex vertices[8] = {
            Vertex(center.x - s, center.y - s, center.z - s),
            Vertex(center.x + s, center.y - s, center.z - s),
            Vertex(center.x + s, center.y + s, center.z - s),
            Vertex(center.x - s, center.y + s, center.z - s),
            Vertex(center.x - s, center.y - s, center.z + s),
            Vertex(center.x + s, center.y - s, center.z + s),
            Vertex(center.x + s, center.y + s, center.z + s),
            Vertex(center.x - s, center.y + s, center.z + s)
        };

        // Front face
        addTriangle(Triangle(vertices[0], vertices[1], vertices[2]));
        addTriangle(Triangle(vertices[0], vertices[2], vertices[3]));

        // Back face
        addTriangle(Triangle(vertices[5], vertices[4], vertices[7]));
        addTriangle(Triangle(vertices[5], vertices[7], vertices[6]));

        // Top face
        addTriangle(Triangle(vertices[3], vertices[2], vertices[6]));
        addTriangle(Triangle(vertices[3], vertices[6], vertices[7]));

        // Bottom face
        addTriangle(Triangle(vertices[4], vertices[5], vertices[1]));
        addTriangle(Triangle(vertices[4], vertices[1], vertices[0]));

        // Right face
        addTriangle(Triangle(vertices[1], vertices[5], vertices[6]));
        addTriangle(Triangle(vertices[1], vertices[6], vertices[2]));

        // Left face
        addTriangle(Triangle(vertices[4], vertices[0], vertices[3]));
        addTriangle(Triangle(vertices[4], vertices[3], vertices[7]));
    }

    void addSphere(const Vertex& center, double radius, int segments, const Color& color) {
        for(int i = 0; i < segments; ++i) {
            double phi1 = M_PI * i / segments;
            double phi2 = M_PI * (i + 1) / segments;

            for(int j = 0; j < segments; ++j) {
                double theta1 = 2 * M_PI * j / segments;
                double theta2 = 2 * M_PI * (j + 1) / segments;

                Vertex v1, v2, v3, v4;

                v1.x = center.x + radius * sin(phi1) * cos(theta1);
                v1.y = center.y + radius * cos(phi1);
                v1.z = center.z + radius * sin(phi1) * sin(theta1);

                v2.x = center.x + radius * sin(phi1) * cos(theta2);
                v2.y = center.y + radius * cos(phi1);
                v2.z = center.z + radius * sin(phi1) * sin(theta2);

                v3.x = center.x + radius * sin(phi2) * cos(theta2);
                v3.y = center.y + radius * cos(phi2);
                v3.z = center.z + radius * sin(phi2) * sin(theta2);

                v4.x = center.x + radius * sin(phi2) * cos(theta1);
                v4.y = center.y + radius * cos(phi2);
                v4.z = center.z + radius * sin(phi2) * sin(theta1);

                addTriangle(Triangle(v1, v2, v3));
                addTriangle(Triangle(v1, v3, v4));
            }
        }
    }

    void setBackgroundColor(const Color& color) {
        backgroundColor = color;
    }

    int getTriangleCount() const {
        return triangles.size();
    }

    void saveToObj(const std::string& filename) const {
        std::ofstream file(filename);

        file << "# Legacy Model Export\n";
        file << "# Vertices: " << triangles.size() * 3 << "\n";
        file << "# Triangles: " << triangles.size() << "\n\n";

        int vertexCount = 0;

        for(const auto& triangle : triangles) {
            for(const auto& vertex : triangle.vertices) {
                file << "v " << vertex.x << " " << vertex.y << " " << vertex.z << "\n";
            }

            file << "f " << (vertexCount + 1) << " "
                 << (vertexCount + 2) << " " << (vertexCount + 3) << "\n";

            vertexCount += 3;
        }

        file.close();
    }
};

} // namespace Legacy
} // namespace Evolution