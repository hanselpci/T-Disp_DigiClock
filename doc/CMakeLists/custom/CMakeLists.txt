if(ESP_PLATFORM)

file(GLOB_RECURSE SOURCES *.c)
set(GUI_GUIDER_COMMON_DIR ${CMAKE_CURRENT_LIST_DIR})

idf_component_register(SRCS ${SOURCES}
                       INCLUDE_DIRS ${GUI_GUIDER_COMMON_DIR} 
                       REQUIRES generated lvgl)

else()
    message(FATAL_ERROR "LVGL LV generated: ESP_PLATFORM is not defined.")
endif()
