if(ESP_PLATFORM)

file(GLOB_RECURSE SOURCES *.c ./images/*.c)
set(GUI_GUIDER_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})

idf_component_register(SRCS ${SOURCES}
                       INCLUDE_DIRS ${GUI_GUIDER_ROOT_DIR} ${GUI_GUIDER_ROOT_DIR}/guider_customer_fonts
                            ${GUI_GUIDER_ROOT_DIR}/guider_fonts
                            ${GUI_GUIDER_ROOT_DIR}/images
                            $ENV{IDF_EXTRA_COMPONENT_DIRS}/lvgl/src/font
                       REQUIRES lvgl
                       PRIV_REQUIRES custom)

else()
    message(FATAL_ERROR "LVGL LV generated: ESP_PLATFORM is not defined.")
endif()
