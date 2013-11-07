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
#include "kvector_t.pypp.h"

namespace bp = boost::python;

void register_kvector_t_class(){

    { //::Geometry::BasicVector3D< double >
        typedef bp::class_< Geometry::BasicVector3D< double > > kvector_t_exposer_t;
        kvector_t_exposer_t kvector_t_exposer = kvector_t_exposer_t( "kvector_t", bp::init< >() );
        bp::scope kvector_t_scope( kvector_t_exposer );
        kvector_t_exposer.def( bp::init< double, double, double >(( bp::arg("x1"), bp::arg("y1"), bp::arg("z1") )) );
        { //::Geometry::BasicVector3D< double >::mag
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef double ( exported_class_t::*mag_function_type )(  ) const;
            
            kvector_t_exposer.def( 
                "mag"
                , mag_function_type( &::Geometry::BasicVector3D< double >::mag ) );
        
        }
        { //::Geometry::BasicVector3D< double >::mag2
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef double ( exported_class_t::*mag2_function_type )(  ) const;
            
            kvector_t_exposer.def( 
                "mag2"
                , mag2_function_type( &::Geometry::BasicVector3D< double >::mag2 ) );
        
        }
        { //::Geometry::BasicVector3D< double >::magxy
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef double ( exported_class_t::*magxy_function_type )(  ) const;
            
            kvector_t_exposer.def( 
                "magxy"
                , magxy_function_type( &::Geometry::BasicVector3D< double >::magxy ) );
        
        }
        { //::Geometry::BasicVector3D< double >::magxy2
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef double ( exported_class_t::*magxy2_function_type )(  ) const;
            
            kvector_t_exposer.def( 
                "magxy2"
                , magxy2_function_type( &::Geometry::BasicVector3D< double >::magxy2 ) );
        
        }
        kvector_t_exposer.def( bp::self *= bp::other< double >() );
        kvector_t_exposer.def( bp::self += bp::self );
        kvector_t_exposer.def( bp::self -= bp::self );
        kvector_t_exposer.def( bp::self /= bp::other< double >() );
        { //::Geometry::BasicVector3D< double >::operator=
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef ::Geometry::BasicVector3D< double > & ( exported_class_t::*assign_function_type )( ::Geometry::BasicVector3D< double > const & ) ;
            
            kvector_t_exposer.def( 
                "assign"
                , assign_function_type( &::Geometry::BasicVector3D< double >::operator= )
                , ( bp::arg("v") )
                , bp::return_self< >() );
        
        }
        { //::Geometry::BasicVector3D< double >::operator[]
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef double ( exported_class_t::*__getitem___function_type )( int ) const;
            
            kvector_t_exposer.def( 
                "__getitem__"
                , __getitem___function_type( &::Geometry::BasicVector3D< double >::operator[] )
                , ( bp::arg("i") ) );
        
        }
        { //::Geometry::BasicVector3D< double >::operator[]
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef double & ( exported_class_t::*__getitem___function_type )( int ) ;
            
            kvector_t_exposer.def( 
                "__getitem__"
                , __getitem___function_type( &::Geometry::BasicVector3D< double >::operator[] )
                , ( bp::arg("i") )
                , bp::return_value_policy< bp::copy_non_const_reference >() );
        
        }
        { //::Geometry::BasicVector3D< double >::setLambdaAlphaPhi
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef void ( exported_class_t::*setLambdaAlphaPhi_function_type )( double const &,double const &,double const & ) ;
            
            kvector_t_exposer.def( 
                "setLambdaAlphaPhi"
                , setLambdaAlphaPhi_function_type( &::Geometry::BasicVector3D< double >::setLambdaAlphaPhi )
                , ( bp::arg("_lambda"), bp::arg("_alpha"), bp::arg("_phi") ) );
        
        }
        { //::Geometry::BasicVector3D< double >::setX
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef void ( exported_class_t::*setX_function_type )( double const & ) ;
            
            kvector_t_exposer.def( 
                "setX"
                , setX_function_type( &::Geometry::BasicVector3D< double >::setX )
                , ( bp::arg("a") ) );
        
        }
        { //::Geometry::BasicVector3D< double >::setXYZ
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef void ( exported_class_t::*setXYZ_function_type )( double const &,double const &,double const & ) ;
            
            kvector_t_exposer.def( 
                "setXYZ"
                , setXYZ_function_type( &::Geometry::BasicVector3D< double >::setXYZ )
                , ( bp::arg("x1"), bp::arg("y1"), bp::arg("z1") ) );
        
        }
        { //::Geometry::BasicVector3D< double >::setY
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef void ( exported_class_t::*setY_function_type )( double const & ) ;
            
            kvector_t_exposer.def( 
                "setY"
                , setY_function_type( &::Geometry::BasicVector3D< double >::setY )
                , ( bp::arg("a") ) );
        
        }
        { //::Geometry::BasicVector3D< double >::setZ
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef void ( exported_class_t::*setZ_function_type )( double const & ) ;
            
            kvector_t_exposer.def( 
                "setZ"
                , setZ_function_type( &::Geometry::BasicVector3D< double >::setZ )
                , ( bp::arg("a") ) );
        
        }
        { //::Geometry::BasicVector3D< double >::x
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef double ( exported_class_t::*x_function_type )(  ) const;
            
            kvector_t_exposer.def( 
                "x"
                , x_function_type( &::Geometry::BasicVector3D< double >::x ) );
        
        }
        { //::Geometry::BasicVector3D< double >::y
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef double ( exported_class_t::*y_function_type )(  ) const;
            
            kvector_t_exposer.def( 
                "y"
                , y_function_type( &::Geometry::BasicVector3D< double >::y ) );
        
        }
        { //::Geometry::BasicVector3D< double >::z
        
            typedef Geometry::BasicVector3D< double > exported_class_t;
            typedef double ( exported_class_t::*z_function_type )(  ) const;
            
            kvector_t_exposer.def( 
                "z"
                , z_function_type( &::Geometry::BasicVector3D< double >::z ) );
        
        }
        kvector_t_exposer.def( bp::self - bp::self );
        kvector_t_exposer.def( bp::self + bp::self );
        kvector_t_exposer.def( bp::other< double >() * bp::self );
        kvector_t_exposer.def( bp::self * bp::other< double >() );
        kvector_t_exposer.def( +bp::self );
        kvector_t_exposer.def( -bp::self );
        kvector_t_exposer.def( bp::self / bp::other< double >() );
        kvector_t_exposer.def( bp::self_ns::str( bp::self ) );
    }

}
