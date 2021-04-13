/*
 * Copyright (C) 2012 Tobias Bolten
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "knnga.hpp"

using namespace Gamera;
using namespace Gamera::GA;



/******************************************************************************/
/******************************************************************************/
/******************************************************************************/


GABaseSetting::GABaseSetting(int opMode /*= GA_SELECTION*/,
                             unsigned int pSize /*= 75*/,
                             double cRate /*= 0.95*/, double mRate /*= 0.05*/) {

    if ( opMode != GA_SELECTION && opMode != GA_WEIGHTING ) {
        throw std::invalid_argument("GABaseSetting: unknown mode of opertation");
    }

    this->opMode = opMode;
    this->pSize = pSize;
    this->cRate = cRate;
    this->mRate = mRate;
}

int GABaseSetting::getOpMode() {
    return this->opMode;
}

unsigned int GABaseSetting::getPopSize() {
    return this->pSize;
}

double GABaseSetting::getCrossRate() {
    return this->cRate;
}

double GABaseSetting::getMutRate() {
    return this->mRate;
}

void GABaseSetting::setOpMode(int opMode) {
    if ( opMode != GA_SELECTION && opMode != GA_WEIGHTING ) {
        throw std::invalid_argument("GABaseSetting: setOpMode: unknown mode of opertation");
    }

    this->opMode = opMode;
}

void GABaseSetting::setPopSize(unsigned int pSize) {
    this->pSize = pSize;
}

void GABaseSetting::setCrossRate(double cRate) {
    this->cRate = cRate;
}

void GABaseSetting::setMutRate(double mRate) {
    this->mRate = mRate;
}



GAParallelization::GAParallelization(bool mode /*= true*/,
                                     unsigned int threads /*= 2*/) {
    this->parallelMode = mode;
    this->threadNum = threads;
}

bool GAParallelization::isParallel() {
    return this->parallelMode;
}

void GAParallelization::changeMode(bool mode /*= true*/) {
    this->parallelMode = mode;
}

unsigned int GAParallelization::getThreadNum() {
    return this->threadNum;
}

void GAParallelization::setThreadNum(unsigned int n /*= 2*/) {
    this->threadNum = n;
}

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/


