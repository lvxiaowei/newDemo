
/*********************
 *      INCLUDES
 *********************/
#include "lv_demo_electric_control.h"
#include "theme.h"
/*********************
 *      DEFINES
 *********************/
 /*Bg positions*/
#define _BG_NONE (-LV_VER_RES)
#define _BG_FULL 0
#define _BG_NORMAL (-4 * (LV_VER_RES / 5))
#define _BG_SMALL (-5 * (LV_VER_RES / 6))

 /*Animations*/
#define _ANIM_TIME  (150)
#define _ANIM_Y (LV_VER_RES / 20)
#define _ANIM_DELAY (40)
#define _ANIM_TIME_BG  (400)
/**********************
 *      TYPEDEFS
 **********************/
typedef enum
{
	page_run = 0,
	page_set,
	page_test
};
/**********************
 *  STATIC PROTOTYPES
 **********************/
static void _running_page_open(uint32_t delay);
static void _settngs_page_open(uint32_t delay);
static void _test_page_open(uint32_t delay);

static lv_obj_t* _add_label(lv_obj_t* parent, const char* txt);
static lv_obj_t* _add_btn(lv_obj_t* parent, const char* txt);

static lv_anim_value_t anim_path_triangle(const lv_anim_path_t* path, const lv_anim_t* a);
static void lv_demo_printer_anim_bg(uint32_t delay, lv_color_t color, int32_t y_new);
static void lv_demo_printer_anim_out_all(lv_obj_t* obj, uint32_t delay);
static void lv_demo_printer_anim_in(lv_obj_t* obj, uint32_t delay);
static void anim_bg_color_cb(lv_anim_t* a, lv_anim_value_t v);
/**********************
 *  STATIC VARIABLES
 **********************/
 //公共对象
static int8_t index_cur_page;
static lv_obj_t* bg_top;
static lv_color_t bg_color_prev;
static lv_color_t bg_color_act;

//运行界面
static lv_obj_t* lable_yarn_current;   /*织线圈数当前值*/
static lv_obj_t* lable_iron_current;   /*铁丝圈数当前值*/
static lv_obj_t* lable_space_current;  /*间隔圈数当前值*/
static lv_obj_t* lable_count_current;  /*长度块数当前值*/
static lv_obj_t* lable_yarn_set;       /*织线圈数设置的值*/
static lv_obj_t* lable_iron_set;	   /*铁丝圈数设置的值*/
static lv_obj_t* lable_space_set;	   /*间隔圈数设置的值*/
static lv_obj_t* lable_count_set;      /*长度块数设置的值*/
static lv_obj_t* lable_speed;          /*转速*/

//设置界面
static lv_font_t* font_small;
static lv_font_t* font_medium;
static lv_font_t* font_large;

//测试界面

/**********************
*      MACROS
**********************/


/**********************
 *   GLOBAL FUNCTIONS
 **********************/
#define LV_DEMO_PRINTER_BG_NONE (LV_VER_RES)


void lv_demo_electric_control(lv_indev_t* keyboard_indev)
{
	lv_port_indev_init();

	kb_indev = keyboard_indev;

	//键盘事件
	lv_group_t* g = lv_group_create();
	lv_group_add_obj(g, lv_scr_act());
	lv_obj_set_event_cb(lv_scr_act(), btn_event);
	lv_indev_set_group(kb_indev, g);

	bg_color_prev = LV_DEMO_PRINTER_BLUE;
	bg_color_act = LV_DEMO_PRINTER_BLUE;

    /* set custom font, support show chinese*/
    LV_FONT_DECLARE(myFont_12);
    LV_FONT_DECLARE(myFont_14);
    LV_FONT_DECLARE(myFont_20);
    font_small  = &myFont_12;
    font_medium = &myFont_14;
    font_large  = &myFont_20;
    lv_theme_t* th = lv_theme_material_init(lv_theme_get_color_primary(), lv_theme_get_color_secondary(), LV_THEME_MATERIAL_FLAG_DARK,
        font_small, font_medium,
        font_small, font_large);
    lv_theme_set_act(th);

    lv_obj_t* scr = lv_obj_create(NULL, NULL);
    lv_scr_load(scr);

	bg_top = lv_obj_create(lv_scr_act(), NULL);
	lv_obj_clean_style_list(bg_top, LV_OBJ_PART_MAIN);
	lv_obj_set_style_local_bg_opa(bg_top, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT,
		LV_OPA_COVER);
	lv_obj_set_style_local_bg_color(bg_top, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT,
		LV_DEMO_PRINTER_GREEN);
	lv_obj_set_size(bg_top, LV_HOR_RES, LV_VER_RES);
	lv_obj_set_y(bg_top, _BG_NORMAL);

	_running_page_open(0);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void _running_page_open(uint32_t delay)
{
	//头部
	lv_obj_t* title = lv_label_create(lv_scr_act(), NULL);
	lv_obj_set_style_local_text_font(title, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_title());
	lv_obj_align(title, NULL, LV_ALIGN_IN_TOP_LEFT, LV_HOR_RES/2-40, 10);
	lv_label_set_text(title, "\xE8\xBF\x90\xE8\xA1\x8C\xE7\x95\x8C\xE9\x9D\xA2");

	//运行数据
	lv_obj_t* running_cont = lv_cont_create(lv_scr_act(), NULL);
	lv_obj_set_size(running_cont, LV_HOR_RES, 4 * (LV_VER_RES / 5));
	lv_obj_clean_style_list(running_cont, LV_CONT_PART_MAIN);
	lv_obj_align(running_cont, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 1 * (LV_VER_RES / 5));

	/*静态的内容*/
	lv_obj_t* content;
	content = _add_label(running_cont, "织线圈数：");
	lv_obj_set_style_local_text_color(content, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
	lv_obj_align(content, NULL, LV_ALIGN_IN_TOP_LEFT, 5, 5 + 35 * 0);
	lv_demo_printer_anim_in(content, 100 * 1);

	content = _add_label(running_cont, "铁丝圈数：");
	lv_obj_set_style_local_text_color(content, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
	lv_obj_align(content, NULL, LV_ALIGN_IN_TOP_LEFT, 5, 5 + 35 * 1);
	lv_demo_printer_anim_in(content, 100*2);

	content = _add_label(running_cont, "间隔圈数：");
	lv_obj_set_style_local_text_color(content, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
	lv_obj_align(content, NULL, LV_ALIGN_IN_TOP_LEFT, 5, 5 + 35 * 2);
	lv_demo_printer_anim_in(content, 100 * 3);

	content = _add_label(running_cont, "长度块数：");
	lv_obj_set_style_local_text_color(content, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
	lv_obj_align(content, NULL, LV_ALIGN_IN_TOP_LEFT, 5, 5 + 35 * 3);
	lv_demo_printer_anim_in(content, 100 * 4);

	/*动态的数据：织线圈数、铁丝圈数、间隔圈数、长度块数*/
	lable_yarn_current = _add_label(running_cont, "0");
	lv_obj_set_style_local_text_font(lable_yarn_current, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_title());
	lv_obj_set_style_local_text_color(lable_yarn_current, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLUE);
	lv_obj_align(lable_yarn_current, NULL, LV_ALIGN_IN_TOP_LEFT, 100, 5 + 35 * 0);
	lv_demo_printer_anim_in(lable_yarn_current, 100 * 1);

	lable_iron_current = _add_label(running_cont, "0");
	lv_obj_set_style_local_text_font(lable_iron_current, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_title());
	lv_obj_set_style_local_text_color(lable_iron_current, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLUE);
	lv_obj_align(lable_iron_current, NULL, LV_ALIGN_IN_TOP_LEFT, 100, 5 + 35 * 1);
	lv_demo_printer_anim_in(lable_iron_current, 100 * 2);

	lable_space_current = _add_label(running_cont, "0");
	lv_obj_set_style_local_text_font(lable_space_current, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_title());
	lv_obj_set_style_local_text_color(lable_space_current, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLUE);
	lv_obj_align(lable_space_current, NULL, LV_ALIGN_IN_TOP_LEFT, 100, 5 + 35 * 2);
	lv_demo_printer_anim_in(lable_space_current, 100 * 3);

	lable_count_current = _add_label(running_cont, "0");
	lv_obj_set_style_local_text_font(lable_count_current, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_title());
	lv_obj_set_style_local_text_color(lable_count_current, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLUE);
	lv_obj_align(lable_count_current, NULL, LV_ALIGN_IN_TOP_LEFT, 100, 5 + 35 * 3);
	lv_demo_printer_anim_in(lable_count_current, 100 * 4);

	lable_yarn_set = _add_label(running_cont, "0");
	lv_obj_set_style_local_text_font(lable_yarn_set, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_title());
	lv_obj_set_style_local_text_color(lable_yarn_set, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
	lv_obj_align(lable_yarn_set, NULL, LV_ALIGN_IN_TOP_LEFT, 160, 5 + 35 * 0);
	lv_demo_printer_anim_in(lable_yarn_set, 100 * 1);

	lable_iron_set = _add_label(running_cont, "0");
	lv_obj_set_style_local_text_font(lable_iron_set, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_title());
	lv_obj_set_style_local_text_color(lable_iron_set, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
	lv_obj_align(lable_iron_set, NULL, LV_ALIGN_IN_TOP_LEFT, 160, 5 + 35 * 1);
	lv_demo_printer_anim_in(lable_iron_set, 100 * 2);

	lable_space_set = _add_label(running_cont, "0");
	lv_obj_set_style_local_text_font(lable_space_set, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_title());
	lv_obj_set_style_local_text_color(lable_space_set, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
	lv_obj_align(lable_space_set, NULL, LV_ALIGN_IN_TOP_LEFT, 160, 5 + 35 * 2);
	lv_demo_printer_anim_in(lable_space_set, 100 * 3);

	lable_count_set = _add_label(running_cont, "0");
	lv_obj_set_style_local_text_font(lable_count_set, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_title());
	lv_obj_set_style_local_text_color(lable_count_set, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
	lv_obj_align(lable_count_set, NULL, LV_ALIGN_IN_TOP_LEFT, 160, 5 + 35 * 3);
	lv_demo_printer_anim_in(lable_count_set, 100 * 4);

	//竖线
	static lv_point_t line_points[] = { {230, 0}, {230, 140} };
	static lv_style_t style_line;
	lv_style_init(&style_line);
	lv_style_set_line_width(&style_line, LV_STATE_DEFAULT, 2);
	lv_style_set_line_color(&style_line, LV_STATE_DEFAULT, LV_COLOR_GRAY);
	lv_style_set_line_rounded(&style_line, LV_STATE_DEFAULT, true);
	lv_obj_t* line = lv_line_create(running_cont, NULL);
	lv_line_set_points(line, line_points, 2);
	lv_obj_add_style(line, LV_LINE_PART_MAIN, &style_line);

	//转速
	content = _add_label(running_cont, "转速（圈）：");
	lv_obj_set_style_local_text_color(content, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
	lv_obj_align(content, NULL, LV_ALIGN_IN_TOP_LEFT, 250, 5 + 35 * 0);
	lv_demo_printer_anim_in(content, 100 * 1);

	lable_speed = _add_label(running_cont, "160");
	lv_obj_set_style_local_text_font(lable_speed, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_title());
	lv_obj_set_style_local_text_color(lable_speed, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLUE);
	lv_obj_align(lable_speed, NULL, LV_ALIGN_IN_TOP_LEFT, 345, 5 + 35 * 0);
	lv_demo_printer_anim_in(lable_speed, 100 * 1);

	//底部按钮
	lv_obj_t* btn;
	btn = _add_btn(running_cont, "主机\n点动");
	lv_obj_set_pos(btn, 0 + 0 * 67, 142);
	lv_demo_printer_anim_in(btn, 100 * 5);

	btn = _add_btn(running_cont, "主机\n运转");
	lv_obj_set_pos(btn, 0 + 1 * 67, 142);
	lv_demo_printer_anim_in(btn, 100 * 5);

	btn = _add_btn(running_cont, "压丝\n点动");
	lv_obj_set_pos(btn, 0 + 2 * 67, 142);
	lv_demo_printer_anim_in(btn, 100 * 5);

	btn = _add_btn(running_cont, "压丝\n停机");
	lv_obj_set_pos(btn, 0 + 3 * 67, 142);
	lv_demo_printer_anim_in(btn, 100 * 5);

	btn = _add_btn(running_cont, "速度\n切换");
	lv_obj_set_pos(btn, 0 + 4 * 67, 142);
	lv_demo_printer_anim_in(btn, 100 * 5);

	btn = _add_btn(running_cont, "界面\n切换");
	lv_obj_set_pos(btn, 0 + 5 * 67, 142);
	lv_demo_printer_anim_in(btn, 100 * 5);

	running_data data = {
			.yarn_current = "1",
			.iron_current = "2",
			.space_current = "3",
			.count_current = "4",
			.yarn_set = "5",
			.iron_set = "6",
			.space_set = "7",
			.count_set = "8",
			.speed = "9"
	};
	set_run_data_all(&data);

	index_cur_page = page_run;
}

static void _settngs_page_open(uint32_t delay)
{
	//头部
	lv_obj_t* title = lv_label_create(lv_scr_act(), NULL);
	lv_obj_set_style_local_text_font(title, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_title());
	lv_obj_align(title, NULL, LV_ALIGN_IN_TOP_LEFT, LV_HOR_RES / 2 - 40, 10);
	lv_obj_set_style_local_text_color(title, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
	lv_label_set_text(title, "设置界面");

	//运行数据
	lv_obj_t* running_cont = lv_cont_create(lv_scr_act(), NULL);
	lv_obj_set_size(running_cont, LV_HOR_RES, 4 * (LV_VER_RES / 5));
	lv_obj_clean_style_list(running_cont, LV_CONT_PART_MAIN);
	lv_obj_align(running_cont, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 1 * (LV_VER_RES / 5));

	/*静态的内容*/
	lv_obj_t* content;
	content = _add_label(running_cont, "织线圈数：");
	lv_obj_set_style_local_text_color(content, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
	lv_obj_align(content, NULL, LV_ALIGN_IN_TOP_LEFT, 5, 5 + 35 * 0);
	lv_obj_set_width(content, 120);
	lv_demo_printer_anim_in(content, 100 * 1);

	content = _add_label(running_cont, "铁丝圈数：");
	lv_obj_set_style_local_text_color(content, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
	lv_obj_align(content, NULL, LV_ALIGN_IN_TOP_LEFT, 5, 5 + 35 * 1);
	lv_demo_printer_anim_in(content, 100 * 2);

	content = _add_label(running_cont, "间隔圈数：");
	lv_obj_set_style_local_text_color(content, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
	lv_obj_align(content, NULL, LV_ALIGN_IN_TOP_LEFT, 5, 5 + 35 * 2);
	lv_demo_printer_anim_in(content, 100 * 3);

	content = _add_label(running_cont, "长度间隔块数：");
	lv_obj_set_style_local_text_color(content, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
	lv_obj_align(content, NULL, LV_ALIGN_IN_TOP_LEFT, 5, 5 + 35 * 3);
	lv_demo_printer_anim_in(content, 100 * 4);

	lv_obj_t* btn = _add_btn(running_cont, "界面\n切换");
	lv_obj_set_pos(btn, 0 + 5 * 67, 142);
	lv_demo_printer_anim_in(btn, 100 * 5);

	index_cur_page = page_set;
}

static void _test_page_open(uint32_t delay)
{
	//头部
	lv_obj_t* title = lv_label_create(lv_scr_act(), NULL);
	lv_obj_set_style_local_text_font(title, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_title());
	lv_obj_align(title, NULL, LV_ALIGN_IN_TOP_LEFT, LV_HOR_RES / 2 - 40, 10);
	lv_obj_set_style_local_text_color(title, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
	lv_label_set_text(title, "测试界面");

	//运行数据
	lv_obj_t* running_cont = lv_cont_create(lv_scr_act(), NULL);
	lv_obj_set_size(running_cont, LV_HOR_RES, 4 * (LV_VER_RES / 5));
	lv_obj_clean_style_list(running_cont, LV_CONT_PART_MAIN);
	lv_obj_align(running_cont, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 1 * (LV_VER_RES / 5));
	/*静态的内容*/
	lv_obj_t* content;
	content = _add_label(running_cont, "织线圈数：");
	lv_obj_set_style_local_text_color(content, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
	lv_obj_align(content, NULL, LV_ALIGN_IN_TOP_LEFT, 5, 5 + 35 * 0);
	lv_obj_set_width(content, 120);
	lv_demo_printer_anim_in(content, 100 * 1);

	content = _add_label(running_cont, "铁丝圈数：");
	lv_obj_set_style_local_text_color(content, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
	lv_obj_align(content, NULL, LV_ALIGN_IN_TOP_LEFT, 5, 5 + 35 * 1);
	lv_demo_printer_anim_in(content, 100 * 2);

	content = _add_label(running_cont, "间隔圈数：");
	lv_obj_set_style_local_text_color(content, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
	lv_obj_align(content, NULL, LV_ALIGN_IN_TOP_LEFT, 5, 5 + 35 * 2);
	lv_demo_printer_anim_in(content, 100 * 3);

	content = _add_label(running_cont, "长度间隔块数：");
	lv_obj_set_style_local_text_color(content, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
	lv_obj_align(content, NULL, LV_ALIGN_IN_TOP_LEFT, 5, 5 + 35 * 3);
	lv_demo_printer_anim_in(content, 100 * 4);

	lv_obj_t* btn = _add_btn(running_cont, "界面\n切换");
	lv_obj_set_pos(btn, 0 + 5 * 67, 142);
	lv_demo_printer_anim_in(btn, 100 * 5);

	index_cur_page = page_test;
}

static lv_obj_t* _add_label(lv_obj_t* parent, const char* txt)
{
    lv_obj_t* label = lv_label_create(parent, NULL);
    lv_obj_set_style_local_text_font(label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_normal());
    lv_label_set_text(label, txt);
    lv_label_set_long_mode(label, LV_LABEL_LONG_BREAK);
    lv_obj_set_width(label, 90);

    return label;
}

static lv_obj_t* _add_btn(lv_obj_t* parent, const char* txt)
{
    lv_obj_t* btn = lv_btn_create(parent, NULL);
    lv_obj_align(btn, NULL, LV_ALIGN_CENTER, 0, -40);
    lv_obj_set_size(btn, 66, 50);
    lv_obj_set_style_local_radius(btn, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);
    lv_obj_set_style_local_border_width(btn, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 2);
    lv_obj_set_style_local_border_color(btn, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_obj_t* label = lv_label_create(btn, NULL);
    lv_obj_set_style_local_text_font(label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_small());
    lv_label_set_text(label, txt);
    return btn;
}

void set_run_data(run_data_type state, run_data_type type, const char* value)
{
	switch (type)
	{
	case RUNNING_YARN:
		lv_label_set_text(RUNNING_CURRENT == state ? lable_yarn_current : lable_yarn_set, value);
		break;
	case RUNNING_IRON:
		lv_label_set_text(RUNNING_CURRENT == state ? lable_iron_current : lable_iron_set, value);
		break;
	case RUNNING_SPACE:
		lv_label_set_text(RUNNING_CURRENT == state ? lable_space_current : lable_space_set, value);
		break;
	case RUNNING_COUNT:
		lv_label_set_text(RUNNING_CURRENT == state ? lable_count_current : lable_count_set, value);
		break;
	case RUNNING_SPEED:
		lv_label_set_text(lable_speed, value);
		break;
	}
}

void set_run_data_all(running_data* data)
{
	lv_label_set_text(lable_yarn_current, data->yarn_current);
	lv_label_set_text(lable_iron_current, data->iron_current);
	lv_label_set_text(lable_space_current, data->space_current);
	lv_label_set_text(lable_count_current, data->count_current);

	lv_label_set_text(lable_yarn_set, data->yarn_set);
	lv_label_set_text(lable_iron_set, data->iron_set);
	lv_label_set_text(lable_space_set, data->space_set);
	lv_label_set_text(lable_count_set, data->count_set);

	lv_label_set_text(lable_speed, data->speed);
}

/**
 * Calculate the current value of an animation applying linear characteristic
 * @param a pointer to an animation
 * @return the current value to set
 */
static lv_anim_value_t anim_path_triangle(const lv_anim_path_t* path, const lv_anim_t* a)
{
	/*Calculate the current step*/
	uint32_t step;
	lv_anim_value_t ret = 0;
	if (a->time == a->act_time) {
		ret = (lv_anim_value_t)a->end;
	}
	else {
		if (a->act_time < a->time / 2) {
			step = ((int32_t)a->act_time * 1024) / (a->time / 2);
			int32_t new_value;
			new_value = (int32_t)step * (_BG_SMALL - a->start);
			new_value = new_value >> 10;
			new_value += a->start;

			ret = (lv_anim_value_t)new_value;
		}
		else {
			uint32_t t = a->act_time - a->time / 2;
			step = ((int32_t)t * 1024) / (a->time / 2);
			int32_t new_value;
			new_value = (int32_t)step * (a->end - _BG_SMALL);
			new_value = new_value >> 10;
			new_value += _BG_SMALL;

			ret = (lv_anim_value_t)new_value;
		}
	}

	return ret;
}

static void lv_demo_printer_anim_bg(uint32_t delay, lv_color_t color, int32_t y_new)
{
	lv_coord_t y_act = lv_obj_get_y(bg_top);
	lv_color_t act_color = lv_obj_get_style_bg_color(bg_top, LV_OBJ_PART_MAIN);
	if (y_new != _BG_NORMAL && y_new == y_act && act_color.full == color.full) return;


	lv_anim_t a;
	if ((y_new == _BG_NORMAL && y_new == y_act) ||
		(y_new == _BG_NORMAL && y_act == _BG_FULL)) {
		lv_anim_path_t path;
		lv_anim_path_init(&path);
		lv_anim_path_set_cb(&path, anim_path_triangle);

		lv_anim_init(&a);
		lv_anim_set_var(&a, bg_top);
		lv_anim_set_time(&a, _ANIM_TIME_BG + 200);
		lv_anim_set_delay(&a, delay);
		lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_y);
		lv_anim_set_values(&a, y_act, y_new);
		lv_anim_set_path(&a, &path);
		lv_anim_start(&a);
	}
	else {
		lv_anim_init(&a);
		lv_anim_set_var(&a, bg_top);
		lv_anim_set_time(&a, _ANIM_TIME_BG);
		lv_anim_set_delay(&a, delay);
		lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_y);
		lv_anim_set_values(&a, lv_obj_get_y(bg_top), y_new);
		lv_anim_start(&a);
	}

	bg_color_prev = bg_color_act;
	bg_color_act = color;

	lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)anim_bg_color_cb);
	lv_anim_set_values(&a, 0, 255);
	lv_anim_set_time(&a, _ANIM_TIME_BG);
	lv_anim_set_path(&a, &lv_anim_path_def);
	lv_anim_start(&a);

}

static void lv_demo_printer_anim_out_all(lv_obj_t* obj, uint32_t delay) {
	lv_obj_t* child = lv_obj_get_child_back(obj, NULL);
	while (child) {
		if ( child != bg_top  && child != lv_scr_act() ) {
			lv_anim_t a;
			lv_anim_init(&a);
			lv_anim_set_var(&a, child);
			lv_anim_set_time(&a, _ANIM_TIME);
			lv_anim_set_delay(&a, delay);
			lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_y);
			if (lv_obj_get_y(child) < 80) {
				lv_anim_set_values(&a, lv_obj_get_y(child),
					lv_obj_get_y(child) - _ANIM_Y);
			}
			else {
				lv_anim_set_values(&a, lv_obj_get_y(child),
					lv_obj_get_y(child) + _ANIM_Y);

				delay += _ANIM_DELAY;
			}
			lv_anim_set_ready_cb(&a, lv_obj_del_anim_ready_cb);
			lv_anim_start(&a);
		}
		child = lv_obj_get_child_back(obj, child);
	}
}

static void lv_demo_printer_anim_in(lv_obj_t* obj, uint32_t delay)
{
	if (obj != bg_top /*&& obj != bg_bottom*/ && obj != lv_scr_act()) {
		lv_anim_t a;
		lv_anim_init(&a);
		lv_anim_set_var(&a, obj);
		lv_anim_set_time(&a, _ANIM_TIME);
		lv_anim_set_delay(&a, delay);
		lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_y);
		lv_anim_set_values(&a, lv_obj_get_y(obj) - _ANIM_Y,
			lv_obj_get_y(obj));
		lv_anim_start(&a);

		lv_obj_fade_in(obj, _ANIM_TIME - 50, delay);
	}

}
static void anim_bg_color_cb(lv_anim_t* a, lv_anim_value_t v)
{
	lv_color_t c = lv_color_mix(bg_color_act, bg_color_prev, v);
	lv_obj_set_style_local_bg_color(bg_top, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, c);
}

LV_EVENT_CB_DECLARE(btn_event)
{
	if (e == LV_EVENT_KEY) {

		const uint32_t* key = lv_event_get_data();

		switch (*key)
		{
		case SDLK_F1:
			btn_event_F1(obj, e);
			break;
		case SDLK_F2:
			btn_event_F2(obj, e);
			break;
		case SDLK_F3:
			btn_event_F3(obj, e);
			break;
		case SDLK_F4:
			btn_event_F4(obj, e);
			break;
		case SDLK_F5:
			btn_event_F5(obj, e);
			break;
		case SDLK_F6:
			btn_event_F6(obj, e);
			break;
		default:
			break;
		}
	}
}

LV_EVENT_CB_DECLARE(btn_event_F1)
{
	printf("11");
}

LV_EVENT_CB_DECLARE(btn_event_F2)
{

}
LV_EVENT_CB_DECLARE(btn_event_F3)
{

}

LV_EVENT_CB_DECLARE(btn_event_F4)
{

}

LV_EVENT_CB_DECLARE(btn_event_F5)
{

}

LV_EVENT_CB_DECLARE(btn_event_F6)
{
	switch (index_cur_page)
	{
	case page_run:
		lv_demo_printer_anim_out_all(lv_scr_act(), 0);
		lv_demo_printer_anim_bg(0, CUSTOM_COLOR_1, _BG_FULL);
		_settngs_page_open(100);
		break;

	case page_set:
		lv_demo_printer_anim_out_all(lv_scr_act(), 0);
		lv_demo_printer_anim_bg(0, LV_COLOR_PURPLE, _BG_FULL);
		_test_page_open(100);
		break;

	case page_test:
		lv_demo_printer_anim_out_all(lv_scr_act(), 0);
		lv_obj_set_style_local_bg_opa(bg_top, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_COVER);
		lv_obj_set_style_local_bg_color(bg_top, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_DEMO_PRINTER_GREEN);
		lv_obj_set_y(bg_top, _BG_NORMAL);
		_running_page_open(100);
		break;
	}
}