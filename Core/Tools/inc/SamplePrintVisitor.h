#ifndef SAMPLEPRINTVISITOR_H
#define SAMPLEPRINTVISITOR_H

#include "ISampleVisitor.h"
#include <string>

//! The SamplePrintVisitor
class BA_CORE_API_ SamplePrintVisitor : public ISampleVisitor
{
public:
    SamplePrintVisitor() {}

    virtual void visit(const ISample *sample);

    virtual void visit(const ICompositeSample *sample);

    virtual void visit(const IClusteredParticles *sample);
    virtual void visit(const Crystal *sample);

    virtual void visit(const IDecoration *sample);
    virtual void visit(const ParticleDecoration *sample);

    virtual void visit(const Layer *sample);

    virtual void visit(const LayerInterface *sample);

    virtual void visit(const MultiLayer *sample);

    virtual void visit(const Particle *sample);
    virtual void visit(const LatticeBasis *sample);
    virtual void visit(const MesoCrystal *sample);
    virtual void visit(const ParticleCoreShell *sample);

    virtual void visit(const ParticleInfo *sample);
    virtual void visit(const DiffuseParticleInfo *sample);
    virtual void visit(const PositionParticleInfo *sample);

    virtual void visit(const IFormFactor *sample);

    virtual void visit(const FormFactorDWBAPol *sample);
    virtual void visit(const FormFactorDWBAPolConstZ *sample);

    virtual void visit(const FormFactorWeighted *sample);

    virtual void visit(const IFormFactorBorn *sample);

    virtual void visit(const FormFactorBox *sample);
    virtual void visit(const FormFactorCone *sample);
    virtual void visit(const FormFactorCone6 *sample);
    virtual void visit(const FormFactorCrystal *sample);
    virtual void visit(const FormFactorCylinder *sample);
    virtual void visit(const FormFactorEllipsoid *sample);
    virtual void visit(const FormFactorFullSphere *sample);
    virtual void visit(const FormFactorFullSpheroid *sample);
    virtual void visit(const FormFactorGauss *sample);
    virtual void visit(const FormFactorHemiSpheroid *sample);
    virtual void visit(const FormFactorLorentz *sample);
    virtual void visit(const FormFactorParallelepiped *sample);
    virtual void visit(const FormFactorPrism3 *sample);
    virtual void visit(const FormFactorPrism6 *sample);
    virtual void visit(const FormFactorPyramid *sample);
    virtual void visit(const FormFactorSphere *sample);
    virtual void visit(const FormFactorSphereGaussianRadius *sample);
    virtual void visit(const FormFactorTetrahedron *sample);
    virtual void visit(const IFormFactorBornSeparable *sample);

    virtual void visit(const IFormFactorDecorator *sample);

    virtual void visit(const FormFactorDWBA *sample);
    virtual void visit(const FormFactorDWBAConstZ *sample);
    virtual void visit(const FormFactorDecoratorDebyeWaller *sample);
    virtual void visit(const FormFactorDecoratorFactor *sample);
    virtual void visit(const FormFactorDecoratorMaterial *sample);
    virtual void visit(const FormFactorDecoratorMultiPositionFactor *sample);
    virtual void visit(const FormFactorDecoratorPositionFactor *sample);
    virtual void visit(const FormFactorDecoratorTransformation *sample);

    virtual void visit(const IInterferenceFunction *sample);
    virtual void visit(const InterferenceFunction1DParaCrystal *sample);
    virtual void visit(const InterferenceFunction2DLattice *sample);
    virtual void visit(const InterferenceFunction2DParaCrystal *sample);
    virtual void visit(const InterferenceFunctionNone *sample);

    virtual void visit(const IRoughness *sample);
    virtual void visit(const LayerRoughness *sample);

private:
    std::string get_indent();
    void print_default(const ISample *sample);
};



#endif // SAMPLEPRINTVISITOR_H
