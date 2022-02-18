#include "main.h"

void task_handler_cmd(void* parameters)
{
    BaseType_t notify_status;
    command_t command;

    while(1)
    {
        notify_status = xTaskNotifyWait(0x00, 0x00, NULL, portMAX_DELAY);
        if (pdTRUE == notify_status)
        {
            process_command(&command);
        }
    }
}

void process_command(command_t *command)
{
    extract_command(command);

    switch(current_state)
    {
        case sMainMenu:
            xTaskNotify(handle_menu_task, (size_t)command, eSetValueWithOverwrite);
            break;

        case sLedEffect:
            xTaskNotify(handle_led_task, (size_t)command, eSetValueWithOverwrite);
            break;

        case sRtcMenu:
        case sRtcTimeConfig:
        case sRtcDateConfig:
        case sRtcReport:
            xTaskNotify(handle_rtc_task, (size_t)command, eSetValueWithOverwrite);
            break;
    }
}

int extract_command(command_t* command)
{
    char msg_char;
    BaseType_t status;

    status = uxQueueMessagesWaiting(queue_data);
    if (!status)
        return -1;

    uint8_t idx = 0;
    do
    {
        status = xQueueReceive(queue_data, &msg_char, 0);
        if (pdTRUE == status)
            command->payload[idx++] = msg_char;
    } while(msg_char != '\n');

    command->payload[idx-1] = '\0'; // rewrite the last char '\n'
    command->len = idx-1; // save length of the string excluding the null char

    return 0;
}

void task_handler_led(void* parameters)
{
    while(1)
    {

    }
}

void task_handler_menu(void* parameters)
{
    while(1)
    {

    }
}

void task_handler_print(void* parameters)
{
    while(1)
    {

    }
}

void task_handler_rtc(void* parameters)
{
    while(1)
    {

    }
}
