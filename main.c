
#include <stdlib.h>
#include "raylib.h"
#include <stdio.h> 

#define TO_SECS 60 
#define WIDTH 2000
#define HEIGHT 1000
#define NUM_FRAMES 60

int main(int argc, char* argv[])
{
    InitWindow(WIDTH, HEIGHT, "Timer- Lock in! ");
    InitAudioDevice();      // Initialize audio device

    Sound fxButton = LoadSound("buttonfx.wav");   // Load button sound
    Texture2D button = LoadTexture("button.png"); // Load button texture

    float frameHeight = (float)button.height / NUM_FRAMES;
    Rectangle sourceRec = { 0, 0, (float)button.width, frameHeight };

    Rectangle btnBounds = {
        WIDTH / 2.0f - button.width / 2.0f,
        HEIGHT / 2.0f - frameHeight / 2.0f,
        (float)button.width,
        frameHeight
    };

    int btnState = 0;
    Vector2 mousePoint = { 0.0f, 0.0f };

    SetTargetFPS(60);

    int TIME_SCHEDULED_MIN = 30;
    if (argc > 1) TIME_SCHEDULED_MIN = atoi(argv[1]);

    const double TIME_SCHEDULED_SEC = (double)TIME_SCHEDULED_MIN * TO_SECS;

    double startTime = GetTime();
    double pausedElapsed = 0.0;
    bool pause = false;

    char text[64];

    while (!WindowShouldClose())
    {
        mousePoint = GetMousePosition();

        if (CheckCollisionPointRec(mousePoint, btnBounds))
        {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                PlaySound(fxButton);
                pause = !pause;

                if (pause)
                {
                    pausedElapsed = GetTime() - startTime;
                    btnState = 2;
                }
                else
                {
                    startTime = GetTime() - pausedElapsed;
                    btnState = 0;
                }
            }
        }

        sourceRec.y = btnState * frameHeight;

        double elapsed = pause
            ? pausedElapsed
            : GetTime() - startTime;

        double remaining = TIME_SCHEDULED_SEC - elapsed;
        if (remaining < 0) remaining = 0;

        snprintf(text, sizeof(text), "Time left: %.0f s", remaining);

        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText(text, WIDTH / 2 - 75, HEIGHT / 2, 20, BLACK);
            DrawTextureRec(button, sourceRec, (Vector2){ btnBounds.x, btnBounds.y }, WHITE);
        EndDrawing();
    }

    UnloadTexture(button);
    UnloadSound(fxButton);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
