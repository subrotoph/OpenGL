//  Copyright © 2020 Subph. All rights reserved.
//

#include "mesh.h"
#include "define.h"

#include "../libraries/tiny_obj_loader/tiny_obj_loader.h"

#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <math.h>
#include <unordered_map>

float * Mesh::generateCube(unsigned long &memorySize, unsigned int details, float scale) {
    float vertices[8][3] = {
        {-.5,  .5,  .5}, {-.5, -.5,  .5}, { .5,  .5,  .5}, { .5, -.5,  .5},
        { .5,  .5, -.5}, { .5, -.5, -.5}, {-.5,  .5, -.5}, {-.5, -.5, -.5}
    };
    unsigned int order[] = {
        6, 7, 0, 0, 7, 1,   2, 3, 4, 4, 3, 5,
        1, 7, 3, 3, 7, 5,   6, 0, 4, 4, 0, 2,
        4, 5, 6, 6, 5, 7,   0, 1, 2, 2, 1, 3
    };
    
    for (int i = 0; i < 24; i++) *(*vertices + i) *= scale;
    
    bool normal = details & MESH_NORMAL;
    bool texture = details & MESH_TEXTURE;
    unsigned int idx = 0;
    unsigned int size = 3 + (normal * 3) + (texture * 2);
    unsigned int totalSize = size * 36;
    float * data = (float*) calloc (totalSize, sizeof(float));
    
    for (int i = 0; i < 36; i++) {
        unsigned int verIdx = order[i];
        idx = i * size;
        data[idx++] = vertices[verIdx][0];
        data[idx++] = vertices[verIdx][1];
        data[idx++] = vertices[verIdx][2];
        if (normal) {
            int side = i / 6;
            int axis = side / 2;
            data[idx + axis] = side % 2 * 2 - 1;
            idx += 3;
        }
        if (texture) {
            int start = i * size;
            int axis = i / 12;
            if (axis == 0) data[idx++] = data[start + 1] > 0;
            else           data[idx++] = data[start    ] > 0;
            if (axis == 2) data[idx++] = data[start + 1] > 0;
            else           data[idx++] = data[start + 2] < 0;
        }
    }
    memorySize = sizeof(float) * totalSize;
    return data;
}

void Mesh::createPlane() {
    vertices  = { -.5, 0., .5,  .5, 0., .5,  .5, 0., -.5,  -.5, 0., -.5 };
    normals   = {  0., 1., 0.,  0., 1., 0.,  0., 1.,  0.,   0., 1.,  0. };
    texCoords = { 0, 1,   1, 1,   1, 0,   0, 0 };
    indices   = { 0, 1, 2, 2, 3, 0 };
}

void Mesh::createQuad() {
    vertices  = { -1., 1., 0.,   1., 1., 0.,   1.,-1., 0.,   -1.,-1., 0., };
    normals   = {  0., 0., 1.,   0., 0., 1.,   0., 0., 1.,    0., 0., 1. };
    texCoords = { 0, 1,   1, 1,   1, 0,   0, 0  };
    indices   = { 0, 1, 2, 2, 3, 0 };
}

void Mesh::createCube() {
    float cubeVertices[8][3] = {
        {-.5,  .5,  .5}, {-.5, -.5,  .5}, { .5,  .5,  .5}, { .5, -.5,  .5},
        { .5,  .5, -.5}, { .5, -.5, -.5}, {-.5,  .5, -.5}, {-.5, -.5, -.5}
    };
    unsigned int cubeIndices[] = {
        6, 7, 0, 0, 7, 1,   2, 3, 4, 4, 3, 5,
        1, 7, 3, 3, 7, 5,   6, 0, 4, 4, 0, 2,
        4, 5, 6, 6, 5, 7,   0, 1, 2, 2, 1, 3
    };

    for (int i = 0; i < 36; i++) {
        float *vertex = cubeVertices[cubeIndices[i]];

        float normal[] = { .0, .0, .0 };
        int side = i / 6;
        int axis = side / 2;
        normal[axis] = side % 2 * 2 - 1;

        float texture[] = { .0, .0 };
        if (axis == 0) texture[0] = vertex[1] > 0;
        else           texture[0] = vertex[0] > 0;
        if (axis == 2) texture[1] = vertex[1] > 0;
        else           texture[1] = vertex[2] < 0;

        vertices .insert(vertices .end(), { vertex[0], vertex[1], vertex[2] });
        normals  .insert(normals  .end(), { normal[0], normal[1], normal[2] });
        texCoords.insert(texCoords.end(), { texture[0], texture[1] });
    }
    
    indices = {
        0 ,1 ,2 ,3 ,4 ,5 ,   6 ,7 ,8 ,9 ,10,11,
        12,13,14,15,16,17,   18,19,20,21,22,23,
        24,25,26,27,28,29,   30,31,32,33,34,35
    };
}


void Mesh::createSphere(int wedge, int segment) {
    float x, y, z, xz;
    float s, t;

    float segmentStep = -2 * PI / segment;  // counter-clockwise
    float wedgeStep = PI / wedge;
    float segmentAngle, wedgeAngle;

    for(int i = 0; i <= wedge; i++) {
        wedgeAngle = i * wedgeStep;             // starting from 0 to pi
        y  = cosf(wedgeAngle);                  // r * cos(u)
        xz = sinf(wedgeAngle);                  // r * sin(u)

        for(int j = 0; j <= segment; j++) {
            segmentAngle = j * segmentStep;     // starting from 0 to 2pi
            x = xz * cosf(segmentAngle);        // r * sin(u) * cos(v)
            z = xz * sinf(segmentAngle);        // r * sin(u) * sin(v)
            
            vertices.insert(vertices.end(), { x, y, z });
            normals .insert(normals .end(), { x, y, z });

            s = (float)j / segment;             // vertex tex coord (s, t)
            t = (float)i / wedge;               // range between [0, 1]
            texCoords.insert(texCoords.end(), { s, t });
        }
    }
    
    int w1, w2;
    int segmentVertices = segment + 1;
    for(int i = 0; i < wedge; i++) {
        w1 = i  * segmentVertices;
        w2 = w1 + segmentVertices;

        for(int j = 0; j < segment; j++) {
            int d = j + 1;
            indices.insert(indices.end(), { w1+j, w2+j, w1+d });
            indices.insert(indices.end(), { w1+d, w2+j, w2+d });
        }
    }
}

void Mesh::genVAO() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(sizeofVertices()));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(sizeofVertices() + sizeofNormals()));
}

void Mesh::genVBO() {
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeofVertices() + sizeofNormals() + sizeofTexCoords(), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeofVertices(), &vertices[0]);
    glBufferSubData(GL_ARRAY_BUFFER, sizeofVertices(), sizeofNormals(), &normals[0]);
    glBufferSubData(GL_ARRAY_BUFFER, sizeofVertices() + sizeofNormals(), sizeofTexCoords(), &texCoords[0]);
}

void Mesh::genEBO() {
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeofIndices(), &indices[0], GL_STATIC_DRAW);
}

void Mesh::removeBuffer() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}

void Mesh::draw() {
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, (int)indices.size(), GL_UNSIGNED_INT, 0);
}

void Mesh::scale(glm::vec3 size) {
    model = glm::scale(model, size);
}

void Mesh::rotate(float angle, glm::vec3 axis) {
    model = glm::rotate(model, glm::radians(angle), axis);
}

void Mesh::translate(glm::vec3 translation) {
    model = glm::translate(model, translation);
}

glm::mat4 Mesh::getMatrix() {
    return model;
}


unsigned long Mesh::sizeofVertices() { return sizeof(float) * vertices.size(); }
unsigned long Mesh::sizeofNormals() { return sizeof(float) * normals.size(); }
unsigned long Mesh::sizeofTexCoords() { return sizeof(float) * texCoords.size(); }
unsigned long Mesh::sizeofIndices() { return sizeof(int) * indices.size(); }



void Mesh::loadModel(const char* filename) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::unordered_map<size_t, uint32_t> uniqueVertices;
    std::string warn, err;
    
    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename)) {
        throw std::runtime_error(warn + err);
    }
    
    for (const auto& shape : shapes) {
        for (uint i = 0; i < shape.mesh.indices.size(); i++) {
            const auto& index = shape.mesh.indices[i];
            
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 0]); // x
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 1]); // u
            vertices.push_back(attrib.vertices[3 * index.vertex_index + 2]); // z
            
            normals.push_back(attrib.normals[3 * index.normal_index + 0]); // x
            normals.push_back(attrib.normals[3 * index.normal_index + 1]); // u
            normals.push_back(attrib.normals[3 * index.normal_index + 2]); // z
            
            texCoords.push_back(attrib.texcoords[2 * index.texcoord_index + 0]); // x
            texCoords.push_back(1.0f - attrib.texcoords[2 * index.texcoord_index + 1]); // y

            indices.push_back(i);
        }
    }
}
