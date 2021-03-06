#ifndef TASK_HANDLER_H
#define TASK_HANDLER_H

typedef struct
{
    char payload[10];
    uint8_t len;
} command_t;

void task_handler_cmd(void* parameters);
int extract_command(command_t* command);
void process_command(command_t* command);

void task_handler_led(void* parameters);
void task_handler_menu(void* parameters);
void task_handler_print(void* parameters);
void task_handler_rtc(void* parameters);

#endif
