// This file has been generated by Py++.

// BornAgain: simulate and fit scattering at grazing incidence 
//! @brief automatically generated boost::python code for PythonCoreAPI  

#include "Macros.h"
GCC_DIAG_OFF(unused-parameter);
GCC_DIAG_OFF(missing-field-initializers);
#include "boost/python.hpp"
GCC_DIAG_ON(unused-parameter);
GCC_DIAG_ON(missing-field-initializers);
#include "PythonCoreList.h"
#include "RotateZ_3D.pypp.h"

namespace bp = boost::python;

struct RotateZ_3D_wrapper : Geometry::RotateZ_3D, bp::wrapper< Geometry::RotateZ_3D > {

    RotateZ_3D_wrapper(Geometry::RotateZ_3D const & arg )
    : Geometry::RotateZ_3D( arg )
      , bp::wrapper< Geometry::RotateZ_3D >(){
        // copy constructor
        
    }

    RotateZ_3D_wrapper(double a )
    : Geometry::RotateZ_3D( a )
      , bp::wrapper< Geometry::RotateZ_3D >(){
        // constructor
    
    }

    virtual void print( ::std::ostream & ostr ) const  {
        if( bp::override func_print = this->get_override( "print" ) )
            func_print( boost::ref(ostr) );
        else
            this->Geometry::RotateZ_3D::print( boost::ref(ostr) );
    }
    
    
    void default_print( ::std::ostream & ostr ) const  {
        Geometry::RotateZ_3D::print( boost::ref(ostr) );
    }

};

void register_RotateZ_3D_class(){

    { //::Geometry::RotateZ_3D
        typedef bp::class_< RotateZ_3D_wrapper, bp::bases< Geometry::ITransform3D > > RotateZ_3D_exposer_t;
        RotateZ_3D_exposer_t RotateZ_3D_exposer = RotateZ_3D_exposer_t( "RotateZ_3D", bp::init< double >(( bp::arg("a") )) );
        bp::scope RotateZ_3D_scope( RotateZ_3D_exposer );
        { //::Geometry::RotateZ_3D::print
        
            typedef void ( ::Geometry::RotateZ_3D::*print_function_type )( ::std::ostream & ) const;
            typedef void ( RotateZ_3D_wrapper::*default_print_function_type )( ::std::ostream & ) const;
            
            RotateZ_3D_exposer.def( 
                "print"
                , print_function_type(&::Geometry::RotateZ_3D::print)
                , default_print_function_type(&RotateZ_3D_wrapper::default_print)
                , ( bp::arg("ostr") ) );
        
        }
    }

}
