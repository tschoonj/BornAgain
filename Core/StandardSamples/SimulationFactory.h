// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/StandardSamples/SimulationFactory.h
//! @brief     Defines class SimulationFactory.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef SIMULATIONFACTORY_H
#define SIMULATIONFACTORY_H

#include "IFactory.h"

//! @class SimulationFactory
//! @ingroup standard_samples
//! @brief Registry to create standard pre-defined simulations.
//! Used in functional tests, performance measurements, etc.

class BA_CORE_API_ SimulationFactory : public IFactory<std::string, class GISASSimulation>
{
public:
    SimulationFactory();
};

#endif // SIMULATIONFACTORY_H
