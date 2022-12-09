#include "test.h"
#include "PlatformThreading.h"
#include <iostream>
#include <cstring>

ADD_TEST(platform_threading,
         {
             platform_set_thread_name(platform_thread_self(), "testThread");
             char buf[80];
             platform_get_thread_name(platform_thread_self(), buf, 80);
             std::cout << "threadname: " << buf << std::endl;
             if (strcmp(buf, "testThread") == 0)
             {
                 std::cout << "succeed!" << std::endl;
             }
             else
             {
                 std::cout << "fail!" << std::endl;
             }
         })