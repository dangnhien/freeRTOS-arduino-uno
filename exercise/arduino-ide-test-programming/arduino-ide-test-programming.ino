// Time   14/7/2022
// Update 31/8/2022
#include <Arduino.h>

#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <queue.h>

QueueHandle_t xQueue;

void VSend1Task(void *pvParameters);
void VSend2Task(void *pvParameters);
void VSend3Task(void *pvParameters);

void VReceiveTask(void *pvParameters);

void setup()
{
  Serial.begin(9600);
  Serial.println(F("In Setup function"));

  xQueue = xQueueCreate(3, sizeof(int));

  if (xQueue == NULL)
    Serial.println("Error create queue");
  else
  {
    Serial.println("Create queue successful");

    xTaskCreate(VReceiveTask, "Receiver", 280, NULL, 2, NULL);
    xTaskCreate(VSend1Task, "Sender1", 64, NULL, 1, NULL);
    xTaskCreate(VSend2Task, "Sender2", 64, NULL, 1, NULL);
    xTaskCreate(VSend3Task, "Sender3", 64, NULL, 1, NULL);
 
    vTaskStartScheduler();
  }
}

void loop()
{
  
}


void VSend1Task(void *pvParameters)
{
  unsigned int lValueToSend = 0;

  for (;;)
  {
    xQueueSend(xQueue, &lValueToSend, portMAX_DELAY);
    Serial.print("Sent1 = ");
    Serial.println(lValueToSend);

    lValueToSend++;
    if (lValueToSend >= 1000)
      lValueToSend = 0;

    vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}


void VSend2Task(void *pvParameters)
{
  unsigned int lValueToSend1 = 10;

  for (;;)
  {
    xQueueSend(xQueue, &lValueToSend1, portMAX_DELAY);
    Serial.print("Sent2 = ");
    Serial.println(lValueToSend1);

    lValueToSend1++;
    if (lValueToSend1 >= 1000)
      lValueToSend1 = 0;

    vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}

void VSend3Task(void *pvParameters)
{
  unsigned int lValueToSend2 = 20;

  for (;;)
  {
    xQueueSend(xQueue, &lValueToSend2, portMAX_DELAY);
    Serial.print("Sent3 = ");
    Serial.println(lValueToSend2);

    lValueToSend2++;
    if (lValueToSend2 >= 1000)
      lValueToSend2 = 0;

    vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}

void VReceiveTask(void *pvParameters)
{
  unsigned int lReceivedValue1, lReceivedValue2, lReceivedValue3;
  int messageWaiting = 0;

  for (;;)
  {
    messageWaiting = uxQueueMessagesWaiting( xQueue );
    if(messageWaiting == 3)
    {
      if (xQueueReceive(xQueue, &lReceivedValue1, portMAX_DELAY) == pdPASS)
      {
        Serial.print("Received 1 = ");
        Serial.println(lReceivedValue1);
      }

      if (xQueueReceive(xQueue, &lReceivedValue2, portMAX_DELAY) == pdPASS)
      {
          Serial.print("Received 2 = ");
          Serial.println(lReceivedValue2);
      }

      if (xQueueReceive(xQueue, &lReceivedValue3, portMAX_DELAY) == pdPASS)
      {
        Serial.print("Received 3 = ");
        Serial.println(lReceivedValue3);
      }
    }
    
    vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}
