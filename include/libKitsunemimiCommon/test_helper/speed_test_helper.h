/**
 *  @file       speed_test_helper.h
 *
 *  @brief      Helper class for benchmark-tests
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#ifndef SPEED_TEST_HELPER_H
#define SPEED_TEST_HELPER_H

#include <string>
#include <iostream>
#include <chrono>
#include <map>
#include <vector>
#include <iomanip>
#include <math.h>

#include <libKitsunemimiCommon/common_items/table_item.h>

namespace Kitsunemimi
{

typedef std::chrono::milliseconds chronoMilliSec;
typedef std::chrono::microseconds chronoMicroSec;
typedef std::chrono::nanoseconds chronoNanoSec;
typedef std::chrono::seconds chronoSec;
typedef std::chrono::high_resolution_clock::time_point chronoTimePoint;
typedef std::chrono::high_resolution_clock chronoClock;

class SpeedTestHelper
{

public:
    enum TIMETYPES {
        SECONDS,
        MILLI_SECONDS,
        MICRO_SECONDS,
        NANO_SECONDS,
    };

    struct TimerSlot
    {
        std::string name = "";
        std::string unitName = "";
        std::vector<double> values;

        std::chrono::high_resolution_clock::time_point start;
        std::chrono::high_resolution_clock::time_point end;

        void startTimer() {
            start = std::chrono::system_clock::now();
        }
        void stopTimer() {
            end = std::chrono::system_clock::now();
        }

        double getDuration(const TIMETYPES type)
        {
            if(type == SECONDS) {
                return std::chrono::duration_cast<chronoSec>(end - start).count();
            }
            if(type == MILLI_SECONDS) {
                return std::chrono::duration_cast<chronoMilliSec>(end - start).count();
            }
            if(type == MICRO_SECONDS) {
                return std::chrono::duration_cast<chronoMicroSec>(end - start).count();
            }
            if(type == NANO_SECONDS) {
                return std::chrono::duration_cast<chronoNanoSec>(end - start).count();
            }

            return 0;
        }
    };

    SpeedTestHelper();

    void addToResult(const TimerSlot timeSlot);
    void printResult();

private:
    std::map<std::string, TimerSlot> m_timeslots;

    TableItem m_result;
};

} // namespace Kitsunemimi

#endif // SPEED_TEST_HELPER_H
