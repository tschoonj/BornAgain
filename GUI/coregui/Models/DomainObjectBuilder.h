// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/DomainObjectBuilder.h
//! @brief     Declares class DomainObjectBuilder
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2016
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   Céline Durniak, Marina Ganeva, David Li, Gennady Pospelov
//! @authors   Walter Van Herck, Joachim Wuttke
//
// ************************************************************************** //

#ifndef DOMAINOBJECTBUILDER_H
#define DOMAINOBJECTBUILDER_H


#include <memory>

class Instrument;
class MultiLayer;
class Layer;
class ParticleLayout;
class IInterferenceFunction;
class Beam;
class SessionItem;

class BA_CORE_API_ DomainObjectBuilder
{
public:
    std::unique_ptr<MultiLayer> buildMultiLayer(const SessionItem &multilayer_item) const;
    std::unique_ptr<Layer> buildLayer(const SessionItem &item) const;
    std::unique_ptr<ParticleLayout> buildParticleLayout(const SessionItem &item) const;
    std::unique_ptr<IInterferenceFunction>
    buildInterferenceFunction(const SessionItem &item) const;
    std::unique_ptr<Instrument> buildInstrument(const SessionItem &instrument_item) const;
    std::unique_ptr<Beam> buildBeam(const SessionItem &item) const;
};

#endif // DOMAINOBJECTBUILDER_H
