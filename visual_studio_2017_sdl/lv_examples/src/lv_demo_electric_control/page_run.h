/**
 * @file page_running.h
 *
 */

#ifndef PAGE_RUN_H
#define PAGE_RUN_H

#pragma execution_character_set("utf-8")

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "global_prototype.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
 /*运行界面创建*/
lv_obj_t* _running_page_create(lv_obj_t* parent);


/**********************
 *      MACROS
 **********************/

#endif /*PAGE_RUN*/

#ifdef __cplusplus
} /* extern "C" */
#endif

