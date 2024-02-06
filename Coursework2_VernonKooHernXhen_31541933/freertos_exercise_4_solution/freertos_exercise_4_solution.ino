#include <Arduino.h>
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <FreeRTOSConfig.h>

#define SERIAL_PORT Serial

void vTask1(void *pvParameters);
void vTask2(void *pvParameters);

void vPrintString( const char *pcString )
{
 /* Write the string to stdout, using a critical section as a crude method of
 mutual exclusion. */
 taskENTER_CRITICAL();
 {
  SERIAL_PORT.println(pcString );
   fflush( stdout );
 }
 taskEXIT_CRITICAL();
}

void setup() {
  
  SERIAL_PORT.begin(115200);

  //set led as output
  pinMode(LED_BUILTIN, OUTPUT);
  //Create tasks
  xTaskCreate( vTask1, "Task1", 1000, NULL , 1, NULL );
  xTaskCreate( vTask2, "Task2", 1000, NULL , 1, NULL );
}

void loop() {
  
}

void vTask1(void *pvParameters) {
  
  TickType_t xLastWakeTime = xTaskGetTickCount();
  const TickType_t xTask1Period = pdMS_TO_TICKS(5000); // 5 seconds
  const TickType_t xTask1ExecutionTime = pdMS_TO_TICKS(1000);// execution time is 1 second
  
  for (;;) {

    TickType_t previousTime = xTaskGetTickCount();
    vPrintString("Task 1 is executing.");

    //light LED up for 1 second execution time
    while (xTaskGetTickCount() - previousTime < xTask1ExecutionTime){

      digitalWrite(LED_BUILTIN,HIGH);
    }
    
    digitalWrite(LED_BUILTIN, LOW);  // Turn off LED
    vPrintString("Task 1 has finished execution.");
    vTaskDelayUntil(&xLastWakeTime, xTask1Period); //repeat every 5 seconds
  
  }
}

void vTask2(void *pvParameters) {

  TickType_t xLastWakeTime = xTaskGetTickCount();
  const TickType_t xTask2Period = pdMS_TO_TICKS(10000); // 10 seconds
  const TickType_t xTask2ExecutionTime = pdMS_TO_TICKS(2000);// 2 seconds
  
  for (;;) {
      
    vTaskDelay(1000);

    TickType_t previousTime = xTaskGetTickCount();
    vPrintString("Task 2 is executing.");  
    //light up LED for 2 seconds execution time
    while (xTaskGetTickCount() - previousTime < xTask2ExecutionTime){
      digitalWrite(LED_BUILTIN,HIGH);
    }
    
    digitalWrite(LED_BUILTIN, LOW);  // Turn off LED
    vPrintString("Task 2 has finished execution.");
    vTaskDelayUntil(&xLastWakeTime, xTask2Period);   //repeat every 10 seconds 
  }
  
}
