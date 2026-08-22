#define NOB_IMPLEMENTATION
#include "nob.h"
#include <string.h>

#define BUILD_FOLDER "./"
#define SRC_FOLDER "./"

int main(int argc, char **argv) {
  NOB_GO_REBUILD_URSELF(argc, argv);
  Nob_Cmd cmd = {0};
  nob_cmd_append(&cmd, "gcc", "-Wall", "-Wextra", "-o", BUILD_FOLDER "timer",
                 SRC_FOLDER "main.c", "statusbar.m");
  nob_cmd_append(&cmd, "-fobjc-arc");
  nob_cmd_append(&cmd, "-I/opt/homebrew/Cellar/raylib/5.5/include");
  nob_cmd_append(&cmd, "-L/opt/homebrew/Cellar/raylib/5.5/lib");
  nob_cmd_append(&cmd, "-lraylib");
  nob_cmd_append(&cmd, "-framework", "AppKit");
  nob_cmd_append(&cmd, "-framework", "Foundation");

  if (!nob_cmd_run(&cmd))
    return 1;
  return 0;
}
