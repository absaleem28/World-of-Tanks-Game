#ifndef TANK_DATA
#define TANK_DATA

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"
#include "core/gpu/shader.h"
#include "lab_m1/tema2/GameComponents/bullet.h"


class Tank
{
    public:
        int lifes;

        glm::vec3 body_color;
        glm::vec3 turret_shooter_color;
        glm::vec3 turret_color;
        glm::vec3 wheels_color;

        bool shotNextBullet = true;
        Bullet *bullet;

        float turret_shooter_angle_right = 0;
        float turret_shooter_angle_up = 0;
        float body_angle = 0;
        
        float timeToShoot = 0;
        float timeToRotate = 0;
        float rotationSense = 0;
        bool doRotate = true;

        Mesh* body;
        Mesh* turret_shooter;
        Mesh* turret;
        Mesh* wheels;

        Shader* body_shader;
        Shader* turret_shooter_shader;
        Shader* turret_shader;
        Shader* wheels_shader;

        glm::vec3 position;

        Tank();
        Tank(
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
            const std::string &fileName_wheels_frag);

        void moveForward(float speed, float deltaTimeSeconds);

        void shotBullet(
                glm::vec3 color, glm::vec3 speed,
                const std::string &fileName_bullet,
                const std::string &fileLocation_bullet, 
                
                GLenum shaderVertex,
                const std::string &fileName_bullet_vertex,
                
                GLenum shaderFragment,
                const std::string &fileName_bullet_frag
        );

        glm::vec3 getBulletStartPosition();
};

#endif