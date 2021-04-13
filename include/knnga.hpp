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

#ifndef gamodule201206
#define gamodule201206

#include "knncoremodule.hpp"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <stdexcept>
#include <cmath>
#include <limits>
#include <algorithm>
#include <sstream>
#include <time.h>
#include <map>

#ifdef _OPENMP
#include <omp.h>
#endif

#include <eo>
#include <es.h>

#include <ga/eoBitOp.h>
#include <eoStochasticUniversalSelect.h>
#include <eoShiftMutation.h>
#include <eoSwapMutation.h>
#include <eoTwoOptMutation.h>

namespace Gamera { namespace GA {

    typedef eoBit<double> SelectionIndi;
    typedef eoReal<double> WeightingIndi;

    enum OperationMode {GA_SELECTION, GA_WEIGHTING};

    template <typename EOT>
    class SelectOneDefaultWorth : public eoSelectOne<EOT> {};

    /**************************************************************************/
    template<class EOT>
    class GATwoOptMutation : public eoMonOp<EOT> {
    /**************************************************************************/
        public:
            typedef typename EOT::AtomType GeneType;

            GATwoOptMutation(){}

            virtual std::string className() const { return "GATwoOptMutation"; }

            bool operator()(EOT& _eo) {
                // generate two different indices
                unsigned int i = eo::rng.random(_eo.size());
                unsigned int j;

                do {
                    j = eo::rng.random(_eo.size());
                } while(i == j);

                unsigned int from = std::min(i,j);
                unsigned int to = std::max(i,j);
                unsigned int idx = (to - from) / 2;

                // inverse between from and to
                for(unsigned k = 0; k <= idx; ++k) {
                    GeneType tmp = _eo[from+k];
                    _eo[from+k] = _eo[to-k];
                    _eo[to-k] = tmp;
                }
                return true;
            }
    };

    /**************************************************************************/
    template<class EOT>
    class GASwapMutation : public eoMonOp<EOT> {
    /**************************************************************************/
        public:
            typedef typename EOT::AtomType GeneType;

            GASwapMutation(const unsigned _howManySwaps=1): howManySwaps(_howManySwaps) {
                if(howManySwaps < 1) {
                    throw std::runtime_error("Invalid number of swaps in GASwapMutation");
                }
            }

            virtual std::string className() const { return "GASwapMutation"; }

            bool operator()(EOT& chrom) {
                unsigned i, j;

                for(unsigned int swap = 0; swap < howManySwaps; swap++) {
                    // generate two different indices
                    i=eo::rng.random(chrom.size());

                    do {
                        j = eo::rng.random(chrom.size());
                    } while (i == j);

                    // swap
                    GeneType tmp = chrom[i];
                    chrom[i] = chrom[j];
                    chrom[j] = tmp;
              }
              return true;
            }

        private:
                unsigned int howManySwaps;
    };

    /**************************************************************************/
    template <typename EOT>
    class GAManualStop : public eoContinue<EOT> {
    /**************************************************************************/
        protected:
            bool continueFlag;

        public:
            GAManualStop() {
                this->continueFlag = true;
            }

            virtual bool operator() ( const eoPop<EOT>& _vEO ) {
                return this->continueFlag;
            }

            bool getFlag() {
                return this->continueFlag;
            }

            void setFlag(bool flag) {
                this->continueFlag = flag;
            }
    };

    /**************************************************************************/
    template <typename EOT>
    class GABestIndiStat : public eoStat<EOT, std::string> {
    /**************************************************************************/
        public:
            using eoStat<EOT, std::string>::value;

            GABestIndiStat(std::string name = "bestIndi")
            : eoStat<EOT, std::string>(std::string(""), name)
            {}

            void operator()(const eoPop<EOT> &pop) {
                const EOT bestIndi = pop.best_element();
                typename EOT::const_iterator it;

                std::ostringstream indiStream;

                indiStream << "[";
                for (it = bestIndi.begin(); it != bestIndi.end(); ++it) {
                    indiStream << *it << " , ";
                }
                indiStream << "]";

                value() = indiStream.str();
            }

            virtual std::string className(void) const { return "GABestIndiStat"; }
    };

    /**************************************************************************/
    template <typename EOT>
    class GAClassifierUpdater : public eoContinue<EOT> {
    /**************************************************************************/
        protected:
            KnnObject *knn;
            double bestFitness;
            std::vector<EOT> bestSolution;
            std::map<unsigned int, unsigned int> *indexRelation;

        public:
            GAClassifierUpdater(KnnObject *knn, std::map<unsigned int, unsigned int> *indexRelation) {
                this->knn = knn;
                this->bestFitness = 0.0;
                this->bestSolution.resize(this->knn->num_features);
                this->indexRelation = indexRelation;
            }

            double getBestFitness() {
                return this->bestFitness;
            }

            virtual bool operator()(const eoPop<EOT>& pop);

            virtual std::string className(void) const { return "GAClassifierUpdater"; }
    };

    template <>
    inline bool GAClassifierUpdater<WeightingIndi>::operator() (const eoPop<WeightingIndi> &pop) {
        const WeightingIndi bestIndi = pop.best_element();
        WeightingIndi::const_iterator it;

        if (bestIndi.fitness() > this->bestFitness) {
            this->bestFitness = bestIndi.fitness();

            std::fill(this->knn->weight_vector, this->knn->weight_vector + this->knn->num_features, 0.0);
            std::fill(this->bestSolution.begin(), this->bestSolution.end(), 0.0);

            for (size_t i = 0; i < bestIndi.size(); ++i) {
                this->knn->weight_vector[(*this->indexRelation)[i]] = bestIndi[i];
                this->bestSolution[(*this->indexRelation)[i]] = bestIndi[i];
            }
        }

        return true;
    }

    template <>
    inline bool GAClassifierUpdater<SelectionIndi>::operator() (const eoPop<SelectionIndi> &pop) {
        const SelectionIndi bestIndi = pop.best_element();
        SelectionIndi::const_iterator it;

        if (bestIndi.fitness() > this->bestFitness) {
            this->bestFitness = bestIndi.fitness();

            std::fill(this->knn->selection_vector, this->knn->selection_vector + this->knn->num_features, 0);
            std::fill(this->bestSolution.begin(), this->bestSolution.end(), false);

            for (size_t i = 0; i < bestIndi.size(); ++i) {
                this->knn->selection_vector[(*this->indexRelation)[i]] = bestIndi[i];
                this->bestSolution[(*this->indexRelation)[i]] = (bool)bestIndi[i];
            }
        }

        return true;
    }

    // *************************************************************************
    template <typename EOT>
    class GAFitnessEval : public eoEvalFunc<EOT> {
    // *************************************************************************
        protected:
            KnnObject *knn;
            std::map<unsigned int, unsigned int> *indexRelation;

            typedef typename EOT::ContainerType ContainerType;
            typedef typename EOT::AtomType AtomType;

        public:
            GAFitnessEval(KnnObject *knn, std::map<unsigned int, unsigned int> *indexRelation) {
                this->knn = knn;
                this->indexRelation = indexRelation;
            }

            virtual std::string className(void) const { return "GAFitnessEval"; }

            virtual void operator()( EOT &individual );
    };

    // specialization for weighting individual
    template <>
    inline void GAFitnessEval<WeightingIndi>::operator()( WeightingIndi &individual ) {
        AtomType* convertedVector = new AtomType[this->knn->num_features];
        std::fill(convertedVector, convertedVector + this->knn->num_features, 0.0);

        for (size_t i = 0; i < individual.size(); ++i) {
            convertedVector[(*this->indexRelation)[i]] = individual[i];
        }

        std::pair<int, int> looEvalRes;
        looEvalRes = leave_one_out(this->knn, std::numeric_limits<int>::max(),
                                   NULL, convertedVector, NULL);

        individual.fitness( looEvalRes.first / (double) looEvalRes.second );
        delete [] convertedVector;
    }

    // specialization for selection individual
    template <>
    inline void GAFitnessEval<SelectionIndi>::operator()( SelectionIndi &individual ) {
        int* convertedVector = new int[this->knn->num_features];
        std::fill(convertedVector, convertedVector + this->knn->num_features, 0);

        for (size_t i = 0; i < individual.size(); ++i) {
            // §4.7/4 from the C++ Standard (Integral Conversion):
            // If the source type is bool, the value false is converted to zero
            // and the value true is converted to one.
            convertedVector[(*this->indexRelation)[i]] = (int) individual[i];
        }

        std::pair<int, int> looEvalRes;
        looEvalRes = leave_one_out(this->knn, std::numeric_limits<int>::max(),
                                   convertedVector, NULL, NULL);

        individual.fitness( looEvalRes.first / (double) looEvalRes.second );
        delete [] convertedVector;
    }

    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////

    /**************************************************************************/
    template <typename EOT, template <typename IndiType> class EO>
    class GAMultiSettingBase {
    /**************************************************************************/
        protected:
            std::vector<EO<EOT>*> *settings;

        public:
            GAMultiSettingBase<EOT, EO>();
            ~GAMultiSettingBase<EOT, EO>();

            std::vector<EO<EOT>*> * getSettings();
    };

    /**************************************************************************/
    template <typename EOT, template <typename IndiType> class EO>
    class GASingleSettingBase {
    /**************************************************************************/
        protected:
            EO<EOT> *setting;

        public:
            GASingleSettingBase<EOT, EO>();
            ~GASingleSettingBase<EOT, EO>();

            EO<EOT> * getSetting();
    };

    /**************************************************************************/
    class GABaseSetting {
    /**************************************************************************/
        protected:
            int opMode;
            unsigned int pSize;
            double cRate;
            double mRate;

        public:
            GABaseSetting(int opMode = GA_SELECTION,
                          unsigned int pSize = 75,
                          double cRate = 0.95, double mRate = 0.05);
            // getter
            int getOpMode();
            unsigned int getPopSize();
            double getCrossRate();
            double getMutRate();

            // setter
            void setOpMode(int opMode);
            void setPopSize(unsigned int pSize);
            void setCrossRate(double cRate);
            void setMutRate(double mRate);
    };

    /**************************************************************************/
    template <typename EOT, template <typename IndiType> class EO = SelectOneDefaultWorth>
    class GASelection : public GASingleSettingBase<EOT, EO> {
    /**************************************************************************/
        public:
            void setRoulettWheel();
            void setRoulettWheelScaled(double preasure = 2.0);
            void setStochUniSampling();
            void setRankSelection(double preasure = 2.0, double exponent = 1.0);
            void setTournamentSelection(unsigned int tSize = 3);
            void setRandomSelection();
    };

    /**************************************************************************/
    template <typename EOT, template <typename IndiType> class EO = eoQuadOp>
    class GACrossover : public GAMultiSettingBase<EOT, EO> {
    /**************************************************************************/
        protected:
            eoRealVectorBounds *bound;

        public:
            GACrossover();
            ~GACrossover();

            // generic functions
            void setNPointCrossover(unsigned int n = 1);
            void setUniformCrossover(double preference = 0.5);

            // weighting functions
            void setSBXcrossover(unsigned int numFeatures, double min,
                                 double max, double eta = 1.0);
            void setSegmentCrossover(unsigned int numFeatures, double min,
                                     double max, double alpha = 0.0);
            void setHypercubeCrossover(unsigned int numFeatures, double min,
                                       double max, double alpha = 0.0);
    };
    
    /**************************************************************************/
    template <typename EOT, template <typename IndiType> class EO = eoMonOp>
    class GAMutation : public GAMultiSettingBase<EOT, EO> {
    /**************************************************************************/
        protected:
            eoRealVectorBounds *bound;

        public:
            GAMutation();
            ~GAMutation();

            void setShiftMutation();
            void setSwapMutation();
            void setInversionMutation();

            // selection functions
            void setBinaryMutation(double rate = 0.05, bool normalize = false);

            // weighting functions
            void setGaussMutation(unsigned int numFeatures, double min,
                                  double max, double sigma, double p_change = 1.0);
    };

    /**************************************************************************/
    template <typename EOT, template <typename IndiType> class EO = eoReplacement>
    class GAReplacement : public GASingleSettingBase<EOT, EO> {
    /**************************************************************************/
        public:
            void setGenerationalReplacement();
            void setSSGAworse();
            void setSSGAdetTournament(unsigned int tSize = 3);
    };
    
    /**************************************************************************/
    template <typename EOT, template <typename IndiType> class EO = eoContinue>
    class GAStopCriteria : public GAMultiSettingBase<EOT, EO> {
    /**************************************************************************/
        public:
            void setBestFitnessStop(double optimum = 1.0);
            void setMaxGenerations(unsigned int n = 100);
            void setMaxFitnessEvals(unsigned int n = 5000);
            void setSteadyStateStop(unsigned int minGens = 40, unsigned int noChangeGens = 10);
    };

    /**************************************************************************/
    class GAParallelization {
    /**************************************************************************/
        protected:
            bool parallelMode;
            unsigned int threadNum;

        public:
            GAParallelization(bool mode = true, unsigned int threads = 2);

            bool isParallel();
            void changeMode(bool mode = true);

            unsigned int getThreadNum();
            void setThreadNum(unsigned int n = 2);
    };

    /**************************************************************************/
    template <typename EOT>
    class GAOptimization {
    /**************************************************************************/
        protected:
            bool running;

            // basic GA settings
            unsigned int popSize;
            double crossoverRate;
            double mutationRate;

            KnnObject *knn;
            GABaseSetting *baseSetting;
            GASelection<EOT> *selection;
            GACrossover<EOT> *crossover;
            GAMutation<EOT> *mutation;
            GAReplacement<EOT> *replacement;
            GAStopCriteria<EOT> *stop;
            GAParallelization *parallelization;

            GAManualStop<EOT> manualStop;

            eoIncrementorParam<unsigned int> *generationCounter;
            eoBestFitnessStat<EOT> *bestStat;
            GAClassifierUpdater<EOT> *kNNUpdater;

            std::ostringstream *monitorStream;
            std::ostringstream *bestIndiStream;

        public:
            GAOptimization<EOT>(KnnObject *knn,
                           GABaseSetting *baseSetting,
                           GASelection<EOT> *selection,
                           GACrossover<EOT> *crossover,
                           GAMutation<EOT> *mutation,
                           GAReplacement<EOT> *replacement,
                           GAStopCriteria<EOT> *stop,
                           GAParallelization *parallel);
            ~GAOptimization<EOT>();

            void StartCalculation();
            void StopCalculation();

            // getter
            bool getRunStatus();

            KnnObject *getKnnObject();

            GABaseSetting * getBaseSetting();
            GASelection<EOT> * getSelection();
            GACrossover<EOT> * getCrossover();
            GAMutation<EOT> * getMutation();
            GAReplacement<EOT> * getReplacement();
            GAStopCriteria<EOT> * getStopCriteria();
            GAParallelization * getParallelization();

            unsigned int getGenerationCount();
            double getBestFitnessValue();
            std::string getMonitorString();
            std::string getBestIndiString();

            // setter
            void setKnnObject(KnnObject *knn);

            void setBaseSetting(GABaseSetting * baseSetting);
            void setSelection(GASelection<EOT> *selection);
            void setCrossover(GACrossover<EOT> *crossover);
            void setMutation(GAMutation<EOT> *mutation);
            void setReplacement(GAReplacement<EOT> *replacement);
            void setStopCriteria(GAStopCriteria<EOT> *stop);
            void setParallelization(GAParallelization *parallel);
    };


/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

template <typename EOT, template <typename IndiType> class EO>
GAMultiSettingBase<EOT, EO>::GAMultiSettingBase() {
    this->settings = new std::vector<EO<EOT>*>();
}

template <typename EOT, template <typename IndiType> class EO>
GAMultiSettingBase<EOT, EO>::~GAMultiSettingBase() {
    typename std::vector<EO<EOT>*>::iterator it;

    for ( it = this->settings->begin(); it != this->settings->end(); ++it ) {
        delete *it;
    }

    delete this->settings;
    this->settings = NULL;
}

template <typename EOT, template <typename IndiType> class EO>
std::vector<EO<EOT>*> * GAMultiSettingBase<EOT, EO>::getSettings() {
    return this->settings;
}

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

template <typename EOT, template <typename IndiType> class EO>
GASingleSettingBase<EOT, EO>::GASingleSettingBase() {
    this->setting = NULL;
}

template <typename EOT, template <typename IndiType> class EO>
GASingleSettingBase<EOT, EO>::~GASingleSettingBase() {
    delete this->setting;
    this->setting = NULL;
}

template <typename EOT, template <typename IndiType> class EO>
EO<EOT> * GASingleSettingBase<EOT, EO>::getSetting() {
    return this->setting;
}

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

template <typename EOT, template <typename IndiType> class EO>
void GASelection<EOT, EO>::setRoulettWheel() {
    if ( this->setting != NULL ) {
        delete this->setting;
        this->setting = NULL;
    }

    eoProportionalSelect<EOT> *roulettWheel; 
    roulettWheel = new eoProportionalSelect<EOT>();

    this->setting = (EO<EOT>*) roulettWheel;
}

template <typename EOT, template <typename IndiType> class EO>
void GASelection<EOT, EO>::setRoulettWheelScaled(double preasure /*= 2.0*/) {
    if ( this->setting != NULL ) {
        delete this->setting;
        this->setting = NULL;
    }

    eoFitnessScalingSelect<EOT> *roulettWheelScaled;
    roulettWheelScaled = new eoFitnessScalingSelect<EOT>(preasure);

    this->setting = (EO<EOT>*) roulettWheelScaled;
}

template <typename EOT, template <typename IndiType> class EO>
void GASelection<EOT, EO>::setStochUniSampling() {
    if ( this->setting != NULL ) {
        delete this->setting;
        this->setting = NULL;
    }

    eoStochasticUniversalSelect<EOT> *stochUniSampling;
    stochUniSampling = new eoStochasticUniversalSelect<EOT>();

    this->setting = (EO<EOT>*) stochUniSampling;
}

template <typename EOT, template <typename IndiType> class EO>
void GASelection<EOT, EO>::setRankSelection(double preasure /*= 2.0*/, double exponent /*= 1.0*/) {
    if ( this->setting != NULL ) {
        delete this->setting;
        this->setting = NULL;
    }

    eoRankingSelect<EOT> *rankSelection;
    rankSelection = new eoRankingSelect<EOT>(preasure, exponent);

    this->setting = (EO<EOT>*) rankSelection;
}

template <typename EOT, template <typename IndiType> class EO>
void GASelection<EOT, EO>::setTournamentSelection(unsigned int tSize /*= 3*/) {
    if ( this->setting != NULL ) {
        delete this->setting;
        this->setting = NULL;
    }

    eoDetTournamentSelect<EOT> *tournamentSelection;
    tournamentSelection = new eoDetTournamentSelect<EOT>(tSize);

    this->setting = (EO<EOT>*) tournamentSelection;
}

template <typename EOT, template <typename IndiType> class EO>
void GASelection<EOT, EO>::setRandomSelection() {
    if ( this->setting != NULL ) {
        delete this->setting;
        this->setting = NULL;
    }

    eoRandomSelect<EOT> *randomSelect;
    randomSelect = new eoRandomSelect<EOT>();

    this->setting = (EO<EOT>*) randomSelect;
}

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

template <typename EOT, template <typename IndiType> class EO>
GACrossover<EOT, EO>::GACrossover() {
    this->bound = NULL;
}

template <typename EOT, template <typename IndiType> class EO>
GACrossover<EOT, EO>::~GACrossover() {
    if ( this->bound != NULL ) {
        delete this->bound;
        this->bound = NULL;
    }
}

template <typename EOT, template <typename IndiType> class EO>
void GACrossover<EOT, EO>::setNPointCrossover(unsigned int n /*= 1*/) {
    eoNPtsBitXover<EOT> *nCrossover;
    nCrossover = new eoNPtsBitXover<EOT>(n);

    this->settings->push_back((EO<EOT>*) nCrossover);
}

template <typename EOT, template <typename IndiType> class EO>
void GACrossover<EOT, EO>::setUniformCrossover(double preference /*= 0.5*/) {
    eoUBitXover<EOT> *uCrossover;
    uCrossover = new eoUBitXover<EOT>(preference);

    this->settings->push_back((EO<EOT>*) uCrossover);
}

template <typename EOT, template <typename IndiType> class EO>
void GACrossover<EOT, EO>::setSBXcrossover(unsigned int numFeatures,
                                           double min, double max,
                                           double eta /*= 1.0*/) {
    if ( this->bound != NULL ) {
        delete this->bound;
        this->bound = NULL;
    }

    this->bound = new eoRealVectorBounds(numFeatures, min, max);

    eoSBXCrossover<EOT> *sbxCrossover;
    sbxCrossover = new eoSBXCrossover<EOT>(*this->bound, eta);

    this->settings->push_back((EO<EOT>*) sbxCrossover);
}

template <typename EOT, template <typename IndiType> class EO>
void GACrossover<EOT, EO>::setSegmentCrossover(unsigned int numFeatures,
                                               double min, double max,
                                               double alpha /*= 0.0*/) {
    if ( this->bound != NULL ) {
        delete this->bound;
        this->bound = NULL;
    }

    this->bound = new eoRealVectorBounds(numFeatures, min, max);

    eoSegmentCrossover<EOT> *segmentCrossover;
    segmentCrossover = new eoSegmentCrossover<EOT>(*this->bound, alpha);

    this->settings->push_back((EO<EOT>*) segmentCrossover);
}

template <typename EOT, template <typename IndiType> class EO>
void GACrossover<EOT, EO>::setHypercubeCrossover(unsigned int numFeatures,
                                                 double min, double max,
                                                 double alpha /*= 0.0*/) {
    if ( this->bound != NULL ) {
        delete this->bound;
        this->bound = NULL;
    }

    this->bound = new eoRealVectorBounds(numFeatures, min, max);

    eoHypercubeCrossover<EOT> *hypercubeCrossover;
    hypercubeCrossover = new eoHypercubeCrossover<EOT>(*this->bound, alpha);

    this->settings->push_back((EO<EOT>*) hypercubeCrossover);
}

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

template <typename EOT, template <typename IndiType> class EO>
GAMutation<EOT, EO>::GAMutation() {
    this->bound = NULL;
}

template <typename EOT, template <typename IndiType> class EO>
GAMutation<EOT, EO>::~GAMutation() {
    if ( this->bound != NULL ) {
        delete this->bound;
        this->bound = NULL;
    }
}

template <typename EOT, template <typename IndiType> class EO>
void GAMutation<EOT, EO>::setShiftMutation() {
    eoShiftMutation<EOT> *shiftMutation;
    shiftMutation = new eoShiftMutation<EOT>();

    this->settings->push_back((EO<EOT>*) shiftMutation);
}

template <typename EOT, template <typename IndiType> class EO>
void GAMutation<EOT, EO>::setSwapMutation() {
    GASwapMutation<EOT> *swapMutation;
    swapMutation = new GASwapMutation<EOT>();

    this->settings->push_back((EO<EOT>*) swapMutation);
}

template <typename EOT, template <typename IndiType> class EO>
void GAMutation<EOT, EO>::setInversionMutation() {
    GATwoOptMutation<EOT> *inversionMutation;
    inversionMutation = new GATwoOptMutation<EOT>();

    this->settings->push_back((EO<EOT>*) inversionMutation);
}

template <typename EOT, template <typename IndiType> class EO>
void GAMutation<EOT, EO>::setBinaryMutation(double rate /*= 0.05*/,
                                            bool normalize /*=false*/) {
    eoBitMutation<EOT> *binaryMutation;
    binaryMutation = new eoBitMutation<EOT>(rate, normalize);

    this->settings->push_back((EO<EOT>*) binaryMutation);
}

template <typename EOT, template <typename IndiType> class EO>
void GAMutation<EOT, EO>::setGaussMutation(unsigned int numFeatures,
                                           double min, double max,
                                           double sigma, double p_change /*= 1.0*/) {
    if ( this->bound != NULL ) {
        delete this->bound;
        this->bound = NULL;
    }

    this->bound = new eoRealVectorBounds(numFeatures, min, max);

    eoNormalVecMutation<EOT> *gaussMutation;
    gaussMutation = new eoNormalVecMutation<EOT>(*this->bound, sigma, p_change);

    this->settings->push_back((EO<EOT>*) gaussMutation);
}

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

template <typename EOT, template <typename IndiType> class EO>
void GAReplacement<EOT, EO>::setGenerationalReplacement() {
    if ( this->setting != NULL ) {
        delete this->setting;
        this->setting = NULL;
    }

    eoGenerationalReplacement<EOT> *genReplacement;
    genReplacement = new eoGenerationalReplacement<EOT>();

    this->setting = (EO<EOT>*) genReplacement;
}

template <typename EOT, template <typename IndiType> class EO>
void GAReplacement<EOT, EO>::setSSGAworse() {
    if ( this->setting != NULL ) {
        delete this->setting;
        this->setting = NULL;
    }

    eoSSGAWorseReplacement<EOT> *ssgaWorse;
    ssgaWorse = new eoSSGAWorseReplacement<EOT>();

    this->setting = (EO<EOT>*) ssgaWorse;
}

template <typename EOT, template <typename IndiType> class EO>
void GAReplacement<EOT, EO>::setSSGAdetTournament(unsigned int tSize /*= 3*/) {
    if ( this->setting != NULL ) {
        delete this->setting;
        this->setting = NULL;
    }

    eoSSGADetTournamentReplacement<EOT> *ssgaDetTour;
    ssgaDetTour = new eoSSGADetTournamentReplacement<EOT>(tSize);

    this->setting = (EO<EOT>*) ssgaDetTour;
}

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

template <typename EOT, template <typename IndiType> class EO>
void GAStopCriteria<EOT, EO>::setBestFitnessStop(double optimum /*= 1.0*/) {
    eoFitContinue<EOT> *bestFitness;
    bestFitness = new eoFitContinue<EOT>(optimum);

    this->settings->push_back((EO<EOT>*) bestFitness);
}

template <typename EOT, template <typename IndiType> class EO>
void GAStopCriteria<EOT, EO>::setMaxGenerations(unsigned int n /*= 100*/) {
    eoGenContinue<EOT> *maxGens;
    maxGens = new eoGenContinue<EOT>(n);

    this->settings->push_back((EO<EOT>*) maxGens);
}

template <typename EOT, template <typename IndiType> class EO>
void GAStopCriteria<EOT, EO>::setMaxFitnessEvals(unsigned int n /*= 5000*/) {
    eoFitContinue<EOT> *maxEvals;
    maxEvals = new eoFitContinue<EOT>(n);

    this->settings->push_back((EO<EOT>*) maxEvals);
}

template <typename EOT, template <typename IndiType> class EO>
void GAStopCriteria<EOT, EO>::setSteadyStateStop(unsigned int minGens /*= 40*/,
                                       unsigned int noChangeGens /*= 10*/) {

    eoSteadyFitContinue<EOT> *steadyFit;
    steadyFit = new eoSteadyFitContinue<EOT>(minGens, noChangeGens);

    this->settings->push_back((EO<EOT>*) steadyFit);
}

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

template <typename EOT>
GAOptimization<EOT>::GAOptimization(KnnObject *knn,
                               GABaseSetting *baseSetting,
                               GASelection<EOT> *selection,
                               GACrossover<EOT> *crossover,
                               GAMutation<EOT> *mutation,
                               GAReplacement<EOT> *replacement,
                               GAStopCriteria<EOT> *stop,
                               GAParallelization *parallel) {

    // status information
    this->running = false;

    // embedded classifier
    this->knn = knn;

    // setting objects
    this->baseSetting = baseSetting;
    this->selection = selection;
    this->crossover = crossover;
    this->mutation = mutation;
    this->replacement = replacement;
    this->stop = stop;
    this->parallelization = parallel;

    // statistics for output
    this->generationCounter = NULL;
    this->bestStat = NULL;
    this->kNNUpdater = NULL;
    this->monitorStream = NULL;
    this->bestIndiStream = NULL;
}

template <typename EOT>
GAOptimization<EOT>::~GAOptimization() {
    if (this->generationCounter != NULL ) {
        delete this->generationCounter;
        this->generationCounter = NULL;
    }
    if (this->bestStat != NULL ) {
        delete this->bestStat;
        this->bestStat = NULL;
    }
    if (this->kNNUpdater != NULL) {
        delete this->kNNUpdater;
        this->kNNUpdater = NULL;
    }
    if (this->monitorStream != NULL) {
        delete this->monitorStream;
        this->monitorStream = NULL;
    }
    if (bestIndiStream != NULL) {
        delete this->bestIndiStream;
        this->bestIndiStream = NULL;
    }
}

template <typename EOT>
void GAOptimization<EOT>::StartCalculation() {

    this->manualStop.setFlag(true);
    this->running = true;

    // seed the random number generator from EO
    rng.reseed(time(NULL));

#ifdef _OPENMP
    // *************** PARALLELIZATION ***************
    // Set parallel environment settings
    // 'make_parallel' from eoParallel works only with an eoParser object
    // so we have to simulate an argc and argv here :(
    int argc = 1;
    char *argv[] = { (char*)"dummy-argv" };
    eoParser parser(argc, argv);

    std::string section("Parallelization");
    parser.setORcreateParam(this->parallelization->isParallel(),
        "parallelize-loop",
        "Enable memory shared parallelization into evaluation's loops",
        '\0', section);
    parser.setORcreateParam(this->parallelization->isParallel(),
        "parallelize-dynamic",
        "Enable dynamic memory shared parallelization",
        '\0', section);

    omp_set_num_threads(this->parallelization->getThreadNum());

    make_parallel(parser);
#endif

    // adjust the individual size for the case of weighting with
    // prior deselected features and build an index relation map
    // for further index mapping
    unsigned int indiLength = (unsigned int)this->knn->num_features;
    std::map<unsigned int, unsigned int> indexRelation;
    unsigned int indiIndex = 0;
    for (size_t i = 0; i < this->knn->num_features; ++i) {
        if (this->knn->selection_vector[i] == 1) {
            indexRelation[indiIndex] = i;
            indiIndex++;
        } else {
            indiLength--;
        }
    }

    // *************** FITNESS SETTINGS ***************
    GAFitnessEval<EOT> fitnessEvalFunctor(this->getKnnObject(), &indexRelation);
    eoEvalFuncCounter<EOT> eval(fitnessEvalFunctor);

    // *************** POPULATIONS SETTINGS ***************
    // Create a population and fill it with random values for the start
    eoPop<EOT> population;
    eoUniformGenerator<typename EOT::AtomType> uniformGen(0.0, 1.0);

    eoInitFixedLength<EOT> random(indiLength, uniformGen);
    population.append(this->baseSetting->getPopSize(), random);

    // calculate the fitness for the individuals in the first generation
    apply<EOT>(eval, population);

    // *************** SELECTION SETTINGS ***************
    SelectOneDefaultWorth<EOT> *selectionMethod = this->selection->getSetting();
    if (selectionMethod == NULL) {
        throw std::runtime_error("GAOptimization.StartCalculation: selection invalid");
    }
    eoSelectPerc<EOT> selection(*selectionMethod);

    // *************** CROSSOVER SETTINGS ***************
    std::vector<eoQuadOp<EOT>*> *crossover = this->crossover->getSettings();
    typename std::vector<eoQuadOp<EOT>*>::iterator crossover_it;

    if (crossover->size() < 1) {
        throw std::runtime_error("GAOptimization.StartCalculation: crossover invalid");
    }

    eoPropCombinedQuadOp<EOT> xover(*(*crossover->begin()), 1.0 / (double)crossover->size());
    for (crossover_it = crossover->begin()+1; crossover_it != crossover->end(); ++crossover_it ) {
        xover.add(*(*crossover_it), 1.0 / (double)crossover->size());
    }

    // *************** MUTATION SETTINGS ***************
    std::vector<eoMonOp<EOT>*> *mutation = this->mutation->getSettings();
    typename std::vector<eoMonOp<EOT>*>::iterator mutation_it;

    if (mutation->size() < 1) {
        throw std::runtime_error("GAOptimization.StartCalculation: mutation invalid");
    }

    eoPropCombinedMonOp<EOT> muta(*(*mutation->begin()), 1.0 / (double)mutation->size());
    for(mutation_it = mutation->begin()+1; mutation_it != mutation->end(); ++mutation_it) {
        muta.add(*(*mutation_it), 1.0 / (double)mutation->size());
    }

    // *************** REPLACEMENT SETTINGS ***************
    eoReplacement<EOT> *replacement = this->replacement->getSetting();
    if (replacement == NULL) {
        throw std::runtime_error("GAOptimization.StartCalculation: replacement invalid");
    }

    // *************** STOP CRITERIA SETTINGS ***************
    std::vector<eoContinue<EOT>*> *stop = this->stop->getSettings();
    typename std::vector<eoContinue<EOT>*>::iterator stop_it;

    if (stop->size() < 1) {
        throw std::runtime_error("GAOptimization.StartCalculation: stop criteria invalid");
    }

    eoCombinedContinue<EOT> continuator(*(*stop->begin()));
    for (stop_it = stop->begin()+1; stop_it != stop->end(); ++stop_it ) {
        continuator.add(*(*stop_it));
    }

    // add the continuator for manual stopping the calculation
    continuator.add(this->manualStop);

    // *************** CHECKPOINT SETTINGS ***************
    eoCheckPoint<EOT> checkpoint( continuator );

    if (this->generationCounter != NULL ) {
        delete this->generationCounter;
    }
    if (this->bestStat != NULL ) {
        delete this->bestStat;
    }
    if (this->kNNUpdater != NULL) {
        delete this->kNNUpdater;
    }
    if (this->monitorStream != NULL) {
        delete this->monitorStream;
    }
    if (this->bestIndiStream != NULL) {
        delete this->bestIndiStream;
    }

    this->generationCounter = new eoIncrementorParam<unsigned int>("Generation");
    this->bestStat = new eoBestFitnessStat<EOT>();
    eoSecondMomentStats<EOT> secondStat;
    GABestIndiStat<EOT> bestIndividualStat;

    this->monitorStream = new std::ostringstream(std::ostringstream::out);
    eoOStreamMonitor monitor(*(this->monitorStream), "\t");
    monitor.add(*(this->generationCounter));
    monitor.add(eval);
    monitor.add(*(this->bestStat));
    monitor.add(secondStat);
    checkpoint.add(monitor);

    this->bestIndiStream = new std::ostringstream(std::ostringstream::out);
    eoOStreamMonitor bestIndiMonitor(*(this->bestIndiStream), "\t");
    bestIndiMonitor.add(bestIndividualStat);
    checkpoint.add(bestIndiMonitor);

    checkpoint.add(*(this->generationCounter));
    checkpoint.add(*(this->bestStat));
    checkpoint.add(secondStat);
    checkpoint.add(bestIndividualStat);

    this->kNNUpdater = new GAClassifierUpdater<EOT>(this->getKnnObject(), &indexRelation);
    checkpoint.add(*(this->kNNUpdater));

    // *************** MAIN SETUP ***************
    eoSGATransform<EOT> transform(xover, this->baseSetting->getCrossRate(),
                                  muta, this->baseSetting->getMutRate());

    eoEasyEA<EOT> realGA( checkpoint, eval, selection, transform, *replacement );

    // run the main GA algorithm
    if (this->manualStop.getFlag()) {
        realGA(population);
    }
    this->running = false;
}

template <typename EOT>
void GAOptimization<EOT>::StopCalculation() {
    this->manualStop.setFlag(false);
}

// *********************** GETTER ***********************

template <typename EOT>
bool GAOptimization<EOT>::getRunStatus() {
    return this->running;
}

template <typename EOT>
KnnObject * GAOptimization<EOT>::getKnnObject() {
    return this->knn;
}

template <typename EOT>
GABaseSetting * GAOptimization<EOT>::getBaseSetting() {
    return this->baseSetting;
}

template <typename EOT>
GASelection<EOT> * GAOptimization<EOT>::getSelection() {
    return this->selection;
}

template <typename EOT>
GACrossover<EOT> * GAOptimization<EOT>::getCrossover() {
    return this->crossover;
}

template <typename EOT>
GAMutation<EOT> * GAOptimization<EOT>::getMutation() {
    return this->mutation;
}

template <typename EOT>
GAReplacement<EOT> * GAOptimization<EOT>::getReplacement() {
    return this->replacement;
}

template <typename EOT>
GAStopCriteria<EOT> * GAOptimization<EOT>::getStopCriteria() {
    return this->stop;
}

template <typename EOT>
GAParallelization * GAOptimization<EOT>::getParallelization() {
    return this->parallelization;
}

template <typename EOT>
unsigned int GAOptimization<EOT>::getGenerationCount() {
    if (this->generationCounter == NULL ) {
        return 0;
    } else {
        return this->generationCounter->value();
    }
}

template <typename EOT>
double GAOptimization<EOT>::getBestFitnessValue() {
    if (this->bestStat == NULL) {
        return 0.0;
    } else {
        return this->kNNUpdater->getBestFitness();
    }
}

template <typename EOT>
std::string GAOptimization<EOT>::getMonitorString() {
    if (this->monitorStream == NULL) {
        return "";
    } else {
        return this->monitorStream->str();
    }
}

template <typename EOT>
std::string GAOptimization<EOT>::getBestIndiString() {
    if (this->bestIndiStream == NULL) {
        return "";
    } else {
        return this->bestIndiStream->str();
    }
}
// *********************** SETTER ***********************

template <typename EOT>
void GAOptimization<EOT>::setKnnObject(KnnObject *knn) {
    this->knn = knn;
}

template <typename EOT>
void GAOptimization<EOT>::setBaseSetting(GABaseSetting * baseSetting) {
    this->baseSetting = baseSetting;
}

template <typename EOT>
void GAOptimization<EOT>::setSelection(GASelection<EOT> *selection) {
    this->selection = selection;
}

template <typename EOT>
void GAOptimization<EOT>::setCrossover(GACrossover<EOT> *crossover) {
    this->crossover = crossover;
}

template <typename EOT>
void GAOptimization<EOT>::setMutation(GAMutation<EOT> *mutation) {
    this->mutation = mutation;
}

template <typename EOT>
void GAOptimization<EOT>::setReplacement(GAReplacement<EOT> *replacement) {
    this->replacement = replacement;
}

template <typename EOT>
void GAOptimization<EOT>::setStopCriteria(GAStopCriteria<EOT> *stop) {
    this->stop = stop;
}

template <typename EOT>
void GAOptimization<EOT>::setParallelization(GAParallelization *parallel) {
    this->parallelization = parallel;
}


}} // end of namespaces

#endif

