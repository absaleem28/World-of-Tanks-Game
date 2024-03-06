#include "lab_m1/tema2/GameComponents/tank.h"
#include "lab_m1/tema2/values.h"

Tank::Tank()
{

}

Tank::Tank(
            int lifes,

            glm::vec3 body_color,
            glm::vec3 turret_shooter_color,
            glm::vec3 turret_color,
            glm::vec3 wheels_color,

            const std::string &fileLocation_mesh, 
            const std::string &fileName_body,
            const std::string &fileName_turret,
            const std::string &fileName_turret_shooter,
            const std::string &fileName_wheels,

            GLenum shaderVertex,
            const std::string &fileName_body_vertex,
            const std::string &fileName_turret_vertex,
            const std::string &fileName_turret_shooter_vertex,
            const std::string &fileName_wheels_vertex,
            
            GLenum shaderFragment,
            const std::string &fileName_body_frag,
            const std::string &fileName_turret_frag,
            const std::string &fileName_turret_shooter_frag,
            const std::string &fileName_wheels_frag)
{
    this->lifes = lifes;

    this->body_color = body_color;
    this->turret_shooter_color = turret_shooter_color;
    this->turret_color = turret_color;
    this->wheels_color = wheels_color;

    this->body = new Mesh("");
    this->turret_shooter = new Mesh("");
    this->turret = new Mesh("");
    this->wheels = new Mesh("");

    this->body->LoadMesh(fileLocation_mesh, fileName_body);
    this->turret_shooter->LoadMesh(fileLocation_mesh, fileName_turret_shooter);
    this->turret->LoadMesh(fileLocation_mesh, fileName_turret);
    this->wheels->LoadMesh(fileLocation_mesh, fileName_wheels);

    this->body_shader = new Shader("");
    this->turret_shooter_shader = new Shader("");
    this->turret_shader = new Shader("");
    this->wheels_shader = new Shader("");

    this->body_shader->AddShader(fileName_body_vertex, shaderVertex);
    this->body_shader->AddShader(fileName_body_frag, shaderFragment);
    this->body_shader->CreateAndLink();

    this->turret_shooter_shader->AddShader(fileName_turret_shooter_vertex, shaderVertex);
    this->turret_shooter_shader->AddShader(fileName_turret_shooter_frag, shaderFragment);
    this->turret_shooter_shader->CreateAndLink();

    this->turret_shader->AddShader(fileName_turret_vertex, shaderVertex);
    this->turret_shader->AddShader(fileName_turret_frag, shaderFragment);
    this->turret_shader->CreateAndLink();

    this->wheels_shader->AddShader(fileName_wheels_vertex, shaderVertex);
    this->wheels_shader->AddShader(fileName_wheels_frag, shaderFragment);
    this->wheels_shader->CreateAndLink();

}

void Tank::moveForward(float speed, float deltaTimeSeconds)
{
    this->position += speed * glm::vec3(cos(this->body_angle), 0, (-sin(this->body_angle))) * deltaTimeSeconds;
}

void Tank::shotBullet(
        glm::vec3 color, glm::vec3 speed,
        const std::string &fileLocation_bullet, 
        const std::string &fileName_bullet,
        
        GLenum shaderVertex,
        const std::string &fileName_bullet_vertex,
        
        GLenum shaderFragment,
        const std::string &fileName_bullet_frag
    )
{
    glm::vec3 bulletPosition = getBulletStartPosition();
    this->bullet = new Bullet(bulletPosition, color, speed,
                fileName_bullet, fileLocation_bullet,
                shaderVertex, fileName_bullet_vertex,
                shaderFragment, fileName_bullet_frag);
    
}

glm::vec3 Tank::getBulletStartPosition()
{
    glm::mat4 modelMatrix(1);

    modelMatrix = glm::translate(glm::mat4(1), this->position);

    modelMatrix = glm::rotate(modelMatrix, this->turret_shooter_angle_right + this->body_angle, glm::vec3(0.0f, 1.0f, 0.0f));

    modelMatrix = glm::translate(modelMatrix, ((float) (this->lifes / (TANK_INITIAL_LIFES))) * glm::vec3(0.25f, 0, 0));

    modelMatrix = glm::translate(modelMatrix, (TANK_BULLET_DISPL) * glm::vec3(0.0f, (TANK_SCALE_FACTOR), 0.0f));

    modelMatrix = glm::rotate(modelMatrix, this->turret_shooter_angle_up, glm::vec3(0.0f, 0.0f, 1.0f));

    modelMatrix = glm::translate(modelMatrix, (TANK_BULLET_DISPL) * glm::vec3((TANK_SCALE_FACTOR), 0.0f, 0.0f));

    return glm::vec3(modelMatrix[3]);
}
