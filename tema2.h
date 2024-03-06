#pragma once

#include <vector>

#include "components/simple_scene.h"
#include "lab_m1/tema2/camera_tema2.h"
#include "lab_m1/tema2/GameComponents/tank.h"
#include "lab_m1/tema2/values.h"

// COLORS
#define RED_COLOR (glm::vec3(1.0f, 0.0f, 0.0f))
#define BLACK_COLOR (glm::vec3(0.0f, 0.0f, 0.0f))

namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
     public:
        Tema2();
        ~Tema2();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderSimpleMesh(
            Mesh *mesh, Shader *shader, glm::vec3 color, int lifes,
            const glm::mat4 &modelMatrix, implemented_tema2::Camera *camera_view
        );

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        void RenderScene(float deltaTimeSeconds, implemented_tema2::Camera *camera_view);
        void DrawWalls(implemented_tema2::Camera *camera_view);
        void DrawTower(implemented_tema2::Camera *camera_view);
        void DrawPlane(implemented_tema2::Camera *camera_view);
        void DrawBuildings(implemented_tema2::Camera *camera_view);
        void DrawTank(float deltaTimeSeconds, implemented_tema2::Camera *camera_view);
        void DrawEnemies(float deltaTimeSeconds, implemented_tema2::Camera *camera_view);
        void DrawBullet(float deltaTimeSeconds, Tank *t, implemented_tema2::Camera *camera_view);
        void DrawLight(implemented_tema2::Camera *camera_view);

        void attackMainTank(Tank *t, Tank *e, float deltaTimeSeconds);
        void simulateMovement(Tank *e, int idx, float deltaTimeSeconds);

        glm::vec3 getP(float distance, float diameter1, float diameter2, glm::vec3 position1, glm::vec3 position2);
        void CheckBuildingCollision(Tank *t);
        void CheckCollision(Tank *t);
        void CheckWallCollision(Tank *t);
        void CheckTowerCollision(Tank *t);
        void CheckTankCollision(Tank *t);
        void ApplyCollisionCase(float radius1, float radius2, glm::vec3 pos1, glm::vec3 pos2, Tank *t);

        // GAME DATA
        float GAME_TIMER = 0;
        float SCORE = 0; // killed enemy

        // VIEW
        glm::mat4 projectionMatrix;

        // CAMERA
        implemented_tema2::Camera *camera;
        implemented_tema2::Camera *camera_minimap;

        // GENERAL MODEL MATRIX
        glm::mat4 modelMatrix = glm::mat4(1);

        // TANK
        Tank *tank;

        // BUILDINGS
        std::vector<glm::vec3> buildings_pos;
        float buildings_no;


        // PLANE
        std::vector<std::vector<glm::vec3>> planePositions =
        {
            { 
                glm::vec3(6.2, OBJECTS_TRANSLATE_OY, 6.2), glm::vec3(18.6, OBJECTS_TRANSLATE_OY, 6.2),
                glm::vec3(6.2, OBJECTS_TRANSLATE_OY, 18.6), glm::vec3(18.6, OBJECTS_TRANSLATE_OY, 18.6)
            },
            { 
                glm::vec3(-6.2, OBJECTS_TRANSLATE_OY, 6.2), glm::vec3(-18.6, OBJECTS_TRANSLATE_OY, 6.2),
                glm::vec3(-6.2, OBJECTS_TRANSLATE_OY, 18.6), glm::vec3(-18.6, OBJECTS_TRANSLATE_OY, 18.6)
            },
            {
                glm::vec3(6.2, OBJECTS_TRANSLATE_OY, -6.2), glm::vec3(18.6, OBJECTS_TRANSLATE_OY, -6.2),
                glm::vec3(6.2, OBJECTS_TRANSLATE_OY, -18.6), glm::vec3(18.6, OBJECTS_TRANSLATE_OY, -18.6)
            },
            { 
                glm::vec3(-6.2, OBJECTS_TRANSLATE_OY, -6.2), glm::vec3(-18.6, OBJECTS_TRANSLATE_OY, -6.2),
                glm::vec3(-6.2, OBJECTS_TRANSLATE_OY, -18.6), glm::vec3(-18.6, OBJECTS_TRANSLATE_OY, -18.6)
            }
        };

        // WALL
        std::vector<glm::vec3> walls_position;

        // TOWER
        std::vector<glm::vec3> towers_position =
        {
            glm::vec3(((PLANE_SIZE) / 2 - (((TOWER_SCALE_FACTOR) * (TOWER_DIM).x) / 2)), OBJECTS_TRANSLATE_OY, ((PLANE_SIZE) / 2 - (((TOWER_SCALE_FACTOR) * (TOWER_DIM).z)) / 2)),
            glm::vec3(-((PLANE_SIZE) / 2 - (((TOWER_SCALE_FACTOR) * (TOWER_DIM).x) / 2)), OBJECTS_TRANSLATE_OY, ((PLANE_SIZE) / 2 - (((TOWER_SCALE_FACTOR) * (TOWER_DIM).z)) / 2)),
            glm::vec3(((PLANE_SIZE) / 2 - (((TOWER_SCALE_FACTOR) * (TOWER_DIM).x) / 2)), OBJECTS_TRANSLATE_OY, -((PLANE_SIZE) / 2 - (((TOWER_SCALE_FACTOR) * (TOWER_DIM).z)) / 2)),
            glm::vec3(-((PLANE_SIZE) / 2 - (((TOWER_SCALE_FACTOR) * (TOWER_DIM).x) / 2)), OBJECTS_TRANSLATE_OY, -((PLANE_SIZE) / 2 - (((TOWER_SCALE_FACTOR) * (TOWER_DIM).z)) / 2))
        };

        // STATIC TANK ON THE TOWER
        Tank* tankOverTower;

        // ENEMY
        std::vector<Tank*> enemies;

        std::vector<float> timersToRotate;

        float contor_until_enemy_allowed_to_shoot = 0;

        int enemiesNo = 0;
        int enemiesNoCopy = 0;

                
                
        glm::vec3 lightPosition;
        unsigned int materialShininess;
        float materialKd;
        float materialKs;
    };
}   // namespace m1
