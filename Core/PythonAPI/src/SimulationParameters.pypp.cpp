// This file has been generated by Py++.

#include "Macros.h"
GCC_DIAG_OFF(unused-parameter);
GCC_DIAG_OFF(missing-field-initializers);
#include "boost/python.hpp"
#include "boost/python/suite/indexing/vector_indexing_suite.hpp"
GCC_DIAG_ON(unused-parameter);
GCC_DIAG_ON(missing-field-initializers);
#include "BasicVector3D.h"
#include "Bin.h"
#include "Crystal.h"
#include "DiffuseParticleInfo.h"
#include "FTDistributions.h"
#include "FormFactorBox.h"
#include "FormFactorCrystal.h"
#include "FormFactorCylinder.h"
#include "FormFactorDecoratorDebyeWaller.h"
#include "FormFactorFullSphere.h"
#include "FormFactorGauss.h"
#include "FormFactorLorentz.h"
#include "FormFactorParallelepiped.h"
#include "FormFactorPrism3.h"
#include "FormFactorPyramid.h"
#include "FormFactorSphereGaussianRadius.h"
#include "HomogeneousMaterial.h"
#include "ICloneable.h"
#include "IClusteredParticles.h"
#include "ICompositeSample.h"
#include "IDecoration.h"
#include "IFormFactor.h"
#include "IFormFactorBorn.h"
#include "IFormFactorDecorator.h"
#include "IInterferenceFunction.h"
#include "IMaterial.h"
#include "IParameterized.h"
#include "ISample.h"
#include "ISampleBuilder.h"
#include "ISelectionRule.h"
#include "ISingleton.h"
#include "Instrument.h"
#include "InterferenceFunction1DParaCrystal.h"
#include "InterferenceFunction2DLattice.h"
#include "InterferenceFunction2DParaCrystal.h"
#include "InterferenceFunctionNone.h"
#include "Lattice.h"
#include "Lattice2DIFParameters.h"
#include "LatticeBasis.h"
#include "Layer.h"
#include "LayerDecorator.h"
#include "LayerRoughness.h"
#include "Lattice2DIFParameters.h"
#include "MaterialManager.h"
#include "MesoCrystal.h"
#include "MultiLayer.h"
#include "OpticalFresnel.h"
#include "ParameterPool.h"
#include "Particle.h"
#include "ParticleBuilder.h"
#include "ParticleCoreShell.h"
#include "ParticleDecoration.h"
#include "OutputData.h"
#include "ParticleInfo.h"
#include "PositionParticleInfo.h"
#include "PythonOutputData.h"
#include "PythonPlusplusHelper.h"
#include "RealParameterWrapper.h"
#include "Simulation.h"
#include "SimulationParameters.h"
#include "IStochasticParameter.h"
#include "StochasticGaussian.h"
#include "StochasticSampledParameter.h"
#include "StochasticDoubleGate.h"
#include "Transform3D.h"
#include "Types.h"
#include "Units.h"
#include "SimulationParameters.pypp.h"

namespace bp = boost::python;

void register_SimulationParameters_class(){

    { //::SimulationParameters
        typedef bp::class_< SimulationParameters > SimulationParameters_exposer_t;
        SimulationParameters_exposer_t SimulationParameters_exposer = SimulationParameters_exposer_t( "SimulationParameters", bp::init< >() );
        bp::scope SimulationParameters_scope( SimulationParameters_exposer );
        bp::enum_< SimulationParameters::EFramework>("EFramework")
            .value("DWBA", SimulationParameters::DWBA)
            .value("BA", SimulationParameters::BA)
            .export_values()
            ;
        bp::enum_< SimulationParameters::EInterferenceApproximation>("EInterferenceApproximation")
            .value("DA", SimulationParameters::DA)
            .value("LMA", SimulationParameters::LMA)
            .value("SSCA", SimulationParameters::SSCA)
            .value("ISGISAXSMOR", SimulationParameters::ISGISAXSMOR)
            .export_values()
            ;
        bp::enum_< SimulationParameters::ELatticeType>("ELatticeType")
            .value("NONE", SimulationParameters::NONE)
            .value("LATTICE", SimulationParameters::LATTICE)
            .value("PARA1D", SimulationParameters::PARA1D)
            .value("PARA1DFINITE", SimulationParameters::PARA1DFINITE)
            .export_values()
            ;
        SimulationParameters_exposer.def_readwrite( "me_framework", &SimulationParameters::me_framework );
        SimulationParameters_exposer.def_readwrite( "me_if_approx", &SimulationParameters::me_if_approx );
        SimulationParameters_exposer.def_readwrite( "me_lattice_type", &SimulationParameters::me_lattice_type );
    }

}
