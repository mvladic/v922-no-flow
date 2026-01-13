
/**
 * @file main
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#define SDL_MAIN_HANDLED        /*To fix SDL's "undefined reference to WinMain" issue*/
#include <SDL2/SDL.h>
#include <emscripten.h>
#include "lvgl/lvgl.h"
#include "lvgl/src/lvgl_private.h"

/*On OSX SDL needs different handling*/
#if defined(__APPLE__) && defined(TARGET_OS_MAC)
# if __APPLE__ && TARGET_OS_MAC
#define SDL_APPLE
# endif
#endif

#include "src/ui/ui.h"
//#include "src/ui/screens.h"

static int monitor_hor_res, monitor_ver_res;

lv_indev_t *enc_indev;
lv_indev_t *kb_indev;

static void hal_init(void)
{
    lv_display_t * disp = lv_sdl_window_create(monitor_hor_res, monitor_ver_res);
    lv_indev_t *mouse_indev = lv_sdl_mouse_create();
    enc_indev = lv_sdl_mousewheel_create();
    kb_indev = lv_sdl_keyboard_create();
}

void setup() {
    monitor_hor_res = 800;
    monitor_ver_res = 480;

    printf("Starting with screen resolution of %dx%d px\n", monitor_hor_res, monitor_ver_res);

    lv_init();

    hal_init();

    // ui_create_groups();
    //lv_indev_set_group(enc_indev, groups.encoder_group);
    //lv_indev_set_group(kb_indev, groups.keyboard_group);
    
    ui_init();
}

void loop() {
    static bool inited = false;
    if (!inited) {
        setup();
        /* Manually force timing mode to RAF (1) after setup.
         * This overrides SDL's internal timing settings which trigger the warning. */
        emscripten_set_main_loop_timing(1, 1);
        inited = true;
    }
    lv_task_handler();
    ui_tick();
}

int main(int argc, char ** argv) {
    /* Set the main loop to run with requestAnimationFrame (fps=0)
     * and stop execution of main (simulate_infinite_loop=1).
     * Initialization (setup) will happen on the first frame. */
    emscripten_set_main_loop(loop, 0, 1);
    return 0;
}
