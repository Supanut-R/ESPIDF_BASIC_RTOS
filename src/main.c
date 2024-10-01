#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>

#define LED1_GPIO_PIN GPIO_NUM_4
#define LED2_GPIO_PIN GPIO_NUM_3

typedef struct{ // define structure
    int param;
    const char* name;
}test_param_t;

TaskHandle_t task2Handler = NULL; // ประกาศตัวแปรของ task ที่ถูกสร้างขึ้นมา เพื่อที่จะ delete task นั้นๆได้

static task_led1(void* pvParameter) {
    test_param_t params = *(test_param_t*)pvParameter;
    //int task2_count = 0;
    while (true) {
        gpio_set_level(LED1_GPIO_PIN, 1); // Turn ON
        vTaskDelay(params.param / portTICK_PERIOD_MS);
        gpio_set_level(LED1_GPIO_PIN, 0); // Turn OFF
        vTaskDelay(params.param / portTICK_PERIOD_MS);
        printf("Name: %s\r\n", params.name);
        //task2_count++;

        //if(task2Handler != NULL){
            //if(task2_count > 10){
                //vTaskDelete(task2Handler);
                //task2Handler = NULL;
            //}
        }
        vTaskDelete(NULL);
    }

static task_led2(void* pvParameter) {
    //int param = *(int*)pvParameter;
    test_param_t params = *(test_param_t*)pvParameter;
    int task2_count = 0;
    while (true) {
        gpio_set_level(LED2_GPIO_PIN, 1); // Turn ON
        vTaskDelay(params.param / portTICK_PERIOD_MS);
        gpio_set_level(LED2_GPIO_PIN, 0); // Turn OFF
        vTaskDelay(params.param / portTICK_PERIOD_MS);
        printf("Name: %s\r\n", params.name);
        task2_count++;

        if(task2Handler != NULL){
            if(task2_count > 15){
                break;
            }
        }
    }
    vTaskDelete(NULL); //ทำลาย task ตัวมันเองเพื่อคืนหน่วยความจำ
}
static void setup() {
    gpio_config_t led1_cfg = {
        .pin_bit_mask = (1ULL << LED1_GPIO_PIN),
        .mode = GPIO_MODE_OUTPUT
    };
    gpio_config(&led1_cfg);
    gpio_config_t led2_cfg = {
        .pin_bit_mask = (1ULL << LED2_GPIO_PIN),
        .mode = GPIO_MODE_OUTPUT
    };
    gpio_config(&led2_cfg);
}

void app_main() {
    setup();
    //static int period1 = 100;
    //static int period2 = 500;
  
    test_param_t param1 ={
        .param = 100,
        .name = "task_led1"
    };
    test_param_t param2 ={
        .param = 500,
        .name = "task_led2"
    };

    xTaskCreate(task_led1, "task_led1", 1024*2, &param1, 1, NULL); //1 refer to task piority
    xTaskCreate(task_led2, "task_led2", 1024*2, &param2, 1, &task2Handler); 
    //ตอนนี้ TASK1 กับ TASL2 มีความสำคัญเท่ากัน เพราะใส่เลข 1 เหมือนกัน (ใส่เลขมาก ความสำคัญจะมาก)
}