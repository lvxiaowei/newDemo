/**
 * @file page_run.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "page_run.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static lv_obj_t* add_content(const char* txt);
static lv_obj_t* add_btn(const char* txt);
static void btn_event_handler(lv_obj_t* obj, lv_event_t event);

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_obj_t* main_cont;

static lv_obj_t* lable_yarn_current;   /*织线圈数当前值*/
static lv_obj_t* lable_iron_current;   /*铁丝圈数当前值*/
static lv_obj_t* lable_space_current;  /*间隔圈数当前值*/
static lv_obj_t* lable_count_current;  /*长度块数当前值*/
static lv_obj_t* lable_yarn_set;    /*织线圈数设置的值*/
static lv_obj_t* lable_iron_set;	/*铁丝圈数设置的值*/
static lv_obj_t* lable_space_set;	/*间隔圈数设置的值*/
static lv_obj_t* lable_count_set;   /*长度块数设置的值*/
static lv_obj_t* lable_speed;   /*转速*/
/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t* _running_page_create(lv_obj_t* parent)
{

	main_cont = lv_obj_create(parent, NULL);
	lv_obj_set_size(main_cont, LV_HOR_RES, LV_VER_RES);
	lv_obj_set_style_local_radius(main_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_border_width(main_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_bg_color(main_cont, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, CUSTOM_COLOR_1);

	//头部
	lv_obj_t* title_box = lv_cont_create(main_cont, NULL);
	lv_cont_set_layout(title_box, LV_LAYOUT_PRETTY_MID);
	lv_obj_set_style_local_radius(title_box, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);
	lv_obj_set_style_local_border_width(title_box, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 0);
	lv_obj_set_size(title_box, LV_HOR_RES, 35);
	lv_obj_set_y(title_box, -10);
	lv_obj_set_style_local_bg_color(title_box, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLUE);
	lv_obj_t* title = lv_label_create(title_box, NULL);
	lv_obj_set_style_local_text_font(title, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_small());
	lv_label_set_text(title, "运行界面");

	//运行数据

	/*静态的内容*/
	lv_obj_t* content;
	content = add_content("织线圈数:");
	lv_obj_align(content, NULL, LV_ALIGN_IN_TOP_LEFT, 5, 35 + 40 * 0);

	content = add_content("铁丝圈数:");
	lv_obj_align(content, NULL, LV_ALIGN_IN_TOP_LEFT, 5, 35 + 40 * 1);

	content = add_content("间隔圈数:");
	lv_obj_align(content, NULL, LV_ALIGN_IN_TOP_LEFT, 5, 35 + 40 * 2);

	content = add_content("长度块数:");
	lv_obj_align(content, NULL, LV_ALIGN_IN_TOP_LEFT, 5, 35 + 40 * 3);

	/*动态的数据：织线圈数、铁丝圈数、间隔圈数、长度块数*/	
	lable_yarn_current = add_content("0");
	lv_obj_set_style_local_text_font(lable_yarn_current, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_title());
	lv_obj_set_style_local_text_color(lable_yarn_current, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLUE);
	lv_obj_align(lable_yarn_current, NULL, LV_ALIGN_IN_TOP_LEFT, 100, 35 + 40 * 0);

	lable_iron_current = add_content("0");
	lv_obj_set_style_local_text_font(lable_iron_current, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_title());
	lv_obj_set_style_local_text_color(lable_iron_current, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLUE);
	lv_obj_align(lable_iron_current, NULL, LV_ALIGN_IN_TOP_LEFT, 100, 35 + 40 * 1);

	lable_space_current = add_content("0");
	lv_obj_set_style_local_text_font(lable_space_current, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_title());
	lv_obj_set_style_local_text_color(lable_space_current, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLUE);
	lv_obj_align(lable_space_current, NULL, LV_ALIGN_IN_TOP_LEFT, 100, 35 + 40 * 2);

	lable_count_current = add_content("0");
	lv_obj_set_style_local_text_font(lable_count_current, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_title());
	lv_obj_set_style_local_text_color(lable_count_current, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLUE);
	lv_obj_align(lable_count_current, NULL, LV_ALIGN_IN_TOP_LEFT, 100, 35 + 40 * 3);

	lable_yarn_set = add_content("0");
	lv_obj_set_style_local_text_font(lable_yarn_set, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_title());
	lv_obj_align(lable_yarn_set, NULL, LV_ALIGN_IN_TOP_LEFT, 160, 35 + 40 * 0);

	lable_iron_set = add_content("0");
	lv_obj_set_style_local_text_font(lable_iron_set, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_title());
	lv_obj_align(lable_iron_set, NULL, LV_ALIGN_IN_TOP_LEFT, 160, 35 + 40 * 1);

	lable_space_set = add_content("0");
	lv_obj_set_style_local_text_font(lable_space_set, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_title());
	lv_obj_align(lable_space_set, NULL, LV_ALIGN_IN_TOP_LEFT, 160, 35 + 40 * 2);

	lable_count_set = add_content("0");
	lv_obj_set_style_local_text_font(lable_count_set, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_title());
	lv_obj_align(lable_count_set, NULL, LV_ALIGN_IN_TOP_LEFT, 160, 35 + 40 * 3);

	//竖线
	static lv_point_t line_points[] = { {230, 35}, {230, 175}};
	static lv_style_t style_line;
	lv_style_init(&style_line);
	lv_style_set_line_width(&style_line, LV_STATE_DEFAULT, 2);
	lv_style_set_line_color(&style_line, LV_STATE_DEFAULT, LV_COLOR_GRAY);
	lv_style_set_line_rounded(&style_line, LV_STATE_DEFAULT, true);
	lv_obj_t* line = lv_line_create(main_cont, NULL);
	lv_line_set_points(line, line_points, 2);
	lv_obj_add_style(line, LV_LINE_PART_MAIN, &style_line);

	//转速
	content = add_content("转速(圈):");
	lv_obj_align(content, NULL, LV_ALIGN_IN_TOP_LEFT, 250, 35 + 40 * 0);
	lv_label_set_long_mode(content, LV_LABEL_LONG_EXPAND);

	lable_speed = add_content("160");
	lv_obj_set_style_local_text_font(lable_speed, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_title());
	lv_obj_set_style_local_text_color(lable_speed, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLUE);
	lv_obj_align(lable_speed, NULL, LV_ALIGN_IN_TOP_LEFT, 345, 35 + 40 * 0);

	//底部按钮
	lv_obj_t* btn;
	btn = add_btn("主机\n点动");
	lv_obj_set_event_cb(btn, btn_event_1);
	lv_obj_set_pos(btn, 0 + 0 * 67, 190);

	btn = add_btn("主机\n运转");
	lv_obj_set_event_cb(btn, btn_event_2);
	lv_obj_set_pos(btn, 0 + 1 * 67, 190);

	btn = add_btn("压丝\n点动");
	lv_obj_set_event_cb(btn, btn_event_3);
	lv_obj_set_pos(btn, 0 + 2 * 67, 190);

	btn = add_btn("压丝\n停机");
	lv_obj_set_event_cb(btn, btn_event_4);
	lv_obj_set_pos(btn, 0 + 3 * 67, 190);

	btn = add_btn("速度\n切换");
	lv_obj_set_event_cb(btn, btn_event_5);
	lv_obj_set_pos(btn, 0 + 4 * 67, 190);

	btn = add_btn("界面\n切换");
	lv_obj_set_event_cb(btn, btn_event_6);
	lv_obj_set_pos(btn, 0 + 5 * 67, 190);

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

	return parent;
}


/**********************
 *   STATIC FUNCTIONS
 **********************/
static void btn_event_handler(lv_obj_t* obj, lv_event_t event)
{
	if (event == LV_EVENT_CLICKED) {
		printf("Clicked\n");
	}
	else if (event == LV_EVENT_VALUE_CHANGED) {
		printf("Toggled\n");
	}
}

static lv_obj_t* add_content(const char* txt)
{
	lv_obj_t* label = lv_label_create(main_cont, NULL);
	lv_obj_set_style_local_bg_color(label, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_CYAN);
	lv_obj_set_style_local_text_color(label, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
	lv_obj_set_style_local_text_font(label, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_normal());
	lv_label_set_text(label, txt);
	lv_label_set_long_mode(label, LV_LABEL_LONG_BREAK);
	lv_obj_set_width(label, 90);

	return label;
}

static lv_obj_t* add_btn(const char* txt)
{
	lv_obj_t* btn = lv_btn_create(main_cont, NULL);
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