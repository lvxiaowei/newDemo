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
	RUNNING_CURRENT, //实时数据
	RUNNING_SET,     //设置的值

	RUNNING_YARN,    //织线圈数
	RUNNING_IRON,    //铁丝圈数
	RUNNING_SPACE,   //间隔圈数
	RUNNING_COUNT,   //长度块数
	RUNNING_SPEED,   //速度设置
} run_data_type;

typedef struct _running_data
{
	char* yarn_current;   /*织线圈数当前值*/
	char* iron_current;   /*铁丝圈数当前值*/
	char* space_current;  /*间隔圈数当前值*/
	char* count_current;  /*长度块数当前值*/
	char* yarn_set;     /*织线圈数设置的值*/
	char* iron_set;	    /*铁丝圈数设置的值*/
	char* space_set;	/*间隔圈数设置的值*/
	char* count_set;    /*长度块数设置的值*/
	char* speed; /*转速*/
}running_data;

/**********************
* GLOBAL PROTOTYPES
**********************/


//界面初始化
void lv_demo_electric_control(void);

/*********************************************运行界面******************************************/
/*快捷键相关的回调*/
LV_EVENT_CB_DECLARE(btn_event_1);  /*主机点动*/
LV_EVENT_CB_DECLARE(btn_event_2);  /*主机运转*/
LV_EVENT_CB_DECLARE(btn_event_3);  /*压丝点动*/
LV_EVENT_CB_DECLARE(btn_event_4);  /*压低停机*/
LV_EVENT_CB_DECLARE(btn_event_5);  /*速度切换*/
LV_EVENT_CB_DECLARE(btn_event_6);  /*界面切换*/

/**
 * 设置运行界面所有的参数的值
 * 例	running_data data = {
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
 * 设置单个参数的值
 * 列（设置纱线当前的值）：	set_run_data(RUNNING_CURRENT, RUNNING_YARN, "020");
 */
static void set_run_data(run_data_type state, run_data_type type, const char* value);

/*********************************************设置界面******************************************/

/*********************************************测试界面******************************************/

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