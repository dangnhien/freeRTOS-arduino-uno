#include <Arduino.h>

#include <Arduino_FreeRTOS.h>
#include <task.h>

TaskHandle_t TaskHandle_1;
TaskHandle_t TaskHandle_2;

unsigned int time_handles=0;

static void MyTask1(void *pvParameters);
static void MyTask2(void *pvParameters);

void setup()
{
    Serial.begin(9600);
    Serial.println(F("In Setup function"));

    xTaskCreate(MyTask1, "Task1", 64, NULL, 1, &TaskHandle_1);
    xTaskCreate(MyTask2, "Task2", 64, NULL, 2, &TaskHandle_2);
    
    time_handles = millis();
}

void loop()
{
  if(millis()-time_handles >=20)
  {
    Serial.println(F("infinite loop"));
    time_handles = millis();
  }
}

void MyTask1(void *pvParameters)
{
    /* Block for 100ms. */
    const TickType_t  xDelay = 100 / portTICK_PERIOD_MS;
    int i=0;
    for (;;)
    {
        i++;
        if(i==20)
          i=0;
          
        Serial.println(F("Task1 running"));
        if(i==10)
         vTaskResume(TaskHandle_2);
       
        if(i==15)
          vTaskDelete(NULL);
          
        vTaskDelay(xDelay);
    }
}

static void MyTask2(void *pvParameters)
{
  const TickType_t  xDelay = 100 / portTICK_PERIOD_MS;
    while (1)
    {
        Serial.println(F("Task 2 running"));
        vTaskSuspend(NULL);
        Serial.println(F("Task 2 running again"));

        vTaskDelay(xDelay);
    }
}