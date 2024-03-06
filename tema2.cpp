#include "lab_m1/tema2/tema2.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;


Tema2::Tema2()
{
}

Tema2::~Tema2()
{
}

void Tema2::Init()
{
    cout << "JOCUL A INCEPUT!" << endl;

    srand(time(0));

    // SET UP GAME CAMERA
    camera = new implemented_tema2::Camera;
    camera->Set(glm::vec3(-4.5, 2, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
    camera->distanceToTarget = 4.5;

    // SET UP MINIMAP
    camera_minimap = new implemented_tema2::Camera;
    camera_minimap->Set(glm::vec3(0, 2, 0), glm::vec3(0, 1, 0), glm::vec3(1, 0, 0));
    camera_minimap->distanceToTarget = 2;

    // SET PERSPECTIVE VIEW
    projectionMatrix = glm::perspective((FOV_CAMERA), window->props.aspectRatio, 0.01f, 200.0f);

    // INITIALIZE MAIN TANK
    tank =  new Tank(
        TANK_INITIAL_LIFES,
        glm::vec3(0.2,0.37,0.23), glm::vec3(1,1,1), glm::vec3(0.5, 0.5, 0.2), glm::vec3(1,1,1),

        PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "models_tema2"),
        "tank_body.obj", "tank_turret.obj", "tank_turret_shooter.obj", "tank_wheels.obj",

        GL_VERTEX_SHADER,
        PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "Shaders", "tankShaders", "tankBody" , "VertexShader.glsl"),
        PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "Shaders", "tankShaders", "tankTrigger" , "VertexShader.glsl"),
        PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "Shaders", "tankShaders", "tankTriggerSupport" , "VertexShader.glsl"),
        PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "Shaders", "tankShaders", "tankWheels" , "VertexShader.glsl"),

        GL_FRAGMENT_SHADER,
        PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "Shaders", "tankShaders", "tankBody", "FragmentShader.glsl"),
        PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "Shaders", "tankShaders", "tankTrigger", "FragmentShader.glsl"),
        PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "Shaders", "tankShaders", "tankTriggerSupport", "FragmentShader.glsl"),
        PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "Shaders", "tankShaders", "tankWheels", "FragmentShader.glsl")
    );

    // INITIAL POSITION
    tank->position = glm::vec3(0, OBJECTS_TRANSLATE_OY, 0);

    // INITIALIZE GAME PLAN
    {
        Mesh* mesh = new Mesh("plane");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "models_tema2"), "plane.fbx");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // INITALIZE BORDER/WALL MESH
    {
        Mesh* mesh = new Mesh("wall");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "models_tema2"), "wall.fbx");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // INITIALIZE TOWER MESH
    {
        Mesh* mesh = new Mesh("tower");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "models_tema2"), "tower.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // INITIALIZE BUILDING/HOME MESH
    {
        Mesh* mesh = new Mesh("home");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "models_tema2"), "home.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    buildings_no = (MINIMUM_BUILDINGS_ON_MAP) + rand() % (MINIMUM_BUILDINGS_ON_MAP);

    for (int i = 0; i < buildings_no; i++)
    {
        buildings_pos.push_back(glm::vec3(-23 +rand() % (46), OBJECTS_TRANSLATE_OY, -23 +rand() % (46)));
    }

    // INITIALIZE STATIC TANK OVER TOWERS MESH
    tankOverTower = new Tank(
        TANK_INITIAL_LIFES,
        glm::vec3(0.9,0.3,0.4), glm::vec3(1,1,1), glm::vec3(0.5, 0.5, 0.2), glm::vec3(1,1,1),

        PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "models_tema2"),
        "tank_body.obj", "tank_turret.obj", "tank_turret_shooter.obj", "tank_wheels.obj",

        GL_VERTEX_SHADER,
        PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "Shaders", "tankShaders", "tankBody" , "VertexShader.glsl"),
        PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "Shaders", "tankShaders", "tankTrigger" , "VertexShader.glsl"),
        PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "Shaders", "tankShaders", "tankTriggerSupport" , "VertexShader.glsl"),
        PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "Shaders", "tankShaders", "tankWheels" , "VertexShader.glsl"),

        GL_FRAGMENT_SHADER,
        PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "Shaders", "tankShaders", "tankBody", "FragmentShader.glsl"),
        PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "Shaders", "tankShaders", "tankTrigger", "FragmentShader.glsl"),
        PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "Shaders", "tankShaders", "tankTriggerSupport", "FragmentShader.glsl"),
        PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "Shaders", "tankShaders", "tankWheels", "FragmentShader.glsl")
    );

    // INITIALIZE SHADERS
    {
        Shader *shader = new Shader("towerShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "Shaders", "towerShader", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "Shaders", "towerShader", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    {
        Shader *shader = new Shader("homeShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "Shaders", "homeShaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "Shaders", "homeShaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    // INITIALIZE LIGHT MESH
    {
        Mesh* mesh = new Mesh("light");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "models_tema2"), "tank_bullet.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        lightPosition = tank->position + (LIGHT_RELATIVE_POSITION_TO_TANK);
        materialShininess = 120;
        materialKd = 1.5;
        materialKs = 0.5;
    }

    // GENERATE ENEMIES NUMBER
    enemiesNo = 4 + rand() % 4;
    enemiesNoCopy = enemiesNo;

    cout << "AU FOST GENERATI " << enemiesNoCopy << " INAMICI!" << endl;

    // INITIALIZE ENEMIES
    for (int i = 0; i < enemiesNo; i++)
    {
        enemies.push_back(
            new Tank(
                TANK_INITIAL_LIFES,
                glm::vec3((float) (rand() % 10) / 10, (float) (rand() % 10) / 10, (float) (rand() % 10) / 10), 
                glm::vec3(1,1,1), glm::vec3(0.5, 0.5, 0.2), glm::vec3(1,1,1),

                PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "models_tema2"),
                "tank_body.obj", "tank_turret.obj", "tank_turret_shooter.obj", "tank_wheels.obj",

                GL_VERTEX_SHADER,
                PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "Shaders", "tankShaders", "tankBody" , "VertexShader.glsl"),
                PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "Shaders", "tankShaders", "tankTrigger" , "VertexShader.glsl"),
                PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "Shaders", "tankShaders", "tankTriggerSupport" , "VertexShader.glsl"),
                PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "Shaders", "tankShaders", "tankWheels" , "VertexShader.glsl"),

                GL_FRAGMENT_SHADER,
                PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "Shaders", "tankShaders", "tankBody", "FragmentShader.glsl"),
                PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "Shaders", "tankShaders", "tankTrigger", "FragmentShader.glsl"),
                PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "Shaders", "tankShaders", "tankTriggerSupport", "FragmentShader.glsl"),
                PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "Shaders", "tankShaders", "tankWheels", "FragmentShader.glsl")
            )
        );

        // GET EACH ENEMY TIMER TO ROTATE
        timersToRotate.push_back(0);        

        // GET START POSITION 
        enemies[i]->position = glm::vec3(-20 + rand() % 40, OBJECTS_TRANSLATE_OY, -20 + rand() % 40);

        // GET START BODY ANGLE
        enemies[i]->body_angle = RADIANS(-180 + rand() % 360);

        // GET TIME UNTIL NEXT ROTATION
        enemies[i]->timeToRotate = 3 + rand() % 5;

        // GET ROTATION SENSE: CLOCKWISE OR ANTICLOCKWISE
        enemies[i]->rotationSense = rand() % 2;
    }

}

void Tema2::FrameStart()
{
    // REMOVE MOUSE CURSOR FROM THE SCREEN
    glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.73, 0.8, 0.92, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Tema2::Update(float deltaTimeSeconds)
{
    // IF NO MORE ENEMIES LEFT -> PLAYER WON GAME
    if (SCORE == enemiesNoCopy)
    {
        // PRINT MESSAGE
        cout << "AI CASTIGAT DUPA " << round(GAME_TIMER) << " SECUNDE!\n";
        std::exit(0);
    }

    // IF STILL ALIVE -> CONTINUE PLAYING
    if (tank->lifes > 0)
    {
        // INCREASE GLOBAL TIMER
        GAME_TIMER += deltaTimeSeconds;

        // INCREASE TIMER UNTIL ENEMIES ARE ALLOWED TO SHOOT
        contor_until_enemy_allowed_to_shoot += deltaTimeSeconds;

        // GET WINDOW SIZE
        glm::ivec2 resolution = window->GetResolution();

        // MAIN SCENE
        projectionMatrix = glm::perspective((FOV_CAMERA), window->props.aspectRatio, 0.01f, 200.0f);

        glViewport(0, 0, resolution.x/2, resolution.y/2);

        RenderScene(deltaTimeSeconds, camera);

        // DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);


        // MINIMAP SCENE
        glClear(GL_DEPTH_BUFFER_BIT);
        
        projectionMatrix = glm::ortho( -(WIDTH_ORTHO), (WIDTH_ORTHO), -(HEIGHT_ORTHO), (HEIGHT_ORTHO), -10.0f, 100.0f);

        glViewport(2, 2, resolution.x / 10, resolution.y / 10);

        RenderScene(deltaTimeSeconds, camera_minimap);

        // DrawCoordinateSystem(camera_minimap->GetViewMatrix(), projectionMatrix);

    } else {
        // IF NO MORE LIFES -> PLAYER LOST GAME
        // PRINT MESSAGE
        cout << "AI PIERDUT DUPA " << round(GAME_TIMER) << " SECUNDE!" << endl;
        cout << "AI REUSIT SA DOBORI " << SCORE << " INAMICI DINTR-UN TOTAL DE " << enemiesNoCopy << " !" << endl;
        std::exit(0);
    }
}

void Tema2::RenderScene(float deltaTimeSeconds, implemented_tema2::Camera *camera_view)
{
        // RENDER PLANE
    DrawPlane(camera_view);
    // RENDER BORDER
    DrawWalls(camera_view);
    // RENDER TOWER
    DrawTower(camera_view);
    // RENDER BUILDINGS
    DrawBuildings(camera_view);
    // RENDER MY TANK
    DrawTank(deltaTimeSeconds, camera_view);
    // RENDER ENEMIES
    DrawEnemies(deltaTimeSeconds, camera_view);
    // RENDER LIGHT
    DrawLight(camera_view);
}

// FUNCTION THAT RENDERS LIGHT SPHERE
void Tema2::DrawLight(implemented_tema2::Camera *camera_view)
{
    modelMatrix = glm::translate(glm::mat4(1), lightPosition);
    RenderSimpleMesh(
                meshes["light"], shaders["Simple"], glm::vec3(0, 0, 0),
                (DEFAULT_OBJECT_NO_LIFE), modelMatrix, camera_view
    );
}

// FUNCTION THAT RENDERS BULDINGS
void Tema2::DrawBuildings(implemented_tema2::Camera *camera_view)
{
    for (int i = 0; i < buildings_no; i ++)
    {
        modelMatrix = glm::translate(glm::mat4(1), buildings_pos[i]);
        RenderSimpleMesh(
            meshes["home"], shaders["homeShader"], glm::vec3(0.7, 0.6, 0.8),
            (DEFAULT_OBJECT_NO_LIFE), modelMatrix, camera_view);
    }
}

// FUNCTION THAT RENDERS BORDERS
void Tema2::DrawWalls(implemented_tema2::Camera *camera_view)
{
    // FOR THE EACH SIDE (OUT OF 4), RENDER 32 "WALL"
    for (int i = 0; i < (WALL_SIDES); i++)
    {
        for (int j = 0; j < (WALLS_EACH_SIDE); j++)
        {
            modelMatrix = glm::rotate(glm::mat4(1), RADIANS((90 * i)) ,glm::vec3(0, 1, 0));
            modelMatrix = glm::translate(modelMatrix, glm::vec3(23.8 - (j * 1.51), 0.5, ((PLANE_SIZE) /  2)));
            RenderSimpleMesh(
                meshes["wall"], shaders["Simple"], glm::vec3(0, 0, 0),
                (DEFAULT_OBJECT_NO_LIFE), modelMatrix, camera_view
            );
        }
    }
}

// FUNCTION THAT RENDERS PLANE
void Tema2::DrawPlane(implemented_tema2::Camera *camera_view)
{
    for (int i = 0; i < planePositions.size(); i++)
    {
        for (int j = 0; j < planePositions[i].size(); j++)
        {
            modelMatrix = glm::translate(glm::mat4(1),planePositions[i][j]);
            modelMatrix = glm::scale(modelMatrix, glm::vec3(13, 1, 13));
            modelMatrix = glm::rotate(modelMatrix, RADIANS(90) ,glm::vec3(1, 0, 0));
            RenderSimpleMesh(
                meshes["plane"], shaders["Simple"], glm::vec3(0, 0, 0),
                (DEFAULT_OBJECT_NO_LIFE), modelMatrix, camera_view
            );
        }
    }
}

// FUNCTION THAT RENDERS TOWER AND TANK OVER IT
void Tema2::DrawTower(implemented_tema2::Camera *camera_view)
{
    for (int i = 0; i < 4; i++)
    {
        modelMatrix = glm::translate(glm::mat4(1), towers_position[i]);

        RenderSimpleMesh(meshes["tower"], shaders["towerShader"], glm::vec3(0.90, 0.85, 0.75), (DEFAULT_OBJECT_NO_LIFE), modelMatrix, camera_view);

        modelMatrix = glm::translate(modelMatrix, (TOWER_DIM) * (TOWER_SCALE_FACTOR) * glm::vec3(0 , 1, 0));

        // RENDER TANK
        RenderSimpleMesh(tankOverTower->body, tankOverTower->body_shader, tankOverTower->body_color, tankOverTower->lifes,modelMatrix, camera_view);
        RenderSimpleMesh(tankOverTower->wheels, tankOverTower->wheels_shader, tankOverTower->wheels_color, tankOverTower->lifes, modelMatrix, camera_view);
        RenderSimpleMesh(tankOverTower->turret, tankOverTower->turret_shader, tankOverTower->turret_color, tankOverTower->lifes, modelMatrix, camera_view);
        RenderSimpleMesh(tankOverTower->turret_shooter, tankOverTower->turret_shooter_shader, tankOverTower->turret_shooter_color, tankOverTower->lifes, modelMatrix, camera_view);

    }
}

// FUNCTION THAT RENDERS PLAYER TANK
void Tema2::DrawTank(float deltaTimeSeconds, implemented_tema2::Camera *camera_view)
{
    // CHECK FOR ANY COLLISION
    CheckCollision(tank);

    // RENDER TANK PARTS
    modelMatrix = glm::translate(glm::mat4(1), tank->position);
    modelMatrix = glm::rotate(modelMatrix, tank->body_angle, glm::vec3(0,1,0));

    // RENDER BODY
    RenderSimpleMesh(tank->body, tank->body_shader, tank->body_color, tank->lifes,modelMatrix, camera_view);

    // RENDER WHEELS
    RenderSimpleMesh(tank->wheels, tank->wheels_shader, tank->wheels_color, tank->lifes, modelMatrix, camera_view);
    
    modelMatrix = glm::translate(modelMatrix, ((TANK_TURRET_DISPL) * (TANK_SCALE_FACTOR)) * glm::vec3(1, 0, 0));
    modelMatrix = glm::rotate(modelMatrix, tank->turret_shooter_angle_right, glm::vec3(0, 1, 0));
    modelMatrix = glm::translate(modelMatrix, -((TANK_TURRET_DISPL) * (TANK_SCALE_FACTOR)) * glm::vec3(1, 0, 0));

    // RENDER TURRET
    RenderSimpleMesh(tank->turret, tank->turret_shader, tank->turret_color, tank->lifes, modelMatrix, camera_view);

    modelMatrix = glm::translate(modelMatrix, ((float) (tank->lifes / (TANK_INITIAL_LIFES))) * glm::vec3(0.25f, 0, 0));
    modelMatrix = glm::translate(modelMatrix, ((TANK_TURRET_SHOOTER_DISPL) * (TANK_SCALE_FACTOR)) * glm::vec3(1, 1, 0));
    modelMatrix = glm::rotate(modelMatrix, tank->turret_shooter_angle_up, glm::vec3(0, 0, 1));
    modelMatrix = glm::translate(modelMatrix, -((TANK_TURRET_SHOOTER_DISPL) * (TANK_SCALE_FACTOR)) * glm::vec3(1, 1, 0));

    //RENDER TURRET SHOOTER
    RenderSimpleMesh(tank->turret_shooter, tank->turret_shooter_shader, tank->turret_shooter_color, tank->lifes, modelMatrix, camera_view);

    // INCREASE TIMER UNTIL TANK ALLOWED TO SHOOT AGAIN
    tank->timeToShoot += deltaTimeSeconds;

    // RENDER BULLETS IF EXISTS
    DrawBullet(deltaTimeSeconds, tank, camera_view);
}

// FUNCTION THAT:
// -    RENDERS BULLET
// -    CHECKS IF BULLETS HITS ANY GAME COMPONENT
// -    MOVE BULLET FORWARD
void Tema2::DrawBullet(float deltaTimeSeconds, Tank *t, implemented_tema2::Camera *camera_view)
{
    // IF ANY TANK "t" shot a bullet
    if(t->bullet)
    {
        modelMatrix = glm::translate(glm::mat4(1), t->bullet->getPosition());
        
        // RENDER BULLET
        RenderSimpleMesh(t->bullet->getMesh(), t->bullet->getShader(), t->bullet->getColor(), (DEFAULT_OBJECT_NO_LIFE), modelMatrix, camera_view);

        // CHECK IF BULLET HIT PLANE
        if (t->bullet && (TANK_BULLET_DIM).y + (t->bullet->getPosition()).y <= OBJECTS_TRANSLATE_OY)
        {
            t->bullet = NULL;
            t->shotNextBullet = true;
        }
        // CHECK IF BULLET HITS BORDERS 
        if (t->bullet && (
                t->bullet->getPosition().x >= ((PLANE_SIZE) /  2) ||
                t->bullet->getPosition().x <= -((PLANE_SIZE) /  2) ||
                t->bullet->getPosition().z >= ((PLANE_SIZE) /  2) || 
                t->bullet->getPosition().z <= -((PLANE_SIZE) /  2)   )
            )
        {
            t->bullet = NULL;
            t->shotNextBullet = true;
        }
        // CHECK IF BULET HITS TOWERS
        if (t->bullet)
        {
            for (int i = 0; i < TOWERS_NO; i++)
            {
                float distance = glm::distance(
                    towers_position[i], t->bullet->getPosition()
                );

                if (distance <= 2.0f)
                {
                    t->bullet = NULL;
                    t->shotNextBullet = true;
                    break;
                }
            }
        }
        // CHECK IF BULLET HITS BUILDINGS
        if (t->bullet)
        {
            for (int i = 0; i < buildings_no; i++)
            {
                float distanceX = glm::distance(
                    buildings_pos[i].x, t->bullet->getPosition().x
                );

                float distanceY = glm::distance(
                    buildings_pos[i].y, t->bullet->getPosition().y
                );

                float distanceZ = glm::distance(
                    buildings_pos[i].z, t->bullet->getPosition().z
                );

                if ( distanceX <= ((BUILDING_DIM).x * (BUILDING_SCALE_FACTOR)) / 2 &&
                    distanceY <= ((BUILDING_DIM).y * (BUILDING_SCALE_FACTOR)) &&
                    distanceZ <= ((BUILDING_DIM).z * (BUILDING_SCALE_FACTOR)) / 2)
                {
                    t->bullet = NULL;
                    t->shotNextBullet = true;
                    break;
                }
            }
        }
        // CHECK IF BULLET HITS ENEMY
        if (t == tank)
        {
            if (t->bullet)
            {
                for (int i = 0; i < enemies.size(); i++)
                {
                    if (t == enemies[i])
                        continue;

                    float distanceX = glm::distance(
                        enemies[i]->position.x, t->bullet->getPosition().x
                    );
                    float distanceY = glm::distance(
                        enemies[i]->position.y, t->bullet->getPosition().y
                    );
                    float distanceZ = glm::distance(
                        enemies[i]->position.z, t->bullet->getPosition().z
                    );

                    if (
                        distanceX <= ((TANK_BODY_DIM).x * (TANK_SCALE_FACTOR)) / 2 &&
                        distanceY <= ((TANK_BODY_DIM).y * (TANK_SCALE_FACTOR)) &&
                        distanceZ <= ((TANK_BODY_DIM).z * (TANK_SCALE_FACTOR)) / 2)
                    {
                        enemies[i]->lifes--;
                        t->bullet = NULL;
                        t->shotNextBullet = true;
                        break;
                    }
                }
            }
        } else // CHECK IF BULLET HITS MAIN PLAYER
        {
            if (t->bullet)
            {
                float distanceX = glm::distance(
                    tank->position.x, t->bullet->getPosition().x
                );
                float distanceY = glm::distance(
                    tank->position.y, t->bullet->getPosition().y
                );
                float distanceZ = glm::distance(
                    tank->position.z, t->bullet->getPosition().z
                );

                if (
                    distanceX <= ((TANK_BODY_DIM).x * (TANK_SCALE_FACTOR)) / 2 &&
                    distanceY <= ((TANK_BODY_DIM).y * (TANK_SCALE_FACTOR)) &&
                    distanceZ <= ((TANK_BODY_DIM).z * (TANK_SCALE_FACTOR)) / 2)
                {
                    tank->lifes--;
                    t->bullet = NULL;
                    t->shotNextBullet = true;
                }
            }
        }

        // MOVE BULLET FORWARD
        if (t->bullet)
        {
            t->bullet->moveBullet(deltaTimeSeconds);
        }
    }
}

// FUNCTION THAT RENDERS ENEMIES
void Tema2::DrawEnemies(float deltaTimeSeconds, implemented_tema2::Camera *camera_view)
{
    // GO TROUGH ALL ENEMIES
    for (int i = 0; i < enemies.size(); i++)
    {
        // ERASE ENEMY IF NOT ALIVE ANYMORE
        if (enemies[i]->lifes == 0)
        {
            enemies[i] = enemies.back();
            enemies.pop_back();
            enemiesNo--;

            cout << "AI DOBORAT UN INAMIC!" << endl;
            cout << "SCORE-UL TAU ACTUAL ESTE: " << ++SCORE << "!\n" << endl;
        }

        // CHECK IF THE MAIN PLAYER TANK IS NEARBY
        attackMainTank(tank, enemies[i], deltaTimeSeconds);

        // SIMULATE MOVEMENT OF ENEMY TANK
        simulateMovement(enemies[i], i, deltaTimeSeconds);

        // CHECK FOR ANY COLLISION
        CheckCollision(enemies[i]);

        // RENDER ENEMY TANK PARTS
        modelMatrix = glm::translate(glm::mat4(1), enemies[i]->position);
        modelMatrix = glm::rotate(modelMatrix, enemies[i]->body_angle, glm::vec3(0,1,0));

        // RENDER BODY
        RenderSimpleMesh(enemies[i]->body, enemies[i]->body_shader, enemies[i]->body_color, enemies[i]->lifes, modelMatrix, camera_view);

        // RENDER WHEELS
        RenderSimpleMesh(enemies[i]->wheels, enemies[i]->wheels_shader, enemies[i]->wheels_color, enemies[i]->lifes, modelMatrix, camera_view);

        modelMatrix = glm::translate(modelMatrix, ((TANK_TURRET_DISPL) * (TANK_SCALE_FACTOR)) * glm::vec3(1, 0, 0));
        modelMatrix = glm::rotate(modelMatrix, enemies[i]->turret_shooter_angle_right, glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, -((TANK_TURRET_DISPL) * (TANK_SCALE_FACTOR)) * glm::vec3(1, 0, 0));

        // RENDER TURRET
        RenderSimpleMesh(enemies[i]->turret, enemies[i]->turret_shader, enemies[i]->turret_color, enemies[i]->lifes, modelMatrix, camera_view);

        // RENDER TURRET SHOOTER
        RenderSimpleMesh(enemies[i]->turret_shooter, enemies[i]->turret_shooter_shader, enemies[i]->turret_shooter_color, enemies[i]->lifes, modelMatrix, camera_view);

        // INCREASE TIMER UNTIL ENEMY IS ALLOWED TO SHOOT AGIAN
        enemies[i]->timeToShoot += deltaTimeSeconds;

        // RENDER BULLETS IF EXISTS
        DrawBullet(deltaTimeSeconds, enemies[i], camera_view);
    }
}

// FUNCTION THAT SIMULATES MOVEMENT OF AN ENEMY
void Tema2::simulateMovement(Tank *e, int idx ,float deltaTimeSeconds)
{
    // INCREASE TIMER UNTIL ENEMY SHOULD ROTATE AGAIN
    timersToRotate[idx] += deltaTimeSeconds;

        // CHECK IF IS THE TIME TO ROTATE
        // ROTATE FOR MAX 2 SECONDS
        if (timersToRotate[idx] >= e->timeToRotate && timersToRotate[idx] <= e->timeToRotate + 2)
        {
            if (e->rotationSense == 0)
            {
                float angle = RADIANS(rand() % 45) * deltaTimeSeconds;
                e->body_angle += angle;
            }
            else
            {
                float angle = RADIANS(rand() % 45) * deltaTimeSeconds;
                e->body_angle -= angle ;
            }

            if (timersToRotate[idx] >= e->timeToRotate + 1.88)
            {
                timersToRotate[idx] = 0;
                e->rotationSense = rand() % 2;
            }

        } else {    // KEEP MOVE FORWARD
            e->moveForward((ENEMIES_SPEED), deltaTimeSeconds);
        }
}

// FUNCTION THAT FOLLOWS AND ATTACK MAIN PLAYER TANK BY THE TURRET
void Tema2::attackMainTank(Tank *t, Tank *e, float deltaTimeSeconds)
{
    // GET DISTANCE BETWEEN MAIN TANK AND CURRENT ENEMENY
    float distance = glm::distance(
        t->position, e->position
    );

    // ACCEPT A MAXIMUM DISTANCE OF 10 UNITS
    if (distance <= 10.0f)
    {
        // GET CURRENT POSITION OF THE SHOOTER
         glm::vec2 e_pos_present = glm::vec2(e->position.x, e->position.z) + ROTATION_2D_MATRIX_CLOCK(e->body_angle) * ROTATION_2D_MATRIX_CLOCK(e->turret_shooter_angle_right) * glm::vec2((TANK_TURRET_SHOOTER_DIM.x), 0);

        // GET NEXT SHOOTER POSITION IF ROTATTED BY RADIANS(60) * deltaTimeSeconds
        glm::vec2 e_pos_next = glm::vec2(e->position.x, e->position.z) + ROTATION_2D_MATRIX_CLOCK(-RADIANS(60) * deltaTimeSeconds) * ROTATION_2D_MATRIX_CLOCK(e->body_angle) * ROTATION_2D_MATRIX_CLOCK(e->turret_shooter_angle_right) * glm::vec2((TANK_TURRET_SHOOTER_DIM.x), 0);

        // GET PREVIOUS SHOOTER POSITION IF ROTATED BY -RADIANS(60) * deltaTimeSecond
         glm::vec2 e_pos_prev = glm::vec2(e->position.x, e->position.z) + ROTATION_2D_MATRIX_CLOCK(RADIANS(60) * deltaTimeSeconds) * ROTATION_2D_MATRIX_CLOCK(e->body_angle) * ROTATION_2D_MATRIX_CLOCK(e->turret_shooter_angle_right) * glm::vec2((TANK_TURRET_SHOOTER_DIM.x), 0);;
        
        // CHECK WHAT POSITION IS CLOSER TO THE TANK
        float distance_present = glm::distance(
            e_pos_present, glm::vec2(t->position.x, t->position.z)
        );
        float distance_next = glm::distance(
            e_pos_next, glm::vec2(t->position.x, t->position.z)
        );
        float distance_prev = glm::distance(
            e_pos_prev, glm::vec2(t->position.x, t->position.z)
        );

        // IF NEXT SHOOTER POSITION MAKES SHOOTER CLOSER TO THE TANK -> ROTATE WITH RADIANS(60) * deltaTimeSeconds
        if (distance_next < distance_present)
        {
            e->turret_shooter_angle_right -= RADIANS(60) * deltaTimeSeconds;
        }
        // IF PREVIOUS SHOOTER POSITION MAKES SHOOTER CLOSER TO THE TANK -> ROTATE WITH -RADIANS(60) * deltaTimeSeconds
        else if (distance_prev < distance_present)
        {
            e->turret_shooter_angle_right += RADIANS(60) * deltaTimeSeconds;
        }
        // ELSE THE SHOOTER IS ENOUGH CLOSE, SHOOT
        else
        {
            // CHECK IF ENEMY TIMER ALLOWS TO SHOOT
            if  (
                contor_until_enemy_allowed_to_shoot >= (LET_ENEMY_START_SHOOT) 
                && e->timeToShoot >= (LET_ENEMY_SHOOT_AGAIN_AFTER)
                )
            {
                if (e->shotNextBullet)
                {                    
                    e->shotBullet(
                        (BLACK_COLOR),      (BULLET_SPEED_ENEMY) * glm::vec3(1, sin(e->turret_shooter_angle_up), 1),
                        "tank_bullet.obj",  PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "models_tema2"),
                        GL_VERTEX_SHADER,   PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "Shaders", "bulletShaders", "VertexShader.glsl"),
                        GL_FRAGMENT_SHADER, PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "Shaders", "bulletShaders", "FragmentShader.glsl")
                    );
                        
                    e->bullet->setAngle(e->turret_shooter_angle_right + e->body_angle);
                    e->bullet->setAngleUp(e->turret_shooter_angle_up);

                    e->shotNextBullet = false;
                    e->timeToShoot = 0;
                }
            }
        }
    }
}

// FUNCTION THAT COMPUTES FACTOR P
glm::vec3 Tema2::getP(float distance, float radius1, float radius2, glm::vec3 position1, glm::vec3 position2)
{
    float P_abs = (radius1 + radius2 - distance);

    glm::vec3 diffCenter = position2 - position1;

    glm::vec3 P = abs(P_abs) * glm::normalize(diffCenter);

    return P;
}

// FUNCTION THAT CHECKS EVERY TYPE COLLISION FOR A TANK
void Tema2::CheckCollision(Tank *t)
{
    //CHECK FOR COLLISION WITH BUILDING
    CheckBuildingCollision(t);
    
    //CHECK FOR COLLISION WITH WALLS
    CheckWallCollision(t); 

    // CHECK FOR COLLISION WITH TOWERS
    CheckTowerCollision(t);

    // CHECK FOR TANK COLLISION WITH OTHER TANK
    CheckTankCollision(t);
}

// FUNCTION THAT CHECKS AND APPLIES COLLISION CASE
void Tema2::ApplyCollisionCase(float radius1, float radius2, glm::vec3 position1, glm::vec3 position2, Tank *t)
{
    float distance = glm::distance(
            position1, position2
        );

    if (distance < radius1 + radius2)
    {
        glm::vec3 P = getP(
            distance, radius1, radius2, position1, position2
        );

        t->position += P * ((P_MULTIPLY_FACTOR));

        if (t == tank)
        {
            camera->position += P * ((P_MULTIPLY_FACTOR));
            camera_minimap->position += P * ((P_MULTIPLY_FACTOR));
        }
    }
}

// FUNCTION THAT CHECKS IF TANK COLLIDED WITH BUILDING
void Tema2::CheckBuildingCollision(Tank *t)
{
    for (int i = 0; i < buildings_no; i++)
    {
        float radius1 = ((float)((BUILDING_DIAMETER)   / 2) * (BUILDING_SCALE_FACTOR));
        float radius2 = ((float)((TANK_DIAMETER)       / 2) * (TANK_SCALE_FACTOR));

        glm::vec3 position1 = buildings_pos[i];
        glm::vec3 position2 = t->position;

        ApplyCollisionCase(radius1, radius2, position1, position2, t);
    }
}

// FUNCTION THAT CHECKS IF TANK COLLIDED WITH THE BORDERS
void Tema2::CheckWallCollision(Tank *t)
{
    for (int i = 0; i < (WALLS_EACH_SIDE); i++)
    {
        for (int j = 0; j < WALLS_EACH_SIDE; j++)
        {
            modelMatrix = glm::rotate(glm::mat4(1), RADIANS((90 * i)) ,glm::vec3(0, 1, 0));
            modelMatrix = glm::translate(modelMatrix, glm::vec3(23.8 - (j * 1.51), 0.03, (PLANE_SIZE / 2) + 1));
            
            float radius1 = ((float)((WALL_DIAMETER)    / 2) * (WALL_SCALE_FACTOR));
            float radius2 = ((float)((TANK_DIAMETER)    / 2) * (TANK_SCALE_FACTOR));

            glm::vec3 position1 = glm::vec3(modelMatrix[3]);
            glm::vec3 position2 = t->position;

            ApplyCollisionCase(radius1, radius2, position1, position2, t);
        }
    }        
}

// FUNCTION THAT CHECKS IF TANK COLLIDED WITH THE TOWER
void Tema2::CheckTowerCollision(Tank *t)
{
    for (int i = 0; i < TOWERS_NO; i++)
    {
        float radius1 = ((float)((TOWER_DIAMETER)   / 2) * (TOWER_SCALE_FACTOR));
        float radius2 = ((float)((TANK_DIAMETER)    / 2) * (TANK_SCALE_FACTOR));

        glm::vec3 position1 = glm::vec3(towers_position[i]);
        glm::vec3 position2 = t->position;

        ApplyCollisionCase(radius1, radius2, position1, position2, t);

    }
}

// FUNCTION THAT CHECKS IF TANK COLLIDED WITH ANOTHER TANK
void Tema2::CheckTankCollision(Tank *t)
{
    for (int i = 0; i < enemiesNo; i++)
    {
        if (t != enemies[i])
        {
            float radius1 = ((float)(TANK_DIAMETER  / 2) * TANK_SCALE_FACTOR);
            float radius2 = ((float)(TANK_DIAMETER  / 2) * TANK_SCALE_FACTOR);

            glm::vec3 position1 = enemies[i]->position;
            glm::vec3 position2 = t->position;

            ApplyCollisionCase(radius1, radius2, position1, position2, t);
        }
    }
}

void Tema2::FrameEnd()
{
}

// FUNCTION THAT RENDER MESHES
void Tema2::RenderSimpleMesh(Mesh *mesh, Shader *shader, glm::vec3 color, int lifes, const glm::mat4 &modelMatrix, implemented_tema2::Camera *camera_view)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    shader->Use();

    // MVP
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera_view->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // GAME DATA
    int location_lifes = glGetUniformLocation(shader->GetProgramID(), "MeshLifes");
    glUniform1i(location_lifes, lifes);

    int location_color = glGetUniformLocation(shader->GetProgramID(), "MeshColor");
    glUniform3fv(location_color, 1, glm::value_ptr(color));

    int location_time = glGetUniformLocation(shader->GetProgramID(), "Time_now");
    float time = Engine::GetElapsedTime();
    glUniform1f(location_time, time);

    // LIGHTING
    int loc_light_position = glGetUniformLocation(shader->program, "light_position");
    glUniform3fv(loc_light_position, 1, glm::value_ptr(lightPosition));

    glm::vec3 eyePosition = camera->position;
    int loc_eye_position = glGetUniformLocation(shader->program, "eye_position");
    glUniform3fv(loc_eye_position, 1, glm::value_ptr(eyePosition));

    int loc_materialShininess = glGetUniformLocation(shader->program, "material_shininess");
    glUniform1i(loc_materialShininess, materialShininess);

    int loc_materialKd = glGetUniformLocation(shader->program, "material_kd");
    glUniform1f(loc_materialKd, materialKd);

    int loc_materialKs = glGetUniformLocation(shader->program, "material_ks");
    glUniform1f(loc_materialKs, materialKs);

    int loc_Color = glGetUniformLocation(shader->program, "object_color");
    glUniform3fv(loc_Color, 1, glm::value_ptr(color));

    mesh->Render();
}

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    // TANK, LIGHT AND CAMERA MOVES FORWARD
    if (window->KeyHold(GLFW_KEY_W))
    {
        tank->position += ROTATION_3D_MATRIX_CLOCK_OY(-tank->body_angle) * (TANK_SPEED) * deltaTime * glm::vec3(1, 0, 0);

        camera->MoveForward((TANK_SPEED) * deltaTime);

        camera_minimap->MoveForwardM((TANK_SPEED) * deltaTime);

        lightPosition = tank->position + (LIGHT_RELATIVE_POSITION_TO_TANK);
    }

    // TANK, LIGHT AND CAMERA ROTATES LEFT
    if (window->KeyHold(GLFW_KEY_A))
    {
        tank->body_angle += RADIANS(TANK_CAMERA_ROTATION_ANGLE) * deltaTime;

        camera->RotateThirdPerson_OY_view(RADIANS(TANK_CAMERA_ROTATION_ANGLE) * deltaTime);
        camera->RotateThirdPerson_OY_position(RADIANS(TANK_CAMERA_ROTATION_ANGLE) * deltaTime);

        camera_minimap->RotateThirdPerson_OY_position(RADIANS(TANK_CAMERA_ROTATION_ANGLE) * deltaTime);
        camera_minimap->RotateThirdPerson_OY_view(RADIANS(TANK_CAMERA_ROTATION_ANGLE) * deltaTime);
    }

    // TANK, LIGHT AND CAMERA MOVES BACKWARD
    if (window->KeyHold(GLFW_KEY_S))
    {
        tank->position -= ROTATION_3D_MATRIX_CLOCK_OY(-tank->body_angle) * (TANK_SPEED) * deltaTime * glm::vec3(1, 0, 0);

        camera->MoveForward(-(TANK_SPEED) * deltaTime);

        camera_minimap->MoveForwardM(-(TANK_SPEED) * deltaTime);

        lightPosition = tank->position + (LIGHT_RELATIVE_POSITION_TO_TANK);
    }

    // TANK, LIGHT AND CAMERA ROTATES RIGHT
    if (window->KeyHold(GLFW_KEY_D))
    {
        tank->body_angle += -RADIANS(TANK_CAMERA_ROTATION_ANGLE) * deltaTime;

        camera->RotateThirdPerson_OY_view(-RADIANS(TANK_CAMERA_ROTATION_ANGLE) * deltaTime);
        camera->RotateThirdPerson_OY_position(-RADIANS(TANK_CAMERA_ROTATION_ANGLE) * deltaTime);

        camera_minimap->RotateThirdPerson_OY_view(-RADIANS(TANK_CAMERA_ROTATION_ANGLE) * deltaTime);
        camera_minimap->RotateThirdPerson_OY_position(-RADIANS(TANK_CAMERA_ROTATION_ANGLE) * deltaTime);
    }
}

void Tema2::OnKeyPress(int key, int mods)
{
    // Add key press event
}

void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // IF MOUSE RIGHT NOT PRESSED, ROTATE TURRET
    if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        tank->turret_shooter_angle_right += -RADIANS(6 * (TURRET_ROTATION_SENSITIVITY) ) * deltaX;

        if  (
                (tank->turret_shooter_angle_up <= RADIANS(MAX_TURRET_UP_ANGLE) && deltaY < 0) ||
                (tank->turret_shooter_angle_up >= RADIANS(MAX_TURRET_DOWN_ANGLE) && deltaY > 0)
            )
        {
            tank->turret_shooter_angle_up += -RADIANS(5 * (TURRET_ROTATION_SENSITIVITY) ) * deltaY;   
        }
    } 
    else // IF MOUSE RIGHT IS PRESSED, ROTATE CAMERA VIEW
    {
        camera->RotateThirdPerson_OY_view(-RADIANS(CAMERA_ROTATION_ANGLE * (TURRET_ROTATION_SENSITIVITY)) * deltaX);
    }   
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // IF LEFT MOUSE BUTTON IS PRESSED, PLAYER WANTS TO SHOOT
    if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT))
    {
        if (tank->shotNextBullet && tank->timeToShoot >= (LET_TANK_SHOOT_AGAIN_AFTER))
        {
            tank->timeToShoot = 0;
            
            tank->shotBullet(
                (BLACK_COLOR),      (BULLET_SPEED_TANK) * glm::vec3(1, sin(tank->turret_shooter_angle_up), 1),
                "tank_bullet.obj",  PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "models_tema2"),
                GL_VERTEX_SHADER,   PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "Shaders", "bulletShaders", "VertexShader.glsl"),
                GL_FRAGMENT_SHADER, PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "Shaders", "bulletShaders", "FragmentShader.glsl")
            );
                
            tank->bullet->setAngle(tank->turret_shooter_angle_right + tank->body_angle);
            tank->bullet->setAngleUp(tank->turret_shooter_angle_up);

            tank->shotNextBullet = false;
        }
    }
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
}
