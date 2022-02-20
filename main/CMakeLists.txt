
file(GLOB_RECURSE SOURCES *.c)
set(INCLUDES .)

idf_component_register(SRCS ${SOURCES}
                    INCLUDE_DIRS ${INCLUDES}
					REQUIRES lvgl lvgl_esp32_drivers generated custom)
