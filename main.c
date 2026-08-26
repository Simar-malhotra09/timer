#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#include "statusbar.h"

#define IM_IN_PUBLIC 0
#define TO_SECS 60
#define WIDTH 300
#define HEIGHT 160
#define NUM_FRAMES 3

int main(int argc, char *argv[]) {
  InitWindow(WIDTH, HEIGHT, "Time to Lock in!");
  InitAudioDevice();
  StatusBarInit();
  StatusBarSetImage("media/osaka_sticker_re.jpeg");

  Sound fxButton = LoadSound("media/buttonfx.wav");
  Sound fxFinished;
  if (IM_IN_PUBLIC) {
    fxFinished = LoadSound("media/YiYi_opening.mp3");
  } else {
    fxFinished = LoadSound("media/sata-andagi.mp3");
  }

  bool timerEnded = false;
  bool finishedPlayed = false;

  Texture2D pause_button = LoadTexture("media/osaka_sticker_re.jpeg");
  pause_button.height = pause_button.height / 3;
  pause_button.width = pause_button.width / 3;

  printf("Pause button height: %f, Pause button width: %f\n",
         (float)pause_button.height, (float)pause_button.width);

  float frameHeight = (float)pause_button.height;
  printf("Frame height: %f\n", frameHeight);

  Rectangle sourceRec = {0, 0, (float)pause_button.width / 6, frameHeight};
  Rectangle btnBounds = {(float)WIDTH / 2 + (float)WIDTH / 4, (float)HEIGHT / 2,
                         pause_button.width, pause_button.height};

  int btnState = 0;
  Vector2 mousePoint = {0.0f, 0.0f};
  SetTargetFPS(60);

  float TIME_SCHEDULED_MIN = 30;
  float TIME_TO_START = 0;
  if (argc > 1) {
    TIME_SCHEDULED_MIN = atof(argv[1]);
    if (argc > 2) {
      TIME_TO_START = atof(argv[2]);
    }
  }

  const double TIME_SCHEDULED_SEC = (double)TIME_SCHEDULED_MIN * TO_SECS;

  double startTime = GetTime();
  double pausedElapsed = 0.0;
  bool pause = false;
  char text[64];

  while (!WindowShouldClose()) {
    mousePoint = GetMousePosition();

    // Pause button logic
    if (!timerEnded && CheckCollisionPointRec(mousePoint, btnBounds)) {
      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        PlaySound(fxButton);
        pause = !pause;
        if (pause) {
          pausedElapsed = GetTime() - startTime;
          btnState = 2;
        } else {
          startTime = GetTime() - pausedElapsed;
          btnState = 0;
        }
      }
    }

    sourceRec.y = btnState * frameHeight;

    if (TIME_TO_START > 0) {
      // wait this many second to start timer, maybe display a msg
      // timer will start shortly and play fxButtuon sound when starts
    }

    double elapsed = pause ? pausedElapsed : GetTime() - startTime;
    double remaining = TIME_SCHEDULED_SEC - elapsed;

    // Timer ended logic
    if (remaining <= 0) {
      remaining = 0;
      timerEnded = true;
      system("osascript -e 'display notification \"Timer finished\" with title "
             "\"Timer\"'");
      if (!finishedPlayed) {
        PlaySound(fxFinished);
        finishedPlayed = true;
      }
    }

    // Only update text while timer is running
    snprintf(text, sizeof(text), "Time left: %.0f s", remaining);
    StatusBarUpdate(text);

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText(text, WIDTH / 2 - 75, HEIGHT / 2, 20, BLACK);
    DrawTexture(pause_button, WIDTH / 2 + WIDTH / 4, HEIGHT / 2, WHITE);
    EndDrawing();

    // Exit after audio finishes
    if (timerEnded && finishedPlayed && !IsSoundPlaying(fxFinished))
      break;
  }

  // Clean up
  StatusBarCleanup();
  UnloadTexture(pause_button);
  UnloadSound(fxButton);
  UnloadSound(fxFinished);
  CloseAudioDevice();
  CloseWindow();

  return 0;
}
