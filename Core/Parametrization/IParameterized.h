// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/IParameterized.h
//! @brief     Defines class IParameterized.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IPARAMETERIZED_H
#define IPARAMETERIZED_H

#include "INamed.h"

class RealLimits;
class ParameterPool;
class RealParameter;

//! Manages a local parameter pool, and a tree of child pools.
//! @ingroup tools_internal

class BA_CORE_API_ IParameterized : public INamed
{
public:
    IParameterized(const std::string& name="");
    IParameterized(const IParameterized& other);
    ~IParameterized();

    IParameterized operator=(const IParameterized& other) = delete;

    //! Returns pointer to the parameter pool.
    ParameterPool* parameterPool() const { return m_pool; }

    //! Creates new parameter pool, with all local parameters and those of its children.
    virtual ParameterPool* createParameterTree() const;

    //! Returns multiline string representing available parameters.
    std::string parametersToString() const;

    RealParameter& registerParameter(const std::string& name, double* parpointer);

    void setParameterValue(const std::string& name, double value);

    RealParameter* parameter(const std::string& name) const;

    //! Action to be taken in inherited class when a parameter has changed.
    virtual void onChange() {}

    void removeParameter(const std::string& name);

private:
    ParameterPool* m_pool; //!< parameter pool (kind of pointer-to-implementation)
};

#endif // IPARAMETERIZED_H
