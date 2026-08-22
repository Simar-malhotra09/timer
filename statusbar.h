#ifndef STATUSBAR_H
#define STATUSBAR_H

#ifdef __cplusplus
extern "C" {
#endif

void StatusBarInit(void);
void StatusBarSetImage(const char *path);
void StatusBarUpdate(const char *text);
void StatusBarCleanup(void);

#ifdef __cplusplus
}
#endif

#endif
