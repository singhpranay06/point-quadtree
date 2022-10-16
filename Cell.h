#include<SDL2/SDL.h>
class Cell{

    public:
        int X,Y,xIN,yIN;
        int limHX1,limHX2,limHY,limVY1,limVY2,limVX,quadrant,count;
        int8_t belongsTo;
        Cell *parent,*quadI=NULL,*quadII=NULL,*quadIII=NULL,*quadIV=NULL;
        bool isDrawn,isFull,gridMade;    
        Cell();
        Cell(int xCoordinate,int yCoordinate);  

};

class linesClass{
    public:
        int X,Y,LineHX1,LineHX2,LineHY,LineVX,LineVY1,LineVY2;
        linesClass();
};

class pointClass{
    public:
        int X,Y;
        pointClass();
};

//custom datatype for quadtree pointer declarations
typedef Cell *NODE;

//function for inserting the new points
NODE insert(NODE locMother,NODE root,int xCoordinate,int yCoordinate,int quad);

// Create a node
NODE newNode(NODE,int,int ,int);

//Driver function that handles user input and quadtree functions
void mainDriver();

//Function for drawing circles using Midpoint circle algo 
void DrawCircle(SDL_Renderer * renderer, int32_t centreX, int32_t centreY, int32_t radius);