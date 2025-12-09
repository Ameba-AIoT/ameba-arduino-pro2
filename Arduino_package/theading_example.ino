class THREAD {
public:
  THREAD(void);
  ~THREAD(void);

  // To start THREAD firmware update process via HTTP
  void start_THREAD_threads();
private:
  static void thread1_task(const void *argument);
  static void thread2_task(const void *argument);

  static void sendPostRequest();
};
THREAD thread;

char BUFFER[1024];
uint32_t threada_id, threadb_id, threadc_id, stack_sizea, stack_sizeb;
int priorityA;

THREAD::THREAD(){};

THREAD::~THREAD(){};


void THREAD::thread1_task(const void *argument) {
  while (1) {
    Serial.println("Thread 1");
    digitalWrite(23, HIGH);
    delay(500);
    digitalWrite(23, LOW);
    delay(500);
  }
}
void THREAD::thread2_task(const void *argument) {
  while (1) {
    Serial.print("thread2");
    digitalWrite(24, HIGH);
    delay(2000);
    digitalWrite(24, LOW);
    delay(2000);
  }
}
void THREAD::start_THREAD_threads() {
  priorityA = osPriorityNormal;
  stack_sizea = 1024;
  threada_id = os_thread_create_arduino(thread1_task, NULL, priorityA, stack_sizea);

  // First thread is to do keep alive connectivity check (post requests every 5s)
  if (threada_id) {
    Serial.println("[THREAD] Keep-alive connectivity thread created successfully.");
  } else {
    Serial.println("[THREAD] Failed to create keep-alive connectivity thread.");
  }

  stack_sizeb = 2048;
  threadb_id = os_thread_create_arduino(thread2_task, NULL, priorityA, stack_sizeb);

  // Second thread is to get the signal to start THREAD process.
  if (threadb_id) {
    Serial.println("[THREAD] Start THREAD process thread created successfully.");
  } else {
    Serial.println("[THREAD] Failed to create Start THREAD process thread.");
  }
}







void setup()
{
    Serial.begin(115200);
        delay(2000);
    // Set up the threads
    thread.start_THREAD_threads();
}
void loop()
{
    // Empty or add non-blocking code here
}
