#include <Arduino.h>

#include <Arduino_FreeRTOS.h>
#include <task.h>

TaskHandle_t TaskHandle_1;
TaskHandle_t TaskHandle_2;

static void MyTask1(void *pvParameters);
static void MyTask2(void *pvParameters);

void setup()
{
    Serial.begin(9600);

    BaseType_t Returned_Task1 = xTaskCreate(MyTask1, "Task1", 64, NULL, 1, &TaskHandle_1);
    BaseType_t Returned_Task2 = xTaskCreate(MyTask2, "Task2", 64, NULL, 2, &TaskHandle_2);

    if(Returned_Task1 == Returned_Task2 && Returned_Task1 == pdPASS)
        Serial.println("Create task successful!");
    else 
        Serial.println("Create task fail!");
}

void loop()
{
    Serial.println(F("infinite loop"));
    delay(10);
}

void MyTask1(void *pvParameters)
{
    for (;;)
    {
        Serial.println(F("Task1 Suspend itself"));
        vTaskSuspend(NULL);

        Serial.println(F("Task1 running again"));
        
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

static void MyTask2(void *pvParameters)
{
    int value = 0;

    while (1)
    {
        value++;
        if (value == 20)
            value = 0;

        if (value == 0)
        {
            Serial.println(F("Task2 Resume Task1"));
            vTaskResume(TaskHandle_1);
        }

        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}



