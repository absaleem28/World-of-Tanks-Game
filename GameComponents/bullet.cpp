#include "lab_m1/tema2/GameComponents/bullet.h"

Bullet::Bullet()
{

}

Bullet::Bullet(glm::vec3 position, glm::vec3 color, glm::vec3 speed,
                const std::string &fileLocation_bullet, 
                const std::string &fileName_bullet,
                
                GLenum shaderVertex,
                const std::string &fileName_bullet_vertex,
                
                GLenum shaderFragment,
                const std::string &fileName_bullet_frag
    )
{
    this->position = position;
    this->color = color;
    this->speedVec = speed;

    this->mesh = new Mesh("");
    this->mesh->LoadMesh(fileLocation_bullet, fileName_bullet);

    this->shader = new Shader("");
    this->shader->AddShader(fileName_bullet_vertex, shaderVertex);
    this->shader->AddShader(fileName_bullet_frag, shaderFragment);
    this->shader->CreateAndLink();
}

glm::vec3 Bullet::getPosition()
{
    return this->position;
}
void Bullet::setPosition(glm::vec3 position)
{
    this->position = position;
}

glm::vec3 Bullet::getColor()
{
    return this->color;
}
void Bullet::setColor(glm::vec3 color)
{
    this->color = color;
}

bool Bullet::getHitTarget()
{
    return this->hitTarget;
}
void Bullet::setHitTarget(bool hitTarget)
{
    this->hitTarget = hitTarget;
}

float Bullet::getAngle()
{
    return this->angle;
}

void Bullet::setAngle(float angle)
{
    this->angle = angle;
}

float Bullet::getAngleUp()
{
    return this->angleUp;
}

void Bullet::setAngleUp(float angleUp)
{
    this->angleUp = angleUp;
}

Mesh* Bullet::getMesh()
{
    return this->mesh;
}

Shader* Bullet::getShader()
{
    return this->shader;
}

void Bullet::moveBullet(float deltaTimeSeconds)
{
    float gravity = 9.81;
    
    this->speedVec.y -= gravity * deltaTimeSeconds;

    this->position += 
        glm::vec3(this->speedVec.x, this->speedVec.y, this->speedVec.z) 
        * glm::vec3(cos(this->angle), 1, -sin(this->angle)) 
        * deltaTimeSeconds;
}