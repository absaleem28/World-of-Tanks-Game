#ifndef BULLET_DATA
#define BULLET_DATA

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"
#include "core/gpu/shader.h"

class Bullet
{
    private:
        Mesh *mesh;
        Shader *shader;

        glm::vec3 position;
        glm::vec3 color;

        glm::vec3 speedVec;

        bool hitTarget= false;

        float angle;
        float angleUp;

    public:
        Bullet();
        Bullet(glm::vec3 position, glm::vec3 color, glm::vec3 speed,
                const std::string &fileLocation_bullet, 
                const std::string &fileName_bullet,
                
                GLenum shaderVertex,
                const std::string &fileName_bullet_vertex,
                
                GLenum shaderFragment,
                const std::string &fileName_bullet_frag
        );

        glm::vec3 getPosition();
        void setPosition(glm::vec3 position);

        glm::vec3 getColor();
        void setColor(glm::vec3 color);

        bool getHitTarget();
        void setHitTarget(bool hitTarget);

        float getAngle();
        void setAngle(float angle);

        float getAngleUp();
        void setAngleUp(float angle);

        Mesh *getMesh();
        
        Shader *getShader();
        
        void moveBullet(float deltaTimeSeconds);
};

#endif