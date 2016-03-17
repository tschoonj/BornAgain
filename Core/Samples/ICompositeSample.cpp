// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Samples/src/ICompositeSample.cpp
//! @brief     Implements class ICompositeSample.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "ICompositeSample.h"
#include "SampleTreeIterator.h"
#include "MessageService.h"
#include "Exceptions.h"
#include "Utils.h"

#include <algorithm>
#include <sstream>


//! Registers child in the container

void ICompositeSample::registerChild(ISample *sample)
{
    if(sample) {
        m_samples.push_back(sample);
    } else {
        throw NullPointerException("ICompositeSample::registerChild -> Error. Null pointer.");
    }
}

//! remove registered child from the container

void ICompositeSample::deregisterChild(ISample *sample)
{
    std::vector<ISample*>::iterator it = std::find(m_samples.begin(), m_samples.end(), sample);
    if (it != m_samples.end()) {
        m_samples.erase(it);
    }
}

ISample *ICompositeSample::operator[](size_t index)
{
    if (childIndexInRange(index)) {
        return m_samples[index];
    }
    return 0;
}

const ISample *ICompositeSample::operator[](size_t index) const
{
    if (childIndexInRange(index)) {
        return m_samples[index];
    }
    return 0;
}

std::vector<const ISample *> ICompositeSample::getChildren() const
{
    std::vector<const ISample *> result;
    for (size_t i=0; i<m_samples.size(); ++i) {
        result.push_back(m_samples[i]);
    }
    return result;
}

std::string ICompositeSample::addParametersToExternalPool(std::string path,
                                                          ParameterPool *external_pool,
                                                          int copy_number) const
{
    std::string new_path
        = IParameterized::addParametersToExternalPool(path, external_pool, copy_number);

    // We need a mechanism to handle cases with multiple children with the same name.
    // First run through all direct children and save their names
    Utils::StringUsageMap strUsageMap;
    for (size_t i = 0; i < m_samples.size(); ++i) {
        strUsageMap.add(new_path + m_samples[i]->getName()); // saving child names
    }
    // Now run through the direct children again and assign a copy number for
    // all children with the same name
    Utils::StringUsageMap strUsageMap2;
    for (size_t i = 0; i < m_samples.size(); ++i) {
        std::string child_name = new_path + m_samples[i]->getName();
        strUsageMap2.add(child_name);
        // Copy number starts from 0:
        int ncopy = strUsageMap2[child_name] - 1;

        // If the child is the only one with that name, we do not want any copy number:
        if (strUsageMap[child_name] == 1)
            ncopy = -1;

        m_samples[i]->addParametersToExternalPool(new_path, external_pool, ncopy);
    }
    return new_path;
}

bool ICompositeSample::childIndexInRange(size_t index) const
{
    return index<m_samples.size();
}
