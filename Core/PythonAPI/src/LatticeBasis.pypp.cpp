// This file has been generated by Py++.

// BornAgain: simulate and fit scattering at grazing incidence 
//! @brief automatically generated boost::python code for PythonCoreAPI  

#include "Macros.h"
GCC_DIAG_OFF(unused-parameter);
GCC_DIAG_OFF(missing-field-initializers);
#include "boost/python.hpp"
GCC_DIAG_ON(unused-parameter);
GCC_DIAG_ON(missing-field-initializers);
#include "__call_policies.pypp.hpp"
#include "__convenience.pypp.hpp"
#include "PythonCoreList.h"
#include "LatticeBasis.pypp.h"

namespace bp = boost::python;

struct LatticeBasis_wrapper : LatticeBasis, bp::wrapper< LatticeBasis > {

    LatticeBasis_wrapper( )
    : LatticeBasis( )
      , bp::wrapper< LatticeBasis >(){
        // null constructor
    
    }

    virtual bool areParametersChanged(  ) {
        if( bp::override func_areParametersChanged = this->get_override( "areParametersChanged" ) )
            return func_areParametersChanged(  );
        else{
            return this->IParameterized::areParametersChanged(  );
        }
    }
    
    bool default_areParametersChanged(  ) {
        return IParameterized::areParametersChanged( );
    }

    virtual void clearParameterPool(  ) {
        if( bp::override func_clearParameterPool = this->get_override( "clearParameterPool" ) )
            func_clearParameterPool(  );
        else{
            this->IParameterized::clearParameterPool(  );
        }
    }
    
    void default_clearParameterPool(  ) {
        IParameterized::clearParameterPool( );
    }

    virtual ::ParameterPool * createParameterTree(  ) const  {
        if( bp::override func_createParameterTree = this->get_override( "createParameterTree" ) )
            return func_createParameterTree(  );
        else{
            return this->IParameterized::createParameterTree(  );
        }
    }
    
    ::ParameterPool * default_createParameterTree(  ) const  {
        return IParameterized::createParameterTree( );
    }

    virtual ::ICompositeSample * getCompositeSample(  ) {
        if( bp::override func_getCompositeSample = this->get_override( "getCompositeSample" ) )
            return func_getCompositeSample(  );
        else{
            return this->ICompositeSample::getCompositeSample(  );
        }
    }
    
    ::ICompositeSample * default_getCompositeSample(  ) {
        return ICompositeSample::getCompositeSample( );
    }

    virtual ::ICompositeSample const * getCompositeSample(  ) const  {
        if( bp::override func_getCompositeSample = this->get_override( "getCompositeSample" ) )
            return func_getCompositeSample(  );
        else{
            return this->ICompositeSample::getCompositeSample(  );
        }
    }
    
    ::ICompositeSample const * default_getCompositeSample(  ) const  {
        return ICompositeSample::getCompositeSample( );
    }

    virtual ::IMaterial const * getMaterial(  ) const  {
        if( bp::override func_getMaterial = this->get_override( "getMaterial" ) )
            return func_getMaterial(  );
        else{
            return this->Particle::getMaterial(  );
        }
    }
    
    ::IMaterial const * default_getMaterial(  ) const  {
        return Particle::getMaterial( );
    }

    virtual ::complex_t getRefractiveIndex(  ) const  {
        if( bp::override func_getRefractiveIndex = this->get_override( "getRefractiveIndex" ) )
            return func_getRefractiveIndex(  );
        else{
            return this->Particle::getRefractiveIndex(  );
        }
    }
    
    ::complex_t default_getRefractiveIndex(  ) const  {
        return Particle::getRefractiveIndex( );
    }

    virtual ::IFormFactor const * getSimpleFormFactor(  ) const  {
        if( bp::override func_getSimpleFormFactor = this->get_override( "getSimpleFormFactor" ) )
            return func_getSimpleFormFactor(  );
        else{
            return this->Particle::getSimpleFormFactor(  );
        }
    }
    
    ::IFormFactor const * default_getSimpleFormFactor(  ) const  {
        return Particle::getSimpleFormFactor( );
    }

    virtual bool hasDistributedFormFactor(  ) const  {
        if( bp::override func_hasDistributedFormFactor = this->get_override( "hasDistributedFormFactor" ) )
            return func_hasDistributedFormFactor(  );
        else{
            return this->Particle::hasDistributedFormFactor(  );
        }
    }
    
    bool default_hasDistributedFormFactor(  ) const  {
        return Particle::hasDistributedFormFactor( );
    }

    virtual void printParameters(  ) const  {
        if( bp::override func_printParameters = this->get_override( "printParameters" ) )
            func_printParameters(  );
        else{
            this->IParameterized::printParameters(  );
        }
    }
    
    void default_printParameters(  ) const  {
        IParameterized::printParameters( );
    }

    virtual void printSampleTree(  ) {
        if( bp::override func_printSampleTree = this->get_override( "printSampleTree" ) )
            func_printSampleTree(  );
        else{
            this->ISample::printSampleTree(  );
        }
    }
    
    void default_printSampleTree(  ) {
        ISample::printSampleTree( );
    }

    virtual void registerParameter( ::std::string const & name, double * parpointer ) {
        namespace bpl = boost::python;
        if( bpl::override func_registerParameter = this->get_override( "registerParameter" ) ){
            bpl::object py_result = bpl::call<bpl::object>( func_registerParameter.ptr(), name, parpointer );
        }
        else{
            IParameterized::registerParameter( name, parpointer );
        }
    }
    
    static void default_registerParameter( ::IParameterized & inst, ::std::string const & name, long unsigned int parpointer ){
        if( dynamic_cast< LatticeBasis_wrapper * >( boost::addressof( inst ) ) ){
            inst.::IParameterized::registerParameter(name, reinterpret_cast< double * >( parpointer ));
        }
        else{
            inst.registerParameter(name, reinterpret_cast< double * >( parpointer ));
        }
    }

    virtual int setMatchedParametersValue( ::std::string const & wildcards, double value ) {
        if( bp::override func_setMatchedParametersValue = this->get_override( "setMatchedParametersValue" ) )
            return func_setMatchedParametersValue( wildcards, value );
        else{
            return this->IParameterized::setMatchedParametersValue( wildcards, value );
        }
    }
    
    int default_setMatchedParametersValue( ::std::string const & wildcards, double value ) {
        return IParameterized::setMatchedParametersValue( wildcards, value );
    }

    virtual bool setParameterValue( ::std::string const & name, double value ) {
        if( bp::override func_setParameterValue = this->get_override( "setParameterValue" ) )
            return func_setParameterValue( name, value );
        else{
            return this->IParameterized::setParameterValue( name, value );
        }
    }
    
    bool default_setParameterValue( ::std::string const & name, double value ) {
        return IParameterized::setParameterValue( name, value );
    }

    virtual void setParametersAreChanged(  ) {
        if( bp::override func_setParametersAreChanged = this->get_override( "setParametersAreChanged" ) )
            func_setParametersAreChanged(  );
        else{
            this->IParameterized::setParametersAreChanged(  );
        }
    }
    
    void default_setParametersAreChanged(  ) {
        IParameterized::setParametersAreChanged( );
    }

    virtual ::size_t size(  ) const  {
        if( bp::override func_size = this->get_override( "size" ) )
            return func_size(  );
        else{
            return this->ICompositeSample::size(  );
        }
    }
    
    ::size_t default_size(  ) const  {
        return ICompositeSample::size( );
    }

};

void register_LatticeBasis_class(){

    { //::LatticeBasis
        typedef bp::class_< LatticeBasis_wrapper, bp::bases< Particle >, boost::noncopyable > LatticeBasis_exposer_t;
        LatticeBasis_exposer_t LatticeBasis_exposer = LatticeBasis_exposer_t( "LatticeBasis", bp::init< >() );
        bp::scope LatticeBasis_scope( LatticeBasis_exposer );
        { //::LatticeBasis::addParticle
        
            typedef void ( ::LatticeBasis::*addParticle_function_type )( ::Particle const &,::std::vector< Geometry::BasicVector3D<double> > ) ;
            
            LatticeBasis_exposer.def( 
                "addParticle"
                , addParticle_function_type( &::LatticeBasis::addParticle )
                , ( bp::arg("particle"), bp::arg("positions") ) );
        
        }
        { //::IParameterized::areParametersChanged
        
            typedef bool ( ::IParameterized::*areParametersChanged_function_type )(  ) ;
            typedef bool ( LatticeBasis_wrapper::*default_areParametersChanged_function_type )(  ) ;
            
            LatticeBasis_exposer.def( 
                "areParametersChanged"
                , areParametersChanged_function_type(&::IParameterized::areParametersChanged)
                , default_areParametersChanged_function_type(&LatticeBasis_wrapper::default_areParametersChanged) );
        
        }
        { //::IParameterized::clearParameterPool
        
            typedef void ( ::IParameterized::*clearParameterPool_function_type )(  ) ;
            typedef void ( LatticeBasis_wrapper::*default_clearParameterPool_function_type )(  ) ;
            
            LatticeBasis_exposer.def( 
                "clearParameterPool"
                , clearParameterPool_function_type(&::IParameterized::clearParameterPool)
                , default_clearParameterPool_function_type(&LatticeBasis_wrapper::default_clearParameterPool) );
        
        }
        { //::IParameterized::createParameterTree
        
            typedef ::ParameterPool * ( ::IParameterized::*createParameterTree_function_type )(  ) const;
            typedef ::ParameterPool * ( LatticeBasis_wrapper::*default_createParameterTree_function_type )(  ) const;
            
            LatticeBasis_exposer.def( 
                "createParameterTree"
                , createParameterTree_function_type(&::IParameterized::createParameterTree)
                , default_createParameterTree_function_type(&LatticeBasis_wrapper::default_createParameterTree)
                , bp::return_value_policy< bp::manage_new_object >() );
        
        }
        { //::ICompositeSample::getCompositeSample
        
            typedef ::ICompositeSample * ( ::ICompositeSample::*getCompositeSample_function_type )(  ) ;
            typedef ::ICompositeSample * ( LatticeBasis_wrapper::*default_getCompositeSample_function_type )(  ) ;
            
            LatticeBasis_exposer.def( 
                "getCompositeSample"
                , getCompositeSample_function_type(&::ICompositeSample::getCompositeSample)
                , default_getCompositeSample_function_type(&LatticeBasis_wrapper::default_getCompositeSample)
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::ICompositeSample::getCompositeSample
        
            typedef ::ICompositeSample const * ( ::ICompositeSample::*getCompositeSample_function_type )(  ) const;
            typedef ::ICompositeSample const * ( LatticeBasis_wrapper::*default_getCompositeSample_function_type )(  ) const;
            
            LatticeBasis_exposer.def( 
                "getCompositeSample"
                , getCompositeSample_function_type(&::ICompositeSample::getCompositeSample)
                , default_getCompositeSample_function_type(&LatticeBasis_wrapper::default_getCompositeSample)
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::Particle::getMaterial
        
            typedef ::IMaterial const * ( ::Particle::*getMaterial_function_type )(  ) const;
            typedef ::IMaterial const * ( LatticeBasis_wrapper::*default_getMaterial_function_type )(  ) const;
            
            LatticeBasis_exposer.def( 
                "getMaterial"
                , getMaterial_function_type(&::Particle::getMaterial)
                , default_getMaterial_function_type(&LatticeBasis_wrapper::default_getMaterial)
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::Particle::getRefractiveIndex
        
            typedef ::complex_t ( ::Particle::*getRefractiveIndex_function_type )(  ) const;
            typedef ::complex_t ( LatticeBasis_wrapper::*default_getRefractiveIndex_function_type )(  ) const;
            
            LatticeBasis_exposer.def( 
                "getRefractiveIndex"
                , getRefractiveIndex_function_type(&::Particle::getRefractiveIndex)
                , default_getRefractiveIndex_function_type(&LatticeBasis_wrapper::default_getRefractiveIndex) );
        
        }
        { //::Particle::getSimpleFormFactor
        
            typedef ::IFormFactor const * ( ::Particle::*getSimpleFormFactor_function_type )(  ) const;
            typedef ::IFormFactor const * ( LatticeBasis_wrapper::*default_getSimpleFormFactor_function_type )(  ) const;
            
            LatticeBasis_exposer.def( 
                "getSimpleFormFactor"
                , getSimpleFormFactor_function_type(&::Particle::getSimpleFormFactor)
                , default_getSimpleFormFactor_function_type(&LatticeBasis_wrapper::default_getSimpleFormFactor)
                , bp::return_value_policy< bp::reference_existing_object >() );
        
        }
        { //::Particle::hasDistributedFormFactor
        
            typedef bool ( ::Particle::*hasDistributedFormFactor_function_type )(  ) const;
            typedef bool ( LatticeBasis_wrapper::*default_hasDistributedFormFactor_function_type )(  ) const;
            
            LatticeBasis_exposer.def( 
                "hasDistributedFormFactor"
                , hasDistributedFormFactor_function_type(&::Particle::hasDistributedFormFactor)
                , default_hasDistributedFormFactor_function_type(&LatticeBasis_wrapper::default_hasDistributedFormFactor) );
        
        }
        { //::IParameterized::printParameters
        
            typedef void ( ::IParameterized::*printParameters_function_type )(  ) const;
            typedef void ( LatticeBasis_wrapper::*default_printParameters_function_type )(  ) const;
            
            LatticeBasis_exposer.def( 
                "printParameters"
                , printParameters_function_type(&::IParameterized::printParameters)
                , default_printParameters_function_type(&LatticeBasis_wrapper::default_printParameters) );
        
        }
        { //::ISample::printSampleTree
        
            typedef void ( ::ISample::*printSampleTree_function_type )(  ) ;
            typedef void ( LatticeBasis_wrapper::*default_printSampleTree_function_type )(  ) ;
            
            LatticeBasis_exposer.def( 
                "printSampleTree"
                , printSampleTree_function_type(&::ISample::printSampleTree)
                , default_printSampleTree_function_type(&LatticeBasis_wrapper::default_printSampleTree) );
        
        }
        { //::IParameterized::registerParameter
        
            typedef void ( *default_registerParameter_function_type )( ::IParameterized &,::std::string const &,long unsigned int );
            
            LatticeBasis_exposer.def( 
                "registerParameter"
                , default_registerParameter_function_type( &LatticeBasis_wrapper::default_registerParameter )
                , ( bp::arg("inst"), bp::arg("name"), bp::arg("parpointer") ) );
        
        }
        { //::IParameterized::setMatchedParametersValue
        
            typedef int ( ::IParameterized::*setMatchedParametersValue_function_type )( ::std::string const &,double ) ;
            typedef int ( LatticeBasis_wrapper::*default_setMatchedParametersValue_function_type )( ::std::string const &,double ) ;
            
            LatticeBasis_exposer.def( 
                "setMatchedParametersValue"
                , setMatchedParametersValue_function_type(&::IParameterized::setMatchedParametersValue)
                , default_setMatchedParametersValue_function_type(&LatticeBasis_wrapper::default_setMatchedParametersValue)
                , ( bp::arg("wildcards"), bp::arg("value") ) );
        
        }
        { //::IParameterized::setParameterValue
        
            typedef bool ( ::IParameterized::*setParameterValue_function_type )( ::std::string const &,double ) ;
            typedef bool ( LatticeBasis_wrapper::*default_setParameterValue_function_type )( ::std::string const &,double ) ;
            
            LatticeBasis_exposer.def( 
                "setParameterValue"
                , setParameterValue_function_type(&::IParameterized::setParameterValue)
                , default_setParameterValue_function_type(&LatticeBasis_wrapper::default_setParameterValue)
                , ( bp::arg("name"), bp::arg("value") ) );
        
        }
        { //::IParameterized::setParametersAreChanged
        
            typedef void ( ::IParameterized::*setParametersAreChanged_function_type )(  ) ;
            typedef void ( LatticeBasis_wrapper::*default_setParametersAreChanged_function_type )(  ) ;
            
            LatticeBasis_exposer.def( 
                "setParametersAreChanged"
                , setParametersAreChanged_function_type(&::IParameterized::setParametersAreChanged)
                , default_setParametersAreChanged_function_type(&LatticeBasis_wrapper::default_setParametersAreChanged) );
        
        }
        { //::ICompositeSample::size
        
            typedef ::size_t ( ::ICompositeSample::*size_function_type )(  ) const;
            typedef ::size_t ( LatticeBasis_wrapper::*default_size_function_type )(  ) const;
            
            LatticeBasis_exposer.def( 
                "size"
                , size_function_type(&::ICompositeSample::size)
                , default_size_function_type(&LatticeBasis_wrapper::default_size) );
        
        }
    }

}
