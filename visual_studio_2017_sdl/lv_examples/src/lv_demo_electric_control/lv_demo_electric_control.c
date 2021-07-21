#include "../../lv_examples.h"

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
static lv_obj_t* tv;
static lv_obj_t* t1;
static lv_obj_t* t2;
static lv_obj_t* t3;

/**********************
*      MACROS
**********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

LV_FONT_DECLARE(myFont)

#define LV_THEME_DEFAULT_FONT_MYFONT       &myFont

#pragma execution_character_set("utf-8")

void lv_demo_electric_control(void)
{
	/* set custom font, support show chinese*/
	lv_theme_t* th = LV_THEME_DEFAULT_INIT(lv_theme_get_color_primary(), lv_theme_get_color_secondary(), LV_THEME_MATERIAL_FLAG_DARK,
		LV_THEME_DEFAULT_FONT_MYFONT, LV_THEME_DEFAULT_FONT_MYFONT,
		LV_THEME_DEFAULT_FONT_MYFONT, LV_THEME_DEFAULT_FONT_MYFONT);
	lv_theme_set_act(th);


	tv = lv_tabview_create(lv_scr_act(), NULL);
	t1 = lv_tabview_add_tab(tv, "‘À––");
	t2 = lv_tabview_add_tab(tv, "≤‚ ‘");
	t3 = lv_tabview_add_tab(tv, "…Ë÷√");

	lv_obj_t* label1 = lv_label_create(tv, NULL);
	lv_label_set_text(label1, LV_SYMBOL_OK);
}


