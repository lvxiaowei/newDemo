/**
 * @file lv_demo_electric_control.h
 *
 */

#ifndef LV_DEMO_ELECTRIC_CONTROL_H
#define LV_DEMO_ELECTRIC_CONTROL_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "global_prototype.h"
#include "lv_port_indev.h"
#include "SDL_keycode.h"
/*********************
 *      DEFINES
 *********************/

#pragma execution_character_set("utf-8")

/*用到的字体
主机点动丝中刀压参器圈块度延总数文时毛测界码线织编置英行设试转运速铁长间隔面停切换01234567890（）：
*/
/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
	static lv_indev_t* kb_indev;
	LV_EVENT_CB_DECLARE(keyboard_event);
	/*快捷键相关的回调*/
	LV_EVENT_CB_DECLARE(btn_event_F1);  /*主机点动*/
	LV_EVENT_CB_DECLARE(btn_event_F2);  /*主机运转*/
	LV_EVENT_CB_DECLARE(btn_event_F3);  /*压丝点动*/
	LV_EVENT_CB_DECLARE(btn_event_F4);  /*压低停机*/
	LV_EVENT_CB_DECLARE(btn_event_F5);  /*速度切换*/
	LV_EVENT_CB_DECLARE(btn_event_F6);  /*界面切换*/
/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_DEMO_ELECTRIC_CONTROL_H*/
