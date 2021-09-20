/**
 *  @file       progress_bar.cpp
 *
 *  @brief      Progress-bar for terminal output
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#include <libKitsunemimiCommon/progress_bar.h>

namespace Kitsunemimi
{

/**
 * @brief constructor
 *
 * @param maxBarWidth maximum number of character in weidth for displaying the progress-bar
 */
ProgressBar::ProgressBar(const uint32_t maxBarWidth)
    : maxBarWidth(maxBarWidth) {}

/**
 * @brief update the output of the progress-bar with a new progress-state
 *
 * @param newProgress new progress-value to display
 *
 * @return true, is 100% or more as input, else false
 */
bool
ProgressBar::updateProgress(const float newProgress)
{
    bool result = false;
    progress = newProgress;

    // check if 1.0 or more are reached and update result for finish
    if(progress >= 1.0f)
    {
        progress = 1.0f;
        result = true;
    }

    // print progress
    std::cout << "[";
    const uint32_t pos = maxBarWidth * progress;
    for(uint32_t i = 0; i < maxBarWidth; i++)
    {
        if(i < pos) {
            std::cout << "=";
        } else if(i == pos) {
            std::cout << ">";
        } else {
            std::cout << " ";
        }
    }
    std::cout << "] " << uint32_t(progress * 100.0) << " %\r";
    std::cout.flush();

    return result;
}

} // namespace Kitsunemimi
