#include"Cell.h"
#include<iostream>
#include<vector>
#include<math.h>
#include<time.h>
#include<cstdlib>


//local declaration for 'Lines' vector, its initialization is in Grid.cpp 
extern std::vector<linesClass> Lines;

//local declaration for 'Points' vector, its initialization is in Grid.cpp 
extern std::vector<pointClass> Points;

//default constructor for Cell class
Cell::Cell(){}


//definition of parameterized constructor of Cell class
Cell::Cell(int a,int b){

   xIN=a;yIN=b;

   // BELOW, THE INPUT COORDINATES OF INDIVIDUAL POINTS ARE BEING TRANSFORMED TO CUSTOM PLANE OF 800 X 600 

   if(xIN==0&&yIN==0){
        X=400;
        Y=300;
        
   }
   else{
        X=400+xIN;

        if(yIN>=0)
            Y=300-(yIN);
        else
            Y=300+(-yIN);
   }
  // std::cout<<"Transformed Values: "<<X<<" | "<<Y<<"\n";
   isFull=true;

}

//defintion of constructor of linesClass
linesClass::linesClass(){};

pointClass::pointClass(){};   

// Create a node
NODE newNode(NODE locMother,int a,int b,int QUAD) {
  NODE q = new Cell(a,b); 
   q->isFull=true;
   q->quadI=q->quadII=q->quadIII=q->quadIV=NULL;
   q->parent=locMother;
   q->quadrant=QUAD;
   q->count=0;
   q->gridMade=false;

   if(locMother!=NULL)
    locMother->count++
    // ,std::cout<<"Parent Count :"<<locMother->count<<"\n"
    ;

switch(QUAD){
  case -1:
          q->quadrant=-1;
          q->limHX1=0;
          q->limHX2=800;
          q->limHY=300;
          q->limVX=400;
          q->limVY1=0;
          q->limVY2=600;
          break;
  case 1:
          q->limHX1=locMother->X;;
          q->limHX2=locMother->limHX2;
          q->limHY=q->Y;
          q->limVX=q->X;
          q->limVY1=locMother->limVY1;
          q->limVY2=locMother->Y;;
          break;
  case 2:
          q->limHX1=locMother->limHX1;
          q->limHX2=locMother->X;
          q->limHY=q->Y;
          q->limVX=q->X;
          q->limVY1=locMother->limVY1;
          q->limVY2=locMother->Y;
          break;
  case 3:
          q->limHX1=locMother->limHX1;
          q->limHX2=locMother->X;
          q->limHY=q->Y;
          q->limVX=q->X;
          q->limVY1=locMother->Y;
          q->limVY2=locMother->limVY2;
          break;
  case 4:
          q->limHX1=locMother->X;
          q->limHX2=locMother->limHX2;
          q->limHY=q->Y;
          q->limVX=q->X;
          q->limVY1=locMother->Y;
          q->limVY2=locMother->limVY2;
          break;
}
if(locMother!=NULL&&locMother->count>0&&locMother->gridMade==false){
  linesClass lineObj;
  lineObj.LineHX1=locMother->limHX1;
  lineObj.LineHX2=locMother->limHX2;
  lineObj.LineHY=locMother->limHY;
  lineObj.LineVX=locMother->limVX;
  lineObj.LineVY1=locMother->limVY1;
  lineObj.LineVY2=locMother->limVY2;
  Lines.push_back(lineObj);
  locMother->gridMade=true;
  // std::cout<<"||||||||JOB DONE||||||||\n";
}

  pointClass pointObj;
  pointObj.X=q->X;
  pointObj.Y=q->Y;
  Points.push_back(pointObj);
  // std::cout<<"created"<<std::endl;
  return q;
}

//definition for the INSERT function

NODE insert(NODE locMother,NODE first,int a,int b,int QUAD){

    NODE root=first;

    if(root==NULL){
      NODE q=newNode(locMother,a,b,QUAD);
      q->belongsTo=QUAD;
      // std::cout<<"Belongs To: "<<QUAD<<std::endl;
      // std::cout<<"parent details : "<<q->parent->X<<" , "<<q->parent->Y<<std::endl;
      // std::cout<<q->limHX1<<" "<<q->limHX2<<" "<<q->limHY<<" "<<q->limVX<<" "<<q->limVY1<<" "<<q->limVY2<<" \n";
      return q; 
    }
    else if((a>root->xIN)&&(b>root->yIN)){      //for 1st quad
     
      // std::cout<<"in 1"<<std::endl;
      root->quadI=insert(root,root->quadI,a,b,1);

      }
    else if((a<root->xIN)&&(b>root->yIN)){      //for 2nd quad
      
      // std::cout<<"in 2"<<std::endl;
      root->quadII=insert(root,root->quadII,a,b,2);
    
      }
    else if((a<root->xIN)&&(b<root->yIN)){      //for 3rd quad
     
      // std::cout<<"in 3"<<std::endl;
      root->quadIII=insert(root,root->quadIII,a,b,3);

      }
    else if((a==root->xIN)&&(b==root->yIN)){    //duplicate coordinates
      // std::cout<<"duplicates ! try again"<<std::endl;
    }
    else {            
                       
      // std::cout<<"in 4"<<std::endl;     //for 4th quad
      root->quadIV=insert(root,root->quadIV,a,b,4);

      }
    
  return first; 
}

//Definition about the driver function
void mainDriver(){
  int x,y;

	//the starting point or the main central root of the entire quadtree
	NODE ORIGIN=newNode(NULL,0,0,-1);
  NODE q=ORIGIN;
  linesClass lineObj;
  lineObj.LineHX1=q->limHX1;
  lineObj.LineHX2=q->limHX2;
  lineObj.LineHY=q->Y;
  lineObj.LineVX=q->X;
  lineObj.LineVY1=q->limVY1;
  lineObj.LineVY2=q->limVY2;
  Lines.push_back(lineObj);
  q->gridMade=true;

	bool done=false;
	int ch,rnum;

	while(!done){
	std::cout<<"Enter your choice"<<std::endl;
	std::cout<<"1.insert\t2.random generation\t3.exit"<<std::endl;
	std::cin>>ch;
	switch(ch){
	case 1:
		std::cout<<"Enter space separated x and y"<<std::endl;
		std::cin>>x>>y;
		ORIGIN=insert(NULL,ORIGIN,x,y,-1);
		break;
  case 2:
    std::cout<<"How many numbers to generate?\n";
    std::cin>>rnum;
    srand(time(0));
    
    for (int i = 0; i < rnum/4; i++){
        // int random = offset + (rand() % range);
        x=1 + (rand()%399);
        y=1 + (rand()%299);
        ORIGIN=insert(NULL,ORIGIN,x,y,-1);
    }
    for (int i = 0; i < rnum/4; i++){
        // int random = offset + (rand() % range);
        x=-400 + (rand()%400);
        y=1 + (rand()%299);
        ORIGIN=insert(NULL,ORIGIN,x,y,-1);
    }
    for (int i = 0; i < rnum/4; i++){
        // int random = offset + (rand() % range);
        x=-400 + (rand()%400);
        y=-300 + (rand()%300);
        ORIGIN=insert(NULL,ORIGIN,x,y,-1);
    }
    for (int i = 0; i < rnum/4; i++){
        // int random = offset + (rand() % range);
        x=1 + (rand()%399);
        y=-300 + (rand()%300);
        ORIGIN=insert(NULL,ORIGIN,x,y,-1);
    }
    break;
	case 3:
		done=true;
    std::cout<<Lines.size()<<"\n";
		break;
	default:std::cout<<"Wrong choice"<<std::endl;
		}
	}
}

//Function for drawing circles using Midpoint circle algo 
void DrawCircle(SDL_Renderer * renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
   const int32_t diameter = (radius * 2);

   int32_t x = (radius - 1);
   int32_t y = 0;
   int32_t tx = 1;
   int32_t ty = 1;
   int32_t error = (tx - diameter);

   while (x >= y)
   {
      //  Each of the following renders an octant of the circle
      SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

      if (error <= 0)
      {
         ++y;
         error += ty;
         ty += 2;
      }

      if (error > 0)
      {
         --x;
         tx += 2;
         error += (tx - diameter);
      }
   }
}