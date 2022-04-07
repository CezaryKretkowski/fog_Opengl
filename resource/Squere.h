//
// Created by cezar on 03.04.2022.
//

#ifndef UNTITLED3_SQUERE_H
#define UNTITLED3_SQUERE_H
std::vector<glm::vec3> vert = {
        glm::vec3(-0.5f, 0.5f, 0.f),
        glm::vec3(0.5f, 0.5f, 0.f),
        glm::vec3(0.5f, -0.5f, 0.f),
        glm::vec3(-0.5f, 0.5f, 0.f),
        glm::vec3(0.5f, -0.5f, 0.f),
        glm::vec3(-0.5f, -0.5f, 0.f)
};
std::vector<glm::vec2> uv = {
        glm::vec2(0.0f, 1.0f),
        glm::vec2(1.0f, 1.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(0.0f, 1.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(0.0f, 0.0f)
};
#endif //UNTITLED3_SQUERE_H
