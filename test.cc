#if 0
#include<algorithm>
#include<boost/regex.hpp>
#include<boost/lambda/lambda.hpp>
#include<iostream>
#include<iterator>
#include<stdio.h> 
#include "test2.h"
#include "test_c.h"
#include "../pwm/pwm.h"
#include "../pwm/command_queue.h"
#include <boost/asio.hpp>
#endif

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <boost/asio.hpp>

#include<boost/regex.hpp>
//#include "server.h"
#include "../pwm/pwm.h"
#include "../pwm/command_queue.h" 
#include <boost/asio.hpp>

using boost::asio::ip::udp;

void regex_test() {
  std::string line;
    boost::regex pat( "^Subject: (Re: |Aw: )*(.*)" );

    while (std::cin)
    {
        std::getline(std::cin, line);
        boost::smatch matches;
        if (boost::regex_match(line, matches, pat))
            std::cout << matches[2] << std::endl;
    }
}

#if 0
void testServo() {
  typedef std::istream_iterator<float> in;
#if 0
  using namespace boost::lambda;

  typedef std::istream_iterator<int> in;
  std::for_each(in(std::cin), in(), std::cout << (_1 * 3) << " ");
#endif
  // min 150
  // max 600
  float frac = .5;
  in eos;
  in it(std::cin);
  pwm p;
  p.init();
  p.setPWMFreq(100);
  p.setMin(200);
  p.setMax(600);
  frac = *it;
  printf("frac %f\n\r", frac);
  while (it != eos) {
    if (*it == 0) {
      break;
    } 
    frac = *it;
    printf("frac %f\n\r", frac);
    p.setPWM(0, frac);
    ++it;

  }
    
}
#endif

void testCommandQueue() {
  CommandQueue<PWMSetting> pwm_setting_queue;
	pwm_setting_queue.Start();
  
	float frac = .5;
  typedef std::istream_iterator<float> in;
  in eos;
  in it(std::cin);
	while (it != eos) {
    if (*it == 0) {
      break;
    } 
    frac = *it;
    ++it;
		auto wait = *it;
    printf("sending to cq frac %f\n\r", frac);
	 	PWMSetting setting{0, frac, static_cast<int64_t>(wait)};
    pwm_setting_queue.AddCommand(setting);
    ++it;
  }
}

class Rover {
	public:

  void InitPwmQueue() {
    std::cerr << "R1";

		pwm_queue_.Start();
    std::cerr << "R2";
  }  	

	void Init() {
    InitPwmQueue(); 
			
	};

  void ServoTest() {
    PWMSetting setting{0, .3, 0};
    pwm_queue_.AddCommand(setting);
    
    PWMSetting setting2{0, 1.2, 0};
    pwm_queue_.AddCommand(setting2);
	}
	private:
		pwm pwm_;
    CommandQueue<PWMSetting> pwm_queue_;

};

int main(int argc, char** argv) { 
  // c_func();
  // printf("Args %d\n", add_1(argc));
  //testServo();
  testCommandQueue();
  return 0;
  //regex_test();
}

