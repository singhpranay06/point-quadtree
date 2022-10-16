#include"Cell.h"

class Grid{

    private:
        int cnt;
        bool isRunning;
        SDL_Window *window;
        SDL_Renderer *renderer;
        bool drawing;

    public:
        Grid();
        ~Grid();

        void init(const char* title,int x,int y,int width,int height,bool fullscreen);
        void handle();
        void update();
        void render();
        void clean();

        bool running(){
            return isRunning;
        }

};