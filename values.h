#ifndef GAME_VALUES
#define GAME_VALUES

#define ROTATION_2D_MATRIX_CLOCK(angle) (glm::mat2(cos(angle), -sin(angle), sin(angle), cos(angle)))
#define ROTATION_2D_MATRIX_ANTICLOCK(angle) (glm::mat2(cos(angle), sin(angle), -sin(angle), cos(angle)))

#define ROTATION_3D_MATRIX_CLOCK_OY(angle) (glm::mat3(cos(angle), 0, sin(angle), 0, 1, 0, -sin(angle), 0, cos(angle)))
#define ROTATION_3D_MATRIX_CLOCK_OZ(angle) (glm::mat3(cos(angle), -sin(angle), 0, sin(angle), cos(angle), 0, 0, 0, 1))

#define PLANE_SIZE 50

#define OBJECTS_TRANSLATE_OY (0.03f)

// LIGHT POSITION COMPARED TO THE TANK
#define LIGHT_RELATIVE_POSITION_TO_TANK (glm::vec3(-2, 5, 0))

// TANK INITIAL LIFE
#define TANK_INITIAL_LIFES (3)
#define DEFAULT_OBJECT_NO_LIFE (3)

// TANK PARTS DIMENSIONS
#define TANK_BODY_DIM (glm::vec3(9.64f, 3.99f, 6.17f))
#define TANK_TURRET_SHOOTER_DIM (glm::vec3(6.43f, 0.603f, 0.603f))
#define TANK_TURRET_DIM (glm::vec3(3.33f, 1.2f, 1.94f))
#define TANK_BULLET_DIM (glm::vec3(0.5f, 0.5f, 0.5f))

// TANK PARTS DISPLACEMENT FROM ORIGIN
#define TANK_BODY_DISPL (glm::vec3(0.0f, 1.0f, 0.0f))
#define TANK_TURRET_SHOOTER_DISPL (glm::vec3(0.0f, 4.75f, 0.0f))
#define TANK_TURRET_DISPL (glm::vec3(0.0f, 4.76f, 0.0f))
#define TANK_BULLET_DISPL (glm::vec3(5.4f, 4.76f, 0.0f))

// OBJECTS DIMENSIONS
#define BUILDING_DIM (glm::vec3(10.f, 16.5f, 10.f))
#define BUILDING_DISPL (glm::vec3(0.0f, 5.0f, 0.0f))
#define TOWER_DIM (glm::vec3(10.0f, 21.1f, 10.0f))
#define TOWER_DISPL (glm::vec3(0.0f, 0.5f, 0.0f))

#define TTL_BULLET (2)
#define BULLET_SPEED_TANK (glm::vec3(15.0f, 12.0f, 15.0f))
#define BULLET_SPEED_ENEMY (glm::vec3(10.0f, 10.0f, 10.0f))

// NUMBER OF DIFFERENT OBJECTS
#define BUILDINGS_NO (5)
#define TOWERS_NO (4)
#define WALL_SIDES (4)
#define WALLS_EACH_SIDE (32)

// TANK SPEED
#define TANK_SPEED (3.0f)
#define ENEMIES_SPEED (1.0f)

// SCALE FACTORS
#define TANK_SCALE_FACTOR (0.2f)
#define WALL_SCALE_FACTOR (1.0f)
#define TOWER_SCALE_FACTOR (0.2f)
#define BUILDING_SCALE_FACTOR (0.2f)

// DATA FOR COLLISION
#define TANK_DIAMETER (11.4f)
#define WALL_DIAMETER (3.0f)
#define TOWER_DIAMETER (10.5f)
#define BUILDING_DIAMETER (14.1f)

// TURRET ROTATION
#define TURRET_ROTATION_SENSITIVITY (0.005f)
#define MAX_TURRET_UP_ANGLE (25.0f)
#define MAX_TURRET_DOWN_ANGLE (-5.0f)

#define P_MULTIPLY_FACTOR (0.5f)

#define TANK_CAMERA_ROTATION_ANGLE (75)
#define CAMERA_ROTATION_ANGLE (30)
#define FOV_CAMERA (RADIANS(60))
#define WIDTH_ORTHO (7.0f)
#define HEIGHT_ORTHO (7.0f)


#define LET_ENEMY_START_SHOOT (10)
#define LET_ENEMY_SHOOT_AGAIN_AFTER (5)
#define LET_TANK_SHOOT_AGAIN_AFTER (2)

#define MINIMUM_BUILDINGS_ON_MAP (6)
#define MAXIMUM_BUILDINGS_ON_MAP (10)

#endif