#ifndef MESSAGE_H__
#define MESSAGE_H__

#include "freertos/FreeRTOS.h"
#include <freertos/task.h>
#include "freertos/queue.h"

#define TASK_MSG_QUEUE_SIZE 10
// #define TASK_MSG_TIMEOUT (10 / portTICK_PERIOD_MS)  /* 10ms */
#define TASK_MSG_TIMEOUT pdMS_TO_TICKS(10)          /* 10ms */

typedef struct _TASK_MSG
{
    int cmd;
    int arg;
} TASK_MSG;

/*-------------- message commands -----------------*/
#define GUI_MSG_SHOW_MAIN_SCREEN   0x1

QueueHandle_t create_msg_queue(void);
BaseType_t send_msg(QueueHandle_t queue, TASK_MSG *msg);
BaseType_t send_msg_data(QueueHandle_t queue, int cmd, int arg);
BaseType_t recv_msg(QueueHandle_t queue, TASK_MSG *msg);
void del_msg_queue(QueueHandle_t queue);

#endif /* MESSAGE_H__ */