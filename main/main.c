#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include <freertos/task.h>
#include <stdio.h>

#include <lvgl.h>
#include <lvgl_helpers.h>

#include "events_init.h"
#include "gui_guider.h"

#include "message.h"

#define LV_TICK_PERIOD_MS     1
#define LV_UPDATE_INTERVAL_MS 10

static void task_lv_tick(void* arg);
static void task_GUI(void* pvParameter);

lv_ui guider_ui;
static QueueHandle_t gui_queue = NULL;

static SemaphoreHandle_t xGuiSemaphore = NULL;

void show_main_screen(lv_ui *ui){
	setup_scr_main_screen(ui);
	lv_scr_load(ui->main_screen);
}

void app_main() {
  // Need to create the GUI task pinned to a core.
  xTaskCreatePinnedToCore(task_GUI, "GUI", 4096 * 2, NULL, 0, NULL, 1);

  // This halts execution of the task until the GUI is ready.
  while((xGuiSemaphore == NULL) || (xSemaphoreTake(xGuiSemaphore, portMAX_DELAY) == pdFALSE)) {};
  xSemaphoreGive(xGuiSemaphore);

  uint32_t count = 0;
  char count_str[4] = {0};
  while(1) {
    snprintf(count_str, 4, "%d", count++);
    if (count == 6){
      send_msg_data(gui_queue, GUI_MSG_SHOW_MAIN_SCREEN, 0);
      count++;
    }else if (count < 6){
      // Use the semaphore to gain acccess to LVGL
      xSemaphoreTake(xGuiSemaphore, portMAX_DELAY);
      lv_label_set_text(guider_ui.splash_screen_lbl_dots, count_str);
      xSemaphoreGive(xGuiSemaphore);
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

static void my_UI(){
  setup_ui(&guider_ui);
  events_init(&guider_ui);
}

static void handle_gui_msg(TASK_MSG* msg)
{
  if(msg == NULL)
    return;
  switch(msg->cmd){
    case GUI_MSG_SHOW_MAIN_SCREEN:
      show_main_screen(&guider_ui);
      if (guider_ui.splash_screen != NULL)
      {
        lv_obj_del(guider_ui.splash_screen);
        guider_ui.splash_screen = NULL;
      }
    break;
  }
}

static void task_GUI(void *pvParameter)
{
  TASK_MSG msg;
  BaseType_t status;

  (void) pvParameter;
  xGuiSemaphore = xSemaphoreCreateMutex();

  // Take semaphore initially while setting up GUI
  xSemaphoreTake(xGuiSemaphore, portMAX_DELAY);

  lv_init();

  // Initialize SPI or I2C bus used by the drivers
  lvgl_driver_init();

  lv_color_t* buf1 = (lv_color_t*)heap_caps_malloc(DISP_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_DMA);
  assert(buf1 != NULL);
  lv_color_t* buf2 = NULL;

  static lv_disp_draw_buf_t disp_buf;
  uint32_t size_in_px = DISP_BUF_SIZE;

  lv_disp_draw_buf_init(&disp_buf, buf1, buf2, size_in_px);

  lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = LV_HOR_RES_MAX;
  disp_drv.ver_res = LV_VER_RES_MAX;
  disp_drv.flush_cb = disp_driver_flush;
  disp_drv.draw_buf = &disp_buf;

  lv_disp_drv_register(&disp_drv);

  const esp_timer_create_args_t periodic_timer_args = {
  .callback = &task_lv_tick,
  .arg = (void*)1,
  .dispatch_method = ESP_TIMER_TASK,
  .name = "periodic_gui",
  .skip_unhandled_events = false,
  };

  esp_timer_handle_t periodic_timer;
  ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
  ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, LV_TICK_PERIOD_MS * 1000));

  my_UI();

  xSemaphoreGive(xGuiSemaphore);
  gui_queue = create_msg_queue();

  while(1) {
    vTaskDelay(pdMS_TO_TICKS(LV_UPDATE_INTERVAL_MS));

    // Try to take semaphore and update GUI
    if(pdTRUE == xSemaphoreTake(xGuiSemaphore, portMAX_DELAY)) {
      status = recv_msg(gui_queue, &msg);
      if (status == pdPASS){
        handle_gui_msg(&msg);
      }
      lv_task_handler();
      xSemaphoreGive(xGuiSemaphore);
    }
  }

  // Shouldn't get here.
  del_msg_queue(gui_queue);
  free(buf1);
  free(buf2);
  vTaskDelete(NULL);
}

static void task_lv_tick(void* arg) {
  (void)arg;
  lv_tick_inc(LV_TICK_PERIOD_MS);
}
