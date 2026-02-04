#include <stdlib.h>
#include "raylib.h"
#include <time.h> 
#include <stdio.h> 

#define TO_SECS 60 
#define WIDTH 200
#define HEIGHT 100
int main(int argc, char* argv[])
{
  
  InitWindow(WIDTH, HEIGHT, "Timer- Lock in! ");
  int TIME_SCHEDULED_MIN= 30; // minutes  

  if(argc > 1){
    TIME_SCHEDULED_MIN= atoi(argv[1]);
  }
  printf("%i",TIME_SCHEDULED_MIN);
  const double TIME_SCHEDULED_SEC = (double)TIME_SCHEDULED_MIN * TO_SECS; 

  clock_t start = clock();

  char text[64];

  while (!WindowShouldClose())
  {
      double elapsed = (double)(clock() - start) / CLOCKS_PER_SEC;
      double remaining = TIME_SCHEDULED_SEC- elapsed;

      if (remaining < 0) remaining = 0;

      snprintf(text, sizeof(text), "Time left: %.0f s", remaining);

      BeginDrawing();
          ClearBackground(RAYWHITE);
          DrawText(text, (WIDTH / 2) -75, (HEIGHT/2), 20, BLACK);
      EndDrawing();
  }

  return 0;
}
