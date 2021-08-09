/**
 * @file page_set.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "page_set.h"


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
static lv_obj_t* main_cont;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
lv_obj_t* _settings_page_open(lv_obj_t* parent)
{
	main_cont = lv_obj_create(parent, NULL);
	lv_obj_set_size(main_cont, LV_HOR_RES, LV_VER_RES);
	lv_obj_set_style_local_radius(main_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_border_width(main_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_bg_color(main_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_ORANGE);


	return main_cont;
}


/**********************
 *   STATIC FUNCTIONS
 **********************/
