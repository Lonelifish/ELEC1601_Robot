#include "stdio.h"
#include "stdlib.h"
#include "sdl.h"
#include "SDL2_gfxPrimitives.h"
#include "time.h"

#include "formulas.h"
#include "wall.h"
#include "robot.h"

int done = 0;


int main(int argc, char *argv[]) {
    SDL_Window *window;
    SDL_Renderer *renderer;

    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        return 1;
    }

    window = SDL_CreateWindow("Robot Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, OVERALL_WINDOW_WIDTH, OVERALL_WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    window = SDL_CreateWindow("Robot Maze", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, OVERALL_WINDOW_WIDTH, OVERALL_WINDOW_HEIGHT, SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, 0);

    struct Robot robot;
    struct Wall_collection *head = NULL;
    int front_left_sensor, front_right_sensor, right_sensor, left_sensor=0;
    clock_t start_time, end_time;
    int msec;

    // SETUP MAZE
    // You can create your own maze here. line of code is adding a wall.
    // You describe position of top left corner of wall (x, y), then width and height going down/to right
    // Relative positions are used (OVERALL_WINDOW_WIDTH and OVERALL_WINDOW_HEIGHT)
    // But you can use absolute positions. 10 is used as the width, but you can change this.
    int i;
    insertAndSetFirstWall(&head, 12,  640-10-120, 450, 10, 30);
    insertAndSetFirstWall(&head, 12,  640-10-220, 450, 10, 30);

    for (i = 0; i < 100; i++){
        insertAndSetFirstWall(&head, i,  640-10-(20 + i) , 350 + i, 10, 10); //1
        insertAndSetFirstWall(&head, i,  640-10-(20 +100 + i) , 350 + i, 10, 10); //1
    }
    insertAndSetFirstWall(&head, 12,  640-10-20, 280, 10, 70);
    insertAndSetFirstWall(&head, 12,  640-10-120, 280, 10, 70);

    for (i = 0; i < 180; i++){
        insertAndSetFirstWall(&head, i,  640-10-(20 +190 - i/2) , 100 + i, 10, 10); //1
    }
    for (i = 0; i < 105; i++){
        insertAndSetFirstWall(&head, i,  640-10-(20 +105/2 - i/2) , 175 + i, 10, 10); //1
    }


    insertAndSetFirstWall(&head, 2,  640-105/2-20, 175, 105/2, 10);
    insertAndSetFirstWall(&head, 2,  640-10-20, 20, 10, 155);
    insertAndSetFirstWall(&head, 2,  640-300-20, 20, 300, 10);
    insertAndSetFirstWall(&head, 2,  640-10-320, 20, 10, 60);
    insertAndSetFirstWall(&head, 2,  640-130-80, 100, 130, 10);
    insertAndSetFirstWall(&head, 2,  640-10-80, 80, 10, 20);
    insertAndSetFirstWall(&head, 2,  640-160-80, 80, 160, 10);


    double j;
    for (i = 0; i < 50; i++){
        j = i;
        insertAndSetFirstWall(&head, i+1,
                              // the most important bit is below.
                              // increase the 20 for a tighter bend
                              // descrease for a more meandering flow
                              640-10-(320 + 30*sin(10*j * M_PI/180)),
                              // increase the 5 for a spacier curve
                              (i * 5)+80,
                              10, 10);
    }
    for (i = 0; i < 75; i++){
        j = i;
        insertAndSetFirstWall(&head, i+1,
                              // the most important bit is below.
                              // increase the 20 for a tighter bend
                              // descrease for a more meandering flow
                              640-10-(240 + 30*sin(10*j * M_PI/180)),
                              // increase the 5 for a spacier curve
                              (i * 5)+80,
                              10, 10);
    }

    insertAndSetFirstWall(&head, 2,  640-105-345, 330, 105, 10);
    insertAndSetFirstWall(&head, 2,  640-10-450, 190, 10, 150);
    insertAndSetFirstWall(&head, 2,  640-70-380, 190, 70, 10);
    insertAndSetFirstWall(&head, 2,  640-10-380, 20, 10, 170);
    insertAndSetFirstWall(&head, 2,  640-260-380, 20, 260, 10);

    insertAndSetFirstWall(&head, 2,  640-345-255, 455, 345, 10);
    insertAndSetFirstWall(&head, 2,  640-10-600, 100, 10, 365);
    insertAndSetFirstWall(&head, 2,  640-70-530, 100, 70, 10);
    insertAndSetFirstWall(&head, 2,  640-10-530, 80, 10, 20);
    insertAndSetFirstWall(&head, 2,  640-110-530, 80, 110, 10);
// For the robot


    setup_robot(&robot);
    updateAllWalls(head, renderer);
    SDL_Event event;
    while(!done){
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
        SDL_RenderClear(renderer);

        //Move robot based on user input commands/auto commands

        if (robot.auto_mode == 1)
            robotAutoMotorMove(&robot, front_left_sensor, front_right_sensor, right_sensor, left_sensor);
        robotMotorMove(&robot);

         //Check if robot reaches endpoint. and check sensor values

//        if (checkRobotReachedEnd(&robot, 640, 340, 10, 100)){ //Maze 1
//            end_time = clock();
//            msec = (end_time-start_time) * 1000 / CLOCKS_PER_SEC;
//            robotSuccess(&robot, msec);
//        }


//        if (checkRobotReachedEnd(&robot, 220, 480, 100, 10)){//Maze 2
//            end_time = clock();
//            msec = (end_time-start_time) * 1000 / CLOCKS_PER_SEC;
//            robotSuccess(&robot, msec);
//        }


//        if (checkRobotReachedEnd(&robot, 0, 340, 10, 100)){ // Maze 3
//            end_time = clock();
//            msec = (end_time-start_time) * 1000 / CLOCKS_PER_SEC;
//            robotSuccess(&robot, msec);
//        }

//
//        if (checkRobotReachedEnd(&robot, 640-10-320, 480, 100, 10)){ //Maze 4
//            end_time = clock();
//            msec = (end_time-start_time) * 1000 / CLOCKS_PER_SEC;
//            robotSuccess(&robot, msec);
//        }


//        if (checkRobotReachedEnd(&robot, 640, 20, 10, 60)){ //Maze 5
//            end_time = clock();
//            msec = (end_time-start_time) * 1000 / CLOCKS_PER_SEC;
//            robotSuccess(&robot, msec);
//        }
//        if (checkRobotReachedEnd(&robot, 120, 480, 100, 10)){ //Maze 6
//            end_time = clock();
//            msec = (end_time-start_time) * 1000 / CLOCKS_PER_SEC;
//            robotSuccess(&robot, msec);
//        }
//        if (checkRobotReachedEnd(&robot, 0, 20, 10, 60)){ //Maze 7
//            end_time = clock();
//            msec = (end_time-start_time) * 1000 / CLOCKS_PER_SEC;
//            robotSuccess(&robot, msec);
//        }
        if (checkRobotReachedEnd(&robot, 640-10-220, 480, 100, 10)){ //Maze 8
            end_time = clock();
            msec = (end_time-start_time) * 1000 / CLOCKS_PER_SEC;
            robotSuccess(&robot, msec);
        }
        else if(checkRobotHitWalls(&robot, head))
            robotCrash(&robot);
        //Otherwise compute sensor information
        else {
            front_left_sensor = checkRobotSensorFrontLeftAllWalls(&robot, head);
            if (front_left_sensor>0)
                printf("Getting close on the Front left. Score = %d\n", front_left_sensor);
               // delay(1000);

            right_sensor = checkRobotSensorRightAllWalls(&robot, head);
            if (right_sensor>0)
                printf("Getting close on the Right. Score = %d\n", right_sensor);
               // delay(1000);

            left_sensor = checkRobotSensorLeftAllWalls(&robot, head);
            if (left_sensor>0)
                printf("Getting close on the Left. Score = %d\n", left_sensor);
               // delay(1000);

            front_right_sensor = checkRobotSensorFrontRightAllWalls(&robot, head);
            if (front_right_sensor>0)
                printf("Getting close on the Front right. Score = %d\n", front_right_sensor);
               // delay(1000);
        }
        robotUpdate(renderer, &robot);
        updateAllWalls(head, renderer);

        // Check for user input
        SDL_RenderPresent(renderer);
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                done = 1;
            }
            const Uint8 *state = SDL_GetKeyboardState(NULL);
            if(state[SDL_SCANCODE_UP] && robot.direction != DOWN){
                robot.direction = UP;
            }
            if(state[SDL_SCANCODE_DOWN] && robot.direction != UP){
                robot.direction = DOWN;
            }
            if(state[SDL_SCANCODE_LEFT] && robot.direction != RIGHT){
                robot.direction = LEFT;
            }
            if(state[SDL_SCANCODE_RIGHT] && robot.direction != LEFT){
                robot.direction = RIGHT;
            }
            if(state[SDL_SCANCODE_SPACE]){
                setup_robot(&robot);
            }
            if(state[SDL_SCANCODE_RETURN]){
                robot.auto_mode = 1;
                start_time = clock();
            }
        }

        SDL_Delay(120);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    printf("DEAD\n");
}
