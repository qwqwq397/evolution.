// Utility Functions - Various helper functions that are no longer used
// This file contains deprecated utility functions kept for reference

#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <cmath>
#include <random>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <functional>
#include <queue>
#include <stack>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <memory>
#include <tuple>
#include <regex>
#include <codecvt>
#include <locale>

namespace Evolution {
namespace Utils {

// String utilities (unused)
namespace String {

std::vector<std::string> split(const std::string& str, const std::string& delimiter) {
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = str.find(delimiter);

    while(end != std::string::npos) {
        tokens.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }

    tokens.push_back(str.substr(start));
    return tokens;
}

std::string join(const std::vector<std::string>& strings, const std::string& delimiter) {
    if(strings.empty()) return "";

    std::string result = strings[0];
    for(size_t i = 1; i < strings.size(); ++i) {
        result += delimiter + strings[i];
    }
    return result;
}

std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    if(start == std::string::npos) return "";

    size_t end = str.find_last_not_of(" \t\n\r");
    return str.substr(start, end - start + 1);
}

std::string toLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return result;
}

std::string toUpper(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::toupper(c); });
    return result;
}

bool startsWith(const std::string& str, const std::string& prefix) {
    return str.length() >= prefix.length() &&
           str.substr(0, prefix.length()) == prefix;
}

bool endsWith(const std::string& str, const std::string& suffix) {
    return str.length() >= suffix.length() &&
           str.substr(str.length() - suffix.length()) == suffix;
}

std::string replace(const std::string& str, const std::string& from, const std::string& to) {
    std::string result = str;
    size_t pos = 0;

    while((pos = result.find(from, pos)) != std::string::npos) {
        result.replace(pos, from.length(), to);
        pos += to.length();
    }

    return result;
}

std::string padLeft(const std::string& str, size_t totalWidth, char padChar = ' ') {
    if(str.length() >= totalWidth) return str;
    return std::string(totalWidth - str.length(), padChar) + str;
}

std::string padRight(const std::string& str, size_t totalWidth, char padChar = ' ') {
    if(str.length() >= totalWidth) return str;
    return str + std::string(totalWidth - str.length(), padChar);
}

bool contains(const std::string& str, const std::string& substr) {
    return str.find(substr) != std::string::npos;
}

int countOccurrences(const std::string& str, const std::string& substr) {
    int count = 0;
    size_t pos = 0;

    while((pos = str.find(substr, pos)) != std::string::npos) {
        count++;
        pos += substr.length();
    }

    return count;
}

std::string reverse(const std::string& str) {
    return std::string(str.rbegin(), str.rend());
}

bool isPalindrome(const std::string& str) {
    int left = 0;
    int right = str.length() - 1;

    while(left < right) {
        if(str[left] != str[right]) return false;
        left++;
        right--;
    }

    return true;
}

std::string capitalize(const std::string& str) {
    if(str.empty()) return str;
    std::string result = str;
    result[0] = std::toupper(result[0]);
    return result;
}

std::string camelCase(const std::string& str) {
    std::vector<std::string> words = split(str, " _-");
    std::string result;

    for(size_t i = 0; i < words.size(); ++i) {
        if(!words[i].empty()) {
            result += capitalize(toLower(words[i]));
        }
    }

    return result;
}

std::string snakeCase(const std::string& str) {
    std::string result;
    for(char c : str) {
        if(std::isupper(c)) {
            if(!result.empty()) result += "_";
            result += std::tolower(c);
        } else if(c == ' ' || c == '-') {
            result += "_";
        } else {
            result += c;
        }
    }
    return result;
}

} // namespace String

// Math utilities (unused)
namespace Math {

const double PI = 3.14159265358979323846;
const double E = 2.71828182845904523536;
const double GOLDEN_RATIO = 1.618033988749895;

template<typename T>
T clamp(T value, T min, T max) {
    return std::max(min, std::min(value, max));
}

template<typename T>
T lerp(T a, T b, T t) {
    return a + t * (b - a);
}

template<typename T>
T smoothStep(T edge0, T edge1, T x) {
    T t = clamp((x - edge0) / (edge1 - edge0), T(0), T(1));
    return t * t * (T(3) - T(2) * t);
}

double degreesToRadians(double degrees) {
    return degrees * PI / 180.0;
}

double radiansToDegrees(double radians) {
    return radians * 180.0 / PI;
}

bool approximatelyEqual(double a, double b, double epsilon = 1e-6) {
    return std::abs(a - b) < epsilon;
}

double normalizeAngle(double angle) {
    angle = fmod(angle, 2.0 * PI);
    if(angle < 0) angle += 2.0 * PI;
    return angle;
}

double shortestAngleDifference(double a, double b) {
    double diff = b - a;
    return normalizeAngle(diff + PI) - PI;
}

double interpolateAngle(double a, double b, double t) {
    return a + shortestAngleDifference(a, b) * t;
}

bool isPowerOfTwo(int n) {
    return n > 0 && (n & (n - 1)) == 0;
}

int nextPowerOfTwo(int n) {
    if(n <= 0) return 1;
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n++;
    return n;
}

unsigned int hashInt(unsigned int x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}

double gaussian(double x, double sigma) {
    return std::exp(-(x * x) / (2.0 * sigma * sigma)) / (sigma * std::sqrt(2.0 * PI));
}

std::vector<double> generateGaussianKernel(int size, double sigma) {
    std::vector<double> kernel(size);
    int center = size / 2;
    double sum = 0;

    for(int i = 0; i < size; ++i) {
        double x = i - center;
        kernel[i] = gaussian(x, sigma);
        sum += kernel[i];
    }

    // Normalize
    for(double& value : kernel) {
        value /= sum;
    }

    return kernel;
}

} // namespace Math

// Random utilities (unused)
namespace Random {

class RandomGenerator {
private:
    std::mt19937 generator;
    std::uniform_real_distribution<double> realDist;
    std::uniform_int_distribution<int> intDist;
    std::normal_distribution<double> normalDist;

public:
    RandomGenerator(uint32_t seed = std::random_device{}())
        : generator(seed), realDist(0.0, 1.0), intDist(0, 100), normalDist(0.0, 1.0) {}

    double randomDouble() { return realDist(generator); }
    double randomDouble(double min, double max) {
        return min + randomDouble() * (max - min);
    }
    int randomInt(int max = 100) { return intDist(generator) % max; }
    int randomInt(int min, int max) { return min + randomInt(max - min); }
    double randomNormal() { return normalDist(generator); }
    bool randomBool(double probability = 0.5) { return randomDouble() < probability; }

    template<typename T>
    T randomChoice(const std::vector<T>& items) {
        if(items.empty()) throw std::runtime_error("Cannot choose from empty vector");
        return items[randomInt(items.size())];
    }

    template<typename T>
    std::vector<T> shuffle(const std::vector<T>& items) {
        std::vector<T> shuffled = items;
        std::shuffle(shuffled.begin(), shuffled.end(), generator);
        return shuffled;
    }

    std::string randomString(int length, const std::string& charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789") {
        std::string result;
        for(int i = 0; i < length; ++i) {
            result += charset[randomInt(charset.length())];
        }
        return result;
    }

    std::string randomDNA(int length) {
        return randomString(length, "ATCG");
    }

    std::string randomProtein(int length) {
        return randomString(length, "ACDEFGHIKLMNPQRSTVWY");
    }
};

} // namespace Random

// Collection utilities (unused)
namespace Collection {

template<typename T>
std::vector<T> filter(const std::vector<T>& items, std::function<bool(const T&)> predicate) {
    std::vector<T> result;
    for(const auto& item : items) {
        if(predicate(item)) {
            result.push_back(item);
        }
    }
    return result;
}

template<typename T, typename R>
std::vector<R> map(const std::vector<T>& items, std::function<R(const T&)> transform) {
    std::vector<R> result;
    result.reserve(items.size());
    for(const auto& item : items) {
        result.push_back(transform(item));
    }
    return result;
}

template<typename T>
T reduce(const std::vector<T>& items, T initial, std::function<T(const T&, const T&)> accumulator) {
    T result = initial;
    for(const auto& item : items) {
        result = accumulator(result, item);
    }
    return result;
}

template<typename T>
bool any(const std::vector<T>& items, std::function<bool(const T&)> predicate) {
    for(const auto& item : items) {
        if(predicate(item)) {
            return true;
        }
    }
    return false;
}

template<typename T>
bool all(const std::vector<T>& items, std::function<bool(const T&)> predicate) {
    for(const auto& item : items) {
        if(!predicate(item)) {
            return false;
        }
    }
    return true;
}

template<typename T>
std::vector<T> unique(const std::vector<T>& items) {
    std::set<T> seen;
    std::vector<T> result;
    for(const auto& item : items) {
        if(seen.insert(item).second) {
            result.push_back(item);
        }
    }
    return result;
}

template<typename T>
std::vector<T> intersect(const std::vector<T>& a, const std::vector<T>& b) {
    std::set<T> setA(a.begin(), a.end());
    std::set<T> setB(b.begin(), b.end());
    std::vector<T> result;
    std::set_intersection(setA.begin(), setA.end(), setB.begin(), setB.end(),
                         std::back_inserter(result));
    return result;
}

template<typename T>
std::vector<T> unionSet(const std::vector<T>& a, const std::vector<T>& b) {
    std::set<T> setA(a.begin(), a.end());
    std::set<T> setB(b.begin(), b.end());
    std::vector<T> result;
    std::set_union(setA.begin(), setA.end(), setB.begin(), setB.end(),
                  std::back_inserter(result));
    return result;
}

template<typename T>
std::vector<T> difference(const std::vector<T>& a, const std::vector<T>& b) {
    std::set<T> setA(a.begin(), a.end());
    std::set<T> setB(b.begin(), b.end());
    std::vector<T> result;
    std::set_difference(setA.begin(), setA.end(), setB.begin(), setB.end(),
                       std::back_inserter(result));
    return result;
}

template<typename T>
std::pair<std::vector<T>, std::vector<T>> partition(const std::vector<T>& items, std::function<bool(const T&)> predicate) {
    std::vector<T> trueItems, falseItems;
    for(const auto& item : items) {
        if(predicate(item)) {
            trueItems.push_back(item);
        } else {
            falseItems.push_back(item);
        }
    }
    return {trueItems, falseItems};
}

template<typename T>
std::vector<std::vector<T>> chunk(const std::vector<T>& items, int chunkSize) {
    std::vector<std::vector<T>> chunks;
    for(size_t i = 0; i < items.size(); i += chunkSize) {
        chunks.emplace_back(items.begin() + i,
                           items.begin() + std::min(i + chunkSize, items.size()));
    }
    return chunks;
}

template<typename T>
std::optional<T> findFirst(const std::vector<T>& items, std::function<bool(const T&)> predicate) {
    for(const auto& item : items) {
        if(predicate(item)) {
            return item;
        }
    }
    return std::nullopt;
}

template<typename T>
int findIndex(const std::vector<T>& items, std::function<bool(const T&)> predicate) {
    for(size_t i = 0; i < items.size(); ++i) {
        if(predicate(items[i])) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

template<typename T>
std::vector<T> take(const std::vector<T>& items, int count) {
    count = std::min(count, static_cast<int>(items.size()));
    return std::vector<T>(items.begin(), items.begin() + count);
}

template<typename T>
std::vector<T> drop(const std::vector<T>& items, int count) {
    count = std::min(count, static_cast<int>(items.size()));
    return std::vector<T>(items.begin() + count, items.end());
}

template<typename T>
T sum(const std::vector<T>& items) {
    return reduce(items, T(0), [](const T& acc, const T& item) { return acc + item; });
}

template<typename T>
T product(const std::vector<T>& items) {
    return reduce(items, T(1), [](const T& acc, const T& item) { return acc * item; });
}

template<typename T>
T average(const std::vector<T>& items) {
    if(items.empty()) return T(0);
    return sum(items) / static_cast<T>(items.size());
}

template<typename T>
T max(const std::vector<T>& items) {
    if(items.empty()) throw std::runtime_error("Cannot find max of empty vector");
    return *std::max_element(items.begin(), items.end());
}

template<typename T>
T min(const std::vector<T>& items) {
    if(items.empty()) throw std::runtime_error("Cannot find min of empty vector");
    return *std::min_element(items.begin(), items.end());
}

} // namespace Collection

// Date/Time utilities (unused)
namespace DateTime {

std::string getCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
    ss << '.' << std::setfill('0') << std::setw(3) << ms.count();
    return ss.str();
}

std::string formatDate(const std::chrono::system_clock::time_point& tp, const std::string& format) {
    auto time_t = std::chrono::system_clock::to_time_t(tp);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), format.c_str());
    return ss.str();
}

std::chrono::system_clock::time_point parseDate(const std::string& dateStr, const std::string& format) {
    std::tm tm = {};
    std::istringstream ss(dateStr);
    ss >> std::get_time(&tm, format.c_str());
    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

int daysBetween(const std::chrono::system_clock::time_point& a, const std::chrono::system_clock::time_point& b) {
    auto duration = std::chrono::duration_cast<std::chrono::hours>(b - a);
    return static_cast<int>(duration.count() / 24);
}

bool isWeekend(const std::chrono::system_clock::time_point& tp) {
    auto time_t = std::chrono::system_clock::to_time_t(tp);
    auto tm = std::localtime(&time_t);
    return tm->tm_wday == 0 || tm->tm_wday == 6; // Sunday or Saturday
}

bool isLeapYear(int year) {
    return (year % 400 == 0) || (year % 100 != 0 && year % 4 == 0);
}

int daysInMonth(int year, int month) {
    static const int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if(month == 2 && isLeapYear(year)) {
        return 29;
    }
    return days[month - 1];
}

std::chrono::system_clock::time_point addDays(const std::chrono::system_clock::time_point& tp, int days) {
    return tp + std::chrono::hours(days * 24);
}

std::chrono::system_clock::time_point addMonths(const std::chrono::system_clock::time_point& tp, int months) {
    auto time_t = std::chrono::system_clock::to_time_t(tp);
    auto tm = std::localtime(&time_t);

    tm->tm_mon += months;
    if(tm->tm_mon > 11) {
        tm->tm_year += tm->tm_mon / 12;
        tm->tm_mon %= 12;
    }

    return std::chrono::system_clock::from_time_t(std::mktime(tm));
}

std::chrono::system_clock::time_point addYears(const std::chrono::system_clock::time_point& tp, int years) {
    auto time_t = std::chrono::system_clock::to_time_t(tp);
    auto tm = std::localtime(&time_t);
    tm->tm_year += years;
    return std::chrono::system_clock::from_time_t(std::mktime(tm));
}

} // namespace DateTime

// File utilities (unused)
namespace File {

bool exists(const std::string& path) {
    std::ifstream file(path);
    return file.good();
}

std::string readAll(const std::string& path) {
    std::ifstream file(path);
    if(!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + path);
    }
    return std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
}

void writeAll(const std::string& path, const std::string& content) {
    std::ofstream file(path);
    if(!file.is_open()) {
        throw std::runtime_error("Cannot write to file: " + path);
    }
    file << content;
}

void appendAll(const std::string& path, const std::string& content) {
    std::ofstream file(path, std::ios::app);
    if(!file.is_open()) {
        throw std::runtime_error("Cannot append to file: " + path);
    }
    file << content;
}

std::vector<std::string> readLines(const std::string& path) {
    std::ifstream file(path);
    std::vector<std::string> lines;
    std::string line;

    while(std::getline(file, line)) {
        lines.push_back(line);
    }

    return lines;
}

void writeLines(const std::string& path, const std::vector<std::string>& lines) {
    std::ofstream file(path);
    for(const auto& line : lines) {
        file << line << "\n";
    }
}

std::string getExtension(const std::string& path) {
    size_t dot = path.find_last_of('.');
    return (dot != std::string::npos) ? path.substr(dot) : "";
}

std::string getBaseName(const std::string& path) {
    size_t slash = path.find_last_of("/\\");
    size_t dot = path.find_last_of('.');

    if(slash == std::string::npos) {
        return (dot != std::string::npos) ? path.substr(0, dot) : path;
    }

    return (dot != std::string::npos && dot > slash) ?
           path.substr(slash + 1, dot - slash - 1) :
           path.substr(slash + 1);
}

std::string getDirectory(const std::string& path) {
    size_t slash = path.find_last_of("/\\");
    return (slash != std::string::npos) ? path.substr(0, slash) : "";
}

std::string joinPath(const std::string& base, const std::string& relative) {
    if(base.empty() || base.back() == '/' || base.back() == '\\') {
        return base + relative;
    }
    return base + "/" + relative;
}

bool copyFile(const std::string& source, const std::string& destination) {
    std::ifstream src(source, std::ios::binary);
    std::ofstream dst(destination, std::ios::binary);

    if(!src.is_open() || !dst.is_open()) {
        return false;
    }

    dst << src.rdbuf();
    return true;
}

std::vector<std::string> findFiles(const std::string& directory, const std::string& pattern) {
    std::vector<std::string> files;
    // In a real implementation, this would use platform-specific APIs
    // For now, just return an empty vector
    return files;
}

long long getFileSize(const std::string& path) {
    std::ifstream file(path, std::ios::binary | std::ios::ate);
    if(!file.is_open()) {
        return -1;
    }
    return file.tellg();
}

} // namespace File

// Hash utilities (unused)
namespace Hash {

uint32_t fnv1a32(const std::string& data) {
    const uint32_t FNV_PRIME_32 = 16777619;
    const uint32_t FNV_OFFSET_BASIS_32 = 2166136261;

    uint32_t hash = FNV_OFFSET_BASIS_32;
    for(unsigned char byte : data) {
        hash ^= byte;
        hash *= FNV_PRIME_32;
    }

    return hash;
}

uint64_t fnv1a64(const std::string& data) {
    const uint64_t FNV_PRIME_64 = 1099511628211ULL;
    const uint64_t FNV_OFFSET_BASIS_64 = 14695981039346656037ULL;

    uint64_t hash = FNV_OFFSET_BASIS_64;
    for(unsigned char byte : data) {
        hash ^= byte;
        hash *= FNV_PRIME_64;
    }

    return hash;
}

uint32_t murmur3_32(const std::string& data, uint32_t seed = 0) {
    const uint32_t c1 = 0xcc9e2d51;
    const uint32_t c2 = 0x1b873593;
    const uint32_t r1 = 15;
    const uint32_t r2 = 13;
    const uint32_t m = 5;
    const uint32_t n = 0xe6546b64;

    uint32_t hash = seed;
    const int nblocks = data.size() / 4;

    const uint32_t* blocks = reinterpret_cast<const uint32_t*>(data.c_str());

    for(int i = 0; i < nblocks; i++) {
        uint32_t k = blocks[i];
        k *= c1;
        k = (k << r1) | (k >> (32 - r1));
        k *= c2;

        hash ^= k;
        hash = ((hash << r2) | (hash >> (32 - r2))) * m + n;
    }

    const uint8_t* tail = reinterpret_cast<const uint8_t*>(data.c_str() + nblocks * 4);
    uint32_t k1 = 0;

    switch(data.size() & 3) {
        case 3: k1 ^= tail[2] << 16;
        case 2: k1 ^= tail[1] << 8;
        case 1: k1 ^= tail[0];
            k1 *= c1;
            k1 = (k1 << r1) | (k1 >> (32 - r1));
            k1 *= c2;
            hash ^= k1;
    }

    hash ^= data.size();
    hash ^= (hash >> 16);
    hash *= 0x85ebca6b;
    hash ^= (hash >> 13);
    hash *= 0xc2b2ae35;
    hash ^= (hash >> 16);

    return hash;
}

std::string md5(const std::string& data) {
    // This would require a proper MD5 implementation
    // For now, just return a placeholder
    return "md5_hash_placeholder";
}

std::string sha256(const std::string& data) {
    // This would require a proper SHA-256 implementation
    // For now, just return a placeholder
    return "sha256_hash_placeholder";
}

} // namespace Hash

} // namespace Utils
} // namespace Evolution