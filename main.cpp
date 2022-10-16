#include<iostream>
#include"Grid.h"

Grid *grid=nullptr;

int main(int argc,char * argv[]){

    //Handles user input loop, nodes creation and coordinate calculation
    mainDriver();

    grid=new Grid();
    
    grid->init("QUADTREES",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600,false);

    const int frameDelay = 1000/60;

    Uint32 frameStart;
    int frameTime;

    while(grid->running()){

        frameStart = SDL_GetTicks();

        grid->handle();
        grid->update();
        grid->render();

        frameTime=frameStart - SDL_GetTicks();
        if(frameDelay>frameTime)
            SDL_Delay(frameDelay-frameTime);

    }

    grid->clean();

    return EXIT_SUCCESS;
}