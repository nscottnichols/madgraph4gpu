// Copyright (C) 2010 The MadGraph5_aMC@NLO development team and contributors.
// Created by: J. Alwall (Oct 2010) for the MG5aMC CPP backend.
//==========================================================================
// Copyright (C) 2020-2023 CERN and UCLouvain.
// Licensed under the GNU Lesser General Public License (version 3 or later).
// Modified by: S. Roiser (Feb 2020) for the MG5aMC CUDACPP plugin.
// Further modified by: S. Hageboeck, O. Mattelaer, S. Roiser, J. Teig, A. Valassi, Z. Wettersten (2020-2023) for the MG5aMC CUDACPP plugin.
//==========================================================================
// This file has been automatically generated for CUDA/C++ standalone by
// MadGraph5_aMC@NLO v. 3.5.3_lo_vect, 2023-12-23
// By the MadGraph5_aMC@NLO Development Team
// Visit launchpad.net/madgraph5 and amcatnlo.web.cern.ch
//==========================================================================

#include "CPPProcess.h"

#include "mgOnGpuConfig.h"

#include "HelAmps_sm.h"
#include "MemoryAccessAmplitudes.h"
#include "MemoryAccessCouplings.h"
#include "MemoryAccessCouplingsFixed.h"
#include "MemoryAccessGs.h"
#include "MemoryAccessMatrixElements.h"
#include "MemoryAccessMomenta.h"
#include "MemoryAccessWavefunctions.h"

#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
#include "MemoryAccessDenominators.h"
#include "MemoryAccessNumerators.h"
#include "coloramps.h"
#endif

#include <algorithm>
#include <array>
#include <cfenv>  // for feenableexcept, fegetexcept and FE_XXX
#include <cfloat> // for FLT_MIN
#include <cstring>
#include <iomanip>
#include <iostream>
#include <memory>

// Test ncu metrics for CUDA thread divergence
#undef MGONGPU_TEST_DIVERGENCE
//#define MGONGPU_TEST_DIVERGENCE 1

//--------------------------------------------------------------------------

// Enable FPE traps (see #701, #733, #831 - except on MacOS where feenableexcept is not defined #730)
// [NB1: Fortran default is -ffpe-trap=none, i.e. FPE traps are not enabled, https://gcc.gnu.org/onlinedocs/gfortran/Debugging-Options.html]
// [NB2: Fortran default is -ffpe-summary=invalid,zero,overflow,underflow,denormal, i.e. warn at the end on STOP]
inline void
fpeEnable()
{
  static bool first = true; // FIXME: quick and dirty hack to do this only once (can be removed when separate C++/CUDA builds are implemented)
  if( !first ) return;
  first = false;
#ifndef __APPLE__ // on MacOS feenableexcept is not defined #730
  //int fpes = fegetexcept();
  //std::cout << "fpeEnable: analyse fegetexcept()=" << fpes << std::endl;
  //std::cout << "fpeEnable:     FE_DIVBYZERO is" << ( ( fpes & FE_DIVBYZERO ) ? " " : " NOT " ) << "enabled" << std::endl;
  //std::cout << "fpeEnable:     FE_INEXACT is" << ( ( fpes & FE_INEXACT ) ? " " : " NOT " ) << "enabled" << std::endl;
  //std::cout << "fpeEnable:     FE_INVALID is" << ( ( fpes & FE_INVALID ) ? " " : " NOT " ) << "enabled" << std::endl;
  //std::cout << "fpeEnable:     FE_OVERFLOW is" << ( ( fpes & FE_OVERFLOW ) ? " " : " NOT " ) << "enabled" << std::endl;
  //std::cout << "fpeEnable:     FE_UNDERFLOW is" << ( ( fpes & FE_UNDERFLOW ) ? " " : " NOT " ) << "enabled" << std::endl;
  ////const char* enableFPEc = getenv( "CUDACPP_RUNTIME_ENABLEFPE" );
  ////const bool enableFPE = ( enableFPEc != 0 ) && ( std::string( enableFPEc ) != "" );
  const bool enableFPE = true;
  if( enableFPE )
  {
    ////std::cout << "WARNING! CUDACPP_RUNTIME_ENABLEFPE is set: enable Floating Point Exceptions" << std::endl;
    std::cerr << "INFO: The following Floating Point Exceptions will cause SIGFPE program aborts: FE_DIVBYZERO, FE_INVALID, FE_OVERFLOW" << std::endl;
    ////feenableexcept( FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW | FE_UNDERFLOW ); // old strategy #701
    feenableexcept( FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW ); // new strategy #831
    //fpes = fegetexcept();
    //std::cout << "fpeEnable: analyse fegetexcept()=" << fpes << std::endl;
    //std::cout << "fpeEnable:     FE_DIVBYZERO is" << ( ( fpes & FE_DIVBYZERO ) ? " " : " NOT " ) << "enabled" << std::endl;
    //std::cout << "fpeEnable:     FE_INEXACT is" << ( ( fpes & FE_INEXACT ) ? " " : " NOT " ) << "enabled" << std::endl;
    //std::cout << "fpeEnable:     FE_INVALID is" << ( ( fpes & FE_INVALID ) ? " " : " NOT " ) << "enabled" << std::endl;
    //std::cout << "fpeEnable:     FE_OVERFLOW is" << ( ( fpes & FE_OVERFLOW ) ? " " : " NOT " ) << "enabled" << std::endl;
    //std::cout << "fpeEnable:     FE_UNDERFLOW is" << ( ( fpes & FE_UNDERFLOW ) ? " " : " NOT " ) << "enabled" << std::endl;
  }
  else
  {
    ////std::cout << "DEBUG: CUDACPP_RUNTIME_ENABLEFPE is NOT set, do not enable Floating Point Exceptions" << std::endl;
    //std::cout << "INFO: Do not enable SIGFPE traps for Floating Point Exceptions" << std::endl;
  }
#else
  //std::cout << "INFO: Keep default SIGFPE settings because feenableexcept is not available on MacOS" << std::endl;
#endif
}

//==========================================================================
// Class member functions for calculating the matrix elements for
// Process: g g > t t~ g g WEIGHTED<=4 @1

#ifdef MGONGPUCPP_GPUIMPL
namespace mg5amcGpu
#else
namespace mg5amcCpu
#endif
{
  constexpr int nw6 = CPPProcess::nw6;     // dimensions of each wavefunction (HELAS KEK 91-11): e.g. 6 for e+ e- -> mu+ mu- (fermions and vectors)
  constexpr int npar = CPPProcess::npar;   // #particles in total (external = initial + final): e.g. 4 for e+ e- -> mu+ mu-
  constexpr int ncomb = CPPProcess::ncomb; // #helicity combinations: e.g. 16 for e+ e- -> mu+ mu- (2**4 = fermion spin up/down ** npar)

  // [NB: I am currently unable to get the right value of nwf in CPPProcess.h - will hardcode it in CPPProcess.cc instead (#644)]
  //using CPPProcess::nwf; // #wavefunctions = #external (npar) + #internal: e.g. 5 for e+ e- -> mu+ mu- (1 internal is gamma or Z)

  using Parameters_sm_dependentCouplings::ndcoup;   // #couplings that vary event by event (depend on running alphas QCD)
  using Parameters_sm_independentCouplings::nicoup; // #couplings that are fixed for all events (do not depend on running alphas QCD)

  // The number of colors
  constexpr int ncolor = 24;

  // The number of SIMD vectors of events processed by calculate_wavefunction
#if defined MGONGPU_CPPSIMD and defined MGONGPU_FPTYPE_DOUBLE and defined MGONGPU_FPTYPE2_FLOAT
  constexpr int nParity = 2;
#else
  constexpr int nParity = 1;
#endif

  // Physics parameters (masses, coupling, etc...)
  // For CUDA performance, hardcoded constexpr's would be better: fewer registers and a tiny throughput increase
  // However, physics parameters are user-defined through card files: use CUDA constant memory instead (issue #39)
  // [NB if hardcoded parameters are used, it's better to define them here to avoid silent shadowing (issue #263)]
  constexpr int nIPD = 2; // SM independent parameters used in this CPPProcess.cc (FIXME? rename as sm_IndepParam?)
  // Note: in the Python code generator, nIPD == nparam, while nIPC <= nicoup, because (see #823)
  // nIPC may vary from one P*/CPPProcess.cc to another, while nicoup is defined in src/Param.h and is common to all P*
  constexpr int nIPC = 0; // SM independent couplings used in this CPPProcess.cc (FIXME? rename as sm_IndepCoupl?)
  static_assert( nIPC <= nicoup );
  static_assert( nIPD >= 0 ); // Hack to avoid build warnings when nIPD==0 is unused
  static_assert( nIPC >= 0 ); // Hack to avoid build warnings when nIPC==0 is unused
#ifdef MGONGPU_HARDCODE_PARAM
  __device__ const fptype cIPD[nIPD] = { (fptype)Parameters_sm::mdl_MT, (fptype)Parameters_sm::mdl_WT };
  __device__ const fptype* cIPC = nullptr; // unused as nIPC=0
#else
#ifdef MGONGPUCPP_GPUIMPL
  __device__ __constant__ fptype cIPD[nIPD];
  __device__ __constant__ fptype* cIPC = nullptr; // unused as nIPC=0
#else
  static fptype cIPD[nIPD];
  static fptype* cIPC = nullptr; // unused as nIPC=0
#endif
#endif

  // AV Jan 2024 (PR #625): this ugly #define was the only way I found to avoid creating arrays[nBsm] in CPPProcess.cc if nBsm is 0
  // The problem is that nBsm is determined when generating Parameters.h, which happens after CPPProcess.cc has already been generated
  // For simplicity, keep this code hardcoded also for SM processes (a nullptr is needed as in the case nBsm == 0)
#ifdef MGONGPUCPP_NBSMINDEPPARAM_GT_0
#ifdef MGONGPU_HARDCODE_PARAM
  __device__ const double* bsmIndepParam = Parameters_sm::mdl_bsmIndepParam;
#else
#ifdef MGONGPUCPP_GPUIMPL
  __device__ __constant__ double bsmIndepParam[Parameters_sm::nBsmIndepParam];
#else
  static double bsmIndepParam[Parameters_sm::nBsmIndepParam];
#endif
#endif
#else
#ifdef MGONGPU_HARDCODE_PARAM
  __device__ const double* bsmIndepParam = nullptr;
#else
#ifdef MGONGPUCPP_GPUIMPL
  __device__ __constant__ double* bsmIndepParam = nullptr;
#else
  static double* bsmIndepParam = nullptr;
#endif
#endif
#endif

  // Helicity combinations (and filtering of "good" helicity combinations)
#ifdef MGONGPUCPP_GPUIMPL
  __device__ __constant__ short cHel[ncomb][npar];
  __device__ __constant__ int cNGoodHel;
  __device__ __constant__ int cGoodHel[ncomb];
#else
  static short cHel[ncomb][npar];
  static int cNGoodHel;
  static int cGoodHel[ncomb];
#endif

  //--------------------------------------------------------------------------

  // Evaluate |M|^2 for each subprocess
  // NB: calculate_wavefunctions ADDS |M|^2 for a given ihel to the running sum of |M|^2 over helicities for the given event(s)
  // (similarly, it also ADDS the numerator and denominator for a given ihel to their running sums over helicities)
  // In CUDA, this device function computes the ME for a single event
  // In C++, this function computes the ME for a single event "page" or SIMD vector (or for two in "mixed" precision mode, nParity=2)
  __device__ INLINE void /* clang-format off */
  calculate_wavefunctions( int ihel,
                           const fptype* allmomenta,      // input: momenta[nevt*npar*4]
                           const fptype* allcouplings,    // input: couplings[nevt*ndcoup*2]
                           fptype* allMEs,                // output: allMEs[nevt], |M|^2 running_sum_over_helicities
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
                           const unsigned int channelId,  // input: multichannel channel id (1 to #diagrams); 0 to disable channel enhancement
                           fptype* allNumerators,         // output: multichannel numerators[nevt], running_sum_over_helicities
                           fptype* allDenominators,       // output: multichannel denominators[nevt], running_sum_over_helicities
#endif
                           fptype_sv* jamp2_sv            // output: jamp2[nParity][ncolor][neppV] for color choice (nullptr if disabled)
#ifndef MGONGPUCPP_GPUIMPL
                           , const int ievt00             // input: first event number in current C++ event page (for CUDA, ievt depends on threadid)
#endif
                           )
  //ALWAYS_INLINE // attributes are not permitted in a function definition
  {
#ifdef MGONGPUCPP_GPUIMPL
    using namespace mg5amcGpu;
    using M_ACCESS = DeviceAccessMomenta;         // non-trivial access: buffer includes all events
    using E_ACCESS = DeviceAccessMatrixElements;  // non-trivial access: buffer includes all events
    using W_ACCESS = DeviceAccessWavefunctions;   // TRIVIAL ACCESS (no kernel splitting yet): buffer for one event
    using A_ACCESS = DeviceAccessAmplitudes;      // TRIVIAL ACCESS (no kernel splitting yet): buffer for one event
    using CD_ACCESS = DeviceAccessCouplings;      // non-trivial access (dependent couplings): buffer includes all events
    using CI_ACCESS = DeviceAccessCouplingsFixed; // TRIVIAL access (independent couplings): buffer for one event
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
    using NUM_ACCESS = DeviceAccessNumerators;    // non-trivial access: buffer includes all events
    using DEN_ACCESS = DeviceAccessDenominators;  // non-trivial access: buffer includes all events
#endif
#else
    using namespace mg5amcCpu;
    using M_ACCESS = HostAccessMomenta;         // non-trivial access: buffer includes all events
    using E_ACCESS = HostAccessMatrixElements;  // non-trivial access: buffer includes all events
    using W_ACCESS = HostAccessWavefunctions;   // TRIVIAL ACCESS (no kernel splitting yet): buffer for one event
    using A_ACCESS = HostAccessAmplitudes;      // TRIVIAL ACCESS (no kernel splitting yet): buffer for one event
    using CD_ACCESS = HostAccessCouplings;      // non-trivial access (dependent couplings): buffer includes all events
    using CI_ACCESS = HostAccessCouplingsFixed; // TRIVIAL access (independent couplings): buffer for one event
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
    using NUM_ACCESS = HostAccessNumerators;    // non-trivial access: buffer includes all events
    using DEN_ACCESS = HostAccessDenominators;  // non-trivial access: buffer includes all events
#endif
#endif /* clang-format on */
    mgDebug( 0, __FUNCTION__ );
    //bool debug = true;
#ifndef MGONGPUCPP_GPUIMPL
    //debug = ( ievt00 >= 64 && ievt00 < 80 && ihel == 3 ); // example: debug #831
    //if( debug ) printf( "calculate_wavefunctions: ievt00=%d\n", ievt00 );
#endif
    //if( debug ) printf( "calculate_wavefunctions: ihel=%d\n", ihel );

    // The variable nwf (which is specific to each P1 subdirectory, #644) is only used here
    // It is hardcoded here because various attempts to hardcode it in CPPProcess.h at generation time gave the wrong result...
    static const int nwf = 26; // #wavefunctions = #external (npar) + #internal: e.g. 5 for e+ e- -> mu+ mu- (1 internal is gamma or Z)

    // Local TEMPORARY variables for a subset of Feynman diagrams in the given CUDA event (ievt) or C++ event page (ipagV)
    // [NB these variables are reused several times (and re-initialised each time) within the same event or event page]
    // ** NB: in other words, amplitudes and wavefunctions still have TRIVIAL ACCESS: there is currently no need
    // ** NB: to have large memory structurs for wavefunctions/amplitudes in all events (no kernel splitting yet)!
    //MemoryBufferWavefunctions w_buffer[nwf]{ neppV };
    cxtype_sv w_sv[nwf][nw6]; // particle wavefunctions within Feynman diagrams (nw6 is often 6, the dimension of spin 1/2 or spin 1 particles)
    cxtype_sv amp_sv[1];      // invariant amplitude for one given Feynman diagram

    // Proof of concept for using fptype* in the interface
    fptype* w_fp[nwf];
    for( int iwf = 0; iwf < nwf; iwf++ ) w_fp[iwf] = reinterpret_cast<fptype*>( w_sv[iwf] );
    fptype* amp_fp;
    amp_fp = reinterpret_cast<fptype*>( amp_sv );

    // Local variables for the given CUDA event (ievt) or C++ event page (ipagV)
    // [jamp: sum (for one event or event page) of the invariant amplitudes for all Feynman diagrams in a given color combination]
    cxtype_sv jamp_sv[ncolor] = {}; // all zeros (NB: vector cxtype_v IS initialized to 0, but scalar cxtype is NOT, if "= {}" is missing!)

    // === Calculate wavefunctions and amplitudes for all diagrams in all processes         ===
    // === (for one event in CUDA, for one - or two in mixed mode - SIMD event pages in C++ ===
#if defined MGONGPU_CPPSIMD and defined MGONGPU_FPTYPE_DOUBLE and defined MGONGPU_FPTYPE2_FLOAT
    // Mixed fptypes #537: float for color algebra and double elsewhere
    // Delay color algebra and ME updates (only on even pages)
    cxtype_sv jamp_sv_previous[ncolor] = {};
    fptype* MEs_previous = 0;
#endif
    for( int iParity = 0; iParity < nParity; ++iParity )
    { // START LOOP ON IPARITY
#ifndef MGONGPUCPP_GPUIMPL
      const int ievt0 = ievt00 + iParity * neppV;
#endif
      //constexpr size_t nxcoup = ndcoup + nicoup; // both dependent and independent couplings (BUG #823)
      constexpr size_t nxcoup = ndcoup + nIPC; // both dependent and independent couplings (FIX #823)
      const fptype* allCOUPs[nxcoup];
#ifdef __CUDACC__
#pragma nv_diagnostic push
#pragma nv_diag_suppress 186 // e.g. <<warning #186-D: pointless comparison of unsigned integer with zero>>
#endif
      for( size_t idcoup = 0; idcoup < ndcoup; idcoup++ )
        allCOUPs[idcoup] = CD_ACCESS::idcoupAccessBufferConst( allcouplings, idcoup ); // dependent couplings, vary event-by-event
      //for( size_t iicoup = 0; iicoup < nicoup; iicoup++ )                             // BUG #823
      for( size_t iicoup = 0; iicoup < nIPC; iicoup++ )                                 // FIX #823
        allCOUPs[ndcoup + iicoup] = CI_ACCESS::iicoupAccessBufferConst( cIPC, iicoup ); // independent couplings, fixed for all events
#ifdef MGONGPUCPP_GPUIMPL
#ifdef __CUDACC__
#pragma nv_diagnostic pop
#endif
      // CUDA kernels take input/output buffers with momenta/MEs for all events
      const fptype* momenta = allmomenta;
      const fptype* COUPs[nxcoup];
      for( size_t ixcoup = 0; ixcoup < nxcoup; ixcoup++ ) COUPs[ixcoup] = allCOUPs[ixcoup];
      fptype* MEs = allMEs;
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      fptype* numerators = allNumerators;
      fptype* denominators = allDenominators;
#endif
#else
      // C++ kernels take input/output buffers with momenta/MEs for one specific event (the first in the current event page)
      const fptype* momenta = M_ACCESS::ieventAccessRecordConst( allmomenta, ievt0 );
      const fptype* COUPs[nxcoup];
      for( size_t idcoup = 0; idcoup < ndcoup; idcoup++ )
        COUPs[idcoup] = CD_ACCESS::ieventAccessRecordConst( allCOUPs[idcoup], ievt0 ); // dependent couplings, vary event-by-event
      //for( size_t iicoup = 0; iicoup < nicoup; iicoup++ ) // BUG #823
      for( size_t iicoup = 0; iicoup < nIPC; iicoup++ )     // FIX #823
        COUPs[ndcoup + iicoup] = allCOUPs[ndcoup + iicoup]; // independent couplings, fixed for all events
      fptype* MEs = E_ACCESS::ieventAccessRecord( allMEs, ievt0 );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      fptype* numerators = NUM_ACCESS::ieventAccessRecord( allNumerators, ievt0 );
      fptype* denominators = DEN_ACCESS::ieventAccessRecord( allDenominators, ievt0 );
#endif
#endif

      // Reset color flows (reset jamp_sv) at the beginning of a new event or event page
      for( int i = 0; i < ncolor; i++ ) { jamp_sv[i] = cxzero_sv(); }

#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Numerators and denominators for the current event (CUDA) or SIMD event page (C++)
      fptype_sv& numerators_sv = NUM_ACCESS::kernelAccess( numerators );
      fptype_sv& denominators_sv = DEN_ACCESS::kernelAccess( denominators );
#endif

      // *** DIAGRAM 1 OF 123 ***

      // Wavefunction(s) for diagram number 1
      vxxxxx<M_ACCESS, W_ACCESS>( momenta, 0., cHel[ihel][0], -1, w_fp[0], 0 );

      vxxxxx<M_ACCESS, W_ACCESS>( momenta, 0., cHel[ihel][1], -1, w_fp[1], 1 );

      oxxxxx<M_ACCESS, W_ACCESS>( momenta, cIPD[0], cHel[ihel][2], +1, w_fp[2], 2 );

      ixxxxx<M_ACCESS, W_ACCESS>( momenta, cIPD[0], cHel[ihel][3], -1, w_fp[3], 3 );

      vxxxxx<M_ACCESS, W_ACCESS>( momenta, 0., cHel[ihel][4], +1, w_fp[4], 4 );

      vxxxxx<M_ACCESS, W_ACCESS>( momenta, 0., cHel[ihel][5], +1, w_fp[5], 5 );

      VVV1P0_1<W_ACCESS, CD_ACCESS>( w_fp[0], w_fp[1], COUPs[0], 1.0, 0., 0., w_fp[6] );
      FFV1P0_3<W_ACCESS, CD_ACCESS>( w_fp[3], w_fp[2], COUPs[1], 1.0, 0., 0., w_fp[7] );

      // Amplitude(s) for diagram number 1
      VVVV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[6], w_fp[7], w_fp[4], w_fp[5], COUPs[2], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[0] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[1] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[6] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[7] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[16] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[17] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[22] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[23] -= cxtype( 0, 1 ) * amp_sv[0];
      VVVV3_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[6], w_fp[7], w_fp[4], w_fp[5], COUPs[2], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[0] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[6] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[12] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[14] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[18] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[20] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[22] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[23] -= cxtype( 0, 1 ) * amp_sv[0];
      VVVV4_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[6], w_fp[7], w_fp[4], w_fp[5], COUPs[2], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[1] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[7] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[12] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[14] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[16] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[17] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[18] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[20] += cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 2 OF 123 ***

      // Wavefunction(s) for diagram number 2
      VVV1P0_1<W_ACCESS, CD_ACCESS>( w_fp[6], w_fp[4], COUPs[0], 1.0, 0., 0., w_fp[8] );

      // Amplitude(s) for diagram number 2
      VVV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[7], w_fp[5], w_fp[8], COUPs[0], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[0] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[6] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[12] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[14] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[18] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[20] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[22] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[23] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 3 OF 123 ***

      // Wavefunction(s) for diagram number 3
      VVV1P0_1<W_ACCESS, CD_ACCESS>( w_fp[6], w_fp[5], COUPs[0], 1.0, 0., 0., w_fp[9] );

      // Amplitude(s) for diagram number 3
      VVV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[7], w_fp[4], w_fp[9], COUPs[0], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[1] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[7] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[12] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[14] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[16] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[17] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[18] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[20] += cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 4 OF 123 ***

      // Wavefunction(s) for diagram number 4
      VVV1P0_1<W_ACCESS, CD_ACCESS>( w_fp[4], w_fp[5], COUPs[0], 1.0, 0., 0., w_fp[10] );

      // Amplitude(s) for diagram number 4
      VVV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[6], w_fp[7], w_fp[10], COUPs[0], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[0] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[1] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[6] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[7] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[16] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[17] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[22] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[23] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 5 OF 123 ***

      // Wavefunction(s) for diagram number 5
      FFV1_1<W_ACCESS, CD_ACCESS>( w_fp[2], w_fp[4], COUPs[1], 1.0, cIPD[0], cIPD[1], w_fp[11] );
      FFV1_2<W_ACCESS, CD_ACCESS>( w_fp[3], w_fp[6], COUPs[1], 1.0, cIPD[0], cIPD[1], w_fp[12] );

      // Amplitude(s) for diagram number 5
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[12], w_fp[11], w_fp[5], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[16] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[17] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 6 OF 123 ***

      // Wavefunction(s) for diagram number 6
      // (none)

      // Amplitude(s) for diagram number 6
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[3], w_fp[11], w_fp[9], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[12] += amp_sv[0];
      jamp_sv[14] -= amp_sv[0];
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[17] += amp_sv[0];

      // *** DIAGRAM 7 OF 123 ***

      // Wavefunction(s) for diagram number 7
      FFV1_2<W_ACCESS, CD_ACCESS>( w_fp[3], w_fp[5], COUPs[1], 1.0, cIPD[0], cIPD[1], w_fp[13] );

      // Amplitude(s) for diagram number 7
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[13], w_fp[11], w_fp[6], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[12] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[14] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 8 OF 123 ***

      // Wavefunction(s) for diagram number 8
      FFV1_1<W_ACCESS, CD_ACCESS>( w_fp[2], w_fp[5], COUPs[1], 1.0, cIPD[0], cIPD[1], w_fp[14] );

      // Amplitude(s) for diagram number 8
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[12], w_fp[14], w_fp[4], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[22] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[23] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 9 OF 123 ***

      // Wavefunction(s) for diagram number 9
      // (none)

      // Amplitude(s) for diagram number 9
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[3], w_fp[14], w_fp[8], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[18] += amp_sv[0];
      jamp_sv[20] -= amp_sv[0];
      jamp_sv[22] -= amp_sv[0];
      jamp_sv[23] += amp_sv[0];

      // *** DIAGRAM 10 OF 123 ***

      // Wavefunction(s) for diagram number 10
      FFV1_2<W_ACCESS, CD_ACCESS>( w_fp[3], w_fp[4], COUPs[1], 1.0, cIPD[0], cIPD[1], w_fp[15] );

      // Amplitude(s) for diagram number 10
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[15], w_fp[14], w_fp[6], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[18] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[20] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 11 OF 123 ***

      // Wavefunction(s) for diagram number 11
      FFV1_1<W_ACCESS, CD_ACCESS>( w_fp[2], w_fp[6], COUPs[1], 1.0, cIPD[0], cIPD[1], w_fp[16] );

      // Amplitude(s) for diagram number 11
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[15], w_fp[16], w_fp[5], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[1] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[7] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 12 OF 123 ***

      // Wavefunction(s) for diagram number 12
      // (none)

      // Amplitude(s) for diagram number 12
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[15], w_fp[2], w_fp[9], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[1] += amp_sv[0];
      jamp_sv[7] -= amp_sv[0];
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[20] += amp_sv[0];

      // *** DIAGRAM 13 OF 123 ***

      // Wavefunction(s) for diagram number 13
      // (none)

      // Amplitude(s) for diagram number 13
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[13], w_fp[16], w_fp[4], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[0] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[6] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 14 OF 123 ***

      // Wavefunction(s) for diagram number 14
      // (none)

      // Amplitude(s) for diagram number 14
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[13], w_fp[2], w_fp[8], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[0] += amp_sv[0];
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[14] += amp_sv[0];

      // *** DIAGRAM 15 OF 123 ***

      // Wavefunction(s) for diagram number 15
      // (none)

      // Amplitude(s) for diagram number 15
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[3], w_fp[16], w_fp[10], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[0] += amp_sv[0];
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[7] += amp_sv[0];

      // *** DIAGRAM 16 OF 123 ***

      // Wavefunction(s) for diagram number 16
      // (none)

      // Amplitude(s) for diagram number 16
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[12], w_fp[2], w_fp[10], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[16] += amp_sv[0];
      jamp_sv[17] -= amp_sv[0];
      jamp_sv[22] -= amp_sv[0];
      jamp_sv[23] += amp_sv[0];

      // *** DIAGRAM 17 OF 123 ***

      // Wavefunction(s) for diagram number 17
      FFV1_1<W_ACCESS, CD_ACCESS>( w_fp[2], w_fp[0], COUPs[1], 1.0, cIPD[0], cIPD[1], w_fp[12] );
      FFV1_2<W_ACCESS, CD_ACCESS>( w_fp[3], w_fp[1], COUPs[1], 1.0, cIPD[0], cIPD[1], w_fp[16] );
      FFV1_1<W_ACCESS, CD_ACCESS>( w_fp[12], w_fp[4], COUPs[1], 1.0, cIPD[0], cIPD[1], w_fp[8] );

      // Amplitude(s) for diagram number 17
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[16], w_fp[8], w_fp[5], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[3] -= amp_sv[0];

      // *** DIAGRAM 18 OF 123 ***

      // Wavefunction(s) for diagram number 18
      FFV1_1<W_ACCESS, CD_ACCESS>( w_fp[12], w_fp[5], COUPs[1], 1.0, cIPD[0], cIPD[1], w_fp[9] );

      // Amplitude(s) for diagram number 18
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[16], w_fp[9], w_fp[4], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[5] -= amp_sv[0];

      // *** DIAGRAM 19 OF 123 ***

      // Wavefunction(s) for diagram number 19
      // (none)

      // Amplitude(s) for diagram number 19
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[16], w_fp[12], w_fp[10], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[3] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[5] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 20 OF 123 ***

      // Wavefunction(s) for diagram number 20
      VVV1P0_1<W_ACCESS, CD_ACCESS>( w_fp[1], w_fp[4], COUPs[0], 1.0, 0., 0., w_fp[6] );
      FFV1P0_3<W_ACCESS, CD_ACCESS>( w_fp[3], w_fp[12], COUPs[1], 1.0, 0., 0., w_fp[17] );

      // Amplitude(s) for diagram number 20
      VVV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[6], w_fp[5], w_fp[17], COUPs[0], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[0] += amp_sv[0];
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[5] += amp_sv[0];

      // *** DIAGRAM 21 OF 123 ***

      // Wavefunction(s) for diagram number 21
      // (none)

      // Amplitude(s) for diagram number 21
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[3], w_fp[9], w_fp[6], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[4] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[5] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 22 OF 123 ***

      // Wavefunction(s) for diagram number 22
      // (none)

      // Amplitude(s) for diagram number 22
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[13], w_fp[12], w_fp[6], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[0] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[2] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 23 OF 123 ***

      // Wavefunction(s) for diagram number 23
      VVV1P0_1<W_ACCESS, CD_ACCESS>( w_fp[1], w_fp[5], COUPs[0], 1.0, 0., 0., w_fp[18] );

      // Amplitude(s) for diagram number 23
      VVV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[18], w_fp[4], w_fp[17], COUPs[0], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[1] += amp_sv[0];
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[3] += amp_sv[0];
      jamp_sv[4] -= amp_sv[0];

      // *** DIAGRAM 24 OF 123 ***

      // Wavefunction(s) for diagram number 24
      // (none)

      // Amplitude(s) for diagram number 24
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[3], w_fp[8], w_fp[18], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[2] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[3] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 25 OF 123 ***

      // Wavefunction(s) for diagram number 25
      // (none)

      // Amplitude(s) for diagram number 25
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[15], w_fp[12], w_fp[18], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[1] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[4] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 26 OF 123 ***

      // Wavefunction(s) for diagram number 26
      FFV1_1<W_ACCESS, CD_ACCESS>( w_fp[12], w_fp[1], COUPs[1], 1.0, cIPD[0], cIPD[1], w_fp[19] );

      // Amplitude(s) for diagram number 26
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[15], w_fp[19], w_fp[5], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[1] -= amp_sv[0];

      // *** DIAGRAM 27 OF 123 ***

      // Wavefunction(s) for diagram number 27
      // (none)

      // Amplitude(s) for diagram number 27
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[15], w_fp[9], w_fp[1], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[4] -= amp_sv[0];

      // *** DIAGRAM 28 OF 123 ***

      // Wavefunction(s) for diagram number 28
      // (none)

      // Amplitude(s) for diagram number 28
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[13], w_fp[19], w_fp[4], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[0] -= amp_sv[0];

      // *** DIAGRAM 29 OF 123 ***

      // Wavefunction(s) for diagram number 29
      // (none)

      // Amplitude(s) for diagram number 29
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[13], w_fp[8], w_fp[1], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[2] -= amp_sv[0];

      // *** DIAGRAM 30 OF 123 ***

      // Wavefunction(s) for diagram number 30
      // (none)

      // Amplitude(s) for diagram number 30
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[3], w_fp[19], w_fp[10], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[0] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[1] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 31 OF 123 ***

      // Wavefunction(s) for diagram number 31
      // (none)

      // Amplitude(s) for diagram number 31
      VVV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[1], w_fp[10], w_fp[17], COUPs[0], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[0] += amp_sv[0];
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[5] += amp_sv[0];

      // *** DIAGRAM 32 OF 123 ***

      // Wavefunction(s) for diagram number 32
      VVVV1P0_1<W_ACCESS, CD_ACCESS>( w_fp[1], w_fp[4], w_fp[5], COUPs[2], 1.0, 0., 0., w_fp[17] );
      VVVV3P0_1<W_ACCESS, CD_ACCESS>( w_fp[1], w_fp[4], w_fp[5], COUPs[2], 1.0, 0., 0., w_fp[19] );
      VVVV4P0_1<W_ACCESS, CD_ACCESS>( w_fp[1], w_fp[4], w_fp[5], COUPs[2], 1.0, 0., 0., w_fp[8] );

      // Amplitude(s) for diagram number 32
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[3], w_fp[12], w_fp[17], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[0] += amp_sv[0];
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[5] += amp_sv[0];
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[3], w_fp[12], w_fp[19], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[2] += amp_sv[0];
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[4] += amp_sv[0];
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[3], w_fp[12], w_fp[8], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[0] -= amp_sv[0];
      jamp_sv[2] += amp_sv[0];
      jamp_sv[4] += amp_sv[0];
      jamp_sv[5] -= amp_sv[0];

      // *** DIAGRAM 33 OF 123 ***

      // Wavefunction(s) for diagram number 33
      FFV1_2<W_ACCESS, CD_ACCESS>( w_fp[3], w_fp[0], COUPs[1], 1.0, cIPD[0], cIPD[1], w_fp[12] );
      FFV1_1<W_ACCESS, CD_ACCESS>( w_fp[2], w_fp[1], COUPs[1], 1.0, cIPD[0], cIPD[1], w_fp[9] );
      FFV1_2<W_ACCESS, CD_ACCESS>( w_fp[12], w_fp[4], COUPs[1], 1.0, cIPD[0], cIPD[1], w_fp[20] );

      // Amplitude(s) for diagram number 33
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[20], w_fp[9], w_fp[5], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[11] -= amp_sv[0];

      // *** DIAGRAM 34 OF 123 ***

      // Wavefunction(s) for diagram number 34
      FFV1_2<W_ACCESS, CD_ACCESS>( w_fp[12], w_fp[5], COUPs[1], 1.0, cIPD[0], cIPD[1], w_fp[21] );

      // Amplitude(s) for diagram number 34
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[21], w_fp[9], w_fp[4], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[9] -= amp_sv[0];

      // *** DIAGRAM 35 OF 123 ***

      // Wavefunction(s) for diagram number 35
      // (none)

      // Amplitude(s) for diagram number 35
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[12], w_fp[9], w_fp[10], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[9] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[11] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 36 OF 123 ***

      // Wavefunction(s) for diagram number 36
      FFV1P0_3<W_ACCESS, CD_ACCESS>( w_fp[12], w_fp[2], COUPs[1], 1.0, 0., 0., w_fp[22] );

      // Amplitude(s) for diagram number 36
      VVV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[6], w_fp[5], w_fp[22], COUPs[0], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[9] += amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[23] += amp_sv[0];

      // *** DIAGRAM 37 OF 123 ***

      // Wavefunction(s) for diagram number 37
      // (none)

      // Amplitude(s) for diagram number 37
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[21], w_fp[2], w_fp[6], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[9] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[15] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 38 OF 123 ***

      // Wavefunction(s) for diagram number 38
      // (none)

      // Amplitude(s) for diagram number 38
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[12], w_fp[14], w_fp[6], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[21] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[23] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 39 OF 123 ***

      // Wavefunction(s) for diagram number 39
      // (none)

      // Amplitude(s) for diagram number 39
      VVV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[18], w_fp[4], w_fp[22], COUPs[0], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[11] += amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[17] += amp_sv[0];
      jamp_sv[21] -= amp_sv[0];

      // *** DIAGRAM 40 OF 123 ***

      // Wavefunction(s) for diagram number 40
      // (none)

      // Amplitude(s) for diagram number 40
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[20], w_fp[2], w_fp[18], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[11] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[21] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 41 OF 123 ***

      // Wavefunction(s) for diagram number 41
      // (none)

      // Amplitude(s) for diagram number 41
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[12], w_fp[11], w_fp[18], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[15] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[17] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 42 OF 123 ***

      // Wavefunction(s) for diagram number 42
      FFV1_2<W_ACCESS, CD_ACCESS>( w_fp[12], w_fp[1], COUPs[1], 1.0, cIPD[0], cIPD[1], w_fp[23] );

      // Amplitude(s) for diagram number 42
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[23], w_fp[11], w_fp[5], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[17] -= amp_sv[0];

      // *** DIAGRAM 43 OF 123 ***

      // Wavefunction(s) for diagram number 43
      // (none)

      // Amplitude(s) for diagram number 43
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[21], w_fp[11], w_fp[1], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[15] -= amp_sv[0];

      // *** DIAGRAM 44 OF 123 ***

      // Wavefunction(s) for diagram number 44
      // (none)

      // Amplitude(s) for diagram number 44
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[23], w_fp[14], w_fp[4], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[23] -= amp_sv[0];

      // *** DIAGRAM 45 OF 123 ***

      // Wavefunction(s) for diagram number 45
      // (none)

      // Amplitude(s) for diagram number 45
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[20], w_fp[14], w_fp[1], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[21] -= amp_sv[0];

      // *** DIAGRAM 46 OF 123 ***

      // Wavefunction(s) for diagram number 46
      // (none)

      // Amplitude(s) for diagram number 46
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[23], w_fp[2], w_fp[10], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[17] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[23] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 47 OF 123 ***

      // Wavefunction(s) for diagram number 47
      // (none)

      // Amplitude(s) for diagram number 47
      VVV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[1], w_fp[10], w_fp[22], COUPs[0], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[9] += amp_sv[0];
      jamp_sv[11] -= amp_sv[0];
      jamp_sv[17] -= amp_sv[0];
      jamp_sv[23] += amp_sv[0];

      // *** DIAGRAM 48 OF 123 ***

      // Wavefunction(s) for diagram number 48
      // (none)

      // Amplitude(s) for diagram number 48
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[12], w_fp[2], w_fp[17], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[9] += amp_sv[0];
      jamp_sv[11] -= amp_sv[0];
      jamp_sv[17] -= amp_sv[0];
      jamp_sv[23] += amp_sv[0];
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[12], w_fp[2], w_fp[19], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[11] -= amp_sv[0];
      jamp_sv[15] += amp_sv[0];
      jamp_sv[17] -= amp_sv[0];
      jamp_sv[21] += amp_sv[0];
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[12], w_fp[2], w_fp[8], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[9] -= amp_sv[0];
      jamp_sv[15] += amp_sv[0];
      jamp_sv[21] += amp_sv[0];
      jamp_sv[23] -= amp_sv[0];

      // *** DIAGRAM 49 OF 123 ***

      // Wavefunction(s) for diagram number 49
      VVV1P0_1<W_ACCESS, CD_ACCESS>( w_fp[0], w_fp[4], COUPs[0], 1.0, 0., 0., w_fp[12] );
      FFV1_2<W_ACCESS, CD_ACCESS>( w_fp[3], w_fp[12], COUPs[1], 1.0, cIPD[0], cIPD[1], w_fp[22] );

      // Amplitude(s) for diagram number 49
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[22], w_fp[9], w_fp[5], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[10] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[11] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 50 OF 123 ***

      // Wavefunction(s) for diagram number 50
      VVV1P0_1<W_ACCESS, CD_ACCESS>( w_fp[12], w_fp[5], COUPs[0], 1.0, 0., 0., w_fp[23] );

      // Amplitude(s) for diagram number 50
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[3], w_fp[9], w_fp[23], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[6] += amp_sv[0];
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[11] += amp_sv[0];

      // *** DIAGRAM 51 OF 123 ***

      // Wavefunction(s) for diagram number 51
      // (none)

      // Amplitude(s) for diagram number 51
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[13], w_fp[9], w_fp[12], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[6] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[8] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 52 OF 123 ***

      // Wavefunction(s) for diagram number 52
      FFV1_1<W_ACCESS, CD_ACCESS>( w_fp[2], w_fp[12], COUPs[1], 1.0, cIPD[0], cIPD[1], w_fp[20] );

      // Amplitude(s) for diagram number 52
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[16], w_fp[20], w_fp[5], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[3] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[13] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 53 OF 123 ***

      // Wavefunction(s) for diagram number 53
      // (none)

      // Amplitude(s) for diagram number 53
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[16], w_fp[2], w_fp[23], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[3] += amp_sv[0];
      jamp_sv[13] -= amp_sv[0];
      jamp_sv[19] -= amp_sv[0];
      jamp_sv[22] += amp_sv[0];

      // *** DIAGRAM 54 OF 123 ***

      // Wavefunction(s) for diagram number 54
      // (none)

      // Amplitude(s) for diagram number 54
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[16], w_fp[14], w_fp[12], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[19] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[22] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 55 OF 123 ***

      // Wavefunction(s) for diagram number 55
      // (none)

      // Amplitude(s) for diagram number 55
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[3], w_fp[20], w_fp[18], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[2] += amp_sv[0];
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[13] += amp_sv[0];

      // *** DIAGRAM 56 OF 123 ***

      // Wavefunction(s) for diagram number 56
      // (none)

      // Amplitude(s) for diagram number 56
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[22], w_fp[2], w_fp[18], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[10] += amp_sv[0];
      jamp_sv[11] -= amp_sv[0];
      jamp_sv[20] -= amp_sv[0];
      jamp_sv[21] += amp_sv[0];

      // *** DIAGRAM 57 OF 123 ***

      // Wavefunction(s) for diagram number 57
      // (none)

      // Amplitude(s) for diagram number 57
      VVV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[12], w_fp[18], w_fp[7], COUPs[0], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[2] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[3] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[10] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[11] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[12] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[13] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[20] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[21] += cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 58 OF 123 ***

      // Wavefunction(s) for diagram number 58
      // (none)

      // Amplitude(s) for diagram number 58
      VVVV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[12], w_fp[1], w_fp[7], w_fp[5], COUPs[2], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[2] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[6] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[8] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[12] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[19] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[20] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[21] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[22] += cxtype( 0, 1 ) * amp_sv[0];
      VVVV3_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[12], w_fp[1], w_fp[7], w_fp[5], COUPs[2], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[2] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[3] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[10] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[11] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[12] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[13] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[20] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[21] -= cxtype( 0, 1 ) * amp_sv[0];
      VVVV4_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[12], w_fp[1], w_fp[7], w_fp[5], COUPs[2], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[3] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[6] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[8] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[10] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[11] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[13] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[19] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[22] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 59 OF 123 ***

      // Wavefunction(s) for diagram number 59
      VVV1P0_1<W_ACCESS, CD_ACCESS>( w_fp[12], w_fp[1], COUPs[0], 1.0, 0., 0., w_fp[21] );

      // Amplitude(s) for diagram number 59
      VVV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[7], w_fp[5], w_fp[21], COUPs[0], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[2] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[6] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[8] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[12] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[19] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[20] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[21] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[22] += cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 60 OF 123 ***

      // Wavefunction(s) for diagram number 60
      // (none)

      // Amplitude(s) for diagram number 60
      VVV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[1], w_fp[7], w_fp[23], COUPs[0], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[3] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[6] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[8] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[10] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[11] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[13] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[19] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[22] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 61 OF 123 ***

      // Wavefunction(s) for diagram number 61
      // (none)

      // Amplitude(s) for diagram number 61
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[3], w_fp[14], w_fp[21], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[19] += amp_sv[0];
      jamp_sv[20] -= amp_sv[0];
      jamp_sv[21] += amp_sv[0];
      jamp_sv[22] -= amp_sv[0];

      // *** DIAGRAM 62 OF 123 ***

      // Wavefunction(s) for diagram number 62
      // (none)

      // Amplitude(s) for diagram number 62
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[22], w_fp[14], w_fp[1], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[20] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[21] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 63 OF 123 ***

      // Wavefunction(s) for diagram number 63
      // (none)

      // Amplitude(s) for diagram number 63
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[13], w_fp[2], w_fp[21], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[2] += amp_sv[0];
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[8] += amp_sv[0];
      jamp_sv[12] -= amp_sv[0];

      // *** DIAGRAM 64 OF 123 ***

      // Wavefunction(s) for diagram number 64
      // (none)

      // Amplitude(s) for diagram number 64
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[13], w_fp[20], w_fp[1], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[2] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[12] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 65 OF 123 ***

      // Wavefunction(s) for diagram number 65
      VVV1P0_1<W_ACCESS, CD_ACCESS>( w_fp[0], w_fp[5], COUPs[0], 1.0, 0., 0., w_fp[20] );
      FFV1_2<W_ACCESS, CD_ACCESS>( w_fp[3], w_fp[20], COUPs[1], 1.0, cIPD[0], cIPD[1], w_fp[21] );

      // Amplitude(s) for diagram number 65
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[21], w_fp[9], w_fp[4], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[8] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[9] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 66 OF 123 ***

      // Wavefunction(s) for diagram number 66
      VVV1P0_1<W_ACCESS, CD_ACCESS>( w_fp[20], w_fp[4], COUPs[0], 1.0, 0., 0., w_fp[22] );

      // Amplitude(s) for diagram number 66
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[3], w_fp[9], w_fp[22], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[7] += amp_sv[0];
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[9] += amp_sv[0];
      jamp_sv[10] -= amp_sv[0];

      // *** DIAGRAM 67 OF 123 ***

      // Wavefunction(s) for diagram number 67
      // (none)

      // Amplitude(s) for diagram number 67
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[15], w_fp[9], w_fp[20], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[7] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[10] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 68 OF 123 ***

      // Wavefunction(s) for diagram number 68
      FFV1_1<W_ACCESS, CD_ACCESS>( w_fp[2], w_fp[20], COUPs[1], 1.0, cIPD[0], cIPD[1], w_fp[23] );

      // Amplitude(s) for diagram number 68
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[16], w_fp[23], w_fp[4], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[5] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[19] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 69 OF 123 ***

      // Wavefunction(s) for diagram number 69
      // (none)

      // Amplitude(s) for diagram number 69
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[16], w_fp[2], w_fp[22], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[5] += amp_sv[0];
      jamp_sv[13] -= amp_sv[0];
      jamp_sv[16] += amp_sv[0];
      jamp_sv[19] -= amp_sv[0];

      // *** DIAGRAM 70 OF 123 ***

      // Wavefunction(s) for diagram number 70
      // (none)

      // Amplitude(s) for diagram number 70
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[16], w_fp[11], w_fp[20], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[13] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[16] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 71 OF 123 ***

      // Wavefunction(s) for diagram number 71
      // (none)

      // Amplitude(s) for diagram number 71
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[3], w_fp[23], w_fp[6], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[4] += amp_sv[0];
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[19] += amp_sv[0];

      // *** DIAGRAM 72 OF 123 ***

      // Wavefunction(s) for diagram number 72
      // (none)

      // Amplitude(s) for diagram number 72
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[21], w_fp[2], w_fp[6], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[8] += amp_sv[0];
      jamp_sv[9] -= amp_sv[0];
      jamp_sv[14] -= amp_sv[0];
      jamp_sv[15] += amp_sv[0];

      // *** DIAGRAM 73 OF 123 ***

      // Wavefunction(s) for diagram number 73
      // (none)

      // Amplitude(s) for diagram number 73
      VVV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[20], w_fp[6], w_fp[7], COUPs[0], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[4] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[5] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[8] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[9] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[14] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[15] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[18] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[19] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 74 OF 123 ***

      // Wavefunction(s) for diagram number 74
      // (none)

      // Amplitude(s) for diagram number 74
      VVVV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[20], w_fp[1], w_fp[7], w_fp[4], COUPs[2], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[4] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[7] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[10] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[13] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[14] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[15] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[16] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[18] -= cxtype( 0, 1 ) * amp_sv[0];
      VVVV3_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[20], w_fp[1], w_fp[7], w_fp[4], COUPs[2], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[4] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[5] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[8] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[9] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[14] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[15] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[18] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[19] += cxtype( 0, 1 ) * amp_sv[0];
      VVVV4_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[20], w_fp[1], w_fp[7], w_fp[4], COUPs[2], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[5] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[7] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[8] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[9] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[10] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[13] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[16] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[19] += cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 75 OF 123 ***

      // Wavefunction(s) for diagram number 75
      VVV1P0_1<W_ACCESS, CD_ACCESS>( w_fp[20], w_fp[1], COUPs[0], 1.0, 0., 0., w_fp[12] );

      // Amplitude(s) for diagram number 75
      VVV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[7], w_fp[4], w_fp[12], COUPs[0], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[4] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[7] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[10] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[13] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[14] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[15] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[16] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[18] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 76 OF 123 ***

      // Wavefunction(s) for diagram number 76
      // (none)

      // Amplitude(s) for diagram number 76
      VVV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[1], w_fp[7], w_fp[22], COUPs[0], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[5] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[7] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[8] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[9] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[10] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[13] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[16] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[19] += cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 77 OF 123 ***

      // Wavefunction(s) for diagram number 77
      // (none)

      // Amplitude(s) for diagram number 77
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[3], w_fp[11], w_fp[12], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[13] += amp_sv[0];
      jamp_sv[14] -= amp_sv[0];
      jamp_sv[15] += amp_sv[0];
      jamp_sv[16] -= amp_sv[0];

      // *** DIAGRAM 78 OF 123 ***

      // Wavefunction(s) for diagram number 78
      // (none)

      // Amplitude(s) for diagram number 78
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[21], w_fp[11], w_fp[1], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[14] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[15] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 79 OF 123 ***

      // Wavefunction(s) for diagram number 79
      // (none)

      // Amplitude(s) for diagram number 79
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[15], w_fp[2], w_fp[12], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[4] += amp_sv[0];
      jamp_sv[7] -= amp_sv[0];
      jamp_sv[10] += amp_sv[0];
      jamp_sv[18] -= amp_sv[0];

      // *** DIAGRAM 80 OF 123 ***

      // Wavefunction(s) for diagram number 80
      // (none)

      // Amplitude(s) for diagram number 80
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[15], w_fp[23], w_fp[1], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[4] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[18] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 81 OF 123 ***

      // Wavefunction(s) for diagram number 81
      FFV1_1<W_ACCESS, CD_ACCESS>( w_fp[9], w_fp[0], COUPs[1], 1.0, cIPD[0], cIPD[1], w_fp[23] );

      // Amplitude(s) for diagram number 81
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[15], w_fp[23], w_fp[5], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[7] -= amp_sv[0];

      // *** DIAGRAM 82 OF 123 ***

      // Wavefunction(s) for diagram number 82
      FFV1_2<W_ACCESS, CD_ACCESS>( w_fp[15], w_fp[0], COUPs[1], 1.0, cIPD[0], cIPD[1], w_fp[12] );

      // Amplitude(s) for diagram number 82
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[12], w_fp[9], w_fp[5], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[10] -= amp_sv[0];

      // *** DIAGRAM 83 OF 123 ***

      // Wavefunction(s) for diagram number 83
      // (none)

      // Amplitude(s) for diagram number 83
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[13], w_fp[23], w_fp[4], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[6] -= amp_sv[0];

      // *** DIAGRAM 84 OF 123 ***

      // Wavefunction(s) for diagram number 84
      FFV1_2<W_ACCESS, CD_ACCESS>( w_fp[13], w_fp[0], COUPs[1], 1.0, cIPD[0], cIPD[1], w_fp[21] );

      // Amplitude(s) for diagram number 84
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[21], w_fp[9], w_fp[4], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[8] -= amp_sv[0];

      // *** DIAGRAM 85 OF 123 ***

      // Wavefunction(s) for diagram number 85
      // (none)

      // Amplitude(s) for diagram number 85
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[3], w_fp[23], w_fp[10], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[6] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[7] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 86 OF 123 ***

      // Wavefunction(s) for diagram number 86
      VVV1P0_1<W_ACCESS, CD_ACCESS>( w_fp[0], w_fp[10], COUPs[0], 1.0, 0., 0., w_fp[23] );

      // Amplitude(s) for diagram number 86
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[3], w_fp[9], w_fp[23], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[6] += amp_sv[0];
      jamp_sv[7] -= amp_sv[0];
      jamp_sv[9] -= amp_sv[0];
      jamp_sv[11] += amp_sv[0];

      // *** DIAGRAM 87 OF 123 ***

      // Wavefunction(s) for diagram number 87
      FFV1_2<W_ACCESS, CD_ACCESS>( w_fp[16], w_fp[0], COUPs[1], 1.0, cIPD[0], cIPD[1], w_fp[22] );

      // Amplitude(s) for diagram number 87
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[22], w_fp[11], w_fp[5], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[16] -= amp_sv[0];

      // *** DIAGRAM 88 OF 123 ***

      // Wavefunction(s) for diagram number 88
      FFV1_1<W_ACCESS, CD_ACCESS>( w_fp[11], w_fp[0], COUPs[1], 1.0, cIPD[0], cIPD[1], w_fp[20] );

      // Amplitude(s) for diagram number 88
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[16], w_fp[20], w_fp[5], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[13] -= amp_sv[0];

      // *** DIAGRAM 89 OF 123 ***

      // Wavefunction(s) for diagram number 89
      // (none)

      // Amplitude(s) for diagram number 89
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[22], w_fp[14], w_fp[4], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[22] -= amp_sv[0];

      // *** DIAGRAM 90 OF 123 ***

      // Wavefunction(s) for diagram number 90
      FFV1_1<W_ACCESS, CD_ACCESS>( w_fp[14], w_fp[0], COUPs[1], 1.0, cIPD[0], cIPD[1], w_fp[24] );

      // Amplitude(s) for diagram number 90
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[16], w_fp[24], w_fp[4], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[19] -= amp_sv[0];

      // *** DIAGRAM 91 OF 123 ***

      // Wavefunction(s) for diagram number 91
      // (none)

      // Amplitude(s) for diagram number 91
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[22], w_fp[2], w_fp[10], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[16] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[22] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 92 OF 123 ***

      // Wavefunction(s) for diagram number 92
      // (none)

      // Amplitude(s) for diagram number 92
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[16], w_fp[2], w_fp[23], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[3] += amp_sv[0];
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[22] += amp_sv[0];

      // *** DIAGRAM 93 OF 123 ***

      // Wavefunction(s) for diagram number 93
      // (none)

      // Amplitude(s) for diagram number 93
      VVVV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[0], w_fp[6], w_fp[7], w_fp[5], COUPs[2], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[0] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[2] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[8] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[14] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[18] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[19] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[21] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[23] -= cxtype( 0, 1 ) * amp_sv[0];
      VVVV3_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[0], w_fp[6], w_fp[7], w_fp[5], COUPs[2], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[0] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[2] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[4] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[5] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[9] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[15] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[21] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[23] -= cxtype( 0, 1 ) * amp_sv[0];
      VVVV4_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[0], w_fp[6], w_fp[7], w_fp[5], COUPs[2], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[4] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[5] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[8] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[9] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[14] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[15] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[18] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[19] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 94 OF 123 ***

      // Wavefunction(s) for diagram number 94
      VVV1P0_1<W_ACCESS, CD_ACCESS>( w_fp[0], w_fp[6], COUPs[0], 1.0, 0., 0., w_fp[22] );

      // Amplitude(s) for diagram number 94
      VVV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[7], w_fp[5], w_fp[22], COUPs[0], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[0] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[2] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[8] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[14] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[18] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[19] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[21] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[23] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 95 OF 123 ***

      // Wavefunction(s) for diagram number 95
      VVV1P0_1<W_ACCESS, CD_ACCESS>( w_fp[0], w_fp[7], COUPs[0], 1.0, 0., 0., w_fp[25] );

      // Amplitude(s) for diagram number 95
      VVV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[6], w_fp[5], w_fp[25], COUPs[0], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[0] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[2] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[4] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[5] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[9] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[15] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[21] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[23] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 96 OF 123 ***

      // Wavefunction(s) for diagram number 96
      // (none)

      // Amplitude(s) for diagram number 96
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[3], w_fp[14], w_fp[22], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[18] += amp_sv[0];
      jamp_sv[19] -= amp_sv[0];
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[23] += amp_sv[0];

      // *** DIAGRAM 97 OF 123 ***

      // Wavefunction(s) for diagram number 97
      // (none)

      // Amplitude(s) for diagram number 97
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[3], w_fp[24], w_fp[6], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[18] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[19] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 98 OF 123 ***

      // Wavefunction(s) for diagram number 98
      // (none)

      // Amplitude(s) for diagram number 98
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[13], w_fp[2], w_fp[22], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[0] += amp_sv[0];
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[14] += amp_sv[0];

      // *** DIAGRAM 99 OF 123 ***

      // Wavefunction(s) for diagram number 99
      // (none)

      // Amplitude(s) for diagram number 99
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[21], w_fp[2], w_fp[6], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[8] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[14] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 100 OF 123 ***

      // Wavefunction(s) for diagram number 100
      // (none)

      // Amplitude(s) for diagram number 100
      VVVV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[0], w_fp[18], w_fp[7], w_fp[4], COUPs[2], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[1] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[4] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[10] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[12] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[13] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[15] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[17] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[20] += cxtype( 0, 1 ) * amp_sv[0];
      VVVV3_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[0], w_fp[18], w_fp[7], w_fp[4], COUPs[2], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[1] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[2] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[3] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[4] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[11] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[15] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[17] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[21] += cxtype( 0, 1 ) * amp_sv[0];
      VVVV4_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[0], w_fp[18], w_fp[7], w_fp[4], COUPs[2], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[2] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[3] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[10] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[11] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[12] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[13] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[20] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[21] += cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 101 OF 123 ***

      // Wavefunction(s) for diagram number 101
      VVV1P0_1<W_ACCESS, CD_ACCESS>( w_fp[0], w_fp[18], COUPs[0], 1.0, 0., 0., w_fp[6] );

      // Amplitude(s) for diagram number 101
      VVV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[7], w_fp[4], w_fp[6], COUPs[0], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[1] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[4] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[10] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[12] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[13] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[15] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[17] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[20] += cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 102 OF 123 ***

      // Wavefunction(s) for diagram number 102
      // (none)

      // Amplitude(s) for diagram number 102
      VVV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[18], w_fp[4], w_fp[25], COUPs[0], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[1] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[2] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[3] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[4] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[11] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[15] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[17] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[21] += cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 103 OF 123 ***

      // Wavefunction(s) for diagram number 103
      // (none)

      // Amplitude(s) for diagram number 103
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[3], w_fp[11], w_fp[6], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[12] += amp_sv[0];
      jamp_sv[13] -= amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[17] += amp_sv[0];

      // *** DIAGRAM 104 OF 123 ***

      // Wavefunction(s) for diagram number 104
      // (none)

      // Amplitude(s) for diagram number 104
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[3], w_fp[20], w_fp[18], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[12] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[13] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 105 OF 123 ***

      // Wavefunction(s) for diagram number 105
      // (none)

      // Amplitude(s) for diagram number 105
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[15], w_fp[2], w_fp[6], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[1] += amp_sv[0];
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[20] += amp_sv[0];

      // *** DIAGRAM 106 OF 123 ***

      // Wavefunction(s) for diagram number 106
      // (none)

      // Amplitude(s) for diagram number 106
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[12], w_fp[2], w_fp[18], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[10] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[20] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 107 OF 123 ***

      // Wavefunction(s) for diagram number 107
      // (none)

      // Amplitude(s) for diagram number 107
      VVVV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[0], w_fp[1], w_fp[7], w_fp[10], COUPs[2], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[0] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[1] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[6] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[7] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[16] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[17] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[22] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[23] -= cxtype( 0, 1 ) * amp_sv[0];
      VVVV3_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[0], w_fp[1], w_fp[7], w_fp[10], COUPs[2], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[0] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[1] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[3] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[5] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[9] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[11] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[17] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[23] -= cxtype( 0, 1 ) * amp_sv[0];
      VVVV4_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[0], w_fp[1], w_fp[7], w_fp[10], COUPs[2], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[3] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[5] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[6] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[7] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[9] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[11] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[16] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[22] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 108 OF 123 ***

      // Wavefunction(s) for diagram number 108
      // (none)

      // Amplitude(s) for diagram number 108
      VVV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[1], w_fp[10], w_fp[25], COUPs[0], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[0] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[1] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[3] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[5] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[9] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[11] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[17] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[23] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 109 OF 123 ***

      // Wavefunction(s) for diagram number 109
      // (none)

      // Amplitude(s) for diagram number 109
      VVV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[1], w_fp[7], w_fp[23], COUPs[0], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[3] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[5] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[6] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[7] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[9] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[11] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[16] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[22] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 110 OF 123 ***

      // Wavefunction(s) for diagram number 110
      // (none)

      // Amplitude(s) for diagram number 110
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[13], w_fp[20], w_fp[1], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[12] -= amp_sv[0];

      // *** DIAGRAM 111 OF 123 ***

      // Wavefunction(s) for diagram number 111
      // (none)

      // Amplitude(s) for diagram number 111
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[21], w_fp[11], w_fp[1], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[14] -= amp_sv[0];

      // *** DIAGRAM 112 OF 123 ***

      // Wavefunction(s) for diagram number 112
      // (none)

      // Amplitude(s) for diagram number 112
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[15], w_fp[24], w_fp[1], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[18] -= amp_sv[0];

      // *** DIAGRAM 113 OF 123 ***

      // Wavefunction(s) for diagram number 113
      // (none)

      // Amplitude(s) for diagram number 113
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[12], w_fp[14], w_fp[1], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[20] -= amp_sv[0];

      // *** DIAGRAM 114 OF 123 ***

      // Wavefunction(s) for diagram number 114
      VVVV1P0_1<W_ACCESS, CD_ACCESS>( w_fp[0], w_fp[1], w_fp[4], COUPs[2], 1.0, 0., 0., w_fp[12] );
      VVVV3P0_1<W_ACCESS, CD_ACCESS>( w_fp[0], w_fp[1], w_fp[4], COUPs[2], 1.0, 0., 0., w_fp[24] );
      VVVV4P0_1<W_ACCESS, CD_ACCESS>( w_fp[0], w_fp[1], w_fp[4], COUPs[2], 1.0, 0., 0., w_fp[21] );

      // Amplitude(s) for diagram number 114
      VVV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[12], w_fp[7], w_fp[5], COUPs[0], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[0] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[2] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[8] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[14] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[18] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[19] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[21] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[23] -= cxtype( 0, 1 ) * amp_sv[0];
      VVV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[24], w_fp[7], w_fp[5], COUPs[0], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[2] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[6] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[8] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[12] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[19] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[20] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[21] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[22] -= cxtype( 0, 1 ) * amp_sv[0];
      VVV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[21], w_fp[7], w_fp[5], COUPs[0], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[0] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[6] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[12] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[14] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[18] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[20] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[22] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[23] += cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 115 OF 123 ***

      // Wavefunction(s) for diagram number 115
      // (none)

      // Amplitude(s) for diagram number 115
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[3], w_fp[14], w_fp[12], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[18] += amp_sv[0];
      jamp_sv[19] -= amp_sv[0];
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[23] += amp_sv[0];
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[3], w_fp[14], w_fp[24], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[19] -= amp_sv[0];
      jamp_sv[20] += amp_sv[0];
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[22] += amp_sv[0];
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[3], w_fp[14], w_fp[21], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[20] += amp_sv[0];
      jamp_sv[22] += amp_sv[0];
      jamp_sv[23] -= amp_sv[0];

      // *** DIAGRAM 116 OF 123 ***

      // Wavefunction(s) for diagram number 116
      // (none)

      // Amplitude(s) for diagram number 116
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[13], w_fp[2], w_fp[12], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[0] += amp_sv[0];
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[14] += amp_sv[0];
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[13], w_fp[2], w_fp[24], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[6] += amp_sv[0];
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[12] += amp_sv[0];
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[13], w_fp[2], w_fp[21], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[0] -= amp_sv[0];
      jamp_sv[6] += amp_sv[0];
      jamp_sv[12] += amp_sv[0];
      jamp_sv[14] -= amp_sv[0];

      // *** DIAGRAM 117 OF 123 ***

      // Wavefunction(s) for diagram number 117
      VVVV1P0_1<W_ACCESS, CD_ACCESS>( w_fp[0], w_fp[1], w_fp[5], COUPs[2], 1.0, 0., 0., w_fp[21] );
      VVVV3P0_1<W_ACCESS, CD_ACCESS>( w_fp[0], w_fp[1], w_fp[5], COUPs[2], 1.0, 0., 0., w_fp[13] );
      VVVV4P0_1<W_ACCESS, CD_ACCESS>( w_fp[0], w_fp[1], w_fp[5], COUPs[2], 1.0, 0., 0., w_fp[24] );

      // Amplitude(s) for diagram number 117
      VVV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[21], w_fp[7], w_fp[4], COUPs[0], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[1] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[4] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[10] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[12] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[13] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[15] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[17] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[20] += cxtype( 0, 1 ) * amp_sv[0];
      VVV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[13], w_fp[7], w_fp[4], COUPs[0], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[4] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[7] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[10] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[13] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[14] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[15] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[16] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[18] += cxtype( 0, 1 ) * amp_sv[0];
      VVV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[24], w_fp[7], w_fp[4], COUPs[0], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[1] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[7] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[12] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[14] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[16] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[17] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[18] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[20] -= cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 118 OF 123 ***

      // Wavefunction(s) for diagram number 118
      // (none)

      // Amplitude(s) for diagram number 118
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[3], w_fp[11], w_fp[21], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[12] += amp_sv[0];
      jamp_sv[13] -= amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[17] += amp_sv[0];
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[3], w_fp[11], w_fp[13], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[13] -= amp_sv[0];
      jamp_sv[14] += amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[16] += amp_sv[0];
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[3], w_fp[11], w_fp[24], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[14] += amp_sv[0];
      jamp_sv[16] += amp_sv[0];
      jamp_sv[17] -= amp_sv[0];

      // *** DIAGRAM 119 OF 123 ***

      // Wavefunction(s) for diagram number 119
      // (none)

      // Amplitude(s) for diagram number 119
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[15], w_fp[2], w_fp[21], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[1] += amp_sv[0];
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[20] += amp_sv[0];
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[15], w_fp[2], w_fp[13], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[7] += amp_sv[0];
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[18] += amp_sv[0];
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[15], w_fp[2], w_fp[24], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[7] += amp_sv[0];
      jamp_sv[18] += amp_sv[0];
      jamp_sv[20] -= amp_sv[0];

      // *** DIAGRAM 120 OF 123 ***

      // Wavefunction(s) for diagram number 120
      VVVV1P0_1<W_ACCESS, CD_ACCESS>( w_fp[0], w_fp[4], w_fp[5], COUPs[2], 1.0, 0., 0., w_fp[24] );
      VVVV3P0_1<W_ACCESS, CD_ACCESS>( w_fp[0], w_fp[4], w_fp[5], COUPs[2], 1.0, 0., 0., w_fp[15] );
      VVVV4P0_1<W_ACCESS, CD_ACCESS>( w_fp[0], w_fp[4], w_fp[5], COUPs[2], 1.0, 0., 0., w_fp[13] );

      // Amplitude(s) for diagram number 120
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[3], w_fp[9], w_fp[24], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[6] += amp_sv[0];
      jamp_sv[7] -= amp_sv[0];
      jamp_sv[9] -= amp_sv[0];
      jamp_sv[11] += amp_sv[0];
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[3], w_fp[9], w_fp[15], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[7] -= amp_sv[0];
      jamp_sv[8] += amp_sv[0];
      jamp_sv[9] -= amp_sv[0];
      jamp_sv[10] += amp_sv[0];
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[3], w_fp[9], w_fp[13], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[8] += amp_sv[0];
      jamp_sv[10] += amp_sv[0];
      jamp_sv[11] -= amp_sv[0];

      // *** DIAGRAM 121 OF 123 ***

      // Wavefunction(s) for diagram number 121
      // (none)

      // Amplitude(s) for diagram number 121
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[16], w_fp[2], w_fp[24], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[3] += amp_sv[0];
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[22] += amp_sv[0];
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[16], w_fp[2], w_fp[15], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[13] += amp_sv[0];
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[19] += amp_sv[0];
      FFV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[16], w_fp[2], w_fp[13], COUPs[1], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[13] += amp_sv[0];
      jamp_sv[19] += amp_sv[0];
      jamp_sv[22] -= amp_sv[0];

      // *** DIAGRAM 122 OF 123 ***

      // Wavefunction(s) for diagram number 122
      // (none)

      // Amplitude(s) for diagram number 122
      VVV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[24], w_fp[1], w_fp[7], COUPs[0], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[3] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[5] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[6] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[7] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[9] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[11] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[16] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[22] -= cxtype( 0, 1 ) * amp_sv[0];
      VVV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[15], w_fp[1], w_fp[7], COUPs[0], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[5] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[7] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[8] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[9] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[10] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[13] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[16] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[19] -= cxtype( 0, 1 ) * amp_sv[0];
      VVV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[13], w_fp[1], w_fp[7], COUPs[0], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[3] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[6] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[8] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[10] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[11] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[13] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[19] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[22] += cxtype( 0, 1 ) * amp_sv[0];

      // *** DIAGRAM 123 OF 123 ***

      // Wavefunction(s) for diagram number 123
      // (none)

      // Amplitude(s) for diagram number 123
      VVV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[0], w_fp[17], w_fp[7], COUPs[0], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[0] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[1] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[3] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[5] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[9] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[11] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[17] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[23] += cxtype( 0, 1 ) * amp_sv[0];
      VVV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[0], w_fp[19], w_fp[7], COUPs[0], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[1] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[2] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[3] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[4] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[11] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[15] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[17] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[21] += cxtype( 0, 1 ) * amp_sv[0];
      VVV1_0<W_ACCESS, A_ACCESS, CD_ACCESS>( w_fp[0], w_fp[8], w_fp[7], COUPs[0], 1.0, &amp_fp[0] );
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      // Here the code base generated with multichannel support updates numerators_sv and denominators_sv (#473)
#endif
      jamp_sv[0] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[2] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[4] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[5] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[9] -= cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[15] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[21] += cxtype( 0, 1 ) * amp_sv[0];
      jamp_sv[23] -= cxtype( 0, 1 ) * amp_sv[0];

      /*
#if not defined MGONGPUCPP_GPUIMPL and defined MGONGPU_FPTYPE2_FLOAT
      // Avoid underflow FPE #831 for jamp (flush-to-zero jamp values whose square is below FLT_MIN)
      constexpr fptype2 minjamp = 1.1 * constexpr_sqrt( FLT_MIN );
      auto underflowFTZ = [&jamp_sv]()
      {
        for( int icolC = 0; icolC < ncolor; icolC++ )
        {
#ifndef MGONGPU_CPPSIMD
          jamp_sv[icolC] = cxtype( cxreal( jamp_sv[icolC] ) * ( std::abs( cxreal( jamp_sv[icolC] ) ) > minjamp ),
                                   cximag( jamp_sv[icolC] ) * ( std::abs( cximag( jamp_sv[icolC] ) ) > minjamp ) );
#else
          for( int i = 0; i < neppV; i++ )
            jamp_sv[icolC][i] = cxtype( cxreal( jamp_sv[icolC][i] ) * ( std::abs( cxreal( jamp_sv[icolC][i] ) ) > minjamp ),
                                        cximag( jamp_sv[icolC][i] ) * ( std::abs( cximag( jamp_sv[icolC][i] ) ) > minjamp ) );
#endif
        }
      };
#endif

#ifndef MGONGPUCPP_GPUIMPL
#ifdef MGONGPU_FPTYPE_FLOAT
      // Fix FPE #831 for FPTYPE=f (scalar and vector)
      underflowFTZ();
#endif
#endif
      */

      // *** COLOR CHOICE BELOW ***
      // Store the leading color flows for choice of color
      if( jamp2_sv ) // disable color choice if nullptr
        for( int icolC = 0; icolC < ncolor; icolC++ )
          jamp2_sv[ncolor * iParity + icolC] += cxabs2( jamp_sv[icolC] );

      // *** COLOR MATRIX BELOW ***
      // (This method used to be called CPPProcess::matrix_1_gg_ttxgg()?)

      // The color denominators (initialize all array elements, with ncolor=24)
      // [NB do keep 'static' for these constexpr arrays, see issue #283]
      static constexpr fptype2 denom[ncolor] = { 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54, 54 }; // 1-D array[24]

      // The color matrix (initialize all array elements, with ncolor=24)
      // [NB do keep 'static' for these constexpr arrays, see issue #283]
      static constexpr fptype2 cf[ncolor][ncolor] = {
        { 512, -64, -64, 8, 8, 80, -64, 8, 8, -1, -1, -10, 8, -1, 80, -10, 71, 62, -1, -10, -10, 62, 62, -28 },
        { -64, 512, 8, 80, -64, 8, 8, -64, -1, -10, 8, -1, -1, -10, -10, 62, 62, -28, 8, -1, 80, -10, 71, 62 },
        { -64, 8, 512, -64, 80, 8, 8, -1, 80, -10, 71, 62, -64, 8, 8, -1, -1, -10, -10, -1, 62, -28, -10, 62 },
        { 8, 80, -64, 512, 8, -64, -1, -10, -10, 62, 62, -28, 8, -64, -1, -10, 8, -1, -1, 8, 71, 62, 80, -10 },
        { 8, -64, 80, 8, 512, -64, -1, 8, 71, 62, 80, -10, -10, -1, 62, -28, -10, 62, -64, 8, 8, -1, -1, -10 },
        { 80, 8, 8, -64, -64, 512, -10, -1, 62, -28, -10, 62, -1, 8, 71, 62, 80, -10, 8, -64, -1, -10, 8, -1 },
        { -64, 8, 8, -1, -1, -10, 512, -64, -64, 8, 8, 80, 80, -10, 8, -1, 62, 71, -10, 62, -1, -10, -28, 62 },
        { 8, -64, -1, -10, 8, -1, -64, 512, 8, 80, -64, 8, -10, 62, -1, -10, -28, 62, 80, -10, 8, -1, 62, 71 },
        { 8, -1, 80, -10, 71, 62, -64, 8, 512, -64, 80, 8, 8, -1, -64, 8, -10, -1, 62, -28, -10, -1, 62, -10 },
        { -1, -10, -10, 62, 62, -28, 8, 80, -64, 512, 8, -64, -1, -10, 8, -64, -1, 8, 71, 62, -1, 8, -10, 80 },
        { -1, 8, 71, 62, 80, -10, 8, -64, 80, 8, 512, -64, 62, -28, -10, -1, 62, -10, 8, -1, -64, 8, -10, -1 },
        { -10, -1, 62, -28, -10, 62, 80, 8, 8, -64, -64, 512, 71, 62, -1, 8, -10, 80, -1, -10, 8, -64, -1, 8 },
        { 8, -1, -64, 8, -10, -1, 80, -10, 8, -1, 62, 71, 512, -64, -64, 8, 8, 80, 62, -10, -28, 62, -1, -10 },
        { -1, -10, 8, -64, -1, 8, -10, 62, -1, -10, -28, 62, -64, 512, 8, 80, -64, 8, -10, 80, 62, 71, 8, -1 },
        { 80, -10, 8, -1, 62, 71, 8, -1, -64, 8, -10, -1, -64, 8, 512, -64, 80, 8, -28, 62, 62, -10, -10, -1 },
        { -10, 62, -1, -10, -28, 62, -1, -10, 8, -64, -1, 8, 8, 80, -64, 512, 8, -64, 62, 71, -10, 80, -1, 8 },
        { 71, 62, -1, 8, -10, 80, 62, -28, -10, -1, 62, -10, 8, -64, 80, 8, 512, -64, -1, 8, -10, -1, -64, 8 },
        { 62, -28, -10, -1, 62, -10, 71, 62, -1, 8, -10, 80, 80, 8, 8, -64, -64, 512, -10, -1, -1, 8, 8, -64 },
        { -1, 8, -10, -1, -64, 8, -10, 80, 62, 71, 8, -1, 62, -10, -28, 62, -1, -10, 512, -64, -64, 8, 8, 80 },
        { -10, -1, -1, 8, 8, -64, 62, -10, -28, 62, -1, -10, -10, 80, 62, 71, 8, -1, -64, 512, 8, 80, -64, 8 },
        { -10, 80, 62, 71, 8, -1, -1, 8, -10, -1, -64, 8, -28, 62, 62, -10, -10, -1, -64, 8, 512, -64, 80, 8 },
        { 62, -10, -28, 62, -1, -10, -10, -1, -1, 8, 8, -64, 62, 71, -10, 80, -1, 8, 8, 80, -64, 512, 8, -64 },
        { 62, 71, -10, 80, -1, 8, -28, 62, 62, -10, -10, -1, -1, 8, -10, -1, -64, 8, 8, -64, 80, 8, 512, -64 },
        { -28, 62, 62, -10, -10, -1, 62, 71, -10, 80, -1, 8, -10, -1, -1, 8, 8, -64, 80, 8, 8, -64, -64, 512 } }; // 2-D array[24][24]

#ifndef MGONGPUCPP_GPUIMPL
      // Pre-compute a constexpr triangular color matrix properly normalized #475
      struct TriangularNormalizedColorMatrix
      {
        // See https://stackoverflow.com/a/34465458
        __host__ __device__ constexpr TriangularNormalizedColorMatrix()
          : value()
        {
          for( int icol = 0; icol < ncolor; icol++ )
          {
            // Diagonal terms
            value[icol][icol] = cf[icol][icol] / denom[icol];
            // Off-diagonal terms
            for( int jcol = icol + 1; jcol < ncolor; jcol++ )
              value[icol][jcol] = 2 * cf[icol][jcol] / denom[icol];
          }
        }
        fptype2 value[ncolor][ncolor];
      };
      static constexpr auto cf2 = TriangularNormalizedColorMatrix();
#endif

      /*
#ifndef MGONGPUCPP_GPUIMPL
#if defined MGONGPU_FPTYPE_DOUBLE and defined MGONGPU_FPTYPE2_FLOAT
      // Fix FPE #831 for FPTYPE=m (scalar and vector)
      underflowFTZ();
#endif
#endif
      */

#if defined MGONGPU_CPPSIMD and defined MGONGPU_FPTYPE_DOUBLE and defined MGONGPU_FPTYPE2_FLOAT
      if( iParity == 0 ) // NB: first page is 0! skip even pages, compute on odd pages
      {
        // Mixed fptypes: delay color algebra and ME updates to next (odd) ipagV
        for( int icol = 0; icol < ncolor; icol++ )
          jamp_sv_previous[icol] = jamp_sv[icol];
        MEs_previous = MEs;
        continue; // go to next iParity in the loop: skip color algebra and ME update on odd pages
      }
      fptype_sv deltaMEs_previous = { 0 };
#endif

      // Sum and square the color flows to get the matrix element
      // (compute |M|^2 by squaring |M|, taking into account colours)
      // Sum and square the color flows to get the matrix element
      // (compute |M|^2 by squaring |M|, taking into account colours)
      fptype_sv deltaMEs = { 0 }; // all zeros https://en.cppreference.com/w/c/language/array_initialization#Notes

      // Use the property that M is a real matrix (see #475):
      // we can rewrite the quadratic form (A-iB)(M)(A+iB) as AMA - iBMA + iBMA + BMB = AMA + BMB
      // In addition, on C++ use the property that M is symmetric (see #475),
      // and also use constexpr to compute "2*" and "/denom[icol]" once and for all at compile time:
      // we gain (not a factor 2...) in speed here as we only loop over the up diagonal part of the matrix.
      // Strangely, CUDA is slower instead, so keep the old implementation for the moment.
#if defined MGONGPU_CPPSIMD and defined MGONGPU_FPTYPE_DOUBLE and defined MGONGPU_FPTYPE2_FLOAT
      fptype2_sv jampR_sv[ncolor] = { 0 };
      fptype2_sv jampI_sv[ncolor] = { 0 };
      for( int icol = 0; icol < ncolor; icol++ )
      {
        jampR_sv[icol] = fpvmerge( cxreal( jamp_sv_previous[icol] ), cxreal( jamp_sv[icol] ) );
        jampI_sv[icol] = fpvmerge( cximag( jamp_sv_previous[icol] ), cximag( jamp_sv[icol] ) );
      }
#endif
      for( int icol = 0; icol < ncolor; icol++ )
      {
        //if( debug ) printf( "calculate_wavefunctions... icol=%d\n", icol );
#ifndef MGONGPUCPP_GPUIMPL
        // === C++ START ===
        // Diagonal terms
#if defined MGONGPU_CPPSIMD and defined MGONGPU_FPTYPE_DOUBLE and defined MGONGPU_FPTYPE2_FLOAT
        fptype2_sv& jampRi_sv = jampR_sv[icol];
        fptype2_sv& jampIi_sv = jampI_sv[icol];
#else
        fptype2_sv jampRi_sv = (fptype2_sv)( cxreal( jamp_sv[icol] ) );
        fptype2_sv jampIi_sv = (fptype2_sv)( cximag( jamp_sv[icol] ) );
#endif
        fptype2_sv ztempR_sv = cf2.value[icol][icol] * jampRi_sv;
        fptype2_sv ztempI_sv = cf2.value[icol][icol] * jampIi_sv;
        // Off-diagonal terms
        for( int jcol = icol + 1; jcol < ncolor; jcol++ )
        {
#if defined MGONGPU_CPPSIMD and defined MGONGPU_FPTYPE_DOUBLE and defined MGONGPU_FPTYPE2_FLOAT
          fptype2_sv& jampRj_sv = jampR_sv[jcol];
          fptype2_sv& jampIj_sv = jampI_sv[jcol];
#else
          fptype2_sv jampRj_sv = (fptype2_sv)( cxreal( jamp_sv[jcol] ) );
          fptype2_sv jampIj_sv = (fptype2_sv)( cximag( jamp_sv[jcol] ) );
#endif
          ztempR_sv += cf2.value[icol][jcol] * jampRj_sv;
          ztempI_sv += cf2.value[icol][jcol] * jampIj_sv;
        }
        /*
#if not defined MGONGPUCPP_GPUIMPL and defined MGONGPU_FPTYPE2_FLOAT
        // Avoid underflow FPE #831 for ztemp (flush-to-zero ztemp values whose square is below FLT_MIN)
#ifndef MGONGPU_CPPSIMD
        ztempR_sv *= ( std::abs( ztempR_sv ) > minjamp );
        ztempI_sv *= ( std::abs( ztempI_sv ) > minjamp );
#else
#ifndef MGONGPU_FPTYPE_DOUBLE // clang-format off
        constexpr int neppV_ztemp = neppV; // FPTYPE=f
#else
        constexpr int neppV_ztemp = neppV2; // FPTYPE=m
#endif // clang-format on
        for( int i = 0; i < neppV_ztemp; i++ ) // NB! This may be either neppV (FPTYPE=f) or neppV2=2*neppV (FPTYPE=m)!
        {
          ztempR_sv[i] *= ( std::abs( ztempR_sv[i] ) > minjamp );
          ztempI_sv[i] *= ( std::abs( ztempI_sv[i] ) > minjamp );
        }
#endif
#endif
        */
        fptype2_sv deltaMEs2 = ( jampRi_sv * ztempR_sv + jampIi_sv * ztempI_sv );
#if defined MGONGPU_CPPSIMD and defined MGONGPU_FPTYPE_DOUBLE and defined MGONGPU_FPTYPE2_FLOAT
        deltaMEs_previous += fpvsplit0( deltaMEs2 );
        deltaMEs += fpvsplit1( deltaMEs2 );
#else
        deltaMEs += deltaMEs2;
#endif
        // === C++ END ===
#else
        // === CUDA START ===
        fptype2_sv ztempR_sv = { 0 };
        fptype2_sv ztempI_sv = { 0 };
        for( int jcol = 0; jcol < ncolor; jcol++ )
        {
          fptype2_sv jampRj_sv = cxreal( jamp_sv[jcol] );
          fptype2_sv jampIj_sv = cximag( jamp_sv[jcol] );
          ztempR_sv += cf[icol][jcol] * jampRj_sv;
          ztempI_sv += cf[icol][jcol] * jampIj_sv;
        }
        deltaMEs += ( ztempR_sv * cxreal( jamp_sv[icol] ) + ztempI_sv * cximag( jamp_sv[icol] ) ) / denom[icol];
        // === CUDA END ===
#endif
      }

      // *** STORE THE RESULTS ***

      // NB: calculate_wavefunctions ADDS |M|^2 for a given ihel to the running sum of |M|^2 over helicities for the given event(s)
      fptype_sv& MEs_sv = E_ACCESS::kernelAccess( MEs );
      MEs_sv += deltaMEs; // fix #435
#if defined MGONGPU_CPPSIMD and defined MGONGPU_FPTYPE_DOUBLE and defined MGONGPU_FPTYPE2_FLOAT
      fptype_sv& MEs_sv_previous = E_ACCESS::kernelAccess( MEs_previous );
      MEs_sv_previous += deltaMEs_previous;
#endif
      /*
#ifdef MGONGPUCPP_GPUIMPL
      if ( cNGoodHel > 0 ) printf( "calculate_wavefunctions: ievt=%6d ihel=%2d me_running=%f\n", blockDim.x * blockIdx.x + threadIdx.x, ihel, MEs_sv );
#else
#ifdef MGONGPU_CPPSIMD
      if( cNGoodHel > 0 )
        for( int ieppV = 0; ieppV < neppV; ieppV++ )
          printf( "calculate_wavefunctions: ievt=%6d ihel=%2d me_running=%f\n", ievt0 + ieppV, ihel, MEs_sv[ieppV] );
#else
      if ( cNGoodHel > 0 ) printf( "calculate_wavefunctions: ievt=%6d ihel=%2d me_running=%f\n", ievt0, ihel, MEs_sv );
#endif
#endif
      */
    } // END LOOP ON IPARITY
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  CPPProcess::CPPProcess( bool verbose,
                          bool debug )
    : m_verbose( verbose )
    , m_debug( debug )
#ifndef MGONGPU_HARDCODE_PARAM
    , m_pars( 0 )
#endif
    , m_masses()
  {
    // Helicities for the process [NB do keep 'static' for this constexpr array, see issue #283]
    // *** NB There is no automatic check yet that these are in the same order as Fortran! #569 ***
    static constexpr short tHel[ncomb][npar] = {
      { -1, -1, -1, 1, -1, -1 },
      { -1, -1, -1, 1, -1, 1 },
      { -1, -1, -1, 1, 1, -1 },
      { -1, -1, -1, 1, 1, 1 },
      { -1, -1, -1, -1, -1, -1 },
      { -1, -1, -1, -1, -1, 1 },
      { -1, -1, -1, -1, 1, -1 },
      { -1, -1, -1, -1, 1, 1 },
      { -1, -1, 1, 1, -1, -1 },
      { -1, -1, 1, 1, -1, 1 },
      { -1, -1, 1, 1, 1, -1 },
      { -1, -1, 1, 1, 1, 1 },
      { -1, -1, 1, -1, -1, -1 },
      { -1, -1, 1, -1, -1, 1 },
      { -1, -1, 1, -1, 1, -1 },
      { -1, -1, 1, -1, 1, 1 },
      { -1, 1, -1, 1, -1, -1 },
      { -1, 1, -1, 1, -1, 1 },
      { -1, 1, -1, 1, 1, -1 },
      { -1, 1, -1, 1, 1, 1 },
      { -1, 1, -1, -1, -1, -1 },
      { -1, 1, -1, -1, -1, 1 },
      { -1, 1, -1, -1, 1, -1 },
      { -1, 1, -1, -1, 1, 1 },
      { -1, 1, 1, 1, -1, -1 },
      { -1, 1, 1, 1, -1, 1 },
      { -1, 1, 1, 1, 1, -1 },
      { -1, 1, 1, 1, 1, 1 },
      { -1, 1, 1, -1, -1, -1 },
      { -1, 1, 1, -1, -1, 1 },
      { -1, 1, 1, -1, 1, -1 },
      { -1, 1, 1, -1, 1, 1 },
      { 1, -1, -1, 1, -1, -1 },
      { 1, -1, -1, 1, -1, 1 },
      { 1, -1, -1, 1, 1, -1 },
      { 1, -1, -1, 1, 1, 1 },
      { 1, -1, -1, -1, -1, -1 },
      { 1, -1, -1, -1, -1, 1 },
      { 1, -1, -1, -1, 1, -1 },
      { 1, -1, -1, -1, 1, 1 },
      { 1, -1, 1, 1, -1, -1 },
      { 1, -1, 1, 1, -1, 1 },
      { 1, -1, 1, 1, 1, -1 },
      { 1, -1, 1, 1, 1, 1 },
      { 1, -1, 1, -1, -1, -1 },
      { 1, -1, 1, -1, -1, 1 },
      { 1, -1, 1, -1, 1, -1 },
      { 1, -1, 1, -1, 1, 1 },
      { 1, 1, -1, 1, -1, -1 },
      { 1, 1, -1, 1, -1, 1 },
      { 1, 1, -1, 1, 1, -1 },
      { 1, 1, -1, 1, 1, 1 },
      { 1, 1, -1, -1, -1, -1 },
      { 1, 1, -1, -1, -1, 1 },
      { 1, 1, -1, -1, 1, -1 },
      { 1, 1, -1, -1, 1, 1 },
      { 1, 1, 1, 1, -1, -1 },
      { 1, 1, 1, 1, -1, 1 },
      { 1, 1, 1, 1, 1, -1 },
      { 1, 1, 1, 1, 1, 1 },
      { 1, 1, 1, -1, -1, -1 },
      { 1, 1, 1, -1, -1, 1 },
      { 1, 1, 1, -1, 1, -1 },
      { 1, 1, 1, -1, 1, 1 } };
#ifdef MGONGPUCPP_GPUIMPL
    gpuMemcpyToSymbol( cHel, tHel, ncomb * npar * sizeof( short ) );
#else
    memcpy( cHel, tHel, ncomb * npar * sizeof( short ) );
#endif
    fpeEnable(); // enable SIGFPE traps for Floating Point Exceptions
  }

  //--------------------------------------------------------------------------

  CPPProcess::~CPPProcess() {}

  //--------------------------------------------------------------------------

#ifndef MGONGPU_HARDCODE_PARAM
  // Initialize process (with parameters read from user cards)
  void
  CPPProcess::initProc( const std::string& param_card_name )
  {
    // Instantiate the model class and set parameters that stay fixed during run
    m_pars = Parameters_sm::getInstance();
    SLHAReader slha( param_card_name, m_verbose );
    m_pars->setIndependentParameters( slha );
    m_pars->setIndependentCouplings();
    //m_pars->setDependentParameters(); // now computed event-by-event (running alphas #373)
    //m_pars->setDependentCouplings(); // now computed event-by-event (running alphas #373)
    if( m_verbose )
    {
      m_pars->printIndependentParameters();
      m_pars->printIndependentCouplings();
      //m_pars->printDependentParameters(); // now computed event-by-event (running alphas #373)
      //m_pars->printDependentCouplings(); // now computed event-by-event (running alphas #373)
    }
    // Set external particle masses for this matrix element
    m_masses.push_back( m_pars->ZERO );
    m_masses.push_back( m_pars->ZERO );
    m_masses.push_back( m_pars->mdl_MT );
    m_masses.push_back( m_pars->mdl_MT );
    m_masses.push_back( m_pars->ZERO );
    m_masses.push_back( m_pars->ZERO );
    // Read physics parameters like masses and couplings from user configuration files (static: initialize once)
    // Then copy them to CUDA constant memory (issue #39) or its C++ emulation in file-scope static memory
    const fptype tIPD[nIPD] = { (fptype)m_pars->mdl_MT, (fptype)m_pars->mdl_WT };
    //const cxtype tIPC[0] = { ... }; // nIPC=0
#ifdef MGONGPUCPP_GPUIMPL
    gpuMemcpyToSymbol( cIPD, tIPD, nIPD * sizeof( fptype ) );
    //gpuMemcpyToSymbol( cIPC, tIPC, 0 * sizeof( cxtype ) ); // nIPC=0
#ifdef MGONGPUCPP_NBSMINDEPPARAM_GT_0
    if( Parameters_sm::nBsmIndepParam > 0 )
      gpuMemcpyToSymbol( bsmIndepParam, m_pars->mdl_bsmIndepParam, Parameters_sm::nBsmIndepParam * sizeof( double ) );
#endif
#else
    memcpy( cIPD, tIPD, nIPD * sizeof( fptype ) );
    //memcpy( cIPC, tIPC, nIPC * sizeof( cxtype ) ); // nIPC=0
#ifdef MGONGPUCPP_NBSMINDEPPARAM_GT_0
    if( Parameters_sm::nBsmIndepParam > 0 )
      memcpy( bsmIndepParam, m_pars->mdl_bsmIndepParam, Parameters_sm::nBsmIndepParam * sizeof( double ) );
#endif
#endif
    //for ( int i=0; i<nIPD; i++ ) std::cout << std::setprecision(17) << "tIPD[i] = " << tIPD[i] << std::endl;
    //for ( int i=0; i<Parameters_sm::nBsmIndepParam; i++ ) std::cout << std::setprecision(17) << "m_pars->mdl_bsmIndepParam[i] = " << m_pars->mdl_bsmIndepParam[i] << std::endl;
  }
#else
  // Initialize process (with hardcoded parameters)
  void
  CPPProcess::initProc( const std::string& /*param_card_name*/ )
  {
    // Use hardcoded physics parameters
    if( m_verbose )
    {
      Parameters_sm::printIndependentParameters();
      Parameters_sm::printIndependentCouplings();
      //Parameters_sm::printDependentParameters(); // now computed event-by-event (running alphas #373)
      //Parameters_sm::printDependentCouplings(); // now computed event-by-event (running alphas #373)
    }
    // Set external particle masses for this matrix element
    m_masses.push_back( Parameters_sm::ZERO );
    m_masses.push_back( Parameters_sm::ZERO );
    m_masses.push_back( Parameters_sm::mdl_MT );
    m_masses.push_back( Parameters_sm::mdl_MT );
    m_masses.push_back( Parameters_sm::ZERO );
    m_masses.push_back( Parameters_sm::ZERO );
  }
#endif

  //--------------------------------------------------------------------------

  // Retrieve the compiler that was used to build this module
  const std::string
  CPPProcess::getCompiler()
  {
    std::stringstream out;
    // CUDA version (NVCC)
    // [Use __NVCC__ instead of MGONGPUCPP_GPUIMPL here!]
    // [This tests if 'nvcc' was used even to build a .cc file, even if not necessarily 'nvcc -x cu' for a .cu file]
    // [Check 'nvcc --compiler-options -dM -E dummy.c | grep CUDA': see https://stackoverflow.com/a/53713712]
#ifdef __NVCC__
#if defined __CUDACC_VER_MAJOR__ && defined __CUDACC_VER_MINOR__ && defined __CUDACC_VER_BUILD__
    out << "nvcc " << __CUDACC_VER_MAJOR__ << "." << __CUDACC_VER_MINOR__ << "." << __CUDACC_VER_BUILD__;
#else
    out << "nvcc UNKNOWN";
#endif
    out << " (";
#endif
    // ICX version (either as CXX or as host compiler inside NVCC)
#if defined __INTEL_COMPILER
#error "icc is no longer supported: please use icx"
#elif defined __INTEL_LLVM_COMPILER // alternative: __INTEL_CLANG_COMPILER
    out << "icx " << __INTEL_LLVM_COMPILER;
#ifdef __NVCC__
    out << ", ";
#else
    out << " (";
#endif
#endif
    // CLANG version (either as CXX or as host compiler inside NVCC or inside ICX)
#if defined __clang__
#if defined __clang_major__ && defined __clang_minor__ && defined __clang_patchlevel__
#ifdef __APPLE__
    out << "Apple clang " << __clang_major__ << "." << __clang_minor__ << "." << __clang_patchlevel__;
#else
    out << "clang " << __clang_major__ << "." << __clang_minor__ << "." << __clang_patchlevel__;
    /*
    // === AV 26-Jan-2024 DISABLE THIS CODE (START)
    // === AV 26-Jan-2024 First, it is totally wrong to assume that the CXX environment variable is used in the build!
    // === AV 26-Jan-2024 Second and worse, here we need build time values, while CXX in this code is evaluated at runtime!
    // GCC toolchain version inside CLANG
    std::string tchainout;
    std::string tchaincmd = "readelf -p .comment $(${CXX} -print-libgcc-file-name) |& grep 'GCC: (GNU)' | grep -v Warning | sort -u | awk '{print $5}'";
    std::unique_ptr<FILE, decltype( &pclose )> tchainpipe( popen( tchaincmd.c_str(), "r" ), pclose );
    if( !tchainpipe ) throw std::runtime_error( "`readelf ...` failed?" );
    std::array<char, 128> tchainbuf;
    while( fgets( tchainbuf.data(), tchainbuf.size(), tchainpipe.get() ) != nullptr ) tchainout += tchainbuf.data();
    tchainout.pop_back(); // remove trailing newline
#if defined __NVCC__ or defined __INTEL_LLVM_COMPILER
    out << ", gcc " << tchainout;
#else
    out << " (gcc " << tchainout << ")";
#endif
    // === AV 26-Jan-2024 DISABLE THIS CODE (END)
    */
#endif
#else
    out << "clang UNKNOWKN";
#endif
#else
    // GCC version (either as CXX or as host compiler inside NVCC)
#if defined __GNUC__ && defined __GNUC_MINOR__ && defined __GNUC_PATCHLEVEL__
    out << "gcc " << __GNUC__ << "." << __GNUC_MINOR__ << "." << __GNUC_PATCHLEVEL__;
#else
    out << "gcc UNKNOWKN";
#endif
#endif
#if defined __NVCC__ or defined __INTEL_LLVM_COMPILER
    out << ")";
#endif
    return out.str();
  }

  //--------------------------------------------------------------------------

  __global__ void /* clang-format off */
  computeDependentCouplings( const fptype* allgs, // input: Gs[nevt]
                             fptype* allcouplings // output: couplings[nevt*ndcoup*2]
#ifndef MGONGPUCPP_GPUIMPL
                             , const int nevt     // input: #events (for cuda: nevt == ndim == gpublocks*gputhreads)
#endif
  ) /* clang-format on */
  {
#ifdef MGONGPUCPP_GPUIMPL
    using namespace mg5amcGpu;
    using G_ACCESS = DeviceAccessGs;
    using C_ACCESS = DeviceAccessCouplings;
    G2COUP<G_ACCESS, C_ACCESS>( allgs, allcouplings, bsmIndepParam );
#else
    using namespace mg5amcCpu;
    using G_ACCESS = HostAccessGs;
    using C_ACCESS = HostAccessCouplings;
    for( int ipagV = 0; ipagV < nevt / neppV; ++ipagV )
    {
      const int ievt0 = ipagV * neppV;
      const fptype* gs = MemoryAccessGs::ieventAccessRecordConst( allgs, ievt0 );
      fptype* couplings = MemoryAccessCouplings::ieventAccessRecord( allcouplings, ievt0 );
      G2COUP<G_ACCESS, C_ACCESS>( gs, couplings, bsmIndepParam );
    }
#endif
  }

  //--------------------------------------------------------------------------

#ifdef MGONGPUCPP_GPUIMPL /* clang-format off */
  __global__ void
  sigmaKin_getGoodHel( const fptype* allmomenta,   // input: momenta[nevt*npar*4]
                       const fptype* allcouplings, // input: couplings[nevt*ndcoup*2]
                       fptype* allMEs,             // output: allMEs[nevt], |M|^2 final_avg_over_helicities
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
                       fptype* allNumerators,      // output: multichannel numerators[nevt], running_sum_over_helicities
                       fptype* allDenominators,    // output: multichannel denominators[nevt], running_sum_over_helicities
#endif
                       bool* isGoodHel )           // output: isGoodHel[ncomb] - device array (CUDA implementation)
  {                                                         /* clang-format on */
    const int ievt = blockDim.x * blockIdx.x + threadIdx.x; // index of event (thread) in grid
    for( int ihel = 0; ihel < ncomb; ihel++ )
    {
      // NEW IMPLEMENTATION OF GETGOODHEL (#630): RESET THE RUNNING SUM OVER HELICITIES TO 0 BEFORE ADDING A NEW HELICITY
      allMEs[ievt] = 0;
      // NB: calculate_wavefunctions ADDS |M|^2 for a given ihel to the running sum of |M|^2 over helicities for the given event(s)
      constexpr fptype_sv* jamp2_sv = nullptr; // no need for color selection during helicity filtering
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      constexpr unsigned int channelId = 0; // disable single-diagram channel enhancement
      calculate_wavefunctions( ihel, allmomenta, allcouplings, allMEs, channelId, allNumerators, allDenominators, jamp2_sv );
#else
      calculate_wavefunctions( ihel, allmomenta, allcouplings, allMEs, jamp2_sv );
#endif
      if( allMEs[ievt] != 0 ) // NEW IMPLEMENTATION OF GETGOODHEL (#630): COMPARE EACH HELICITY CONTRIBUTION TO 0
      {
        //if ( !isGoodHel[ihel] ) std::cout << "sigmaKin_getGoodHel ihel=" << ihel << " TRUE" << std::endl;
        isGoodHel[ihel] = true;
      }
    }
  }
#else
  void
  sigmaKin_getGoodHel( const fptype* allmomenta,   // input: momenta[nevt*npar*4]
                       const fptype* allcouplings, // input: couplings[nevt*ndcoup*2]
                       fptype* allMEs,             // output: allMEs[nevt], |M|^2 final_avg_over_helicities
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
                       fptype* allNumerators,      // output: multichannel numerators[nevt], running_sum_over_helicities
                       fptype* allDenominators,    // output: multichannel denominators[nevt], running_sum_over_helicities
#endif
                       bool* isGoodHel,            // output: isGoodHel[ncomb] - host array (C++ implementation)
                       const int nevt )            // input: #events (for cuda: nevt == ndim == gpublocks*gputhreads)
  {
    //assert( (size_t)(allmomenta) % mgOnGpu::cppAlign == 0 ); // SANITY CHECK: require SIMD-friendly alignment [COMMENT OUT TO TEST MISALIGNED ACCESS]
    //assert( (size_t)(allMEs) % mgOnGpu::cppAlign == 0 ); // SANITY CHECK: require SIMD-friendly alignment [COMMENT OUT TO TEST MISALIGNED ACCESS]
    // Allocate arrays at build time to contain at least 16 events (or at least neppV events if neppV>16, e.g. in future VPUs)
    constexpr int maxtry0 = std::max( 16, neppV ); // 16, but at least neppV (otherwise the npagV loop does not even start)
    // Loop over only nevt events if nevt is < 16 (note that nevt is always >= neppV)
    assert( nevt >= neppV );
    const int maxtry = std::min( maxtry0, nevt ); // 16, but at most nevt (avoid invalid memory access if nevt<maxtry0)

    // HELICITY LOOP: CALCULATE WAVEFUNCTIONS
    const int npagV = maxtry / neppV;
#if defined MGONGPU_CPPSIMD and defined MGONGPU_FPTYPE_DOUBLE and defined MGONGPU_FPTYPE2_FLOAT
    // Mixed fptypes #537: float for color algebra and double elsewhere
    // Delay color algebra and ME updates (only on even pages)
    assert( npagV % 2 == 0 );     // SANITY CHECK for mixed fptypes: two neppV-pages are merged to one 2*neppV-page
    const int npagV2 = npagV / 2; // loop on two SIMD pages (neppV events) at a time
#else
    const int npagV2 = npagV;            // loop on one SIMD page (neppV events) at a time
#endif
    for( int ipagV2 = 0; ipagV2 < npagV2; ++ipagV2 )
    {
#if defined MGONGPU_CPPSIMD and defined MGONGPU_FPTYPE_DOUBLE and defined MGONGPU_FPTYPE2_FLOAT
      const int ievt00 = ipagV2 * neppV * 2; // loop on two SIMD pages (neppV events) at a time
#else
      const int ievt00 = ipagV2 * neppV; // loop on one SIMD page (neppV events) at a time
#endif
      for( int ihel = 0; ihel < ncomb; ihel++ )
      {
        // NEW IMPLEMENTATION OF GETGOODHEL (#630): RESET THE RUNNING SUM OVER HELICITIES TO 0 BEFORE ADDING A NEW HELICITY
        for( int ieppV = 0; ieppV < neppV; ++ieppV )
        {
          const int ievt = ievt00 + ieppV;
          allMEs[ievt] = 0;
#if defined MGONGPU_CPPSIMD and defined MGONGPU_FPTYPE_DOUBLE and defined MGONGPU_FPTYPE2_FLOAT
          const int ievt2 = ievt00 + ieppV + neppV;
          allMEs[ievt2] = 0;
#endif
        }
        constexpr fptype_sv* jamp2_sv = nullptr; // no need for color selection during helicity filtering
        //std::cout << "sigmaKin_getGoodHel ihel=" << ihel << ( isGoodHel[ihel] ? " true" : " false" ) << std::endl;
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
        constexpr unsigned int channelId = 0; // disable single-diagram channel enhancement
        calculate_wavefunctions( ihel, allmomenta, allcouplings, allMEs, channelId, allNumerators, allDenominators, jamp2_sv, ievt00 );
#else
        calculate_wavefunctions( ihel, allmomenta, allcouplings, allMEs, jamp2_sv, ievt00 );
#endif
        for( int ieppV = 0; ieppV < neppV; ++ieppV )
        {
          const int ievt = ievt00 + ieppV;
          if( allMEs[ievt] != 0 ) // NEW IMPLEMENTATION OF GETGOODHEL (#630): COMPARE EACH HELICITY CONTRIBUTION TO 0
          {
            //if ( !isGoodHel[ihel] ) std::cout << "sigmaKin_getGoodHel ihel=" << ihel << " TRUE" << std::endl;
            isGoodHel[ihel] = true;
          }
#if defined MGONGPU_CPPSIMD and defined MGONGPU_FPTYPE_DOUBLE and defined MGONGPU_FPTYPE2_FLOAT
          const int ievt2 = ievt00 + ieppV + neppV;
          if( allMEs[ievt2] != 0 ) // NEW IMPLEMENTATION OF GETGOODHEL (#630): COMPARE EACH HELICITY CONTRIBUTION TO 0
          {
            //if ( !isGoodHel[ihel] ) std::cout << "sigmaKin_getGoodHel ihel=" << ihel << " TRUE" << std::endl;
            isGoodHel[ihel] = true;
          }
#endif
        }
      }
    }
  }
#endif

  //--------------------------------------------------------------------------

  int                                          // output: nGoodHel (the number of good helicity combinations out of ncomb)
  sigmaKin_setGoodHel( const bool* isGoodHel ) // input: isGoodHel[ncomb] - host array (CUDA and C++)
  {
    int nGoodHel = 0;
    int goodHel[ncomb] = { 0 }; // all zeros https://en.cppreference.com/w/c/language/array_initialization#Notes
    for( int ihel = 0; ihel < ncomb; ihel++ )
    {
      //std::cout << "sigmaKin_setGoodHel ihel=" << ihel << ( isGoodHel[ihel] ? " true" : " false" ) << std::endl;
      if( isGoodHel[ihel] )
      {
        goodHel[nGoodHel] = ihel;
        nGoodHel++;
      }
    }
#ifdef MGONGPUCPP_GPUIMPL
    gpuMemcpyToSymbol( cNGoodHel, &nGoodHel, sizeof( int ) );
    gpuMemcpyToSymbol( cGoodHel, goodHel, ncomb * sizeof( int ) );
#else
    cNGoodHel = nGoodHel;
    for( int ihel = 0; ihel < ncomb; ihel++ ) cGoodHel[ihel] = goodHel[ihel];
#endif
    return nGoodHel;
  }

  //--------------------------------------------------------------------------
  // Evaluate |M|^2, part independent of incoming flavour

  __global__ void /* clang-format off */
  sigmaKin( const fptype* allmomenta,      // input: momenta[nevt*npar*4]
            const fptype* allcouplings,    // input: couplings[nevt*ndcoup*2]
            const fptype* allrndhel,       // input: random numbers[nevt] for helicity selection
            const fptype* allrndcol,       // input: random numbers[nevt] for color selection
            fptype* allMEs,                // output: allMEs[nevt], |M|^2 final_avg_over_helicities
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
            const unsigned int channelId,  // input: multichannel channel id (1 to #diagrams); 0 to disable channel enhancement
            fptype* allNumerators,         // output: multichannel numerators[nevt], running_sum_over_helicities
            fptype* allDenominators,       // output: multichannel denominators[nevt], running_sum_over_helicities
#endif
            int* allselhel,                // output: helicity selection[nevt]
            int* allselcol                 // output: helicity selection[nevt]
#ifndef MGONGPUCPP_GPUIMPL
            , const int nevt               // input: #events (for cuda: nevt == ndim == gpublocks*gputhreads)
#endif
            ) /* clang-format on */
  {
    mgDebugInitialise();

    // SANITY CHECKS for cudacpp code generation (see issues #272 and #343 and PRs #619, #626, #360, #396 and #754)
    // These variable are not used anywhere else in the code and their scope is limited to this sanity check
    {
      // nprocesses == 2 may happen for "mirror processes" such as P0_uux_ttx within pp_tt012j (see PR #754)
      constexpr int nprocesses = 1;
      static_assert( nprocesses == 1 || nprocesses == 2, "Assume nprocesses == 1 or 2" );
      constexpr int process_id = 1; // code generation source: standalone_cudacpp
      static_assert( process_id == 1, "Assume process_id == 1" );
    }

    // Denominators: spins, colors and identical particles
    constexpr int helcolDenominators[1] = { 512 }; // assume nprocesses == 1 (#272 and #343)

#ifdef MGONGPUCPP_GPUIMPL
    // Remember: in CUDA this is a kernel for one event, in c++ this processes n events
    const int ievt = blockDim.x * blockIdx.x + threadIdx.x; // index of event (thread) in grid
#else
    //assert( (size_t)(allmomenta) % mgOnGpu::cppAlign == 0 ); // SANITY CHECK: require SIMD-friendly alignment [COMMENT OUT TO TEST MISALIGNED ACCESS]
    //assert( (size_t)(allMEs) % mgOnGpu::cppAlign == 0 ); // SANITY CHECK: require SIMD-friendly alignment [COMMENT OUT TO TEST MISALIGNED ACCESS]
    using E_ACCESS = HostAccessMatrixElements; // non-trivial access: buffer includes all events
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
    using NUM_ACCESS = HostAccessNumerators;   // non-trivial access: buffer includes all events
    using DEN_ACCESS = HostAccessDenominators; // non-trivial access: buffer includes all events
#endif
#endif

    // Start sigmaKin_lines

#include "GpuAbstraction.h"

    // === PART 0 - INITIALISATION (before calculate_wavefunctions) ===
    // Reset the "matrix elements" - running sums of |M|^2 over helicities for the given event
#ifdef MGONGPUCPP_GPUIMPL
    allMEs[ievt] = 0;
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
    allNumerators[ievt] = 0;
    allDenominators[ievt] = 0;
#endif
#else
    const int npagV = nevt / neppV;
    for( int ipagV = 0; ipagV < npagV; ++ipagV )
    {
      const int ievt0 = ipagV * neppV;
      fptype* MEs = E_ACCESS::ieventAccessRecord( allMEs, ievt0 );
      fptype_sv& MEs_sv = E_ACCESS::kernelAccess( MEs );
      MEs_sv = fptype_sv{ 0 };
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      fptype* numerators = NUM_ACCESS::ieventAccessRecord( allNumerators, ievt0 );
      fptype* denominators = DEN_ACCESS::ieventAccessRecord( allDenominators, ievt0 );
      fptype_sv& numerators_sv = NUM_ACCESS::kernelAccess( numerators );
      fptype_sv& denominators_sv = DEN_ACCESS::kernelAccess( denominators );
      numerators_sv = fptype_sv{ 0 };
      denominators_sv = fptype_sv{ 0 };
#endif
    }
#endif

    // === PART 1 - HELICITY LOOP: CALCULATE WAVEFUNCTIONS ===
    // (in both CUDA and C++, using precomputed good helicities)

#ifdef MGONGPUCPP_GPUIMPL // CUDA OR C++

    // *** START OF PART 1a - CUDA (one event per CPU thread) ***
    // Running sum of partial amplitudes squared for event by event color selection (#402)
    // (for the single event processed in calculate_wavefunctions)
    fptype_sv jamp2_sv[nParity * ncolor] = { 0 };
    fptype MEs_ighel[ncomb] = { 0 }; // sum of MEs for all good helicities up to ighel (for this event)
    for( int ighel = 0; ighel < cNGoodHel; ighel++ )
    {
      const int ihel = cGoodHel[ighel];
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      calculate_wavefunctions( ihel, allmomenta, allcouplings, allMEs, channelId, allNumerators, allDenominators, jamp2_sv );
#else
      calculate_wavefunctions( ihel, allmomenta, allcouplings, allMEs, jamp2_sv );
#endif
      MEs_ighel[ighel] = allMEs[ievt];
    }
    // Event-by-event random choice of helicity #403
    //printf( "sigmaKin: ievt=%4d rndhel=%f\n", ievt, allrndhel[ievt] );
    for( int ighel = 0; ighel < cNGoodHel; ighel++ )
    {
      if( allrndhel[ievt] < ( MEs_ighel[ighel] / MEs_ighel[cNGoodHel - 1] ) )
      {
        const int ihelF = cGoodHel[ighel] + 1; // NB Fortran [1,ncomb], cudacpp [0,ncomb-1]
        allselhel[ievt] = ihelF;
        //printf( "sigmaKin: ievt=%4d ihel=%4d\n", ievt, ihelF );
        break;
      }
    }
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
    // Event-by-event random choice of color #402
    if( channelId != 0 ) // no event-by-event choice of color if channelId == 0 (fix FPE #783)
    {
      const unsigned int channelIdC = channelId - 1; // coloramps.h uses the C array indexing starting at 0
      fptype targetamp[ncolor] = { 0 };
      for( int icolC = 0; icolC < ncolor; icolC++ )
      {
        if( icolC == 0 )
          targetamp[icolC] = 0;
        else
          targetamp[icolC] = targetamp[icolC - 1];
        if( mgOnGpu::icolamp[channelIdC][icolC] ) targetamp[icolC] += jamp2_sv[icolC];
      }
      //printf( "sigmaKin: ievt=%4d rndcol=%f\n", ievt, allrndcol[ievt] );
      for( int icolC = 0; icolC < ncolor; icolC++ )
      {
        if( allrndcol[ievt] < ( targetamp[icolC] / targetamp[ncolor - 1] ) )
        {
          allselcol[ievt] = icolC + 1; // NB Fortran [1,ncolor], cudacpp [0,ncolor-1]
          break;
        }
      }
    }
#endif
    // *** END OF PART 1a - CUDA (one event per CPU thread) ***

#else // CUDA OR C++

    // *** START OF PART 1b - C++ (loop on event pages)
#if defined MGONGPU_CPPSIMD and defined MGONGPU_FPTYPE_DOUBLE and defined MGONGPU_FPTYPE2_FLOAT
    // Mixed fptypes #537: float for color algebra and double elsewhere
    // Delay color algebra and ME updates (only on even pages)
    assert( npagV % 2 == 0 );     // SANITY CHECK for mixed fptypes: two neppV-pages are merged to one 2*neppV-page
    const int npagV2 = npagV / 2; // loop on two SIMD pages (neppV events) at a time
#else
    const int npagV2 = npagV;            // loop on one SIMD page (neppV events) at a time
#endif
#ifdef _OPENMP
    // OMP multithreading #575 (NB: tested only with gcc11 so far)
    // See https://www.openmp.org/specifications/
    // - default(none): no variables are shared by default
    // - shared: as the name says
    // - private: give each thread its own copy, without initialising
    // - firstprivate: give each thread its own copy, and initialise with value from outside
#define _OMPLIST0 allcouplings, allMEs, allmomenta, allrndcol, allrndhel, allselcol, allselhel, cGoodHel, cNGoodHel, npagV2
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
#define _OMPLIST1 , allDenominators, allNumerators, channelId, mgOnGpu::icolamp
#else
#define _OMPLIST1
#endif
#pragma omp parallel for default( none ) shared( _OMPLIST0 _OMPLIST1 )
#undef _OMPLIST0
#undef _OMPLIST1
#endif // _OPENMP
    for( int ipagV2 = 0; ipagV2 < npagV2; ++ipagV2 )
    {
      // Running sum of partial amplitudes squared for event by event color selection (#402)
      // (jamp2[nParity][ncolor][neppV] for the SIMD vector - or the two SIMD vectors - of events processed in calculate_wavefunctions)
      fptype_sv jamp2_sv[nParity * ncolor] = { 0 };
      fptype_sv MEs_ighel[ncomb] = { 0 };    // sum of MEs for all good helicities up to ighel (for the first - and/or only - neppV page)
#if defined MGONGPU_CPPSIMD and defined MGONGPU_FPTYPE_DOUBLE and defined MGONGPU_FPTYPE2_FLOAT
      fptype_sv MEs_ighel2[ncomb] = { 0 };   // sum of MEs for all good helicities up to ighel (for the second neppV page)
      const int ievt00 = ipagV2 * neppV * 2; // loop on two SIMD pages (neppV events) at a time
#else
      const int ievt00 = ipagV2 * neppV; // loop on one SIMD page (neppV events) at a time
#endif
      for( int ighel = 0; ighel < cNGoodHel; ighel++ )
      {
        const int ihel = cGoodHel[ighel];
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
        calculate_wavefunctions( ihel, allmomenta, allcouplings, allMEs, channelId, allNumerators, allDenominators, jamp2_sv, ievt00 );
#else
        calculate_wavefunctions( ihel, allmomenta, allcouplings, allMEs, jamp2_sv, ievt00 );
#endif
        MEs_ighel[ighel] = E_ACCESS::kernelAccess( E_ACCESS::ieventAccessRecord( allMEs, ievt00 ) );
#if defined MGONGPU_CPPSIMD and defined MGONGPU_FPTYPE_DOUBLE and defined MGONGPU_FPTYPE2_FLOAT
        MEs_ighel2[ighel] = E_ACCESS::kernelAccess( E_ACCESS::ieventAccessRecord( allMEs, ievt00 + neppV ) );
#endif
      }
      // Event-by-event random choice of helicity #403
      for( int ieppV = 0; ieppV < neppV; ++ieppV )
      {
        const int ievt = ievt00 + ieppV;
        //printf( "sigmaKin: ievt=%4d rndhel=%f\n", ievt, allrndhel[ievt] );
        for( int ighel = 0; ighel < cNGoodHel; ighel++ )
        {
#if defined MGONGPU_CPPSIMD
          const bool okhel = allrndhel[ievt] < ( MEs_ighel[ighel][ieppV] / MEs_ighel[cNGoodHel - 1][ieppV] );
#else
          const bool okhel = allrndhel[ievt] < ( MEs_ighel[ighel] / MEs_ighel[cNGoodHel - 1] );
#endif
          if( okhel )
          {
            const int ihelF = cGoodHel[ighel] + 1; // NB Fortran [1,ncomb], cudacpp [0,ncomb-1]
            allselhel[ievt] = ihelF;
            //printf( "sigmaKin: ievt=%4d ihel=%4d\n", ievt, ihelF );
            break;
          }
        }
#if defined MGONGPU_CPPSIMD and defined MGONGPU_FPTYPE_DOUBLE and defined MGONGPU_FPTYPE2_FLOAT
        const int ievt2 = ievt00 + ieppV + neppV;
        //printf( "sigmaKin: ievt=%4d rndhel=%f\n", ievt2, allrndhel[ievt2] );
        for( int ighel = 0; ighel < cNGoodHel; ighel++ )
        {
          if( allrndhel[ievt2] < ( MEs_ighel2[ighel][ieppV] / MEs_ighel2[cNGoodHel - 1][ieppV] ) )
          {
            const int ihelF = cGoodHel[ighel] + 1; // NB Fortran [1,ncomb], cudacpp [0,ncomb-1]
            allselhel[ievt2] = ihelF;
            //printf( "sigmaKin: ievt=%4d ihel=%4d\n", ievt, ihelF );
            break;
          }
        }
#endif
      }
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL // multichannel enabled (random color choice)
      // Event-by-event random choice of color #402
      if( channelId != 0 ) // no event-by-event choice of color if channelId == 0 (fix FPE #783)
      {
        const unsigned int channelIdC = channelId - 1; // coloramps.h uses the C array indexing starting at 0
        fptype_sv targetamp[ncolor] = { 0 };
        for( int icolC = 0; icolC < ncolor; icolC++ )
        {
          if( icolC == 0 )
            targetamp[icolC] = fptype_sv{ 0 };
          else
            targetamp[icolC] = targetamp[icolC - 1];
          if( mgOnGpu::icolamp[channelIdC][icolC] ) targetamp[icolC] += jamp2_sv[icolC];
        }
#if defined MGONGPU_CPPSIMD and defined MGONGPU_FPTYPE_DOUBLE and defined MGONGPU_FPTYPE2_FLOAT
        fptype_sv targetamp2[ncolor] = { 0 };
        for( int icolC = 0; icolC < ncolor; icolC++ )
        {
          if( icolC == 0 )
            targetamp2[icolC] = fptype_sv{ 0 };
          else
            targetamp2[icolC] = targetamp2[icolC - 1];
          if( mgOnGpu::icolamp[channelIdC][icolC] ) targetamp2[icolC] += jamp2_sv[ncolor + icolC];
        }
#endif
        for( int ieppV = 0; ieppV < neppV; ++ieppV )
        {
          const int ievt = ievt00 + ieppV;
          //printf( "sigmaKin: ievt=%4d rndcol=%f\n", ievt, allrndcol[ievt] );
          for( int icolC = 0; icolC < ncolor; icolC++ )
          {
#if defined MGONGPU_CPPSIMD
            const bool okcol = allrndcol[ievt] < ( targetamp[icolC][ieppV] / targetamp[ncolor - 1][ieppV] );
#else
            const bool okcol = allrndcol[ievt] < ( targetamp[icolC] / targetamp[ncolor - 1] );
#endif
            if( okcol )
            {
              allselcol[ievt] = icolC + 1; // NB Fortran [1,ncolor], cudacpp [0,ncolor-1]
              break;
            }
          }
#if defined MGONGPU_CPPSIMD and defined MGONGPU_FPTYPE_DOUBLE and defined MGONGPU_FPTYPE2_FLOAT
          const int ievt2 = ievt00 + ieppV + neppV;
          //printf( "sigmaKin: ievt=%4d rndcol=%f\n", ievt2, allrndcol[ievt2] );
          for( int icolC = 0; icolC < ncolor; icolC++ )
          {
            if( allrndcol[ievt2] < ( targetamp2[icolC][ieppV] / targetamp2[ncolor - 1][ieppV] ) )
            {
              allselcol[ievt2] = icolC + 1; // NB Fortran [1,ncolor], cudacpp [0,ncolor-1]
              break;
            }
          }
#endif
        }
      }
#endif // multichannel enabled (random color choice)
    }
    // *** END OF PART 1b - C++ (loop on event pages)

#endif // CUDA or C++

    // === PART 2 - FINALISATION (after calculate_wavefunctions) ===
    // Get the final |M|^2 as an average over helicities/colors of the running sum of |M|^2 over helicities for the given event
    // [NB 'sum over final spins, average over initial spins', eg see
    // https://www.uzh.ch/cmsssl/physik/dam/jcr:2e24b7b1-f4d7-4160-817e-47b13dbf1d7c/Handout_4_2016-UZH.pdf]
#ifdef MGONGPUCPP_GPUIMPL
    allMEs[ievt] /= helcolDenominators[0];
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
    if( channelId > 0 ) allMEs[ievt] *= allNumerators[ievt] / allDenominators[ievt];
#endif
#else
    for( int ipagV = 0; ipagV < npagV; ++ipagV )
    {
      const int ievt0 = ipagV * neppV;
      fptype* MEs = E_ACCESS::ieventAccessRecord( allMEs, ievt0 );
      fptype_sv& MEs_sv = E_ACCESS::kernelAccess( MEs );
      MEs_sv /= helcolDenominators[0];
#ifdef MGONGPU_SUPPORTS_MULTICHANNEL
      if( channelId > 0 )
      {
        fptype* numerators = NUM_ACCESS::ieventAccessRecord( allNumerators, ievt0 );
        fptype* denominators = DEN_ACCESS::ieventAccessRecord( allDenominators, ievt0 );
        fptype_sv& numerators_sv = NUM_ACCESS::kernelAccess( numerators );
        fptype_sv& denominators_sv = DEN_ACCESS::kernelAccess( denominators );
        MEs_sv *= numerators_sv / denominators_sv;
      }
#endif
      //for( int ieppV = 0; ieppV < neppV; ieppV++ )
      //{
      //  const unsigned int ievt = ipagV * neppV + ieppV;
      //  printf( "sigmaKin: ievt=%2d me=%f\n", ievt, allMEs[ievt] );
      //}
    }
#endif
    mgDebugFinalise();
  }

  //--------------------------------------------------------------------------

} // end namespace

//==========================================================================
