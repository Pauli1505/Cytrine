// config.h
#ifndef CONFIG_H
#define CONFIG_H

// DEBUGGING
#define DEBUG_MODE 1 // DEBUG_MODE makes the app print debug info. (warning if you like your sweet sweet performance, this uses if statements)
#define LOG_LEVEL 2 // 0 = none, 1 = err only, 2 = error + warning (best for debugging), 3 = Verbose


// GRAPHICS
#define VSYNC 1 // for the sake of debuggery imma turn this off for now
#define SCREEN_WIDTH 1920 // ASSUME 1080P AND 1920X1080 MONITOR
#define SCREEN_HEIGHT 1080 // ASSUME 1080P AND 1920X1080 MONITOR (im not sure if i need to switch this out)
#define FULLSCREEN_MODE 0 // 0 = Windowed, 1 = Fullscreen

// Performance
/*#define MAX_FPS 60*/
// fps is handled by vsync.
#define USE_MULTITHREADING 1 // Enable multithreading

// PHYSICS
// TODO: add physics engine (stupd get your ass here now!! wait no, we wanted to do that together)
#define PHYSICS_STEP 0.016f    // Fixed physics timestep (seconds)
#define ENABLE_GRAVITY 1       // Enable gravity (1 = on, 0 = off)
#define GRAVITY_FORCE -9.8f    // Gravity strength


// AUDIO
// TODO: add fmod or openal (stupd get your ass here now!! this time im right)
#define ENABLE_AUDIO 1    // Enable audio (1 = on, 0 = off)
#define MASTER_VOLUME 100 // Master volume (0 to 100)

// TODO: Dev tools implementation




#endif // CONFIG_H
