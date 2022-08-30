#include <Arduino.h>

#include <Arduino_FreeRTOS.h>
#include <task.h>

static void MyTask1(void *pvParameters);
static void MyTask2(void *pvParameters);
static void MyTask3(void *pvParameters);
static void MyTaskIdle(void *pvParameters);

void setup()
{
  Serial.begin(9600);
  
  BaseType_t Returned1 = xTaskCreate(MyTask1, "Task_1", 64, NULL, 2, NULL);
  BaseType_t Returned2 =  xTaskCreate(MyTask2, "Task_2", 64, NULL, 2, NULL);
  BaseType_t Returned3 = xTaskCreate(MyTask3, "Task_3", 64, NULL, 2, NULL);
  BaseType_t ReturnedIdle =  xTaskCreate(MyTaskIdle, "Task_Idle", 64, NULL,0, NULL);

  if(Returned1 == Returned2 \
    && Returned1 == Returned3 \
    && Returned1 == ReturnedIdle \
    && Returned1 == pdPASS)
      Serial.println("Start Program!");
  else
      Serial.println("Error create. Please create task again!");

}

void loop()
{

}

static void MyTask1(void *pvParameters)
{
  for(;;)
  {
    Serial.println("Task1");
    vTaskDelay(50/portTICK_PERIOD_MS);
  }
}

static void MyTask2(void *pvParameters)
{
  for(;;)
  {
    Serial.println("Task2");
    vTaskDelay(60/portTICK_PERIOD_MS);
  }
}

static void MyTask3(void *pvParameters)
{
  for(;;)
  {
    Serial.println("Task3");
    vTaskDelay(70/portTICK_PERIOD_MS);
  }
}

static void MyTaskIdle(void *pvParameters)
{
  for(;;)
  {
    Serial.println("Task Idle");
    delay(10);
  }
}

