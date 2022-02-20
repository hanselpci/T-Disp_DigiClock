/*
 * Copyright 2022 NXP
 * SPDX-License-Identifier: MIT
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"


void setup_scr_splash_screen(lv_ui *ui){

	//Write codes splash_screen
	ui->splash_screen = lv_obj_create(NULL);

	//Write style state: LV_STATE_DEFAULT for style_splash_screen_main_main_default
	static lv_style_t style_splash_screen_main_main_default;
	lv_style_reset(&style_splash_screen_main_main_default);
	lv_style_set_bg_color(&style_splash_screen_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_opa(&style_splash_screen_main_main_default, 0);
	lv_obj_add_style(ui->splash_screen, &style_splash_screen_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes splash_screen_cont_1
	ui->splash_screen_cont_1 = lv_obj_create(ui->splash_screen);
	lv_obj_set_pos(ui->splash_screen_cont_1, 1, 1);
	lv_obj_set_size(ui->splash_screen_cont_1, 133, 238);

	//Write style state: LV_STATE_DEFAULT for style_splash_screen_cont_1_main_main_default
	static lv_style_t style_splash_screen_cont_1_main_main_default;
	lv_style_reset(&style_splash_screen_cont_1_main_main_default);
	lv_style_set_radius(&style_splash_screen_cont_1_main_main_default, 0);
	lv_style_set_bg_color(&style_splash_screen_cont_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_splash_screen_cont_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_splash_screen_cont_1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_splash_screen_cont_1_main_main_default, 255);
	lv_style_set_border_color(&style_splash_screen_cont_1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_border_width(&style_splash_screen_cont_1_main_main_default, 0);
	lv_style_set_border_opa(&style_splash_screen_cont_1_main_main_default, 255);
	lv_style_set_pad_left(&style_splash_screen_cont_1_main_main_default, 0);
	lv_style_set_pad_right(&style_splash_screen_cont_1_main_main_default, 0);
	lv_style_set_pad_top(&style_splash_screen_cont_1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_splash_screen_cont_1_main_main_default, 0);
	lv_obj_add_style(ui->splash_screen_cont_1, &style_splash_screen_cont_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes splash_screen_lbl_title
	ui->splash_screen_lbl_title = lv_label_create(ui->splash_screen_cont_1);
	lv_obj_set_pos(ui->splash_screen_lbl_title, 0, 73);
	lv_obj_set_size(ui->splash_screen_lbl_title, 133, 30);
	lv_label_set_text(ui->splash_screen_lbl_title, "网络数字钟");
	lv_label_set_long_mode(ui->splash_screen_lbl_title, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->splash_screen_lbl_title, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_splash_screen_lbl_title_main_main_default
	static lv_style_t style_splash_screen_lbl_title_main_main_default;
	lv_style_reset(&style_splash_screen_lbl_title_main_main_default);
	lv_style_set_radius(&style_splash_screen_lbl_title_main_main_default, 0);
	lv_style_set_bg_color(&style_splash_screen_lbl_title_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_splash_screen_lbl_title_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_splash_screen_lbl_title_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_splash_screen_lbl_title_main_main_default, 0);
	lv_style_set_text_color(&style_splash_screen_lbl_title_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_splash_screen_lbl_title_main_main_default, &lv_font_simsun_18);
	lv_style_set_text_letter_space(&style_splash_screen_lbl_title_main_main_default, 2);
	lv_style_set_pad_left(&style_splash_screen_lbl_title_main_main_default, 0);
	lv_style_set_pad_right(&style_splash_screen_lbl_title_main_main_default, 0);
	lv_style_set_pad_top(&style_splash_screen_lbl_title_main_main_default, 0);
	lv_style_set_pad_bottom(&style_splash_screen_lbl_title_main_main_default, 0);
	lv_obj_add_style(ui->splash_screen_lbl_title, &style_splash_screen_lbl_title_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes splash_screen_lbl_version
	ui->splash_screen_lbl_version = lv_label_create(ui->splash_screen_cont_1);
	lv_obj_set_pos(ui->splash_screen_lbl_version, 0, 102);
	lv_obj_set_size(ui->splash_screen_lbl_version, 133, 30);
	lv_label_set_text(ui->splash_screen_lbl_version, "v1.0");
	lv_label_set_long_mode(ui->splash_screen_lbl_version, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->splash_screen_lbl_version, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_splash_screen_lbl_version_main_main_default
	static lv_style_t style_splash_screen_lbl_version_main_main_default;
	lv_style_reset(&style_splash_screen_lbl_version_main_main_default);
	lv_style_set_radius(&style_splash_screen_lbl_version_main_main_default, 0);
	lv_style_set_bg_color(&style_splash_screen_lbl_version_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_splash_screen_lbl_version_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_splash_screen_lbl_version_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_splash_screen_lbl_version_main_main_default, 0);
	lv_style_set_text_color(&style_splash_screen_lbl_version_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_splash_screen_lbl_version_main_main_default, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_splash_screen_lbl_version_main_main_default, 2);
	lv_style_set_pad_left(&style_splash_screen_lbl_version_main_main_default, 0);
	lv_style_set_pad_right(&style_splash_screen_lbl_version_main_main_default, 0);
	lv_style_set_pad_top(&style_splash_screen_lbl_version_main_main_default, 0);
	lv_style_set_pad_bottom(&style_splash_screen_lbl_version_main_main_default, 0);
	lv_obj_add_style(ui->splash_screen_lbl_version, &style_splash_screen_lbl_version_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes splash_screen_lbl_status
	ui->splash_screen_lbl_status = lv_label_create(ui->splash_screen_cont_1);
	lv_obj_set_pos(ui->splash_screen_lbl_status, 10, 202);
	lv_obj_set_size(ui->splash_screen_lbl_status, 91, 20);
	lv_label_set_text(ui->splash_screen_lbl_status, "网络连接中.");
	lv_label_set_long_mode(ui->splash_screen_lbl_status, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->splash_screen_lbl_status, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_splash_screen_lbl_status_main_main_default
	static lv_style_t style_splash_screen_lbl_status_main_main_default;
	lv_style_reset(&style_splash_screen_lbl_status_main_main_default);
	lv_style_set_radius(&style_splash_screen_lbl_status_main_main_default, 0);
	lv_style_set_bg_color(&style_splash_screen_lbl_status_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_splash_screen_lbl_status_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_splash_screen_lbl_status_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_splash_screen_lbl_status_main_main_default, 0);
	lv_style_set_text_color(&style_splash_screen_lbl_status_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_splash_screen_lbl_status_main_main_default, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_splash_screen_lbl_status_main_main_default, 2);
	lv_style_set_pad_left(&style_splash_screen_lbl_status_main_main_default, 0);
	lv_style_set_pad_right(&style_splash_screen_lbl_status_main_main_default, 0);
	lv_style_set_pad_top(&style_splash_screen_lbl_status_main_main_default, 0);
	lv_style_set_pad_bottom(&style_splash_screen_lbl_status_main_main_default, 0);
	lv_obj_add_style(ui->splash_screen_lbl_status, &style_splash_screen_lbl_status_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes splash_screen_lbl_dots
	ui->splash_screen_lbl_dots = lv_label_create(ui->splash_screen_cont_1);
	lv_obj_set_pos(ui->splash_screen_lbl_dots, 87, 202);
	lv_obj_set_size(ui->splash_screen_lbl_dots, 36, 20);
	lv_label_set_text(ui->splash_screen_lbl_dots, "0");
	lv_label_set_long_mode(ui->splash_screen_lbl_dots, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->splash_screen_lbl_dots, LV_TEXT_ALIGN_LEFT, 0);

	//Write style state: LV_STATE_DEFAULT for style_splash_screen_lbl_dots_main_main_default
	static lv_style_t style_splash_screen_lbl_dots_main_main_default;
	lv_style_reset(&style_splash_screen_lbl_dots_main_main_default);
	lv_style_set_radius(&style_splash_screen_lbl_dots_main_main_default, 0);
	lv_style_set_bg_color(&style_splash_screen_lbl_dots_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_splash_screen_lbl_dots_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_splash_screen_lbl_dots_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_splash_screen_lbl_dots_main_main_default, 0);
	lv_style_set_text_color(&style_splash_screen_lbl_dots_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_splash_screen_lbl_dots_main_main_default, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_splash_screen_lbl_dots_main_main_default, 2);
	lv_style_set_pad_left(&style_splash_screen_lbl_dots_main_main_default, 0);
	lv_style_set_pad_right(&style_splash_screen_lbl_dots_main_main_default, 0);
	lv_style_set_pad_top(&style_splash_screen_lbl_dots_main_main_default, 0);
	lv_style_set_pad_bottom(&style_splash_screen_lbl_dots_main_main_default, 0);
	lv_obj_add_style(ui->splash_screen_lbl_dots, &style_splash_screen_lbl_dots_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
}