//  stopwatch.h
//  three_sum
//
//  Created by William McCarthy on 22/7/20.
//  Copyright © 2020 William McCarthy. All rights reserved.
//

#ifndef __stopwatch_h__
#define __stopwatch_h__

#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>

//--------------------------------------------------------------------------------------------------------
class stopwatch
{
  /* stopwatch that adds up all the times it was running (start --> stop == a running interval)
     start --> stop, then start--> stop, will add up the two intervals it was running
     reset to clear all times so far
   */
  typedef std::chrono::system_clock sysclock;
  typedef std::chrono::time_point<sysclock> timepoint;
  typedef std::chrono::milliseconds milliseconds;

private:
  timepoint start_time_, end_time_;
  bool running_, paused_;
  std::string name_;
  int precision_;
  double total_time_;

public:
  stopwatch() : stopwatch("stopwatch") {}
  stopwatch(const std::string &name_, int precision = 6)
      : start_time_(sysclock::now()), end_time_(start_time_), running_(false), paused_(false), name_(name_), precision_(precision) {}

  void start()
  {
    if (paused_)
    {
      total_time_ += time_interval(start_time_, end_time_);
      paused_ = false;
    }
    if (!running_)
    {
      start_time_ = sysclock::now();
      end_time_ = start_time_;
    }
    running_ = true;
  }
  void stop()
  {
    if (!running_)
    {
      return;
    }
    end_time_ = sysclock::now();
    running_ = false;
    paused_ = true;
  }
  void reset()
  {
    std::cout << "resetting timer to 0...............................................\n";
    total_time_ = 0;
    start_time_ = sysclock::now();
    end_time_ = sysclock::now();
    running_ = false;
  }

  double time_interval(timepoint start, timepoint end) const
  {
    return std::chrono::duration_cast<milliseconds>(end - start).count();
  }
  double elapsed_ms() const
  {
    timepoint end = running_ ? sysclock::now() : end_time_;
    return time_interval(start_time_, end) + total_time_;
  }
  double elapsed_seconds() const { return elapsed_ms() / 1000.0; }

  friend std::ostream &operator<<(std::ostream &os, const stopwatch &sw)
  {
    return os << sw.name_ << " elapsed time: "
              << std::setprecision(sw.precision_) << std::fixed
              << sw.elapsed_seconds() << " s \n";
  }

  static void run_tests()
  {
    stopwatch sw("test", 4);
    sw.start_stop_test(1000);
    sw.start_stop_test(100);
    sw.start_stop_test(500);

    sw.reset();
    sw.start_stop_test(500);
    sw.start_stop_test(100);
    sw.start_stop_test(1000);
  }

private:
  static void stall(int n)
  {
    double total = 0.0;
    for (int i = 0; i < n; ++i)
    {
      for (int j = 0; j < n; ++j)
      {
        for (int k = 0; k < n; ++k)
        {
          total += 2.5;
        }
      }
    }
  }
  void start_stop_test(int n)
  {
    std::cout << __FUNCTION__ << " using " << n << "...\n";
    start();
    stall(n);
    stop();
    std::cout << "sw is: " << *this << "\n";
  }
};

#endif /* __stopwatch_h__ */
