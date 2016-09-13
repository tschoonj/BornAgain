// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/FitKernel.cpp
//! @brief     Implements class FitKernel.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "FitKernel.h"
#include "FitKernelImp.h"
#include "MinimizerFactory.h"
#include "FitParameter.h"

FitKernel::FitKernel()
    : m_impl(new FitKernelImp)
{

}

FitKernel::~FitKernel()
{

}

void FitKernel::setMinimizer(const std::string &minimizerName, const std::string &algorithmName)
{
    m_impl->setMinimizer(MinimizerFactory::createMinimizer(minimizerName, algorithmName));
}

void FitKernel::addFitParameter(const std::string &name, double value,
                                const RealLimits &lim, const Attributes &attr, double step)
{

    m_impl->addFitParameter(new FitParameter(name, value, step, lim, attr));

}

void FitKernel::setObjectiveFunction(function_chi2_t func)
{
    m_impl->setObjectiveFunction(func);
}

void FitKernel::minimize()
{
    m_impl->minimize();
}
