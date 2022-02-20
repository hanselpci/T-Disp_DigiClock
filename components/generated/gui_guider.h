/*
 * Copyright 2022 NXP
 * SPDX-License-Identifier: MIT
 */

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl/lvgl.h"
#include "guider_fonts.h"

typedef struct
{
	lv_obj_t *splash_screen;
	lv_obj_t *splash_screen_cont_1;
	lv_obj_t *splash_screen_lbl_title;
	lv_obj_t *splash_screen_lbl_version;
	lv_obj_t *splash_screen_lbl_status;
	lv_obj_t *splash_screen_lbl_dots;
	lv_obj_t *main_screen;
	lv_obj_t *main_screen_cont_1;
	lv_obj_t *main_screen_txtWeather;
	lv_obj_t *main_screen_txtLocation;
	lv_obj_t *main_screen_txtIP;
	lv_obj_t *main_screen_txtTime;
	lv_obj_t *main_screen_txtDate;
}lv_ui;

void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;
void setup_scr_splash_screen(lv_ui *ui);
void setup_scr_main_screen(lv_ui *ui);

#ifdef __cplusplus
}
#endif
#endif