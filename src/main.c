#include <raylib.h>

int main ()
{
    InitWindow(800, 400, "Hello World");
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        DrawFPS(0, 0);
        EndDrawing();
    }
    CloseWindow();
	return 0;
}
