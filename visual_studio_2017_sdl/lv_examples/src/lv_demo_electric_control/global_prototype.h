#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../../lv_examples.h"
/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
typedef enum {
	RUNNING_CURRENT, //ʵʱ����
	RUNNING_SET,     //���õ�ֵ

	RUNNING_YARN,    //֯��Ȧ��
	RUNNING_IRON,    //��˿Ȧ��
	RUNNING_SPACE,   //���Ȧ��
	RUNNING_COUNT,   //���ȿ���
	RUNNING_SPEED,   //�ٶ�����
} run_data_type;

typedef struct _running_data
{
	char* yarn_current;   /*֯��Ȧ����ǰֵ*/
	char* iron_current;   /*��˿Ȧ����ǰֵ*/
	char* space_current;  /*���Ȧ����ǰֵ*/
	char* count_current;  /*���ȿ�����ǰֵ*/
	char* yarn_set;     /*֯��Ȧ�����õ�ֵ*/
	char* iron_set;	    /*��˿Ȧ�����õ�ֵ*/
	char* space_set;	/*���Ȧ�����õ�ֵ*/
	char* count_set;    /*���ȿ������õ�ֵ*/
	char* speed; /*ת��*/
}running_data;

/**********************
* GLOBAL PROTOTYPES
**********************/


//�����ʼ��
void lv_demo_electric_control(void);

/*********************************************���н���******************************************/
/*��ݼ���صĻص�*/
LV_EVENT_CB_DECLARE(btn_event_1);  /*�����㶯*/
LV_EVENT_CB_DECLARE(btn_event_2);  /*������ת*/
LV_EVENT_CB_DECLARE(btn_event_3);  /*ѹ˿�㶯*/
LV_EVENT_CB_DECLARE(btn_event_4);  /*ѹ��ͣ��*/
LV_EVENT_CB_DECLARE(btn_event_5);  /*�ٶ��л�*/
LV_EVENT_CB_DECLARE(btn_event_6);  /*�����л�*/

/**
 * �������н������еĲ�����ֵ
 * ��	running_data data = {
		    .yarn_current="1",
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
 */
static void set_run_data_all(running_data* data);
/**
 * ���õ���������ֵ
 * �У�����ɴ�ߵ�ǰ��ֵ����	set_run_data(RUNNING_CURRENT, RUNNING_YARN, "020");
 */
static void set_run_data(run_data_type state, run_data_type type, const char* value);

/*********************************************���ý���******************************************/

/*********************************************���Խ���******************************************/

/**********************
 *      MACROS
 **********************/

 /**********************
  *   STATIC FUNCTIONS
  **********************/

LV_EVENT_CB_DECLARE(btn_event_1)
{

}

LV_EVENT_CB_DECLARE(btn_event_2)
{

}
LV_EVENT_CB_DECLARE(btn_event_3)
{

}

LV_EVENT_CB_DECLARE(btn_event_4)
{

}

LV_EVENT_CB_DECLARE(btn_event_5)
{

}


#ifdef __cplusplus
} /* extern "C" */
#endif