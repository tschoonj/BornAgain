%extend BasicVector3D<double> {
    BasicVector3D<double> __add__(const BasicVector3D<double>& rhs) const {
        return *($self) + rhs; }
    BasicVector3D<double> __mul__(double c) const {
        return c * *($self); }
    BasicVector3D<double> __rmul__(double c) const {
        return *($self) * c; }
    BasicVector3D<double> __neg__() const {
        return - *($self); }
};

%extend OutputData<double> {
    double __getitem__(unsigned int i) { return (*($self))[i]; }
    double __setitem__(unsigned int i, double value)
    {
        (*($self))[i] = value;
        return (*($self))[i];
    }
};

%extend FixedBinAxis {
    double __getitem__(unsigned int i) { return (*($self))[i]; }
};

%extend VariableBinAxis {
    double __getitem__(unsigned int i) { return (*($self))[i]; }
};

%extend IMultiLayerBuilder {
    virtual RealParameter* registerParameter(const std::string& name, int64_t parpointer) {
        return &((*($self)).registerParameter(name, (double*)parpointer)); }

    virtual void setParameterValue(const std::string& name, double value) {
        dynamic_cast<IParameterized*>($self)->setParameterValue(name, value); }

    static bool isPythonBuilder() {
        return true; }
};

// necessary to export this since Python does not support dynamic casting
%extend Histogram2D {
    static Histogram2D* dynamicCast(IHistogram* pHistogram) {
        return dynamic_cast<Histogram2D*>(pHistogram); }
};

// necessary to export this since Python does not support dynamic casting
%extend Histogram1D {
    static Histogram1D* dynamicCast(IHistogram* pHistogram) {
        return dynamic_cast<Histogram1D*>(pHistogram); }
};

// needed to prevent ownership problems with passed IMultiLayerBuilder
%rename(setSampleBuilderCpp) Simulation::setSampleBuilder;
%extend Simulation {
    %pythoncode %{
         def setSampleBuilder(self, ptr):
             self.samplebuilder = ptr
             self.setSampleBuilderCpp(ptr)
    %}
 };

%rename(setSampleBuilderCpp) SpecularSimulation::setSampleBuilder;
%extend SpecularSimulation {
    %pythoncode %{
         def setSampleBuilder(self, ptr):
             self.samplebuilder = ptr
             self.setSampleBuilderCpp(ptr)
    %}
 };

// force swig to use move ctor instead of copy ctor
%typemap(out) SlicedParticle %{
    $result = SWIG_NewPointerObj(new $1_ltype(std::move($1)), $&1_descriptor, SWIG_POINTER_OWN);
  %}

// --- ParameterPool accessors -------------------------------------------------------------------

%pythoncode %{
class ParameterPoolIterator(object):

    def __init__(self, pool):
        self.pool = pool
        self.index = -1

    def __iter__(self):
        return self

    def next(self):
        self.index += 1
        if self.index < self.pool.size():
            return self.pool[self.index]
        else:
            raise StopIteration

    def __next__(self):
        return self.next()
%}


%extend ParameterPool {
    const RealParameter* __getitem__(size_t index) const
    {
        return (*($self))[index];
    }

%pythoncode {
    def __iter__(self):
        return ParameterPoolIterator(self)
}
};


