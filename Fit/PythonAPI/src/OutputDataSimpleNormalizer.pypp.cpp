// This file has been generated by Py++.

#include "Macros.h"
GCC_DIAG_OFF(unused-parameter);
GCC_DIAG_OFF(missing-field-initializers);
#include "boost/python.hpp"
#include "boost/python/suite/indexing/vector_indexing_suite.hpp"
GCC_DIAG_ON(unused-parameter);
GCC_DIAG_ON(missing-field-initializers);
#include "AttLimits.h"
#include "IChiSquaredModule.h"
#include "IMinimizer.h"
#include "ChiSquaredModule.h"
#include "FitSuite.h"
#include "FitSuiteParameters.h"
#include "MinimizerFactory.h"
#include "PythonPlusplusFitHelper.h"
#include "MathFunctions.h"
#include "ISquaredFunction.h"
#include "IOutputDataNormalizer.h"
#include "OutputDataSimpleNormalizer.pypp.h"

namespace bp = boost::python;

struct OutputDataSimpleNormalizer_wrapper : OutputDataSimpleNormalizer, bp::wrapper< OutputDataSimpleNormalizer > {

    OutputDataSimpleNormalizer_wrapper(OutputDataSimpleNormalizer const & arg )
    : OutputDataSimpleNormalizer( arg )
      , bp::wrapper< OutputDataSimpleNormalizer >(){
        // copy constructor
        
    }

    OutputDataSimpleNormalizer_wrapper(double scale=1.0e+0, double shift=0.0 )
    : OutputDataSimpleNormalizer( scale, shift )
      , bp::wrapper< OutputDataSimpleNormalizer >(){
        // constructor
    
    }

    virtual ::OutputDataSimpleNormalizer * clone(  ) const  {
        if( bp::override func_clone = this->get_override( "clone" ) )
            return func_clone(  );
        else{
            return this->OutputDataSimpleNormalizer::clone(  );
        }
    }
    
    ::OutputDataSimpleNormalizer * default_clone(  ) const  {
        return OutputDataSimpleNormalizer::clone( );
    }

    virtual void setMaximumIntensity( double max_intensity ) {
        if( bp::override func_setMaximumIntensity = this->get_override( "setMaximumIntensity" ) )
            func_setMaximumIntensity( max_intensity );
        else{
            this->OutputDataSimpleNormalizer::setMaximumIntensity( max_intensity );
        }
    }
    
    void default_setMaximumIntensity( double max_intensity ) {
        OutputDataSimpleNormalizer::setMaximumIntensity( max_intensity );
    }

    virtual ::OutputData< double > * createNormalizedData( ::OutputData< double > const & data ) const  {
        if( bp::override func_createNormalizedData = this->get_override( "createNormalizedData" ) )
            return func_createNormalizedData( boost::ref(data) );
        else{
            return this->OutputDataNormalizer::createNormalizedData( boost::ref(data) );
        }
    }
    
    ::OutputData< double > * default_createNormalizedData( ::OutputData< double > const & data ) const  {
        return OutputDataNormalizer::createNormalizedData( boost::ref(data) );
    }

};

void register_OutputDataSimpleNormalizer_class(){

    bp::class_< OutputDataSimpleNormalizer_wrapper, bp::bases< OutputDataNormalizer > >( "OutputDataSimpleNormalizer", bp::init< bp::optional< double, double > >(( bp::arg("scale")=1.0e+0, bp::arg("shift")=0.0 )) )    
        .def( 
            "clone"
            , (::OutputDataSimpleNormalizer * ( ::OutputDataSimpleNormalizer::* )(  ) const)(&::OutputDataSimpleNormalizer::clone)
            , (::OutputDataSimpleNormalizer * ( OutputDataSimpleNormalizer_wrapper::* )(  ) const)(&OutputDataSimpleNormalizer_wrapper::default_clone)
            , bp::return_value_policy< bp::manage_new_object >() )    
        .def( 
            "setMaximumIntensity"
            , (void ( ::OutputDataSimpleNormalizer::* )( double ) )(&::OutputDataSimpleNormalizer::setMaximumIntensity)
            , (void ( OutputDataSimpleNormalizer_wrapper::* )( double ) )(&OutputDataSimpleNormalizer_wrapper::default_setMaximumIntensity)
            , ( bp::arg("max_intensity") ) )    
        .def( 
            "createNormalizedData"
            , (::OutputData< double > * ( ::OutputDataNormalizer::* )( ::OutputData< double > const & ) const)(&::OutputDataNormalizer::createNormalizedData)
            , (::OutputData< double > * ( OutputDataSimpleNormalizer_wrapper::* )( ::OutputData< double > const & ) const)(&OutputDataSimpleNormalizer_wrapper::default_createNormalizedData)
            , ( bp::arg("data") )
            , bp::return_value_policy< bp::manage_new_object >() );

}
