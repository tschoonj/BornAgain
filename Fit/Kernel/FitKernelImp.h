// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Fit/Minimizer/FitKernelImp.h
//! @brief     Defines class FitKernelImp.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef FITKERNELIMP_H
#define FITKERNELIMP_H

#include "WinDllMacros.h"
#include "KernelTypes.h"
#include "FitSuiteParameters.h"
#include "ObjectiveFunction.h"
#include <memory>

class IMinimizer;
class FitParameter;

//! @class FitKernelImp
//! @ingroup fitting_internal
//! @brief The FitKernel implementation.

class BA_CORE_API_ FitKernelImp
{
public:
    FitKernelImp();
    ~FitKernelImp();

    //! Sets minimizer
    void setMinimizer(IMinimizer* minimizer);

    //! Adds fit parameter
    void addFitParameter(FitParameter* par);

    void setObjectiveFunction(objective_function_t func);

    void minimize();

    //! Reports results of minimization in the form of multi-line string.
    std::string reportResults() const;

    FitSuiteParameters* fitParameters();

     IMinimizer *minimizer() ;

private:
    FitSuiteParameters m_fit_parameters;
    std::unique_ptr<IMinimizer> m_minimizer;
    ObjectiveFunction m_objective_function;
};

#endif
