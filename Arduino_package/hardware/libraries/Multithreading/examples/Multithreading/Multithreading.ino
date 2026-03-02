/*
  Multithreading example

  Example demonstrating the use of multithreading on AmebaPro2 boards.
  - creates two threads:
    - thread A: prints "executing thread a" every 500ms
    - thread B: prints "executing thread b" every 2000ms

  Example guide:
  https://ameba-doc-arduino-sdk.readthedocs-hosted.com/en/latest/ameba_pro2/amb82-mini/Example_Guides/Multithreading/Multithreading.html
*/

char BUFFER[1024];
uint32_t thread_a_id, thread_b_id, stack_size_a, stack_size_b;
int priority_a;

void setup()
{
    Serial.begin(115200);
    delay(2000);
    start_multithreading();
}

void loop()
{
    // put your main code here, to run repeatedly:
}

void start_multithreading()
{
    Serial.println("Starting multithreading");
    priority_a = osPriorityNormal;
    stack_size_a = 1024;
    thread_a_id = os_thread_create_arduino(thread_a_task, NULL, priority_a, stack_size_a);

    if (thread_a_id) {
        Serial.println("Thread A created successfully");
    } else {
        Serial.println("Failed to create thread A");
    }

    stack_size_b = 2048;
    thread_b_id = os_thread_create_arduino(thread_b_task, NULL, priority_a, stack_size_b);

    if (thread_b_id) {
        Serial.println("Thread B created successfully");
    } else {
        Serial.println("Failed to create thread B");
    }
}

void thread_a_task(const void *argument)
{
    while (1) {
        Serial.println("executing thread A");
        delay(500);
    }
}

void thread_b_task(const void *argument)
{
    while (1) {
        Serial.println("executing thread B");
        delay(2000);
    }
}
