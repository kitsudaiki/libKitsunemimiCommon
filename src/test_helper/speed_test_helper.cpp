/**
 *  @file       speed_test_helper.cpp
 *
 *  @brief      Helper class for benchmark-tests
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#include <libKitsunemimiCommon/test_helper/speed_test_helper.h>

namespace Kitsunemimi
{

SpeedTestHelper::SpeedTestHelper()
{
    m_result.addColumn("name");
    m_result.addColumn("average");
    m_result.addColumn("standard deviation");
}

/**
 * @brief add timeslot-object to the result-output. It calculates the duration and
 *        standard deviation of the timeslot-object.
 */
void
SpeedTestHelper::addToResult(const SpeedTestHelper::TimerSlot timeSlot)
{
    double duration = 0.0;
    double standardDeviation = 0.0;

    // calculate duration
    for(uint32_t i = 0; i < timeSlot.values.size(); i++) {
        duration += timeSlot.values.at(i);
    }
    duration /= static_cast<double>(timeSlot.values.size());

    // calculate standard deviation
    for(uint32_t i = 0; i < timeSlot.values.size(); i++)
    {
        double singleValue = timeSlot.values.at(i) - duration;
        standardDeviation += singleValue * singleValue;
    }
    standardDeviation /= static_cast<double>(timeSlot.values.size());
    standardDeviation = sqrt(standardDeviation);

    // convert duration to string
    std::ostringstream durationObj;
    durationObj << std::fixed;
    durationObj << std::setprecision(3);
    durationObj << duration;

    // convert standard deviation to string
    std::ostringstream standardDeviationObj;
    standardDeviationObj << std::fixed;
    standardDeviationObj << std::setprecision(3);
    standardDeviationObj << standardDeviation;

    // add row to result table
    m_result.addRow(std::vector<std::string>{timeSlot.name,
                                             durationObj.str() + " " + timeSlot.unitName,
                                             standardDeviationObj.str() + " " + timeSlot.unitName});
}

/**
 * @brief print result as table
 */
void
SpeedTestHelper::printResult()
{
    std::cout<<m_result.toString()<<std::endl;
}

} // namespace Kitsunemimi
