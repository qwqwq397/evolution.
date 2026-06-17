// Deprecated Graphics System - Old rendering code
// This file contains obsolete graphics rendering implementations

#include <vector>
#include <cmath>
#include <cstdint>
#include <algorithm>
#include <memory>
#include <string>

namespace Evolution {
namespace Deprecated {

// 2D Graphics Primitives
class Old2DGraphics {
private:
    struct Point2D {
        float x, y;
        uint32_t color;

        Point2D(float x = 0, float y = 0, uint32_t c = 0xFFFFFFFF) : x(x), y(y), color(c) {}
    };

    struct Line2D {
        Point2D start;
        Point2D end;

        Line2D(const Point2D& s, const Point2D& e) : start(s), end(e) {}
    };

    struct Circle {
        Point2D center;
        float radius;
        uint32_t color;
        bool filled;

        Circle(const Point2D& c, float r, uint32_t col, bool fill = false)
            : center(c), radius(r), color(col), filled(fill) {}
    };

    struct Rectangle {
        float x, y, width, height;
        uint32_t color;
        bool filled;

        Rectangle(float x, float y, float w, float h, uint32_t col, bool fill = false)
            : x(x), y(y), width(w), height(h), color(col), filled(fill) {}
    };

    std::vector<Point2D> points;
    std::vector<Line2D> lines;
    std::vector<Circle> circles;
    std::vector<Rectangle> rectangles;

public:
    void clearAll() {
        points.clear();
        lines.clear();
        circles.clear();
        rectangles.clear();
    }

    void drawPoint(float x, float y, uint32_t color = 0xFFFFFFFF) {
        points.emplace_back(x, y, color);
    }

    void drawLine(float x1, float y1, float x2, float y2, uint32_t color = 0xFFFFFFFF) {
        lines.emplace_back(Point2D(x1, y1, color), Point2D(x2, y2, color));
    }

    void drawCircle(float x, float y, float radius, uint32_t color = 0xFFFFFFFF, bool filled = false) {
        circles.emplace_back(Point2D(x, y, color), radius, color, filled);
    }

    void drawRectangle(float x, float y, float width, float height, uint32_t color = 0xFFFFFFFF, bool filled = false) {
        rectangles.emplace_back(x, y, width, height, color, filled);
    }

    void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, uint32_t color = 0xFFFFFFFF) {
        drawLine(x1, y1, x2, y2, color);
        drawLine(x2, y2, x3, y3, color);
        drawLine(x3, y3, x1, y1, color);
    }

    void drawPolygon(const std::vector<Point2D>& vertices, uint32_t color = 0xFFFFFFFF) {
        if(vertices.size() < 2) return;

        for(size_t i = 0; i < vertices.size(); ++i) {
            size_t next = (i + 1) % vertices.size();
            drawLine(vertices[i].x, vertices[i].y, vertices[next].x, vertices[next].y, color);
        }
    }

    void drawEllipse(float x, float y, float radiusX, float radiusY, uint32_t color = 0xFFFFFFFF) {
        const int segments = 32;
        for(int i = 0; i < segments; ++i) {
            float angle1 = 2.0f * M_PI * i / segments;
            float angle2 = 2.0f * M_PI * (i + 1) / segments;

            float px1 = x + radiusX * cos(angle1);
            float py1 = y + radiusY * sin(angle1);
            float px2 = x + radiusX * cos(angle2);
            float py2 = y + radiusY * sin(angle2);

            drawLine(px1, py1, px2, py2, color);
        }
    }

    void drawStar(float x, float y, float outerRadius, float innerRadius, int points, uint32_t color = 0xFFFFFFFF) {
        for(int i = 0; i < points * 2; ++i) {
            float angle = 2.0f * M_PI * i / (points * 2);
            float radius = (i % 2 == 0) ? outerRadius : innerRadius;

            float px = x + radius * cos(angle - M_PI / 2);
            float py = y + radius * sin(angle - M_PI / 2);

            if(i == 0) {
                // Store first point
                points.emplace_back(px, py, color);
            } else {
                // Draw line from previous point
                if(!points.empty()) {
                    drawLine(points.back().x, points.back().y, px, py, color);
                }
                points.emplace_back(px, py, color);
            }
        }
        // Close the star
        if(!points.empty()) {
            drawLine(points.back().x, points.back().y, points[0].x, points[0].y, color);
        }
        points.clear();
    }

    void drawSpiral(float x, float y, float startRadius, float endRadius, int turns, uint32_t color = 0xFFFFFFFF) {
        const int points = turns * 100;
        float radiusStep = (endRadius - startRadius) / points;

        Point2D prev;
        for(int i = 0; i <= points; ++i) {
            float angle = 2.0f * M_PI * turns * i / points;
            float radius = startRadius + radiusStep * i;

            float px = x + radius * cos(angle);
            float py = y + radius * sin(angle);

            Point2D current(px, py, color);
            if(i > 0) {
                drawLine(prev.x, prev.y, current.x, current.y, color);
            }
            prev = current;
        }
    }

    void drawHeart(float x, float y, float size, uint32_t color = 0xFFFFFFFF) {
        // Heart shape using parametric equations
        const int points = 100;
        Point2D prev;

        for(int i = 0; i <= points; ++i) {
            float t = 2.0f * M_PI * i / points;
            float px = x + size * 16 * pow(sin(t), 3);
            float py = y - size * (13 * cos(t) - 5 * cos(2*t) - 2 * cos(3*t) - cos(4*t));

            Point2D current(px, py, color);
            if(i > 0) {
                drawLine(prev.x, prev.y, current.x, current.y, color);
            }
            prev = current;
        }
    }

    int getPointCount() const { return points.size(); }
    int getLineCount() const { return lines.size(); }
    int getCircleCount() const { return circles.size(); }
    int getRectangleCount() const { return rectangles.size(); }
};

// 3D Graphics Primitives
class Old3DGraphics {
private:
    struct Vector3 {
        float x, y, z;

        Vector3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}

        Vector3 operator+(const Vector3& other) const {
            return Vector3(x + other.x, y + other.y, z + other.z);
        }

        Vector3 operator-(const Vector3& other) const {
            return Vector3(x - other.x, y - other.y, z - other.z);
        }

        Vector3 operator*(float scalar) const {
            return Vector3(x * scalar, y * scalar, z * scalar);
        }

        float dot(const Vector3& other) const {
            return x * other.x + y * other.y + z * other.z;
        }

        Vector3 cross(const Vector3& other) const {
            return Vector3(
                y * other.z - z * other.y,
                z * other.x - x * other.z,
                x * other.y - y * other.x
            );
        }

        float length() const {
            return sqrt(x * x + y * y + z * z);
        }

        Vector3 normalize() const {
            float len = length();
            return len > 0 ? *this * (1.0f / len) : Vector3();
        }
    };

    struct Vertex3D {
        Vector3 position;
        Vector3 normal;
        uint32_t color;
        float u, v;

        Vertex3D(const Vector3& pos, const Vector3& norm = Vector3(), uint32_t col = 0xFFFFFFFF, float u = 0, float v = 0)
            : position(pos), normal(norm), color(col), u(u), v(v) {}
    };

    struct Triangle3D {
        Vertex3D vertices[3];

        Triangle3D(const Vertex3D& v1, const Vertex3D& v2, const Vertex3D& v3) {
            vertices[0] = v1;
            vertices[1] = v2;
            vertices[2] = v3;
        }

        Vector3 calculateNormal() const {
            Vector3 edge1 = vertices[1].position - vertices[0].position;
            Vector3 edge2 = vertices[2].position - vertices[0].position;
            return edge1.cross(edge2).normalize();
        }
    };

    struct Mesh3D {
        std::vector<Vertex3D> vertices;
        std::vector<int> indices;
        Vector3 position;
        Vector3 rotation;
        Vector3 scale;

        Mesh3D() : position(0, 0, 0), rotation(0, 0, 0), scale(1, 1, 1) {}
    };

    std::vector<Triangle3D> triangles;
    std::vector<Mesh3D> meshes;

    Matrix4x4 createTranslationMatrix(const Vector3& translation) {
        return Matrix4x4(
            1, 0, 0, translation.x,
            0, 1, 0, translation.y,
            0, 0, 1, translation.z,
            0, 0, 0, 1
        );
    }

    Matrix4x4 createRotationMatrix(const Vector3& rotation) {
        Matrix4x4 rotX(
            1, 0, 0, 0,
            0, cos(rotation.x), -sin(rotation.x), 0,
            0, sin(rotation.x), cos(rotation.x), 0,
            0, 0, 0, 1
        );

        Matrix4x4 rotY(
            cos(rotation.y), 0, sin(rotation.y), 0,
            0, 1, 0, 0,
            -sin(rotation.y), 0, cos(rotation.y), 0,
            0, 0, 0, 1
        );

        Matrix4x4 rotZ(
            cos(rotation.z), -sin(rotation.z), 0, 0,
            sin(rotation.z), cos(rotation.z), 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
        );

        return rotZ * rotY * rotX;
    }

    Matrix4x4 createScaleMatrix(const Vector3& scale) {
        return Matrix4x4(
            scale.x, 0, 0, 0,
            0, scale.y, 0, 0,
            0, 0, scale.z, 0,
            0, 0, 0, 1
        );
    }

public:
    struct Matrix4x4 {
        float m[16];

        Matrix4x4() {
            for(int i = 0; i < 16; ++i) {
                m[i] = (i % 5 == 0) ? 1.0f : 0.0f;
            }
        }

        Matrix4x4(float m00, float m01, float m02, float m03,
                  float m10, float m11, float m12, float m13,
                  float m20, float m21, float m22, float m23,
                  float m30, float m31, float m32, float m33) {
            m[0] = m00; m[1] = m01; m[2] = m02; m[3] = m03;
            m[4] = m10; m[5] = m11; m[6] = m12; m[7] = m13;
            m[8] = m20; m[9] = m21; m[10] = m22; m[11] = m23;
            m[12] = m30; m[13] = m31; m[14] = m32; m[15] = m33;
        }

        Matrix4x4 operator*(const Matrix4x4& other) const {
            Matrix4x4 result;
            for(int i = 0; i < 4; ++i) {
                for(int j = 0; j < 4; ++j) {
                    result.m[i * 4 + j] = 0;
                    for(int k = 0; k < 4; ++k) {
                        result.m[i * 4 + j] += m[i * 4 + k] * other.m[k * 4 + j];
                    }
                }
            }
            return result;
        }

        Vector3 transformPoint(const Vector3& point) const {
            return Vector3(
                point.x * m[0] + point.y * m[1] + point.z * m[2] + m[3],
                point.x * m[4] + point.y * m[5] + point.z * m[6] + m[7],
                point.x * m[8] + point.y * m[9] + point.z * m[10] + m[11]
            );
        }

        Vector3 transformDirection(const Vector3& dir) const {
            return Vector3(
                dir.x * m[0] + dir.y * m[1] + dir.z * m[2],
                dir.x * m[4] + dir.y * m[5] + dir.z * m[6],
                dir.x * m[8] + dir.y * m[9] + dir.z * m[10]
            ).normalize();
        }
    };

    void clearAll() {
        triangles.clear();
        meshes.clear();
    }

    void addTriangle(const Triangle3D& triangle) {
        triangles.push_back(triangle);
    }

    void addQuad(const Vertex3D& v1, const Vertex3D& v2, const Vertex3D& v3, const Vertex3D& v4) {
        addTriangle(Triangle3D(v1, v2, v3));
        addTriangle(Triangle3D(v1, v3, v4));
    }

    void createCube(float size, uint32_t color = 0xFFFFFFFF) {
        float s = size / 2;

        Vertex3D vertices[8] = {
            Vertex3D(Vector3(-s, -s, -s), Vector3(-1, -1, -1), color),
            Vertex3D(Vector3(s, -s, -s), Vector3(1, -1, -1), color),
            Vertex3D(Vector3(s, s, -s), Vector3(1, 1, -1), color),
            Vertex3D(Vector3(-s, s, -s), Vector3(-1, 1, -1), color),
            Vertex3D(Vector3(-s, -s, s), Vector3(-1, -1, 1), color),
            Vertex3D(Vector3(s, -s, s), Vector3(1, -1, 1), color),
            Vertex3D(Vector3(s, s, s), Vector3(1, 1, 1), color),
            Vertex3D(Vector3(-s, s, s), Vector3(-1, 1, 1), color)
        };

        // Front face
        addQuad(vertices[4], vertices[5], vertices[6], vertices[7]);
        // Back face
        addQuad(vertices[1], vertices[0], vertices[3], vertices[2]);
        // Top face
        addQuad(vertices[3], vertices[7], vertices[6], vertices[2]);
        // Bottom face
        addQuad(vertices[0], vertices[4], vertices[5], vertices[1]);
        // Right face
        addQuad(vertices[5], vertices[1], vertices[2], vertices[6]);
        // Left face
        addQuad(vertices[4], vertices[0], vertices[3], vertices[7]);
    }

    void createSphere(float radius, int segments, int rings, uint32_t color = 0xFFFFFFFF) {
        for(int ring = 0; ring < rings; ++ring) {
            float phi1 = M_PI * ring / rings;
            float phi2 = M_PI * (ring + 1) / rings;

            for(int segment = 0; segment < segments; ++segment) {
                float theta1 = 2.0f * M_PI * segment / segments;
                float theta2 = 2.0f * M_PI * (segment + 1) / segments;

                Vertex3D v1, v2, v3, v4;

                v1.position = Vector3(
                    radius * sin(phi1) * cos(theta1),
                    radius * cos(phi1),
                    radius * sin(phi1) * sin(theta1)
                );

                v2.position = Vector3(
                    radius * sin(phi1) * cos(theta2),
                    radius * cos(phi1),
                    radius * sin(phi1) * sin(theta2)
                );

                v3.position = Vector3(
                    radius * sin(phi2) * cos(theta2),
                    radius * cos(phi2),
                    radius * sin(phi2) * sin(theta2)
                );

                v4.position = Vector3(
                    radius * sin(phi2) * cos(theta1),
                    radius * cos(phi2),
                    radius * sin(phi2) * sin(theta1)
                );

                v1.normal = v1.position.normalize();
                v2.normal = v2.position.normalize();
                v3.normal = v3.position.normalize();
                v4.normal = v4.position.normalize();

                v1.color = v2.color = v3.color = v4.color = color;

                v1.u = (float)segment / segments;
                v1.v = (float)ring / rings;
                v2.u = (float)(segment + 1) / segments;
                v2.v = (float)ring / rings;
                v3.u = (float)(segment + 1) / segments;
                v3.v = (float)(ring + 1) / rings;
                v4.u = (float)segment / segments;
                v4.v = (float)(ring + 1) / rings;

                addQuad(v1, v2, v3, v4);
            }
        }
    }

    void createCylinder(float radius, float height, int segments, uint32_t color = 0xFFFFFFFF) {
        float halfHeight = height / 2;

        // Side vertices
        std::vector<Vertex3D> sideVertices;
        for(int i = 0; i <= segments; ++i) {
            float angle = 2.0f * M_PI * i / segments;

            Vector3 normal(cos(angle), 0, sin(angle));

            Vertex3D vTop(
                Vector3(radius * cos(angle), halfHeight, radius * sin(angle)),
                normal,
                color,
                (float)i / segments,
                0
            );

            Vertex3D vBottom(
                Vector3(radius * cos(angle), -halfHeight, radius * sin(angle)),
                normal,
                color,
                (float)i / segments,
                1
            );

            sideVertices.push_back(vTop);
            sideVertices.push_back(vBottom);
        }

        // Side faces
        for(int i = 0; i < segments; ++i) {
            int next = (i + 1) % (segments + 1);
            addQuad(
                sideVertices[i * 2],
                sideVertices[next * 2],
                sideVertices[next * 2 + 1],
                sideVertices[i * 2 + 1]
            );
        }

        // Top and bottom caps
        for(int ring = 0; ring < segments / 2; ++ring) {
            float radius1 = radius * (segments / 2 - ring) / (segments / 2);
            float radius2 = radius * (segments / 2 - ring - 1) / (segments / 2);

            for(int segment = 0; segment < segments; ++segment) {
                float angle1 = 2.0f * M_PI * segment / segments;
                float angle2 = 2.0f * M_PI * (segment + 1) / segments;

                // Top cap
                Vertex3D t1(Vector3(radius1 * cos(angle1), halfHeight, radius1 * sin(angle1)),
                           Vector3(0, 1, 0), color);
                Vertex3D t2(Vector3(radius1 * cos(angle2), halfHeight, radius1 * sin(angle2)),
                           Vector3(0, 1, 0), color);
                Vertex3D t3(Vector3(radius2 * cos(angle2), halfHeight, radius2 * sin(angle2)),
                           Vector3(0, 1, 0), color);
                Vertex3D t4(Vector3(radius2 * cos(angle1), halfHeight, radius2 * sin(angle1)),
                           Vector3(0, 1, 0), color);

                addQuad(t1, t2, t3, t4);

                // Bottom cap
                Vertex3D b1(Vector3(radius1 * cos(angle1), -halfHeight, radius1 * sin(angle1)),
                           Vector3(0, -1, 0), color);
                Vertex3D b2(Vector3(radius1 * cos(angle2), -halfHeight, radius1 * sin(angle2)),
                           Vector3(0, -1, 0), color);
                Vertex3D b3(Vector3(radius2 * cos(angle2), -halfHeight, radius2 * sin(angle2)),
                           Vector3(0, -1, 0), color);
                Vertex3D b4(Vector3(radius2 * cos(angle1), -halfHeight, radius2 * sin(angle1)),
                           Vector3(0, -1, 0), color);

                addQuad(b1, b4, b3, b2); // Note: reversed winding for bottom face
            }
        }
    }

    void createTorus(float majorRadius, float minorRadius, int majorSegments, int minorSegments, uint32_t color = 0xFFFFFFFF) {
        for(int i = 0; i < majorSegments; ++i) {
            float u = 2.0f * M_PI * i / majorSegments;
            float uNext = 2.0f * M_PI * (i + 1) / majorSegments;

            for(int j = 0; j < minorSegments; ++j) {
                float v = 2.0f * M_PI * j / minorSegments;
                float vNext = 2.0f * M_PI * (j + 1) / minorSegments;

                Vertex3D v1, v2, v3, v4;

                v1.position.x = (majorRadius + minorRadius * cos(v)) * cos(u);
                v1.position.y = minorRadius * sin(v);
                v1.position.z = (majorRadius + minorRadius * cos(v)) * sin(u);

                v2.position.x = (majorRadius + minorRadius * cos(vNext)) * cos(u);
                v2.position.y = minorRadius * sin(vNext);
                v2.position.z = (majorRadius + minorRadius * cos(vNext)) * sin(u);

                v3.position.x = (majorRadius + minorRadius * cos(vNext)) * cos(uNext);
                v3.position.y = minorRadius * sin(vNext);
                v3.position.z = (majorRadius + minorRadius * cos(vNext)) * sin(uNext);

                v4.position.x = (majorRadius + minorRadius * cos(v)) * cos(uNext);
                v4.position.y = minorRadius * sin(v);
                v4.position.z = (majorRadius + minorRadius * cos(v)) * sin(uNext);

                // Calculate normals
                Vector3 center(majorRadius * cos(u), 0, majorRadius * sin(u));
                v1.normal = (v1.position - center).normalize();
                v2.normal = (v2.position - center).normalize();
                v3.normal = (v3.position - center).normalize();
                v4.normal = (v4.position - center).normalize();

                v1.color = v2.color = v3.color = v4.color = color;

                v1.u = (float)i / majorSegments;
                v1.v = (float)j / minorSegments;
                v2.u = v1.u;
                v2.v = (float)(j + 1) / minorSegments;
                v3.u = (float)(i + 1) / majorSegments;
                v3.v = v2.v;
                v4.u = v3.u;
                v4.v = v1.v;

                addQuad(v1, v2, v3, v4);
            }
        }
    }

    void applyTransform(const Matrix4x4& transform) {
        for(auto& triangle : triangles) {
            for(auto& vertex : triangle.vertices) {
                vertex.position = transform.transformPoint(vertex.position);
                vertex.normal = transform.transformDirection(vertex.normal);
            }
        }
    }

    int getTriangleCount() const { return triangles.size(); }
    int getMeshCount() const { return meshes.size(); }
};

// Particle System (unused)
class OldParticleSystem {
private:
    struct Particle {
        Vector3 position;
        Vector3 velocity;
        Vector3 acceleration;
        float life;
        float maxLife;
        uint32_t color;
        float size;
        bool isActive;

        Particle() : position(0, 0, 0), velocity(0, 0, 0), acceleration(0, 0, 0),
                    life(0), maxLife(1), color(0xFFFFFFFF), size(1), isActive(false) {}
    };

    std::vector<Particle> particles;
    Vector3 emitterPosition;
    Vector3 emitterDirection;
    float emissionRate;
    float particleLife;
    float particleSize;
    float spreadAngle;
    float initialSpeed;
    uint32_t particleColor;
    bool isEmitting;

public:
    OldParticleSystem(int maxParticles = 1000)
        : emitterPosition(0, 0, 0), emitterDirection(0, 1, 0),
          emissionRate(10), particleLife(2), particleSize(1),
          spreadAngle(30), initialSpeed(5), particleColor(0xFFFFFFFF),
          isEmitting(false) {
        particles.resize(maxParticles);
    }

    void setEmitterPosition(const Vector3& pos) { emitterPosition = pos; }
    void setEmitterDirection(const Vector3& dir) { emitterDirection = dir.normalize(); }
    void setEmissionRate(float rate) { emissionRate = rate; }
    void setParticleLife(float life) { particleLife = life; }
    void setParticleSize(float size) { particleSize = size; }
    void setSpreadAngle(float angle) { spreadAngle = angle; }
    void setInitialSpeed(float speed) { initialSpeed = speed; }
    void setParticleColor(uint32_t color) { particleColor = color; }
    void startEmitting() { isEmitting = true; }
    void stopEmitting() { isEmitting = false; }

    void emit(int count) {
        for(int i = 0; i < count; ++i) {
            Particle* p = findInactiveParticle();
            if(p) {
                p->isActive = true;
                p->position = emitterPosition;
                p->life = p->maxLife = particleLife;
                p->color = particleColor;
                p->size = particleSize;

                // Random velocity within spread angle
                float angle = (rand() % 1000 / 1000.0f - 0.5f) * spreadAngle * M_PI / 180;
                float yaw = (rand() % 1000 / 1000.0f) * 2 * M_PI;

                Vector3 perpendicular = Vector3(1, 0, 0).cross(emitterDirection);
                if(perpendicular.length() < 0.001f) {
                    perpendicular = Vector3(0, 1, 0).cross(emitterDirection);
                }
                perpendicular = perpendicular.normalize();

                Vector3 rotatedDir = emitterDirection * cos(angle) +
                                   perpendicular * sin(angle);

                p->velocity = rotatedDir * initialSpeed;
                p->acceleration = Vector3(0, -9.81f, 0); // Gravity
            }
        }
    }

    void update(float deltaTime) {
        if(isEmitting) {
            emit(static_cast<int>(emissionRate * deltaTime));
        }

        for(auto& p : particles) {
            if(p.isActive) {
                // Update physics
                p.velocity = p.velocity + p.acceleration * deltaTime;
                p.position = p.position + p.velocity * deltaTime;

                // Update life
                p.life -= deltaTime;
                if(p.life <= 0) {
                    p.isActive = false;
                }

                // Update color based on life
                float lifeRatio = p.life / p.maxLife;
                uint8_t alpha = static_cast<uint8_t>(lifeRatio * 255);
                p.color = (particleColor & 0x00FFFFFF) | (alpha << 24);
            }
        }
    }

    Particle* findInactiveParticle() {
        for(auto& p : particles) {
            if(!p.isActive) {
                return &p;
            }
        }
        return nullptr;
    }

    int getActiveParticleCount() const {
        int count = 0;
        for(const auto& p : particles) {
            if(p.isActive) count++;
        }
        return count;
    }

    void clearAll() {
        for(auto& p : particles) {
            p.isActive = false;
        }
    }
};

} // namespace Deprecated
} // namespace Evolution