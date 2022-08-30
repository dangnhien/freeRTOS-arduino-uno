#include <Arduino.h>

#include <Arduino_FreeRTOS.h>
#include <task.h>

TaskHandle_t TaskHandle_1 = NULL;
TaskHandle_t TaskHandle_2 = NULL;

void MyTask1(void *pvParameters);
void MyTask2(void *pvParameters);
void MyTaskIdle(void *pvParameters);

void setup()
{
  Serial.begin(9600);

  BaseType_t Returned1 = xTaskCreate(MyTask1, "LED1", 64, NULL, 1, &TaskHandle_1);
  BaseType_t ReturnedIdle = xTaskCreate(MyTaskIdle, "Idle", 64, NULL, 0, NULL);

  if(Returned1 == ReturnedIdle && Returned1 == pdPASS)
    Serial.println("Start program");
  else
    Serial.println("Error!");

  vTaskStartScheduler();
}

void loop()
{

}

void MyTask1(void *pvParameters)
{
  while (1)
  {
    static int digit = 0;
    digit++;
    (digit>10) ? digit = 0 : digit = digit;

    Serial.println("Task1 run");

    if (digit == 10)
    {
      xTaskCreate(MyTask2, "LED2", 64, NULL, 2, &TaskHandle_2);
       Serial.println("Task2 create");
    }

    vTaskDelay(100/ portTICK_PERIOD_MS);
  }
}

void MyTask2(void *pvParameters)
{
  for (;;)
  {
    Serial.println("Task2 run and delete Task1");

    if(TaskHandle_1 != NULL)
    {
      vTaskDelete(TaskHandle_1); 
      TaskHandle_1 = NULL;
    }
    
    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}

void MyTaskIdle(void *pvParameters)
{
  for (;;)
  {
    Serial.println("Task Idle run");

    vTaskDelay(20 / portTICK_PERIOD_MS);
  }
}
