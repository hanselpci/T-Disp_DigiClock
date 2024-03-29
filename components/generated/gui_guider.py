# Copyright 2021 NXP
# SPDX-License-Identifier: MIT

import SDL
import utime as time
import usys as sys
import lvgl as lv
import lodepng as png
import ustruct

lv.init()
SDL.init(w=135,h=240)

# Register SDL display driver.
disp_buf1 = lv.disp_draw_buf_t()
buf1_1 = bytearray(135*10)
disp_buf1.init(buf1_1, None, len(buf1_1)//4)
disp_drv = lv.disp_drv_t()
disp_drv.init()
disp_drv.draw_buf = disp_buf1
disp_drv.flush_cb = SDL.monitor_flush
disp_drv.hor_res = 135
disp_drv.ver_res = 240
disp_drv.register()

# Regsiter SDL mouse driver
indev_drv = lv.indev_drv_t()
indev_drv.init() 
indev_drv.type = lv.INDEV_TYPE.POINTER
indev_drv.read_cb = SDL.mouse_read
indev_drv.register()

# Below: Taken from https://github.com/lvgl/lv_binding_micropython/blob/master/driver/js/imagetools.py#L22-L94

COLOR_SIZE = lv.color_t.__SIZE__
COLOR_IS_SWAPPED = hasattr(lv.color_t().ch,'green_h')

class lodepng_error(RuntimeError):
    def __init__(self, err):
        if type(err) is int:
            super().__init__(png.error_text(err))
        else:
            super().__init__(err)

# Parse PNG file header
# Taken from https://github.com/shibukawa/imagesize_py/blob/ffef30c1a4715c5acf90e8945ceb77f4a2ed2d45/imagesize.py#L63-L85

def get_png_info(decoder, src, header):
    # Only handle variable image types

    if lv.img.src_get_type(src) != lv.img.SRC.VARIABLE:
        return lv.RES.INV

    data = lv.img_dsc_t.__cast__(src).data
    if data == None:
        return lv.RES.INV

    png_header = bytes(data.__dereference__(24))

    if png_header.startswith(b'\211PNG\r\n\032\n'):
        if png_header[12:16] == b'IHDR':
            start = 16
        # Maybe this is for an older PNG version.
        else:
            start = 8
        try:
            width, height = ustruct.unpack(">LL", png_header[start:start+8])
        except ustruct.error:
            return lv.RES.INV
    else:
        return lv.RES.INV

    header.always_zero = 0
    header.w = width
    header.h = height
    header.cf = lv.img.CF.TRUE_COLOR_ALPHA

    return lv.RES.OK

def convert_rgba8888_to_bgra8888(img_view):
    for i in range(0, len(img_view), lv.color_t.__SIZE__):
        ch = lv.color_t.__cast__(img_view[i:i]).ch
        ch.red, ch.blue = ch.blue, ch.red

# Read and parse PNG file

def open_png(decoder, dsc):
    img_dsc = lv.img_dsc_t.__cast__(dsc.src)
    png_data = img_dsc.data
    png_size = img_dsc.data_size
    png_decoded = png.C_Pointer()
    png_width = png.C_Pointer()
    png_height = png.C_Pointer()
    error = png.decode32(png_decoded, png_width, png_height, png_data, png_size)
    if error:
        raise lodepng_error(error)
    img_size = png_width.int_val * png_height.int_val * 4
    img_data = png_decoded.ptr_val
    img_view = img_data.__dereference__(img_size)

    if COLOR_SIZE == 4:
        convert_rgba8888_to_bgra8888(img_view)
    else:
        raise lodepng_error("Error: Color mode not supported yet!")

    dsc.img_data = img_data
    return lv.RES.OK

# Above: Taken from https://github.com/lvgl/lv_binding_micropython/blob/master/driver/js/imagetools.py#L22-L94

decoder = lv.img.decoder_create()
decoder.info_cb = get_png_info
decoder.open_cb = open_png

def anim_x_cb(obj, v):
    obj.set_x(v)

def anim_y_cb(obj, v):
    obj.set_y(v)

def ta_event_cb(e,kb):
    code = e.get_code()
    ta = e.get_target()
    if code == lv.EVENT.FOCUSED:
        kb.set_textarea(ta)
        kb.clear_flag(lv.obj.FLAG.HIDDEN)

    if code == lv.EVENT.DEFOCUSED:
        kb.set_textarea(None)
        kb.add_flag(lv.obj.FLAG.HIDDEN)


splash_screen = lv.obj()
# create style style_splash_screen_main_main_default
style_splash_screen_main_main_default = lv.style_t()
style_splash_screen_main_main_default.init()
style_splash_screen_main_main_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_splash_screen_main_main_default.set_bg_opa(0)

# add style for splash_screen
splash_screen.add_style(style_splash_screen_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

splash_screen_cont_1 = lv.obj(splash_screen)
splash_screen_cont_1.set_pos(1,1)
splash_screen_cont_1.set_size(133,238)
splash_screen_lbl_title = lv.label(splash_screen_cont_1)
splash_screen_lbl_title.set_pos(0,73)
splash_screen_lbl_title.set_size(133,30)
splash_screen_lbl_title.set_text("网络数字钟")
splash_screen_lbl_title.set_long_mode(lv.label.LONG.WRAP)
splash_screen_lbl_title.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_splash_screen_lbl_title_main_main_default
style_splash_screen_lbl_title_main_main_default = lv.style_t()
style_splash_screen_lbl_title_main_main_default.init()
style_splash_screen_lbl_title_main_main_default.set_radius(0)
style_splash_screen_lbl_title_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_splash_screen_lbl_title_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_splash_screen_lbl_title_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_splash_screen_lbl_title_main_main_default.set_bg_opa(0)
style_splash_screen_lbl_title_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_splash_screen_lbl_title_main_main_default.set_text_font(lv.font_simsun_18)
except AttributeError:
    try:
        style_splash_screen_lbl_title_main_main_default.set_text_font(lv.font_montserrat_18)
    except AttributeError:
        style_splash_screen_lbl_title_main_main_default.set_text_font(lv.font_montserrat_16)
style_splash_screen_lbl_title_main_main_default.set_text_letter_space(2)
style_splash_screen_lbl_title_main_main_default.set_pad_left(0)
style_splash_screen_lbl_title_main_main_default.set_pad_right(0)
style_splash_screen_lbl_title_main_main_default.set_pad_top(0)
style_splash_screen_lbl_title_main_main_default.set_pad_bottom(0)

# add style for splash_screen_lbl_title
splash_screen_lbl_title.add_style(style_splash_screen_lbl_title_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

splash_screen_lbl_version = lv.label(splash_screen_cont_1)
splash_screen_lbl_version.set_pos(0,102)
splash_screen_lbl_version.set_size(133,30)
splash_screen_lbl_version.set_text("v1.0")
splash_screen_lbl_version.set_long_mode(lv.label.LONG.WRAP)
splash_screen_lbl_version.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_splash_screen_lbl_version_main_main_default
style_splash_screen_lbl_version_main_main_default = lv.style_t()
style_splash_screen_lbl_version_main_main_default.init()
style_splash_screen_lbl_version_main_main_default.set_radius(0)
style_splash_screen_lbl_version_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_splash_screen_lbl_version_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_splash_screen_lbl_version_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_splash_screen_lbl_version_main_main_default.set_bg_opa(0)
style_splash_screen_lbl_version_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_splash_screen_lbl_version_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_splash_screen_lbl_version_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_splash_screen_lbl_version_main_main_default.set_text_font(lv.font_montserrat_16)
style_splash_screen_lbl_version_main_main_default.set_text_letter_space(2)
style_splash_screen_lbl_version_main_main_default.set_pad_left(0)
style_splash_screen_lbl_version_main_main_default.set_pad_right(0)
style_splash_screen_lbl_version_main_main_default.set_pad_top(0)
style_splash_screen_lbl_version_main_main_default.set_pad_bottom(0)

# add style for splash_screen_lbl_version
splash_screen_lbl_version.add_style(style_splash_screen_lbl_version_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

splash_screen_lbl_status = lv.label(splash_screen_cont_1)
splash_screen_lbl_status.set_pos(10,202)
splash_screen_lbl_status.set_size(91,20)
splash_screen_lbl_status.set_text("网络连接中.")
splash_screen_lbl_status.set_long_mode(lv.label.LONG.WRAP)
splash_screen_lbl_status.set_style_text_align(lv.TEXT_ALIGN.LEFT, 0)
# create style style_splash_screen_lbl_status_main_main_default
style_splash_screen_lbl_status_main_main_default = lv.style_t()
style_splash_screen_lbl_status_main_main_default.init()
style_splash_screen_lbl_status_main_main_default.set_radius(0)
style_splash_screen_lbl_status_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_splash_screen_lbl_status_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_splash_screen_lbl_status_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_splash_screen_lbl_status_main_main_default.set_bg_opa(0)
style_splash_screen_lbl_status_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_splash_screen_lbl_status_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_splash_screen_lbl_status_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_splash_screen_lbl_status_main_main_default.set_text_font(lv.font_montserrat_16)
style_splash_screen_lbl_status_main_main_default.set_text_letter_space(2)
style_splash_screen_lbl_status_main_main_default.set_pad_left(0)
style_splash_screen_lbl_status_main_main_default.set_pad_right(0)
style_splash_screen_lbl_status_main_main_default.set_pad_top(0)
style_splash_screen_lbl_status_main_main_default.set_pad_bottom(0)

# add style for splash_screen_lbl_status
splash_screen_lbl_status.add_style(style_splash_screen_lbl_status_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

splash_screen_lbl_dots = lv.label(splash_screen_cont_1)
splash_screen_lbl_dots.set_pos(87,202)
splash_screen_lbl_dots.set_size(36,20)
splash_screen_lbl_dots.set_text("0")
splash_screen_lbl_dots.set_long_mode(lv.label.LONG.WRAP)
splash_screen_lbl_dots.set_style_text_align(lv.TEXT_ALIGN.LEFT, 0)
# create style style_splash_screen_lbl_dots_main_main_default
style_splash_screen_lbl_dots_main_main_default = lv.style_t()
style_splash_screen_lbl_dots_main_main_default.init()
style_splash_screen_lbl_dots_main_main_default.set_radius(0)
style_splash_screen_lbl_dots_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_splash_screen_lbl_dots_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_splash_screen_lbl_dots_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_splash_screen_lbl_dots_main_main_default.set_bg_opa(0)
style_splash_screen_lbl_dots_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_splash_screen_lbl_dots_main_main_default.set_text_font(lv.font_simsun_12)
except AttributeError:
    try:
        style_splash_screen_lbl_dots_main_main_default.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        style_splash_screen_lbl_dots_main_main_default.set_text_font(lv.font_montserrat_16)
style_splash_screen_lbl_dots_main_main_default.set_text_letter_space(2)
style_splash_screen_lbl_dots_main_main_default.set_pad_left(0)
style_splash_screen_lbl_dots_main_main_default.set_pad_right(0)
style_splash_screen_lbl_dots_main_main_default.set_pad_top(0)
style_splash_screen_lbl_dots_main_main_default.set_pad_bottom(0)

# add style for splash_screen_lbl_dots
splash_screen_lbl_dots.add_style(style_splash_screen_lbl_dots_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_splash_screen_cont_1_main_main_default
style_splash_screen_cont_1_main_main_default = lv.style_t()
style_splash_screen_cont_1_main_main_default.init()
style_splash_screen_cont_1_main_main_default.set_radius(0)
style_splash_screen_cont_1_main_main_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_splash_screen_cont_1_main_main_default.set_bg_grad_color(lv.color_make(0xff,0xff,0xff))
style_splash_screen_cont_1_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_splash_screen_cont_1_main_main_default.set_bg_opa(255)
style_splash_screen_cont_1_main_main_default.set_border_color(lv.color_make(0x00,0x00,0x00))
style_splash_screen_cont_1_main_main_default.set_border_width(0)
style_splash_screen_cont_1_main_main_default.set_border_opa(255)
style_splash_screen_cont_1_main_main_default.set_pad_left(0)
style_splash_screen_cont_1_main_main_default.set_pad_right(0)
style_splash_screen_cont_1_main_main_default.set_pad_top(0)
style_splash_screen_cont_1_main_main_default.set_pad_bottom(0)

# add style for splash_screen_cont_1
splash_screen_cont_1.add_style(style_splash_screen_cont_1_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

main_screen = lv.obj()
# create style style_main_screen_main_main_default
style_main_screen_main_main_default = lv.style_t()
style_main_screen_main_main_default.init()
style_main_screen_main_main_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_main_screen_main_main_default.set_bg_opa(0)

# add style for main_screen
main_screen.add_style(style_main_screen_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

main_screen_cont_1 = lv.obj(main_screen)
main_screen_cont_1.set_pos(1,1)
main_screen_cont_1.set_size(133,238)
main_screen_txtWeather = lv.spangroup(main_screen_cont_1)
main_screen_txtWeather.set_pos(1,174)
main_screen_txtWeather.set_size(130,28)
main_screen_txtWeather.set_align(lv.TEXT_ALIGN.LEFT)
main_screen_txtWeather.set_overflow(lv.SPAN_OVERFLOW.CLIP)
main_screen_txtWeather.set_mode(lv.SPAN_MODE.BREAK)
main_screen_txtWeather_span = main_screen_txtWeather.new_span()
main_screen_txtWeather_span.set_text("Weather:    ")
main_screen_txtWeather_span.style.set_text_color(lv.color_make(0x00,0x00,0x00))
main_screen_txtWeather_span.style.set_text_decor(lv.TEXT_DECOR.NONE)
try:
    main_screen_txtWeather_span.style.set_text_font(lv.font_montserratMedium_12)
except AttributeError:
    try:
        main_screen_txtWeather_span.style.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        main_screen_txtWeather_span.style.set_text_font(lv.font_montserrat_16)
main_screen_txtWeather_span = main_screen_txtWeather.new_span()
main_screen_txtWeather_span.set_text("10 / Rain")
main_screen_txtWeather_span.style.set_text_color(lv.color_make(0x00,0x00,0x00))
main_screen_txtWeather_span.style.set_text_decor(lv.TEXT_DECOR.NONE)
try:
    main_screen_txtWeather_span.style.set_text_font(lv.font_montserratMedium_12)
except AttributeError:
    try:
        main_screen_txtWeather_span.style.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        main_screen_txtWeather_span.style.set_text_font(lv.font_montserrat_16)
main_screen_txtWeather.refr_mode()
main_screen_txtLocation = lv.spangroup(main_screen_cont_1)
main_screen_txtLocation.set_pos(1,152)
main_screen_txtLocation.set_size(130,28)
main_screen_txtLocation.set_align(lv.TEXT_ALIGN.LEFT)
main_screen_txtLocation.set_overflow(lv.SPAN_OVERFLOW.CLIP)
main_screen_txtLocation.set_mode(lv.SPAN_MODE.BREAK)
main_screen_txtLocation_span = main_screen_txtLocation.new_span()
main_screen_txtLocation_span.set_text("Location:    ")
main_screen_txtLocation_span.style.set_text_color(lv.color_make(0x00,0x00,0x00))
main_screen_txtLocation_span.style.set_text_decor(lv.TEXT_DECOR.NONE)
try:
    main_screen_txtLocation_span.style.set_text_font(lv.font_montserratMedium_12)
except AttributeError:
    try:
        main_screen_txtLocation_span.style.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        main_screen_txtLocation_span.style.set_text_font(lv.font_montserrat_16)
main_screen_txtLocation_span = main_screen_txtLocation.new_span()
main_screen_txtLocation_span.set_text("Shenzhen")
main_screen_txtLocation_span.style.set_text_color(lv.color_make(0x00,0x00,0x00))
main_screen_txtLocation_span.style.set_text_decor(lv.TEXT_DECOR.NONE)
try:
    main_screen_txtLocation_span.style.set_text_font(lv.font_montserratMedium_12)
except AttributeError:
    try:
        main_screen_txtLocation_span.style.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        main_screen_txtLocation_span.style.set_text_font(lv.font_montserrat_16)
main_screen_txtLocation.refr_mode()
main_screen_txtIP = lv.spangroup(main_screen_cont_1)
main_screen_txtIP.set_pos(1,129)
main_screen_txtIP.set_size(130,20)
main_screen_txtIP.set_align(lv.TEXT_ALIGN.LEFT)
main_screen_txtIP.set_overflow(lv.SPAN_OVERFLOW.CLIP)
main_screen_txtIP.set_mode(lv.SPAN_MODE.BREAK)
main_screen_txtIP_span = main_screen_txtIP.new_span()
main_screen_txtIP_span.set_text("IP:    ")
main_screen_txtIP_span.style.set_text_color(lv.color_make(0x00,0x00,0x00))
main_screen_txtIP_span.style.set_text_decor(lv.TEXT_DECOR.NONE)
try:
    main_screen_txtIP_span.style.set_text_font(lv.font_montserratMedium_12)
except AttributeError:
    try:
        main_screen_txtIP_span.style.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        main_screen_txtIP_span.style.set_text_font(lv.font_montserrat_16)
main_screen_txtIP_span = main_screen_txtIP.new_span()
main_screen_txtIP_span.set_text("192.168.1.10")
main_screen_txtIP_span.style.set_text_color(lv.color_make(0x00,0x00,0x00))
main_screen_txtIP_span.style.set_text_decor(lv.TEXT_DECOR.NONE)
try:
    main_screen_txtIP_span.style.set_text_font(lv.font_montserratMedium_12)
except AttributeError:
    try:
        main_screen_txtIP_span.style.set_text_font(lv.font_montserrat_12)
    except AttributeError:
        main_screen_txtIP_span.style.set_text_font(lv.font_montserrat_16)
main_screen_txtIP.refr_mode()
main_screen_txtTime = lv.label(main_screen_cont_1)
main_screen_txtTime.set_pos(-1,19)
main_screen_txtTime.set_size(130,30)
main_screen_txtTime.set_text("12:00")
main_screen_txtTime.set_long_mode(lv.label.LONG.WRAP)
main_screen_txtTime.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_main_screen_txttime_main_main_default
style_main_screen_txttime_main_main_default = lv.style_t()
style_main_screen_txttime_main_main_default.init()
style_main_screen_txttime_main_main_default.set_radius(0)
style_main_screen_txttime_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_main_screen_txttime_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_main_screen_txttime_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_main_screen_txttime_main_main_default.set_bg_opa(0)
style_main_screen_txttime_main_main_default.set_text_color(lv.color_make(0x00,0x00,0x00))
try:
    style_main_screen_txttime_main_main_default.set_text_font(lv.font_montserratMedium_24)
except AttributeError:
    try:
        style_main_screen_txttime_main_main_default.set_text_font(lv.font_montserrat_24)
    except AttributeError:
        style_main_screen_txttime_main_main_default.set_text_font(lv.font_montserrat_16)
style_main_screen_txttime_main_main_default.set_text_letter_space(2)
style_main_screen_txttime_main_main_default.set_pad_left(0)
style_main_screen_txttime_main_main_default.set_pad_right(0)
style_main_screen_txttime_main_main_default.set_pad_top(0)
style_main_screen_txttime_main_main_default.set_pad_bottom(0)

# add style for main_screen_txtTime
main_screen_txtTime.add_style(style_main_screen_txttime_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

main_screen_txtDate = lv.label(main_screen_cont_1)
main_screen_txtDate.set_pos(-1,49)
main_screen_txtDate.set_size(130,16)
main_screen_txtDate.set_text("Jan. 1")
main_screen_txtDate.set_long_mode(lv.label.LONG.WRAP)
main_screen_txtDate.set_style_text_align(lv.TEXT_ALIGN.CENTER, 0)
# create style style_main_screen_cont_1_main_main_default
style_main_screen_cont_1_main_main_default = lv.style_t()
style_main_screen_cont_1_main_main_default.init()
style_main_screen_cont_1_main_main_default.set_radius(0)
style_main_screen_cont_1_main_main_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_main_screen_cont_1_main_main_default.set_bg_grad_color(lv.color_make(0xff,0xff,0xff))
style_main_screen_cont_1_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_main_screen_cont_1_main_main_default.set_bg_opa(255)
style_main_screen_cont_1_main_main_default.set_border_color(lv.color_make(0x00,0x00,0x00))
style_main_screen_cont_1_main_main_default.set_border_width(0)
style_main_screen_cont_1_main_main_default.set_border_opa(255)
style_main_screen_cont_1_main_main_default.set_pad_left(0)
style_main_screen_cont_1_main_main_default.set_pad_right(0)
style_main_screen_cont_1_main_main_default.set_pad_top(0)
style_main_screen_cont_1_main_main_default.set_pad_bottom(0)

# add style for main_screen_cont_1
main_screen_cont_1.add_style(style_main_screen_cont_1_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)




# content from custom.py

# Load the default screen
lv.scr_load(splash_screen)

while SDL.check():
    time.sleep_ms(5)
