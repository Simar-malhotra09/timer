#import <Cocoa/Cocoa.h>
#include "statusbar.h"

static NSStatusItem *statusItem = nil;

void StatusBarInit(void) {
  if (statusItem != nil) {
    return;
  }
  statusItem = [[NSStatusBar systemStatusBar]
      statusItemWithLength:NSVariableStatusItemLength];
  statusItem.button.title = @"Timer";
}

void StatusBarSetImage(const char *path) {
  if (statusItem == nil || path == NULL) {
    return;
  }
  NSImage *image =
      [[NSImage alloc] initWithContentsOfFile:[NSString stringWithUTF8String:path]];
  if (image == nil) {
    return;
  }
  image.size = NSMakeSize(18, 18);
  statusItem.button.image = image;
  statusItem.button.imagePosition = NSImageLeft;
}

void StatusBarUpdate(const char *text) {
  if (statusItem == nil || text == NULL) {
    return;
  }
  statusItem.button.title = [NSString stringWithUTF8String:text];
}

void StatusBarCleanup(void) {
  if (statusItem == nil) {
    return;
  }
  [[NSStatusBar systemStatusBar] removeStatusItem:statusItem];
  statusItem = nil;
}
