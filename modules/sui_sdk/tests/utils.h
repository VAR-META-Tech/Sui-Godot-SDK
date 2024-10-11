#ifndef SUI_TEST_SLEEP_UTILS
#define SUI_TEST_SLEEP_UTILS
#include "time.h"
void sleep(int seconds)
{
  time_t start_time = time(NULL);
  while (difftime(time(NULL), start_time) < seconds)
    ;
}
#endif