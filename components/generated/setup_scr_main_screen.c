/*
 * Copyright 2022 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"


void setup_scr_main_screen(lv_ui *ui){

	//Write codes main_screen
	ui->main_screen = lv_obj_create(NULL);

	//Write style state: LV_STATE_DEFAULT for style_main_screen_main_main_default
	static lv_style_t style_main_screen_main_main_default;
	lv_style_reset(&style_main_screen_main_main_default);
	lv_style_set_bg_color(&style_main_screen_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_opa(&style_main_screen_main_main_default, 0);
	lv_obj_add_style(ui->main_screen, &style_main_screen_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes main_screen_cont_1
	ui->main_screen_cont_1 = lv_obj_create(ui->main_screen);
	lv_obj_set_pos(ui->main_screen_cont_1, 1, 1);
	lv_obj_set_size(ui->main_screen_cont_1, 133, 238);

	//Write style state: LV_STATE_DEFAULT for style_main_screen_cont_1_main_main_default
	static lv_style_t style_main_screen_cont_1_main_main_default;
	lv_style_reset(&style_main_screen_cont_1_main_main_default);
	lv_style_set_radius(&style_main_screen_cont_1_main_main_default, 0);
	lv_style_set_bg_color(&style_main_screen_cont_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_main_screen_cont_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_main_screen_cont_1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_main_screen_cont_1_main_main_default, 255);
	lv_style_set_border_color(&style_main_screen_cont_1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_border_width(&style_main_screen_cont_1_main_main_default, 0);
	lv_style_set_border_opa(&style_main_screen_cont_1_main_main_default, 255);
	lv_style_set_pad_left(&style_main_screen_cont_1_main_main_default, 0);
	lv_style_set_pad_right(&style_main_screen_cont_1_main_main_default, 0);
	lv_style_set_pad_top(&style_main_screen_cont_1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_main_screen_cont_1_main_main_default, 0);
	lv_obj_add_style(ui->main_screen_cont_1, &style_main_screen_cont_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes main_screen_txtWeather
	ui->main_screen_txtWeather = lv_spangroup_create(ui->main_screen_cont_1);
	lv_obj_set_pos(ui->main_screen_txtWeather, 1, 174);
	lv_obj_set_size(ui->main_screen_txtWeather, 130, 28);
	lv_spangroup_set_align(ui->main_screen_txtWeather, LV_TEXT_ALIGN_LEFT);
	lv_spangroup_set_overflow(ui->main_screen_txtWeather, LV_SPAN_OVERFLOW_CLIP);
	lv_spangroup_set_mode(ui->main_screen_txtWeather, LV_SPAN_MODE_BREAK);

	//create spans
	lv_span_t *main_screen_txtWeather_span;

	//create a new span
	main_screen_txtWeather_span = lv_spangroup_new_span(ui->main_screen_txtWeather);
	lv_span_set_text(main_screen_txtWeather_span, "Weather:    ");
	lv_style_set_text_color(&main_screen_txtWeather_span->style, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_decor(&main_screen_txtWeather_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&main_screen_txtWeather_span->style, &lv_font_montserratMedium_12);

	//create a new span
	main_screen_txtWeather_span = lv_spangroup_new_span(ui->main_screen_txtWeather);
	lv_span_set_text(main_screen_txtWeather_span, "10 / Rain");
	lv_style_set_text_color(&main_screen_txtWeather_span->style, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_decor(&main_screen_txtWeather_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&main_screen_txtWeather_span->style, &lv_font_montserratMedium_12);
	lv_spangroup_refr_mode(ui->main_screen_txtWeather);

	//Write codes main_screen_txtLocation
	ui->main_screen_txtLocation = lv_spangroup_create(ui->main_screen_cont_1);
	lv_obj_set_pos(ui->main_screen_txtLocation, 1, 152);
	lv_obj_set_size(ui->main_screen_txtLocation, 130, 28);
	lv_spangroup_set_align(ui->main_screen_txtLocation, LV_TEXT_ALIGN_LEFT);
	lv_spangroup_set_overflow(ui->main_screen_txtLocation, LV_SPAN_OVERFLOW_CLIP);
	lv_spangroup_set_mode(ui->main_screen_txtLocation, LV_SPAN_MODE_BREAK);

	//create spans
	lv_span_t *main_screen_txtLocation_span;

	//create a new span
	main_screen_txtLocation_span = lv_spangroup_new_span(ui->main_screen_txtLocation);
	lv_span_set_text(main_screen_txtLocation_span, "Location:    ");
	lv_style_set_text_color(&main_screen_txtLocation_span->style, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_decor(&main_screen_txtLocation_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&main_screen_txtLocation_span->style, &lv_font_montserratMedium_12);

	//create a new span
	main_screen_txtLocation_span = lv_spangroup_new_span(ui->main_screen_txtLocation);
	lv_span_set_text(main_screen_txtLocation_span, "Shenzhen");
	lv_style_set_text_color(&main_screen_txtLocation_span->style, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_decor(&main_screen_txtLocation_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&main_screen_txtLocation_span->style, &lv_font_montserratMedium_12);
	lv_spangroup_refr_mode(ui->main_screen_txtLocation);

	//Write codes main_screen_txtIP
	ui->main_screen_txtIP = lv_spangroup_create(ui->main_screen_cont_1);
	lv_obj_set_pos(ui->main_screen_txtIP, 1, 129);
	lv_obj_set_size(ui->main_screen_txtIP, 130, 20);
	lv_spangroup_set_align(ui->main_screen_txtIP, LV_TEXT_ALIGN_LEFT);
	lv_spangroup_set_overflow(ui->main_screen_txtIP, LV_SPAN_OVERFLOW_CLIP);
	lv_spangroup_set_mode(ui->main_screen_txtIP, LV_SPAN_MODE_BREAK);

	//create spans
	lv_span_t *main_screen_txtIP_span;

	//create a new span
	main_screen_txtIP_span = lv_spangroup_new_span(ui->main_screen_txtIP);
	lv_span_set_text(main_screen_txtIP_span, "IP:    ");
	lv_style_set_text_color(&main_screen_txtIP_span->style, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_decor(&main_screen_txtIP_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&main_screen_txtIP_span->style, &lv_font_montserratMedium_12);

	//create a new span
	main_screen_txtIP_span = lv_spangroup_new_span(ui->main_screen_txtIP);
	lv_span_set_text(main_screen_txtIP_span, "192.168.1.10");
	lv_style_set_text_color(&main_screen_txtIP_span->style, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_decor(&main_screen_txtIP_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&main_screen_txtIP_span->style, &lv_font_montserratMedium_12);
	lv_spangroup_refr_mode(ui->main_screen_txtIP);

	//Write codes main_screen_txtTime
	ui->main_screen_txtTime = lv_label_create(ui->main_screen_cont_1);
	lv_obj_set_pos(ui->main_screen_txtTime, -1, 19);
	lv_obj_set_size(ui->main_screen_txtTime, 130, 30);
	lv_label_set_text(ui->main_screen_txtTime, "12:00");
	lv_label_set_long_mode(ui->main_screen_txtTime, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->main_screen_txtTime, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_main_screen_txttime_main_main_default
	static lv_style_t style_main_screen_txttime_main_main_default;
	lv_style_reset(&style_main_screen_txttime_main_main_default);
	lv_style_set_radius(&style_main_screen_txttime_main_main_default, 0);
	lv_style_set_bg_color(&style_main_screen_txttime_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_main_screen_txttime_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_main_screen_txttime_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_main_screen_txttime_main_main_default, 0);
	lv_style_set_text_color(&style_main_screen_txttime_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_main_screen_txttime_main_main_default, &lv_font_montserratMedium_24);
	lv_style_set_text_letter_space(&style_main_screen_txttime_main_main_default, 2);
	lv_style_set_pad_left(&style_main_screen_txttime_main_main_default, 0);
	lv_style_set_pad_right(&style_main_screen_txttime_main_main_default, 0);
	lv_style_set_pad_top(&style_main_screen_txttime_main_main_default, 0);
	lv_style_set_pad_bottom(&style_main_screen_txttime_main_main_default, 0);
	lv_obj_add_style(ui->main_screen_txtTime, &style_main_screen_txttime_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes main_screen_txtDate
	ui->main_screen_txtDate = lv_label_create(ui->main_screen_cont_1);
	lv_obj_set_pos(ui->main_screen_txtDate, -1, 49);
	lv_obj_set_size(ui->main_screen_txtDate, 130, 16);
	lv_label_set_text(ui->main_screen_txtDate, "Jan. 1");
	lv_label_set_long_mode(ui->main_screen_txtDate, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->main_screen_txtDate, LV_TEXT_ALIGN_CENTER, 0);
}