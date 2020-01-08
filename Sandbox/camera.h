//  Copyright © 2019 Subph. All rights reserved.
//

#pragma once

#include <glm/glm.hpp>

class Camera {
    
public:
    Camera(glm::vec3 position, glm::vec3 direction = glm::vec3(0, 0, 0));
    
    void reset();
    void setInvertedAxis(bool value);
    void setLockFocus(bool value);
    void setPosition(glm::vec3 position);
    void lookAt(glm::vec3 focusPos);
    
    void move(glm::vec3 direction);
    void turn(glm::vec2 delta);
    void zoom(float delta);
    
    glm::vec3 getPosition();
    glm::mat4 getViewMatrix();
    glm::mat4 getProjection(float ratio);
    
private:
    glm::vec3 focusPoint;
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 right;
    glm::vec3 up;
    glm::vec3 worldUp;

    float yaw, pitch, roll;
    
    int axis;
    float speed;
    float sensitivity;
    float viewDistance;
    float viewAngle;
    
    float maxZoom;
    float maxPitch;
    
    bool lockFocus;
    bool useConstraint;
    
    void updateVector();
    void updateRotation();
};