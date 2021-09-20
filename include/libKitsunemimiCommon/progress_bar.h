/**
 *  @file       progress_bar.h
 *
 *  @brief      Progress-bar for terminal output
 *
 *  @author     Tobias Anker <tobias.anker@kitsunemimi.moe>
 *
 *  @copyright  MIT License
 */

#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

#include <stdint.h>
#include <unistd.h>
#include <iostream>

class ProgressBar_Test;

namespace Kitsunemimi
{

class ProgressBar
{
public:
    ProgressBar(const uint32_t maxBarWidth = 80);
    bool updateProgress(const float newProgress);

private:
    const uint32_t maxBarWidth = 80;
    float progress = 0.0;

    friend ProgressBar_Test;
};

} // namespace Kitsunemimi

#endif // PROGRESS_BAR_H
