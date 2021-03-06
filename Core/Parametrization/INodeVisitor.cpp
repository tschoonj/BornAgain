// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Parametrization/INodeVisitor.cpp
//! @brief     Implements class INodeVisitor.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "IterationStrategy.h"
#include "NodeIterator.h"

void VisitNodesPreorder(const INode& node, INodeVisitor& visitor)
{
    NodeIterator<PreorderStrategy> it(&node);
    it.first();
    while (!it.isDone()) {
        visitor.setDepth(it.depth());
        const INode *child = it.getCurrent();
        child->accept(&visitor);
        it.next();
    }
}

void VisitNodesPostorder(const INode& node, INodeVisitor& visitor)
{
    NodeIterator<PostorderStrategy> it(&node);
    it.first();
    while (!it.isDone()) {
        visitor.setDepth(it.depth());
        const INode *child = it.getCurrent();
        child->accept(&visitor);
        it.next();
    }
}
