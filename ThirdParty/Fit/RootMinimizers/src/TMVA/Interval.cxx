// @(#)root/tmva $Id$
// Author: Peter Speckmayer

/**********************************************************************************
 * Project: TMVA - a Root-integrated toolkit for multivariate data analysis       *
 * Package: TMVA                                                                  *
 * Class  : TMVA::Interval                                                        *
 * Web    : http://tmva.sourceforge.net                                           *
 *                                                                                *
 * Description:                                                                   *
 *      Implementation (see header for description)                               *
 *                                                                                *
 * Authors (alphabetical):                                                        *
 *      Peter Speckmayer <speckmay@mail.cern.ch>  - CERN, Switzerland             *
 *                                                                                *
 * Copyright (c) 2005:                                                            *
 *      CERN, Switzerland                                                         *
 *      MPI-K Heidelberg, Germany                                                 *
 *                                                                                *
 * Redistribution and use in source and binary forms, with or without             *
 * modification, are permitted according to the terms listed in LICENSE           *
 * (http://tmva.sourceforge.net/LICENSE)                                          *
 *                                                                                *
 * File and Version Information:                                                  *
 **********************************************************************************/

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// Interval                                                                 //
//                                                                          //
// Interval definition, continuous and discrete                             //
//                                                                          //
// Interval(min,max)  : a continous interval [min,max]                      //
// Interval(min,max,n): a "discrete interval" [min,max], i.e the n numbers: //
//          min, min+step, min+2*step,...., min+(n-1)*step, min+n*step=max  //
//   e.g.: Interval(1,5,5)=1,2,3,4,5                                        //
//         Interval(.5,1.,6)= .5, .6., .7, .8, .9, 1.0                      //
//                                                                          //
//  Note: **bin** counting starts from ZERO unlike in ROOT histograms       //
//////////////////////////////////////////////////////////////////////////////
/* Begin_Html
<center><h2>the TMVA::Interval Class</h2></center>

<ul>
   <li> Interval definition, continuous and discrete
   <ul>
         <li>  Interval(min,max)  : a continous interval [min,max]
         <li>  Interval(min,max,n): a "discrete interval" [min,max], i.e the n numbers:<br>
         min, min+step, min+2*step,...., min+(n-1)*step=max <br>
         e.g.: Interval(1,5,5)=1,2,3,4,5                    <br>
         Interval(.5,1.,6)= .5, .6., .7, .8, .9, 1.0        <br>

   </ul>
</ul>
<pre>

    Example:   Interval(.5,1.,6)

             [ min                           max ]
         ------------------------------------------------------------
                |     |     |     |     |     |
               .5    .6    .7    .8    .9    1.0

         bin    0     1     2     3     4     5


</pre>
End_Html */

//#include "TMath.h"
#include "TMVA/TRandom3.h"
//#include "ThreadLocalStorage.h"

#include "TMVA/Interval.h"
//#include "MsgLogger.h"
#include <stdexcept>
#include <iostream>

//ClassImp(TMVA::Interval)

//_______________________________________________________________________
BA_TMVA::Interval::Interval( Double_t min, Double_t max, Int_t nbins ) :
   fMin(min),
   fMax(max),
   fNbins(nbins)
{
   // defines minimum and maximum of an interval
   // when nbins > 0, interval describes a discrete distribution (equally distributed in the interval)
   // when nbins == 0, interval describes a continous interval
   //
   if (fMax - fMin < 0) {
//       Log() << kFATAL << "maximum lower than minimum" << Endl;
       throw std::logic_error("maximum lower than minimum");
   }
   if (nbins < 0) {
//      Log() << kFATAL << "nbins < 0" << Endl;
      throw std::logic_error("nbins < 0");
      return;
   }
   else if (nbins == 1) {
//      Log() << kFATAL << "interval has to have at least 2 bins if discrete" << Endl;
      throw std::logic_error("interval has to have at least 2 bins if discrete");
      return;
   }
}

BA_TMVA::Interval::Interval( const Interval& other ) :
   fMin  ( other.fMin ),
   fMax  ( other.fMax ),
   fNbins( other.fNbins )
{
}

//_______________________________________________________________________
BA_TMVA::Interval::~Interval()
{
   // destructor
}

//_______________________________________________________________________
Double_t BA_TMVA::Interval::GetElement( Int_t bin ) const
{
   // calculates the value of the "number" bin in a discrete interval.
   // Parameters:
   //        Double_t position
   //
   if (fNbins <= 0) {
//      Log() << kFATAL << "GetElement only defined for discrete value Intervals" << Endl;
       throw std::logic_error("GetElement only defined for discrete value Intervals");
      return 0.0;
   }
   else if (bin < 0 || bin >= fNbins) {
//      Log() << kFATAL << "bin " << bin << " out of range: interval *bins* count from 0 to " << fNbins-1  << Endl;
      throw std::logic_error("out of range: interval *bins*");
      return 0.0;
   }
      return fMin + ( (Double_t(bin)/(fNbins-1)) *(fMax - fMin) );
}

//_______________________________________________________________________
Double_t BA_TMVA::Interval::GetStepSize( Int_t iBin )  const
{
   // retuns the step size between the numbers of a "discrete Interval"
   if (fNbins <= 0) {
//      Log() << kFATAL << "GetElement only defined for discrete value Intervals" << Endl;
      throw std::logic_error("GetElement only defined for discrete value Intervals");
   }
   if (iBin<0) {
//      Log() << kFATAL << "You asked for iBin=" << iBin
//            <<" in interval .. and.. sorry, I cannot let this happen.."<<Endl;
       throw std::logic_error("iBin out of range");
   }
   return (fMax-fMin)/(Double_t)(fNbins-1);
}

//_______________________________________________________________________
Double_t BA_TMVA::Interval::GetRndm( BA_ROOT::TRandom3& rnd )  const
{
   // get uniformely distributed number within interval
   return rnd.Rndm()*(fMax - fMin) + fMin;
}

Double_t BA_TMVA::Interval::GetWidth() const
{
   return fMax - fMin;
}
Double_t BA_TMVA::Interval::GetMean()  const
{
   return (fMax + fMin)/2;
}

void BA_TMVA::Interval::Print(std::ostream &os) const
{
   for (Int_t i=0; i<GetNbins(); i++){
      os << "| " << GetElement(i)<<" |" ;
   }
}

//TMVA::MsgLogger& TMVA::Interval::Log() const {
//  TTHREAD_TLS_DECL_ARG(MsgLogger,logger,"Interval");   // message logger
//  return logger;
//}
