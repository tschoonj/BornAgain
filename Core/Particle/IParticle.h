// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Core/Particle/IParticle.h
//! @brief     Defines interface IParticle.
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#ifndef IPARTICLE_H
#define IPARTICLE_H

#include "IAbstractParticle.h"
#include "Rotations.h"
#include "SafePointerVector.h"
#include "SlicedParticle.h"
#include "Vectors3D.h"
#include "ZLimits.h"
#include <memory>


struct ParticleLimits
{
    double m_bottom;
    double m_top;
};

//! Pure virtual base class for Particle, ParticleComposition, ParticleCoreShell, MesoCrystal.
//! Provides position/rotation and form factor. Abundance is inherited from IAbstractParticle.
//!
//! @ingroup samples

class BA_CORE_API_ IParticle : public IAbstractParticle
{
public:
    ~IParticle() {}
    IParticle* clone() const  override=0;

    void accept(INodeVisitor* visitor) const override { visitor->visit(this); }

    //! Create a form factor for this particle
    virtual IFormFactor* createFormFactor() const;

    //! Create a sliced form factor for this particle
    virtual SlicedParticle createSlicedParticle(ZLimits limits) const;

    //! Returns particle position.
    kvector_t position() const { return m_position; }

    //! Sets relative position of the particle's reference point in the
    //! coordinate system of parent.
    //! @param position: relative position vector (components are in nanometers)
    void setPosition(kvector_t position) { m_position = position; }

    //! Sets relative position of the particle's reference point in the
    //! coordinate system of parent.
    //! @param x: x-coordinate in nanometers
    //! @param y: y-coordinate in nanometers
    //! @param z: z-coordinate in nanometers
    void setPosition(double x, double y, double z) { m_position = kvector_t(x, y, z); }

    //! Translates the particle
    void translate(kvector_t translation) override final;

    //! Returns rotation object
    const IRotation* rotation() const;

    //! Sets transformation.
    void setRotation(const IRotation& rotation);

    //! Applies transformation by composing it with the existing one
    void rotate(const IRotation& rotation);

    std::vector<const INode*> getChildren() const override;

    void registerAbundance(bool make_registered = true);

    //! Registers the three components of its position
    void registerPosition(bool make_registered = true);

    //! Decompose in constituent IParticle objects
    virtual SafePointerVector<IParticle> decompose() const;

    //! Top and bottom z-coordinate
    virtual ParticleLimits bottomTopZ() const;

protected:
    //! Creates a composed IRotation object
    IRotation* createComposedRotation(const IRotation* p_rotation) const;

    //! Gets a composed translation vector
    kvector_t composedTranslation(const IRotation* p_rotation, kvector_t translation) const;

    //! Registers abundance and position
    void registerParticleProperties();

    kvector_t m_position;
    std::unique_ptr<IRotation> mP_rotation;
};

#endif // IPARTICLE_H
