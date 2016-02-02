// This file has been generated by Py++.

// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      Automatically generated boost::python code for BornAgain Python bindings
//! @brief     Automatically generated boost::python code for BornAgain Python bindings
//!
//! @homepage  http://bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Juelich GmbH 2015
//! @authors   Scientific Computing Group at MLZ Garching
//! @authors   C. Durniak, M. Ganeva, G. Pospelov, W. Van Herck, J. Wuttke
//
// ************************************************************************** //

#include "Macros.h"
GCC_DIAG_OFF(unused-parameter)
GCC_DIAG_OFF(missing-field-initializers)
#include "boost/python.hpp"
GCC_DIAG_ON(unused-parameter)
GCC_DIAG_ON(missing-field-initializers)
#include "PythonCoreList.h"
#include "FTDecayFunction2DCauchy.pypp.h"

namespace bp = boost::python;

struct FTDecayFunction2DCauchy_wrapper : FTDecayFunction2DCauchy, bp::wrapper< FTDecayFunction2DCauchy > {

    FTDecayFunction2DCauchy_wrapper(FTDecayFunction2DCauchy const & arg )
    : FTDecayFunction2DCauchy( arg )
      , bp::wrapper< FTDecayFunction2DCauchy >(){
        // copy constructor
        m_pyobj = 0;
    }

    FTDecayFunction2DCauchy_wrapper(double decay_length_x, double decay_length_y )
    : FTDecayFunction2DCauchy( decay_length_x, decay_length_y )
      , bp::wrapper< FTDecayFunction2DCauchy >(){
        // constructor
    m_pyobj = 0;
    }

    virtual ::FTDecayFunction2DCauchy * clone(  ) const  {
        if( bp::override func_clone = this->get_override( "clone" ) )
            return func_clone(  );
        else{
            return this->FTDecayFunction2DCauchy::clone(  );
        }
    }
    
    ::FTDecayFunction2DCauchy * default_clone(  ) const  {
        return FTDecayFunction2DCauchy::clone( );
    }

    virtual double evaluate( double qx, double qy ) const  {
        if( bp::override func_evaluate = this->get_override( "evaluate" ) )
            return func_evaluate( qx, qy );
        else{
            return this->FTDecayFunction2DCauchy::evaluate( qx, qy );
        }
    }
    
    double default_evaluate( double qx, double qy ) const  {
        return FTDecayFunction2DCauchy::evaluate( qx, qy );
    }

    PyObject* m_pyobj;

};

void register_FTDecayFunction2DCauchy_class(){

    { //::FTDecayFunction2DCauchy
        typedef bp::class_< FTDecayFunction2DCauchy_wrapper, bp::bases< IFTDecayFunction2D >, std::auto_ptr< FTDecayFunction2DCauchy_wrapper > > FTDecayFunction2DCauchy_exposer_t;
        FTDecayFunction2DCauchy_exposer_t FTDecayFunction2DCauchy_exposer = FTDecayFunction2DCauchy_exposer_t( "FTDecayFunction2DCauchy", "2 dimensional Cauchy decay function in reciprocal space.", bp::init< double, double >(( bp::arg("decay_length_x"), bp::arg("decay_length_y") )) );
        bp::scope FTDecayFunction2DCauchy_scope( FTDecayFunction2DCauchy_exposer );
        { //::FTDecayFunction2DCauchy::clone
        
            typedef ::FTDecayFunction2DCauchy * ( ::FTDecayFunction2DCauchy::*clone_function_type)(  ) const;
            typedef ::FTDecayFunction2DCauchy * ( FTDecayFunction2DCauchy_wrapper::*default_clone_function_type)(  ) const;
            
            FTDecayFunction2DCauchy_exposer.def( 
                "clone"
                , clone_function_type(&::FTDecayFunction2DCauchy::clone)
                , default_clone_function_type(&FTDecayFunction2DCauchy_wrapper::default_clone)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::FTDecayFunction2DCauchy::evaluate
        
            typedef double ( ::FTDecayFunction2DCauchy::*evaluate_function_type)( double,double ) const;
            typedef double ( FTDecayFunction2DCauchy_wrapper::*default_evaluate_function_type)( double,double ) const;
            
            FTDecayFunction2DCauchy_exposer.def( 
                "evaluate"
                , evaluate_function_type(&::FTDecayFunction2DCauchy::evaluate)
                , default_evaluate_function_type(&FTDecayFunction2DCauchy_wrapper::default_evaluate)
                , ( bp::arg("qx"), bp::arg("qy") ) );
        
        }
    }

}