// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SimulationWidgets/SimulationSetupAssistant.h
//! @brief     Defines class SimulationSetupAssistant
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SIMULATIONSETUPASSISTANT_H
#define SIMULATIONSETUPASSISTANT_H

#include "WinDllMacros.h"
#include <QStringList>

class MultiLayerItem;
class GISASInstrumentItem;
class RealDataItem;

//! The SimulationSetupAssistant class provides sample, instrument and real data validation before
//! submitting the job.

class BA_CORE_API_ SimulationSetupAssistant {
public:
    SimulationSetupAssistant();

    bool isValidSimulationSetup(const MultiLayerItem *multiLayerItem,
                                const GISASInstrumentItem *instrumentItem,
                                const RealDataItem *realData = 0);
private:
    void clear();
    void checkMultiLayerItem(const MultiLayerItem *multiLayerItem);
    void checkInstrumentItem(const GISASInstrumentItem *instrumentItem);
    void checkFittingSetup(const GISASInstrumentItem *instrumentItem, const RealDataItem *realData);
    QString composeMessage();

    bool m_isValid;
    QStringList m_messages;
};


#endif // SIMULATIONSETUPASSISTANT_H
