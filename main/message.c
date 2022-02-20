#include "message.h"


QueueHandle_t create_msg_queue(void)
{
    return xQueueCreate(TASK_MSG_QUEUE_SIZE, sizeof(TASK_MSG));
}

BaseType_t send_msg(QueueHandle_t queue, TASK_MSG *msg)
{
    if(queue == NULL)
        return pdFAIL;
    return xQueueSend(queue, msg, TASK_MSG_TIMEOUT);
}

BaseType_t send_msg_data(QueueHandle_t queue, int cmd, int arg)
{
    TASK_MSG msg;

    if (queue == NULL)
        return pdFAIL;
    
    msg.cmd = cmd;
    msg.arg = arg;
    return xQueueSend(queue, &msg, TASK_MSG_TIMEOUT);
}

BaseType_t recv_msg(QueueHandle_t queue, TASK_MSG *msg)
{
    if (queue == NULL)
        return pdFAIL;
    return xQueueReceive(queue, msg, 0);
}

void del_msg_queue(QueueHandle_t queue)
{
    if (queue != NULL)
        vQueueDelete(queue);
}