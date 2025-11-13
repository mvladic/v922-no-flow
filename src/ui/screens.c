#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;
uint32_t active_theme_index = 0;

int compareRollerOptions(lv_roller_t *roller, const char *new_val, const char *cur_val, lv_roller_mode_t mode) {
    (void)(mode);

    uint32_t new_option_count = 1;

    for (int i = 0; ; i++) {
        if (new_val[i] == '\0') {
            if (cur_val[i] != '\0' && cur_val[i] != '\n') {
                return 1;
            }
            break;
        }

        if (new_val[i] != cur_val[i]) {
            return 1;
        }
 
        if (new_val[i] == '\n') {
            new_option_count++;
        }
    }

#if LVGL_VERSION_MAJOR >= 9
    return lv_roller_get_option_count((const lv_obj_t *)roller) == new_option_count ? 0 : 1;    
#else
    return lv_roller_get_option_cnt((const lv_obj_t *)roller) == new_option_count ? 0 : 1;    
#endif
}

void create_screen_main() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_roller_create(parent_obj);
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 360, 181);
            lv_obj_set_size(obj, 80, 100);
            lv_roller_set_options(obj, "", LV_ROLLER_MODE_INFINITE);
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 140, 66);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, action_opt1, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Button");
                }
            }
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 341, 67);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, action_opt2, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Button");
                }
            }
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 540, 67);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, action_opt3, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Button");
                }
            }
        }
    }
    
    tick_screen_main();
}

void tick_screen_main() {
    {
        const char *new_val = get_var_options();
        const char *cur_val = lv_roller_get_options(objects.obj0);
        if (compareRollerOptions((lv_roller_t *)objects.obj0, new_val, cur_val, LV_ROLLER_MODE_INFINITE) != 0) {
            tick_value_change_obj = objects.obj0;
            lv_roller_set_options(objects.obj0, new_val, LV_ROLLER_MODE_INFINITE);
            tick_value_change_obj = NULL;
        }
    }
}



typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_main();
}
