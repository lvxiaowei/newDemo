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

/*�õ�������
�����㶯˿�е�ѹ����Ȧ�����������ʱë�������֯����Ӣ������ת�������������ͣ�л�01234567890������
*/
/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
	static lv_indev_t* kb_indev;
	LV_EVENT_CB_DECLARE(keyboard_event);
	/*��ݼ���صĻص�*/
	LV_EVENT_CB_DECLARE(btn_event_F1);  /*�����㶯*/
	LV_EVENT_CB_DECLARE(btn_event_F2);  /*������ת*/
	LV_EVENT_CB_DECLARE(btn_event_F3);  /*ѹ˿�㶯*/
	LV_EVENT_CB_DECLARE(btn_event_F4);  /*ѹ��ͣ��*/
	LV_EVENT_CB_DECLARE(btn_event_F5);  /*�ٶ��л�*/
	LV_EVENT_CB_DECLARE(btn_event_F6);  /*�����л�*/
/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_DEMO_ELECTRIC_CONTROL_H*/
