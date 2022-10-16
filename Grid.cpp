#include<iostream>
#include<vector>
#include"Grid.h"

std::vector<linesClass> Lines;
std::vector<pointClass> Points;

// Construct the grid

Grid::Grid(){cnt=0;}

//Destroy the grid

Grid::~Grid(){}

//Initialize window drawing systems

void Grid::init(const char* title,int x,int y,int width,int height,bool fullscreen){

    int flags=0;
    if(fullscreen)
        flags=1;

    if(SDL_Init(SDL_INIT_EVERYTHING)==0){

        std::cout<<"Subsystems Initialized !...\n";

        window= SDL_CreateWindow(title,x,y,width,height,flags);

        if(window)
            std::cout<<"Window Created !...\n";
        
        renderer= SDL_CreateRenderer(window,-1,0);

        if(renderer){
            std::cout<<"Renderer Created !..."<<std::endl;

        }

        isRunning=true;

    }

    else{
        std::cout<<"Error :"<<SDL_GetError()<<std::endl;
        isRunning=false;
    }
}

//handle user events like keypresses

void Grid::handle(){

    SDL_Event event;
    SDL_Delay(10);
        SDL_PollEvent(&event);
        
        switch (event.type){

            case SDL_QUIT:
                isRunning=false;
                break;
            // TODO input handling code goes here

            //This is will record the mouse click and draw the line

            case SDL_MOUSEBUTTONDOWN:
                
                switch (event.button.button){
                    case SDL_BUTTON_LEFT:
                        drawing = true;
                }
                break;

            case SDL_MOUSEBUTTONUP:
                switch (event.button.button){

                    case SDL_BUTTON_LEFT:
                      //  drawing = false;
                        break;
                }
                break;
        }

}

//update section for objects with changing states

void Grid::update(){}


//Render or draw the new changes on the screen

void Grid::render(){

     if(renderer){

    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);

    //this is where the magic happens

    if(drawing){
            for(auto i=Lines.begin();i!=Lines.end();i++){
                linesClass c=(*i);
                SDL_SetRenderDrawColor(renderer,0,0,255,255);
                SDL_RenderDrawLine(renderer,c.LineHX1,c.LineHY,c.LineHX2,c.LineHY);
                SDL_RenderDrawLine(renderer,c.LineVX,c.LineVY1,c.LineVX,c.LineVY2);
                drawing=1;       
            }
            for(auto j=Points.begin();j!=Points.end();j++){
                pointClass c=(*j);
                SDL_SetRenderDrawColor(renderer,255,255,0,255);
                DrawCircle(renderer,c.X,c.Y,3);   
            }

    }

    SDL_RenderPresent(renderer);

        }
    
}

//Garbage collection and clean up

void Grid::clean(){

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    std::cout<<"Window and Subsystems Terminated !...\n";
}