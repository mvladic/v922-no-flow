
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
#include "src/ui/screens.h"

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
    ui_tick();
}

void loop() {
    lv_task_handler();
    ui_tick();
}

int main(int argc, char ** argv) {
    setup();

    emscripten_set_main_loop(loop, 100, false);
}

int opt = 0;

void action_opt1(lv_event_t * e) {
    opt = 0;
}

void action_opt2(lv_event_t * e) {
    opt = 1;
}

void action_opt3(lv_event_t * e) {
    opt = 2;
}

const char *get_var_options() {
    if (opt == 0) {
        return "A\nB\nC\nD\nE";
    } else if (opt == 1) {
        return "A\nB\nC\nD\n";
    } else {
        return "A\nB\nC\n\n\n\n";
    }
}

void set_var_options(const char *value) {
}
