#include "LatticeBasis.h"
#include "FormFactors.h"
#include "DiffuseParticleInfo.h"

LatticeBasis::LatticeBasis()
: Particle(complex_t(1.0, 0.0))
{
    setName("LatticeBasis");
}

LatticeBasis::LatticeBasis(const Particle& particle)
: Particle(complex_t(1.0, 0.0))
{
    setName("LatticeBasis");
    std::vector<kvector_t> positions;
    positions.push_back(kvector_t(0.0, 0.0, 0.0));
    addParticle( particle, positions );
}

LatticeBasis::LatticeBasis(const Particle& particle,
        std::vector<kvector_t> positions)
: Particle(complex_t(1.0, 0.0))
{
    setName("LatticeBasis");
    addParticle(particle, positions);
}

LatticeBasis::~LatticeBasis()
{
    for (size_t index=0; index<m_particles.size(); ++index) {
        delete m_particles[index];
    }
}

LatticeBasis* LatticeBasis::clone() const
{
    LatticeBasis *p_new = new LatticeBasis();
    for (size_t index=0; index<m_particles.size(); ++index) {
        p_new->addParticle(*m_particles[index], m_positions_vector[index]);
    }
    p_new->setName(getName());
    p_new->m_ambient_refractive_index = this->m_ambient_refractive_index;
    return p_new;
}

void LatticeBasis::addParticle(const Particle& particle, std::vector<kvector_t > positions)
{
    Particle *np = particle.clone();
    registerChild(np);
    m_particles.push_back(np);
    m_positions_vector.push_back(positions);
}

void LatticeBasis::setAmbientRefractiveIndex(complex_t refractive_index)
{
    Particle::setAmbientRefractiveIndex(refractive_index);
    for (size_t index=0; index<m_particles.size(); ++index) {
        m_particles[index]->setAmbientRefractiveIndex(refractive_index);
    }
}

IFormFactor* LatticeBasis::createFormFactor() const
{
    FormFactorWeighted *p_ff = new FormFactorWeighted();
    for (size_t index=0; index<m_particles.size(); ++index) {
        IFormFactor *p_particle_ff = m_particles[index]->createFormFactor();
        FormFactorDecoratorMultiPositionFactor pos_ff(*p_particle_ff, m_positions_vector[index]);
        p_ff->addFormFactor(pos_ff);
        delete p_particle_ff;
    }
    p_ff->setAmbientRefractiveIndex(m_ambient_refractive_index);
    return p_ff;
}

std::vector<DiffuseParticleInfo *> LatticeBasis::createDiffuseParticleInfos() const
{
    std::vector<DiffuseParticleInfo *> result;
    for (size_t index=0; index<getNbrParticles(); ++index) {
        const Particle *p_particle = getParticle(index);
        if (p_particle->hasDistributedFormFactor()) {
            DiffuseParticleInfo *p_new_info = new DiffuseParticleInfo(
                    p_particle->clone());
            p_new_info->setNumberPerMeso((double)getNbrPositionsForParticle(index));
            result.push_back(p_new_info);
        }
    }
    return result;
}
