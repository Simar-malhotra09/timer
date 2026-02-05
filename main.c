#include <stdlib.h>
#include "raylib.h"
#include <stdio.h> 

#define TO_SECS 60 
#define WIDTH 1000/3
#define HEIGHT 500/3
#define NUM_FRAMES 3  

typedef struct{
    Texture2D texture;
    Vector2 position;
    int width;   
    int height; 
} Button;

Button button_new(const char* imagePath, Vector2 imagePosition, float scale){
    Button button;
    Image image = LoadImage(imagePath);
    int originalWidth = image.width;
    int originalHeight = image.height;
    int newWidth = (int)(originalWidth * scale);
    int newHeight = (int)(originalHeight * scale);
    ImageResize(&image, newWidth, newHeight);
    button.texture = LoadTextureFromImage(image);
    UnloadImage(image);
    button.position = imagePosition;
    button.width = newWidth;   
    button.height = newHeight;
    
    return button;  
}

int main(int argc, char* argv[])
{
    InitWindow(WIDTH, HEIGHT, "Timer- Lock in! ");
    InitAudioDevice();
    Sound fxButton = LoadSound("buttonfx.wav");
    
    Button button = button_new("osaka_sticker.jpeg", (Vector2){WIDTH - 100, HEIGHT - 50}, 0.05f);
    
    float frameHeight = (float)button.height / NUM_FRAMES;
    Rectangle sourceRec = { 0, 0, (float)button.width, frameHeight };
    Rectangle btnBounds = {
        button.position.x - button.width ,   
        button.position.y - frameHeight,     
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
        
        double elapsed = pause ? pausedElapsed : GetTime() - startTime;
        double remaining = TIME_SCHEDULED_SEC - elapsed;
        if (remaining < 0) remaining = 0;
        
        snprintf(text, sizeof(text), "Time left: %.0f s", remaining);
        
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText(text, WIDTH / 2 - 75, HEIGHT / 2, 20, BLACK);
            DrawTextureRec(button.texture, sourceRec, (Vector2){ btnBounds.x, btnBounds.y }, WHITE);
        EndDrawing();
    }
    
    UnloadTexture(button.texture);  
    UnloadSound(fxButton);
    CloseAudioDevice();
    CloseWindow();
    
    return 0;
}
