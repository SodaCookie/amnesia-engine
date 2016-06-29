#include "SDL.h"
#include "SDL_render.h"
#include "SDL_rect.h"
#include "../amnesia/classes/lightsource.h"
#include <vector>

#ifdef main
# undef main
#endif /* main */

int main(int argc, char *argv[]) {
    SDL_Surface* screen;
    //Start
    SDL_Init(SDL_INIT_EVERYTHING);

    // Create scene
    LightSource light = LightSource(Vector(320, 240), 100);
    std::vector<Polygon> shapes = std::vector<Polygon>();
    std::vector<Vector> view_points
        {Vector(0, 0), Vector(640, 0), Vector(640, 480), Vector(0, 480)};
    std::vector<Vector> square_points
        {Vector(100, 100), Vector(100, 200), Vector(200, 200), Vector(200, 100)};
    Polygon square = Polygon(square_points);
    shapes.push_back(square);
    Polygon view = Polygon(view_points);

    auto blocks = light.process(shapes, view);

    //Set up screen
    SDL_Window *win = SDL_CreateWindow(
        "Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);

    SDL_Renderer *ren = SDL_CreateRenderer(
        win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);
    SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);

    for (Polygon block : blocks) {
        std::vector<SDL_Point> points = std::vector<SDL_Point>();
        for (Vector point : block.get_vertices()) {
            SDL_Point spoint = {(int)point.x, (int)point.y};
            points.push_back(spoint);
        }
        SDL_RenderDrawLines(ren, points.data(), points.size());
    }

    SDL_RenderPresent(ren);

    SDL_Delay(10000);
    SDL_Quit();

    return 0;
}