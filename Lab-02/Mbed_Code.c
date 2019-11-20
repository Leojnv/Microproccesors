#include "mbed.h"
#include <stdbool.h>
#define DELAY 50
#define MODE_1 4
#define MODE_2 5
#define MODE_3 31


DigitalIn PB_UP(PD_6);
DigitalIn PB_DOWN(PD_7);

DigitalOut led0(A0);        // PA3
DigitalOut led1(A5);        // PF10
DigitalOut led2(A4);        // PF5
DigitalOut led3(A3);        // PF3
DigitalOut led4(A2);        // PC3
DigitalOut led5(A1);        // PC0

typedef struct {
    int delay;              // Delay in order to debounce
    int counter;            // Counter that will help to determine stable state

    bool state;             // Stable state
    bool state_raw;         // Raw input
    bool edge_rise;         // For Pull-Up
    bool edge_fall;         // For Pull-Down
} Button;

typedef struct {
    int status;
    int counter_slow;
    int counter;
} blinker_led;

void init_blink(blinker_led *led);
int blink(blinker_led *led, int high_count, int low_count, int *counter);

void initButton(Button *button, bool initialState);
void debounce(Button *button, bool entry);
int getRiseEdge(Button *btn);
int getFallEdge(Button *btn);

void counter_ud(int bottom_count, int top_count, int *counter);
void display_1(int bottom_count, int top_count, int *counter);
void display_2(int bottom_count, int top_count, int *counter);
void display_3(int bottom_count, int top_count, int *counter);

Button btnUp;
Button btnDown;

int main()
{

    blinker_led led_0;

    initButton(&btnUp, false);
    initButton(&btnDown, false);
    init_blink(&led_0);

    int counter_mode = 0;

    while(1) {
        led0 = blink(&led_0, 500, 500, &led_0.counter);
        counter_ud(0,MODE_1, &counter_mode);
        debounce(&btnUp, PB_UP);
        debounce(&btnDown, PB_DOWN);        
        wait(0.001);
    }
}
void counter_ud(int bottom_count, int top_count, int *counter_mode)
{
    switch (top_count) {
        case MODE_1:
            display_1(bottom_count, top_count, counter_mode);
            break;
        case MODE_2:
            display_2(bottom_count, top_count, counter_mode);
            break;
        case MODE_3:
            display_3(bottom_count, top_count, counter_mode);
            break;
        default:
            break;
    }
}
void display_1(int bottom_count, int top_count, int *counter_mode)
{

    if(*counter_mode >= bottom_count && *counter_mode <= top_count) {

        if(getFallEdge(&btnUp) && *counter_mode < top_count)
            (*counter_mode)++;
        if(getFallEdge(&btnDown) && *counter_mode > bottom_count)
            (*counter_mode)--;

        led1 = ( *counter_mode == 0 );
        led2 = ( *counter_mode == 1 );
        led3 = ( *counter_mode == 2 );
        led4 = ( *counter_mode == 3 );
        led5 = ( *counter_mode == 4 );
    }
}
void display_2(int bottom_count, int top_count, int *counter_mode)
{

    if(*counter_mode >= bottom_count && *counter_mode <= top_count) {

        if(getFallEdge(&btnUp) && *counter_mode < top_count)
            (*counter_mode)++;
        if(getFallEdge(&btnDown) && *counter_mode > bottom_count)
            (*counter_mode)--;

        *counter_mode > 0 ? led1 = 1 : led1 = 0;
        *counter_mode > 1 ? led2 = 1 : led2 = 0;
        *counter_mode > 2 ? led3 = 1 : led3 = 0;
        *counter_mode > 3 ? led4 = 1 : led4 = 0;
        *counter_mode > 4 ? led5 = 1 : led5 = 0;
    }
}
void display_3(int bottom_count, int top_count, int *counter_mode)
{

    if(*counter_mode >= bottom_count && *counter_mode <= top_count) {

        if(getFallEdge(&btnUp) && *counter_mode < top_count)
            (*counter_mode)++;
        if(getFallEdge(&btnDown) && *counter_mode > bottom_count)
            (*counter_mode)--;

        led1 = ( *counter_mode & (1<<0) );
        led2 = ( *counter_mode & (1<<1) );
        led3 = ( *counter_mode & (1<<2) );
        led4 = ( *counter_mode & (1<<3) );
        led5 = ( *counter_mode & (1<<4) );
    }
}
void init_blink(blinker_led *led)
{
    led->status = 0;
    led->counter_slow = 0;
    led->counter = 0;
}

int blink(blinker_led *led, int high_count, int low_count, int *counter)
{
    *counter += 1;
    if(led->status == 1 && *counter == high_count) {
        *counter = 0;
        led->status = 0;
    }
    if(led->status == 0 && *counter == low_count) {
        *counter = 0;
        led->status = 1;
    }
    return led->status;
}

void initButton(Button *button, bool initialState)
{
    button->delay = DELAY;
    button->counter = 0;
    button->state = initialState;
    button->state_raw = initialState;
    button->edge_rise = false;
    button->edge_fall = false;
}

void debounce(Button *button, bool entry)
{
    button->edge_rise = false;
    button->edge_fall = false;
    button->state_raw = entry;

    button->counter++;

    if(button->state == button->state_raw)
        button->counter = 0;

    if(button->counter >= button->delay) {
        button->counter = 0;
        if(button->state_raw) {
            button->state = button->state_raw;
            button->edge_rise = true;
        } else {
            button->state = button->state_raw;
            button->edge_fall = true;
        }
    }
}

int getRiseEdge(Button *btn)
{
    return btn->edge_rise;
}
int getFallEdge(Button *btn)
{
    return btn->edge_fall;
}


