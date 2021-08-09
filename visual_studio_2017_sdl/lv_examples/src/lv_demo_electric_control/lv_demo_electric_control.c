
/*********************
 *      INCLUDES
 *********************/
#include "lv_demo_electric_control.h"
#include "page_run.h"
#include "page_set.h"
#include "page_cfg.h"
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_obj_t* page_run;
static lv_obj_t* page_set;
static lv_obj_t* page_cfg;

static lv_font_t* font_small;
static lv_font_t* font_medium;
static lv_font_t* font_large;

/**********************
*      MACROS
**********************/


/**********************
 *   GLOBAL FUNCTIONS
 **********************/
#define LV_DEMO_PRINTER_BG_NONE (LV_VER_RES)

#pragma execution_character_set("utf-8")


void lv_demo_electric_control(void)
{
    /* set custom font, support show chinese*/
    LV_FONT_DECLARE(myFont_12);
    LV_FONT_DECLARE(myFont_14);
    LV_FONT_DECLARE(myFont_16);
    font_small  = &myFont_12;
    font_medium = &myFont_14;
    font_large  = &myFont_16;
    lv_theme_t* th = lv_theme_material_init(lv_theme_get_color_primary(), lv_theme_get_color_secondary(), LV_THEME_MATERIAL_FLAG_DARK,
        font_small, font_medium,
        font_small, font_large);
    lv_theme_set_act(th);

	lv_obj_set_style_local_bg_color(lv_scr_act(), LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, lv_color_hex(0x343247));


    page_run = _running_page_open(lv_scr_act());

    page_set = _settings_page_open(lv_scr_act());

}

/**********************
 *   STATIC FUNCTIONS
 **********************/
#define DEMO_PRINTER_ANIM_TIME  (150)
#define DEMO_PRINTER_ANIM_Y (LV_VER_RES / 20)
#define DEMO_PRINTER_ANIM_DELAY (40)
static void lv_demo_printer_anim_out_all(lv_obj_t* obj, uint32_t delay) {
    lv_obj_t* child = lv_obj_get_child_back(obj, NULL);
    while (child) {
        if (/*child != scan_img && child != bg_top && child != bg_bottom &&*/ child != lv_scr_act()) {
            lv_anim_t a;
            lv_anim_init(&a);
            lv_anim_set_var(&a, child);
            lv_anim_set_time(&a, DEMO_PRINTER_ANIM_TIME);
            lv_anim_set_delay(&a, delay);
            lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_y);
            if (lv_obj_get_y(child) < 80) {
                lv_anim_set_values(&a, lv_obj_get_y(child),
                    lv_obj_get_y(child) - DEMO_PRINTER_ANIM_Y);
            }
            else {
                lv_anim_set_values(&a, lv_obj_get_y(child),
                    lv_obj_get_y(child) + DEMO_PRINTER_ANIM_Y);

                delay += DEMO_PRINTER_ANIM_DELAY;
            }
            lv_anim_set_ready_cb(&a, lv_obj_del_anim_ready_cb);
            lv_anim_start(&a);
        }
        child = lv_obj_get_child_back(obj, child);
    }
}