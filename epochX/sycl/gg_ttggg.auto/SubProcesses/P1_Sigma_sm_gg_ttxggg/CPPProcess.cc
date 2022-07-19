//==========================================================================
// This file has been automatically generated for SYCL standalone by
// MadGraph5_aMC@NLO v. 2.9.5, 2021-08-22
// By the MadGraph5_aMC@NLO Development Team
// Visit launchpad.net/madgraph5 and amcatnlo.web.cern.ch
//==========================================================================

#include <algorithm>
#include <array>
#include <cstring>
#include <memory>

#include "mgOnGpuConfig.h"
#include "mgOnGpuTypes.h"
#include "mgOnGpuVectors.h"

#include "CPPProcess.h"
#include "HelAmps_sm.h"

//==========================================================================
// Class member functions for calculating the matrix elements for
// Process: g g > t t~ g g g WEIGHTED<=5 @1

namespace Proc
{
  using mgOnGpu::np4; // dimensions of 4-momenta (E,px,py,pz)
  using mgOnGpu::npar; // #particles in total (external = initial + final): e.g. 4 for e+ e- -> mu+ mu-
  using mgOnGpu::ncomb; // #helicity combinations: e.g. 16 for e+ e- -> mu+ mu- (2**4 = fermion spin up/down ** npar)

  using mgOnGpu::nwf; // #wavefunctions = #external (npar) + #internal: e.g. 5 for e+ e- -> mu+ mu- (1 internal is gamma or Z)
  using mgOnGpu::nw6; // dimensions of each wavefunction (HELAS KEK 91-11): e.g. 6 for e+ e- -> mu+ mu- (fermions and vectors)

  //--------------------------------------------------------------------------

  // Evaluate |M|^2 for each subprocess
  // NB: calculate_wavefunctions ADDS |M|^2 for a given ihel to the running sum of |M|^2 over helicities for the given event(s)
  SYCL_EXTERNAL
  INLINE
  void calculate_wavefunctions( int ihel,
                                const fptype_sv* __restrict__ allmomenta, // input: momenta as AOSOA[npagM][npar][4][neppM] with nevt=npagM*neppM
                                fptype_sv* allMEs,                        // output: allMEs[npagM][neppM], final |M|^2 averaged over helicities
                                size_t ievt,
                                const short*  __restrict__ cHel,
                                const fptype* __restrict__ cIPC,
                                const fptype* __restrict__ cIPD
                                )
  //ALWAYS_INLINE // attributes are not permitted in a function definition
  {
    using namespace MG5_sm;
    mgDebug( 0, __FUNCTION__ );
    const cxtype* COUPs = reinterpret_cast<const cxtype*>(cIPC);


    // The number of colors
    constexpr int ncolor = 120;

    // Local TEMPORARY variables for a subset of Feynman diagrams in the given SYCL event (ievt)
    // [NB these variables are reused several times (and re-initialised each time) within the same event or event page]
    cxtype_sv w_sv[nwf][nw6]; // particle wavefunctions within Feynman diagrams (nw6 is often 6, the dimension of spin 1/2 or spin 1 particles)
    cxtype_sv amp_sv[1]; // invariant amplitude for one given Feynman diagram

    // Local variables for the given CUDA event (ievt) or C++ event page (ipagV)
    cxtype_sv jamp_sv[ncolor] = {}; // sum of the invariant amplitudes for all Feynman diagrams in the event or event page

    // === Calculate wavefunctions and amplitudes for all diagrams in all processes - Loop over nevt events ===

    {
      // Reset color flows (reset jamp_sv) at the beginning of a new event or event page
      for( int i=0; i<ncolor; i++ ){ jamp_sv[i] = cxzero_sv(); }

      // *** DIAGRAM 1 OF 1240 ***

      // Wavefunction(s) for diagram number 1
      vxxxxx( allmomenta, ievt, 0., cHel[ihel*npar + 0], -1, w_sv[0], 0 );

      vxxxxx( allmomenta, ievt, 0., cHel[ihel*npar + 1], -1, w_sv[1], 1 );

      oxxxxx( allmomenta, ievt, cIPD[0], cHel[ihel*npar + 2], +1, w_sv[2], 2 );

      ixxxxx( allmomenta, ievt, cIPD[0], cHel[ihel*npar + 3], -1, w_sv[3], 3 );

      vxxxxx( allmomenta, ievt, 0., cHel[ihel*npar + 4], +1, w_sv[4], 4 );

      vxxxxx( allmomenta, ievt, 0., cHel[ihel*npar + 5], +1, w_sv[5], 5 );

      vxxxxx( allmomenta, ievt, 0., cHel[ihel*npar + 6], +1, w_sv[6], 6 );

      VVV1P0_1( w_sv[0], w_sv[1], COUPs[0], 0., 0., w_sv[7] );
      FFV1P0_3( w_sv[3], w_sv[2], COUPs[1], 0., 0., w_sv[8] );
      VVV1P0_1( w_sv[7], w_sv[4], COUPs[0], 0., 0., w_sv[9] );
      VVV1P0_1( w_sv[8], w_sv[5], COUPs[0], 0., 0., w_sv[10] );

      // Amplitude(s) for diagram number 1
      VVV1_0( w_sv[9], w_sv[10], w_sv[6], COUPs[0], &amp_sv[0] );
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[25] += +amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[94] += +amp_sv[0];
      jamp_sv[95] -= amp_sv[0];
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];

      // *** DIAGRAM 2 OF 1240 ***

      // Wavefunction(s) for diagram number 2
      VVV1P0_1( w_sv[8], w_sv[6], COUPs[0], 0., 0., w_sv[11] );

      // Amplitude(s) for diagram number 2
      VVV1_0( w_sv[9], w_sv[11], w_sv[5], COUPs[0], &amp_sv[0] );
      jamp_sv[0] -= amp_sv[0];
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];
      jamp_sv[118] += +amp_sv[0];
      jamp_sv[119] -= amp_sv[0];

      // *** DIAGRAM 3 OF 1240 ***

      // Wavefunction(s) for diagram number 3
      // (none)

      // Amplitude(s) for diagram number 3
      VVVV1_0( w_sv[8], w_sv[5], w_sv[6], w_sv[9], COUPs[2], &amp_sv[0] );
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[25] += +amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[94] += +amp_sv[0];
      jamp_sv[95] -= amp_sv[0];
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];
      VVVV3_0( w_sv[8], w_sv[5], w_sv[6], w_sv[9], COUPs[2], &amp_sv[0] );
      jamp_sv[0] -= amp_sv[0];
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];
      jamp_sv[118] += +amp_sv[0];
      jamp_sv[119] -= amp_sv[0];
      VVVV4_0( w_sv[8], w_sv[5], w_sv[6], w_sv[9], COUPs[2], &amp_sv[0] );
      jamp_sv[0] -= amp_sv[0];
      jamp_sv[1] += +amp_sv[0];
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[25] -= amp_sv[0];
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[49] -= amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[55] += +amp_sv[0];
      jamp_sv[90] += +amp_sv[0];
      jamp_sv[92] -= amp_sv[0];
      jamp_sv[94] -= amp_sv[0];
      jamp_sv[95] += +amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];
      jamp_sv[118] += +amp_sv[0];
      jamp_sv[119] -= amp_sv[0];

      // *** DIAGRAM 4 OF 1240 ***

      // Wavefunction(s) for diagram number 4
      VVV1P0_1( w_sv[7], w_sv[5], COUPs[0], 0., 0., w_sv[12] );
      VVV1P0_1( w_sv[8], w_sv[4], COUPs[0], 0., 0., w_sv[13] );

      // Amplitude(s) for diagram number 4
      VVV1_0( w_sv[12], w_sv[13], w_sv[6], COUPs[0], &amp_sv[0] );
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[27] += +amp_sv[0];
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[70] += +amp_sv[0];
      jamp_sv[71] -= amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[97] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];

      // *** DIAGRAM 5 OF 1240 ***

      // Wavefunction(s) for diagram number 5
      // (none)

      // Amplitude(s) for diagram number 5
      VVV1_0( w_sv[12], w_sv[11], w_sv[4], COUPs[0], &amp_sv[0] );
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[97] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      jamp_sv[113] -= amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];

      // *** DIAGRAM 6 OF 1240 ***

      // Wavefunction(s) for diagram number 6
      // (none)

      // Amplitude(s) for diagram number 6
      VVVV1_0( w_sv[8], w_sv[4], w_sv[6], w_sv[12], COUPs[2], &amp_sv[0] );
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[27] += +amp_sv[0];
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[70] += +amp_sv[0];
      jamp_sv[71] -= amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[97] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];
      VVVV3_0( w_sv[8], w_sv[4], w_sv[6], w_sv[12], COUPs[2], &amp_sv[0] );
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[97] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      jamp_sv[113] -= amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];
      VVVV4_0( w_sv[8], w_sv[4], w_sv[6], w_sv[12], COUPs[2], &amp_sv[0] );
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[3] += +amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[27] -= amp_sv[0];
      jamp_sv[66] += +amp_sv[0];
      jamp_sv[68] -= amp_sv[0];
      jamp_sv[70] -= amp_sv[0];
      jamp_sv[71] += +amp_sv[0];
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[73] -= amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[79] += +amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      jamp_sv[113] -= amp_sv[0];

      // *** DIAGRAM 7 OF 1240 ***

      // Wavefunction(s) for diagram number 7
      VVV1P0_1( w_sv[7], w_sv[6], COUPs[0], 0., 0., w_sv[14] );

      // Amplitude(s) for diagram number 7
      VVV1_0( w_sv[14], w_sv[13], w_sv[5], COUPs[0], &amp_sv[0] );
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[29] += +amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[64] += +amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[97] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];

      // *** DIAGRAM 8 OF 1240 ***

      // Wavefunction(s) for diagram number 8
      // (none)

      // Amplitude(s) for diagram number 8
      VVV1_0( w_sv[14], w_sv[10], w_sv[4], COUPs[0], &amp_sv[0] );
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[89] -= amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[102] -= amp_sv[0];

      // *** DIAGRAM 9 OF 1240 ***

      // Wavefunction(s) for diagram number 9
      // (none)

      // Amplitude(s) for diagram number 9
      VVVV1_0( w_sv[8], w_sv[4], w_sv[5], w_sv[14], COUPs[2], &amp_sv[0] );
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[29] += +amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[64] += +amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[97] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      VVVV3_0( w_sv[8], w_sv[4], w_sv[5], w_sv[14], COUPs[2], &amp_sv[0] );
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[89] -= amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      VVVV4_0( w_sv[8], w_sv[4], w_sv[5], w_sv[14], COUPs[2], &amp_sv[0] );
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[5] += +amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[29] -= amp_sv[0];
      jamp_sv[60] += +amp_sv[0];
      jamp_sv[62] -= amp_sv[0];
      jamp_sv[64] -= amp_sv[0];
      jamp_sv[65] += +amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[89] -= amp_sv[0];
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[97] -= amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[103] += +amp_sv[0];

      // *** DIAGRAM 10 OF 1240 ***

      // Wavefunction(s) for diagram number 10
      VVVV1P0_1( w_sv[7], w_sv[4], w_sv[5], COUPs[2], 0., 0., w_sv[15] );
      VVVV3P0_1( w_sv[7], w_sv[4], w_sv[5], COUPs[2], 0., 0., w_sv[16] );
      VVVV4P0_1( w_sv[7], w_sv[4], w_sv[5], COUPs[2], 0., 0., w_sv[17] );

      // Amplitude(s) for diagram number 10
      VVV1_0( w_sv[8], w_sv[6], w_sv[15], COUPs[0], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[24] -= amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[84] += +amp_sv[0];
      jamp_sv[86] -= amp_sv[0];
      jamp_sv[96] -= amp_sv[0];
      jamp_sv[97] += +amp_sv[0];
      jamp_sv[102] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      jamp_sv[113] -= amp_sv[0];
      jamp_sv[118] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];
      VVV1_0( w_sv[8], w_sv[6], w_sv[16], COUPs[0], &amp_sv[0] );
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[97] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      jamp_sv[113] -= amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];
      VVV1_0( w_sv[8], w_sv[6], w_sv[17], COUPs[0], &amp_sv[0] );
      jamp_sv[0] -= amp_sv[0];
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];
      jamp_sv[118] += +amp_sv[0];
      jamp_sv[119] -= amp_sv[0];

      // *** DIAGRAM 11 OF 1240 ***

      // Wavefunction(s) for diagram number 11
      VVVV1P0_1( w_sv[7], w_sv[4], w_sv[6], COUPs[2], 0., 0., w_sv[18] );
      VVVV3P0_1( w_sv[7], w_sv[4], w_sv[6], COUPs[2], 0., 0., w_sv[19] );
      VVVV4P0_1( w_sv[7], w_sv[4], w_sv[6], COUPs[2], 0., 0., w_sv[20] );

      // Amplitude(s) for diagram number 11
      VVV1_0( w_sv[8], w_sv[5], w_sv[18], COUPs[0], &amp_sv[0] );
      jamp_sv[1] += +amp_sv[0];
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[25] -= amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[72] -= amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[78] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[89] -= amp_sv[0];
      jamp_sv[94] -= amp_sv[0];
      jamp_sv[95] += +amp_sv[0];
      jamp_sv[108] += +amp_sv[0];
      jamp_sv[110] -= amp_sv[0];
      VVV1_0( w_sv[8], w_sv[5], w_sv[19], COUPs[0], &amp_sv[0] );
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[89] -= amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      VVV1_0( w_sv[8], w_sv[5], w_sv[20], COUPs[0], &amp_sv[0] );
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[25] += +amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[94] += +amp_sv[0];
      jamp_sv[95] -= amp_sv[0];
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];

      // *** DIAGRAM 12 OF 1240 ***

      // Wavefunction(s) for diagram number 12
      VVVV1P0_1( w_sv[7], w_sv[5], w_sv[6], COUPs[2], 0., 0., w_sv[21] );
      VVVV3P0_1( w_sv[7], w_sv[5], w_sv[6], COUPs[2], 0., 0., w_sv[22] );
      VVVV4P0_1( w_sv[7], w_sv[5], w_sv[6], COUPs[2], 0., 0., w_sv[23] );

      // Amplitude(s) for diagram number 12
      VVV1_0( w_sv[8], w_sv[4], w_sv[21], COUPs[0], &amp_sv[0] );
      jamp_sv[3] += +amp_sv[0];
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[27] -= amp_sv[0];
      jamp_sv[29] += +amp_sv[0];
      jamp_sv[48] -= amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[54] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[64] += +amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[70] -= amp_sv[0];
      jamp_sv[71] += +amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[114] += +amp_sv[0];
      jamp_sv[116] -= amp_sv[0];
      VVV1_0( w_sv[8], w_sv[4], w_sv[22], COUPs[0], &amp_sv[0] );
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[29] += +amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[64] += +amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[97] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      VVV1_0( w_sv[8], w_sv[4], w_sv[23], COUPs[0], &amp_sv[0] );
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[27] += +amp_sv[0];
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[70] += +amp_sv[0];
      jamp_sv[71] -= amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[97] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];

      // *** DIAGRAM 13 OF 1240 ***

      // Wavefunction(s) for diagram number 13
      VVV1P0_1( w_sv[4], w_sv[5], COUPs[0], 0., 0., w_sv[24] );

      // Amplitude(s) for diagram number 13
      VVVV1_0( w_sv[7], w_sv[8], w_sv[24], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[5] += +amp_sv[0];
      jamp_sv[24] -= amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[29] -= amp_sv[0];
      jamp_sv[64] -= amp_sv[0];
      jamp_sv[65] += +amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[89] -= amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      jamp_sv[113] -= amp_sv[0];
      jamp_sv[118] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];
      VVVV3_0( w_sv[7], w_sv[8], w_sv[24], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[24] -= amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[84] += +amp_sv[0];
      jamp_sv[86] -= amp_sv[0];
      jamp_sv[96] -= amp_sv[0];
      jamp_sv[97] += +amp_sv[0];
      jamp_sv[102] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      jamp_sv[113] -= amp_sv[0];
      jamp_sv[118] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];
      VVVV4_0( w_sv[7], w_sv[8], w_sv[24], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[4] += +amp_sv[0];
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[28] -= amp_sv[0];
      jamp_sv[29] += +amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[64] += +amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[84] += +amp_sv[0];
      jamp_sv[86] -= amp_sv[0];
      jamp_sv[88] -= amp_sv[0];
      jamp_sv[89] += +amp_sv[0];
      jamp_sv[96] -= amp_sv[0];
      jamp_sv[97] += +amp_sv[0];
      jamp_sv[102] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];

      // *** DIAGRAM 14 OF 1240 ***

      // Wavefunction(s) for diagram number 14
      VVV1P0_1( w_sv[7], w_sv[8], COUPs[0], 0., 0., w_sv[25] );

      // Amplitude(s) for diagram number 14
      VVV1_0( w_sv[24], w_sv[6], w_sv[25], COUPs[0], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[5] += +amp_sv[0];
      jamp_sv[24] -= amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[29] -= amp_sv[0];
      jamp_sv[64] -= amp_sv[0];
      jamp_sv[65] += +amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[89] -= amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      jamp_sv[113] -= amp_sv[0];
      jamp_sv[118] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];

      // *** DIAGRAM 15 OF 1240 ***

      // Wavefunction(s) for diagram number 15
      VVV1P0_1( w_sv[7], w_sv[24], COUPs[0], 0., 0., w_sv[26] );

      // Amplitude(s) for diagram number 15
      VVV1_0( w_sv[8], w_sv[6], w_sv[26], COUPs[0], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[24] -= amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[84] += +amp_sv[0];
      jamp_sv[86] -= amp_sv[0];
      jamp_sv[96] -= amp_sv[0];
      jamp_sv[97] += +amp_sv[0];
      jamp_sv[102] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      jamp_sv[113] -= amp_sv[0];
      jamp_sv[118] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];

      // *** DIAGRAM 16 OF 1240 ***

      // Wavefunction(s) for diagram number 16
      // (none)

      // Amplitude(s) for diagram number 16
      VVV1_0( w_sv[8], w_sv[24], w_sv[14], COUPs[0], &amp_sv[0] );
      jamp_sv[4] += +amp_sv[0];
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[28] -= amp_sv[0];
      jamp_sv[29] += +amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[64] += +amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[84] += +amp_sv[0];
      jamp_sv[86] -= amp_sv[0];
      jamp_sv[88] -= amp_sv[0];
      jamp_sv[89] += +amp_sv[0];
      jamp_sv[96] -= amp_sv[0];
      jamp_sv[97] += +amp_sv[0];
      jamp_sv[102] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];

      // *** DIAGRAM 17 OF 1240 ***

      // Wavefunction(s) for diagram number 17
      VVV1P0_1( w_sv[4], w_sv[6], COUPs[0], 0., 0., w_sv[27] );

      // Amplitude(s) for diagram number 17
      VVVV1_0( w_sv[7], w_sv[8], w_sv[27], w_sv[5], COUPs[2], &amp_sv[0] );
      jamp_sv[1] += +amp_sv[0];
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[3] += +amp_sv[0];
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[25] -= amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[27] -= amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[70] -= amp_sv[0];
      jamp_sv[71] += +amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[89] -= amp_sv[0];
      jamp_sv[94] -= amp_sv[0];
      jamp_sv[95] += +amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      jamp_sv[113] -= amp_sv[0];
      VVVV3_0( w_sv[7], w_sv[8], w_sv[27], w_sv[5], COUPs[2], &amp_sv[0] );
      jamp_sv[1] += +amp_sv[0];
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[25] -= amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[72] -= amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[78] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[89] -= amp_sv[0];
      jamp_sv[94] -= amp_sv[0];
      jamp_sv[95] += +amp_sv[0];
      jamp_sv[108] += +amp_sv[0];
      jamp_sv[110] -= amp_sv[0];
      VVVV4_0( w_sv[7], w_sv[8], w_sv[27], w_sv[5], COUPs[2], &amp_sv[0] );
      jamp_sv[2] += +amp_sv[0];
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[26] -= amp_sv[0];
      jamp_sv[27] += +amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[70] += +amp_sv[0];
      jamp_sv[71] -= amp_sv[0];
      jamp_sv[72] -= amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[78] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[108] += +amp_sv[0];
      jamp_sv[110] -= amp_sv[0];
      jamp_sv[112] -= amp_sv[0];
      jamp_sv[113] += +amp_sv[0];

      // *** DIAGRAM 18 OF 1240 ***

      // Wavefunction(s) for diagram number 18
      // (none)

      // Amplitude(s) for diagram number 18
      VVV1_0( w_sv[27], w_sv[5], w_sv[25], COUPs[0], &amp_sv[0] );
      jamp_sv[1] += +amp_sv[0];
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[3] += +amp_sv[0];
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[25] -= amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[27] -= amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[70] -= amp_sv[0];
      jamp_sv[71] += +amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[89] -= amp_sv[0];
      jamp_sv[94] -= amp_sv[0];
      jamp_sv[95] += +amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      jamp_sv[113] -= amp_sv[0];

      // *** DIAGRAM 19 OF 1240 ***

      // Wavefunction(s) for diagram number 19
      VVV1P0_1( w_sv[7], w_sv[27], COUPs[0], 0., 0., w_sv[28] );

      // Amplitude(s) for diagram number 19
      VVV1_0( w_sv[8], w_sv[5], w_sv[28], COUPs[0], &amp_sv[0] );
      jamp_sv[1] += +amp_sv[0];
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[25] -= amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[72] -= amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[78] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[89] -= amp_sv[0];
      jamp_sv[94] -= amp_sv[0];
      jamp_sv[95] += +amp_sv[0];
      jamp_sv[108] += +amp_sv[0];
      jamp_sv[110] -= amp_sv[0];

      // *** DIAGRAM 20 OF 1240 ***

      // Wavefunction(s) for diagram number 20
      // (none)

      // Amplitude(s) for diagram number 20
      VVV1_0( w_sv[8], w_sv[27], w_sv[12], COUPs[0], &amp_sv[0] );
      jamp_sv[2] += +amp_sv[0];
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[26] -= amp_sv[0];
      jamp_sv[27] += +amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[70] += +amp_sv[0];
      jamp_sv[71] -= amp_sv[0];
      jamp_sv[72] -= amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[78] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[108] += +amp_sv[0];
      jamp_sv[110] -= amp_sv[0];
      jamp_sv[112] -= amp_sv[0];
      jamp_sv[113] += +amp_sv[0];

      // *** DIAGRAM 21 OF 1240 ***

      // Wavefunction(s) for diagram number 21
      VVV1P0_1( w_sv[5], w_sv[6], COUPs[0], 0., 0., w_sv[29] );

      // Amplitude(s) for diagram number 21
      VVVV1_0( w_sv[7], w_sv[8], w_sv[4], w_sv[29], COUPs[2], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[5] += +amp_sv[0];
      jamp_sv[24] -= amp_sv[0];
      jamp_sv[25] += +amp_sv[0];
      jamp_sv[27] += +amp_sv[0];
      jamp_sv[29] -= amp_sv[0];
      jamp_sv[64] -= amp_sv[0];
      jamp_sv[65] += +amp_sv[0];
      jamp_sv[70] += +amp_sv[0];
      jamp_sv[71] -= amp_sv[0];
      jamp_sv[94] += +amp_sv[0];
      jamp_sv[95] -= amp_sv[0];
      jamp_sv[118] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];
      VVVV3_0( w_sv[7], w_sv[8], w_sv[4], w_sv[29], COUPs[2], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[24] -= amp_sv[0];
      jamp_sv[25] += +amp_sv[0];
      jamp_sv[48] -= amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[54] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[94] += +amp_sv[0];
      jamp_sv[95] -= amp_sv[0];
      jamp_sv[114] += +amp_sv[0];
      jamp_sv[116] -= amp_sv[0];
      jamp_sv[118] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];
      VVVV4_0( w_sv[7], w_sv[8], w_sv[4], w_sv[29], COUPs[2], &amp_sv[0] );
      jamp_sv[3] += +amp_sv[0];
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[27] -= amp_sv[0];
      jamp_sv[29] += +amp_sv[0];
      jamp_sv[48] -= amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[54] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[64] += +amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[70] -= amp_sv[0];
      jamp_sv[71] += +amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[114] += +amp_sv[0];
      jamp_sv[116] -= amp_sv[0];

      // *** DIAGRAM 22 OF 1240 ***

      // Wavefunction(s) for diagram number 22
      // (none)

      // Amplitude(s) for diagram number 22
      VVV1_0( w_sv[4], w_sv[29], w_sv[25], COUPs[0], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[5] += +amp_sv[0];
      jamp_sv[24] -= amp_sv[0];
      jamp_sv[25] += +amp_sv[0];
      jamp_sv[27] += +amp_sv[0];
      jamp_sv[29] -= amp_sv[0];
      jamp_sv[64] -= amp_sv[0];
      jamp_sv[65] += +amp_sv[0];
      jamp_sv[70] += +amp_sv[0];
      jamp_sv[71] -= amp_sv[0];
      jamp_sv[94] += +amp_sv[0];
      jamp_sv[95] -= amp_sv[0];
      jamp_sv[118] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];

      // *** DIAGRAM 23 OF 1240 ***

      // Wavefunction(s) for diagram number 23
      // (none)

      // Amplitude(s) for diagram number 23
      VVV1_0( w_sv[8], w_sv[29], w_sv[9], COUPs[0], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[24] -= amp_sv[0];
      jamp_sv[25] += +amp_sv[0];
      jamp_sv[48] -= amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[54] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[94] += +amp_sv[0];
      jamp_sv[95] -= amp_sv[0];
      jamp_sv[114] += +amp_sv[0];
      jamp_sv[116] -= amp_sv[0];
      jamp_sv[118] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];

      // *** DIAGRAM 24 OF 1240 ***

      // Wavefunction(s) for diagram number 24
      VVV1P0_1( w_sv[7], w_sv[29], COUPs[0], 0., 0., w_sv[25] );

      // Amplitude(s) for diagram number 24
      VVV1_0( w_sv[8], w_sv[4], w_sv[25], COUPs[0], &amp_sv[0] );
      jamp_sv[3] += +amp_sv[0];
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[27] -= amp_sv[0];
      jamp_sv[29] += +amp_sv[0];
      jamp_sv[48] -= amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[54] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[64] += +amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[70] -= amp_sv[0];
      jamp_sv[71] += +amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[114] += +amp_sv[0];
      jamp_sv[116] -= amp_sv[0];

      // *** DIAGRAM 25 OF 1240 ***

      // Wavefunction(s) for diagram number 25
      VVVV1P0_1( w_sv[4], w_sv[5], w_sv[6], COUPs[2], 0., 0., w_sv[30] );
      VVVV3P0_1( w_sv[4], w_sv[5], w_sv[6], COUPs[2], 0., 0., w_sv[31] );
      VVVV4P0_1( w_sv[4], w_sv[5], w_sv[6], COUPs[2], 0., 0., w_sv[32] );

      // Amplitude(s) for diagram number 25
      VVV1_0( w_sv[7], w_sv[8], w_sv[30], COUPs[0], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[5] += +amp_sv[0];
      jamp_sv[24] -= amp_sv[0];
      jamp_sv[25] += +amp_sv[0];
      jamp_sv[27] += +amp_sv[0];
      jamp_sv[29] -= amp_sv[0];
      jamp_sv[64] -= amp_sv[0];
      jamp_sv[65] += +amp_sv[0];
      jamp_sv[70] += +amp_sv[0];
      jamp_sv[71] -= amp_sv[0];
      jamp_sv[94] += +amp_sv[0];
      jamp_sv[95] -= amp_sv[0];
      jamp_sv[118] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];
      VVV1_0( w_sv[7], w_sv[8], w_sv[31], COUPs[0], &amp_sv[0] );
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[2] += +amp_sv[0];
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[4] += +amp_sv[0];
      jamp_sv[25] += +amp_sv[0];
      jamp_sv[26] -= amp_sv[0];
      jamp_sv[27] += +amp_sv[0];
      jamp_sv[28] -= amp_sv[0];
      jamp_sv[70] += +amp_sv[0];
      jamp_sv[71] -= amp_sv[0];
      jamp_sv[88] -= amp_sv[0];
      jamp_sv[89] += +amp_sv[0];
      jamp_sv[94] += +amp_sv[0];
      jamp_sv[95] -= amp_sv[0];
      jamp_sv[112] -= amp_sv[0];
      jamp_sv[113] += +amp_sv[0];
      VVV1_0( w_sv[7], w_sv[8], w_sv[32], COUPs[0], &amp_sv[0] );
      jamp_sv[0] -= amp_sv[0];
      jamp_sv[2] += +amp_sv[0];
      jamp_sv[4] += +amp_sv[0];
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[26] -= amp_sv[0];
      jamp_sv[28] -= amp_sv[0];
      jamp_sv[29] += +amp_sv[0];
      jamp_sv[64] += +amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[88] -= amp_sv[0];
      jamp_sv[89] += +amp_sv[0];
      jamp_sv[112] -= amp_sv[0];
      jamp_sv[113] += +amp_sv[0];
      jamp_sv[118] += +amp_sv[0];
      jamp_sv[119] -= amp_sv[0];

      // *** DIAGRAM 26 OF 1240 ***

      // Wavefunction(s) for diagram number 26
      FFV1_1( w_sv[2], w_sv[4], COUPs[1], cIPD[0], cIPD[1], w_sv[33] );
      FFV1_2( w_sv[3], w_sv[7], COUPs[1], cIPD[0], cIPD[1], w_sv[34] );
      FFV1_1( w_sv[33], w_sv[5], COUPs[1], cIPD[0], cIPD[1], w_sv[35] );

      // Amplitude(s) for diagram number 26
      FFV1_0( w_sv[34], w_sv[35], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[64] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[65] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 27 OF 1240 ***

      // Wavefunction(s) for diagram number 27
      FFV1_1( w_sv[33], w_sv[6], COUPs[1], cIPD[0], cIPD[1], w_sv[36] );

      // Amplitude(s) for diagram number 27
      FFV1_0( w_sv[34], w_sv[36], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[70] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[71] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 28 OF 1240 ***

      // Wavefunction(s) for diagram number 28
      FFV1P0_3( w_sv[3], w_sv[33], COUPs[1], 0., 0., w_sv[37] );

      // Amplitude(s) for diagram number 28
      VVV1_0( w_sv[12], w_sv[37], w_sv[6], COUPs[0], &amp_sv[0] );
      jamp_sv[48] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[54] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[60] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[62] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[66] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[68] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[70] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[71] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 29 OF 1240 ***

      // Wavefunction(s) for diagram number 29
      // (none)

      // Amplitude(s) for diagram number 29
      FFV1_0( w_sv[3], w_sv[36], w_sv[12], COUPs[1], &amp_sv[0] );
      jamp_sv[66] += +amp_sv[0];
      jamp_sv[68] -= amp_sv[0];
      jamp_sv[70] -= amp_sv[0];
      jamp_sv[71] += +amp_sv[0];

      // *** DIAGRAM 30 OF 1240 ***

      // Wavefunction(s) for diagram number 30
      // (none)

      // Amplitude(s) for diagram number 30
      VVV1_0( w_sv[14], w_sv[37], w_sv[5], COUPs[0], &amp_sv[0] );
      jamp_sv[49] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[55] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[60] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[62] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[64] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[65] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[66] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[68] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 31 OF 1240 ***

      // Wavefunction(s) for diagram number 31
      // (none)

      // Amplitude(s) for diagram number 31
      FFV1_0( w_sv[3], w_sv[35], w_sv[14], COUPs[1], &amp_sv[0] );
      jamp_sv[60] += +amp_sv[0];
      jamp_sv[62] -= amp_sv[0];
      jamp_sv[64] -= amp_sv[0];
      jamp_sv[65] += +amp_sv[0];

      // *** DIAGRAM 32 OF 1240 ***

      // Wavefunction(s) for diagram number 32
      // (none)

      // Amplitude(s) for diagram number 32
      FFV1_0( w_sv[3], w_sv[33], w_sv[21], COUPs[1], &amp_sv[0] );
      jamp_sv[48] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[49] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[54] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[55] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[64] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[65] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[70] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[71] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[33], w_sv[22], COUPs[1], &amp_sv[0] );
      jamp_sv[49] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[55] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[60] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[62] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[64] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[65] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[66] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[68] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[33], w_sv[23], COUPs[1], &amp_sv[0] );
      jamp_sv[48] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[54] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[60] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[62] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[66] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[68] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[70] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[71] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 33 OF 1240 ***

      // Wavefunction(s) for diagram number 33
      FFV1_2( w_sv[3], w_sv[5], COUPs[1], cIPD[0], cIPD[1], w_sv[38] );
      FFV1_1( w_sv[33], w_sv[7], COUPs[1], cIPD[0], cIPD[1], w_sv[39] );

      // Amplitude(s) for diagram number 33
      FFV1_0( w_sv[38], w_sv[39], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[49] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[55] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 34 OF 1240 ***

      // Wavefunction(s) for diagram number 34
      FFV1_2( w_sv[38], w_sv[7], COUPs[1], cIPD[0], cIPD[1], w_sv[40] );

      // Amplitude(s) for diagram number 34
      FFV1_0( w_sv[40], w_sv[33], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[66] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[68] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 35 OF 1240 ***

      // Wavefunction(s) for diagram number 35
      // (none)

      // Amplitude(s) for diagram number 35
      FFV1_0( w_sv[38], w_sv[33], w_sv[14], COUPs[1], &amp_sv[0] );
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[68] += +amp_sv[0];

      // *** DIAGRAM 36 OF 1240 ***

      // Wavefunction(s) for diagram number 36
      FFV1_2( w_sv[3], w_sv[6], COUPs[1], cIPD[0], cIPD[1], w_sv[41] );

      // Amplitude(s) for diagram number 36
      FFV1_0( w_sv[41], w_sv[39], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[48] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[54] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 37 OF 1240 ***

      // Wavefunction(s) for diagram number 37
      FFV1_2( w_sv[41], w_sv[7], COUPs[1], cIPD[0], cIPD[1], w_sv[42] );

      // Amplitude(s) for diagram number 37
      FFV1_0( w_sv[42], w_sv[33], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[60] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[62] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 38 OF 1240 ***

      // Wavefunction(s) for diagram number 38
      // (none)

      // Amplitude(s) for diagram number 38
      FFV1_0( w_sv[41], w_sv[33], w_sv[12], COUPs[1], &amp_sv[0] );
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[62] += +amp_sv[0];

      // *** DIAGRAM 39 OF 1240 ***

      // Wavefunction(s) for diagram number 39
      // (none)

      // Amplitude(s) for diagram number 39
      FFV1_0( w_sv[3], w_sv[39], w_sv[29], COUPs[1], &amp_sv[0] );
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[49] -= amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[55] += +amp_sv[0];

      // *** DIAGRAM 40 OF 1240 ***

      // Wavefunction(s) for diagram number 40
      // (none)

      // Amplitude(s) for diagram number 40
      FFV1_0( w_sv[34], w_sv[33], w_sv[29], COUPs[1], &amp_sv[0] );
      jamp_sv[64] += +amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[70] -= amp_sv[0];
      jamp_sv[71] += +amp_sv[0];

      // *** DIAGRAM 41 OF 1240 ***

      // Wavefunction(s) for diagram number 41
      // (none)

      // Amplitude(s) for diagram number 41
      FFV1_0( w_sv[3], w_sv[33], w_sv[25], COUPs[1], &amp_sv[0] );
      jamp_sv[48] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[49] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[54] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[55] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[64] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[65] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[70] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[71] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 42 OF 1240 ***

      // Wavefunction(s) for diagram number 42
      FFV1_1( w_sv[2], w_sv[5], COUPs[1], cIPD[0], cIPD[1], w_sv[39] );
      FFV1_1( w_sv[39], w_sv[4], COUPs[1], cIPD[0], cIPD[1], w_sv[43] );

      // Amplitude(s) for diagram number 42
      FFV1_0( w_sv[34], w_sv[43], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[88] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[89] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 43 OF 1240 ***

      // Wavefunction(s) for diagram number 43
      FFV1_1( w_sv[39], w_sv[6], COUPs[1], cIPD[0], cIPD[1], w_sv[44] );

      // Amplitude(s) for diagram number 43
      FFV1_0( w_sv[34], w_sv[44], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[94] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[95] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 44 OF 1240 ***

      // Wavefunction(s) for diagram number 44
      FFV1P0_3( w_sv[3], w_sv[39], COUPs[1], 0., 0., w_sv[45] );

      // Amplitude(s) for diagram number 44
      VVV1_0( w_sv[9], w_sv[45], w_sv[6], COUPs[0], &amp_sv[0] );
      jamp_sv[72] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[78] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[84] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[86] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[90] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[92] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[94] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[95] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 45 OF 1240 ***

      // Wavefunction(s) for diagram number 45
      // (none)

      // Amplitude(s) for diagram number 45
      FFV1_0( w_sv[3], w_sv[44], w_sv[9], COUPs[1], &amp_sv[0] );
      jamp_sv[90] += +amp_sv[0];
      jamp_sv[92] -= amp_sv[0];
      jamp_sv[94] -= amp_sv[0];
      jamp_sv[95] += +amp_sv[0];

      // *** DIAGRAM 46 OF 1240 ***

      // Wavefunction(s) for diagram number 46
      // (none)

      // Amplitude(s) for diagram number 46
      VVV1_0( w_sv[14], w_sv[45], w_sv[4], COUPs[0], &amp_sv[0] );
      jamp_sv[73] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[79] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[84] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[86] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[88] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[89] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[90] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[92] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 47 OF 1240 ***

      // Wavefunction(s) for diagram number 47
      // (none)

      // Amplitude(s) for diagram number 47
      FFV1_0( w_sv[3], w_sv[43], w_sv[14], COUPs[1], &amp_sv[0] );
      jamp_sv[84] += +amp_sv[0];
      jamp_sv[86] -= amp_sv[0];
      jamp_sv[88] -= amp_sv[0];
      jamp_sv[89] += +amp_sv[0];

      // *** DIAGRAM 48 OF 1240 ***

      // Wavefunction(s) for diagram number 48
      // (none)

      // Amplitude(s) for diagram number 48
      FFV1_0( w_sv[3], w_sv[39], w_sv[18], COUPs[1], &amp_sv[0] );
      jamp_sv[72] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[73] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[78] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[79] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[88] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[89] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[94] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[95] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[39], w_sv[19], COUPs[1], &amp_sv[0] );
      jamp_sv[73] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[79] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[84] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[86] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[88] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[89] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[90] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[92] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[39], w_sv[20], COUPs[1], &amp_sv[0] );
      jamp_sv[72] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[78] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[84] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[86] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[90] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[92] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[94] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[95] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 49 OF 1240 ***

      // Wavefunction(s) for diagram number 49
      FFV1_2( w_sv[3], w_sv[4], COUPs[1], cIPD[0], cIPD[1], w_sv[46] );
      FFV1_1( w_sv[39], w_sv[7], COUPs[1], cIPD[0], cIPD[1], w_sv[47] );

      // Amplitude(s) for diagram number 49
      FFV1_0( w_sv[46], w_sv[47], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[73] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[79] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 50 OF 1240 ***

      // Wavefunction(s) for diagram number 50
      FFV1_2( w_sv[46], w_sv[7], COUPs[1], cIPD[0], cIPD[1], w_sv[48] );

      // Amplitude(s) for diagram number 50
      FFV1_0( w_sv[48], w_sv[39], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[90] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[92] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 51 OF 1240 ***

      // Wavefunction(s) for diagram number 51
      // (none)

      // Amplitude(s) for diagram number 51
      FFV1_0( w_sv[46], w_sv[39], w_sv[14], COUPs[1], &amp_sv[0] );
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[92] += +amp_sv[0];

      // *** DIAGRAM 52 OF 1240 ***

      // Wavefunction(s) for diagram number 52
      // (none)

      // Amplitude(s) for diagram number 52
      FFV1_0( w_sv[41], w_sv[47], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[72] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[78] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 53 OF 1240 ***

      // Wavefunction(s) for diagram number 53
      // (none)

      // Amplitude(s) for diagram number 53
      FFV1_0( w_sv[42], w_sv[39], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[84] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[86] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 54 OF 1240 ***

      // Wavefunction(s) for diagram number 54
      // (none)

      // Amplitude(s) for diagram number 54
      FFV1_0( w_sv[41], w_sv[39], w_sv[9], COUPs[1], &amp_sv[0] );
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];

      // *** DIAGRAM 55 OF 1240 ***

      // Wavefunction(s) for diagram number 55
      // (none)

      // Amplitude(s) for diagram number 55
      FFV1_0( w_sv[3], w_sv[47], w_sv[27], COUPs[1], &amp_sv[0] );
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[73] -= amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[79] += +amp_sv[0];

      // *** DIAGRAM 56 OF 1240 ***

      // Wavefunction(s) for diagram number 56
      // (none)

      // Amplitude(s) for diagram number 56
      FFV1_0( w_sv[34], w_sv[39], w_sv[27], COUPs[1], &amp_sv[0] );
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[89] -= amp_sv[0];
      jamp_sv[94] -= amp_sv[0];
      jamp_sv[95] += +amp_sv[0];

      // *** DIAGRAM 57 OF 1240 ***

      // Wavefunction(s) for diagram number 57
      // (none)

      // Amplitude(s) for diagram number 57
      FFV1_0( w_sv[3], w_sv[39], w_sv[28], COUPs[1], &amp_sv[0] );
      jamp_sv[72] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[73] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[78] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[79] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[88] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[89] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[94] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[95] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 58 OF 1240 ***

      // Wavefunction(s) for diagram number 58
      FFV1_1( w_sv[2], w_sv[6], COUPs[1], cIPD[0], cIPD[1], w_sv[47] );
      FFV1_1( w_sv[47], w_sv[4], COUPs[1], cIPD[0], cIPD[1], w_sv[49] );

      // Amplitude(s) for diagram number 58
      FFV1_0( w_sv[34], w_sv[49], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[112] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[113] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 59 OF 1240 ***

      // Wavefunction(s) for diagram number 59
      FFV1_1( w_sv[47], w_sv[5], COUPs[1], cIPD[0], cIPD[1], w_sv[50] );

      // Amplitude(s) for diagram number 59
      FFV1_0( w_sv[34], w_sv[50], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[118] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[119] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 60 OF 1240 ***

      // Wavefunction(s) for diagram number 60
      FFV1P0_3( w_sv[3], w_sv[47], COUPs[1], 0., 0., w_sv[51] );

      // Amplitude(s) for diagram number 60
      VVV1_0( w_sv[9], w_sv[51], w_sv[5], COUPs[0], &amp_sv[0] );
      jamp_sv[96] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[102] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[108] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[110] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[114] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[116] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[118] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[119] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 61 OF 1240 ***

      // Wavefunction(s) for diagram number 61
      // (none)

      // Amplitude(s) for diagram number 61
      FFV1_0( w_sv[3], w_sv[50], w_sv[9], COUPs[1], &amp_sv[0] );
      jamp_sv[114] += +amp_sv[0];
      jamp_sv[116] -= amp_sv[0];
      jamp_sv[118] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];

      // *** DIAGRAM 62 OF 1240 ***

      // Wavefunction(s) for diagram number 62
      // (none)

      // Amplitude(s) for diagram number 62
      VVV1_0( w_sv[12], w_sv[51], w_sv[4], COUPs[0], &amp_sv[0] );
      jamp_sv[97] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[103] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[108] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[110] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[112] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[113] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[114] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[116] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 63 OF 1240 ***

      // Wavefunction(s) for diagram number 63
      // (none)

      // Amplitude(s) for diagram number 63
      FFV1_0( w_sv[3], w_sv[49], w_sv[12], COUPs[1], &amp_sv[0] );
      jamp_sv[108] += +amp_sv[0];
      jamp_sv[110] -= amp_sv[0];
      jamp_sv[112] -= amp_sv[0];
      jamp_sv[113] += +amp_sv[0];

      // *** DIAGRAM 64 OF 1240 ***

      // Wavefunction(s) for diagram number 64
      // (none)

      // Amplitude(s) for diagram number 64
      FFV1_0( w_sv[3], w_sv[47], w_sv[15], COUPs[1], &amp_sv[0] );
      jamp_sv[96] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[97] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[102] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[103] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[112] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[113] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[118] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[119] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[47], w_sv[16], COUPs[1], &amp_sv[0] );
      jamp_sv[97] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[103] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[108] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[110] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[112] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[113] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[114] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[116] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[47], w_sv[17], COUPs[1], &amp_sv[0] );
      jamp_sv[96] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[102] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[108] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[110] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[114] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[116] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[118] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[119] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 65 OF 1240 ***

      // Wavefunction(s) for diagram number 65
      FFV1_1( w_sv[47], w_sv[7], COUPs[1], cIPD[0], cIPD[1], w_sv[52] );

      // Amplitude(s) for diagram number 65
      FFV1_0( w_sv[46], w_sv[52], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[97] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[103] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 66 OF 1240 ***

      // Wavefunction(s) for diagram number 66
      // (none)

      // Amplitude(s) for diagram number 66
      FFV1_0( w_sv[48], w_sv[47], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[114] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[116] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 67 OF 1240 ***

      // Wavefunction(s) for diagram number 67
      // (none)

      // Amplitude(s) for diagram number 67
      FFV1_0( w_sv[46], w_sv[47], w_sv[12], COUPs[1], &amp_sv[0] );
      jamp_sv[97] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];

      // *** DIAGRAM 68 OF 1240 ***

      // Wavefunction(s) for diagram number 68
      // (none)

      // Amplitude(s) for diagram number 68
      FFV1_0( w_sv[38], w_sv[52], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[96] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[102] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 69 OF 1240 ***

      // Wavefunction(s) for diagram number 69
      // (none)

      // Amplitude(s) for diagram number 69
      FFV1_0( w_sv[40], w_sv[47], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[108] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[110] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 70 OF 1240 ***

      // Wavefunction(s) for diagram number 70
      // (none)

      // Amplitude(s) for diagram number 70
      FFV1_0( w_sv[38], w_sv[47], w_sv[9], COUPs[1], &amp_sv[0] );
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];

      // *** DIAGRAM 71 OF 1240 ***

      // Wavefunction(s) for diagram number 71
      // (none)

      // Amplitude(s) for diagram number 71
      FFV1_0( w_sv[3], w_sv[52], w_sv[24], COUPs[1], &amp_sv[0] );
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[97] -= amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[103] += +amp_sv[0];

      // *** DIAGRAM 72 OF 1240 ***

      // Wavefunction(s) for diagram number 72
      // (none)

      // Amplitude(s) for diagram number 72
      FFV1_0( w_sv[34], w_sv[47], w_sv[24], COUPs[1], &amp_sv[0] );
      jamp_sv[112] += +amp_sv[0];
      jamp_sv[113] -= amp_sv[0];
      jamp_sv[118] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];

      // *** DIAGRAM 73 OF 1240 ***

      // Wavefunction(s) for diagram number 73
      // (none)

      // Amplitude(s) for diagram number 73
      FFV1_0( w_sv[3], w_sv[47], w_sv[26], COUPs[1], &amp_sv[0] );
      jamp_sv[96] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[97] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[102] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[103] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[112] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[113] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[118] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[119] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 74 OF 1240 ***

      // Wavefunction(s) for diagram number 74
      FFV1_1( w_sv[2], w_sv[7], COUPs[1], cIPD[0], cIPD[1], w_sv[52] );
      FFV1_2( w_sv[46], w_sv[5], COUPs[1], cIPD[0], cIPD[1], w_sv[7] );

      // Amplitude(s) for diagram number 74
      FFV1_0( w_sv[7], w_sv[52], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[5] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[29] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 75 OF 1240 ***

      // Wavefunction(s) for diagram number 75
      FFV1_2( w_sv[46], w_sv[6], COUPs[1], cIPD[0], cIPD[1], w_sv[53] );

      // Amplitude(s) for diagram number 75
      FFV1_0( w_sv[53], w_sv[52], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[3] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[27] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 76 OF 1240 ***

      // Wavefunction(s) for diagram number 76
      FFV1P0_3( w_sv[46], w_sv[2], COUPs[1], 0., 0., w_sv[54] );

      // Amplitude(s) for diagram number 76
      VVV1_0( w_sv[12], w_sv[54], w_sv[6], COUPs[0], &amp_sv[0] );
      jamp_sv[3] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[27] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[73] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[79] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[97] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[103] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[114] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[116] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 77 OF 1240 ***

      // Wavefunction(s) for diagram number 77
      // (none)

      // Amplitude(s) for diagram number 77
      FFV1_0( w_sv[53], w_sv[2], w_sv[12], COUPs[1], &amp_sv[0] );
      jamp_sv[3] += +amp_sv[0];
      jamp_sv[27] -= amp_sv[0];
      jamp_sv[73] -= amp_sv[0];
      jamp_sv[79] += +amp_sv[0];

      // *** DIAGRAM 78 OF 1240 ***

      // Wavefunction(s) for diagram number 78
      // (none)

      // Amplitude(s) for diagram number 78
      VVV1_0( w_sv[14], w_sv[54], w_sv[5], COUPs[0], &amp_sv[0] );
      jamp_sv[5] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[29] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[73] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[79] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[90] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[92] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[97] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[103] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 79 OF 1240 ***

      // Wavefunction(s) for diagram number 79
      // (none)

      // Amplitude(s) for diagram number 79
      FFV1_0( w_sv[7], w_sv[2], w_sv[14], COUPs[1], &amp_sv[0] );
      jamp_sv[5] += +amp_sv[0];
      jamp_sv[29] -= amp_sv[0];
      jamp_sv[97] -= amp_sv[0];
      jamp_sv[103] += +amp_sv[0];

      // *** DIAGRAM 80 OF 1240 ***

      // Wavefunction(s) for diagram number 80
      // (none)

      // Amplitude(s) for diagram number 80
      FFV1_0( w_sv[46], w_sv[2], w_sv[21], COUPs[1], &amp_sv[0] );
      jamp_sv[3] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[5] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[27] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[29] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[90] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[92] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[114] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[116] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[46], w_sv[2], w_sv[22], COUPs[1], &amp_sv[0] );
      jamp_sv[5] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[29] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[73] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[79] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[90] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[92] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[97] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[103] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[46], w_sv[2], w_sv[23], COUPs[1], &amp_sv[0] );
      jamp_sv[3] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[27] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[73] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[79] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[97] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[103] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[114] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[116] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 81 OF 1240 ***

      // Wavefunction(s) for diagram number 81
      // (none)

      // Amplitude(s) for diagram number 81
      FFV1_0( w_sv[46], w_sv[52], w_sv[29], COUPs[1], &amp_sv[0] );
      jamp_sv[3] += +amp_sv[0];
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[27] -= amp_sv[0];
      jamp_sv[29] += +amp_sv[0];

      // *** DIAGRAM 82 OF 1240 ***

      // Wavefunction(s) for diagram number 82
      // (none)

      // Amplitude(s) for diagram number 82
      FFV1_0( w_sv[48], w_sv[2], w_sv[29], COUPs[1], &amp_sv[0] );
      jamp_sv[90] += +amp_sv[0];
      jamp_sv[92] -= amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];

      // *** DIAGRAM 83 OF 1240 ***

      // Wavefunction(s) for diagram number 83
      // (none)

      // Amplitude(s) for diagram number 83
      FFV1_0( w_sv[46], w_sv[2], w_sv[25], COUPs[1], &amp_sv[0] );
      jamp_sv[3] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[5] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[27] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[29] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[90] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[92] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[114] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[116] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 84 OF 1240 ***

      // Wavefunction(s) for diagram number 84
      FFV1_2( w_sv[38], w_sv[4], COUPs[1], cIPD[0], cIPD[1], w_sv[25] );

      // Amplitude(s) for diagram number 84
      FFV1_0( w_sv[25], w_sv[52], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[4] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[28] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 85 OF 1240 ***

      // Wavefunction(s) for diagram number 85
      FFV1_2( w_sv[38], w_sv[6], COUPs[1], cIPD[0], cIPD[1], w_sv[48] );

      // Amplitude(s) for diagram number 85
      FFV1_0( w_sv[48], w_sv[52], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[1] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[25] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 86 OF 1240 ***

      // Wavefunction(s) for diagram number 86
      FFV1P0_3( w_sv[38], w_sv[2], COUPs[1], 0., 0., w_sv[23] );

      // Amplitude(s) for diagram number 86
      VVV1_0( w_sv[9], w_sv[23], w_sv[6], COUPs[0], &amp_sv[0] );
      jamp_sv[1] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[25] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[49] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[55] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[96] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[102] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[108] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[110] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 87 OF 1240 ***

      // Wavefunction(s) for diagram number 87
      // (none)

      // Amplitude(s) for diagram number 87
      FFV1_0( w_sv[48], w_sv[2], w_sv[9], COUPs[1], &amp_sv[0] );
      jamp_sv[1] += +amp_sv[0];
      jamp_sv[25] -= amp_sv[0];
      jamp_sv[49] -= amp_sv[0];
      jamp_sv[55] += +amp_sv[0];

      // *** DIAGRAM 88 OF 1240 ***

      // Wavefunction(s) for diagram number 88
      // (none)

      // Amplitude(s) for diagram number 88
      VVV1_0( w_sv[14], w_sv[23], w_sv[4], COUPs[0], &amp_sv[0] );
      jamp_sv[4] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[28] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[49] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[55] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[66] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[68] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[96] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[102] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 89 OF 1240 ***

      // Wavefunction(s) for diagram number 89
      // (none)

      // Amplitude(s) for diagram number 89
      FFV1_0( w_sv[25], w_sv[2], w_sv[14], COUPs[1], &amp_sv[0] );
      jamp_sv[4] += +amp_sv[0];
      jamp_sv[28] -= amp_sv[0];
      jamp_sv[96] -= amp_sv[0];
      jamp_sv[102] += +amp_sv[0];

      // *** DIAGRAM 90 OF 1240 ***

      // Wavefunction(s) for diagram number 90
      // (none)

      // Amplitude(s) for diagram number 90
      FFV1_0( w_sv[38], w_sv[2], w_sv[18], COUPs[1], &amp_sv[0] );
      jamp_sv[1] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[4] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[25] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[28] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[66] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[68] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[108] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[110] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[38], w_sv[2], w_sv[19], COUPs[1], &amp_sv[0] );
      jamp_sv[4] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[28] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[49] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[55] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[66] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[68] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[96] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[102] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[38], w_sv[2], w_sv[20], COUPs[1], &amp_sv[0] );
      jamp_sv[1] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[25] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[49] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[55] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[96] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[102] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[108] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[110] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 91 OF 1240 ***

      // Wavefunction(s) for diagram number 91
      // (none)

      // Amplitude(s) for diagram number 91
      FFV1_0( w_sv[38], w_sv[52], w_sv[27], COUPs[1], &amp_sv[0] );
      jamp_sv[1] += +amp_sv[0];
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[25] -= amp_sv[0];
      jamp_sv[28] += +amp_sv[0];

      // *** DIAGRAM 92 OF 1240 ***

      // Wavefunction(s) for diagram number 92
      // (none)

      // Amplitude(s) for diagram number 92
      FFV1_0( w_sv[40], w_sv[2], w_sv[27], COUPs[1], &amp_sv[0] );
      jamp_sv[66] += +amp_sv[0];
      jamp_sv[68] -= amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];

      // *** DIAGRAM 93 OF 1240 ***

      // Wavefunction(s) for diagram number 93
      // (none)

      // Amplitude(s) for diagram number 93
      FFV1_0( w_sv[38], w_sv[2], w_sv[28], COUPs[1], &amp_sv[0] );
      jamp_sv[1] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[4] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[25] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[28] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[66] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[68] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[108] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[110] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 94 OF 1240 ***

      // Wavefunction(s) for diagram number 94
      FFV1_2( w_sv[41], w_sv[4], COUPs[1], cIPD[0], cIPD[1], w_sv[28] );

      // Amplitude(s) for diagram number 94
      FFV1_0( w_sv[28], w_sv[52], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[2] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[26] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 95 OF 1240 ***

      // Wavefunction(s) for diagram number 95
      FFV1_2( w_sv[41], w_sv[5], COUPs[1], cIPD[0], cIPD[1], w_sv[40] );

      // Amplitude(s) for diagram number 95
      FFV1_0( w_sv[40], w_sv[52], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[0] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[24] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 96 OF 1240 ***

      // Wavefunction(s) for diagram number 96
      FFV1P0_3( w_sv[41], w_sv[2], COUPs[1], 0., 0., w_sv[20] );

      // Amplitude(s) for diagram number 96
      VVV1_0( w_sv[9], w_sv[20], w_sv[5], COUPs[0], &amp_sv[0] );
      jamp_sv[0] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[24] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[48] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[54] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[72] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[78] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[84] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[86] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 97 OF 1240 ***

      // Wavefunction(s) for diagram number 97
      // (none)

      // Amplitude(s) for diagram number 97
      FFV1_0( w_sv[40], w_sv[2], w_sv[9], COUPs[1], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[24] -= amp_sv[0];
      jamp_sv[48] -= amp_sv[0];
      jamp_sv[54] += +amp_sv[0];

      // *** DIAGRAM 98 OF 1240 ***

      // Wavefunction(s) for diagram number 98
      // (none)

      // Amplitude(s) for diagram number 98
      VVV1_0( w_sv[12], w_sv[20], w_sv[4], COUPs[0], &amp_sv[0] );
      jamp_sv[2] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[26] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[48] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[54] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[60] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[62] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[72] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[78] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 99 OF 1240 ***

      // Wavefunction(s) for diagram number 99
      // (none)

      // Amplitude(s) for diagram number 99
      FFV1_0( w_sv[28], w_sv[2], w_sv[12], COUPs[1], &amp_sv[0] );
      jamp_sv[2] += +amp_sv[0];
      jamp_sv[26] -= amp_sv[0];
      jamp_sv[72] -= amp_sv[0];
      jamp_sv[78] += +amp_sv[0];

      // *** DIAGRAM 100 OF 1240 ***

      // Wavefunction(s) for diagram number 100
      // (none)

      // Amplitude(s) for diagram number 100
      FFV1_0( w_sv[41], w_sv[2], w_sv[15], COUPs[1], &amp_sv[0] );
      jamp_sv[0] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[2] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[24] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[26] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[60] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[62] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[84] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[86] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[41], w_sv[2], w_sv[16], COUPs[1], &amp_sv[0] );
      jamp_sv[2] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[26] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[48] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[54] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[60] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[62] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[72] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[78] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[41], w_sv[2], w_sv[17], COUPs[1], &amp_sv[0] );
      jamp_sv[0] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[24] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[48] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[54] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[72] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[78] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[84] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[86] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 101 OF 1240 ***

      // Wavefunction(s) for diagram number 101
      // (none)

      // Amplitude(s) for diagram number 101
      FFV1_0( w_sv[41], w_sv[52], w_sv[24], COUPs[1], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[24] -= amp_sv[0];
      jamp_sv[26] += +amp_sv[0];

      // *** DIAGRAM 102 OF 1240 ***

      // Wavefunction(s) for diagram number 102
      // (none)

      // Amplitude(s) for diagram number 102
      FFV1_0( w_sv[42], w_sv[2], w_sv[24], COUPs[1], &amp_sv[0] );
      jamp_sv[60] += +amp_sv[0];
      jamp_sv[62] -= amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];

      // *** DIAGRAM 103 OF 1240 ***

      // Wavefunction(s) for diagram number 103
      // (none)

      // Amplitude(s) for diagram number 103
      FFV1_0( w_sv[41], w_sv[2], w_sv[26], COUPs[1], &amp_sv[0] );
      jamp_sv[0] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[2] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[24] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[26] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[60] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[62] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[84] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[86] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 104 OF 1240 ***

      // Wavefunction(s) for diagram number 104
      FFV1_2( w_sv[3], w_sv[24], COUPs[1], cIPD[0], cIPD[1], w_sv[26] );

      // Amplitude(s) for diagram number 104
      FFV1_0( w_sv[26], w_sv[52], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[4] += +amp_sv[0];
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[28] -= amp_sv[0];
      jamp_sv[29] += +amp_sv[0];

      // *** DIAGRAM 105 OF 1240 ***

      // Wavefunction(s) for diagram number 105
      VVV1P0_1( w_sv[24], w_sv[6], COUPs[0], 0., 0., w_sv[42] );

      // Amplitude(s) for diagram number 105
      FFV1_0( w_sv[3], w_sv[52], w_sv[42], COUPs[1], &amp_sv[0] );
      jamp_sv[0] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[2] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[4] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[5] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[24] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[26] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[28] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[29] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 106 OF 1240 ***

      // Wavefunction(s) for diagram number 106
      FFV1_1( w_sv[2], w_sv[24], COUPs[1], cIPD[0], cIPD[1], w_sv[17] );

      // Amplitude(s) for diagram number 106
      FFV1_0( w_sv[34], w_sv[17], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[64] += +amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[88] -= amp_sv[0];
      jamp_sv[89] += +amp_sv[0];

      // *** DIAGRAM 107 OF 1240 ***

      // Wavefunction(s) for diagram number 107
      // (none)

      // Amplitude(s) for diagram number 107
      FFV1_0( w_sv[34], w_sv[2], w_sv[42], COUPs[1], &amp_sv[0] );
      jamp_sv[64] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[65] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[88] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[89] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[112] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[113] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[118] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[119] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 108 OF 1240 ***

      // Wavefunction(s) for diagram number 108
      // (none)

      // Amplitude(s) for diagram number 108
      FFV1_0( w_sv[3], w_sv[17], w_sv[14], COUPs[1], &amp_sv[0] );
      jamp_sv[60] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[62] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[64] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[65] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[84] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[86] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[88] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[89] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 109 OF 1240 ***

      // Wavefunction(s) for diagram number 109
      // (none)

      // Amplitude(s) for diagram number 109
      FFV1_0( w_sv[26], w_sv[2], w_sv[14], COUPs[1], &amp_sv[0] );
      jamp_sv[4] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[5] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[28] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[29] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[96] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[97] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[102] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[103] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 110 OF 1240 ***

      // Wavefunction(s) for diagram number 110
      FFV1_2( w_sv[3], w_sv[27], COUPs[1], cIPD[0], cIPD[1], w_sv[14] );

      // Amplitude(s) for diagram number 110
      FFV1_0( w_sv[14], w_sv[52], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[2] += +amp_sv[0];
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[26] -= amp_sv[0];
      jamp_sv[27] += +amp_sv[0];

      // *** DIAGRAM 111 OF 1240 ***

      // Wavefunction(s) for diagram number 111
      VVV1P0_1( w_sv[27], w_sv[5], COUPs[0], 0., 0., w_sv[16] );

      // Amplitude(s) for diagram number 111
      FFV1_0( w_sv[3], w_sv[52], w_sv[16], COUPs[1], &amp_sv[0] );
      jamp_sv[1] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[2] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[3] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[4] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[25] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[26] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[27] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[28] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 112 OF 1240 ***

      // Wavefunction(s) for diagram number 112
      FFV1_1( w_sv[2], w_sv[27], COUPs[1], cIPD[0], cIPD[1], w_sv[15] );

      // Amplitude(s) for diagram number 112
      FFV1_0( w_sv[34], w_sv[15], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[70] += +amp_sv[0];
      jamp_sv[71] -= amp_sv[0];
      jamp_sv[112] -= amp_sv[0];
      jamp_sv[113] += +amp_sv[0];

      // *** DIAGRAM 113 OF 1240 ***

      // Wavefunction(s) for diagram number 113
      // (none)

      // Amplitude(s) for diagram number 113
      FFV1_0( w_sv[34], w_sv[2], w_sv[16], COUPs[1], &amp_sv[0] );
      jamp_sv[70] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[71] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[88] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[89] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[94] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[95] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[112] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[113] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 114 OF 1240 ***

      // Wavefunction(s) for diagram number 114
      // (none)

      // Amplitude(s) for diagram number 114
      FFV1_0( w_sv[3], w_sv[15], w_sv[12], COUPs[1], &amp_sv[0] );
      jamp_sv[66] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[68] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[70] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[71] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[108] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[110] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[112] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[113] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 115 OF 1240 ***

      // Wavefunction(s) for diagram number 115
      // (none)

      // Amplitude(s) for diagram number 115
      FFV1_0( w_sv[14], w_sv[2], w_sv[12], COUPs[1], &amp_sv[0] );
      jamp_sv[2] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[3] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[26] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[27] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[72] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[73] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[78] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[79] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 116 OF 1240 ***

      // Wavefunction(s) for diagram number 116
      FFV1_2( w_sv[3], w_sv[29], COUPs[1], cIPD[0], cIPD[1], w_sv[12] );

      // Amplitude(s) for diagram number 116
      FFV1_0( w_sv[12], w_sv[52], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[24] -= amp_sv[0];
      jamp_sv[25] += +amp_sv[0];

      // *** DIAGRAM 117 OF 1240 ***

      // Wavefunction(s) for diagram number 117
      VVV1P0_1( w_sv[4], w_sv[29], COUPs[0], 0., 0., w_sv[19] );

      // Amplitude(s) for diagram number 117
      FFV1_0( w_sv[3], w_sv[52], w_sv[19], COUPs[1], &amp_sv[0] );
      jamp_sv[0] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[1] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[3] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[5] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[24] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[25] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[27] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[29] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 118 OF 1240 ***

      // Wavefunction(s) for diagram number 118
      FFV1_1( w_sv[2], w_sv[29], COUPs[1], cIPD[0], cIPD[1], w_sv[18] );

      // Amplitude(s) for diagram number 118
      FFV1_0( w_sv[34], w_sv[18], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[94] += +amp_sv[0];
      jamp_sv[95] -= amp_sv[0];
      jamp_sv[118] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];

      // *** DIAGRAM 119 OF 1240 ***

      // Wavefunction(s) for diagram number 119
      // (none)

      // Amplitude(s) for diagram number 119
      FFV1_0( w_sv[34], w_sv[2], w_sv[19], COUPs[1], &amp_sv[0] );
      jamp_sv[64] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[65] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[70] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[71] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[94] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[95] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[118] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[119] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 120 OF 1240 ***

      // Wavefunction(s) for diagram number 120
      // (none)

      // Amplitude(s) for diagram number 120
      FFV1_0( w_sv[3], w_sv[18], w_sv[9], COUPs[1], &amp_sv[0] );
      jamp_sv[90] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[92] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[94] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[95] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[114] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[116] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[118] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[119] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 121 OF 1240 ***

      // Wavefunction(s) for diagram number 121
      // (none)

      // Amplitude(s) for diagram number 121
      FFV1_0( w_sv[12], w_sv[2], w_sv[9], COUPs[1], &amp_sv[0] );
      jamp_sv[0] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[1] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[24] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[25] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[48] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[49] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[54] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[55] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 122 OF 1240 ***

      // Wavefunction(s) for diagram number 122
      // (none)

      // Amplitude(s) for diagram number 122
      FFV1_0( w_sv[3], w_sv[52], w_sv[30], COUPs[1], &amp_sv[0] );
      jamp_sv[0] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[1] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[3] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[5] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[24] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[25] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[27] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[29] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[52], w_sv[31], COUPs[1], &amp_sv[0] );
      jamp_sv[1] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[2] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[3] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[4] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[25] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[26] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[27] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[28] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[52], w_sv[32], COUPs[1], &amp_sv[0] );
      jamp_sv[0] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[2] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[4] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[5] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[24] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[26] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[28] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[29] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 123 OF 1240 ***

      // Wavefunction(s) for diagram number 123
      // (none)

      // Amplitude(s) for diagram number 123
      FFV1_0( w_sv[34], w_sv[2], w_sv[30], COUPs[1], &amp_sv[0] );
      jamp_sv[64] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[65] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[70] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[71] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[94] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[95] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[118] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[119] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[34], w_sv[2], w_sv[31], COUPs[1], &amp_sv[0] );
      jamp_sv[70] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[71] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[88] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[89] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[94] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[95] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[112] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[113] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[34], w_sv[2], w_sv[32], COUPs[1], &amp_sv[0] );
      jamp_sv[64] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[65] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[88] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[89] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[112] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[113] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[118] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[119] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 124 OF 1240 ***

      // Wavefunction(s) for diagram number 124
      FFV1_1( w_sv[2], w_sv[0], COUPs[1], cIPD[0], cIPD[1], w_sv[34] );
      FFV1_2( w_sv[3], w_sv[1], COUPs[1], cIPD[0], cIPD[1], w_sv[52] );
      FFV1_1( w_sv[34], w_sv[4], COUPs[1], cIPD[0], cIPD[1], w_sv[9] );
      FFV1_2( w_sv[52], w_sv[5], COUPs[1], cIPD[0], cIPD[1], w_sv[22] );

      // Amplitude(s) for diagram number 124
      FFV1_0( w_sv[22], w_sv[9], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[11] -= amp_sv[0];

      // *** DIAGRAM 125 OF 1240 ***

      // Wavefunction(s) for diagram number 125
      FFV1_2( w_sv[52], w_sv[6], COUPs[1], cIPD[0], cIPD[1], w_sv[21] );

      // Amplitude(s) for diagram number 125
      FFV1_0( w_sv[21], w_sv[9], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[9] -= amp_sv[0];

      // *** DIAGRAM 126 OF 1240 ***

      // Wavefunction(s) for diagram number 126
      FFV1_1( w_sv[34], w_sv[5], COUPs[1], cIPD[0], cIPD[1], w_sv[55] );
      FFV1_2( w_sv[52], w_sv[4], COUPs[1], cIPD[0], cIPD[1], w_sv[56] );

      // Amplitude(s) for diagram number 126
      FFV1_0( w_sv[56], w_sv[55], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[17] -= amp_sv[0];

      // *** DIAGRAM 127 OF 1240 ***

      // Wavefunction(s) for diagram number 127
      // (none)

      // Amplitude(s) for diagram number 127
      FFV1_0( w_sv[21], w_sv[55], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[15] -= amp_sv[0];

      // *** DIAGRAM 128 OF 1240 ***

      // Wavefunction(s) for diagram number 128
      FFV1_1( w_sv[34], w_sv[6], COUPs[1], cIPD[0], cIPD[1], w_sv[57] );

      // Amplitude(s) for diagram number 128
      FFV1_0( w_sv[56], w_sv[57], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[23] -= amp_sv[0];

      // *** DIAGRAM 129 OF 1240 ***

      // Wavefunction(s) for diagram number 129
      // (none)

      // Amplitude(s) for diagram number 129
      FFV1_0( w_sv[22], w_sv[57], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[21] -= amp_sv[0];

      // *** DIAGRAM 130 OF 1240 ***

      // Wavefunction(s) for diagram number 130
      FFV1P0_3( w_sv[52], w_sv[34], COUPs[1], 0., 0., w_sv[58] );

      // Amplitude(s) for diagram number 130
      VVV1_0( w_sv[24], w_sv[6], w_sv[58], COUPs[0], &amp_sv[0] );
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[23] += +amp_sv[0];

      // *** DIAGRAM 131 OF 1240 ***

      // Wavefunction(s) for diagram number 131
      FFV1_1( w_sv[34], w_sv[24], COUPs[1], cIPD[0], cIPD[1], w_sv[59] );

      // Amplitude(s) for diagram number 131
      FFV1_0( w_sv[52], w_sv[59], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[9] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[15] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 132 OF 1240 ***

      // Wavefunction(s) for diagram number 132
      // (none)

      // Amplitude(s) for diagram number 132
      FFV1_0( w_sv[52], w_sv[57], w_sv[24], COUPs[1], &amp_sv[0] );
      jamp_sv[21] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[23] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 133 OF 1240 ***

      // Wavefunction(s) for diagram number 133
      // (none)

      // Amplitude(s) for diagram number 133
      VVV1_0( w_sv[27], w_sv[5], w_sv[58], COUPs[0], &amp_sv[0] );
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[21] -= amp_sv[0];

      // *** DIAGRAM 134 OF 1240 ***

      // Wavefunction(s) for diagram number 134
      FFV1_1( w_sv[34], w_sv[27], COUPs[1], cIPD[0], cIPD[1], w_sv[60] );

      // Amplitude(s) for diagram number 134
      FFV1_0( w_sv[52], w_sv[60], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[11] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[21] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 135 OF 1240 ***

      // Wavefunction(s) for diagram number 135
      // (none)

      // Amplitude(s) for diagram number 135
      FFV1_0( w_sv[52], w_sv[55], w_sv[27], COUPs[1], &amp_sv[0] );
      jamp_sv[15] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[17] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 136 OF 1240 ***

      // Wavefunction(s) for diagram number 136
      // (none)

      // Amplitude(s) for diagram number 136
      VVV1_0( w_sv[4], w_sv[29], w_sv[58], COUPs[0], &amp_sv[0] );
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[11] -= amp_sv[0];
      jamp_sv[17] -= amp_sv[0];
      jamp_sv[23] += +amp_sv[0];

      // *** DIAGRAM 137 OF 1240 ***

      // Wavefunction(s) for diagram number 137
      // (none)

      // Amplitude(s) for diagram number 137
      FFV1_0( w_sv[52], w_sv[9], w_sv[29], COUPs[1], &amp_sv[0] );
      jamp_sv[9] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[11] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 138 OF 1240 ***

      // Wavefunction(s) for diagram number 138
      FFV1_1( w_sv[34], w_sv[29], COUPs[1], cIPD[0], cIPD[1], w_sv[58] );

      // Amplitude(s) for diagram number 138
      FFV1_0( w_sv[52], w_sv[58], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[17] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[23] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 139 OF 1240 ***

      // Wavefunction(s) for diagram number 139
      // (none)

      // Amplitude(s) for diagram number 139
      FFV1_0( w_sv[52], w_sv[34], w_sv[30], COUPs[1], &amp_sv[0] );
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[11] -= amp_sv[0];
      jamp_sv[17] -= amp_sv[0];
      jamp_sv[23] += +amp_sv[0];
      FFV1_0( w_sv[52], w_sv[34], w_sv[31], COUPs[1], &amp_sv[0] );
      jamp_sv[11] -= amp_sv[0];
      jamp_sv[15] += +amp_sv[0];
      jamp_sv[17] -= amp_sv[0];
      jamp_sv[21] += +amp_sv[0];
      FFV1_0( w_sv[52], w_sv[34], w_sv[32], COUPs[1], &amp_sv[0] );
      jamp_sv[9] -= amp_sv[0];
      jamp_sv[15] += +amp_sv[0];
      jamp_sv[21] += +amp_sv[0];
      jamp_sv[23] -= amp_sv[0];

      // *** DIAGRAM 140 OF 1240 ***

      // Wavefunction(s) for diagram number 140
      VVV1P0_1( w_sv[1], w_sv[4], COUPs[0], 0., 0., w_sv[61] );
      FFV1P0_3( w_sv[3], w_sv[34], COUPs[1], 0., 0., w_sv[62] );
      VVV1P0_1( w_sv[61], w_sv[5], COUPs[0], 0., 0., w_sv[63] );

      // Amplitude(s) for diagram number 140
      VVV1_0( w_sv[62], w_sv[63], w_sv[6], COUPs[0], &amp_sv[0] );
      jamp_sv[0] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[6] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[12] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[14] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[18] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[20] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[22] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[23] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 141 OF 1240 ***

      // Wavefunction(s) for diagram number 141
      VVV1P0_1( w_sv[61], w_sv[6], COUPs[0], 0., 0., w_sv[64] );

      // Amplitude(s) for diagram number 141
      VVV1_0( w_sv[62], w_sv[64], w_sv[5], COUPs[0], &amp_sv[0] );
      jamp_sv[1] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[7] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[12] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[14] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[16] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[17] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[18] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[20] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 142 OF 1240 ***

      // Wavefunction(s) for diagram number 142
      // (none)

      // Amplitude(s) for diagram number 142
      VVVV1_0( w_sv[61], w_sv[5], w_sv[6], w_sv[62], COUPs[2], &amp_sv[0] );
      jamp_sv[0] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[6] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[12] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[14] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[18] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[20] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[22] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[23] += +cxtype(0,1)*amp_sv[0];
      VVVV3_0( w_sv[61], w_sv[5], w_sv[6], w_sv[62], COUPs[2], &amp_sv[0] );
      jamp_sv[1] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[7] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[12] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[14] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[16] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[17] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[18] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[20] -= cxtype(0,1)*amp_sv[0];
      VVVV4_0( w_sv[61], w_sv[5], w_sv[6], w_sv[62], COUPs[2], &amp_sv[0] );
      jamp_sv[0] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[1] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[6] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[7] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[16] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[17] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[22] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[23] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 143 OF 1240 ***

      // Wavefunction(s) for diagram number 143
      FFV1_2( w_sv[3], w_sv[61], COUPs[1], cIPD[0], cIPD[1], w_sv[65] );

      // Amplitude(s) for diagram number 143
      FFV1_0( w_sv[65], w_sv[55], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[16] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[17] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 144 OF 1240 ***

      // Wavefunction(s) for diagram number 144
      // (none)

      // Amplitude(s) for diagram number 144
      FFV1_0( w_sv[3], w_sv[55], w_sv[64], COUPs[1], &amp_sv[0] );
      jamp_sv[12] += +amp_sv[0];
      jamp_sv[14] -= amp_sv[0];
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[17] += +amp_sv[0];

      // *** DIAGRAM 145 OF 1240 ***

      // Wavefunction(s) for diagram number 145
      // (none)

      // Amplitude(s) for diagram number 145
      FFV1_0( w_sv[65], w_sv[57], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[22] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[23] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 146 OF 1240 ***

      // Wavefunction(s) for diagram number 146
      // (none)

      // Amplitude(s) for diagram number 146
      FFV1_0( w_sv[3], w_sv[57], w_sv[63], COUPs[1], &amp_sv[0] );
      jamp_sv[18] += +amp_sv[0];
      jamp_sv[20] -= amp_sv[0];
      jamp_sv[22] -= amp_sv[0];
      jamp_sv[23] += +amp_sv[0];

      // *** DIAGRAM 147 OF 1240 ***

      // Wavefunction(s) for diagram number 147
      FFV1_1( w_sv[34], w_sv[61], COUPs[1], cIPD[0], cIPD[1], w_sv[66] );

      // Amplitude(s) for diagram number 147
      FFV1_0( w_sv[38], w_sv[66], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[1] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[7] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 148 OF 1240 ***

      // Wavefunction(s) for diagram number 148
      FFV1P0_3( w_sv[38], w_sv[34], COUPs[1], 0., 0., w_sv[67] );

      // Amplitude(s) for diagram number 148
      VVV1_0( w_sv[61], w_sv[6], w_sv[67], COUPs[0], &amp_sv[0] );
      jamp_sv[1] += +amp_sv[0];
      jamp_sv[7] -= amp_sv[0];
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[20] += +amp_sv[0];

      // *** DIAGRAM 149 OF 1240 ***

      // Wavefunction(s) for diagram number 149
      // (none)

      // Amplitude(s) for diagram number 149
      FFV1_0( w_sv[38], w_sv[57], w_sv[61], COUPs[1], &amp_sv[0] );
      jamp_sv[18] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[20] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 150 OF 1240 ***

      // Wavefunction(s) for diagram number 150
      // (none)

      // Amplitude(s) for diagram number 150
      FFV1_0( w_sv[41], w_sv[66], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[0] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[6] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 151 OF 1240 ***

      // Wavefunction(s) for diagram number 151
      FFV1P0_3( w_sv[41], w_sv[34], COUPs[1], 0., 0., w_sv[68] );

      // Amplitude(s) for diagram number 151
      VVV1_0( w_sv[61], w_sv[5], w_sv[68], COUPs[0], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[14] += +amp_sv[0];

      // *** DIAGRAM 152 OF 1240 ***

      // Wavefunction(s) for diagram number 152
      // (none)

      // Amplitude(s) for diagram number 152
      FFV1_0( w_sv[41], w_sv[55], w_sv[61], COUPs[1], &amp_sv[0] );
      jamp_sv[12] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[14] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 153 OF 1240 ***

      // Wavefunction(s) for diagram number 153
      // (none)

      // Amplitude(s) for diagram number 153
      FFV1_0( w_sv[3], w_sv[66], w_sv[29], COUPs[1], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[7] += +amp_sv[0];

      // *** DIAGRAM 154 OF 1240 ***

      // Wavefunction(s) for diagram number 154
      // (none)

      // Amplitude(s) for diagram number 154
      VVV1_0( w_sv[61], w_sv[29], w_sv[62], COUPs[0], &amp_sv[0] );
      jamp_sv[0] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[1] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[6] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[7] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[16] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[17] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[22] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[23] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 155 OF 1240 ***

      // Wavefunction(s) for diagram number 155
      // (none)

      // Amplitude(s) for diagram number 155
      FFV1_0( w_sv[3], w_sv[58], w_sv[61], COUPs[1], &amp_sv[0] );
      jamp_sv[16] += +amp_sv[0];
      jamp_sv[17] -= amp_sv[0];
      jamp_sv[22] -= amp_sv[0];
      jamp_sv[23] += +amp_sv[0];

      // *** DIAGRAM 156 OF 1240 ***

      // Wavefunction(s) for diagram number 156
      VVV1P0_1( w_sv[1], w_sv[5], COUPs[0], 0., 0., w_sv[66] );
      VVV1P0_1( w_sv[66], w_sv[4], COUPs[0], 0., 0., w_sv[69] );

      // Amplitude(s) for diagram number 156
      VVV1_0( w_sv[62], w_sv[69], w_sv[6], COUPs[0], &amp_sv[0] );
      jamp_sv[2] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[6] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[8] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[12] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[19] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[20] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[21] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[22] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 157 OF 1240 ***

      // Wavefunction(s) for diagram number 157
      VVV1P0_1( w_sv[66], w_sv[6], COUPs[0], 0., 0., w_sv[70] );

      // Amplitude(s) for diagram number 157
      VVV1_0( w_sv[62], w_sv[70], w_sv[4], COUPs[0], &amp_sv[0] );
      jamp_sv[3] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[6] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[8] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[10] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[11] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[13] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[19] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[22] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 158 OF 1240 ***

      // Wavefunction(s) for diagram number 158
      // (none)

      // Amplitude(s) for diagram number 158
      VVVV1_0( w_sv[66], w_sv[4], w_sv[6], w_sv[62], COUPs[2], &amp_sv[0] );
      jamp_sv[2] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[6] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[8] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[12] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[19] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[20] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[21] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[22] -= cxtype(0,1)*amp_sv[0];
      VVVV3_0( w_sv[66], w_sv[4], w_sv[6], w_sv[62], COUPs[2], &amp_sv[0] );
      jamp_sv[3] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[6] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[8] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[10] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[11] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[13] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[19] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[22] -= cxtype(0,1)*amp_sv[0];
      VVVV4_0( w_sv[66], w_sv[4], w_sv[6], w_sv[62], COUPs[2], &amp_sv[0] );
      jamp_sv[2] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[3] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[10] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[11] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[12] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[13] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[20] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[21] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 159 OF 1240 ***

      // Wavefunction(s) for diagram number 159
      FFV1_2( w_sv[3], w_sv[66], COUPs[1], cIPD[0], cIPD[1], w_sv[71] );

      // Amplitude(s) for diagram number 159
      FFV1_0( w_sv[71], w_sv[9], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[10] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[11] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 160 OF 1240 ***

      // Wavefunction(s) for diagram number 160
      // (none)

      // Amplitude(s) for diagram number 160
      FFV1_0( w_sv[3], w_sv[9], w_sv[70], COUPs[1], &amp_sv[0] );
      jamp_sv[6] += +amp_sv[0];
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[11] += +amp_sv[0];

      // *** DIAGRAM 161 OF 1240 ***

      // Wavefunction(s) for diagram number 161
      // (none)

      // Amplitude(s) for diagram number 161
      FFV1_0( w_sv[71], w_sv[57], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[20] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[21] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 162 OF 1240 ***

      // Wavefunction(s) for diagram number 162
      // (none)

      // Amplitude(s) for diagram number 162
      FFV1_0( w_sv[3], w_sv[57], w_sv[69], COUPs[1], &amp_sv[0] );
      jamp_sv[19] += +amp_sv[0];
      jamp_sv[20] -= amp_sv[0];
      jamp_sv[21] += +amp_sv[0];
      jamp_sv[22] -= amp_sv[0];

      // *** DIAGRAM 163 OF 1240 ***

      // Wavefunction(s) for diagram number 163
      FFV1_1( w_sv[34], w_sv[66], COUPs[1], cIPD[0], cIPD[1], w_sv[72] );

      // Amplitude(s) for diagram number 163
      FFV1_0( w_sv[46], w_sv[72], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[3] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[13] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 164 OF 1240 ***

      // Wavefunction(s) for diagram number 164
      FFV1P0_3( w_sv[46], w_sv[34], COUPs[1], 0., 0., w_sv[73] );

      // Amplitude(s) for diagram number 164
      VVV1_0( w_sv[66], w_sv[6], w_sv[73], COUPs[0], &amp_sv[0] );
      jamp_sv[3] += +amp_sv[0];
      jamp_sv[13] -= amp_sv[0];
      jamp_sv[19] -= amp_sv[0];
      jamp_sv[22] += +amp_sv[0];

      // *** DIAGRAM 165 OF 1240 ***

      // Wavefunction(s) for diagram number 165
      // (none)

      // Amplitude(s) for diagram number 165
      FFV1_0( w_sv[46], w_sv[57], w_sv[66], COUPs[1], &amp_sv[0] );
      jamp_sv[19] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[22] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 166 OF 1240 ***

      // Wavefunction(s) for diagram number 166
      // (none)

      // Amplitude(s) for diagram number 166
      FFV1_0( w_sv[41], w_sv[72], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[2] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[12] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 167 OF 1240 ***

      // Wavefunction(s) for diagram number 167
      // (none)

      // Amplitude(s) for diagram number 167
      VVV1_0( w_sv[66], w_sv[4], w_sv[68], COUPs[0], &amp_sv[0] );
      jamp_sv[2] += +amp_sv[0];
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[8] += +amp_sv[0];
      jamp_sv[12] -= amp_sv[0];

      // *** DIAGRAM 168 OF 1240 ***

      // Wavefunction(s) for diagram number 168
      // (none)

      // Amplitude(s) for diagram number 168
      FFV1_0( w_sv[41], w_sv[9], w_sv[66], COUPs[1], &amp_sv[0] );
      jamp_sv[6] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[8] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 169 OF 1240 ***

      // Wavefunction(s) for diagram number 169
      // (none)

      // Amplitude(s) for diagram number 169
      FFV1_0( w_sv[3], w_sv[72], w_sv[27], COUPs[1], &amp_sv[0] );
      jamp_sv[2] += +amp_sv[0];
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[13] += +amp_sv[0];

      // *** DIAGRAM 170 OF 1240 ***

      // Wavefunction(s) for diagram number 170
      // (none)

      // Amplitude(s) for diagram number 170
      VVV1_0( w_sv[66], w_sv[27], w_sv[62], COUPs[0], &amp_sv[0] );
      jamp_sv[2] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[3] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[10] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[11] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[12] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[13] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[20] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[21] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 171 OF 1240 ***

      // Wavefunction(s) for diagram number 171
      // (none)

      // Amplitude(s) for diagram number 171
      FFV1_0( w_sv[3], w_sv[60], w_sv[66], COUPs[1], &amp_sv[0] );
      jamp_sv[10] += +amp_sv[0];
      jamp_sv[11] -= amp_sv[0];
      jamp_sv[20] -= amp_sv[0];
      jamp_sv[21] += +amp_sv[0];

      // *** DIAGRAM 172 OF 1240 ***

      // Wavefunction(s) for diagram number 172
      VVV1P0_1( w_sv[1], w_sv[6], COUPs[0], 0., 0., w_sv[72] );
      VVV1P0_1( w_sv[72], w_sv[4], COUPs[0], 0., 0., w_sv[74] );

      // Amplitude(s) for diagram number 172
      VVV1_0( w_sv[62], w_sv[74], w_sv[5], COUPs[0], &amp_sv[0] );
      jamp_sv[4] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[7] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[10] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[13] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[14] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[15] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[16] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[18] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 173 OF 1240 ***

      // Wavefunction(s) for diagram number 173
      VVV1P0_1( w_sv[72], w_sv[5], COUPs[0], 0., 0., w_sv[75] );

      // Amplitude(s) for diagram number 173
      VVV1_0( w_sv[62], w_sv[75], w_sv[4], COUPs[0], &amp_sv[0] );
      jamp_sv[5] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[7] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[8] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[9] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[10] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[13] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[16] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[19] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 174 OF 1240 ***

      // Wavefunction(s) for diagram number 174
      // (none)

      // Amplitude(s) for diagram number 174
      VVVV1_0( w_sv[72], w_sv[4], w_sv[5], w_sv[62], COUPs[2], &amp_sv[0] );
      jamp_sv[4] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[7] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[10] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[13] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[14] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[15] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[16] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[18] += +cxtype(0,1)*amp_sv[0];
      VVVV3_0( w_sv[72], w_sv[4], w_sv[5], w_sv[62], COUPs[2], &amp_sv[0] );
      jamp_sv[5] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[7] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[8] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[9] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[10] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[13] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[16] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[19] += +cxtype(0,1)*amp_sv[0];
      VVVV4_0( w_sv[72], w_sv[4], w_sv[5], w_sv[62], COUPs[2], &amp_sv[0] );
      jamp_sv[4] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[5] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[8] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[9] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[14] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[15] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[18] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[19] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 175 OF 1240 ***

      // Wavefunction(s) for diagram number 175
      FFV1_2( w_sv[3], w_sv[72], COUPs[1], cIPD[0], cIPD[1], w_sv[76] );

      // Amplitude(s) for diagram number 175
      FFV1_0( w_sv[76], w_sv[9], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[8] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[9] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 176 OF 1240 ***

      // Wavefunction(s) for diagram number 176
      // (none)

      // Amplitude(s) for diagram number 176
      FFV1_0( w_sv[3], w_sv[9], w_sv[75], COUPs[1], &amp_sv[0] );
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[10] -= amp_sv[0];

      // *** DIAGRAM 177 OF 1240 ***

      // Wavefunction(s) for diagram number 177
      // (none)

      // Amplitude(s) for diagram number 177
      FFV1_0( w_sv[76], w_sv[55], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[14] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[15] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 178 OF 1240 ***

      // Wavefunction(s) for diagram number 178
      // (none)

      // Amplitude(s) for diagram number 178
      FFV1_0( w_sv[3], w_sv[55], w_sv[74], COUPs[1], &amp_sv[0] );
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[14] -= amp_sv[0];
      jamp_sv[15] += +amp_sv[0];
      jamp_sv[16] -= amp_sv[0];

      // *** DIAGRAM 179 OF 1240 ***

      // Wavefunction(s) for diagram number 179
      FFV1_1( w_sv[34], w_sv[72], COUPs[1], cIPD[0], cIPD[1], w_sv[77] );

      // Amplitude(s) for diagram number 179
      FFV1_0( w_sv[46], w_sv[77], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[5] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[19] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 180 OF 1240 ***

      // Wavefunction(s) for diagram number 180
      // (none)

      // Amplitude(s) for diagram number 180
      VVV1_0( w_sv[72], w_sv[5], w_sv[73], COUPs[0], &amp_sv[0] );
      jamp_sv[5] += +amp_sv[0];
      jamp_sv[13] -= amp_sv[0];
      jamp_sv[16] += +amp_sv[0];
      jamp_sv[19] -= amp_sv[0];

      // *** DIAGRAM 181 OF 1240 ***

      // Wavefunction(s) for diagram number 181
      // (none)

      // Amplitude(s) for diagram number 181
      FFV1_0( w_sv[46], w_sv[55], w_sv[72], COUPs[1], &amp_sv[0] );
      jamp_sv[13] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[16] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 182 OF 1240 ***

      // Wavefunction(s) for diagram number 182
      // (none)

      // Amplitude(s) for diagram number 182
      FFV1_0( w_sv[38], w_sv[77], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[4] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[18] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 183 OF 1240 ***

      // Wavefunction(s) for diagram number 183
      // (none)

      // Amplitude(s) for diagram number 183
      VVV1_0( w_sv[72], w_sv[4], w_sv[67], COUPs[0], &amp_sv[0] );
      jamp_sv[4] += +amp_sv[0];
      jamp_sv[7] -= amp_sv[0];
      jamp_sv[10] += +amp_sv[0];
      jamp_sv[18] -= amp_sv[0];

      // *** DIAGRAM 184 OF 1240 ***

      // Wavefunction(s) for diagram number 184
      // (none)

      // Amplitude(s) for diagram number 184
      FFV1_0( w_sv[38], w_sv[9], w_sv[72], COUPs[1], &amp_sv[0] );
      jamp_sv[7] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[10] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 185 OF 1240 ***

      // Wavefunction(s) for diagram number 185
      // (none)

      // Amplitude(s) for diagram number 185
      FFV1_0( w_sv[3], w_sv[77], w_sv[24], COUPs[1], &amp_sv[0] );
      jamp_sv[4] += +amp_sv[0];
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[19] += +amp_sv[0];

      // *** DIAGRAM 186 OF 1240 ***

      // Wavefunction(s) for diagram number 186
      // (none)

      // Amplitude(s) for diagram number 186
      VVV1_0( w_sv[72], w_sv[24], w_sv[62], COUPs[0], &amp_sv[0] );
      jamp_sv[4] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[5] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[8] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[9] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[14] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[15] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[18] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[19] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 187 OF 1240 ***

      // Wavefunction(s) for diagram number 187
      // (none)

      // Amplitude(s) for diagram number 187
      FFV1_0( w_sv[3], w_sv[59], w_sv[72], COUPs[1], &amp_sv[0] );
      jamp_sv[8] += +amp_sv[0];
      jamp_sv[9] -= amp_sv[0];
      jamp_sv[14] -= amp_sv[0];
      jamp_sv[15] += +amp_sv[0];

      // *** DIAGRAM 188 OF 1240 ***

      // Wavefunction(s) for diagram number 188
      FFV1_1( w_sv[34], w_sv[1], COUPs[1], cIPD[0], cIPD[1], w_sv[77] );

      // Amplitude(s) for diagram number 188
      FFV1_0( w_sv[7], w_sv[77], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[5] -= amp_sv[0];

      // *** DIAGRAM 189 OF 1240 ***

      // Wavefunction(s) for diagram number 189
      // (none)

      // Amplitude(s) for diagram number 189
      FFV1_0( w_sv[53], w_sv[77], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[3] -= amp_sv[0];

      // *** DIAGRAM 190 OF 1240 ***

      // Wavefunction(s) for diagram number 190
      FFV1_2( w_sv[46], w_sv[1], COUPs[1], cIPD[0], cIPD[1], w_sv[78] );

      // Amplitude(s) for diagram number 190
      FFV1_0( w_sv[78], w_sv[55], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[16] -= amp_sv[0];

      // *** DIAGRAM 191 OF 1240 ***

      // Wavefunction(s) for diagram number 191
      // (none)

      // Amplitude(s) for diagram number 191
      FFV1_0( w_sv[53], w_sv[55], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[13] -= amp_sv[0];

      // *** DIAGRAM 192 OF 1240 ***

      // Wavefunction(s) for diagram number 192
      // (none)

      // Amplitude(s) for diagram number 192
      FFV1_0( w_sv[78], w_sv[57], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[22] -= amp_sv[0];

      // *** DIAGRAM 193 OF 1240 ***

      // Wavefunction(s) for diagram number 193
      // (none)

      // Amplitude(s) for diagram number 193
      FFV1_0( w_sv[7], w_sv[57], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[19] -= amp_sv[0];

      // *** DIAGRAM 194 OF 1240 ***

      // Wavefunction(s) for diagram number 194
      // (none)

      // Amplitude(s) for diagram number 194
      FFV1_0( w_sv[46], w_sv[77], w_sv[29], COUPs[1], &amp_sv[0] );
      jamp_sv[3] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[5] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 195 OF 1240 ***

      // Wavefunction(s) for diagram number 195
      // (none)

      // Amplitude(s) for diagram number 195
      VVV1_0( w_sv[1], w_sv[29], w_sv[73], COUPs[0], &amp_sv[0] );
      jamp_sv[3] += +amp_sv[0];
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[22] += +amp_sv[0];

      // *** DIAGRAM 196 OF 1240 ***

      // Wavefunction(s) for diagram number 196
      // (none)

      // Amplitude(s) for diagram number 196
      FFV1_0( w_sv[46], w_sv[58], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[16] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[22] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 197 OF 1240 ***

      // Wavefunction(s) for diagram number 197
      // (none)

      // Amplitude(s) for diagram number 197
      FFV1_0( w_sv[25], w_sv[77], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[4] -= amp_sv[0];

      // *** DIAGRAM 198 OF 1240 ***

      // Wavefunction(s) for diagram number 198
      // (none)

      // Amplitude(s) for diagram number 198
      FFV1_0( w_sv[48], w_sv[77], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[1] -= amp_sv[0];

      // *** DIAGRAM 199 OF 1240 ***

      // Wavefunction(s) for diagram number 199
      FFV1_2( w_sv[38], w_sv[1], COUPs[1], cIPD[0], cIPD[1], w_sv[58] );

      // Amplitude(s) for diagram number 199
      FFV1_0( w_sv[58], w_sv[9], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[10] -= amp_sv[0];

      // *** DIAGRAM 200 OF 1240 ***

      // Wavefunction(s) for diagram number 200
      // (none)

      // Amplitude(s) for diagram number 200
      FFV1_0( w_sv[48], w_sv[9], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[7] -= amp_sv[0];

      // *** DIAGRAM 201 OF 1240 ***

      // Wavefunction(s) for diagram number 201
      // (none)

      // Amplitude(s) for diagram number 201
      FFV1_0( w_sv[58], w_sv[57], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[20] -= amp_sv[0];

      // *** DIAGRAM 202 OF 1240 ***

      // Wavefunction(s) for diagram number 202
      // (none)

      // Amplitude(s) for diagram number 202
      FFV1_0( w_sv[25], w_sv[57], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[18] -= amp_sv[0];

      // *** DIAGRAM 203 OF 1240 ***

      // Wavefunction(s) for diagram number 203
      // (none)

      // Amplitude(s) for diagram number 203
      FFV1_0( w_sv[38], w_sv[77], w_sv[27], COUPs[1], &amp_sv[0] );
      jamp_sv[1] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[4] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 204 OF 1240 ***

      // Wavefunction(s) for diagram number 204
      // (none)

      // Amplitude(s) for diagram number 204
      VVV1_0( w_sv[1], w_sv[27], w_sv[67], COUPs[0], &amp_sv[0] );
      jamp_sv[1] += +amp_sv[0];
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[20] += +amp_sv[0];

      // *** DIAGRAM 205 OF 1240 ***

      // Wavefunction(s) for diagram number 205
      // (none)

      // Amplitude(s) for diagram number 205
      FFV1_0( w_sv[38], w_sv[60], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[10] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[20] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 206 OF 1240 ***

      // Wavefunction(s) for diagram number 206
      // (none)

      // Amplitude(s) for diagram number 206
      FFV1_0( w_sv[28], w_sv[77], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[2] -= amp_sv[0];

      // *** DIAGRAM 207 OF 1240 ***

      // Wavefunction(s) for diagram number 207
      // (none)

      // Amplitude(s) for diagram number 207
      FFV1_0( w_sv[40], w_sv[77], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[0] -= amp_sv[0];

      // *** DIAGRAM 208 OF 1240 ***

      // Wavefunction(s) for diagram number 208
      FFV1_2( w_sv[41], w_sv[1], COUPs[1], cIPD[0], cIPD[1], w_sv[60] );

      // Amplitude(s) for diagram number 208
      FFV1_0( w_sv[60], w_sv[9], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[8] -= amp_sv[0];

      // *** DIAGRAM 209 OF 1240 ***

      // Wavefunction(s) for diagram number 209
      // (none)

      // Amplitude(s) for diagram number 209
      FFV1_0( w_sv[40], w_sv[9], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[6] -= amp_sv[0];

      // *** DIAGRAM 210 OF 1240 ***

      // Wavefunction(s) for diagram number 210
      // (none)

      // Amplitude(s) for diagram number 210
      FFV1_0( w_sv[60], w_sv[55], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[14] -= amp_sv[0];

      // *** DIAGRAM 211 OF 1240 ***

      // Wavefunction(s) for diagram number 211
      // (none)

      // Amplitude(s) for diagram number 211
      FFV1_0( w_sv[28], w_sv[55], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[12] -= amp_sv[0];

      // *** DIAGRAM 212 OF 1240 ***

      // Wavefunction(s) for diagram number 212
      // (none)

      // Amplitude(s) for diagram number 212
      FFV1_0( w_sv[41], w_sv[77], w_sv[24], COUPs[1], &amp_sv[0] );
      jamp_sv[0] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[2] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 213 OF 1240 ***

      // Wavefunction(s) for diagram number 213
      // (none)

      // Amplitude(s) for diagram number 213
      VVV1_0( w_sv[1], w_sv[24], w_sv[68], COUPs[0], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[14] += +amp_sv[0];

      // *** DIAGRAM 214 OF 1240 ***

      // Wavefunction(s) for diagram number 214
      // (none)

      // Amplitude(s) for diagram number 214
      FFV1_0( w_sv[41], w_sv[59], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[8] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[14] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 215 OF 1240 ***

      // Wavefunction(s) for diagram number 215
      // (none)

      // Amplitude(s) for diagram number 215
      FFV1_0( w_sv[26], w_sv[77], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[4] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[5] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 216 OF 1240 ***

      // Wavefunction(s) for diagram number 216
      // (none)

      // Amplitude(s) for diagram number 216
      FFV1_0( w_sv[3], w_sv[77], w_sv[42], COUPs[1], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[5] += +amp_sv[0];

      // *** DIAGRAM 217 OF 1240 ***

      // Wavefunction(s) for diagram number 217
      VVV1P0_1( w_sv[1], w_sv[24], COUPs[0], 0., 0., w_sv[59] );

      // Amplitude(s) for diagram number 217
      VVV1_0( w_sv[62], w_sv[59], w_sv[6], COUPs[0], &amp_sv[0] );
      jamp_sv[0] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[2] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[8] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[14] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[18] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[19] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[21] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[23] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 218 OF 1240 ***

      // Wavefunction(s) for diagram number 218
      // (none)

      // Amplitude(s) for diagram number 218
      VVV1_0( w_sv[62], w_sv[1], w_sv[42], COUPs[0], &amp_sv[0] );
      jamp_sv[0] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[2] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[4] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[5] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[9] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[15] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[21] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[23] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 219 OF 1240 ***

      // Wavefunction(s) for diagram number 219
      // (none)

      // Amplitude(s) for diagram number 219
      VVVV1_0( w_sv[1], w_sv[24], w_sv[6], w_sv[62], COUPs[2], &amp_sv[0] );
      jamp_sv[0] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[2] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[8] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[14] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[18] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[19] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[21] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[23] += +cxtype(0,1)*amp_sv[0];
      VVVV3_0( w_sv[1], w_sv[24], w_sv[6], w_sv[62], COUPs[2], &amp_sv[0] );
      jamp_sv[4] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[5] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[8] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[9] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[14] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[15] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[18] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[19] -= cxtype(0,1)*amp_sv[0];
      VVVV4_0( w_sv[1], w_sv[24], w_sv[6], w_sv[62], COUPs[2], &amp_sv[0] );
      jamp_sv[0] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[2] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[4] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[5] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[9] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[15] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[21] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[23] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 220 OF 1240 ***

      // Wavefunction(s) for diagram number 220
      // (none)

      // Amplitude(s) for diagram number 220
      FFV1_0( w_sv[3], w_sv[57], w_sv[59], COUPs[1], &amp_sv[0] );
      jamp_sv[18] += +amp_sv[0];
      jamp_sv[19] -= amp_sv[0];
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[23] += +amp_sv[0];

      // *** DIAGRAM 221 OF 1240 ***

      // Wavefunction(s) for diagram number 221
      // (none)

      // Amplitude(s) for diagram number 221
      FFV1_0( w_sv[26], w_sv[57], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[18] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[19] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 222 OF 1240 ***

      // Wavefunction(s) for diagram number 222
      // (none)

      // Amplitude(s) for diagram number 222
      FFV1_0( w_sv[14], w_sv[77], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[2] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[3] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 223 OF 1240 ***

      // Wavefunction(s) for diagram number 223
      // (none)

      // Amplitude(s) for diagram number 223
      FFV1_0( w_sv[3], w_sv[77], w_sv[16], COUPs[1], &amp_sv[0] );
      jamp_sv[1] += +amp_sv[0];
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[3] += +amp_sv[0];
      jamp_sv[4] -= amp_sv[0];

      // *** DIAGRAM 224 OF 1240 ***

      // Wavefunction(s) for diagram number 224
      VVV1P0_1( w_sv[1], w_sv[27], COUPs[0], 0., 0., w_sv[68] );

      // Amplitude(s) for diagram number 224
      VVV1_0( w_sv[62], w_sv[68], w_sv[5], COUPs[0], &amp_sv[0] );
      jamp_sv[1] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[4] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[10] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[12] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[13] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[15] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[17] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[20] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 225 OF 1240 ***

      // Wavefunction(s) for diagram number 225
      // (none)

      // Amplitude(s) for diagram number 225
      VVV1_0( w_sv[62], w_sv[1], w_sv[16], COUPs[0], &amp_sv[0] );
      jamp_sv[1] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[2] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[3] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[4] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[11] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[15] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[17] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[21] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 226 OF 1240 ***

      // Wavefunction(s) for diagram number 226
      // (none)

      // Amplitude(s) for diagram number 226
      VVVV1_0( w_sv[1], w_sv[27], w_sv[5], w_sv[62], COUPs[2], &amp_sv[0] );
      jamp_sv[1] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[4] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[10] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[12] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[13] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[15] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[17] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[20] -= cxtype(0,1)*amp_sv[0];
      VVVV3_0( w_sv[1], w_sv[27], w_sv[5], w_sv[62], COUPs[2], &amp_sv[0] );
      jamp_sv[2] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[3] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[10] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[11] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[12] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[13] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[20] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[21] += +cxtype(0,1)*amp_sv[0];
      VVVV4_0( w_sv[1], w_sv[27], w_sv[5], w_sv[62], COUPs[2], &amp_sv[0] );
      jamp_sv[1] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[2] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[3] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[4] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[11] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[15] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[17] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[21] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 227 OF 1240 ***

      // Wavefunction(s) for diagram number 227
      // (none)

      // Amplitude(s) for diagram number 227
      FFV1_0( w_sv[3], w_sv[55], w_sv[68], COUPs[1], &amp_sv[0] );
      jamp_sv[12] += +amp_sv[0];
      jamp_sv[13] -= amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[17] += +amp_sv[0];

      // *** DIAGRAM 228 OF 1240 ***

      // Wavefunction(s) for diagram number 228
      // (none)

      // Amplitude(s) for diagram number 228
      FFV1_0( w_sv[14], w_sv[55], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[12] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[13] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 229 OF 1240 ***

      // Wavefunction(s) for diagram number 229
      // (none)

      // Amplitude(s) for diagram number 229
      FFV1_0( w_sv[12], w_sv[77], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[0] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[1] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 230 OF 1240 ***

      // Wavefunction(s) for diagram number 230
      // (none)

      // Amplitude(s) for diagram number 230
      FFV1_0( w_sv[3], w_sv[77], w_sv[19], COUPs[1], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[5] += +amp_sv[0];

      // *** DIAGRAM 231 OF 1240 ***

      // Wavefunction(s) for diagram number 231
      VVV1P0_1( w_sv[1], w_sv[29], COUPs[0], 0., 0., w_sv[67] );

      // Amplitude(s) for diagram number 231
      VVV1_0( w_sv[62], w_sv[67], w_sv[4], COUPs[0], &amp_sv[0] );
      jamp_sv[3] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[5] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[6] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[7] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[9] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[11] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[16] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[22] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 232 OF 1240 ***

      // Wavefunction(s) for diagram number 232
      // (none)

      // Amplitude(s) for diagram number 232
      VVV1_0( w_sv[62], w_sv[1], w_sv[19], COUPs[0], &amp_sv[0] );
      jamp_sv[0] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[1] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[3] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[5] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[9] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[11] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[17] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[23] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 233 OF 1240 ***

      // Wavefunction(s) for diagram number 233
      // (none)

      // Amplitude(s) for diagram number 233
      VVVV1_0( w_sv[1], w_sv[4], w_sv[29], w_sv[62], COUPs[2], &amp_sv[0] );
      jamp_sv[0] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[1] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[6] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[7] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[16] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[17] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[22] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[23] += +cxtype(0,1)*amp_sv[0];
      VVVV3_0( w_sv[1], w_sv[4], w_sv[29], w_sv[62], COUPs[2], &amp_sv[0] );
      jamp_sv[3] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[5] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[6] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[7] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[9] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[11] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[16] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[22] -= cxtype(0,1)*amp_sv[0];
      VVVV4_0( w_sv[1], w_sv[4], w_sv[29], w_sv[62], COUPs[2], &amp_sv[0] );
      jamp_sv[0] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[1] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[3] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[5] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[9] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[11] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[17] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[23] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 234 OF 1240 ***

      // Wavefunction(s) for diagram number 234
      // (none)

      // Amplitude(s) for diagram number 234
      FFV1_0( w_sv[3], w_sv[9], w_sv[67], COUPs[1], &amp_sv[0] );
      jamp_sv[6] += +amp_sv[0];
      jamp_sv[7] -= amp_sv[0];
      jamp_sv[9] -= amp_sv[0];
      jamp_sv[11] += +amp_sv[0];

      // *** DIAGRAM 235 OF 1240 ***

      // Wavefunction(s) for diagram number 235
      // (none)

      // Amplitude(s) for diagram number 235
      FFV1_0( w_sv[12], w_sv[9], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[6] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[7] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 236 OF 1240 ***

      // Wavefunction(s) for diagram number 236
      VVVV1P0_1( w_sv[1], w_sv[4], w_sv[5], COUPs[2], 0., 0., w_sv[73] );
      VVVV3P0_1( w_sv[1], w_sv[4], w_sv[5], COUPs[2], 0., 0., w_sv[79] );
      VVVV4P0_1( w_sv[1], w_sv[4], w_sv[5], COUPs[2], 0., 0., w_sv[80] );

      // Amplitude(s) for diagram number 236
      VVV1_0( w_sv[73], w_sv[6], w_sv[62], COUPs[0], &amp_sv[0] );
      jamp_sv[0] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[2] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[8] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[14] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[18] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[19] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[21] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[23] += +cxtype(0,1)*amp_sv[0];
      VVV1_0( w_sv[79], w_sv[6], w_sv[62], COUPs[0], &amp_sv[0] );
      jamp_sv[2] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[6] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[8] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[12] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[19] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[20] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[21] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[22] += +cxtype(0,1)*amp_sv[0];
      VVV1_0( w_sv[80], w_sv[6], w_sv[62], COUPs[0], &amp_sv[0] );
      jamp_sv[0] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[6] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[12] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[14] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[18] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[20] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[22] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[23] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 237 OF 1240 ***

      // Wavefunction(s) for diagram number 237
      // (none)

      // Amplitude(s) for diagram number 237
      FFV1_0( w_sv[3], w_sv[57], w_sv[73], COUPs[1], &amp_sv[0] );
      jamp_sv[18] += +amp_sv[0];
      jamp_sv[19] -= amp_sv[0];
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[23] += +amp_sv[0];
      FFV1_0( w_sv[3], w_sv[57], w_sv[79], COUPs[1], &amp_sv[0] );
      jamp_sv[19] -= amp_sv[0];
      jamp_sv[20] += +amp_sv[0];
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[22] += +amp_sv[0];
      FFV1_0( w_sv[3], w_sv[57], w_sv[80], COUPs[1], &amp_sv[0] );
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[20] += +amp_sv[0];
      jamp_sv[22] += +amp_sv[0];
      jamp_sv[23] -= amp_sv[0];

      // *** DIAGRAM 238 OF 1240 ***

      // Wavefunction(s) for diagram number 238
      // (none)

      // Amplitude(s) for diagram number 238
      FFV1_0( w_sv[41], w_sv[34], w_sv[73], COUPs[1], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[14] += +amp_sv[0];
      FFV1_0( w_sv[41], w_sv[34], w_sv[79], COUPs[1], &amp_sv[0] );
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[6] += +amp_sv[0];
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[12] += +amp_sv[0];
      FFV1_0( w_sv[41], w_sv[34], w_sv[80], COUPs[1], &amp_sv[0] );
      jamp_sv[0] -= amp_sv[0];
      jamp_sv[6] += +amp_sv[0];
      jamp_sv[12] += +amp_sv[0];
      jamp_sv[14] -= amp_sv[0];

      // *** DIAGRAM 239 OF 1240 ***

      // Wavefunction(s) for diagram number 239
      VVVV1P0_1( w_sv[1], w_sv[4], w_sv[6], COUPs[2], 0., 0., w_sv[57] );
      VVVV3P0_1( w_sv[1], w_sv[4], w_sv[6], COUPs[2], 0., 0., w_sv[81] );
      VVVV4P0_1( w_sv[1], w_sv[4], w_sv[6], COUPs[2], 0., 0., w_sv[82] );

      // Amplitude(s) for diagram number 239
      VVV1_0( w_sv[57], w_sv[5], w_sv[62], COUPs[0], &amp_sv[0] );
      jamp_sv[1] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[4] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[10] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[12] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[13] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[15] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[17] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[20] -= cxtype(0,1)*amp_sv[0];
      VVV1_0( w_sv[81], w_sv[5], w_sv[62], COUPs[0], &amp_sv[0] );
      jamp_sv[4] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[7] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[10] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[13] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[14] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[15] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[16] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[18] -= cxtype(0,1)*amp_sv[0];
      VVV1_0( w_sv[82], w_sv[5], w_sv[62], COUPs[0], &amp_sv[0] );
      jamp_sv[1] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[7] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[12] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[14] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[16] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[17] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[18] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[20] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 240 OF 1240 ***

      // Wavefunction(s) for diagram number 240
      // (none)

      // Amplitude(s) for diagram number 240
      FFV1_0( w_sv[3], w_sv[55], w_sv[57], COUPs[1], &amp_sv[0] );
      jamp_sv[12] += +amp_sv[0];
      jamp_sv[13] -= amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[17] += +amp_sv[0];
      FFV1_0( w_sv[3], w_sv[55], w_sv[81], COUPs[1], &amp_sv[0] );
      jamp_sv[13] -= amp_sv[0];
      jamp_sv[14] += +amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[16] += +amp_sv[0];
      FFV1_0( w_sv[3], w_sv[55], w_sv[82], COUPs[1], &amp_sv[0] );
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[14] += +amp_sv[0];
      jamp_sv[16] += +amp_sv[0];
      jamp_sv[17] -= amp_sv[0];

      // *** DIAGRAM 241 OF 1240 ***

      // Wavefunction(s) for diagram number 241
      // (none)

      // Amplitude(s) for diagram number 241
      FFV1_0( w_sv[38], w_sv[34], w_sv[57], COUPs[1], &amp_sv[0] );
      jamp_sv[1] += +amp_sv[0];
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[20] += +amp_sv[0];
      FFV1_0( w_sv[38], w_sv[34], w_sv[81], COUPs[1], &amp_sv[0] );
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[18] += +amp_sv[0];
      FFV1_0( w_sv[38], w_sv[34], w_sv[82], COUPs[1], &amp_sv[0] );
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[18] += +amp_sv[0];
      jamp_sv[20] -= amp_sv[0];

      // *** DIAGRAM 242 OF 1240 ***

      // Wavefunction(s) for diagram number 242
      VVVV1P0_1( w_sv[1], w_sv[5], w_sv[6], COUPs[2], 0., 0., w_sv[55] );
      VVVV3P0_1( w_sv[1], w_sv[5], w_sv[6], COUPs[2], 0., 0., w_sv[83] );
      VVVV4P0_1( w_sv[1], w_sv[5], w_sv[6], COUPs[2], 0., 0., w_sv[84] );

      // Amplitude(s) for diagram number 242
      VVV1_0( w_sv[55], w_sv[4], w_sv[62], COUPs[0], &amp_sv[0] );
      jamp_sv[3] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[5] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[6] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[7] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[9] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[11] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[16] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[22] -= cxtype(0,1)*amp_sv[0];
      VVV1_0( w_sv[83], w_sv[4], w_sv[62], COUPs[0], &amp_sv[0] );
      jamp_sv[5] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[7] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[8] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[9] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[10] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[13] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[16] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[19] -= cxtype(0,1)*amp_sv[0];
      VVV1_0( w_sv[84], w_sv[4], w_sv[62], COUPs[0], &amp_sv[0] );
      jamp_sv[3] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[6] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[8] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[10] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[11] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[13] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[19] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[22] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 243 OF 1240 ***

      // Wavefunction(s) for diagram number 243
      // (none)

      // Amplitude(s) for diagram number 243
      FFV1_0( w_sv[3], w_sv[9], w_sv[55], COUPs[1], &amp_sv[0] );
      jamp_sv[6] += +amp_sv[0];
      jamp_sv[7] -= amp_sv[0];
      jamp_sv[9] -= amp_sv[0];
      jamp_sv[11] += +amp_sv[0];
      FFV1_0( w_sv[3], w_sv[9], w_sv[83], COUPs[1], &amp_sv[0] );
      jamp_sv[7] -= amp_sv[0];
      jamp_sv[8] += +amp_sv[0];
      jamp_sv[9] -= amp_sv[0];
      jamp_sv[10] += +amp_sv[0];
      FFV1_0( w_sv[3], w_sv[9], w_sv[84], COUPs[1], &amp_sv[0] );
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[8] += +amp_sv[0];
      jamp_sv[10] += +amp_sv[0];
      jamp_sv[11] -= amp_sv[0];

      // *** DIAGRAM 244 OF 1240 ***

      // Wavefunction(s) for diagram number 244
      // (none)

      // Amplitude(s) for diagram number 244
      FFV1_0( w_sv[46], w_sv[34], w_sv[55], COUPs[1], &amp_sv[0] );
      jamp_sv[3] += +amp_sv[0];
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[22] += +amp_sv[0];
      FFV1_0( w_sv[46], w_sv[34], w_sv[83], COUPs[1], &amp_sv[0] );
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[19] += +amp_sv[0];
      FFV1_0( w_sv[46], w_sv[34], w_sv[84], COUPs[1], &amp_sv[0] );
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[19] += +amp_sv[0];
      jamp_sv[22] -= amp_sv[0];

      // *** DIAGRAM 245 OF 1240 ***

      // Wavefunction(s) for diagram number 245
      // (none)

      // Amplitude(s) for diagram number 245
      FFV1_0( w_sv[3], w_sv[77], w_sv[30], COUPs[1], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[5] += +amp_sv[0];
      FFV1_0( w_sv[3], w_sv[77], w_sv[31], COUPs[1], &amp_sv[0] );
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[2] += +amp_sv[0];
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[4] += +amp_sv[0];
      FFV1_0( w_sv[3], w_sv[77], w_sv[32], COUPs[1], &amp_sv[0] );
      jamp_sv[0] -= amp_sv[0];
      jamp_sv[2] += +amp_sv[0];
      jamp_sv[4] += +amp_sv[0];
      jamp_sv[5] -= amp_sv[0];

      // *** DIAGRAM 246 OF 1240 ***

      // Wavefunction(s) for diagram number 246
      // (none)

      // Amplitude(s) for diagram number 246
      VVV1_0( w_sv[1], w_sv[30], w_sv[62], COUPs[0], &amp_sv[0] );
      jamp_sv[0] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[1] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[3] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[5] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[9] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[11] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[17] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[23] += +cxtype(0,1)*amp_sv[0];
      VVV1_0( w_sv[1], w_sv[31], w_sv[62], COUPs[0], &amp_sv[0] );
      jamp_sv[1] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[2] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[3] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[4] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[11] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[15] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[17] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[21] += +cxtype(0,1)*amp_sv[0];
      VVV1_0( w_sv[1], w_sv[32], w_sv[62], COUPs[0], &amp_sv[0] );
      jamp_sv[0] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[2] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[4] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[5] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[9] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[15] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[21] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[23] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 247 OF 1240 ***

      // Wavefunction(s) for diagram number 247
      FFV1_2( w_sv[3], w_sv[0], COUPs[1], cIPD[0], cIPD[1], w_sv[62] );
      FFV1_1( w_sv[2], w_sv[1], COUPs[1], cIPD[0], cIPD[1], w_sv[77] );
      FFV1_2( w_sv[62], w_sv[4], COUPs[1], cIPD[0], cIPD[1], w_sv[34] );
      FFV1_1( w_sv[77], w_sv[5], COUPs[1], cIPD[0], cIPD[1], w_sv[9] );

      // Amplitude(s) for diagram number 247
      FFV1_0( w_sv[34], w_sv[9], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[41] -= amp_sv[0];

      // *** DIAGRAM 248 OF 1240 ***

      // Wavefunction(s) for diagram number 248
      FFV1_1( w_sv[77], w_sv[6], COUPs[1], cIPD[0], cIPD[1], w_sv[85] );

      // Amplitude(s) for diagram number 248
      FFV1_0( w_sv[34], w_sv[85], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[47] -= amp_sv[0];

      // *** DIAGRAM 249 OF 1240 ***

      // Wavefunction(s) for diagram number 249
      FFV1_2( w_sv[62], w_sv[5], COUPs[1], cIPD[0], cIPD[1], w_sv[86] );
      FFV1_1( w_sv[77], w_sv[4], COUPs[1], cIPD[0], cIPD[1], w_sv[87] );

      // Amplitude(s) for diagram number 249
      FFV1_0( w_sv[86], w_sv[87], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[35] -= amp_sv[0];

      // *** DIAGRAM 250 OF 1240 ***

      // Wavefunction(s) for diagram number 250
      // (none)

      // Amplitude(s) for diagram number 250
      FFV1_0( w_sv[86], w_sv[85], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[45] -= amp_sv[0];

      // *** DIAGRAM 251 OF 1240 ***

      // Wavefunction(s) for diagram number 251
      FFV1_2( w_sv[62], w_sv[6], COUPs[1], cIPD[0], cIPD[1], w_sv[88] );

      // Amplitude(s) for diagram number 251
      FFV1_0( w_sv[88], w_sv[87], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[33] -= amp_sv[0];

      // *** DIAGRAM 252 OF 1240 ***

      // Wavefunction(s) for diagram number 252
      // (none)

      // Amplitude(s) for diagram number 252
      FFV1_0( w_sv[88], w_sv[9], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[39] -= amp_sv[0];

      // *** DIAGRAM 253 OF 1240 ***

      // Wavefunction(s) for diagram number 253
      FFV1P0_3( w_sv[62], w_sv[77], COUPs[1], 0., 0., w_sv[89] );

      // Amplitude(s) for diagram number 253
      VVV1_0( w_sv[24], w_sv[6], w_sv[89], COUPs[0], &amp_sv[0] );
      jamp_sv[33] += +amp_sv[0];
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[45] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];

      // *** DIAGRAM 254 OF 1240 ***

      // Wavefunction(s) for diagram number 254
      FFV1_2( w_sv[62], w_sv[24], COUPs[1], cIPD[0], cIPD[1], w_sv[90] );

      // Amplitude(s) for diagram number 254
      FFV1_0( w_sv[90], w_sv[77], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[45] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[47] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 255 OF 1240 ***

      // Wavefunction(s) for diagram number 255
      // (none)

      // Amplitude(s) for diagram number 255
      FFV1_0( w_sv[88], w_sv[77], w_sv[24], COUPs[1], &amp_sv[0] );
      jamp_sv[33] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[39] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 256 OF 1240 ***

      // Wavefunction(s) for diagram number 256
      // (none)

      // Amplitude(s) for diagram number 256
      VVV1_0( w_sv[27], w_sv[5], w_sv[89], COUPs[0], &amp_sv[0] );
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[45] -= amp_sv[0];

      // *** DIAGRAM 257 OF 1240 ***

      // Wavefunction(s) for diagram number 257
      FFV1_2( w_sv[62], w_sv[27], COUPs[1], cIPD[0], cIPD[1], w_sv[91] );

      // Amplitude(s) for diagram number 257
      FFV1_0( w_sv[91], w_sv[77], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[39] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[41] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 258 OF 1240 ***

      // Wavefunction(s) for diagram number 258
      // (none)

      // Amplitude(s) for diagram number 258
      FFV1_0( w_sv[86], w_sv[77], w_sv[27], COUPs[1], &amp_sv[0] );
      jamp_sv[35] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[45] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 259 OF 1240 ***

      // Wavefunction(s) for diagram number 259
      // (none)

      // Amplitude(s) for diagram number 259
      VVV1_0( w_sv[4], w_sv[29], w_sv[89], COUPs[0], &amp_sv[0] );
      jamp_sv[33] += +amp_sv[0];
      jamp_sv[35] -= amp_sv[0];
      jamp_sv[41] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];

      // *** DIAGRAM 260 OF 1240 ***

      // Wavefunction(s) for diagram number 260
      // (none)

      // Amplitude(s) for diagram number 260
      FFV1_0( w_sv[34], w_sv[77], w_sv[29], COUPs[1], &amp_sv[0] );
      jamp_sv[41] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[47] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 261 OF 1240 ***

      // Wavefunction(s) for diagram number 261
      FFV1_2( w_sv[62], w_sv[29], COUPs[1], cIPD[0], cIPD[1], w_sv[89] );

      // Amplitude(s) for diagram number 261
      FFV1_0( w_sv[89], w_sv[77], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[33] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[35] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 262 OF 1240 ***

      // Wavefunction(s) for diagram number 262
      // (none)

      // Amplitude(s) for diagram number 262
      FFV1_0( w_sv[62], w_sv[77], w_sv[30], COUPs[1], &amp_sv[0] );
      jamp_sv[33] += +amp_sv[0];
      jamp_sv[35] -= amp_sv[0];
      jamp_sv[41] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      FFV1_0( w_sv[62], w_sv[77], w_sv[31], COUPs[1], &amp_sv[0] );
      jamp_sv[35] -= amp_sv[0];
      jamp_sv[39] += +amp_sv[0];
      jamp_sv[41] -= amp_sv[0];
      jamp_sv[45] += +amp_sv[0];
      FFV1_0( w_sv[62], w_sv[77], w_sv[32], COUPs[1], &amp_sv[0] );
      jamp_sv[33] -= amp_sv[0];
      jamp_sv[39] += +amp_sv[0];
      jamp_sv[45] += +amp_sv[0];
      jamp_sv[47] -= amp_sv[0];

      // *** DIAGRAM 263 OF 1240 ***

      // Wavefunction(s) for diagram number 263
      FFV1P0_3( w_sv[62], w_sv[2], COUPs[1], 0., 0., w_sv[92] );

      // Amplitude(s) for diagram number 263
      VVV1_0( w_sv[92], w_sv[63], w_sv[6], COUPs[0], &amp_sv[0] );
      jamp_sv[33] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[57] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[81] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[87] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[105] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[111] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[117] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[119] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 264 OF 1240 ***

      // Wavefunction(s) for diagram number 264
      // (none)

      // Amplitude(s) for diagram number 264
      VVV1_0( w_sv[92], w_sv[64], w_sv[5], COUPs[0], &amp_sv[0] );
      jamp_sv[35] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[59] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[81] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[87] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[93] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[95] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[105] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[111] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 265 OF 1240 ***

      // Wavefunction(s) for diagram number 265
      // (none)

      // Amplitude(s) for diagram number 265
      VVVV1_0( w_sv[61], w_sv[5], w_sv[6], w_sv[92], COUPs[2], &amp_sv[0] );
      jamp_sv[33] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[57] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[81] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[87] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[105] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[111] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[117] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[119] += +cxtype(0,1)*amp_sv[0];
      VVVV3_0( w_sv[61], w_sv[5], w_sv[6], w_sv[92], COUPs[2], &amp_sv[0] );
      jamp_sv[35] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[59] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[81] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[87] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[93] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[95] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[105] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[111] -= cxtype(0,1)*amp_sv[0];
      VVVV4_0( w_sv[61], w_sv[5], w_sv[6], w_sv[92], COUPs[2], &amp_sv[0] );
      jamp_sv[33] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[35] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[57] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[59] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[93] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[95] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[117] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[119] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 266 OF 1240 ***

      // Wavefunction(s) for diagram number 266
      FFV1_1( w_sv[2], w_sv[61], COUPs[1], cIPD[0], cIPD[1], w_sv[93] );

      // Amplitude(s) for diagram number 266
      FFV1_0( w_sv[86], w_sv[93], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[35] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[59] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 267 OF 1240 ***

      // Wavefunction(s) for diagram number 267
      // (none)

      // Amplitude(s) for diagram number 267
      FFV1_0( w_sv[86], w_sv[2], w_sv[64], COUPs[1], &amp_sv[0] );
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[105] -= amp_sv[0];
      jamp_sv[111] += +amp_sv[0];

      // *** DIAGRAM 268 OF 1240 ***

      // Wavefunction(s) for diagram number 268
      // (none)

      // Amplitude(s) for diagram number 268
      FFV1_0( w_sv[88], w_sv[93], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[33] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[57] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 269 OF 1240 ***

      // Wavefunction(s) for diagram number 269
      // (none)

      // Amplitude(s) for diagram number 269
      FFV1_0( w_sv[88], w_sv[2], w_sv[63], COUPs[1], &amp_sv[0] );
      jamp_sv[33] += +amp_sv[0];
      jamp_sv[57] -= amp_sv[0];
      jamp_sv[81] -= amp_sv[0];
      jamp_sv[87] += +amp_sv[0];

      // *** DIAGRAM 270 OF 1240 ***

      // Wavefunction(s) for diagram number 270
      FFV1_2( w_sv[62], w_sv[61], COUPs[1], cIPD[0], cIPD[1], w_sv[94] );

      // Amplitude(s) for diagram number 270
      FFV1_0( w_sv[94], w_sv[39], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[93] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[95] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 271 OF 1240 ***

      // Wavefunction(s) for diagram number 271
      FFV1P0_3( w_sv[62], w_sv[39], COUPs[1], 0., 0., w_sv[95] );

      // Amplitude(s) for diagram number 271
      VVV1_0( w_sv[61], w_sv[6], w_sv[95], COUPs[0], &amp_sv[0] );
      jamp_sv[81] += +amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[93] -= amp_sv[0];
      jamp_sv[95] += +amp_sv[0];

      // *** DIAGRAM 272 OF 1240 ***

      // Wavefunction(s) for diagram number 272
      // (none)

      // Amplitude(s) for diagram number 272
      FFV1_0( w_sv[88], w_sv[39], w_sv[61], COUPs[1], &amp_sv[0] );
      jamp_sv[81] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[87] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 273 OF 1240 ***

      // Wavefunction(s) for diagram number 273
      // (none)

      // Amplitude(s) for diagram number 273
      FFV1_0( w_sv[94], w_sv[47], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[117] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[119] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 274 OF 1240 ***

      // Wavefunction(s) for diagram number 274
      FFV1P0_3( w_sv[62], w_sv[47], COUPs[1], 0., 0., w_sv[96] );

      // Amplitude(s) for diagram number 274
      VVV1_0( w_sv[61], w_sv[5], w_sv[96], COUPs[0], &amp_sv[0] );
      jamp_sv[105] += +amp_sv[0];
      jamp_sv[111] -= amp_sv[0];
      jamp_sv[117] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];

      // *** DIAGRAM 275 OF 1240 ***

      // Wavefunction(s) for diagram number 275
      // (none)

      // Amplitude(s) for diagram number 275
      FFV1_0( w_sv[86], w_sv[47], w_sv[61], COUPs[1], &amp_sv[0] );
      jamp_sv[105] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[111] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 276 OF 1240 ***

      // Wavefunction(s) for diagram number 276
      // (none)

      // Amplitude(s) for diagram number 276
      FFV1_0( w_sv[94], w_sv[2], w_sv[29], COUPs[1], &amp_sv[0] );
      jamp_sv[93] += +amp_sv[0];
      jamp_sv[95] -= amp_sv[0];
      jamp_sv[117] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];

      // *** DIAGRAM 277 OF 1240 ***

      // Wavefunction(s) for diagram number 277
      // (none)

      // Amplitude(s) for diagram number 277
      VVV1_0( w_sv[61], w_sv[29], w_sv[92], COUPs[0], &amp_sv[0] );
      jamp_sv[33] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[35] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[57] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[59] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[93] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[95] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[117] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[119] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 278 OF 1240 ***

      // Wavefunction(s) for diagram number 278
      // (none)

      // Amplitude(s) for diagram number 278
      FFV1_0( w_sv[89], w_sv[2], w_sv[61], COUPs[1], &amp_sv[0] );
      jamp_sv[33] += +amp_sv[0];
      jamp_sv[35] -= amp_sv[0];
      jamp_sv[57] -= amp_sv[0];
      jamp_sv[59] += +amp_sv[0];

      // *** DIAGRAM 279 OF 1240 ***

      // Wavefunction(s) for diagram number 279
      // (none)

      // Amplitude(s) for diagram number 279
      VVV1_0( w_sv[92], w_sv[69], w_sv[6], COUPs[0], &amp_sv[0] );
      jamp_sv[39] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[57] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[63] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[81] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[107] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[111] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[113] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[117] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 280 OF 1240 ***

      // Wavefunction(s) for diagram number 280
      // (none)

      // Amplitude(s) for diagram number 280
      VVV1_0( w_sv[92], w_sv[70], w_sv[4], COUPs[0], &amp_sv[0] );
      jamp_sv[41] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[57] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[63] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[69] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[71] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[83] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[107] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[117] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 281 OF 1240 ***

      // Wavefunction(s) for diagram number 281
      // (none)

      // Amplitude(s) for diagram number 281
      VVVV1_0( w_sv[66], w_sv[4], w_sv[6], w_sv[92], COUPs[2], &amp_sv[0] );
      jamp_sv[39] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[57] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[63] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[81] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[107] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[111] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[113] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[117] -= cxtype(0,1)*amp_sv[0];
      VVVV3_0( w_sv[66], w_sv[4], w_sv[6], w_sv[92], COUPs[2], &amp_sv[0] );
      jamp_sv[41] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[57] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[63] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[69] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[71] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[83] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[107] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[117] -= cxtype(0,1)*amp_sv[0];
      VVVV4_0( w_sv[66], w_sv[4], w_sv[6], w_sv[92], COUPs[2], &amp_sv[0] );
      jamp_sv[39] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[41] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[69] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[71] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[81] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[83] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[111] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[113] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 282 OF 1240 ***

      // Wavefunction(s) for diagram number 282
      FFV1_1( w_sv[2], w_sv[66], COUPs[1], cIPD[0], cIPD[1], w_sv[94] );

      // Amplitude(s) for diagram number 282
      FFV1_0( w_sv[34], w_sv[94], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[41] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[83] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 283 OF 1240 ***

      // Wavefunction(s) for diagram number 283
      // (none)

      // Amplitude(s) for diagram number 283
      FFV1_0( w_sv[34], w_sv[2], w_sv[70], COUPs[1], &amp_sv[0] );
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[107] -= amp_sv[0];
      jamp_sv[117] += +amp_sv[0];

      // *** DIAGRAM 284 OF 1240 ***

      // Wavefunction(s) for diagram number 284
      // (none)

      // Amplitude(s) for diagram number 284
      FFV1_0( w_sv[88], w_sv[94], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[39] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[81] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 285 OF 1240 ***

      // Wavefunction(s) for diagram number 285
      // (none)

      // Amplitude(s) for diagram number 285
      FFV1_0( w_sv[88], w_sv[2], w_sv[69], COUPs[1], &amp_sv[0] );
      jamp_sv[39] += +amp_sv[0];
      jamp_sv[57] -= amp_sv[0];
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[81] -= amp_sv[0];

      // *** DIAGRAM 286 OF 1240 ***

      // Wavefunction(s) for diagram number 286
      FFV1_2( w_sv[62], w_sv[66], COUPs[1], cIPD[0], cIPD[1], w_sv[97] );

      // Amplitude(s) for diagram number 286
      FFV1_0( w_sv[97], w_sv[33], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[69] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[71] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 287 OF 1240 ***

      // Wavefunction(s) for diagram number 287
      FFV1P0_3( w_sv[62], w_sv[33], COUPs[1], 0., 0., w_sv[98] );

      // Amplitude(s) for diagram number 287
      VVV1_0( w_sv[66], w_sv[6], w_sv[98], COUPs[0], &amp_sv[0] );
      jamp_sv[57] += +amp_sv[0];
      jamp_sv[63] -= amp_sv[0];
      jamp_sv[69] -= amp_sv[0];
      jamp_sv[71] += +amp_sv[0];

      // *** DIAGRAM 288 OF 1240 ***

      // Wavefunction(s) for diagram number 288
      // (none)

      // Amplitude(s) for diagram number 288
      FFV1_0( w_sv[88], w_sv[33], w_sv[66], COUPs[1], &amp_sv[0] );
      jamp_sv[57] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[63] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 289 OF 1240 ***

      // Wavefunction(s) for diagram number 289
      // (none)

      // Amplitude(s) for diagram number 289
      FFV1_0( w_sv[97], w_sv[47], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[111] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[113] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 290 OF 1240 ***

      // Wavefunction(s) for diagram number 290
      // (none)

      // Amplitude(s) for diagram number 290
      VVV1_0( w_sv[66], w_sv[4], w_sv[96], COUPs[0], &amp_sv[0] );
      jamp_sv[107] += +amp_sv[0];
      jamp_sv[111] -= amp_sv[0];
      jamp_sv[113] += +amp_sv[0];
      jamp_sv[117] -= amp_sv[0];

      // *** DIAGRAM 291 OF 1240 ***

      // Wavefunction(s) for diagram number 291
      // (none)

      // Amplitude(s) for diagram number 291
      FFV1_0( w_sv[34], w_sv[47], w_sv[66], COUPs[1], &amp_sv[0] );
      jamp_sv[107] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[117] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 292 OF 1240 ***

      // Wavefunction(s) for diagram number 292
      // (none)

      // Amplitude(s) for diagram number 292
      FFV1_0( w_sv[97], w_sv[2], w_sv[27], COUPs[1], &amp_sv[0] );
      jamp_sv[69] += +amp_sv[0];
      jamp_sv[71] -= amp_sv[0];
      jamp_sv[111] -= amp_sv[0];
      jamp_sv[113] += +amp_sv[0];

      // *** DIAGRAM 293 OF 1240 ***

      // Wavefunction(s) for diagram number 293
      // (none)

      // Amplitude(s) for diagram number 293
      VVV1_0( w_sv[66], w_sv[27], w_sv[92], COUPs[0], &amp_sv[0] );
      jamp_sv[39] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[41] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[69] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[71] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[81] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[83] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[111] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[113] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 294 OF 1240 ***

      // Wavefunction(s) for diagram number 294
      // (none)

      // Amplitude(s) for diagram number 294
      FFV1_0( w_sv[91], w_sv[2], w_sv[66], COUPs[1], &amp_sv[0] );
      jamp_sv[39] += +amp_sv[0];
      jamp_sv[41] -= amp_sv[0];
      jamp_sv[81] -= amp_sv[0];
      jamp_sv[83] += +amp_sv[0];

      // *** DIAGRAM 295 OF 1240 ***

      // Wavefunction(s) for diagram number 295
      // (none)

      // Amplitude(s) for diagram number 295
      VVV1_0( w_sv[92], w_sv[74], w_sv[5], COUPs[0], &amp_sv[0] );
      jamp_sv[45] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[59] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[69] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[83] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[87] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[89] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[93] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[105] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 296 OF 1240 ***

      // Wavefunction(s) for diagram number 296
      // (none)

      // Amplitude(s) for diagram number 296
      VVV1_0( w_sv[92], w_sv[75], w_sv[4], COUPs[0], &amp_sv[0] );
      jamp_sv[47] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[59] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[63] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[65] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[69] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[83] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[93] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[107] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 297 OF 1240 ***

      // Wavefunction(s) for diagram number 297
      // (none)

      // Amplitude(s) for diagram number 297
      VVVV1_0( w_sv[72], w_sv[4], w_sv[5], w_sv[92], COUPs[2], &amp_sv[0] );
      jamp_sv[45] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[59] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[69] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[83] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[87] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[89] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[93] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[105] += +cxtype(0,1)*amp_sv[0];
      VVVV3_0( w_sv[72], w_sv[4], w_sv[5], w_sv[92], COUPs[2], &amp_sv[0] );
      jamp_sv[47] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[59] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[63] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[65] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[69] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[83] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[93] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[107] += +cxtype(0,1)*amp_sv[0];
      VVVV4_0( w_sv[72], w_sv[4], w_sv[5], w_sv[92], COUPs[2], &amp_sv[0] );
      jamp_sv[45] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[47] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[63] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[65] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[87] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[89] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[105] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[107] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 298 OF 1240 ***

      // Wavefunction(s) for diagram number 298
      FFV1_1( w_sv[2], w_sv[72], COUPs[1], cIPD[0], cIPD[1], w_sv[97] );

      // Amplitude(s) for diagram number 298
      FFV1_0( w_sv[34], w_sv[97], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[47] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[107] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 299 OF 1240 ***

      // Wavefunction(s) for diagram number 299
      // (none)

      // Amplitude(s) for diagram number 299
      FFV1_0( w_sv[34], w_sv[2], w_sv[75], COUPs[1], &amp_sv[0] );
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[93] += +amp_sv[0];
      jamp_sv[107] -= amp_sv[0];

      // *** DIAGRAM 300 OF 1240 ***

      // Wavefunction(s) for diagram number 300
      // (none)

      // Amplitude(s) for diagram number 300
      FFV1_0( w_sv[86], w_sv[97], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[45] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[105] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 301 OF 1240 ***

      // Wavefunction(s) for diagram number 301
      // (none)

      // Amplitude(s) for diagram number 301
      FFV1_0( w_sv[86], w_sv[2], w_sv[74], COUPs[1], &amp_sv[0] );
      jamp_sv[45] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[69] += +amp_sv[0];
      jamp_sv[105] -= amp_sv[0];

      // *** DIAGRAM 302 OF 1240 ***

      // Wavefunction(s) for diagram number 302
      FFV1_2( w_sv[62], w_sv[72], COUPs[1], cIPD[0], cIPD[1], w_sv[99] );

      // Amplitude(s) for diagram number 302
      FFV1_0( w_sv[99], w_sv[33], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[63] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[65] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 303 OF 1240 ***

      // Wavefunction(s) for diagram number 303
      // (none)

      // Amplitude(s) for diagram number 303
      VVV1_0( w_sv[72], w_sv[5], w_sv[98], COUPs[0], &amp_sv[0] );
      jamp_sv[59] += +amp_sv[0];
      jamp_sv[63] -= amp_sv[0];
      jamp_sv[65] += +amp_sv[0];
      jamp_sv[69] -= amp_sv[0];

      // *** DIAGRAM 304 OF 1240 ***

      // Wavefunction(s) for diagram number 304
      // (none)

      // Amplitude(s) for diagram number 304
      FFV1_0( w_sv[86], w_sv[33], w_sv[72], COUPs[1], &amp_sv[0] );
      jamp_sv[59] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[69] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 305 OF 1240 ***

      // Wavefunction(s) for diagram number 305
      // (none)

      // Amplitude(s) for diagram number 305
      FFV1_0( w_sv[99], w_sv[39], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[87] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[89] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 306 OF 1240 ***

      // Wavefunction(s) for diagram number 306
      // (none)

      // Amplitude(s) for diagram number 306
      VVV1_0( w_sv[72], w_sv[4], w_sv[95], COUPs[0], &amp_sv[0] );
      jamp_sv[83] += +amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[89] += +amp_sv[0];
      jamp_sv[93] -= amp_sv[0];

      // *** DIAGRAM 307 OF 1240 ***

      // Wavefunction(s) for diagram number 307
      // (none)

      // Amplitude(s) for diagram number 307
      FFV1_0( w_sv[34], w_sv[39], w_sv[72], COUPs[1], &amp_sv[0] );
      jamp_sv[83] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[93] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 308 OF 1240 ***

      // Wavefunction(s) for diagram number 308
      // (none)

      // Amplitude(s) for diagram number 308
      FFV1_0( w_sv[99], w_sv[2], w_sv[24], COUPs[1], &amp_sv[0] );
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[89] += +amp_sv[0];

      // *** DIAGRAM 309 OF 1240 ***

      // Wavefunction(s) for diagram number 309
      // (none)

      // Amplitude(s) for diagram number 309
      VVV1_0( w_sv[72], w_sv[24], w_sv[92], COUPs[0], &amp_sv[0] );
      jamp_sv[45] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[47] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[63] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[65] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[87] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[89] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[105] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[107] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 310 OF 1240 ***

      // Wavefunction(s) for diagram number 310
      // (none)

      // Amplitude(s) for diagram number 310
      FFV1_0( w_sv[90], w_sv[2], w_sv[72], COUPs[1], &amp_sv[0] );
      jamp_sv[45] += +amp_sv[0];
      jamp_sv[47] -= amp_sv[0];
      jamp_sv[105] -= amp_sv[0];
      jamp_sv[107] += +amp_sv[0];

      // *** DIAGRAM 311 OF 1240 ***

      // Wavefunction(s) for diagram number 311
      FFV1_2( w_sv[62], w_sv[1], COUPs[1], cIPD[0], cIPD[1], w_sv[99] );

      // Amplitude(s) for diagram number 311
      FFV1_0( w_sv[99], w_sv[35], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[65] -= amp_sv[0];

      // *** DIAGRAM 312 OF 1240 ***

      // Wavefunction(s) for diagram number 312
      // (none)

      // Amplitude(s) for diagram number 312
      FFV1_0( w_sv[99], w_sv[36], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[71] -= amp_sv[0];

      // *** DIAGRAM 313 OF 1240 ***

      // Wavefunction(s) for diagram number 313
      FFV1_1( w_sv[33], w_sv[1], COUPs[1], cIPD[0], cIPD[1], w_sv[100] );

      // Amplitude(s) for diagram number 313
      FFV1_0( w_sv[86], w_sv[100], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[59] -= amp_sv[0];

      // *** DIAGRAM 314 OF 1240 ***

      // Wavefunction(s) for diagram number 314
      // (none)

      // Amplitude(s) for diagram number 314
      FFV1_0( w_sv[86], w_sv[36], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[69] -= amp_sv[0];

      // *** DIAGRAM 315 OF 1240 ***

      // Wavefunction(s) for diagram number 315
      // (none)

      // Amplitude(s) for diagram number 315
      FFV1_0( w_sv[88], w_sv[100], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[57] -= amp_sv[0];

      // *** DIAGRAM 316 OF 1240 ***

      // Wavefunction(s) for diagram number 316
      // (none)

      // Amplitude(s) for diagram number 316
      FFV1_0( w_sv[88], w_sv[35], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[63] -= amp_sv[0];

      // *** DIAGRAM 317 OF 1240 ***

      // Wavefunction(s) for diagram number 317
      // (none)

      // Amplitude(s) for diagram number 317
      FFV1_0( w_sv[99], w_sv[33], w_sv[29], COUPs[1], &amp_sv[0] );
      jamp_sv[65] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[71] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 318 OF 1240 ***

      // Wavefunction(s) for diagram number 318
      // (none)

      // Amplitude(s) for diagram number 318
      VVV1_0( w_sv[1], w_sv[29], w_sv[98], COUPs[0], &amp_sv[0] );
      jamp_sv[57] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[71] += +amp_sv[0];

      // *** DIAGRAM 319 OF 1240 ***

      // Wavefunction(s) for diagram number 319
      // (none)

      // Amplitude(s) for diagram number 319
      FFV1_0( w_sv[89], w_sv[33], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[57] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[59] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 320 OF 1240 ***

      // Wavefunction(s) for diagram number 320
      // (none)

      // Amplitude(s) for diagram number 320
      FFV1_0( w_sv[99], w_sv[43], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[89] -= amp_sv[0];

      // *** DIAGRAM 321 OF 1240 ***

      // Wavefunction(s) for diagram number 321
      // (none)

      // Amplitude(s) for diagram number 321
      FFV1_0( w_sv[99], w_sv[44], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[95] -= amp_sv[0];

      // *** DIAGRAM 322 OF 1240 ***

      // Wavefunction(s) for diagram number 322
      FFV1_1( w_sv[39], w_sv[1], COUPs[1], cIPD[0], cIPD[1], w_sv[89] );

      // Amplitude(s) for diagram number 322
      FFV1_0( w_sv[34], w_sv[89], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[83] -= amp_sv[0];

      // *** DIAGRAM 323 OF 1240 ***

      // Wavefunction(s) for diagram number 323
      // (none)

      // Amplitude(s) for diagram number 323
      FFV1_0( w_sv[34], w_sv[44], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[93] -= amp_sv[0];

      // *** DIAGRAM 324 OF 1240 ***

      // Wavefunction(s) for diagram number 324
      // (none)

      // Amplitude(s) for diagram number 324
      FFV1_0( w_sv[88], w_sv[89], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[81] -= amp_sv[0];

      // *** DIAGRAM 325 OF 1240 ***

      // Wavefunction(s) for diagram number 325
      // (none)

      // Amplitude(s) for diagram number 325
      FFV1_0( w_sv[88], w_sv[43], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[87] -= amp_sv[0];

      // *** DIAGRAM 326 OF 1240 ***

      // Wavefunction(s) for diagram number 326
      // (none)

      // Amplitude(s) for diagram number 326
      FFV1_0( w_sv[99], w_sv[39], w_sv[27], COUPs[1], &amp_sv[0] );
      jamp_sv[89] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[95] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 327 OF 1240 ***

      // Wavefunction(s) for diagram number 327
      // (none)

      // Amplitude(s) for diagram number 327
      VVV1_0( w_sv[1], w_sv[27], w_sv[95], COUPs[0], &amp_sv[0] );
      jamp_sv[81] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[89] -= amp_sv[0];
      jamp_sv[95] += +amp_sv[0];

      // *** DIAGRAM 328 OF 1240 ***

      // Wavefunction(s) for diagram number 328
      // (none)

      // Amplitude(s) for diagram number 328
      FFV1_0( w_sv[91], w_sv[39], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[81] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[83] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 329 OF 1240 ***

      // Wavefunction(s) for diagram number 329
      // (none)

      // Amplitude(s) for diagram number 329
      FFV1_0( w_sv[99], w_sv[49], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[113] -= amp_sv[0];

      // *** DIAGRAM 330 OF 1240 ***

      // Wavefunction(s) for diagram number 330
      // (none)

      // Amplitude(s) for diagram number 330
      FFV1_0( w_sv[99], w_sv[50], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[119] -= amp_sv[0];

      // *** DIAGRAM 331 OF 1240 ***

      // Wavefunction(s) for diagram number 331
      FFV1_1( w_sv[47], w_sv[1], COUPs[1], cIPD[0], cIPD[1], w_sv[91] );

      // Amplitude(s) for diagram number 331
      FFV1_0( w_sv[34], w_sv[91], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[107] -= amp_sv[0];

      // *** DIAGRAM 332 OF 1240 ***

      // Wavefunction(s) for diagram number 332
      // (none)

      // Amplitude(s) for diagram number 332
      FFV1_0( w_sv[34], w_sv[50], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[117] -= amp_sv[0];

      // *** DIAGRAM 333 OF 1240 ***

      // Wavefunction(s) for diagram number 333
      // (none)

      // Amplitude(s) for diagram number 333
      FFV1_0( w_sv[86], w_sv[91], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[105] -= amp_sv[0];

      // *** DIAGRAM 334 OF 1240 ***

      // Wavefunction(s) for diagram number 334
      // (none)

      // Amplitude(s) for diagram number 334
      FFV1_0( w_sv[86], w_sv[49], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[111] -= amp_sv[0];

      // *** DIAGRAM 335 OF 1240 ***

      // Wavefunction(s) for diagram number 335
      // (none)

      // Amplitude(s) for diagram number 335
      FFV1_0( w_sv[99], w_sv[47], w_sv[24], COUPs[1], &amp_sv[0] );
      jamp_sv[113] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[119] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 336 OF 1240 ***

      // Wavefunction(s) for diagram number 336
      // (none)

      // Amplitude(s) for diagram number 336
      VVV1_0( w_sv[1], w_sv[24], w_sv[96], COUPs[0], &amp_sv[0] );
      jamp_sv[105] += +amp_sv[0];
      jamp_sv[107] -= amp_sv[0];
      jamp_sv[113] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];

      // *** DIAGRAM 337 OF 1240 ***

      // Wavefunction(s) for diagram number 337
      // (none)

      // Amplitude(s) for diagram number 337
      FFV1_0( w_sv[90], w_sv[47], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[105] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[107] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 338 OF 1240 ***

      // Wavefunction(s) for diagram number 338
      // (none)

      // Amplitude(s) for diagram number 338
      FFV1_0( w_sv[99], w_sv[17], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[65] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[89] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 339 OF 1240 ***

      // Wavefunction(s) for diagram number 339
      // (none)

      // Amplitude(s) for diagram number 339
      FFV1_0( w_sv[99], w_sv[2], w_sv[42], COUPs[1], &amp_sv[0] );
      jamp_sv[65] += +amp_sv[0];
      jamp_sv[89] -= amp_sv[0];
      jamp_sv[113] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];

      // *** DIAGRAM 340 OF 1240 ***

      // Wavefunction(s) for diagram number 340
      // (none)

      // Amplitude(s) for diagram number 340
      VVV1_0( w_sv[92], w_sv[59], w_sv[6], COUPs[0], &amp_sv[0] );
      jamp_sv[33] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[39] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[63] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[87] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[105] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[107] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[113] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[119] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 341 OF 1240 ***

      // Wavefunction(s) for diagram number 341
      // (none)

      // Amplitude(s) for diagram number 341
      VVV1_0( w_sv[92], w_sv[1], w_sv[42], COUPs[0], &amp_sv[0] );
      jamp_sv[33] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[39] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[45] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[47] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[65] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[89] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[113] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[119] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 342 OF 1240 ***

      // Wavefunction(s) for diagram number 342
      // (none)

      // Amplitude(s) for diagram number 342
      VVVV1_0( w_sv[1], w_sv[24], w_sv[6], w_sv[92], COUPs[2], &amp_sv[0] );
      jamp_sv[33] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[39] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[63] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[87] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[105] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[107] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[113] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[119] += +cxtype(0,1)*amp_sv[0];
      VVVV3_0( w_sv[1], w_sv[24], w_sv[6], w_sv[92], COUPs[2], &amp_sv[0] );
      jamp_sv[45] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[47] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[63] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[65] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[87] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[89] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[105] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[107] -= cxtype(0,1)*amp_sv[0];
      VVVV4_0( w_sv[1], w_sv[24], w_sv[6], w_sv[92], COUPs[2], &amp_sv[0] );
      jamp_sv[33] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[39] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[45] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[47] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[65] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[89] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[113] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[119] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 343 OF 1240 ***

      // Wavefunction(s) for diagram number 343
      // (none)

      // Amplitude(s) for diagram number 343
      FFV1_0( w_sv[88], w_sv[2], w_sv[59], COUPs[1], &amp_sv[0] );
      jamp_sv[33] += +amp_sv[0];
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[63] -= amp_sv[0];
      jamp_sv[87] += +amp_sv[0];

      // *** DIAGRAM 344 OF 1240 ***

      // Wavefunction(s) for diagram number 344
      // (none)

      // Amplitude(s) for diagram number 344
      FFV1_0( w_sv[88], w_sv[17], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[63] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[87] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 345 OF 1240 ***

      // Wavefunction(s) for diagram number 345
      // (none)

      // Amplitude(s) for diagram number 345
      FFV1_0( w_sv[99], w_sv[15], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[71] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[113] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 346 OF 1240 ***

      // Wavefunction(s) for diagram number 346
      // (none)

      // Amplitude(s) for diagram number 346
      FFV1_0( w_sv[99], w_sv[2], w_sv[16], COUPs[1], &amp_sv[0] );
      jamp_sv[71] += +amp_sv[0];
      jamp_sv[89] -= amp_sv[0];
      jamp_sv[95] += +amp_sv[0];
      jamp_sv[113] -= amp_sv[0];

      // *** DIAGRAM 347 OF 1240 ***

      // Wavefunction(s) for diagram number 347
      // (none)

      // Amplitude(s) for diagram number 347
      VVV1_0( w_sv[92], w_sv[68], w_sv[5], COUPs[0], &amp_sv[0] );
      jamp_sv[35] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[45] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[69] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[81] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[83] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[89] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[95] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[111] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 348 OF 1240 ***

      // Wavefunction(s) for diagram number 348
      // (none)

      // Amplitude(s) for diagram number 348
      VVV1_0( w_sv[92], w_sv[1], w_sv[16], COUPs[0], &amp_sv[0] );
      jamp_sv[35] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[39] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[41] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[45] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[71] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[89] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[95] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[113] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 349 OF 1240 ***

      // Wavefunction(s) for diagram number 349
      // (none)

      // Amplitude(s) for diagram number 349
      VVVV1_0( w_sv[1], w_sv[27], w_sv[5], w_sv[92], COUPs[2], &amp_sv[0] );
      jamp_sv[35] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[45] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[69] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[81] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[83] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[89] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[95] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[111] -= cxtype(0,1)*amp_sv[0];
      VVVV3_0( w_sv[1], w_sv[27], w_sv[5], w_sv[92], COUPs[2], &amp_sv[0] );
      jamp_sv[39] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[41] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[69] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[71] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[81] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[83] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[111] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[113] += +cxtype(0,1)*amp_sv[0];
      VVVV4_0( w_sv[1], w_sv[27], w_sv[5], w_sv[92], COUPs[2], &amp_sv[0] );
      jamp_sv[35] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[39] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[41] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[45] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[71] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[89] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[95] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[113] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 350 OF 1240 ***

      // Wavefunction(s) for diagram number 350
      // (none)

      // Amplitude(s) for diagram number 350
      FFV1_0( w_sv[86], w_sv[2], w_sv[68], COUPs[1], &amp_sv[0] );
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[45] -= amp_sv[0];
      jamp_sv[69] -= amp_sv[0];
      jamp_sv[111] += +amp_sv[0];

      // *** DIAGRAM 351 OF 1240 ***

      // Wavefunction(s) for diagram number 351
      // (none)

      // Amplitude(s) for diagram number 351
      FFV1_0( w_sv[86], w_sv[15], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[69] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[111] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 352 OF 1240 ***

      // Wavefunction(s) for diagram number 352
      // (none)

      // Amplitude(s) for diagram number 352
      FFV1_0( w_sv[99], w_sv[18], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[95] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[119] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 353 OF 1240 ***

      // Wavefunction(s) for diagram number 353
      // (none)

      // Amplitude(s) for diagram number 353
      FFV1_0( w_sv[99], w_sv[2], w_sv[19], COUPs[1], &amp_sv[0] );
      jamp_sv[65] += +amp_sv[0];
      jamp_sv[71] -= amp_sv[0];
      jamp_sv[95] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];

      // *** DIAGRAM 354 OF 1240 ***

      // Wavefunction(s) for diagram number 354
      // (none)

      // Amplitude(s) for diagram number 354
      VVV1_0( w_sv[92], w_sv[67], w_sv[4], COUPs[0], &amp_sv[0] );
      jamp_sv[41] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[47] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[57] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[59] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[65] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[71] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[93] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[117] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 355 OF 1240 ***

      // Wavefunction(s) for diagram number 355
      // (none)

      // Amplitude(s) for diagram number 355
      VVV1_0( w_sv[92], w_sv[1], w_sv[19], COUPs[0], &amp_sv[0] );
      jamp_sv[33] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[35] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[41] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[47] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[65] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[71] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[95] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[119] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 356 OF 1240 ***

      // Wavefunction(s) for diagram number 356
      // (none)

      // Amplitude(s) for diagram number 356
      VVVV1_0( w_sv[1], w_sv[4], w_sv[29], w_sv[92], COUPs[2], &amp_sv[0] );
      jamp_sv[33] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[35] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[57] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[59] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[93] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[95] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[117] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[119] += +cxtype(0,1)*amp_sv[0];
      VVVV3_0( w_sv[1], w_sv[4], w_sv[29], w_sv[92], COUPs[2], &amp_sv[0] );
      jamp_sv[41] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[47] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[57] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[59] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[65] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[71] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[93] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[117] -= cxtype(0,1)*amp_sv[0];
      VVVV4_0( w_sv[1], w_sv[4], w_sv[29], w_sv[92], COUPs[2], &amp_sv[0] );
      jamp_sv[33] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[35] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[41] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[47] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[65] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[71] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[95] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[119] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 357 OF 1240 ***

      // Wavefunction(s) for diagram number 357
      // (none)

      // Amplitude(s) for diagram number 357
      FFV1_0( w_sv[34], w_sv[2], w_sv[67], COUPs[1], &amp_sv[0] );
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[47] -= amp_sv[0];
      jamp_sv[93] -= amp_sv[0];
      jamp_sv[117] += +amp_sv[0];

      // *** DIAGRAM 358 OF 1240 ***

      // Wavefunction(s) for diagram number 358
      // (none)

      // Amplitude(s) for diagram number 358
      FFV1_0( w_sv[34], w_sv[18], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[93] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[117] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 359 OF 1240 ***

      // Wavefunction(s) for diagram number 359
      // (none)

      // Amplitude(s) for diagram number 359
      VVV1_0( w_sv[73], w_sv[6], w_sv[92], COUPs[0], &amp_sv[0] );
      jamp_sv[33] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[39] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[63] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[87] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[105] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[107] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[113] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[119] += +cxtype(0,1)*amp_sv[0];
      VVV1_0( w_sv[79], w_sv[6], w_sv[92], COUPs[0], &amp_sv[0] );
      jamp_sv[39] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[57] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[63] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[81] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[107] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[111] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[113] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[117] += +cxtype(0,1)*amp_sv[0];
      VVV1_0( w_sv[80], w_sv[6], w_sv[92], COUPs[0], &amp_sv[0] );
      jamp_sv[33] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[57] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[81] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[87] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[105] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[111] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[117] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[119] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 360 OF 1240 ***

      // Wavefunction(s) for diagram number 360
      // (none)

      // Amplitude(s) for diagram number 360
      FFV1_0( w_sv[88], w_sv[2], w_sv[73], COUPs[1], &amp_sv[0] );
      jamp_sv[33] += +amp_sv[0];
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[63] -= amp_sv[0];
      jamp_sv[87] += +amp_sv[0];
      FFV1_0( w_sv[88], w_sv[2], w_sv[79], COUPs[1], &amp_sv[0] );
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[57] += +amp_sv[0];
      jamp_sv[63] -= amp_sv[0];
      jamp_sv[81] += +amp_sv[0];
      FFV1_0( w_sv[88], w_sv[2], w_sv[80], COUPs[1], &amp_sv[0] );
      jamp_sv[33] -= amp_sv[0];
      jamp_sv[57] += +amp_sv[0];
      jamp_sv[81] += +amp_sv[0];
      jamp_sv[87] -= amp_sv[0];

      // *** DIAGRAM 361 OF 1240 ***

      // Wavefunction(s) for diagram number 361
      // (none)

      // Amplitude(s) for diagram number 361
      FFV1_0( w_sv[62], w_sv[47], w_sv[73], COUPs[1], &amp_sv[0] );
      jamp_sv[105] += +amp_sv[0];
      jamp_sv[107] -= amp_sv[0];
      jamp_sv[113] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];
      FFV1_0( w_sv[62], w_sv[47], w_sv[79], COUPs[1], &amp_sv[0] );
      jamp_sv[107] -= amp_sv[0];
      jamp_sv[111] += +amp_sv[0];
      jamp_sv[113] -= amp_sv[0];
      jamp_sv[117] += +amp_sv[0];
      FFV1_0( w_sv[62], w_sv[47], w_sv[80], COUPs[1], &amp_sv[0] );
      jamp_sv[105] -= amp_sv[0];
      jamp_sv[111] += +amp_sv[0];
      jamp_sv[117] += +amp_sv[0];
      jamp_sv[119] -= amp_sv[0];

      // *** DIAGRAM 362 OF 1240 ***

      // Wavefunction(s) for diagram number 362
      // (none)

      // Amplitude(s) for diagram number 362
      VVV1_0( w_sv[57], w_sv[5], w_sv[92], COUPs[0], &amp_sv[0] );
      jamp_sv[35] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[45] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[69] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[81] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[83] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[89] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[95] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[111] -= cxtype(0,1)*amp_sv[0];
      VVV1_0( w_sv[81], w_sv[5], w_sv[92], COUPs[0], &amp_sv[0] );
      jamp_sv[45] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[59] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[69] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[83] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[87] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[89] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[93] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[105] -= cxtype(0,1)*amp_sv[0];
      VVV1_0( w_sv[82], w_sv[5], w_sv[92], COUPs[0], &amp_sv[0] );
      jamp_sv[35] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[59] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[81] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[87] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[93] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[95] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[105] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[111] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 363 OF 1240 ***

      // Wavefunction(s) for diagram number 363
      // (none)

      // Amplitude(s) for diagram number 363
      FFV1_0( w_sv[86], w_sv[2], w_sv[57], COUPs[1], &amp_sv[0] );
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[45] -= amp_sv[0];
      jamp_sv[69] -= amp_sv[0];
      jamp_sv[111] += +amp_sv[0];
      FFV1_0( w_sv[86], w_sv[2], w_sv[81], COUPs[1], &amp_sv[0] );
      jamp_sv[45] -= amp_sv[0];
      jamp_sv[59] += +amp_sv[0];
      jamp_sv[69] -= amp_sv[0];
      jamp_sv[105] += +amp_sv[0];
      FFV1_0( w_sv[86], w_sv[2], w_sv[82], COUPs[1], &amp_sv[0] );
      jamp_sv[35] -= amp_sv[0];
      jamp_sv[59] += +amp_sv[0];
      jamp_sv[105] += +amp_sv[0];
      jamp_sv[111] -= amp_sv[0];

      // *** DIAGRAM 364 OF 1240 ***

      // Wavefunction(s) for diagram number 364
      // (none)

      // Amplitude(s) for diagram number 364
      FFV1_0( w_sv[62], w_sv[39], w_sv[57], COUPs[1], &amp_sv[0] );
      jamp_sv[81] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[89] -= amp_sv[0];
      jamp_sv[95] += +amp_sv[0];
      FFV1_0( w_sv[62], w_sv[39], w_sv[81], COUPs[1], &amp_sv[0] );
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[87] += +amp_sv[0];
      jamp_sv[89] -= amp_sv[0];
      jamp_sv[93] += +amp_sv[0];
      FFV1_0( w_sv[62], w_sv[39], w_sv[82], COUPs[1], &amp_sv[0] );
      jamp_sv[81] -= amp_sv[0];
      jamp_sv[87] += +amp_sv[0];
      jamp_sv[93] += +amp_sv[0];
      jamp_sv[95] -= amp_sv[0];

      // *** DIAGRAM 365 OF 1240 ***

      // Wavefunction(s) for diagram number 365
      // (none)

      // Amplitude(s) for diagram number 365
      VVV1_0( w_sv[55], w_sv[4], w_sv[92], COUPs[0], &amp_sv[0] );
      jamp_sv[41] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[47] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[57] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[59] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[65] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[71] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[93] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[117] -= cxtype(0,1)*amp_sv[0];
      VVV1_0( w_sv[83], w_sv[4], w_sv[92], COUPs[0], &amp_sv[0] );
      jamp_sv[47] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[59] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[63] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[65] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[69] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[83] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[93] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[107] -= cxtype(0,1)*amp_sv[0];
      VVV1_0( w_sv[84], w_sv[4], w_sv[92], COUPs[0], &amp_sv[0] );
      jamp_sv[41] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[57] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[63] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[69] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[71] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[83] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[107] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[117] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 366 OF 1240 ***

      // Wavefunction(s) for diagram number 366
      // (none)

      // Amplitude(s) for diagram number 366
      FFV1_0( w_sv[34], w_sv[2], w_sv[55], COUPs[1], &amp_sv[0] );
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[47] -= amp_sv[0];
      jamp_sv[93] -= amp_sv[0];
      jamp_sv[117] += +amp_sv[0];
      FFV1_0( w_sv[34], w_sv[2], w_sv[83], COUPs[1], &amp_sv[0] );
      jamp_sv[47] -= amp_sv[0];
      jamp_sv[83] += +amp_sv[0];
      jamp_sv[93] -= amp_sv[0];
      jamp_sv[107] += +amp_sv[0];
      FFV1_0( w_sv[34], w_sv[2], w_sv[84], COUPs[1], &amp_sv[0] );
      jamp_sv[41] -= amp_sv[0];
      jamp_sv[83] += +amp_sv[0];
      jamp_sv[107] += +amp_sv[0];
      jamp_sv[117] -= amp_sv[0];

      // *** DIAGRAM 367 OF 1240 ***

      // Wavefunction(s) for diagram number 367
      // (none)

      // Amplitude(s) for diagram number 367
      FFV1_0( w_sv[62], w_sv[33], w_sv[55], COUPs[1], &amp_sv[0] );
      jamp_sv[57] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[71] += +amp_sv[0];
      FFV1_0( w_sv[62], w_sv[33], w_sv[83], COUPs[1], &amp_sv[0] );
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[69] += +amp_sv[0];
      FFV1_0( w_sv[62], w_sv[33], w_sv[84], COUPs[1], &amp_sv[0] );
      jamp_sv[57] -= amp_sv[0];
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[69] += +amp_sv[0];
      jamp_sv[71] -= amp_sv[0];

      // *** DIAGRAM 368 OF 1240 ***

      // Wavefunction(s) for diagram number 368
      // (none)

      // Amplitude(s) for diagram number 368
      FFV1_0( w_sv[99], w_sv[2], w_sv[30], COUPs[1], &amp_sv[0] );
      jamp_sv[65] += +amp_sv[0];
      jamp_sv[71] -= amp_sv[0];
      jamp_sv[95] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];
      FFV1_0( w_sv[99], w_sv[2], w_sv[31], COUPs[1], &amp_sv[0] );
      jamp_sv[71] -= amp_sv[0];
      jamp_sv[89] += +amp_sv[0];
      jamp_sv[95] -= amp_sv[0];
      jamp_sv[113] += +amp_sv[0];
      FFV1_0( w_sv[99], w_sv[2], w_sv[32], COUPs[1], &amp_sv[0] );
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[89] += +amp_sv[0];
      jamp_sv[113] += +amp_sv[0];
      jamp_sv[119] -= amp_sv[0];

      // *** DIAGRAM 369 OF 1240 ***

      // Wavefunction(s) for diagram number 369
      // (none)

      // Amplitude(s) for diagram number 369
      VVV1_0( w_sv[1], w_sv[30], w_sv[92], COUPs[0], &amp_sv[0] );
      jamp_sv[33] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[35] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[41] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[47] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[65] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[71] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[95] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[119] += +cxtype(0,1)*amp_sv[0];
      VVV1_0( w_sv[1], w_sv[31], w_sv[92], COUPs[0], &amp_sv[0] );
      jamp_sv[35] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[39] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[41] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[45] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[71] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[89] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[95] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[113] += +cxtype(0,1)*amp_sv[0];
      VVV1_0( w_sv[1], w_sv[32], w_sv[92], COUPs[0], &amp_sv[0] );
      jamp_sv[33] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[39] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[45] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[47] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[65] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[89] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[113] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[119] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 370 OF 1240 ***

      // Wavefunction(s) for diagram number 370
      VVV1P0_1( w_sv[0], w_sv[4], COUPs[0], 0., 0., w_sv[92] );
      FFV1_2( w_sv[3], w_sv[92], COUPs[1], cIPD[0], cIPD[1], w_sv[99] );

      // Amplitude(s) for diagram number 370
      FFV1_0( w_sv[99], w_sv[9], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[40] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[41] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 371 OF 1240 ***

      // Wavefunction(s) for diagram number 371
      // (none)

      // Amplitude(s) for diagram number 371
      FFV1_0( w_sv[99], w_sv[85], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[46] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[47] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 372 OF 1240 ***

      // Wavefunction(s) for diagram number 372
      VVV1P0_1( w_sv[92], w_sv[5], COUPs[0], 0., 0., w_sv[62] );
      FFV1P0_3( w_sv[3], w_sv[77], COUPs[1], 0., 0., w_sv[34] );

      // Amplitude(s) for diagram number 372
      VVV1_0( w_sv[62], w_sv[34], w_sv[6], COUPs[0], &amp_sv[0] );
      jamp_sv[24] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[30] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[36] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[38] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[42] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[44] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[46] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[47] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 373 OF 1240 ***

      // Wavefunction(s) for diagram number 373
      // (none)

      // Amplitude(s) for diagram number 373
      FFV1_0( w_sv[3], w_sv[85], w_sv[62], COUPs[1], &amp_sv[0] );
      jamp_sv[42] += +amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];

      // *** DIAGRAM 374 OF 1240 ***

      // Wavefunction(s) for diagram number 374
      VVV1P0_1( w_sv[92], w_sv[6], COUPs[0], 0., 0., w_sv[86] );

      // Amplitude(s) for diagram number 374
      VVV1_0( w_sv[86], w_sv[34], w_sv[5], COUPs[0], &amp_sv[0] );
      jamp_sv[25] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[31] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[36] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[38] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[40] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[41] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[42] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[44] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 375 OF 1240 ***

      // Wavefunction(s) for diagram number 375
      // (none)

      // Amplitude(s) for diagram number 375
      FFV1_0( w_sv[3], w_sv[9], w_sv[86], COUPs[1], &amp_sv[0] );
      jamp_sv[36] += +amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[41] += +amp_sv[0];

      // *** DIAGRAM 376 OF 1240 ***

      // Wavefunction(s) for diagram number 376
      VVVV1P0_1( w_sv[92], w_sv[5], w_sv[6], COUPs[2], 0., 0., w_sv[88] );
      VVVV3P0_1( w_sv[92], w_sv[5], w_sv[6], COUPs[2], 0., 0., w_sv[90] );
      VVVV4P0_1( w_sv[92], w_sv[5], w_sv[6], COUPs[2], 0., 0., w_sv[96] );

      // Amplitude(s) for diagram number 376
      FFV1_0( w_sv[3], w_sv[77], w_sv[88], COUPs[1], &amp_sv[0] );
      jamp_sv[24] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[25] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[30] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[31] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[40] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[41] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[46] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[47] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[77], w_sv[90], COUPs[1], &amp_sv[0] );
      jamp_sv[25] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[31] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[36] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[38] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[40] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[41] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[42] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[44] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[77], w_sv[96], COUPs[1], &amp_sv[0] );
      jamp_sv[24] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[30] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[36] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[38] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[42] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[44] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[46] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[47] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 377 OF 1240 ***

      // Wavefunction(s) for diagram number 377
      FFV1_1( w_sv[77], w_sv[92], COUPs[1], cIPD[0], cIPD[1], w_sv[95] );

      // Amplitude(s) for diagram number 377
      FFV1_0( w_sv[38], w_sv[95], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[25] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[31] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 378 OF 1240 ***

      // Wavefunction(s) for diagram number 378
      FFV1_2( w_sv[38], w_sv[92], COUPs[1], cIPD[0], cIPD[1], w_sv[98] );

      // Amplitude(s) for diagram number 378
      FFV1_0( w_sv[98], w_sv[77], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[42] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[44] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 379 OF 1240 ***

      // Wavefunction(s) for diagram number 379
      // (none)

      // Amplitude(s) for diagram number 379
      FFV1_0( w_sv[38], w_sv[77], w_sv[86], COUPs[1], &amp_sv[0] );
      jamp_sv[25] += +amp_sv[0];
      jamp_sv[31] -= amp_sv[0];
      jamp_sv[42] -= amp_sv[0];
      jamp_sv[44] += +amp_sv[0];

      // *** DIAGRAM 380 OF 1240 ***

      // Wavefunction(s) for diagram number 380
      // (none)

      // Amplitude(s) for diagram number 380
      FFV1_0( w_sv[41], w_sv[95], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[24] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[30] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 381 OF 1240 ***

      // Wavefunction(s) for diagram number 381
      FFV1_2( w_sv[41], w_sv[92], COUPs[1], cIPD[0], cIPD[1], w_sv[101] );

      // Amplitude(s) for diagram number 381
      FFV1_0( w_sv[101], w_sv[77], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[36] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[38] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 382 OF 1240 ***

      // Wavefunction(s) for diagram number 382
      // (none)

      // Amplitude(s) for diagram number 382
      FFV1_0( w_sv[41], w_sv[77], w_sv[62], COUPs[1], &amp_sv[0] );
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[30] -= amp_sv[0];
      jamp_sv[36] -= amp_sv[0];
      jamp_sv[38] += +amp_sv[0];

      // *** DIAGRAM 383 OF 1240 ***

      // Wavefunction(s) for diagram number 383
      // (none)

      // Amplitude(s) for diagram number 383
      FFV1_0( w_sv[3], w_sv[95], w_sv[29], COUPs[1], &amp_sv[0] );
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[25] -= amp_sv[0];
      jamp_sv[30] -= amp_sv[0];
      jamp_sv[31] += +amp_sv[0];

      // *** DIAGRAM 384 OF 1240 ***

      // Wavefunction(s) for diagram number 384
      // (none)

      // Amplitude(s) for diagram number 384
      FFV1_0( w_sv[99], w_sv[77], w_sv[29], COUPs[1], &amp_sv[0] );
      jamp_sv[40] += +amp_sv[0];
      jamp_sv[41] -= amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];

      // *** DIAGRAM 385 OF 1240 ***

      // Wavefunction(s) for diagram number 385
      VVV1P0_1( w_sv[92], w_sv[29], COUPs[0], 0., 0., w_sv[95] );

      // Amplitude(s) for diagram number 385
      FFV1_0( w_sv[3], w_sv[77], w_sv[95], COUPs[1], &amp_sv[0] );
      jamp_sv[24] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[25] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[30] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[31] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[40] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[41] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[46] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[47] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 386 OF 1240 ***

      // Wavefunction(s) for diagram number 386
      FFV1_1( w_sv[2], w_sv[92], COUPs[1], cIPD[0], cIPD[1], w_sv[102] );

      // Amplitude(s) for diagram number 386
      FFV1_0( w_sv[22], w_sv[102], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[11] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[53] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 387 OF 1240 ***

      // Wavefunction(s) for diagram number 387
      // (none)

      // Amplitude(s) for diagram number 387
      FFV1_0( w_sv[21], w_sv[102], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[9] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[51] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 388 OF 1240 ***

      // Wavefunction(s) for diagram number 388
      FFV1P0_3( w_sv[52], w_sv[2], COUPs[1], 0., 0., w_sv[103] );

      // Amplitude(s) for diagram number 388
      VVV1_0( w_sv[62], w_sv[103], w_sv[6], COUPs[0], &amp_sv[0] );
      jamp_sv[9] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[51] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[75] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[85] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[99] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[109] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[115] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[118] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 389 OF 1240 ***

      // Wavefunction(s) for diagram number 389
      // (none)

      // Amplitude(s) for diagram number 389
      FFV1_0( w_sv[21], w_sv[2], w_sv[62], COUPs[1], &amp_sv[0] );
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[85] += +amp_sv[0];

      // *** DIAGRAM 390 OF 1240 ***

      // Wavefunction(s) for diagram number 390
      // (none)

      // Amplitude(s) for diagram number 390
      VVV1_0( w_sv[86], w_sv[103], w_sv[5], COUPs[0], &amp_sv[0] );
      jamp_sv[11] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[53] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[75] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[85] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[91] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[94] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[99] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[109] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 391 OF 1240 ***

      // Wavefunction(s) for diagram number 391
      // (none)

      // Amplitude(s) for diagram number 391
      FFV1_0( w_sv[22], w_sv[2], w_sv[86], COUPs[1], &amp_sv[0] );
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[99] -= amp_sv[0];
      jamp_sv[109] += +amp_sv[0];

      // *** DIAGRAM 392 OF 1240 ***

      // Wavefunction(s) for diagram number 392
      // (none)

      // Amplitude(s) for diagram number 392
      FFV1_0( w_sv[52], w_sv[2], w_sv[88], COUPs[1], &amp_sv[0] );
      jamp_sv[9] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[11] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[51] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[53] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[91] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[94] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[115] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[118] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[52], w_sv[2], w_sv[90], COUPs[1], &amp_sv[0] );
      jamp_sv[11] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[53] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[75] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[85] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[91] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[94] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[99] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[109] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[52], w_sv[2], w_sv[96], COUPs[1], &amp_sv[0] );
      jamp_sv[9] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[51] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[75] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[85] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[99] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[109] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[115] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[118] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 393 OF 1240 ***

      // Wavefunction(s) for diagram number 393
      FFV1_2( w_sv[52], w_sv[92], COUPs[1], cIPD[0], cIPD[1], w_sv[104] );

      // Amplitude(s) for diagram number 393
      FFV1_0( w_sv[104], w_sv[39], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[91] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[94] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 394 OF 1240 ***

      // Wavefunction(s) for diagram number 394
      FFV1_1( w_sv[39], w_sv[92], COUPs[1], cIPD[0], cIPD[1], w_sv[105] );

      // Amplitude(s) for diagram number 394
      FFV1_0( w_sv[52], w_sv[105], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[75] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[85] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 395 OF 1240 ***

      // Wavefunction(s) for diagram number 395
      // (none)

      // Amplitude(s) for diagram number 395
      FFV1_0( w_sv[52], w_sv[39], w_sv[86], COUPs[1], &amp_sv[0] );
      jamp_sv[75] += +amp_sv[0];
      jamp_sv[85] -= amp_sv[0];
      jamp_sv[91] -= amp_sv[0];
      jamp_sv[94] += +amp_sv[0];

      // *** DIAGRAM 396 OF 1240 ***

      // Wavefunction(s) for diagram number 396
      // (none)

      // Amplitude(s) for diagram number 396
      FFV1_0( w_sv[104], w_sv[47], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[115] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[118] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 397 OF 1240 ***

      // Wavefunction(s) for diagram number 397
      FFV1_1( w_sv[47], w_sv[92], COUPs[1], cIPD[0], cIPD[1], w_sv[106] );

      // Amplitude(s) for diagram number 397
      FFV1_0( w_sv[52], w_sv[106], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[99] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[109] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 398 OF 1240 ***

      // Wavefunction(s) for diagram number 398
      // (none)

      // Amplitude(s) for diagram number 398
      FFV1_0( w_sv[52], w_sv[47], w_sv[62], COUPs[1], &amp_sv[0] );
      jamp_sv[99] += +amp_sv[0];
      jamp_sv[109] -= amp_sv[0];
      jamp_sv[115] -= amp_sv[0];
      jamp_sv[118] += +amp_sv[0];

      // *** DIAGRAM 399 OF 1240 ***

      // Wavefunction(s) for diagram number 399
      // (none)

      // Amplitude(s) for diagram number 399
      FFV1_0( w_sv[104], w_sv[2], w_sv[29], COUPs[1], &amp_sv[0] );
      jamp_sv[91] += +amp_sv[0];
      jamp_sv[94] -= amp_sv[0];
      jamp_sv[115] -= amp_sv[0];
      jamp_sv[118] += +amp_sv[0];

      // *** DIAGRAM 400 OF 1240 ***

      // Wavefunction(s) for diagram number 400
      // (none)

      // Amplitude(s) for diagram number 400
      FFV1_0( w_sv[52], w_sv[102], w_sv[29], COUPs[1], &amp_sv[0] );
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[11] -= amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[53] += +amp_sv[0];

      // *** DIAGRAM 401 OF 1240 ***

      // Wavefunction(s) for diagram number 401
      // (none)

      // Amplitude(s) for diagram number 401
      FFV1_0( w_sv[52], w_sv[2], w_sv[95], COUPs[1], &amp_sv[0] );
      jamp_sv[9] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[11] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[51] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[53] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[91] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[94] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[115] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[118] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 402 OF 1240 ***

      // Wavefunction(s) for diagram number 402
      // (none)

      // Amplitude(s) for diagram number 402
      FFV1_0( w_sv[71], w_sv[102], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[10] += +amp_sv[0];
      jamp_sv[11] -= amp_sv[0];
      jamp_sv[52] -= amp_sv[0];
      jamp_sv[53] += +amp_sv[0];

      // *** DIAGRAM 403 OF 1240 ***

      // Wavefunction(s) for diagram number 403
      // (none)

      // Amplitude(s) for diagram number 403
      FFV1_0( w_sv[3], w_sv[102], w_sv[70], COUPs[1], &amp_sv[0] );
      jamp_sv[6] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[8] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[10] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[11] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[48] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[50] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[52] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[53] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 404 OF 1240 ***

      // Wavefunction(s) for diagram number 404
      // (none)

      // Amplitude(s) for diagram number 404
      FFV1_0( w_sv[99], w_sv[94], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[40] += +amp_sv[0];
      jamp_sv[41] -= amp_sv[0];
      jamp_sv[82] -= amp_sv[0];
      jamp_sv[83] += +amp_sv[0];

      // *** DIAGRAM 405 OF 1240 ***

      // Wavefunction(s) for diagram number 405
      // (none)

      // Amplitude(s) for diagram number 405
      FFV1_0( w_sv[99], w_sv[2], w_sv[70], COUPs[1], &amp_sv[0] );
      jamp_sv[40] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[41] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[82] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[83] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[106] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[107] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[116] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[117] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 406 OF 1240 ***

      // Wavefunction(s) for diagram number 406
      // (none)

      // Amplitude(s) for diagram number 406
      FFV1_0( w_sv[3], w_sv[94], w_sv[86], COUPs[1], &amp_sv[0] );
      jamp_sv[36] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[38] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[40] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[41] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[78] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[80] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[82] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[83] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 407 OF 1240 ***

      // Wavefunction(s) for diagram number 407
      // (none)

      // Amplitude(s) for diagram number 407
      FFV1_0( w_sv[71], w_sv[2], w_sv[86], COUPs[1], &amp_sv[0] );
      jamp_sv[10] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[11] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[52] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[53] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[98] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[99] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[108] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[109] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 408 OF 1240 ***

      // Wavefunction(s) for diagram number 408
      // (none)

      // Amplitude(s) for diagram number 408
      VVVV1_0( w_sv[92], w_sv[66], w_sv[8], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[6] += +amp_sv[0];
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[36] -= amp_sv[0];
      jamp_sv[38] += +amp_sv[0];
      jamp_sv[48] -= amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[78] += +amp_sv[0];
      jamp_sv[80] -= amp_sv[0];
      jamp_sv[98] -= amp_sv[0];
      jamp_sv[99] += +amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      jamp_sv[107] -= amp_sv[0];
      jamp_sv[108] += +amp_sv[0];
      jamp_sv[109] -= amp_sv[0];
      jamp_sv[116] -= amp_sv[0];
      jamp_sv[117] += +amp_sv[0];
      VVVV3_0( w_sv[92], w_sv[66], w_sv[8], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[6] += +amp_sv[0];
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[48] -= amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      jamp_sv[107] -= amp_sv[0];
      jamp_sv[116] -= amp_sv[0];
      jamp_sv[117] += +amp_sv[0];
      VVVV4_0( w_sv[92], w_sv[66], w_sv[8], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[36] += +amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      jamp_sv[99] -= amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      jamp_sv[109] += +amp_sv[0];

      // *** DIAGRAM 409 OF 1240 ***

      // Wavefunction(s) for diagram number 409
      VVV1P0_1( w_sv[92], w_sv[66], COUPs[0], 0., 0., w_sv[104] );

      // Amplitude(s) for diagram number 409
      VVV1_0( w_sv[8], w_sv[6], w_sv[104], COUPs[0], &amp_sv[0] );
      jamp_sv[6] += +amp_sv[0];
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[36] -= amp_sv[0];
      jamp_sv[38] += +amp_sv[0];
      jamp_sv[48] -= amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[78] += +amp_sv[0];
      jamp_sv[80] -= amp_sv[0];
      jamp_sv[98] -= amp_sv[0];
      jamp_sv[99] += +amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      jamp_sv[107] -= amp_sv[0];
      jamp_sv[108] += +amp_sv[0];
      jamp_sv[109] -= amp_sv[0];
      jamp_sv[116] -= amp_sv[0];
      jamp_sv[117] += +amp_sv[0];

      // *** DIAGRAM 410 OF 1240 ***

      // Wavefunction(s) for diagram number 410
      VVV1P0_1( w_sv[92], w_sv[8], COUPs[0], 0., 0., w_sv[107] );

      // Amplitude(s) for diagram number 410
      VVV1_0( w_sv[66], w_sv[6], w_sv[107], COUPs[0], &amp_sv[0] );
      jamp_sv[6] += +amp_sv[0];
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[48] -= amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      jamp_sv[107] -= amp_sv[0];
      jamp_sv[116] -= amp_sv[0];
      jamp_sv[117] += +amp_sv[0];

      // *** DIAGRAM 411 OF 1240 ***

      // Wavefunction(s) for diagram number 411
      // (none)

      // Amplitude(s) for diagram number 411
      VVV1_0( w_sv[66], w_sv[8], w_sv[86], COUPs[0], &amp_sv[0] );
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[36] += +amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      jamp_sv[99] -= amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      jamp_sv[109] += +amp_sv[0];

      // *** DIAGRAM 412 OF 1240 ***

      // Wavefunction(s) for diagram number 412
      // (none)

      // Amplitude(s) for diagram number 412
      FFV1_0( w_sv[3], w_sv[47], w_sv[104], COUPs[1], &amp_sv[0] );
      jamp_sv[98] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[99] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[106] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[107] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[108] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[109] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[116] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[117] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 413 OF 1240 ***

      // Wavefunction(s) for diagram number 413
      // (none)

      // Amplitude(s) for diagram number 413
      FFV1_0( w_sv[3], w_sv[106], w_sv[66], COUPs[1], &amp_sv[0] );
      jamp_sv[98] += +amp_sv[0];
      jamp_sv[99] -= amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      jamp_sv[109] += +amp_sv[0];

      // *** DIAGRAM 414 OF 1240 ***

      // Wavefunction(s) for diagram number 414
      // (none)

      // Amplitude(s) for diagram number 414
      FFV1_0( w_sv[99], w_sv[47], w_sv[66], COUPs[1], &amp_sv[0] );
      jamp_sv[106] += +amp_sv[0];
      jamp_sv[107] -= amp_sv[0];
      jamp_sv[116] -= amp_sv[0];
      jamp_sv[117] += +amp_sv[0];

      // *** DIAGRAM 415 OF 1240 ***

      // Wavefunction(s) for diagram number 415
      // (none)

      // Amplitude(s) for diagram number 415
      FFV1_0( w_sv[41], w_sv[2], w_sv[104], COUPs[1], &amp_sv[0] );
      jamp_sv[6] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[8] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[36] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[38] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[48] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[50] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[78] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[80] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 416 OF 1240 ***

      // Wavefunction(s) for diagram number 416
      // (none)

      // Amplitude(s) for diagram number 416
      FFV1_0( w_sv[41], w_sv[102], w_sv[66], COUPs[1], &amp_sv[0] );
      jamp_sv[6] += +amp_sv[0];
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[48] -= amp_sv[0];
      jamp_sv[50] += +amp_sv[0];

      // *** DIAGRAM 417 OF 1240 ***

      // Wavefunction(s) for diagram number 417
      // (none)

      // Amplitude(s) for diagram number 417
      FFV1_0( w_sv[101], w_sv[2], w_sv[66], COUPs[1], &amp_sv[0] );
      jamp_sv[36] += +amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[80] += +amp_sv[0];

      // *** DIAGRAM 418 OF 1240 ***

      // Wavefunction(s) for diagram number 418
      // (none)

      // Amplitude(s) for diagram number 418
      FFV1_0( w_sv[76], w_sv[102], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[8] += +amp_sv[0];
      jamp_sv[9] -= amp_sv[0];
      jamp_sv[50] -= amp_sv[0];
      jamp_sv[51] += +amp_sv[0];

      // *** DIAGRAM 419 OF 1240 ***

      // Wavefunction(s) for diagram number 419
      // (none)

      // Amplitude(s) for diagram number 419
      FFV1_0( w_sv[3], w_sv[102], w_sv[75], COUPs[1], &amp_sv[0] );
      jamp_sv[7] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[8] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[9] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[10] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[49] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[50] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[51] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[52] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 420 OF 1240 ***

      // Wavefunction(s) for diagram number 420
      // (none)

      // Amplitude(s) for diagram number 420
      FFV1_0( w_sv[99], w_sv[97], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[46] += +amp_sv[0];
      jamp_sv[47] -= amp_sv[0];
      jamp_sv[106] -= amp_sv[0];
      jamp_sv[107] += +amp_sv[0];

      // *** DIAGRAM 421 OF 1240 ***

      // Wavefunction(s) for diagram number 421
      // (none)

      // Amplitude(s) for diagram number 421
      FFV1_0( w_sv[99], w_sv[2], w_sv[75], COUPs[1], &amp_sv[0] );
      jamp_sv[46] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[47] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[82] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[83] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[92] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[93] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[106] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[107] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 422 OF 1240 ***

      // Wavefunction(s) for diagram number 422
      // (none)

      // Amplitude(s) for diagram number 422
      FFV1_0( w_sv[3], w_sv[97], w_sv[62], COUPs[1], &amp_sv[0] );
      jamp_sv[42] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[44] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[46] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[47] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[102] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[104] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[106] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[107] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 423 OF 1240 ***

      // Wavefunction(s) for diagram number 423
      // (none)

      // Amplitude(s) for diagram number 423
      FFV1_0( w_sv[76], w_sv[2], w_sv[62], COUPs[1], &amp_sv[0] );
      jamp_sv[8] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[9] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[50] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[51] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[74] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[75] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[84] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[85] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 424 OF 1240 ***

      // Wavefunction(s) for diagram number 424
      // (none)

      // Amplitude(s) for diagram number 424
      VVVV1_0( w_sv[92], w_sv[72], w_sv[8], w_sv[5], COUPs[2], &amp_sv[0] );
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[42] -= amp_sv[0];
      jamp_sv[44] += +amp_sv[0];
      jamp_sv[49] -= amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[74] -= amp_sv[0];
      jamp_sv[75] += +amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[84] += +amp_sv[0];
      jamp_sv[85] -= amp_sv[0];
      jamp_sv[92] -= amp_sv[0];
      jamp_sv[93] += +amp_sv[0];
      jamp_sv[102] += +amp_sv[0];
      jamp_sv[104] -= amp_sv[0];
      VVVV3_0( w_sv[92], w_sv[72], w_sv[8], w_sv[5], COUPs[2], &amp_sv[0] );
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[49] -= amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[92] -= amp_sv[0];
      jamp_sv[93] += +amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      jamp_sv[107] -= amp_sv[0];
      VVVV4_0( w_sv[92], w_sv[72], w_sv[8], w_sv[5], COUPs[2], &amp_sv[0] );
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[42] += +amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[85] += +amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      jamp_sv[107] -= amp_sv[0];

      // *** DIAGRAM 425 OF 1240 ***

      // Wavefunction(s) for diagram number 425
      VVV1P0_1( w_sv[92], w_sv[72], COUPs[0], 0., 0., w_sv[104] );

      // Amplitude(s) for diagram number 425
      VVV1_0( w_sv[8], w_sv[5], w_sv[104], COUPs[0], &amp_sv[0] );
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[42] -= amp_sv[0];
      jamp_sv[44] += +amp_sv[0];
      jamp_sv[49] -= amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[74] -= amp_sv[0];
      jamp_sv[75] += +amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[84] += +amp_sv[0];
      jamp_sv[85] -= amp_sv[0];
      jamp_sv[92] -= amp_sv[0];
      jamp_sv[93] += +amp_sv[0];
      jamp_sv[102] += +amp_sv[0];
      jamp_sv[104] -= amp_sv[0];

      // *** DIAGRAM 426 OF 1240 ***

      // Wavefunction(s) for diagram number 426
      // (none)

      // Amplitude(s) for diagram number 426
      VVV1_0( w_sv[72], w_sv[5], w_sv[107], COUPs[0], &amp_sv[0] );
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[49] -= amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[92] -= amp_sv[0];
      jamp_sv[93] += +amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      jamp_sv[107] -= amp_sv[0];

      // *** DIAGRAM 427 OF 1240 ***

      // Wavefunction(s) for diagram number 427
      // (none)

      // Amplitude(s) for diagram number 427
      VVV1_0( w_sv[72], w_sv[8], w_sv[62], COUPs[0], &amp_sv[0] );
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[42] += +amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[85] += +amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      jamp_sv[107] -= amp_sv[0];

      // *** DIAGRAM 428 OF 1240 ***

      // Wavefunction(s) for diagram number 428
      // (none)

      // Amplitude(s) for diagram number 428
      FFV1_0( w_sv[3], w_sv[39], w_sv[104], COUPs[1], &amp_sv[0] );
      jamp_sv[74] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[75] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[82] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[83] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[84] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[85] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[92] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[93] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 429 OF 1240 ***

      // Wavefunction(s) for diagram number 429
      // (none)

      // Amplitude(s) for diagram number 429
      FFV1_0( w_sv[3], w_sv[105], w_sv[72], COUPs[1], &amp_sv[0] );
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[85] += +amp_sv[0];

      // *** DIAGRAM 430 OF 1240 ***

      // Wavefunction(s) for diagram number 430
      // (none)

      // Amplitude(s) for diagram number 430
      FFV1_0( w_sv[99], w_sv[39], w_sv[72], COUPs[1], &amp_sv[0] );
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[92] -= amp_sv[0];
      jamp_sv[93] += +amp_sv[0];

      // *** DIAGRAM 431 OF 1240 ***

      // Wavefunction(s) for diagram number 431
      // (none)

      // Amplitude(s) for diagram number 431
      FFV1_0( w_sv[38], w_sv[2], w_sv[104], COUPs[1], &amp_sv[0] );
      jamp_sv[7] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[10] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[42] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[44] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[49] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[52] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[102] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[104] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 432 OF 1240 ***

      // Wavefunction(s) for diagram number 432
      // (none)

      // Amplitude(s) for diagram number 432
      FFV1_0( w_sv[38], w_sv[102], w_sv[72], COUPs[1], &amp_sv[0] );
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[49] -= amp_sv[0];
      jamp_sv[52] += +amp_sv[0];

      // *** DIAGRAM 433 OF 1240 ***

      // Wavefunction(s) for diagram number 433
      // (none)

      // Amplitude(s) for diagram number 433
      FFV1_0( w_sv[98], w_sv[2], w_sv[72], COUPs[1], &amp_sv[0] );
      jamp_sv[42] += +amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[104] += +amp_sv[0];

      // *** DIAGRAM 434 OF 1240 ***

      // Wavefunction(s) for diagram number 434
      VVV1P0_1( w_sv[92], w_sv[1], COUPs[0], 0., 0., w_sv[104] );

      // Amplitude(s) for diagram number 434
      VVV1_0( w_sv[104], w_sv[10], w_sv[6], COUPs[0], &amp_sv[0] );
      jamp_sv[7] -= amp_sv[0];
      jamp_sv[25] += +amp_sv[0];
      jamp_sv[31] -= amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[91] -= amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[93] -= amp_sv[0];
      jamp_sv[94] += +amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[108] -= amp_sv[0];

      // *** DIAGRAM 435 OF 1240 ***

      // Wavefunction(s) for diagram number 435
      // (none)

      // Amplitude(s) for diagram number 435
      VVV1_0( w_sv[104], w_sv[11], w_sv[5], COUPs[0], &amp_sv[0] );
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[30] -= amp_sv[0];
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      jamp_sv[115] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];
      jamp_sv[117] -= amp_sv[0];
      jamp_sv[118] += +amp_sv[0];

      // *** DIAGRAM 436 OF 1240 ***

      // Wavefunction(s) for diagram number 436
      // (none)

      // Amplitude(s) for diagram number 436
      VVVV1_0( w_sv[8], w_sv[5], w_sv[6], w_sv[104], COUPs[2], &amp_sv[0] );
      jamp_sv[7] -= amp_sv[0];
      jamp_sv[25] += +amp_sv[0];
      jamp_sv[31] -= amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[91] -= amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[93] -= amp_sv[0];
      jamp_sv[94] += +amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      VVVV3_0( w_sv[8], w_sv[5], w_sv[6], w_sv[104], COUPs[2], &amp_sv[0] );
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[30] -= amp_sv[0];
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      jamp_sv[115] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];
      jamp_sv[117] -= amp_sv[0];
      jamp_sv[118] += +amp_sv[0];
      VVVV4_0( w_sv[8], w_sv[5], w_sv[6], w_sv[104], COUPs[2], &amp_sv[0] );
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[25] -= amp_sv[0];
      jamp_sv[30] -= amp_sv[0];
      jamp_sv[31] += +amp_sv[0];
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[49] -= amp_sv[0];
      jamp_sv[91] += +amp_sv[0];
      jamp_sv[92] -= amp_sv[0];
      jamp_sv[93] += +amp_sv[0];
      jamp_sv[94] -= amp_sv[0];
      jamp_sv[115] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];
      jamp_sv[117] -= amp_sv[0];
      jamp_sv[118] += +amp_sv[0];

      // *** DIAGRAM 437 OF 1240 ***

      // Wavefunction(s) for diagram number 437
      VVV1P0_1( w_sv[1], w_sv[8], COUPs[0], 0., 0., w_sv[108] );

      // Amplitude(s) for diagram number 437
      VVV1_0( w_sv[62], w_sv[108], w_sv[6], COUPs[0], &amp_sv[0] );
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[24] -= amp_sv[0];
      jamp_sv[30] += +amp_sv[0];
      jamp_sv[36] += +amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[42] += +amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[85] += +amp_sv[0];
      jamp_sv[99] -= amp_sv[0];
      jamp_sv[109] += +amp_sv[0];
      jamp_sv[115] += +amp_sv[0];
      jamp_sv[118] -= amp_sv[0];

      // *** DIAGRAM 438 OF 1240 ***

      // Wavefunction(s) for diagram number 438
      // (none)

      // Amplitude(s) for diagram number 438
      VVV1_0( w_sv[62], w_sv[1], w_sv[11], COUPs[0], &amp_sv[0] );
      jamp_sv[8] += +amp_sv[0];
      jamp_sv[24] -= amp_sv[0];
      jamp_sv[30] += +amp_sv[0];
      jamp_sv[36] += +amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[50] -= amp_sv[0];
      jamp_sv[74] -= amp_sv[0];
      jamp_sv[84] += +amp_sv[0];
      jamp_sv[99] -= amp_sv[0];
      jamp_sv[102] += +amp_sv[0];
      jamp_sv[104] -= amp_sv[0];
      jamp_sv[106] -= amp_sv[0];
      jamp_sv[107] += +amp_sv[0];
      jamp_sv[109] += +amp_sv[0];
      jamp_sv[115] += +amp_sv[0];
      jamp_sv[118] -= amp_sv[0];

      // *** DIAGRAM 439 OF 1240 ***

      // Wavefunction(s) for diagram number 439
      // (none)

      // Amplitude(s) for diagram number 439
      VVVV1_0( w_sv[1], w_sv[8], w_sv[6], w_sv[62], COUPs[2], &amp_sv[0] );
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[24] -= amp_sv[0];
      jamp_sv[30] += +amp_sv[0];
      jamp_sv[36] += +amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[42] += +amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[85] += +amp_sv[0];
      jamp_sv[99] -= amp_sv[0];
      jamp_sv[109] += +amp_sv[0];
      jamp_sv[115] += +amp_sv[0];
      jamp_sv[118] -= amp_sv[0];
      VVVV3_0( w_sv[1], w_sv[8], w_sv[6], w_sv[62], COUPs[2], &amp_sv[0] );
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[42] += +amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[85] += +amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      jamp_sv[107] -= amp_sv[0];
      VVVV4_0( w_sv[1], w_sv[8], w_sv[6], w_sv[62], COUPs[2], &amp_sv[0] );
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[30] -= amp_sv[0];
      jamp_sv[36] -= amp_sv[0];
      jamp_sv[38] += +amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[99] += +amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      jamp_sv[107] -= amp_sv[0];
      jamp_sv[109] -= amp_sv[0];
      jamp_sv[115] -= amp_sv[0];
      jamp_sv[118] += +amp_sv[0];

      // *** DIAGRAM 440 OF 1240 ***

      // Wavefunction(s) for diagram number 440
      // (none)

      // Amplitude(s) for diagram number 440
      VVV1_0( w_sv[86], w_sv[108], w_sv[5], COUPs[0], &amp_sv[0] );
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[25] -= amp_sv[0];
      jamp_sv[31] += +amp_sv[0];
      jamp_sv[36] += +amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[42] += +amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[85] += +amp_sv[0];
      jamp_sv[91] += +amp_sv[0];
      jamp_sv[94] -= amp_sv[0];
      jamp_sv[99] -= amp_sv[0];
      jamp_sv[109] += +amp_sv[0];

      // *** DIAGRAM 441 OF 1240 ***

      // Wavefunction(s) for diagram number 441
      // (none)

      // Amplitude(s) for diagram number 441
      VVV1_0( w_sv[86], w_sv[1], w_sv[10], COUPs[0], &amp_sv[0] );
      jamp_sv[10] += +amp_sv[0];
      jamp_sv[25] -= amp_sv[0];
      jamp_sv[31] += +amp_sv[0];
      jamp_sv[42] += +amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[52] -= amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[78] += +amp_sv[0];
      jamp_sv[80] -= amp_sv[0];
      jamp_sv[82] -= amp_sv[0];
      jamp_sv[83] += +amp_sv[0];
      jamp_sv[85] += +amp_sv[0];
      jamp_sv[91] += +amp_sv[0];
      jamp_sv[94] -= amp_sv[0];
      jamp_sv[98] -= amp_sv[0];
      jamp_sv[108] += +amp_sv[0];

      // *** DIAGRAM 442 OF 1240 ***

      // Wavefunction(s) for diagram number 442
      // (none)

      // Amplitude(s) for diagram number 442
      VVVV1_0( w_sv[1], w_sv[8], w_sv[5], w_sv[86], COUPs[2], &amp_sv[0] );
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[25] -= amp_sv[0];
      jamp_sv[31] += +amp_sv[0];
      jamp_sv[36] += +amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[42] += +amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[85] += +amp_sv[0];
      jamp_sv[91] += +amp_sv[0];
      jamp_sv[94] -= amp_sv[0];
      jamp_sv[99] -= amp_sv[0];
      jamp_sv[109] += +amp_sv[0];
      VVVV3_0( w_sv[1], w_sv[8], w_sv[5], w_sv[86], COUPs[2], &amp_sv[0] );
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[36] += +amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      jamp_sv[99] -= amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      jamp_sv[109] += +amp_sv[0];
      VVVV4_0( w_sv[1], w_sv[8], w_sv[5], w_sv[86], COUPs[2], &amp_sv[0] );
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[25] += +amp_sv[0];
      jamp_sv[31] -= amp_sv[0];
      jamp_sv[42] -= amp_sv[0];
      jamp_sv[44] += +amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[75] += +amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[85] -= amp_sv[0];
      jamp_sv[91] -= amp_sv[0];
      jamp_sv[94] += +amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      jamp_sv[108] -= amp_sv[0];

      // *** DIAGRAM 443 OF 1240 ***

      // Wavefunction(s) for diagram number 443
      VVVV1P0_1( w_sv[92], w_sv[1], w_sv[5], COUPs[2], 0., 0., w_sv[109] );
      VVVV3P0_1( w_sv[92], w_sv[1], w_sv[5], COUPs[2], 0., 0., w_sv[110] );
      VVVV4P0_1( w_sv[92], w_sv[1], w_sv[5], COUPs[2], 0., 0., w_sv[111] );

      // Amplitude(s) for diagram number 443
      VVV1_0( w_sv[8], w_sv[6], w_sv[109], COUPs[0], &amp_sv[0] );
      jamp_sv[6] += +amp_sv[0];
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[36] -= amp_sv[0];
      jamp_sv[38] += +amp_sv[0];
      jamp_sv[48] -= amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[78] += +amp_sv[0];
      jamp_sv[80] -= amp_sv[0];
      jamp_sv[98] -= amp_sv[0];
      jamp_sv[99] += +amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      jamp_sv[107] -= amp_sv[0];
      jamp_sv[108] += +amp_sv[0];
      jamp_sv[109] -= amp_sv[0];
      jamp_sv[116] -= amp_sv[0];
      jamp_sv[117] += +amp_sv[0];
      VVV1_0( w_sv[8], w_sv[6], w_sv[110], COUPs[0], &amp_sv[0] );
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[30] -= amp_sv[0];
      jamp_sv[36] -= amp_sv[0];
      jamp_sv[38] += +amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[99] += +amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      jamp_sv[107] -= amp_sv[0];
      jamp_sv[109] -= amp_sv[0];
      jamp_sv[115] -= amp_sv[0];
      jamp_sv[118] += +amp_sv[0];
      VVV1_0( w_sv[8], w_sv[6], w_sv[111], COUPs[0], &amp_sv[0] );
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[30] -= amp_sv[0];
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      jamp_sv[115] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];
      jamp_sv[117] -= amp_sv[0];
      jamp_sv[118] += +amp_sv[0];

      // *** DIAGRAM 444 OF 1240 ***

      // Wavefunction(s) for diagram number 444
      VVVV1P0_1( w_sv[92], w_sv[1], w_sv[6], COUPs[2], 0., 0., w_sv[112] );
      VVVV3P0_1( w_sv[92], w_sv[1], w_sv[6], COUPs[2], 0., 0., w_sv[113] );
      VVVV4P0_1( w_sv[92], w_sv[1], w_sv[6], COUPs[2], 0., 0., w_sv[114] );

      // Amplitude(s) for diagram number 444
      VVV1_0( w_sv[8], w_sv[5], w_sv[112], COUPs[0], &amp_sv[0] );
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[42] -= amp_sv[0];
      jamp_sv[44] += +amp_sv[0];
      jamp_sv[49] -= amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[74] -= amp_sv[0];
      jamp_sv[75] += +amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[84] += +amp_sv[0];
      jamp_sv[85] -= amp_sv[0];
      jamp_sv[92] -= amp_sv[0];
      jamp_sv[93] += +amp_sv[0];
      jamp_sv[102] += +amp_sv[0];
      jamp_sv[104] -= amp_sv[0];
      VVV1_0( w_sv[8], w_sv[5], w_sv[113], COUPs[0], &amp_sv[0] );
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[25] += +amp_sv[0];
      jamp_sv[31] -= amp_sv[0];
      jamp_sv[42] -= amp_sv[0];
      jamp_sv[44] += +amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[75] += +amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[85] -= amp_sv[0];
      jamp_sv[91] -= amp_sv[0];
      jamp_sv[94] += +amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      VVV1_0( w_sv[8], w_sv[5], w_sv[114], COUPs[0], &amp_sv[0] );
      jamp_sv[7] -= amp_sv[0];
      jamp_sv[25] += +amp_sv[0];
      jamp_sv[31] -= amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[91] -= amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[93] -= amp_sv[0];
      jamp_sv[94] += +amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[108] -= amp_sv[0];

      // *** DIAGRAM 445 OF 1240 ***

      // Wavefunction(s) for diagram number 445
      // (none)

      // Amplitude(s) for diagram number 445
      VVV1_0( w_sv[1], w_sv[8], w_sv[88], COUPs[0], &amp_sv[0] );
      jamp_sv[9] -= amp_sv[0];
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[25] -= amp_sv[0];
      jamp_sv[30] -= amp_sv[0];
      jamp_sv[31] += +amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[46] += +amp_sv[0];
      jamp_sv[47] -= amp_sv[0];
      jamp_sv[51] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[91] += +amp_sv[0];
      jamp_sv[94] -= amp_sv[0];
      jamp_sv[115] -= amp_sv[0];
      jamp_sv[118] += +amp_sv[0];
      VVV1_0( w_sv[1], w_sv[8], w_sv[90], COUPs[0], &amp_sv[0] );
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[25] -= amp_sv[0];
      jamp_sv[31] += +amp_sv[0];
      jamp_sv[36] += +amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[42] += +amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[85] += +amp_sv[0];
      jamp_sv[91] += +amp_sv[0];
      jamp_sv[94] -= amp_sv[0];
      jamp_sv[99] -= amp_sv[0];
      jamp_sv[109] += +amp_sv[0];
      VVV1_0( w_sv[1], w_sv[8], w_sv[96], COUPs[0], &amp_sv[0] );
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[24] -= amp_sv[0];
      jamp_sv[30] += +amp_sv[0];
      jamp_sv[36] += +amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[42] += +amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[85] += +amp_sv[0];
      jamp_sv[99] -= amp_sv[0];
      jamp_sv[109] += +amp_sv[0];
      jamp_sv[115] += +amp_sv[0];
      jamp_sv[118] -= amp_sv[0];

      // *** DIAGRAM 446 OF 1240 ***

      // Wavefunction(s) for diagram number 446
      // (none)

      // Amplitude(s) for diagram number 446
      VVVV1_0( w_sv[92], w_sv[1], w_sv[8], w_sv[29], COUPs[2], &amp_sv[0] );
      jamp_sv[6] += +amp_sv[0];
      jamp_sv[7] -= amp_sv[0];
      jamp_sv[24] -= amp_sv[0];
      jamp_sv[25] += +amp_sv[0];
      jamp_sv[30] += +amp_sv[0];
      jamp_sv[31] -= amp_sv[0];
      jamp_sv[48] -= amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[91] -= amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[93] -= amp_sv[0];
      jamp_sv[94] += +amp_sv[0];
      jamp_sv[115] += +amp_sv[0];
      jamp_sv[116] -= amp_sv[0];
      jamp_sv[117] += +amp_sv[0];
      jamp_sv[118] -= amp_sv[0];
      VVVV3_0( w_sv[92], w_sv[1], w_sv[8], w_sv[29], COUPs[2], &amp_sv[0] );
      jamp_sv[6] += +amp_sv[0];
      jamp_sv[7] -= amp_sv[0];
      jamp_sv[9] -= amp_sv[0];
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[46] += +amp_sv[0];
      jamp_sv[47] -= amp_sv[0];
      jamp_sv[48] -= amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[51] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[93] -= amp_sv[0];
      jamp_sv[116] -= amp_sv[0];
      jamp_sv[117] += +amp_sv[0];
      VVVV4_0( w_sv[92], w_sv[1], w_sv[8], w_sv[29], COUPs[2], &amp_sv[0] );
      jamp_sv[9] -= amp_sv[0];
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[25] -= amp_sv[0];
      jamp_sv[30] -= amp_sv[0];
      jamp_sv[31] += +amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[46] += +amp_sv[0];
      jamp_sv[47] -= amp_sv[0];
      jamp_sv[51] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[91] += +amp_sv[0];
      jamp_sv[94] -= amp_sv[0];
      jamp_sv[115] -= amp_sv[0];
      jamp_sv[118] += +amp_sv[0];

      // *** DIAGRAM 447 OF 1240 ***

      // Wavefunction(s) for diagram number 447
      // (none)

      // Amplitude(s) for diagram number 447
      VVV1_0( w_sv[8], w_sv[29], w_sv[104], COUPs[0], &amp_sv[0] );
      jamp_sv[6] += +amp_sv[0];
      jamp_sv[7] -= amp_sv[0];
      jamp_sv[24] -= amp_sv[0];
      jamp_sv[25] += +amp_sv[0];
      jamp_sv[30] += +amp_sv[0];
      jamp_sv[31] -= amp_sv[0];
      jamp_sv[48] -= amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[91] -= amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[93] -= amp_sv[0];
      jamp_sv[94] += +amp_sv[0];
      jamp_sv[115] += +amp_sv[0];
      jamp_sv[116] -= amp_sv[0];
      jamp_sv[117] += +amp_sv[0];
      jamp_sv[118] -= amp_sv[0];

      // *** DIAGRAM 448 OF 1240 ***

      // Wavefunction(s) for diagram number 448
      // (none)

      // Amplitude(s) for diagram number 448
      VVV1_0( w_sv[1], w_sv[29], w_sv[107], COUPs[0], &amp_sv[0] );
      jamp_sv[6] += +amp_sv[0];
      jamp_sv[7] -= amp_sv[0];
      jamp_sv[9] -= amp_sv[0];
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[46] += +amp_sv[0];
      jamp_sv[47] -= amp_sv[0];
      jamp_sv[48] -= amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[51] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[93] -= amp_sv[0];
      jamp_sv[116] -= amp_sv[0];
      jamp_sv[117] += +amp_sv[0];

      // *** DIAGRAM 449 OF 1240 ***

      // Wavefunction(s) for diagram number 449
      // (none)

      // Amplitude(s) for diagram number 449
      VVV1_0( w_sv[1], w_sv[8], w_sv[95], COUPs[0], &amp_sv[0] );
      jamp_sv[9] -= amp_sv[0];
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[25] -= amp_sv[0];
      jamp_sv[30] -= amp_sv[0];
      jamp_sv[31] += +amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[46] += +amp_sv[0];
      jamp_sv[47] -= amp_sv[0];
      jamp_sv[51] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[91] += +amp_sv[0];
      jamp_sv[94] -= amp_sv[0];
      jamp_sv[115] -= amp_sv[0];
      jamp_sv[118] += +amp_sv[0];

      // *** DIAGRAM 450 OF 1240 ***

      // Wavefunction(s) for diagram number 450
      // (none)

      // Amplitude(s) for diagram number 450
      VVV1_0( w_sv[104], w_sv[45], w_sv[6], COUPs[0], &amp_sv[0] );
      jamp_sv[74] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[78] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[80] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[84] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[91] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[92] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[93] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[94] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 451 OF 1240 ***

      // Wavefunction(s) for diagram number 451
      // (none)

      // Amplitude(s) for diagram number 451
      FFV1_0( w_sv[3], w_sv[44], w_sv[104], COUPs[1], &amp_sv[0] );
      jamp_sv[91] += +amp_sv[0];
      jamp_sv[92] -= amp_sv[0];
      jamp_sv[93] += +amp_sv[0];
      jamp_sv[94] -= amp_sv[0];

      // *** DIAGRAM 452 OF 1240 ***

      // Wavefunction(s) for diagram number 452
      // (none)

      // Amplitude(s) for diagram number 452
      FFV1_0( w_sv[99], w_sv[89], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[82] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[83] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 453 OF 1240 ***

      // Wavefunction(s) for diagram number 453
      // (none)

      // Amplitude(s) for diagram number 453
      FFV1_0( w_sv[99], w_sv[44], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[92] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[93] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 454 OF 1240 ***

      // Wavefunction(s) for diagram number 454
      // (none)

      // Amplitude(s) for diagram number 454
      FFV1_0( w_sv[3], w_sv[89], w_sv[86], COUPs[1], &amp_sv[0] );
      jamp_sv[78] += +amp_sv[0];
      jamp_sv[80] -= amp_sv[0];
      jamp_sv[82] -= amp_sv[0];
      jamp_sv[83] += +amp_sv[0];

      // *** DIAGRAM 455 OF 1240 ***

      // Wavefunction(s) for diagram number 455
      // (none)

      // Amplitude(s) for diagram number 455
      VVV1_0( w_sv[86], w_sv[1], w_sv[45], COUPs[0], &amp_sv[0] );
      jamp_sv[75] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[78] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[80] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[82] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[83] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[85] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[91] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[94] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 456 OF 1240 ***

      // Wavefunction(s) for diagram number 456
      // (none)

      // Amplitude(s) for diagram number 456
      FFV1_0( w_sv[3], w_sv[39], w_sv[112], COUPs[1], &amp_sv[0] );
      jamp_sv[74] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[75] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[82] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[83] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[84] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[85] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[92] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[93] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[39], w_sv[113], COUPs[1], &amp_sv[0] );
      jamp_sv[75] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[78] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[80] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[82] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[83] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[85] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[91] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[94] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[39], w_sv[114], COUPs[1], &amp_sv[0] );
      jamp_sv[74] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[78] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[80] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[84] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[91] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[92] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[93] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[94] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 457 OF 1240 ***

      // Wavefunction(s) for diagram number 457
      // (none)

      // Amplitude(s) for diagram number 457
      FFV1_0( w_sv[41], w_sv[39], w_sv[104], COUPs[1], &amp_sv[0] );
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[84] -= amp_sv[0];

      // *** DIAGRAM 458 OF 1240 ***

      // Wavefunction(s) for diagram number 458
      // (none)

      // Amplitude(s) for diagram number 458
      FFV1_0( w_sv[41], w_sv[105], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[74] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[84] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 459 OF 1240 ***

      // Wavefunction(s) for diagram number 459
      // (none)

      // Amplitude(s) for diagram number 459
      FFV1_0( w_sv[101], w_sv[39], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[78] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[80] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 460 OF 1240 ***

      // Wavefunction(s) for diagram number 460
      // (none)

      // Amplitude(s) for diagram number 460
      VVV1_0( w_sv[104], w_sv[51], w_sv[5], COUPs[0], &amp_sv[0] );
      jamp_sv[98] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[102] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[104] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[108] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[115] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[116] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[117] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[118] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 461 OF 1240 ***

      // Wavefunction(s) for diagram number 461
      // (none)

      // Amplitude(s) for diagram number 461
      FFV1_0( w_sv[3], w_sv[50], w_sv[104], COUPs[1], &amp_sv[0] );
      jamp_sv[115] += +amp_sv[0];
      jamp_sv[116] -= amp_sv[0];
      jamp_sv[117] += +amp_sv[0];
      jamp_sv[118] -= amp_sv[0];

      // *** DIAGRAM 462 OF 1240 ***

      // Wavefunction(s) for diagram number 462
      // (none)

      // Amplitude(s) for diagram number 462
      FFV1_0( w_sv[99], w_sv[91], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[106] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[107] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 463 OF 1240 ***

      // Wavefunction(s) for diagram number 463
      // (none)

      // Amplitude(s) for diagram number 463
      FFV1_0( w_sv[99], w_sv[50], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[116] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[117] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 464 OF 1240 ***

      // Wavefunction(s) for diagram number 464
      // (none)

      // Amplitude(s) for diagram number 464
      FFV1_0( w_sv[3], w_sv[91], w_sv[62], COUPs[1], &amp_sv[0] );
      jamp_sv[102] += +amp_sv[0];
      jamp_sv[104] -= amp_sv[0];
      jamp_sv[106] -= amp_sv[0];
      jamp_sv[107] += +amp_sv[0];

      // *** DIAGRAM 465 OF 1240 ***

      // Wavefunction(s) for diagram number 465
      // (none)

      // Amplitude(s) for diagram number 465
      VVV1_0( w_sv[62], w_sv[1], w_sv[51], COUPs[0], &amp_sv[0] );
      jamp_sv[99] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[102] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[104] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[106] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[107] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[109] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[115] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[118] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 466 OF 1240 ***

      // Wavefunction(s) for diagram number 466
      // (none)

      // Amplitude(s) for diagram number 466
      FFV1_0( w_sv[3], w_sv[47], w_sv[109], COUPs[1], &amp_sv[0] );
      jamp_sv[98] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[99] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[106] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[107] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[108] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[109] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[116] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[117] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[47], w_sv[110], COUPs[1], &amp_sv[0] );
      jamp_sv[99] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[102] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[104] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[106] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[107] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[109] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[115] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[118] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[47], w_sv[111], COUPs[1], &amp_sv[0] );
      jamp_sv[98] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[102] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[104] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[108] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[115] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[116] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[117] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[118] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 467 OF 1240 ***

      // Wavefunction(s) for diagram number 467
      // (none)

      // Amplitude(s) for diagram number 467
      FFV1_0( w_sv[38], w_sv[47], w_sv[104], COUPs[1], &amp_sv[0] );
      jamp_sv[98] += +amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[108] -= amp_sv[0];

      // *** DIAGRAM 468 OF 1240 ***

      // Wavefunction(s) for diagram number 468
      // (none)

      // Amplitude(s) for diagram number 468
      FFV1_0( w_sv[38], w_sv[106], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[98] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[108] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 469 OF 1240 ***

      // Wavefunction(s) for diagram number 469
      // (none)

      // Amplitude(s) for diagram number 469
      FFV1_0( w_sv[98], w_sv[47], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[102] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[104] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 470 OF 1240 ***

      // Wavefunction(s) for diagram number 470
      // (none)

      // Amplitude(s) for diagram number 470
      VVV1_0( w_sv[104], w_sv[23], w_sv[6], COUPs[0], &amp_sv[0] );
      jamp_sv[7] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[25] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[31] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[49] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[98] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[102] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[104] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[108] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 471 OF 1240 ***

      // Wavefunction(s) for diagram number 471
      // (none)

      // Amplitude(s) for diagram number 471
      FFV1_0( w_sv[48], w_sv[2], w_sv[104], COUPs[1], &amp_sv[0] );
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[25] -= amp_sv[0];
      jamp_sv[31] += +amp_sv[0];
      jamp_sv[49] -= amp_sv[0];

      // *** DIAGRAM 472 OF 1240 ***

      // Wavefunction(s) for diagram number 472
      // (none)

      // Amplitude(s) for diagram number 472
      FFV1_0( w_sv[58], w_sv[102], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[10] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[52] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 473 OF 1240 ***

      // Wavefunction(s) for diagram number 473
      // (none)

      // Amplitude(s) for diagram number 473
      FFV1_0( w_sv[48], w_sv[102], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[7] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[49] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 474 OF 1240 ***

      // Wavefunction(s) for diagram number 474
      // (none)

      // Amplitude(s) for diagram number 474
      FFV1_0( w_sv[58], w_sv[2], w_sv[86], COUPs[1], &amp_sv[0] );
      jamp_sv[10] += +amp_sv[0];
      jamp_sv[52] -= amp_sv[0];
      jamp_sv[98] -= amp_sv[0];
      jamp_sv[108] += +amp_sv[0];

      // *** DIAGRAM 475 OF 1240 ***

      // Wavefunction(s) for diagram number 475
      // (none)

      // Amplitude(s) for diagram number 475
      VVV1_0( w_sv[86], w_sv[1], w_sv[23], COUPs[0], &amp_sv[0] );
      jamp_sv[10] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[25] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[31] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[42] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[44] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[52] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[98] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[108] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 476 OF 1240 ***

      // Wavefunction(s) for diagram number 476
      // (none)

      // Amplitude(s) for diagram number 476
      FFV1_0( w_sv[38], w_sv[2], w_sv[112], COUPs[1], &amp_sv[0] );
      jamp_sv[7] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[10] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[42] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[44] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[49] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[52] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[102] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[104] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[38], w_sv[2], w_sv[113], COUPs[1], &amp_sv[0] );
      jamp_sv[10] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[25] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[31] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[42] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[44] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[52] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[98] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[108] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[38], w_sv[2], w_sv[114], COUPs[1], &amp_sv[0] );
      jamp_sv[7] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[25] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[31] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[49] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[98] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[102] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[104] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[108] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 477 OF 1240 ***

      // Wavefunction(s) for diagram number 477
      // (none)

      // Amplitude(s) for diagram number 477
      VVV1_0( w_sv[104], w_sv[20], w_sv[5], COUPs[0], &amp_sv[0] );
      jamp_sv[6] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[24] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[30] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[48] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[74] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[78] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[80] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[84] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 478 OF 1240 ***

      // Wavefunction(s) for diagram number 478
      // (none)

      // Amplitude(s) for diagram number 478
      FFV1_0( w_sv[40], w_sv[2], w_sv[104], COUPs[1], &amp_sv[0] );
      jamp_sv[6] += +amp_sv[0];
      jamp_sv[24] -= amp_sv[0];
      jamp_sv[30] += +amp_sv[0];
      jamp_sv[48] -= amp_sv[0];

      // *** DIAGRAM 479 OF 1240 ***

      // Wavefunction(s) for diagram number 479
      // (none)

      // Amplitude(s) for diagram number 479
      FFV1_0( w_sv[60], w_sv[102], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[8] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[50] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 480 OF 1240 ***

      // Wavefunction(s) for diagram number 480
      // (none)

      // Amplitude(s) for diagram number 480
      FFV1_0( w_sv[40], w_sv[102], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[6] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[48] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 481 OF 1240 ***

      // Wavefunction(s) for diagram number 481
      // (none)

      // Amplitude(s) for diagram number 481
      FFV1_0( w_sv[60], w_sv[2], w_sv[62], COUPs[1], &amp_sv[0] );
      jamp_sv[8] += +amp_sv[0];
      jamp_sv[50] -= amp_sv[0];
      jamp_sv[74] -= amp_sv[0];
      jamp_sv[84] += +amp_sv[0];

      // *** DIAGRAM 482 OF 1240 ***

      // Wavefunction(s) for diagram number 482
      // (none)

      // Amplitude(s) for diagram number 482
      VVV1_0( w_sv[62], w_sv[1], w_sv[20], COUPs[0], &amp_sv[0] );
      jamp_sv[8] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[24] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[30] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[36] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[38] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[50] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[74] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[84] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 483 OF 1240 ***

      // Wavefunction(s) for diagram number 483
      // (none)

      // Amplitude(s) for diagram number 483
      FFV1_0( w_sv[41], w_sv[2], w_sv[109], COUPs[1], &amp_sv[0] );
      jamp_sv[6] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[8] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[36] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[38] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[48] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[50] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[78] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[80] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[41], w_sv[2], w_sv[110], COUPs[1], &amp_sv[0] );
      jamp_sv[8] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[24] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[30] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[36] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[38] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[50] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[74] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[84] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[41], w_sv[2], w_sv[111], COUPs[1], &amp_sv[0] );
      jamp_sv[6] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[24] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[30] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[48] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[74] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[78] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[80] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[84] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 484 OF 1240 ***

      // Wavefunction(s) for diagram number 484
      // (none)

      // Amplitude(s) for diagram number 484
      FFV1_0( w_sv[3], w_sv[18], w_sv[104], COUPs[1], &amp_sv[0] );
      jamp_sv[91] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[92] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[93] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[94] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[115] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[116] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[117] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[118] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 485 OF 1240 ***

      // Wavefunction(s) for diagram number 485
      // (none)

      // Amplitude(s) for diagram number 485
      FFV1_0( w_sv[12], w_sv[2], w_sv[104], COUPs[1], &amp_sv[0] );
      jamp_sv[6] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[7] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[24] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[25] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[30] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[31] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[48] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[49] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 486 OF 1240 ***

      // Wavefunction(s) for diagram number 486
      // (none)

      // Amplitude(s) for diagram number 486
      FFV1_0( w_sv[3], w_sv[102], w_sv[67], COUPs[1], &amp_sv[0] );
      jamp_sv[6] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[7] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[9] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[11] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[48] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[49] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[51] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[53] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 487 OF 1240 ***

      // Wavefunction(s) for diagram number 487
      // (none)

      // Amplitude(s) for diagram number 487
      FFV1_0( w_sv[12], w_sv[102], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[6] += +amp_sv[0];
      jamp_sv[7] -= amp_sv[0];
      jamp_sv[48] -= amp_sv[0];
      jamp_sv[49] += +amp_sv[0];

      // *** DIAGRAM 488 OF 1240 ***

      // Wavefunction(s) for diagram number 488
      // (none)

      // Amplitude(s) for diagram number 488
      FFV1_0( w_sv[99], w_sv[2], w_sv[67], COUPs[1], &amp_sv[0] );
      jamp_sv[40] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[41] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[46] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[47] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[92] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[93] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[116] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[117] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 489 OF 1240 ***

      // Wavefunction(s) for diagram number 489
      // (none)

      // Amplitude(s) for diagram number 489
      FFV1_0( w_sv[99], w_sv[18], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[93] -= amp_sv[0];
      jamp_sv[116] -= amp_sv[0];
      jamp_sv[117] += +amp_sv[0];

      // *** DIAGRAM 490 OF 1240 ***

      // Wavefunction(s) for diagram number 490
      // (none)

      // Amplitude(s) for diagram number 490
      FFV1_0( w_sv[3], w_sv[102], w_sv[55], COUPs[1], &amp_sv[0] );
      jamp_sv[6] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[7] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[9] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[11] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[48] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[49] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[51] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[53] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[102], w_sv[83], COUPs[1], &amp_sv[0] );
      jamp_sv[7] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[8] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[9] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[10] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[49] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[50] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[51] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[52] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[102], w_sv[84], COUPs[1], &amp_sv[0] );
      jamp_sv[6] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[8] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[10] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[11] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[48] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[50] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[52] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[53] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 491 OF 1240 ***

      // Wavefunction(s) for diagram number 491
      // (none)

      // Amplitude(s) for diagram number 491
      FFV1_0( w_sv[99], w_sv[2], w_sv[55], COUPs[1], &amp_sv[0] );
      jamp_sv[40] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[41] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[46] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[47] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[92] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[93] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[116] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[117] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[99], w_sv[2], w_sv[83], COUPs[1], &amp_sv[0] );
      jamp_sv[46] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[47] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[82] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[83] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[92] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[93] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[106] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[107] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[99], w_sv[2], w_sv[84], COUPs[1], &amp_sv[0] );
      jamp_sv[40] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[41] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[82] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[83] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[106] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[107] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[116] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[117] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 492 OF 1240 ***

      // Wavefunction(s) for diagram number 492
      // (none)

      // Amplitude(s) for diagram number 492
      VVV1_0( w_sv[92], w_sv[55], w_sv[8], COUPs[0], &amp_sv[0] );
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[11] -= amp_sv[0];
      jamp_sv[40] += +amp_sv[0];
      jamp_sv[41] -= amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[49] -= amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[53] += +amp_sv[0];
      jamp_sv[92] -= amp_sv[0];
      jamp_sv[93] += +amp_sv[0];
      jamp_sv[116] += +amp_sv[0];
      jamp_sv[117] -= amp_sv[0];
      VVV1_0( w_sv[92], w_sv[83], w_sv[8], COUPs[0], &amp_sv[0] );
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[49] -= amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[92] -= amp_sv[0];
      jamp_sv[93] += +amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      jamp_sv[107] -= amp_sv[0];
      VVV1_0( w_sv[92], w_sv[84], w_sv[8], COUPs[0], &amp_sv[0] );
      jamp_sv[6] += +amp_sv[0];
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[48] -= amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      jamp_sv[107] -= amp_sv[0];
      jamp_sv[116] -= amp_sv[0];
      jamp_sv[117] += +amp_sv[0];

      // *** DIAGRAM 493 OF 1240 ***

      // Wavefunction(s) for diagram number 493
      VVV1P0_1( w_sv[0], w_sv[5], COUPs[0], 0., 0., w_sv[92] );
      FFV1_2( w_sv[3], w_sv[92], COUPs[1], cIPD[0], cIPD[1], w_sv[99] );

      // Amplitude(s) for diagram number 493
      FFV1_0( w_sv[99], w_sv[87], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[34] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[35] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 494 OF 1240 ***

      // Wavefunction(s) for diagram number 494
      // (none)

      // Amplitude(s) for diagram number 494
      FFV1_0( w_sv[99], w_sv[85], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[44] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[45] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 495 OF 1240 ***

      // Wavefunction(s) for diagram number 495
      VVV1P0_1( w_sv[92], w_sv[4], COUPs[0], 0., 0., w_sv[102] );

      // Amplitude(s) for diagram number 495
      VVV1_0( w_sv[102], w_sv[34], w_sv[6], COUPs[0], &amp_sv[0] );
      jamp_sv[26] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[30] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[32] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[36] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[43] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[44] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[45] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[46] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 496 OF 1240 ***

      // Wavefunction(s) for diagram number 496
      // (none)

      // Amplitude(s) for diagram number 496
      FFV1_0( w_sv[3], w_sv[85], w_sv[102], COUPs[1], &amp_sv[0] );
      jamp_sv[43] += +amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[45] += +amp_sv[0];
      jamp_sv[46] -= amp_sv[0];

      // *** DIAGRAM 497 OF 1240 ***

      // Wavefunction(s) for diagram number 497
      VVV1P0_1( w_sv[92], w_sv[6], COUPs[0], 0., 0., w_sv[104] );

      // Amplitude(s) for diagram number 497
      VVV1_0( w_sv[104], w_sv[34], w_sv[4], COUPs[0], &amp_sv[0] );
      jamp_sv[27] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[30] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[32] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[34] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[35] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[37] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[43] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[46] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 498 OF 1240 ***

      // Wavefunction(s) for diagram number 498
      // (none)

      // Amplitude(s) for diagram number 498
      FFV1_0( w_sv[3], w_sv[87], w_sv[104], COUPs[1], &amp_sv[0] );
      jamp_sv[30] += +amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[35] += +amp_sv[0];

      // *** DIAGRAM 499 OF 1240 ***

      // Wavefunction(s) for diagram number 499
      VVVV1P0_1( w_sv[92], w_sv[4], w_sv[6], COUPs[2], 0., 0., w_sv[111] );
      VVVV3P0_1( w_sv[92], w_sv[4], w_sv[6], COUPs[2], 0., 0., w_sv[110] );
      VVVV4P0_1( w_sv[92], w_sv[4], w_sv[6], COUPs[2], 0., 0., w_sv[109] );

      // Amplitude(s) for diagram number 499
      FFV1_0( w_sv[3], w_sv[77], w_sv[111], COUPs[1], &amp_sv[0] );
      jamp_sv[26] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[27] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[34] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[35] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[36] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[37] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[44] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[45] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[77], w_sv[110], COUPs[1], &amp_sv[0] );
      jamp_sv[27] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[30] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[32] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[34] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[35] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[37] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[43] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[46] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[77], w_sv[109], COUPs[1], &amp_sv[0] );
      jamp_sv[26] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[30] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[32] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[36] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[43] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[44] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[45] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[46] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 500 OF 1240 ***

      // Wavefunction(s) for diagram number 500
      FFV1_1( w_sv[77], w_sv[92], COUPs[1], cIPD[0], cIPD[1], w_sv[62] );

      // Amplitude(s) for diagram number 500
      FFV1_0( w_sv[46], w_sv[62], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[27] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[37] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 501 OF 1240 ***

      // Wavefunction(s) for diagram number 501
      FFV1_2( w_sv[46], w_sv[92], COUPs[1], cIPD[0], cIPD[1], w_sv[114] );

      // Amplitude(s) for diagram number 501
      FFV1_0( w_sv[114], w_sv[77], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[43] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[46] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 502 OF 1240 ***

      // Wavefunction(s) for diagram number 502
      // (none)

      // Amplitude(s) for diagram number 502
      FFV1_0( w_sv[46], w_sv[77], w_sv[104], COUPs[1], &amp_sv[0] );
      jamp_sv[27] += +amp_sv[0];
      jamp_sv[37] -= amp_sv[0];
      jamp_sv[43] -= amp_sv[0];
      jamp_sv[46] += +amp_sv[0];

      // *** DIAGRAM 503 OF 1240 ***

      // Wavefunction(s) for diagram number 503
      // (none)

      // Amplitude(s) for diagram number 503
      FFV1_0( w_sv[41], w_sv[62], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[26] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[36] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 504 OF 1240 ***

      // Wavefunction(s) for diagram number 504
      FFV1_2( w_sv[41], w_sv[92], COUPs[1], cIPD[0], cIPD[1], w_sv[113] );

      // Amplitude(s) for diagram number 504
      FFV1_0( w_sv[113], w_sv[77], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[30] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[32] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 505 OF 1240 ***

      // Wavefunction(s) for diagram number 505
      // (none)

      // Amplitude(s) for diagram number 505
      FFV1_0( w_sv[41], w_sv[77], w_sv[102], COUPs[1], &amp_sv[0] );
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[30] -= amp_sv[0];
      jamp_sv[32] += +amp_sv[0];
      jamp_sv[36] -= amp_sv[0];

      // *** DIAGRAM 506 OF 1240 ***

      // Wavefunction(s) for diagram number 506
      // (none)

      // Amplitude(s) for diagram number 506
      FFV1_0( w_sv[3], w_sv[62], w_sv[27], COUPs[1], &amp_sv[0] );
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[27] -= amp_sv[0];
      jamp_sv[36] -= amp_sv[0];
      jamp_sv[37] += +amp_sv[0];

      // *** DIAGRAM 507 OF 1240 ***

      // Wavefunction(s) for diagram number 507
      // (none)

      // Amplitude(s) for diagram number 507
      FFV1_0( w_sv[99], w_sv[77], w_sv[27], COUPs[1], &amp_sv[0] );
      jamp_sv[34] += +amp_sv[0];
      jamp_sv[35] -= amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[45] += +amp_sv[0];

      // *** DIAGRAM 508 OF 1240 ***

      // Wavefunction(s) for diagram number 508
      VVV1P0_1( w_sv[92], w_sv[27], COUPs[0], 0., 0., w_sv[62] );

      // Amplitude(s) for diagram number 508
      FFV1_0( w_sv[3], w_sv[77], w_sv[62], COUPs[1], &amp_sv[0] );
      jamp_sv[26] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[27] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[34] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[35] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[36] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[37] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[44] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[45] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 509 OF 1240 ***

      // Wavefunction(s) for diagram number 509
      FFV1_1( w_sv[2], w_sv[92], COUPs[1], cIPD[0], cIPD[1], w_sv[112] );

      // Amplitude(s) for diagram number 509
      FFV1_0( w_sv[56], w_sv[112], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[17] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[77] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 510 OF 1240 ***

      // Wavefunction(s) for diagram number 510
      // (none)

      // Amplitude(s) for diagram number 510
      FFV1_0( w_sv[21], w_sv[112], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[15] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[75] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 511 OF 1240 ***

      // Wavefunction(s) for diagram number 511
      // (none)

      // Amplitude(s) for diagram number 511
      VVV1_0( w_sv[102], w_sv[103], w_sv[6], COUPs[0], &amp_sv[0] );
      jamp_sv[15] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[51] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[61] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[75] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[101] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[109] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[112] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[115] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 512 OF 1240 ***

      // Wavefunction(s) for diagram number 512
      // (none)

      // Amplitude(s) for diagram number 512
      FFV1_0( w_sv[21], w_sv[2], w_sv[102], COUPs[1], &amp_sv[0] );
      jamp_sv[15] += +amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[61] += +amp_sv[0];
      jamp_sv[75] -= amp_sv[0];

      // *** DIAGRAM 513 OF 1240 ***

      // Wavefunction(s) for diagram number 513
      // (none)

      // Amplitude(s) for diagram number 513
      VVV1_0( w_sv[104], w_sv[103], w_sv[4], COUPs[0], &amp_sv[0] );
      jamp_sv[17] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[51] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[61] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[67] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[70] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[77] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[101] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[115] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 514 OF 1240 ***

      // Wavefunction(s) for diagram number 514
      // (none)

      // Amplitude(s) for diagram number 514
      FFV1_0( w_sv[56], w_sv[2], w_sv[104], COUPs[1], &amp_sv[0] );
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[101] -= amp_sv[0];
      jamp_sv[115] += +amp_sv[0];

      // *** DIAGRAM 515 OF 1240 ***

      // Wavefunction(s) for diagram number 515
      // (none)

      // Amplitude(s) for diagram number 515
      FFV1_0( w_sv[52], w_sv[2], w_sv[111], COUPs[1], &amp_sv[0] );
      jamp_sv[15] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[17] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[67] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[70] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[75] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[77] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[109] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[112] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[52], w_sv[2], w_sv[110], COUPs[1], &amp_sv[0] );
      jamp_sv[17] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[51] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[61] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[67] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[70] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[77] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[101] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[115] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[52], w_sv[2], w_sv[109], COUPs[1], &amp_sv[0] );
      jamp_sv[15] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[51] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[61] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[75] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[101] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[109] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[112] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[115] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 516 OF 1240 ***

      // Wavefunction(s) for diagram number 516
      FFV1_2( w_sv[52], w_sv[92], COUPs[1], cIPD[0], cIPD[1], w_sv[86] );

      // Amplitude(s) for diagram number 516
      FFV1_0( w_sv[86], w_sv[33], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[67] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[70] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 517 OF 1240 ***

      // Wavefunction(s) for diagram number 517
      FFV1_1( w_sv[33], w_sv[92], COUPs[1], cIPD[0], cIPD[1], w_sv[98] );

      // Amplitude(s) for diagram number 517
      FFV1_0( w_sv[52], w_sv[98], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[51] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[61] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 518 OF 1240 ***

      // Wavefunction(s) for diagram number 518
      // (none)

      // Amplitude(s) for diagram number 518
      FFV1_0( w_sv[52], w_sv[33], w_sv[104], COUPs[1], &amp_sv[0] );
      jamp_sv[51] += +amp_sv[0];
      jamp_sv[61] -= amp_sv[0];
      jamp_sv[67] -= amp_sv[0];
      jamp_sv[70] += +amp_sv[0];

      // *** DIAGRAM 519 OF 1240 ***

      // Wavefunction(s) for diagram number 519
      // (none)

      // Amplitude(s) for diagram number 519
      FFV1_0( w_sv[86], w_sv[47], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[109] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[112] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 520 OF 1240 ***

      // Wavefunction(s) for diagram number 520
      FFV1_1( w_sv[47], w_sv[92], COUPs[1], cIPD[0], cIPD[1], w_sv[106] );

      // Amplitude(s) for diagram number 520
      FFV1_0( w_sv[52], w_sv[106], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[101] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[115] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 521 OF 1240 ***

      // Wavefunction(s) for diagram number 521
      // (none)

      // Amplitude(s) for diagram number 521
      FFV1_0( w_sv[52], w_sv[47], w_sv[102], COUPs[1], &amp_sv[0] );
      jamp_sv[101] += +amp_sv[0];
      jamp_sv[109] -= amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      jamp_sv[115] -= amp_sv[0];

      // *** DIAGRAM 522 OF 1240 ***

      // Wavefunction(s) for diagram number 522
      // (none)

      // Amplitude(s) for diagram number 522
      FFV1_0( w_sv[86], w_sv[2], w_sv[27], COUPs[1], &amp_sv[0] );
      jamp_sv[67] += +amp_sv[0];
      jamp_sv[70] -= amp_sv[0];
      jamp_sv[109] -= amp_sv[0];
      jamp_sv[112] += +amp_sv[0];

      // *** DIAGRAM 523 OF 1240 ***

      // Wavefunction(s) for diagram number 523
      // (none)

      // Amplitude(s) for diagram number 523
      FFV1_0( w_sv[52], w_sv[112], w_sv[27], COUPs[1], &amp_sv[0] );
      jamp_sv[15] += +amp_sv[0];
      jamp_sv[17] -= amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[77] += +amp_sv[0];

      // *** DIAGRAM 524 OF 1240 ***

      // Wavefunction(s) for diagram number 524
      // (none)

      // Amplitude(s) for diagram number 524
      FFV1_0( w_sv[52], w_sv[2], w_sv[62], COUPs[1], &amp_sv[0] );
      jamp_sv[15] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[17] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[67] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[70] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[75] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[77] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[109] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[112] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 525 OF 1240 ***

      // Wavefunction(s) for diagram number 525
      // (none)

      // Amplitude(s) for diagram number 525
      FFV1_0( w_sv[65], w_sv[112], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[16] += +amp_sv[0];
      jamp_sv[17] -= amp_sv[0];
      jamp_sv[76] -= amp_sv[0];
      jamp_sv[77] += +amp_sv[0];

      // *** DIAGRAM 526 OF 1240 ***

      // Wavefunction(s) for diagram number 526
      // (none)

      // Amplitude(s) for diagram number 526
      FFV1_0( w_sv[3], w_sv[112], w_sv[64], COUPs[1], &amp_sv[0] );
      jamp_sv[12] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[14] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[16] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[17] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[72] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[74] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[76] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[77] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 527 OF 1240 ***

      // Wavefunction(s) for diagram number 527
      // (none)

      // Amplitude(s) for diagram number 527
      FFV1_0( w_sv[99], w_sv[93], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[34] += +amp_sv[0];
      jamp_sv[35] -= amp_sv[0];
      jamp_sv[58] -= amp_sv[0];
      jamp_sv[59] += +amp_sv[0];

      // *** DIAGRAM 528 OF 1240 ***

      // Wavefunction(s) for diagram number 528
      // (none)

      // Amplitude(s) for diagram number 528
      FFV1_0( w_sv[99], w_sv[2], w_sv[64], COUPs[1], &amp_sv[0] );
      jamp_sv[34] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[35] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[58] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[59] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[104] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[105] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[110] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[111] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 529 OF 1240 ***

      // Wavefunction(s) for diagram number 529
      // (none)

      // Amplitude(s) for diagram number 529
      FFV1_0( w_sv[3], w_sv[93], w_sv[104], COUPs[1], &amp_sv[0] );
      jamp_sv[30] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[32] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[34] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[35] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[54] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[56] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[58] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[59] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 530 OF 1240 ***

      // Wavefunction(s) for diagram number 530
      // (none)

      // Amplitude(s) for diagram number 530
      FFV1_0( w_sv[65], w_sv[2], w_sv[104], COUPs[1], &amp_sv[0] );
      jamp_sv[16] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[17] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[76] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[77] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[100] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[101] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[114] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[115] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 531 OF 1240 ***

      // Wavefunction(s) for diagram number 531
      // (none)

      // Amplitude(s) for diagram number 531
      VVVV1_0( w_sv[92], w_sv[61], w_sv[8], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[12] += +amp_sv[0];
      jamp_sv[14] -= amp_sv[0];
      jamp_sv[30] -= amp_sv[0];
      jamp_sv[32] += +amp_sv[0];
      jamp_sv[54] += +amp_sv[0];
      jamp_sv[56] -= amp_sv[0];
      jamp_sv[72] -= amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[100] -= amp_sv[0];
      jamp_sv[101] += +amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[105] -= amp_sv[0];
      jamp_sv[110] -= amp_sv[0];
      jamp_sv[111] += +amp_sv[0];
      jamp_sv[114] += +amp_sv[0];
      jamp_sv[115] -= amp_sv[0];
      VVVV3_0( w_sv[92], w_sv[61], w_sv[8], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[12] += +amp_sv[0];
      jamp_sv[14] -= amp_sv[0];
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[72] -= amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[105] -= amp_sv[0];
      jamp_sv[110] -= amp_sv[0];
      jamp_sv[111] += +amp_sv[0];
      VVVV4_0( w_sv[92], w_sv[61], w_sv[8], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[30] += +amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      jamp_sv[101] -= amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      jamp_sv[115] += +amp_sv[0];

      // *** DIAGRAM 532 OF 1240 ***

      // Wavefunction(s) for diagram number 532
      VVV1P0_1( w_sv[92], w_sv[61], COUPs[0], 0., 0., w_sv[86] );

      // Amplitude(s) for diagram number 532
      VVV1_0( w_sv[8], w_sv[6], w_sv[86], COUPs[0], &amp_sv[0] );
      jamp_sv[12] += +amp_sv[0];
      jamp_sv[14] -= amp_sv[0];
      jamp_sv[30] -= amp_sv[0];
      jamp_sv[32] += +amp_sv[0];
      jamp_sv[54] += +amp_sv[0];
      jamp_sv[56] -= amp_sv[0];
      jamp_sv[72] -= amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[100] -= amp_sv[0];
      jamp_sv[101] += +amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[105] -= amp_sv[0];
      jamp_sv[110] -= amp_sv[0];
      jamp_sv[111] += +amp_sv[0];
      jamp_sv[114] += +amp_sv[0];
      jamp_sv[115] -= amp_sv[0];

      // *** DIAGRAM 533 OF 1240 ***

      // Wavefunction(s) for diagram number 533
      VVV1P0_1( w_sv[92], w_sv[8], COUPs[0], 0., 0., w_sv[101] );

      // Amplitude(s) for diagram number 533
      VVV1_0( w_sv[61], w_sv[6], w_sv[101], COUPs[0], &amp_sv[0] );
      jamp_sv[12] += +amp_sv[0];
      jamp_sv[14] -= amp_sv[0];
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[72] -= amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[105] -= amp_sv[0];
      jamp_sv[110] -= amp_sv[0];
      jamp_sv[111] += +amp_sv[0];

      // *** DIAGRAM 534 OF 1240 ***

      // Wavefunction(s) for diagram number 534
      // (none)

      // Amplitude(s) for diagram number 534
      VVV1_0( w_sv[61], w_sv[8], w_sv[104], COUPs[0], &amp_sv[0] );
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[30] += +amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      jamp_sv[101] -= amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      jamp_sv[115] += +amp_sv[0];

      // *** DIAGRAM 535 OF 1240 ***

      // Wavefunction(s) for diagram number 535
      // (none)

      // Amplitude(s) for diagram number 535
      FFV1_0( w_sv[3], w_sv[47], w_sv[86], COUPs[1], &amp_sv[0] );
      jamp_sv[100] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[101] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[104] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[105] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[110] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[111] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[114] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[115] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 536 OF 1240 ***

      // Wavefunction(s) for diagram number 536
      // (none)

      // Amplitude(s) for diagram number 536
      FFV1_0( w_sv[3], w_sv[106], w_sv[61], COUPs[1], &amp_sv[0] );
      jamp_sv[100] += +amp_sv[0];
      jamp_sv[101] -= amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      jamp_sv[115] += +amp_sv[0];

      // *** DIAGRAM 537 OF 1240 ***

      // Wavefunction(s) for diagram number 537
      // (none)

      // Amplitude(s) for diagram number 537
      FFV1_0( w_sv[99], w_sv[47], w_sv[61], COUPs[1], &amp_sv[0] );
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[105] -= amp_sv[0];
      jamp_sv[110] -= amp_sv[0];
      jamp_sv[111] += +amp_sv[0];

      // *** DIAGRAM 538 OF 1240 ***

      // Wavefunction(s) for diagram number 538
      // (none)

      // Amplitude(s) for diagram number 538
      FFV1_0( w_sv[41], w_sv[2], w_sv[86], COUPs[1], &amp_sv[0] );
      jamp_sv[12] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[14] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[30] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[32] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[54] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[56] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[72] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[74] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 539 OF 1240 ***

      // Wavefunction(s) for diagram number 539
      // (none)

      // Amplitude(s) for diagram number 539
      FFV1_0( w_sv[41], w_sv[112], w_sv[61], COUPs[1], &amp_sv[0] );
      jamp_sv[12] += +amp_sv[0];
      jamp_sv[14] -= amp_sv[0];
      jamp_sv[72] -= amp_sv[0];
      jamp_sv[74] += +amp_sv[0];

      // *** DIAGRAM 540 OF 1240 ***

      // Wavefunction(s) for diagram number 540
      // (none)

      // Amplitude(s) for diagram number 540
      FFV1_0( w_sv[113], w_sv[2], w_sv[61], COUPs[1], &amp_sv[0] );
      jamp_sv[30] += +amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[56] += +amp_sv[0];

      // *** DIAGRAM 541 OF 1240 ***

      // Wavefunction(s) for diagram number 541
      // (none)

      // Amplitude(s) for diagram number 541
      FFV1_0( w_sv[76], w_sv[112], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[14] += +amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[74] -= amp_sv[0];
      jamp_sv[75] += +amp_sv[0];

      // *** DIAGRAM 542 OF 1240 ***

      // Wavefunction(s) for diagram number 542
      // (none)

      // Amplitude(s) for diagram number 542
      FFV1_0( w_sv[3], w_sv[112], w_sv[74], COUPs[1], &amp_sv[0] );
      jamp_sv[13] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[14] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[15] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[16] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[73] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[74] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[75] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[76] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 543 OF 1240 ***

      // Wavefunction(s) for diagram number 543
      // (none)

      // Amplitude(s) for diagram number 543
      FFV1_0( w_sv[99], w_sv[97], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[44] += +amp_sv[0];
      jamp_sv[45] -= amp_sv[0];
      jamp_sv[104] -= amp_sv[0];
      jamp_sv[105] += +amp_sv[0];

      // *** DIAGRAM 544 OF 1240 ***

      // Wavefunction(s) for diagram number 544
      // (none)

      // Amplitude(s) for diagram number 544
      FFV1_0( w_sv[99], w_sv[2], w_sv[74], COUPs[1], &amp_sv[0] );
      jamp_sv[44] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[45] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[58] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[59] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[68] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[69] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[104] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[105] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 545 OF 1240 ***

      // Wavefunction(s) for diagram number 545
      // (none)

      // Amplitude(s) for diagram number 545
      FFV1_0( w_sv[3], w_sv[97], w_sv[102], COUPs[1], &amp_sv[0] );
      jamp_sv[43] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[44] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[45] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[46] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[103] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[104] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[105] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[106] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 546 OF 1240 ***

      // Wavefunction(s) for diagram number 546
      // (none)

      // Amplitude(s) for diagram number 546
      FFV1_0( w_sv[76], w_sv[2], w_sv[102], COUPs[1], &amp_sv[0] );
      jamp_sv[14] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[15] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[50] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[51] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[60] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[61] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[74] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[75] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 547 OF 1240 ***

      // Wavefunction(s) for diagram number 547
      // (none)

      // Amplitude(s) for diagram number 547
      VVVV1_0( w_sv[92], w_sv[72], w_sv[8], w_sv[4], COUPs[2], &amp_sv[0] );
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[43] -= amp_sv[0];
      jamp_sv[46] += +amp_sv[0];
      jamp_sv[50] -= amp_sv[0];
      jamp_sv[51] += +amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[60] += +amp_sv[0];
      jamp_sv[61] -= amp_sv[0];
      jamp_sv[68] -= amp_sv[0];
      jamp_sv[69] += +amp_sv[0];
      jamp_sv[73] -= amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[103] += +amp_sv[0];
      jamp_sv[106] -= amp_sv[0];
      VVVV3_0( w_sv[92], w_sv[72], w_sv[8], w_sv[4], COUPs[2], &amp_sv[0] );
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[14] -= amp_sv[0];
      jamp_sv[15] += +amp_sv[0];
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[45] += +amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[68] -= amp_sv[0];
      jamp_sv[69] += +amp_sv[0];
      jamp_sv[73] -= amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[105] -= amp_sv[0];
      VVVV4_0( w_sv[92], w_sv[72], w_sv[8], w_sv[4], COUPs[2], &amp_sv[0] );
      jamp_sv[14] -= amp_sv[0];
      jamp_sv[15] += +amp_sv[0];
      jamp_sv[43] += +amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[45] += +amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[61] += +amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[105] -= amp_sv[0];
      jamp_sv[106] += +amp_sv[0];

      // *** DIAGRAM 548 OF 1240 ***

      // Wavefunction(s) for diagram number 548
      VVV1P0_1( w_sv[92], w_sv[72], COUPs[0], 0., 0., w_sv[86] );

      // Amplitude(s) for diagram number 548
      VVV1_0( w_sv[8], w_sv[4], w_sv[86], COUPs[0], &amp_sv[0] );
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[43] -= amp_sv[0];
      jamp_sv[46] += +amp_sv[0];
      jamp_sv[50] -= amp_sv[0];
      jamp_sv[51] += +amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[60] += +amp_sv[0];
      jamp_sv[61] -= amp_sv[0];
      jamp_sv[68] -= amp_sv[0];
      jamp_sv[69] += +amp_sv[0];
      jamp_sv[73] -= amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[103] += +amp_sv[0];
      jamp_sv[106] -= amp_sv[0];

      // *** DIAGRAM 549 OF 1240 ***

      // Wavefunction(s) for diagram number 549
      // (none)

      // Amplitude(s) for diagram number 549
      VVV1_0( w_sv[72], w_sv[4], w_sv[101], COUPs[0], &amp_sv[0] );
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[14] -= amp_sv[0];
      jamp_sv[15] += +amp_sv[0];
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[45] += +amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[68] -= amp_sv[0];
      jamp_sv[69] += +amp_sv[0];
      jamp_sv[73] -= amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[105] -= amp_sv[0];

      // *** DIAGRAM 550 OF 1240 ***

      // Wavefunction(s) for diagram number 550
      // (none)

      // Amplitude(s) for diagram number 550
      VVV1_0( w_sv[72], w_sv[8], w_sv[102], COUPs[0], &amp_sv[0] );
      jamp_sv[14] -= amp_sv[0];
      jamp_sv[15] += +amp_sv[0];
      jamp_sv[43] += +amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[45] += +amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[61] += +amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[105] -= amp_sv[0];
      jamp_sv[106] += +amp_sv[0];

      // *** DIAGRAM 551 OF 1240 ***

      // Wavefunction(s) for diagram number 551
      // (none)

      // Amplitude(s) for diagram number 551
      FFV1_0( w_sv[3], w_sv[33], w_sv[86], COUPs[1], &amp_sv[0] );
      jamp_sv[50] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[51] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[58] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[59] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[60] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[61] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[68] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[69] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 552 OF 1240 ***

      // Wavefunction(s) for diagram number 552
      // (none)

      // Amplitude(s) for diagram number 552
      FFV1_0( w_sv[3], w_sv[98], w_sv[72], COUPs[1], &amp_sv[0] );
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[61] += +amp_sv[0];

      // *** DIAGRAM 553 OF 1240 ***

      // Wavefunction(s) for diagram number 553
      // (none)

      // Amplitude(s) for diagram number 553
      FFV1_0( w_sv[99], w_sv[33], w_sv[72], COUPs[1], &amp_sv[0] );
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[68] -= amp_sv[0];
      jamp_sv[69] += +amp_sv[0];

      // *** DIAGRAM 554 OF 1240 ***

      // Wavefunction(s) for diagram number 554
      // (none)

      // Amplitude(s) for diagram number 554
      FFV1_0( w_sv[46], w_sv[2], w_sv[86], COUPs[1], &amp_sv[0] );
      jamp_sv[13] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[16] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[43] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[46] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[73] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[76] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[103] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[106] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 555 OF 1240 ***

      // Wavefunction(s) for diagram number 555
      // (none)

      // Amplitude(s) for diagram number 555
      FFV1_0( w_sv[46], w_sv[112], w_sv[72], COUPs[1], &amp_sv[0] );
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[73] -= amp_sv[0];
      jamp_sv[76] += +amp_sv[0];

      // *** DIAGRAM 556 OF 1240 ***

      // Wavefunction(s) for diagram number 556
      // (none)

      // Amplitude(s) for diagram number 556
      FFV1_0( w_sv[114], w_sv[2], w_sv[72], COUPs[1], &amp_sv[0] );
      jamp_sv[43] += +amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      jamp_sv[106] += +amp_sv[0];

      // *** DIAGRAM 557 OF 1240 ***

      // Wavefunction(s) for diagram number 557
      VVV1P0_1( w_sv[92], w_sv[1], COUPs[0], 0., 0., w_sv[86] );

      // Amplitude(s) for diagram number 557
      VVV1_0( w_sv[86], w_sv[13], w_sv[6], COUPs[0], &amp_sv[0] );
      jamp_sv[13] -= amp_sv[0];
      jamp_sv[27] += +amp_sv[0];
      jamp_sv[37] -= amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[67] -= amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[69] -= amp_sv[0];
      jamp_sv[70] += +amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      jamp_sv[114] -= amp_sv[0];

      // *** DIAGRAM 558 OF 1240 ***

      // Wavefunction(s) for diagram number 558
      // (none)

      // Amplitude(s) for diagram number 558
      VVV1_0( w_sv[86], w_sv[11], w_sv[4], COUPs[0], &amp_sv[0] );
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[36] -= amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      jamp_sv[109] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];
      jamp_sv[111] -= amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      jamp_sv[114] -= amp_sv[0];

      // *** DIAGRAM 559 OF 1240 ***

      // Wavefunction(s) for diagram number 559
      // (none)

      // Amplitude(s) for diagram number 559
      VVVV1_0( w_sv[8], w_sv[4], w_sv[6], w_sv[86], COUPs[2], &amp_sv[0] );
      jamp_sv[13] -= amp_sv[0];
      jamp_sv[27] += +amp_sv[0];
      jamp_sv[37] -= amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[67] -= amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[69] -= amp_sv[0];
      jamp_sv[70] += +amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      VVVV3_0( w_sv[8], w_sv[4], w_sv[6], w_sv[86], COUPs[2], &amp_sv[0] );
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[36] -= amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      jamp_sv[109] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];
      jamp_sv[111] -= amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      VVVV4_0( w_sv[8], w_sv[4], w_sv[6], w_sv[86], COUPs[2], &amp_sv[0] );
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[27] -= amp_sv[0];
      jamp_sv[36] -= amp_sv[0];
      jamp_sv[37] += +amp_sv[0];
      jamp_sv[67] += +amp_sv[0];
      jamp_sv[68] -= amp_sv[0];
      jamp_sv[69] += +amp_sv[0];
      jamp_sv[70] -= amp_sv[0];
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[73] -= amp_sv[0];
      jamp_sv[109] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];
      jamp_sv[111] -= amp_sv[0];
      jamp_sv[112] += +amp_sv[0];

      // *** DIAGRAM 560 OF 1240 ***

      // Wavefunction(s) for diagram number 560
      // (none)

      // Amplitude(s) for diagram number 560
      VVV1_0( w_sv[102], w_sv[108], w_sv[6], COUPs[0], &amp_sv[0] );
      jamp_sv[15] += +amp_sv[0];
      jamp_sv[26] -= amp_sv[0];
      jamp_sv[30] += +amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[36] += +amp_sv[0];
      jamp_sv[43] += +amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[45] += +amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[61] += +amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[101] -= amp_sv[0];
      jamp_sv[109] += +amp_sv[0];
      jamp_sv[112] -= amp_sv[0];
      jamp_sv[115] += +amp_sv[0];

      // *** DIAGRAM 561 OF 1240 ***

      // Wavefunction(s) for diagram number 561
      // (none)

      // Amplitude(s) for diagram number 561
      VVV1_0( w_sv[102], w_sv[1], w_sv[11], COUPs[0], &amp_sv[0] );
      jamp_sv[14] += +amp_sv[0];
      jamp_sv[26] -= amp_sv[0];
      jamp_sv[30] += +amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[36] += +amp_sv[0];
      jamp_sv[50] -= amp_sv[0];
      jamp_sv[60] += +amp_sv[0];
      jamp_sv[74] -= amp_sv[0];
      jamp_sv[101] -= amp_sv[0];
      jamp_sv[103] += +amp_sv[0];
      jamp_sv[104] -= amp_sv[0];
      jamp_sv[105] += +amp_sv[0];
      jamp_sv[106] -= amp_sv[0];
      jamp_sv[109] += +amp_sv[0];
      jamp_sv[112] -= amp_sv[0];
      jamp_sv[115] += +amp_sv[0];

      // *** DIAGRAM 562 OF 1240 ***

      // Wavefunction(s) for diagram number 562
      // (none)

      // Amplitude(s) for diagram number 562
      VVVV1_0( w_sv[1], w_sv[8], w_sv[6], w_sv[102], COUPs[2], &amp_sv[0] );
      jamp_sv[15] += +amp_sv[0];
      jamp_sv[26] -= amp_sv[0];
      jamp_sv[30] += +amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[36] += +amp_sv[0];
      jamp_sv[43] += +amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[45] += +amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[61] += +amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[101] -= amp_sv[0];
      jamp_sv[109] += +amp_sv[0];
      jamp_sv[112] -= amp_sv[0];
      jamp_sv[115] += +amp_sv[0];
      VVVV3_0( w_sv[1], w_sv[8], w_sv[6], w_sv[102], COUPs[2], &amp_sv[0] );
      jamp_sv[14] -= amp_sv[0];
      jamp_sv[15] += +amp_sv[0];
      jamp_sv[43] += +amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[45] += +amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[61] += +amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[105] -= amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      VVVV4_0( w_sv[1], w_sv[8], w_sv[6], w_sv[102], COUPs[2], &amp_sv[0] );
      jamp_sv[14] -= amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[30] -= amp_sv[0];
      jamp_sv[32] += +amp_sv[0];
      jamp_sv[36] -= amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[101] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[105] -= amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      jamp_sv[109] -= amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      jamp_sv[115] -= amp_sv[0];

      // *** DIAGRAM 563 OF 1240 ***

      // Wavefunction(s) for diagram number 563
      // (none)

      // Amplitude(s) for diagram number 563
      VVV1_0( w_sv[104], w_sv[108], w_sv[4], COUPs[0], &amp_sv[0] );
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[27] -= amp_sv[0];
      jamp_sv[30] += +amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[37] += +amp_sv[0];
      jamp_sv[43] += +amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[61] += +amp_sv[0];
      jamp_sv[67] += +amp_sv[0];
      jamp_sv[70] -= amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[101] -= amp_sv[0];
      jamp_sv[115] += +amp_sv[0];

      // *** DIAGRAM 564 OF 1240 ***

      // Wavefunction(s) for diagram number 564
      // (none)

      // Amplitude(s) for diagram number 564
      VVV1_0( w_sv[104], w_sv[1], w_sv[13], COUPs[0], &amp_sv[0] );
      jamp_sv[16] += +amp_sv[0];
      jamp_sv[27] -= amp_sv[0];
      jamp_sv[37] += +amp_sv[0];
      jamp_sv[43] += +amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[54] += +amp_sv[0];
      jamp_sv[56] -= amp_sv[0];
      jamp_sv[58] -= amp_sv[0];
      jamp_sv[59] += +amp_sv[0];
      jamp_sv[61] += +amp_sv[0];
      jamp_sv[67] += +amp_sv[0];
      jamp_sv[70] -= amp_sv[0];
      jamp_sv[76] -= amp_sv[0];
      jamp_sv[100] -= amp_sv[0];
      jamp_sv[114] += +amp_sv[0];

      // *** DIAGRAM 565 OF 1240 ***

      // Wavefunction(s) for diagram number 565
      // (none)

      // Amplitude(s) for diagram number 565
      VVVV1_0( w_sv[1], w_sv[8], w_sv[4], w_sv[104], COUPs[2], &amp_sv[0] );
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[27] -= amp_sv[0];
      jamp_sv[30] += +amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[37] += +amp_sv[0];
      jamp_sv[43] += +amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[61] += +amp_sv[0];
      jamp_sv[67] += +amp_sv[0];
      jamp_sv[70] -= amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[101] -= amp_sv[0];
      jamp_sv[115] += +amp_sv[0];
      VVVV3_0( w_sv[1], w_sv[8], w_sv[4], w_sv[104], COUPs[2], &amp_sv[0] );
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[30] += +amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      jamp_sv[101] -= amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      jamp_sv[115] += +amp_sv[0];
      VVVV4_0( w_sv[1], w_sv[8], w_sv[4], w_sv[104], COUPs[2], &amp_sv[0] );
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[27] += +amp_sv[0];
      jamp_sv[37] -= amp_sv[0];
      jamp_sv[43] -= amp_sv[0];
      jamp_sv[46] += +amp_sv[0];
      jamp_sv[51] += +amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[61] -= amp_sv[0];
      jamp_sv[67] -= amp_sv[0];
      jamp_sv[70] += +amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      jamp_sv[114] -= amp_sv[0];

      // *** DIAGRAM 566 OF 1240 ***

      // Wavefunction(s) for diagram number 566
      VVVV1P0_1( w_sv[92], w_sv[1], w_sv[4], COUPs[2], 0., 0., w_sv[105] );
      VVVV3P0_1( w_sv[92], w_sv[1], w_sv[4], COUPs[2], 0., 0., w_sv[95] );
      VVVV4P0_1( w_sv[92], w_sv[1], w_sv[4], COUPs[2], 0., 0., w_sv[107] );

      // Amplitude(s) for diagram number 566
      VVV1_0( w_sv[8], w_sv[6], w_sv[105], COUPs[0], &amp_sv[0] );
      jamp_sv[12] += +amp_sv[0];
      jamp_sv[14] -= amp_sv[0];
      jamp_sv[30] -= amp_sv[0];
      jamp_sv[32] += +amp_sv[0];
      jamp_sv[54] += +amp_sv[0];
      jamp_sv[56] -= amp_sv[0];
      jamp_sv[72] -= amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[100] -= amp_sv[0];
      jamp_sv[101] += +amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[105] -= amp_sv[0];
      jamp_sv[110] -= amp_sv[0];
      jamp_sv[111] += +amp_sv[0];
      jamp_sv[114] += +amp_sv[0];
      jamp_sv[115] -= amp_sv[0];
      VVV1_0( w_sv[8], w_sv[6], w_sv[95], COUPs[0], &amp_sv[0] );
      jamp_sv[14] -= amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[30] -= amp_sv[0];
      jamp_sv[32] += +amp_sv[0];
      jamp_sv[36] -= amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[101] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[105] -= amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      jamp_sv[109] -= amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      jamp_sv[115] -= amp_sv[0];
      VVV1_0( w_sv[8], w_sv[6], w_sv[107], COUPs[0], &amp_sv[0] );
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[36] -= amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      jamp_sv[109] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];
      jamp_sv[111] -= amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      jamp_sv[114] -= amp_sv[0];

      // *** DIAGRAM 567 OF 1240 ***

      // Wavefunction(s) for diagram number 567
      VVVV1P0_1( w_sv[92], w_sv[1], w_sv[6], COUPs[2], 0., 0., w_sv[96] );
      VVVV3P0_1( w_sv[92], w_sv[1], w_sv[6], COUPs[2], 0., 0., w_sv[90] );
      VVVV4P0_1( w_sv[92], w_sv[1], w_sv[6], COUPs[2], 0., 0., w_sv[88] );

      // Amplitude(s) for diagram number 567
      VVV1_0( w_sv[8], w_sv[4], w_sv[96], COUPs[0], &amp_sv[0] );
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[43] -= amp_sv[0];
      jamp_sv[46] += +amp_sv[0];
      jamp_sv[50] -= amp_sv[0];
      jamp_sv[51] += +amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[60] += +amp_sv[0];
      jamp_sv[61] -= amp_sv[0];
      jamp_sv[68] -= amp_sv[0];
      jamp_sv[69] += +amp_sv[0];
      jamp_sv[73] -= amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[103] += +amp_sv[0];
      jamp_sv[106] -= amp_sv[0];
      VVV1_0( w_sv[8], w_sv[4], w_sv[90], COUPs[0], &amp_sv[0] );
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[27] += +amp_sv[0];
      jamp_sv[37] -= amp_sv[0];
      jamp_sv[43] -= amp_sv[0];
      jamp_sv[46] += +amp_sv[0];
      jamp_sv[51] += +amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[61] -= amp_sv[0];
      jamp_sv[67] -= amp_sv[0];
      jamp_sv[70] += +amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      VVV1_0( w_sv[8], w_sv[4], w_sv[88], COUPs[0], &amp_sv[0] );
      jamp_sv[13] -= amp_sv[0];
      jamp_sv[27] += +amp_sv[0];
      jamp_sv[37] -= amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[67] -= amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[69] -= amp_sv[0];
      jamp_sv[70] += +amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      jamp_sv[114] -= amp_sv[0];

      // *** DIAGRAM 568 OF 1240 ***

      // Wavefunction(s) for diagram number 568
      // (none)

      // Amplitude(s) for diagram number 568
      VVV1_0( w_sv[1], w_sv[8], w_sv[111], COUPs[0], &amp_sv[0] );
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[27] -= amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[36] -= amp_sv[0];
      jamp_sv[37] += +amp_sv[0];
      jamp_sv[44] += +amp_sv[0];
      jamp_sv[45] -= amp_sv[0];
      jamp_sv[67] += +amp_sv[0];
      jamp_sv[70] -= amp_sv[0];
      jamp_sv[75] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[109] -= amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      VVV1_0( w_sv[1], w_sv[8], w_sv[110], COUPs[0], &amp_sv[0] );
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[27] -= amp_sv[0];
      jamp_sv[30] += +amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[37] += +amp_sv[0];
      jamp_sv[43] += +amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[61] += +amp_sv[0];
      jamp_sv[67] += +amp_sv[0];
      jamp_sv[70] -= amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[101] -= amp_sv[0];
      jamp_sv[115] += +amp_sv[0];
      VVV1_0( w_sv[1], w_sv[8], w_sv[109], COUPs[0], &amp_sv[0] );
      jamp_sv[15] += +amp_sv[0];
      jamp_sv[26] -= amp_sv[0];
      jamp_sv[30] += +amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[36] += +amp_sv[0];
      jamp_sv[43] += +amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[45] += +amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[61] += +amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[101] -= amp_sv[0];
      jamp_sv[109] += +amp_sv[0];
      jamp_sv[112] -= amp_sv[0];
      jamp_sv[115] += +amp_sv[0];

      // *** DIAGRAM 569 OF 1240 ***

      // Wavefunction(s) for diagram number 569
      // (none)

      // Amplitude(s) for diagram number 569
      VVVV1_0( w_sv[92], w_sv[1], w_sv[8], w_sv[27], COUPs[2], &amp_sv[0] );
      jamp_sv[12] += +amp_sv[0];
      jamp_sv[13] -= amp_sv[0];
      jamp_sv[26] -= amp_sv[0];
      jamp_sv[27] += +amp_sv[0];
      jamp_sv[36] += +amp_sv[0];
      jamp_sv[37] -= amp_sv[0];
      jamp_sv[67] -= amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[69] -= amp_sv[0];
      jamp_sv[70] += +amp_sv[0];
      jamp_sv[72] -= amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[109] += +amp_sv[0];
      jamp_sv[110] -= amp_sv[0];
      jamp_sv[111] += +amp_sv[0];
      jamp_sv[112] -= amp_sv[0];
      VVVV3_0( w_sv[92], w_sv[1], w_sv[8], w_sv[27], COUPs[2], &amp_sv[0] );
      jamp_sv[12] += +amp_sv[0];
      jamp_sv[13] -= amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[44] += +amp_sv[0];
      jamp_sv[45] -= amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[69] -= amp_sv[0];
      jamp_sv[72] -= amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[75] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[110] -= amp_sv[0];
      jamp_sv[111] += +amp_sv[0];
      VVVV4_0( w_sv[92], w_sv[1], w_sv[8], w_sv[27], COUPs[2], &amp_sv[0] );
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[27] -= amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[36] -= amp_sv[0];
      jamp_sv[37] += +amp_sv[0];
      jamp_sv[44] += +amp_sv[0];
      jamp_sv[45] -= amp_sv[0];
      jamp_sv[67] += +amp_sv[0];
      jamp_sv[70] -= amp_sv[0];
      jamp_sv[75] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[109] -= amp_sv[0];
      jamp_sv[112] += +amp_sv[0];

      // *** DIAGRAM 570 OF 1240 ***

      // Wavefunction(s) for diagram number 570
      // (none)

      // Amplitude(s) for diagram number 570
      VVV1_0( w_sv[8], w_sv[27], w_sv[86], COUPs[0], &amp_sv[0] );
      jamp_sv[12] += +amp_sv[0];
      jamp_sv[13] -= amp_sv[0];
      jamp_sv[26] -= amp_sv[0];
      jamp_sv[27] += +amp_sv[0];
      jamp_sv[36] += +amp_sv[0];
      jamp_sv[37] -= amp_sv[0];
      jamp_sv[67] -= amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[69] -= amp_sv[0];
      jamp_sv[70] += +amp_sv[0];
      jamp_sv[72] -= amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[109] += +amp_sv[0];
      jamp_sv[110] -= amp_sv[0];
      jamp_sv[111] += +amp_sv[0];
      jamp_sv[112] -= amp_sv[0];

      // *** DIAGRAM 571 OF 1240 ***

      // Wavefunction(s) for diagram number 571
      // (none)

      // Amplitude(s) for diagram number 571
      VVV1_0( w_sv[1], w_sv[27], w_sv[101], COUPs[0], &amp_sv[0] );
      jamp_sv[12] += +amp_sv[0];
      jamp_sv[13] -= amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[44] += +amp_sv[0];
      jamp_sv[45] -= amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[69] -= amp_sv[0];
      jamp_sv[72] -= amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[75] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[110] -= amp_sv[0];
      jamp_sv[111] += +amp_sv[0];

      // *** DIAGRAM 572 OF 1240 ***

      // Wavefunction(s) for diagram number 572
      // (none)

      // Amplitude(s) for diagram number 572
      VVV1_0( w_sv[1], w_sv[8], w_sv[62], COUPs[0], &amp_sv[0] );
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[27] -= amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[36] -= amp_sv[0];
      jamp_sv[37] += +amp_sv[0];
      jamp_sv[44] += +amp_sv[0];
      jamp_sv[45] -= amp_sv[0];
      jamp_sv[67] += +amp_sv[0];
      jamp_sv[70] -= amp_sv[0];
      jamp_sv[75] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[109] -= amp_sv[0];
      jamp_sv[112] += +amp_sv[0];

      // *** DIAGRAM 573 OF 1240 ***

      // Wavefunction(s) for diagram number 573
      // (none)

      // Amplitude(s) for diagram number 573
      VVV1_0( w_sv[86], w_sv[37], w_sv[6], COUPs[0], &amp_sv[0] );
      jamp_sv[50] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[54] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[56] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[60] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[67] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[68] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[69] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[70] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 574 OF 1240 ***

      // Wavefunction(s) for diagram number 574
      // (none)

      // Amplitude(s) for diagram number 574
      FFV1_0( w_sv[3], w_sv[36], w_sv[86], COUPs[1], &amp_sv[0] );
      jamp_sv[67] += +amp_sv[0];
      jamp_sv[68] -= amp_sv[0];
      jamp_sv[69] += +amp_sv[0];
      jamp_sv[70] -= amp_sv[0];

      // *** DIAGRAM 575 OF 1240 ***

      // Wavefunction(s) for diagram number 575
      // (none)

      // Amplitude(s) for diagram number 575
      FFV1_0( w_sv[99], w_sv[100], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[58] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[59] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 576 OF 1240 ***

      // Wavefunction(s) for diagram number 576
      // (none)

      // Amplitude(s) for diagram number 576
      FFV1_0( w_sv[99], w_sv[36], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[68] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[69] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 577 OF 1240 ***

      // Wavefunction(s) for diagram number 577
      // (none)

      // Amplitude(s) for diagram number 577
      FFV1_0( w_sv[3], w_sv[100], w_sv[104], COUPs[1], &amp_sv[0] );
      jamp_sv[54] += +amp_sv[0];
      jamp_sv[56] -= amp_sv[0];
      jamp_sv[58] -= amp_sv[0];
      jamp_sv[59] += +amp_sv[0];

      // *** DIAGRAM 578 OF 1240 ***

      // Wavefunction(s) for diagram number 578
      // (none)

      // Amplitude(s) for diagram number 578
      VVV1_0( w_sv[104], w_sv[1], w_sv[37], COUPs[0], &amp_sv[0] );
      jamp_sv[51] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[54] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[56] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[58] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[59] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[61] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[67] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[70] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 579 OF 1240 ***

      // Wavefunction(s) for diagram number 579
      // (none)

      // Amplitude(s) for diagram number 579
      FFV1_0( w_sv[3], w_sv[33], w_sv[96], COUPs[1], &amp_sv[0] );
      jamp_sv[50] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[51] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[58] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[59] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[60] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[61] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[68] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[69] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[33], w_sv[90], COUPs[1], &amp_sv[0] );
      jamp_sv[51] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[54] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[56] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[58] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[59] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[61] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[67] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[70] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[33], w_sv[88], COUPs[1], &amp_sv[0] );
      jamp_sv[50] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[54] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[56] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[60] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[67] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[68] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[69] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[70] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 580 OF 1240 ***

      // Wavefunction(s) for diagram number 580
      // (none)

      // Amplitude(s) for diagram number 580
      FFV1_0( w_sv[41], w_sv[33], w_sv[86], COUPs[1], &amp_sv[0] );
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[60] -= amp_sv[0];

      // *** DIAGRAM 581 OF 1240 ***

      // Wavefunction(s) for diagram number 581
      // (none)

      // Amplitude(s) for diagram number 581
      FFV1_0( w_sv[41], w_sv[98], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[50] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[60] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 582 OF 1240 ***

      // Wavefunction(s) for diagram number 582
      // (none)

      // Amplitude(s) for diagram number 582
      FFV1_0( w_sv[113], w_sv[33], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[54] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[56] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 583 OF 1240 ***

      // Wavefunction(s) for diagram number 583
      // (none)

      // Amplitude(s) for diagram number 583
      VVV1_0( w_sv[86], w_sv[51], w_sv[4], COUPs[0], &amp_sv[0] );
      jamp_sv[100] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[103] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[106] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[109] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[110] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[111] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[112] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[114] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 584 OF 1240 ***

      // Wavefunction(s) for diagram number 584
      // (none)

      // Amplitude(s) for diagram number 584
      FFV1_0( w_sv[3], w_sv[49], w_sv[86], COUPs[1], &amp_sv[0] );
      jamp_sv[109] += +amp_sv[0];
      jamp_sv[110] -= amp_sv[0];
      jamp_sv[111] += +amp_sv[0];
      jamp_sv[112] -= amp_sv[0];

      // *** DIAGRAM 585 OF 1240 ***

      // Wavefunction(s) for diagram number 585
      // (none)

      // Amplitude(s) for diagram number 585
      FFV1_0( w_sv[99], w_sv[91], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[104] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[105] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 586 OF 1240 ***

      // Wavefunction(s) for diagram number 586
      // (none)

      // Amplitude(s) for diagram number 586
      FFV1_0( w_sv[99], w_sv[49], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[110] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[111] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 587 OF 1240 ***

      // Wavefunction(s) for diagram number 587
      // (none)

      // Amplitude(s) for diagram number 587
      FFV1_0( w_sv[3], w_sv[91], w_sv[102], COUPs[1], &amp_sv[0] );
      jamp_sv[103] += +amp_sv[0];
      jamp_sv[104] -= amp_sv[0];
      jamp_sv[105] += +amp_sv[0];
      jamp_sv[106] -= amp_sv[0];

      // *** DIAGRAM 588 OF 1240 ***

      // Wavefunction(s) for diagram number 588
      // (none)

      // Amplitude(s) for diagram number 588
      VVV1_0( w_sv[102], w_sv[1], w_sv[51], COUPs[0], &amp_sv[0] );
      jamp_sv[101] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[103] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[104] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[105] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[106] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[109] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[112] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[115] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 589 OF 1240 ***

      // Wavefunction(s) for diagram number 589
      // (none)

      // Amplitude(s) for diagram number 589
      FFV1_0( w_sv[3], w_sv[47], w_sv[105], COUPs[1], &amp_sv[0] );
      jamp_sv[100] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[101] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[104] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[105] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[110] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[111] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[114] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[115] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[47], w_sv[95], COUPs[1], &amp_sv[0] );
      jamp_sv[101] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[103] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[104] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[105] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[106] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[109] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[112] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[115] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[47], w_sv[107], COUPs[1], &amp_sv[0] );
      jamp_sv[100] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[103] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[106] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[109] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[110] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[111] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[112] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[114] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 590 OF 1240 ***

      // Wavefunction(s) for diagram number 590
      // (none)

      // Amplitude(s) for diagram number 590
      FFV1_0( w_sv[46], w_sv[47], w_sv[86], COUPs[1], &amp_sv[0] );
      jamp_sv[100] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      jamp_sv[114] -= amp_sv[0];

      // *** DIAGRAM 591 OF 1240 ***

      // Wavefunction(s) for diagram number 591
      // (none)

      // Amplitude(s) for diagram number 591
      FFV1_0( w_sv[46], w_sv[106], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[100] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[114] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 592 OF 1240 ***

      // Wavefunction(s) for diagram number 592
      // (none)

      // Amplitude(s) for diagram number 592
      FFV1_0( w_sv[114], w_sv[47], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[103] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[106] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 593 OF 1240 ***

      // Wavefunction(s) for diagram number 593
      // (none)

      // Amplitude(s) for diagram number 593
      VVV1_0( w_sv[86], w_sv[54], w_sv[6], COUPs[0], &amp_sv[0] );
      jamp_sv[13] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[27] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[37] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[73] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[100] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[103] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[106] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[114] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 594 OF 1240 ***

      // Wavefunction(s) for diagram number 594
      // (none)

      // Amplitude(s) for diagram number 594
      FFV1_0( w_sv[53], w_sv[2], w_sv[86], COUPs[1], &amp_sv[0] );
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[27] -= amp_sv[0];
      jamp_sv[37] += +amp_sv[0];
      jamp_sv[73] -= amp_sv[0];

      // *** DIAGRAM 595 OF 1240 ***

      // Wavefunction(s) for diagram number 595
      // (none)

      // Amplitude(s) for diagram number 595
      FFV1_0( w_sv[78], w_sv[112], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[16] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[76] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 596 OF 1240 ***

      // Wavefunction(s) for diagram number 596
      // (none)

      // Amplitude(s) for diagram number 596
      FFV1_0( w_sv[53], w_sv[112], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[13] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[73] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 597 OF 1240 ***

      // Wavefunction(s) for diagram number 597
      // (none)

      // Amplitude(s) for diagram number 597
      FFV1_0( w_sv[78], w_sv[2], w_sv[104], COUPs[1], &amp_sv[0] );
      jamp_sv[16] += +amp_sv[0];
      jamp_sv[76] -= amp_sv[0];
      jamp_sv[100] -= amp_sv[0];
      jamp_sv[114] += +amp_sv[0];

      // *** DIAGRAM 598 OF 1240 ***

      // Wavefunction(s) for diagram number 598
      // (none)

      // Amplitude(s) for diagram number 598
      VVV1_0( w_sv[104], w_sv[1], w_sv[54], COUPs[0], &amp_sv[0] );
      jamp_sv[16] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[27] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[37] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[43] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[46] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[76] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[100] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[114] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 599 OF 1240 ***

      // Wavefunction(s) for diagram number 599
      // (none)

      // Amplitude(s) for diagram number 599
      FFV1_0( w_sv[46], w_sv[2], w_sv[96], COUPs[1], &amp_sv[0] );
      jamp_sv[13] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[16] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[43] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[46] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[73] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[76] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[103] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[106] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[46], w_sv[2], w_sv[90], COUPs[1], &amp_sv[0] );
      jamp_sv[16] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[27] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[37] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[43] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[46] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[76] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[100] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[114] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[46], w_sv[2], w_sv[88], COUPs[1], &amp_sv[0] );
      jamp_sv[13] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[27] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[37] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[73] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[100] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[103] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[106] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[114] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 600 OF 1240 ***

      // Wavefunction(s) for diagram number 600
      // (none)

      // Amplitude(s) for diagram number 600
      VVV1_0( w_sv[86], w_sv[20], w_sv[4], COUPs[0], &amp_sv[0] );
      jamp_sv[12] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[26] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[36] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[50] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[54] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[56] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[60] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[72] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 601 OF 1240 ***

      // Wavefunction(s) for diagram number 601
      // (none)

      // Amplitude(s) for diagram number 601
      FFV1_0( w_sv[28], w_sv[2], w_sv[86], COUPs[1], &amp_sv[0] );
      jamp_sv[12] += +amp_sv[0];
      jamp_sv[26] -= amp_sv[0];
      jamp_sv[36] += +amp_sv[0];
      jamp_sv[72] -= amp_sv[0];

      // *** DIAGRAM 602 OF 1240 ***

      // Wavefunction(s) for diagram number 602
      // (none)

      // Amplitude(s) for diagram number 602
      FFV1_0( w_sv[60], w_sv[112], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[14] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[74] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 603 OF 1240 ***

      // Wavefunction(s) for diagram number 603
      // (none)

      // Amplitude(s) for diagram number 603
      FFV1_0( w_sv[28], w_sv[112], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[12] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[72] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 604 OF 1240 ***

      // Wavefunction(s) for diagram number 604
      // (none)

      // Amplitude(s) for diagram number 604
      FFV1_0( w_sv[60], w_sv[2], w_sv[102], COUPs[1], &amp_sv[0] );
      jamp_sv[14] += +amp_sv[0];
      jamp_sv[50] -= amp_sv[0];
      jamp_sv[60] += +amp_sv[0];
      jamp_sv[74] -= amp_sv[0];

      // *** DIAGRAM 605 OF 1240 ***

      // Wavefunction(s) for diagram number 605
      // (none)

      // Amplitude(s) for diagram number 605
      VVV1_0( w_sv[102], w_sv[1], w_sv[20], COUPs[0], &amp_sv[0] );
      jamp_sv[14] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[26] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[30] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[32] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[36] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[50] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[60] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[74] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 606 OF 1240 ***

      // Wavefunction(s) for diagram number 606
      // (none)

      // Amplitude(s) for diagram number 606
      FFV1_0( w_sv[41], w_sv[2], w_sv[105], COUPs[1], &amp_sv[0] );
      jamp_sv[12] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[14] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[30] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[32] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[54] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[56] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[72] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[74] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[41], w_sv[2], w_sv[95], COUPs[1], &amp_sv[0] );
      jamp_sv[14] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[26] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[30] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[32] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[36] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[50] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[60] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[74] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[41], w_sv[2], w_sv[107], COUPs[1], &amp_sv[0] );
      jamp_sv[12] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[26] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[36] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[50] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[54] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[56] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[60] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[72] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 607 OF 1240 ***

      // Wavefunction(s) for diagram number 607
      // (none)

      // Amplitude(s) for diagram number 607
      FFV1_0( w_sv[3], w_sv[15], w_sv[86], COUPs[1], &amp_sv[0] );
      jamp_sv[67] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[68] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[69] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[70] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[109] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[110] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[111] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[112] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 608 OF 1240 ***

      // Wavefunction(s) for diagram number 608
      // (none)

      // Amplitude(s) for diagram number 608
      FFV1_0( w_sv[14], w_sv[2], w_sv[86], COUPs[1], &amp_sv[0] );
      jamp_sv[12] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[13] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[26] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[27] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[36] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[37] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[72] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[73] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 609 OF 1240 ***

      // Wavefunction(s) for diagram number 609
      // (none)

      // Amplitude(s) for diagram number 609
      FFV1_0( w_sv[3], w_sv[112], w_sv[68], COUPs[1], &amp_sv[0] );
      jamp_sv[12] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[13] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[15] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[17] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[72] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[73] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[75] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[77] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 610 OF 1240 ***

      // Wavefunction(s) for diagram number 610
      // (none)

      // Amplitude(s) for diagram number 610
      FFV1_0( w_sv[14], w_sv[112], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[12] += +amp_sv[0];
      jamp_sv[13] -= amp_sv[0];
      jamp_sv[72] -= amp_sv[0];
      jamp_sv[73] += +amp_sv[0];

      // *** DIAGRAM 611 OF 1240 ***

      // Wavefunction(s) for diagram number 611
      // (none)

      // Amplitude(s) for diagram number 611
      FFV1_0( w_sv[99], w_sv[2], w_sv[68], COUPs[1], &amp_sv[0] );
      jamp_sv[34] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[35] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[44] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[45] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[68] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[69] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[110] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[111] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 612 OF 1240 ***

      // Wavefunction(s) for diagram number 612
      // (none)

      // Amplitude(s) for diagram number 612
      FFV1_0( w_sv[99], w_sv[15], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[69] -= amp_sv[0];
      jamp_sv[110] -= amp_sv[0];
      jamp_sv[111] += +amp_sv[0];

      // *** DIAGRAM 613 OF 1240 ***

      // Wavefunction(s) for diagram number 613
      // (none)

      // Amplitude(s) for diagram number 613
      FFV1_0( w_sv[3], w_sv[112], w_sv[57], COUPs[1], &amp_sv[0] );
      jamp_sv[12] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[13] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[15] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[17] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[72] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[73] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[75] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[77] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[112], w_sv[81], COUPs[1], &amp_sv[0] );
      jamp_sv[13] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[14] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[15] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[16] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[73] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[74] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[75] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[76] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[112], w_sv[82], COUPs[1], &amp_sv[0] );
      jamp_sv[12] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[14] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[16] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[17] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[72] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[74] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[76] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[77] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 614 OF 1240 ***

      // Wavefunction(s) for diagram number 614
      // (none)

      // Amplitude(s) for diagram number 614
      FFV1_0( w_sv[99], w_sv[2], w_sv[57], COUPs[1], &amp_sv[0] );
      jamp_sv[34] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[35] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[44] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[45] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[68] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[69] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[110] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[111] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[99], w_sv[2], w_sv[81], COUPs[1], &amp_sv[0] );
      jamp_sv[44] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[45] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[58] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[59] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[68] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[69] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[104] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[105] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[99], w_sv[2], w_sv[82], COUPs[1], &amp_sv[0] );
      jamp_sv[34] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[35] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[58] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[59] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[104] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[105] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[110] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[111] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 615 OF 1240 ***

      // Wavefunction(s) for diagram number 615
      // (none)

      // Amplitude(s) for diagram number 615
      VVV1_0( w_sv[92], w_sv[57], w_sv[8], COUPs[0], &amp_sv[0] );
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[15] += +amp_sv[0];
      jamp_sv[17] -= amp_sv[0];
      jamp_sv[34] += +amp_sv[0];
      jamp_sv[35] -= amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[45] += +amp_sv[0];
      jamp_sv[68] -= amp_sv[0];
      jamp_sv[69] += +amp_sv[0];
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[73] -= amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[77] += +amp_sv[0];
      jamp_sv[110] += +amp_sv[0];
      jamp_sv[111] -= amp_sv[0];
      VVV1_0( w_sv[92], w_sv[81], w_sv[8], COUPs[0], &amp_sv[0] );
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[14] -= amp_sv[0];
      jamp_sv[15] += +amp_sv[0];
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[45] += +amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[68] -= amp_sv[0];
      jamp_sv[69] += +amp_sv[0];
      jamp_sv[73] -= amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[105] -= amp_sv[0];
      VVV1_0( w_sv[92], w_sv[82], w_sv[8], COUPs[0], &amp_sv[0] );
      jamp_sv[12] += +amp_sv[0];
      jamp_sv[14] -= amp_sv[0];
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[72] -= amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[105] -= amp_sv[0];
      jamp_sv[110] -= amp_sv[0];
      jamp_sv[111] += +amp_sv[0];

      // *** DIAGRAM 616 OF 1240 ***

      // Wavefunction(s) for diagram number 616
      VVV1P0_1( w_sv[0], w_sv[6], COUPs[0], 0., 0., w_sv[92] );
      FFV1_2( w_sv[3], w_sv[92], COUPs[1], cIPD[0], cIPD[1], w_sv[99] );

      // Amplitude(s) for diagram number 616
      FFV1_0( w_sv[99], w_sv[87], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[32] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[33] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 617 OF 1240 ***

      // Wavefunction(s) for diagram number 617
      // (none)

      // Amplitude(s) for diagram number 617
      FFV1_0( w_sv[99], w_sv[9], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[38] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[39] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 618 OF 1240 ***

      // Wavefunction(s) for diagram number 618
      VVV1P0_1( w_sv[92], w_sv[4], COUPs[0], 0., 0., w_sv[112] );

      // Amplitude(s) for diagram number 618
      VVV1_0( w_sv[112], w_sv[34], w_sv[5], COUPs[0], &amp_sv[0] );
      jamp_sv[28] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[31] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[34] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[37] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[38] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[39] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[40] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[42] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 619 OF 1240 ***

      // Wavefunction(s) for diagram number 619
      // (none)

      // Amplitude(s) for diagram number 619
      FFV1_0( w_sv[3], w_sv[9], w_sv[112], COUPs[1], &amp_sv[0] );
      jamp_sv[37] += +amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[39] += +amp_sv[0];
      jamp_sv[40] -= amp_sv[0];

      // *** DIAGRAM 620 OF 1240 ***

      // Wavefunction(s) for diagram number 620
      VVV1P0_1( w_sv[92], w_sv[5], COUPs[0], 0., 0., w_sv[86] );

      // Amplitude(s) for diagram number 620
      VVV1_0( w_sv[86], w_sv[34], w_sv[4], COUPs[0], &amp_sv[0] );
      jamp_sv[29] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[31] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[32] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[33] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[34] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[37] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[40] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[43] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 621 OF 1240 ***

      // Wavefunction(s) for diagram number 621
      // (none)

      // Amplitude(s) for diagram number 621
      FFV1_0( w_sv[3], w_sv[87], w_sv[86], COUPs[1], &amp_sv[0] );
      jamp_sv[31] += +amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[33] += +amp_sv[0];
      jamp_sv[34] -= amp_sv[0];

      // *** DIAGRAM 622 OF 1240 ***

      // Wavefunction(s) for diagram number 622
      VVVV1P0_1( w_sv[92], w_sv[4], w_sv[5], COUPs[2], 0., 0., w_sv[107] );
      VVVV3P0_1( w_sv[92], w_sv[4], w_sv[5], COUPs[2], 0., 0., w_sv[95] );
      VVVV4P0_1( w_sv[92], w_sv[4], w_sv[5], COUPs[2], 0., 0., w_sv[105] );

      // Amplitude(s) for diagram number 622
      FFV1_0( w_sv[3], w_sv[77], w_sv[107], COUPs[1], &amp_sv[0] );
      jamp_sv[28] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[29] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[32] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[33] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[38] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[39] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[42] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[43] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[77], w_sv[95], COUPs[1], &amp_sv[0] );
      jamp_sv[29] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[31] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[32] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[33] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[34] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[37] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[40] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[43] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[77], w_sv[105], COUPs[1], &amp_sv[0] );
      jamp_sv[28] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[31] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[34] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[37] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[38] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[39] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[40] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[42] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 623 OF 1240 ***

      // Wavefunction(s) for diagram number 623
      FFV1_1( w_sv[77], w_sv[92], COUPs[1], cIPD[0], cIPD[1], w_sv[102] );

      // Amplitude(s) for diagram number 623
      FFV1_0( w_sv[46], w_sv[102], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[29] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[43] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 624 OF 1240 ***

      // Wavefunction(s) for diagram number 624
      FFV1_2( w_sv[46], w_sv[92], COUPs[1], cIPD[0], cIPD[1], w_sv[88] );

      // Amplitude(s) for diagram number 624
      FFV1_0( w_sv[88], w_sv[77], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[37] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[40] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 625 OF 1240 ***

      // Wavefunction(s) for diagram number 625
      // (none)

      // Amplitude(s) for diagram number 625
      FFV1_0( w_sv[46], w_sv[77], w_sv[86], COUPs[1], &amp_sv[0] );
      jamp_sv[29] += +amp_sv[0];
      jamp_sv[37] -= amp_sv[0];
      jamp_sv[40] += +amp_sv[0];
      jamp_sv[43] -= amp_sv[0];

      // *** DIAGRAM 626 OF 1240 ***

      // Wavefunction(s) for diagram number 626
      // (none)

      // Amplitude(s) for diagram number 626
      FFV1_0( w_sv[38], w_sv[102], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[28] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[42] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 627 OF 1240 ***

      // Wavefunction(s) for diagram number 627
      FFV1_2( w_sv[38], w_sv[92], COUPs[1], cIPD[0], cIPD[1], w_sv[90] );

      // Amplitude(s) for diagram number 627
      FFV1_0( w_sv[90], w_sv[77], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[31] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[34] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 628 OF 1240 ***

      // Wavefunction(s) for diagram number 628
      // (none)

      // Amplitude(s) for diagram number 628
      FFV1_0( w_sv[38], w_sv[77], w_sv[112], COUPs[1], &amp_sv[0] );
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[31] -= amp_sv[0];
      jamp_sv[34] += +amp_sv[0];
      jamp_sv[42] -= amp_sv[0];

      // *** DIAGRAM 629 OF 1240 ***

      // Wavefunction(s) for diagram number 629
      // (none)

      // Amplitude(s) for diagram number 629
      FFV1_0( w_sv[3], w_sv[102], w_sv[24], COUPs[1], &amp_sv[0] );
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[29] -= amp_sv[0];
      jamp_sv[42] -= amp_sv[0];
      jamp_sv[43] += +amp_sv[0];

      // *** DIAGRAM 630 OF 1240 ***

      // Wavefunction(s) for diagram number 630
      // (none)

      // Amplitude(s) for diagram number 630
      FFV1_0( w_sv[99], w_sv[77], w_sv[24], COUPs[1], &amp_sv[0] );
      jamp_sv[32] += +amp_sv[0];
      jamp_sv[33] -= amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[39] += +amp_sv[0];

      // *** DIAGRAM 631 OF 1240 ***

      // Wavefunction(s) for diagram number 631
      VVV1P0_1( w_sv[92], w_sv[24], COUPs[0], 0., 0., w_sv[102] );

      // Amplitude(s) for diagram number 631
      FFV1_0( w_sv[3], w_sv[77], w_sv[102], COUPs[1], &amp_sv[0] );
      jamp_sv[28] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[29] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[32] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[33] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[38] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[39] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[42] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[43] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 632 OF 1240 ***

      // Wavefunction(s) for diagram number 632
      FFV1_1( w_sv[2], w_sv[92], COUPs[1], cIPD[0], cIPD[1], w_sv[96] );

      // Amplitude(s) for diagram number 632
      FFV1_0( w_sv[56], w_sv[96], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[23] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[101] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 633 OF 1240 ***

      // Wavefunction(s) for diagram number 633
      // (none)

      // Amplitude(s) for diagram number 633
      FFV1_0( w_sv[22], w_sv[96], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[21] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[99] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 634 OF 1240 ***

      // Wavefunction(s) for diagram number 634
      // (none)

      // Amplitude(s) for diagram number 634
      VVV1_0( w_sv[112], w_sv[103], w_sv[5], COUPs[0], &amp_sv[0] );
      jamp_sv[21] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[53] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[67] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[77] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[85] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[88] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[91] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[99] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 635 OF 1240 ***

      // Wavefunction(s) for diagram number 635
      // (none)

      // Amplitude(s) for diagram number 635
      FFV1_0( w_sv[22], w_sv[2], w_sv[112], COUPs[1], &amp_sv[0] );
      jamp_sv[21] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[67] += +amp_sv[0];
      jamp_sv[99] -= amp_sv[0];

      // *** DIAGRAM 636 OF 1240 ***

      // Wavefunction(s) for diagram number 636
      // (none)

      // Amplitude(s) for diagram number 636
      VVV1_0( w_sv[86], w_sv[103], w_sv[4], COUPs[0], &amp_sv[0] );
      jamp_sv[23] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[53] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[61] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[64] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[67] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[77] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[91] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[101] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 637 OF 1240 ***

      // Wavefunction(s) for diagram number 637
      // (none)

      // Amplitude(s) for diagram number 637
      FFV1_0( w_sv[56], w_sv[2], w_sv[86], COUPs[1], &amp_sv[0] );
      jamp_sv[23] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[91] += +amp_sv[0];
      jamp_sv[101] -= amp_sv[0];

      // *** DIAGRAM 638 OF 1240 ***

      // Wavefunction(s) for diagram number 638
      // (none)

      // Amplitude(s) for diagram number 638
      FFV1_0( w_sv[52], w_sv[2], w_sv[107], COUPs[1], &amp_sv[0] );
      jamp_sv[21] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[23] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[61] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[64] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[85] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[88] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[99] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[101] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[52], w_sv[2], w_sv[95], COUPs[1], &amp_sv[0] );
      jamp_sv[23] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[53] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[61] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[64] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[67] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[77] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[91] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[101] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[52], w_sv[2], w_sv[105], COUPs[1], &amp_sv[0] );
      jamp_sv[21] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[53] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[67] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[77] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[85] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[88] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[91] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[99] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 639 OF 1240 ***

      // Wavefunction(s) for diagram number 639
      FFV1_2( w_sv[52], w_sv[92], COUPs[1], cIPD[0], cIPD[1], w_sv[104] );

      // Amplitude(s) for diagram number 639
      FFV1_0( w_sv[104], w_sv[33], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[61] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[64] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 640 OF 1240 ***

      // Wavefunction(s) for diagram number 640
      FFV1_1( w_sv[33], w_sv[92], COUPs[1], cIPD[0], cIPD[1], w_sv[114] );

      // Amplitude(s) for diagram number 640
      FFV1_0( w_sv[52], w_sv[114], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[53] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[67] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 641 OF 1240 ***

      // Wavefunction(s) for diagram number 641
      // (none)

      // Amplitude(s) for diagram number 641
      FFV1_0( w_sv[52], w_sv[33], w_sv[86], COUPs[1], &amp_sv[0] );
      jamp_sv[53] += +amp_sv[0];
      jamp_sv[61] -= amp_sv[0];
      jamp_sv[64] += +amp_sv[0];
      jamp_sv[67] -= amp_sv[0];

      // *** DIAGRAM 642 OF 1240 ***

      // Wavefunction(s) for diagram number 642
      // (none)

      // Amplitude(s) for diagram number 642
      FFV1_0( w_sv[104], w_sv[39], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[85] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[88] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 643 OF 1240 ***

      // Wavefunction(s) for diagram number 643
      FFV1_1( w_sv[39], w_sv[92], COUPs[1], cIPD[0], cIPD[1], w_sv[106] );

      // Amplitude(s) for diagram number 643
      FFV1_0( w_sv[52], w_sv[106], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[77] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[91] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 644 OF 1240 ***

      // Wavefunction(s) for diagram number 644
      // (none)

      // Amplitude(s) for diagram number 644
      FFV1_0( w_sv[52], w_sv[39], w_sv[112], COUPs[1], &amp_sv[0] );
      jamp_sv[77] += +amp_sv[0];
      jamp_sv[85] -= amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[91] -= amp_sv[0];

      // *** DIAGRAM 645 OF 1240 ***

      // Wavefunction(s) for diagram number 645
      // (none)

      // Amplitude(s) for diagram number 645
      FFV1_0( w_sv[104], w_sv[2], w_sv[24], COUPs[1], &amp_sv[0] );
      jamp_sv[61] += +amp_sv[0];
      jamp_sv[64] -= amp_sv[0];
      jamp_sv[85] -= amp_sv[0];
      jamp_sv[88] += +amp_sv[0];

      // *** DIAGRAM 646 OF 1240 ***

      // Wavefunction(s) for diagram number 646
      // (none)

      // Amplitude(s) for diagram number 646
      FFV1_0( w_sv[52], w_sv[96], w_sv[24], COUPs[1], &amp_sv[0] );
      jamp_sv[21] += +amp_sv[0];
      jamp_sv[23] -= amp_sv[0];
      jamp_sv[99] -= amp_sv[0];
      jamp_sv[101] += +amp_sv[0];

      // *** DIAGRAM 647 OF 1240 ***

      // Wavefunction(s) for diagram number 647
      // (none)

      // Amplitude(s) for diagram number 647
      FFV1_0( w_sv[52], w_sv[2], w_sv[102], COUPs[1], &amp_sv[0] );
      jamp_sv[21] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[23] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[61] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[64] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[85] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[88] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[99] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[101] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 648 OF 1240 ***

      // Wavefunction(s) for diagram number 648
      // (none)

      // Amplitude(s) for diagram number 648
      FFV1_0( w_sv[65], w_sv[96], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[22] += +amp_sv[0];
      jamp_sv[23] -= amp_sv[0];
      jamp_sv[100] -= amp_sv[0];
      jamp_sv[101] += +amp_sv[0];

      // *** DIAGRAM 649 OF 1240 ***

      // Wavefunction(s) for diagram number 649
      // (none)

      // Amplitude(s) for diagram number 649
      FFV1_0( w_sv[3], w_sv[96], w_sv[63], COUPs[1], &amp_sv[0] );
      jamp_sv[18] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[20] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[22] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[23] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[96] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[98] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[100] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[101] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 650 OF 1240 ***

      // Wavefunction(s) for diagram number 650
      // (none)

      // Amplitude(s) for diagram number 650
      FFV1_0( w_sv[99], w_sv[93], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[32] += +amp_sv[0];
      jamp_sv[33] -= amp_sv[0];
      jamp_sv[56] -= amp_sv[0];
      jamp_sv[57] += +amp_sv[0];

      // *** DIAGRAM 651 OF 1240 ***

      // Wavefunction(s) for diagram number 651
      // (none)

      // Amplitude(s) for diagram number 651
      FFV1_0( w_sv[99], w_sv[2], w_sv[63], COUPs[1], &amp_sv[0] );
      jamp_sv[32] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[33] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[56] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[57] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[80] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[81] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[86] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[87] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 652 OF 1240 ***

      // Wavefunction(s) for diagram number 652
      // (none)

      // Amplitude(s) for diagram number 652
      FFV1_0( w_sv[3], w_sv[93], w_sv[86], COUPs[1], &amp_sv[0] );
      jamp_sv[31] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[32] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[33] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[34] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[55] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[56] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[57] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[58] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 653 OF 1240 ***

      // Wavefunction(s) for diagram number 653
      // (none)

      // Amplitude(s) for diagram number 653
      FFV1_0( w_sv[65], w_sv[2], w_sv[86], COUPs[1], &amp_sv[0] );
      jamp_sv[22] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[23] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[76] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[77] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[90] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[91] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[100] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[101] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 654 OF 1240 ***

      // Wavefunction(s) for diagram number 654
      // (none)

      // Amplitude(s) for diagram number 654
      VVVV1_0( w_sv[92], w_sv[61], w_sv[8], w_sv[5], COUPs[2], &amp_sv[0] );
      jamp_sv[18] += +amp_sv[0];
      jamp_sv[20] -= amp_sv[0];
      jamp_sv[31] -= amp_sv[0];
      jamp_sv[34] += +amp_sv[0];
      jamp_sv[55] += +amp_sv[0];
      jamp_sv[58] -= amp_sv[0];
      jamp_sv[76] -= amp_sv[0];
      jamp_sv[77] += +amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[81] -= amp_sv[0];
      jamp_sv[86] -= amp_sv[0];
      jamp_sv[87] += +amp_sv[0];
      jamp_sv[90] += +amp_sv[0];
      jamp_sv[91] -= amp_sv[0];
      jamp_sv[96] -= amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      VVVV3_0( w_sv[92], w_sv[61], w_sv[8], w_sv[5], COUPs[2], &amp_sv[0] );
      jamp_sv[18] += +amp_sv[0];
      jamp_sv[20] -= amp_sv[0];
      jamp_sv[22] -= amp_sv[0];
      jamp_sv[23] += +amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[33] += +amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[57] -= amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[81] -= amp_sv[0];
      jamp_sv[86] -= amp_sv[0];
      jamp_sv[87] += +amp_sv[0];
      jamp_sv[96] -= amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      jamp_sv[101] -= amp_sv[0];
      VVVV4_0( w_sv[92], w_sv[61], w_sv[8], w_sv[5], COUPs[2], &amp_sv[0] );
      jamp_sv[22] -= amp_sv[0];
      jamp_sv[23] += +amp_sv[0];
      jamp_sv[31] += +amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[33] += +amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[57] -= amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[91] += +amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      jamp_sv[101] -= amp_sv[0];

      // *** DIAGRAM 655 OF 1240 ***

      // Wavefunction(s) for diagram number 655
      VVV1P0_1( w_sv[92], w_sv[61], COUPs[0], 0., 0., w_sv[104] );

      // Amplitude(s) for diagram number 655
      VVV1_0( w_sv[8], w_sv[5], w_sv[104], COUPs[0], &amp_sv[0] );
      jamp_sv[18] += +amp_sv[0];
      jamp_sv[20] -= amp_sv[0];
      jamp_sv[31] -= amp_sv[0];
      jamp_sv[34] += +amp_sv[0];
      jamp_sv[55] += +amp_sv[0];
      jamp_sv[58] -= amp_sv[0];
      jamp_sv[76] -= amp_sv[0];
      jamp_sv[77] += +amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[81] -= amp_sv[0];
      jamp_sv[86] -= amp_sv[0];
      jamp_sv[87] += +amp_sv[0];
      jamp_sv[90] += +amp_sv[0];
      jamp_sv[91] -= amp_sv[0];
      jamp_sv[96] -= amp_sv[0];
      jamp_sv[98] += +amp_sv[0];

      // *** DIAGRAM 656 OF 1240 ***

      // Wavefunction(s) for diagram number 656
      VVV1P0_1( w_sv[92], w_sv[8], COUPs[0], 0., 0., w_sv[113] );

      // Amplitude(s) for diagram number 656
      VVV1_0( w_sv[61], w_sv[5], w_sv[113], COUPs[0], &amp_sv[0] );
      jamp_sv[18] += +amp_sv[0];
      jamp_sv[20] -= amp_sv[0];
      jamp_sv[22] -= amp_sv[0];
      jamp_sv[23] += +amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[33] += +amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[57] -= amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[81] -= amp_sv[0];
      jamp_sv[86] -= amp_sv[0];
      jamp_sv[87] += +amp_sv[0];
      jamp_sv[96] -= amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      jamp_sv[101] -= amp_sv[0];

      // *** DIAGRAM 657 OF 1240 ***

      // Wavefunction(s) for diagram number 657
      // (none)

      // Amplitude(s) for diagram number 657
      VVV1_0( w_sv[61], w_sv[8], w_sv[86], COUPs[0], &amp_sv[0] );
      jamp_sv[22] -= amp_sv[0];
      jamp_sv[23] += +amp_sv[0];
      jamp_sv[31] += +amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[33] += +amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[57] -= amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[91] += +amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      jamp_sv[101] -= amp_sv[0];

      // *** DIAGRAM 658 OF 1240 ***

      // Wavefunction(s) for diagram number 658
      // (none)

      // Amplitude(s) for diagram number 658
      FFV1_0( w_sv[3], w_sv[39], w_sv[104], COUPs[1], &amp_sv[0] );
      jamp_sv[76] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[77] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[80] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[81] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[86] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[87] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[90] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[91] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 659 OF 1240 ***

      // Wavefunction(s) for diagram number 659
      // (none)

      // Amplitude(s) for diagram number 659
      FFV1_0( w_sv[3], w_sv[106], w_sv[61], COUPs[1], &amp_sv[0] );
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[91] += +amp_sv[0];

      // *** DIAGRAM 660 OF 1240 ***

      // Wavefunction(s) for diagram number 660
      // (none)

      // Amplitude(s) for diagram number 660
      FFV1_0( w_sv[99], w_sv[39], w_sv[61], COUPs[1], &amp_sv[0] );
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[81] -= amp_sv[0];
      jamp_sv[86] -= amp_sv[0];
      jamp_sv[87] += +amp_sv[0];

      // *** DIAGRAM 661 OF 1240 ***

      // Wavefunction(s) for diagram number 661
      // (none)

      // Amplitude(s) for diagram number 661
      FFV1_0( w_sv[38], w_sv[2], w_sv[104], COUPs[1], &amp_sv[0] );
      jamp_sv[18] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[20] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[31] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[34] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[55] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[58] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[96] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[98] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 662 OF 1240 ***

      // Wavefunction(s) for diagram number 662
      // (none)

      // Amplitude(s) for diagram number 662
      FFV1_0( w_sv[38], w_sv[96], w_sv[61], COUPs[1], &amp_sv[0] );
      jamp_sv[18] += +amp_sv[0];
      jamp_sv[20] -= amp_sv[0];
      jamp_sv[96] -= amp_sv[0];
      jamp_sv[98] += +amp_sv[0];

      // *** DIAGRAM 663 OF 1240 ***

      // Wavefunction(s) for diagram number 663
      // (none)

      // Amplitude(s) for diagram number 663
      FFV1_0( w_sv[90], w_sv[2], w_sv[61], COUPs[1], &amp_sv[0] );
      jamp_sv[31] += +amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[58] += +amp_sv[0];

      // *** DIAGRAM 664 OF 1240 ***

      // Wavefunction(s) for diagram number 664
      // (none)

      // Amplitude(s) for diagram number 664
      FFV1_0( w_sv[71], w_sv[96], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[20] += +amp_sv[0];
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[98] -= amp_sv[0];
      jamp_sv[99] += +amp_sv[0];

      // *** DIAGRAM 665 OF 1240 ***

      // Wavefunction(s) for diagram number 665
      // (none)

      // Amplitude(s) for diagram number 665
      FFV1_0( w_sv[3], w_sv[96], w_sv[69], COUPs[1], &amp_sv[0] );
      jamp_sv[19] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[20] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[21] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[22] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[97] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[98] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[99] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[100] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 666 OF 1240 ***

      // Wavefunction(s) for diagram number 666
      // (none)

      // Amplitude(s) for diagram number 666
      FFV1_0( w_sv[99], w_sv[94], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[38] += +amp_sv[0];
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[80] -= amp_sv[0];
      jamp_sv[81] += +amp_sv[0];

      // *** DIAGRAM 667 OF 1240 ***

      // Wavefunction(s) for diagram number 667
      // (none)

      // Amplitude(s) for diagram number 667
      FFV1_0( w_sv[99], w_sv[2], w_sv[69], COUPs[1], &amp_sv[0] );
      jamp_sv[38] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[39] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[56] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[57] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[62] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[63] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[80] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[81] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 668 OF 1240 ***

      // Wavefunction(s) for diagram number 668
      // (none)

      // Amplitude(s) for diagram number 668
      FFV1_0( w_sv[3], w_sv[94], w_sv[112], COUPs[1], &amp_sv[0] );
      jamp_sv[37] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[38] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[39] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[40] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[79] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[80] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[81] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[82] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 669 OF 1240 ***

      // Wavefunction(s) for diagram number 669
      // (none)

      // Amplitude(s) for diagram number 669
      FFV1_0( w_sv[71], w_sv[2], w_sv[112], COUPs[1], &amp_sv[0] );
      jamp_sv[20] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[21] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[52] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[53] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[66] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[67] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[98] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[99] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 670 OF 1240 ***

      // Wavefunction(s) for diagram number 670
      // (none)

      // Amplitude(s) for diagram number 670
      VVVV1_0( w_sv[92], w_sv[66], w_sv[8], w_sv[4], COUPs[2], &amp_sv[0] );
      jamp_sv[19] += +amp_sv[0];
      jamp_sv[22] -= amp_sv[0];
      jamp_sv[37] -= amp_sv[0];
      jamp_sv[40] += +amp_sv[0];
      jamp_sv[52] -= amp_sv[0];
      jamp_sv[53] += +amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[57] -= amp_sv[0];
      jamp_sv[62] -= amp_sv[0];
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[66] += +amp_sv[0];
      jamp_sv[67] -= amp_sv[0];
      jamp_sv[79] += +amp_sv[0];
      jamp_sv[82] -= amp_sv[0];
      jamp_sv[97] -= amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      VVVV3_0( w_sv[92], w_sv[66], w_sv[8], w_sv[4], COUPs[2], &amp_sv[0] );
      jamp_sv[19] += +amp_sv[0];
      jamp_sv[20] -= amp_sv[0];
      jamp_sv[21] += +amp_sv[0];
      jamp_sv[22] -= amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[39] += +amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[57] -= amp_sv[0];
      jamp_sv[62] -= amp_sv[0];
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[81] -= amp_sv[0];
      jamp_sv[97] -= amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      jamp_sv[99] -= amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      VVVV4_0( w_sv[92], w_sv[66], w_sv[8], w_sv[4], COUPs[2], &amp_sv[0] );
      jamp_sv[20] -= amp_sv[0];
      jamp_sv[21] += +amp_sv[0];
      jamp_sv[37] += +amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[39] += +amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[67] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[81] -= amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      jamp_sv[99] -= amp_sv[0];

      // *** DIAGRAM 671 OF 1240 ***

      // Wavefunction(s) for diagram number 671
      VVV1P0_1( w_sv[92], w_sv[66], COUPs[0], 0., 0., w_sv[104] );

      // Amplitude(s) for diagram number 671
      VVV1_0( w_sv[8], w_sv[4], w_sv[104], COUPs[0], &amp_sv[0] );
      jamp_sv[19] += +amp_sv[0];
      jamp_sv[22] -= amp_sv[0];
      jamp_sv[37] -= amp_sv[0];
      jamp_sv[40] += +amp_sv[0];
      jamp_sv[52] -= amp_sv[0];
      jamp_sv[53] += +amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[57] -= amp_sv[0];
      jamp_sv[62] -= amp_sv[0];
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[66] += +amp_sv[0];
      jamp_sv[67] -= amp_sv[0];
      jamp_sv[79] += +amp_sv[0];
      jamp_sv[82] -= amp_sv[0];
      jamp_sv[97] -= amp_sv[0];
      jamp_sv[100] += +amp_sv[0];

      // *** DIAGRAM 672 OF 1240 ***

      // Wavefunction(s) for diagram number 672
      // (none)

      // Amplitude(s) for diagram number 672
      VVV1_0( w_sv[66], w_sv[4], w_sv[113], COUPs[0], &amp_sv[0] );
      jamp_sv[19] += +amp_sv[0];
      jamp_sv[20] -= amp_sv[0];
      jamp_sv[21] += +amp_sv[0];
      jamp_sv[22] -= amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[39] += +amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[57] -= amp_sv[0];
      jamp_sv[62] -= amp_sv[0];
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[81] -= amp_sv[0];
      jamp_sv[97] -= amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      jamp_sv[99] -= amp_sv[0];
      jamp_sv[100] += +amp_sv[0];

      // *** DIAGRAM 673 OF 1240 ***

      // Wavefunction(s) for diagram number 673
      // (none)

      // Amplitude(s) for diagram number 673
      VVV1_0( w_sv[66], w_sv[8], w_sv[112], COUPs[0], &amp_sv[0] );
      jamp_sv[20] -= amp_sv[0];
      jamp_sv[21] += +amp_sv[0];
      jamp_sv[37] += +amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[39] += +amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[67] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[81] -= amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      jamp_sv[99] -= amp_sv[0];

      // *** DIAGRAM 674 OF 1240 ***

      // Wavefunction(s) for diagram number 674
      // (none)

      // Amplitude(s) for diagram number 674
      FFV1_0( w_sv[3], w_sv[33], w_sv[104], COUPs[1], &amp_sv[0] );
      jamp_sv[52] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[53] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[56] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[57] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[62] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[63] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[66] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[67] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 675 OF 1240 ***

      // Wavefunction(s) for diagram number 675
      // (none)

      // Amplitude(s) for diagram number 675
      FFV1_0( w_sv[3], w_sv[114], w_sv[66], COUPs[1], &amp_sv[0] );
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[67] += +amp_sv[0];

      // *** DIAGRAM 676 OF 1240 ***

      // Wavefunction(s) for diagram number 676
      // (none)

      // Amplitude(s) for diagram number 676
      FFV1_0( w_sv[99], w_sv[33], w_sv[66], COUPs[1], &amp_sv[0] );
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[57] -= amp_sv[0];
      jamp_sv[62] -= amp_sv[0];
      jamp_sv[63] += +amp_sv[0];

      // *** DIAGRAM 677 OF 1240 ***

      // Wavefunction(s) for diagram number 677
      // (none)

      // Amplitude(s) for diagram number 677
      FFV1_0( w_sv[46], w_sv[2], w_sv[104], COUPs[1], &amp_sv[0] );
      jamp_sv[19] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[22] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[37] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[40] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[79] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[82] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[97] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[100] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 678 OF 1240 ***

      // Wavefunction(s) for diagram number 678
      // (none)

      // Amplitude(s) for diagram number 678
      FFV1_0( w_sv[46], w_sv[96], w_sv[66], COUPs[1], &amp_sv[0] );
      jamp_sv[19] += +amp_sv[0];
      jamp_sv[22] -= amp_sv[0];
      jamp_sv[97] -= amp_sv[0];
      jamp_sv[100] += +amp_sv[0];

      // *** DIAGRAM 679 OF 1240 ***

      // Wavefunction(s) for diagram number 679
      // (none)

      // Amplitude(s) for diagram number 679
      FFV1_0( w_sv[88], w_sv[2], w_sv[66], COUPs[1], &amp_sv[0] );
      jamp_sv[37] += +amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[82] += +amp_sv[0];

      // *** DIAGRAM 680 OF 1240 ***

      // Wavefunction(s) for diagram number 680
      VVV1P0_1( w_sv[92], w_sv[1], COUPs[0], 0., 0., w_sv[104] );

      // Amplitude(s) for diagram number 680
      VVV1_0( w_sv[104], w_sv[13], w_sv[5], COUPs[0], &amp_sv[0] );
      jamp_sv[19] -= amp_sv[0];
      jamp_sv[29] += +amp_sv[0];
      jamp_sv[43] -= amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[61] -= amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[63] -= amp_sv[0];
      jamp_sv[64] += +amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[97] += +amp_sv[0];

      // *** DIAGRAM 681 OF 1240 ***

      // Wavefunction(s) for diagram number 681
      // (none)

      // Amplitude(s) for diagram number 681
      VVV1_0( w_sv[104], w_sv[10], w_sv[4], COUPs[0], &amp_sv[0] );
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[42] -= amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[85] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[96] += +amp_sv[0];

      // *** DIAGRAM 682 OF 1240 ***

      // Wavefunction(s) for diagram number 682
      // (none)

      // Amplitude(s) for diagram number 682
      VVVV1_0( w_sv[8], w_sv[4], w_sv[5], w_sv[104], COUPs[2], &amp_sv[0] );
      jamp_sv[19] -= amp_sv[0];
      jamp_sv[29] += +amp_sv[0];
      jamp_sv[43] -= amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[61] -= amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[63] -= amp_sv[0];
      jamp_sv[64] += +amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[97] += +amp_sv[0];
      VVVV3_0( w_sv[8], w_sv[4], w_sv[5], w_sv[104], COUPs[2], &amp_sv[0] );
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[42] -= amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[85] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[96] += +amp_sv[0];
      VVVV4_0( w_sv[8], w_sv[4], w_sv[5], w_sv[104], COUPs[2], &amp_sv[0] );
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[19] += +amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[29] -= amp_sv[0];
      jamp_sv[42] -= amp_sv[0];
      jamp_sv[43] += +amp_sv[0];
      jamp_sv[61] += +amp_sv[0];
      jamp_sv[62] -= amp_sv[0];
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[64] -= amp_sv[0];
      jamp_sv[85] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[97] -= amp_sv[0];

      // *** DIAGRAM 683 OF 1240 ***

      // Wavefunction(s) for diagram number 683
      // (none)

      // Amplitude(s) for diagram number 683
      VVV1_0( w_sv[112], w_sv[108], w_sv[5], COUPs[0], &amp_sv[0] );
      jamp_sv[21] += +amp_sv[0];
      jamp_sv[28] -= amp_sv[0];
      jamp_sv[31] += +amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[37] += +amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[39] += +amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[42] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[67] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[85] += +amp_sv[0];
      jamp_sv[88] -= amp_sv[0];
      jamp_sv[91] += +amp_sv[0];
      jamp_sv[99] -= amp_sv[0];

      // *** DIAGRAM 684 OF 1240 ***

      // Wavefunction(s) for diagram number 684
      // (none)

      // Amplitude(s) for diagram number 684
      VVV1_0( w_sv[112], w_sv[1], w_sv[10], COUPs[0], &amp_sv[0] );
      jamp_sv[20] += +amp_sv[0];
      jamp_sv[28] -= amp_sv[0];
      jamp_sv[31] += +amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[42] += +amp_sv[0];
      jamp_sv[52] -= amp_sv[0];
      jamp_sv[66] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[79] += +amp_sv[0];
      jamp_sv[80] -= amp_sv[0];
      jamp_sv[81] += +amp_sv[0];
      jamp_sv[82] -= amp_sv[0];
      jamp_sv[85] += +amp_sv[0];
      jamp_sv[88] -= amp_sv[0];
      jamp_sv[91] += +amp_sv[0];
      jamp_sv[98] -= amp_sv[0];

      // *** DIAGRAM 685 OF 1240 ***

      // Wavefunction(s) for diagram number 685
      // (none)

      // Amplitude(s) for diagram number 685
      VVVV1_0( w_sv[1], w_sv[8], w_sv[5], w_sv[112], COUPs[2], &amp_sv[0] );
      jamp_sv[21] += +amp_sv[0];
      jamp_sv[28] -= amp_sv[0];
      jamp_sv[31] += +amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[37] += +amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[39] += +amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[42] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[67] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[85] += +amp_sv[0];
      jamp_sv[88] -= amp_sv[0];
      jamp_sv[91] += +amp_sv[0];
      jamp_sv[99] -= amp_sv[0];
      VVVV3_0( w_sv[1], w_sv[8], w_sv[5], w_sv[112], COUPs[2], &amp_sv[0] );
      jamp_sv[20] -= amp_sv[0];
      jamp_sv[21] += +amp_sv[0];
      jamp_sv[37] += +amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[39] += +amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[67] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[81] -= amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      jamp_sv[99] -= amp_sv[0];
      VVVV4_0( w_sv[1], w_sv[8], w_sv[5], w_sv[112], COUPs[2], &amp_sv[0] );
      jamp_sv[20] -= amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[31] -= amp_sv[0];
      jamp_sv[34] += +amp_sv[0];
      jamp_sv[42] -= amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[77] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[81] -= amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[85] -= amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[91] -= amp_sv[0];
      jamp_sv[98] += +amp_sv[0];

      // *** DIAGRAM 686 OF 1240 ***

      // Wavefunction(s) for diagram number 686
      // (none)

      // Amplitude(s) for diagram number 686
      VVV1_0( w_sv[86], w_sv[108], w_sv[4], COUPs[0], &amp_sv[0] );
      jamp_sv[23] += +amp_sv[0];
      jamp_sv[29] -= amp_sv[0];
      jamp_sv[31] += +amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[33] += +amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[37] += +amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[43] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[61] += +amp_sv[0];
      jamp_sv[64] -= amp_sv[0];
      jamp_sv[67] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[91] += +amp_sv[0];
      jamp_sv[101] -= amp_sv[0];

      // *** DIAGRAM 687 OF 1240 ***

      // Wavefunction(s) for diagram number 687
      // (none)

      // Amplitude(s) for diagram number 687
      VVV1_0( w_sv[86], w_sv[1], w_sv[13], COUPs[0], &amp_sv[0] );
      jamp_sv[22] += +amp_sv[0];
      jamp_sv[29] -= amp_sv[0];
      jamp_sv[37] += +amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[43] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[55] += +amp_sv[0];
      jamp_sv[56] -= amp_sv[0];
      jamp_sv[57] += +amp_sv[0];
      jamp_sv[58] -= amp_sv[0];
      jamp_sv[61] += +amp_sv[0];
      jamp_sv[64] -= amp_sv[0];
      jamp_sv[67] += +amp_sv[0];
      jamp_sv[76] -= amp_sv[0];
      jamp_sv[90] += +amp_sv[0];
      jamp_sv[100] -= amp_sv[0];

      // *** DIAGRAM 688 OF 1240 ***

      // Wavefunction(s) for diagram number 688
      // (none)

      // Amplitude(s) for diagram number 688
      VVVV1_0( w_sv[1], w_sv[8], w_sv[4], w_sv[86], COUPs[2], &amp_sv[0] );
      jamp_sv[23] += +amp_sv[0];
      jamp_sv[29] -= amp_sv[0];
      jamp_sv[31] += +amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[33] += +amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[37] += +amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[43] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[61] += +amp_sv[0];
      jamp_sv[64] -= amp_sv[0];
      jamp_sv[67] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[91] += +amp_sv[0];
      jamp_sv[101] -= amp_sv[0];
      VVVV3_0( w_sv[1], w_sv[8], w_sv[4], w_sv[86], COUPs[2], &amp_sv[0] );
      jamp_sv[22] -= amp_sv[0];
      jamp_sv[23] += +amp_sv[0];
      jamp_sv[31] += +amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[33] += +amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[57] -= amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[91] += +amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      jamp_sv[101] -= amp_sv[0];
      VVVV4_0( w_sv[1], w_sv[8], w_sv[4], w_sv[86], COUPs[2], &amp_sv[0] );
      jamp_sv[22] -= amp_sv[0];
      jamp_sv[29] += +amp_sv[0];
      jamp_sv[37] -= amp_sv[0];
      jamp_sv[40] += +amp_sv[0];
      jamp_sv[43] -= amp_sv[0];
      jamp_sv[53] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[57] -= amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[61] -= amp_sv[0];
      jamp_sv[64] += +amp_sv[0];
      jamp_sv[67] -= amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[100] += +amp_sv[0];

      // *** DIAGRAM 689 OF 1240 ***

      // Wavefunction(s) for diagram number 689
      VVVV1P0_1( w_sv[92], w_sv[1], w_sv[4], COUPs[2], 0., 0., w_sv[98] );
      VVVV3P0_1( w_sv[92], w_sv[1], w_sv[4], COUPs[2], 0., 0., w_sv[62] );
      VVVV4P0_1( w_sv[92], w_sv[1], w_sv[4], COUPs[2], 0., 0., w_sv[101] );

      // Amplitude(s) for diagram number 689
      VVV1_0( w_sv[8], w_sv[5], w_sv[98], COUPs[0], &amp_sv[0] );
      jamp_sv[18] += +amp_sv[0];
      jamp_sv[20] -= amp_sv[0];
      jamp_sv[31] -= amp_sv[0];
      jamp_sv[34] += +amp_sv[0];
      jamp_sv[55] += +amp_sv[0];
      jamp_sv[58] -= amp_sv[0];
      jamp_sv[76] -= amp_sv[0];
      jamp_sv[77] += +amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[81] -= amp_sv[0];
      jamp_sv[86] -= amp_sv[0];
      jamp_sv[87] += +amp_sv[0];
      jamp_sv[90] += +amp_sv[0];
      jamp_sv[91] -= amp_sv[0];
      jamp_sv[96] -= amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      VVV1_0( w_sv[8], w_sv[5], w_sv[62], COUPs[0], &amp_sv[0] );
      jamp_sv[20] -= amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[31] -= amp_sv[0];
      jamp_sv[34] += +amp_sv[0];
      jamp_sv[42] -= amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[77] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[81] -= amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[85] -= amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[91] -= amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      VVV1_0( w_sv[8], w_sv[5], w_sv[101], COUPs[0], &amp_sv[0] );
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[42] -= amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[85] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[96] += +amp_sv[0];

      // *** DIAGRAM 690 OF 1240 ***

      // Wavefunction(s) for diagram number 690
      VVVV1P0_1( w_sv[92], w_sv[1], w_sv[5], COUPs[2], 0., 0., w_sv[109] );
      VVVV3P0_1( w_sv[92], w_sv[1], w_sv[5], COUPs[2], 0., 0., w_sv[110] );
      VVVV4P0_1( w_sv[92], w_sv[1], w_sv[5], COUPs[2], 0., 0., w_sv[111] );

      // Amplitude(s) for diagram number 690
      VVV1_0( w_sv[8], w_sv[4], w_sv[109], COUPs[0], &amp_sv[0] );
      jamp_sv[19] += +amp_sv[0];
      jamp_sv[22] -= amp_sv[0];
      jamp_sv[37] -= amp_sv[0];
      jamp_sv[40] += +amp_sv[0];
      jamp_sv[52] -= amp_sv[0];
      jamp_sv[53] += +amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[57] -= amp_sv[0];
      jamp_sv[62] -= amp_sv[0];
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[66] += +amp_sv[0];
      jamp_sv[67] -= amp_sv[0];
      jamp_sv[79] += +amp_sv[0];
      jamp_sv[82] -= amp_sv[0];
      jamp_sv[97] -= amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      VVV1_0( w_sv[8], w_sv[4], w_sv[110], COUPs[0], &amp_sv[0] );
      jamp_sv[22] -= amp_sv[0];
      jamp_sv[29] += +amp_sv[0];
      jamp_sv[37] -= amp_sv[0];
      jamp_sv[40] += +amp_sv[0];
      jamp_sv[43] -= amp_sv[0];
      jamp_sv[53] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[57] -= amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[61] -= amp_sv[0];
      jamp_sv[64] += +amp_sv[0];
      jamp_sv[67] -= amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      VVV1_0( w_sv[8], w_sv[4], w_sv[111], COUPs[0], &amp_sv[0] );
      jamp_sv[19] -= amp_sv[0];
      jamp_sv[29] += +amp_sv[0];
      jamp_sv[43] -= amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[61] -= amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[63] -= amp_sv[0];
      jamp_sv[64] += +amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[97] += +amp_sv[0];

      // *** DIAGRAM 691 OF 1240 ***

      // Wavefunction(s) for diagram number 691
      // (none)

      // Amplitude(s) for diagram number 691
      VVV1_0( w_sv[1], w_sv[8], w_sv[107], COUPs[0], &amp_sv[0] );
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[23] += +amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[29] -= amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[33] += +amp_sv[0];
      jamp_sv[38] += +amp_sv[0];
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[42] -= amp_sv[0];
      jamp_sv[43] += +amp_sv[0];
      jamp_sv[61] += +amp_sv[0];
      jamp_sv[64] -= amp_sv[0];
      jamp_sv[85] -= amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[99] += +amp_sv[0];
      jamp_sv[101] -= amp_sv[0];
      VVV1_0( w_sv[1], w_sv[8], w_sv[95], COUPs[0], &amp_sv[0] );
      jamp_sv[23] += +amp_sv[0];
      jamp_sv[29] -= amp_sv[0];
      jamp_sv[31] += +amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[33] += +amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[37] += +amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[43] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[61] += +amp_sv[0];
      jamp_sv[64] -= amp_sv[0];
      jamp_sv[67] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[91] += +amp_sv[0];
      jamp_sv[101] -= amp_sv[0];
      VVV1_0( w_sv[1], w_sv[8], w_sv[105], COUPs[0], &amp_sv[0] );
      jamp_sv[21] += +amp_sv[0];
      jamp_sv[28] -= amp_sv[0];
      jamp_sv[31] += +amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[37] += +amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[39] += +amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[42] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[67] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[85] += +amp_sv[0];
      jamp_sv[88] -= amp_sv[0];
      jamp_sv[91] += +amp_sv[0];
      jamp_sv[99] -= amp_sv[0];

      // *** DIAGRAM 692 OF 1240 ***

      // Wavefunction(s) for diagram number 692
      // (none)

      // Amplitude(s) for diagram number 692
      VVVV1_0( w_sv[92], w_sv[1], w_sv[8], w_sv[24], COUPs[2], &amp_sv[0] );
      jamp_sv[18] += +amp_sv[0];
      jamp_sv[19] -= amp_sv[0];
      jamp_sv[28] -= amp_sv[0];
      jamp_sv[29] += +amp_sv[0];
      jamp_sv[42] += +amp_sv[0];
      jamp_sv[43] -= amp_sv[0];
      jamp_sv[61] -= amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[63] -= amp_sv[0];
      jamp_sv[64] += +amp_sv[0];
      jamp_sv[85] += +amp_sv[0];
      jamp_sv[86] -= amp_sv[0];
      jamp_sv[87] += +amp_sv[0];
      jamp_sv[88] -= amp_sv[0];
      jamp_sv[96] -= amp_sv[0];
      jamp_sv[97] += +amp_sv[0];
      VVVV3_0( w_sv[92], w_sv[1], w_sv[8], w_sv[24], COUPs[2], &amp_sv[0] );
      jamp_sv[18] += +amp_sv[0];
      jamp_sv[19] -= amp_sv[0];
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[23] += +amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[33] += +amp_sv[0];
      jamp_sv[38] += +amp_sv[0];
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[63] -= amp_sv[0];
      jamp_sv[86] -= amp_sv[0];
      jamp_sv[87] += +amp_sv[0];
      jamp_sv[96] -= amp_sv[0];
      jamp_sv[97] += +amp_sv[0];
      jamp_sv[99] += +amp_sv[0];
      jamp_sv[101] -= amp_sv[0];
      VVVV4_0( w_sv[92], w_sv[1], w_sv[8], w_sv[24], COUPs[2], &amp_sv[0] );
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[23] += +amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[29] -= amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[33] += +amp_sv[0];
      jamp_sv[38] += +amp_sv[0];
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[42] -= amp_sv[0];
      jamp_sv[43] += +amp_sv[0];
      jamp_sv[61] += +amp_sv[0];
      jamp_sv[64] -= amp_sv[0];
      jamp_sv[85] -= amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[99] += +amp_sv[0];
      jamp_sv[101] -= amp_sv[0];

      // *** DIAGRAM 693 OF 1240 ***

      // Wavefunction(s) for diagram number 693
      // (none)

      // Amplitude(s) for diagram number 693
      VVV1_0( w_sv[8], w_sv[24], w_sv[104], COUPs[0], &amp_sv[0] );
      jamp_sv[18] += +amp_sv[0];
      jamp_sv[19] -= amp_sv[0];
      jamp_sv[28] -= amp_sv[0];
      jamp_sv[29] += +amp_sv[0];
      jamp_sv[42] += +amp_sv[0];
      jamp_sv[43] -= amp_sv[0];
      jamp_sv[61] -= amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[63] -= amp_sv[0];
      jamp_sv[64] += +amp_sv[0];
      jamp_sv[85] += +amp_sv[0];
      jamp_sv[86] -= amp_sv[0];
      jamp_sv[87] += +amp_sv[0];
      jamp_sv[88] -= amp_sv[0];
      jamp_sv[96] -= amp_sv[0];
      jamp_sv[97] += +amp_sv[0];

      // *** DIAGRAM 694 OF 1240 ***

      // Wavefunction(s) for diagram number 694
      // (none)

      // Amplitude(s) for diagram number 694
      VVV1_0( w_sv[1], w_sv[24], w_sv[113], COUPs[0], &amp_sv[0] );
      jamp_sv[18] += +amp_sv[0];
      jamp_sv[19] -= amp_sv[0];
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[23] += +amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[33] += +amp_sv[0];
      jamp_sv[38] += +amp_sv[0];
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[63] -= amp_sv[0];
      jamp_sv[86] -= amp_sv[0];
      jamp_sv[87] += +amp_sv[0];
      jamp_sv[96] -= amp_sv[0];
      jamp_sv[97] += +amp_sv[0];
      jamp_sv[99] += +amp_sv[0];
      jamp_sv[101] -= amp_sv[0];

      // *** DIAGRAM 695 OF 1240 ***

      // Wavefunction(s) for diagram number 695
      // (none)

      // Amplitude(s) for diagram number 695
      VVV1_0( w_sv[1], w_sv[8], w_sv[102], COUPs[0], &amp_sv[0] );
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[23] += +amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[29] -= amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[33] += +amp_sv[0];
      jamp_sv[38] += +amp_sv[0];
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[42] -= amp_sv[0];
      jamp_sv[43] += +amp_sv[0];
      jamp_sv[61] += +amp_sv[0];
      jamp_sv[64] -= amp_sv[0];
      jamp_sv[85] -= amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[99] += +amp_sv[0];
      jamp_sv[101] -= amp_sv[0];

      // *** DIAGRAM 696 OF 1240 ***

      // Wavefunction(s) for diagram number 696
      // (none)

      // Amplitude(s) for diagram number 696
      VVV1_0( w_sv[104], w_sv[37], w_sv[5], COUPs[0], &amp_sv[0] );
      jamp_sv[52] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[55] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[58] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[61] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[62] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[63] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[64] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[66] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 697 OF 1240 ***

      // Wavefunction(s) for diagram number 697
      // (none)

      // Amplitude(s) for diagram number 697
      FFV1_0( w_sv[3], w_sv[35], w_sv[104], COUPs[1], &amp_sv[0] );
      jamp_sv[61] += +amp_sv[0];
      jamp_sv[62] -= amp_sv[0];
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[64] -= amp_sv[0];

      // *** DIAGRAM 698 OF 1240 ***

      // Wavefunction(s) for diagram number 698
      // (none)

      // Amplitude(s) for diagram number 698
      FFV1_0( w_sv[99], w_sv[100], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[56] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[57] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 699 OF 1240 ***

      // Wavefunction(s) for diagram number 699
      // (none)

      // Amplitude(s) for diagram number 699
      FFV1_0( w_sv[99], w_sv[35], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[62] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[63] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 700 OF 1240 ***

      // Wavefunction(s) for diagram number 700
      // (none)

      // Amplitude(s) for diagram number 700
      FFV1_0( w_sv[3], w_sv[100], w_sv[86], COUPs[1], &amp_sv[0] );
      jamp_sv[55] += +amp_sv[0];
      jamp_sv[56] -= amp_sv[0];
      jamp_sv[57] += +amp_sv[0];
      jamp_sv[58] -= amp_sv[0];

      // *** DIAGRAM 701 OF 1240 ***

      // Wavefunction(s) for diagram number 701
      // (none)

      // Amplitude(s) for diagram number 701
      VVV1_0( w_sv[86], w_sv[1], w_sv[37], COUPs[0], &amp_sv[0] );
      jamp_sv[53] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[55] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[56] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[57] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[58] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[61] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[64] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[67] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 702 OF 1240 ***

      // Wavefunction(s) for diagram number 702
      // (none)

      // Amplitude(s) for diagram number 702
      FFV1_0( w_sv[3], w_sv[33], w_sv[109], COUPs[1], &amp_sv[0] );
      jamp_sv[52] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[53] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[56] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[57] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[62] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[63] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[66] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[67] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[33], w_sv[110], COUPs[1], &amp_sv[0] );
      jamp_sv[53] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[55] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[56] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[57] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[58] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[61] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[64] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[67] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[33], w_sv[111], COUPs[1], &amp_sv[0] );
      jamp_sv[52] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[55] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[58] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[61] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[62] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[63] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[64] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[66] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 703 OF 1240 ***

      // Wavefunction(s) for diagram number 703
      // (none)

      // Amplitude(s) for diagram number 703
      FFV1_0( w_sv[38], w_sv[33], w_sv[104], COUPs[1], &amp_sv[0] );
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[66] -= amp_sv[0];

      // *** DIAGRAM 704 OF 1240 ***

      // Wavefunction(s) for diagram number 704
      // (none)

      // Amplitude(s) for diagram number 704
      FFV1_0( w_sv[38], w_sv[114], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[52] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[66] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 705 OF 1240 ***

      // Wavefunction(s) for diagram number 705
      // (none)

      // Amplitude(s) for diagram number 705
      FFV1_0( w_sv[90], w_sv[33], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[55] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[58] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 706 OF 1240 ***

      // Wavefunction(s) for diagram number 706
      // (none)

      // Amplitude(s) for diagram number 706
      VVV1_0( w_sv[104], w_sv[45], w_sv[4], COUPs[0], &amp_sv[0] );
      jamp_sv[76] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[79] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[82] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[85] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[86] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[87] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[88] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[90] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 707 OF 1240 ***

      // Wavefunction(s) for diagram number 707
      // (none)

      // Amplitude(s) for diagram number 707
      FFV1_0( w_sv[3], w_sv[43], w_sv[104], COUPs[1], &amp_sv[0] );
      jamp_sv[85] += +amp_sv[0];
      jamp_sv[86] -= amp_sv[0];
      jamp_sv[87] += +amp_sv[0];
      jamp_sv[88] -= amp_sv[0];

      // *** DIAGRAM 708 OF 1240 ***

      // Wavefunction(s) for diagram number 708
      // (none)

      // Amplitude(s) for diagram number 708
      FFV1_0( w_sv[99], w_sv[89], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[80] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[81] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 709 OF 1240 ***

      // Wavefunction(s) for diagram number 709
      // (none)

      // Amplitude(s) for diagram number 709
      FFV1_0( w_sv[99], w_sv[43], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[86] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[87] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 710 OF 1240 ***

      // Wavefunction(s) for diagram number 710
      // (none)

      // Amplitude(s) for diagram number 710
      FFV1_0( w_sv[3], w_sv[89], w_sv[112], COUPs[1], &amp_sv[0] );
      jamp_sv[79] += +amp_sv[0];
      jamp_sv[80] -= amp_sv[0];
      jamp_sv[81] += +amp_sv[0];
      jamp_sv[82] -= amp_sv[0];

      // *** DIAGRAM 711 OF 1240 ***

      // Wavefunction(s) for diagram number 711
      // (none)

      // Amplitude(s) for diagram number 711
      VVV1_0( w_sv[112], w_sv[1], w_sv[45], COUPs[0], &amp_sv[0] );
      jamp_sv[77] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[79] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[80] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[81] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[82] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[85] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[88] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[91] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 712 OF 1240 ***

      // Wavefunction(s) for diagram number 712
      // (none)

      // Amplitude(s) for diagram number 712
      FFV1_0( w_sv[3], w_sv[39], w_sv[98], COUPs[1], &amp_sv[0] );
      jamp_sv[76] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[77] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[80] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[81] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[86] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[87] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[90] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[91] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[39], w_sv[62], COUPs[1], &amp_sv[0] );
      jamp_sv[77] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[79] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[80] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[81] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[82] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[85] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[88] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[91] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[39], w_sv[101], COUPs[1], &amp_sv[0] );
      jamp_sv[76] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[79] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[82] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[85] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[86] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[87] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[88] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[90] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 713 OF 1240 ***

      // Wavefunction(s) for diagram number 713
      // (none)

      // Amplitude(s) for diagram number 713
      FFV1_0( w_sv[46], w_sv[39], w_sv[104], COUPs[1], &amp_sv[0] );
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[90] -= amp_sv[0];

      // *** DIAGRAM 714 OF 1240 ***

      // Wavefunction(s) for diagram number 714
      // (none)

      // Amplitude(s) for diagram number 714
      FFV1_0( w_sv[46], w_sv[106], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[76] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[90] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 715 OF 1240 ***

      // Wavefunction(s) for diagram number 715
      // (none)

      // Amplitude(s) for diagram number 715
      FFV1_0( w_sv[88], w_sv[39], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[79] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[82] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 716 OF 1240 ***

      // Wavefunction(s) for diagram number 716
      // (none)

      // Amplitude(s) for diagram number 716
      VVV1_0( w_sv[104], w_sv[54], w_sv[5], COUPs[0], &amp_sv[0] );
      jamp_sv[19] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[29] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[43] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[76] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[79] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[82] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[90] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[97] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 717 OF 1240 ***

      // Wavefunction(s) for diagram number 717
      // (none)

      // Amplitude(s) for diagram number 717
      FFV1_0( w_sv[7], w_sv[2], w_sv[104], COUPs[1], &amp_sv[0] );
      jamp_sv[19] += +amp_sv[0];
      jamp_sv[29] -= amp_sv[0];
      jamp_sv[43] += +amp_sv[0];
      jamp_sv[97] -= amp_sv[0];

      // *** DIAGRAM 718 OF 1240 ***

      // Wavefunction(s) for diagram number 718
      // (none)

      // Amplitude(s) for diagram number 718
      FFV1_0( w_sv[78], w_sv[96], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[22] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[100] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 719 OF 1240 ***

      // Wavefunction(s) for diagram number 719
      // (none)

      // Amplitude(s) for diagram number 719
      FFV1_0( w_sv[7], w_sv[96], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[19] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[97] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 720 OF 1240 ***

      // Wavefunction(s) for diagram number 720
      // (none)

      // Amplitude(s) for diagram number 720
      FFV1_0( w_sv[78], w_sv[2], w_sv[86], COUPs[1], &amp_sv[0] );
      jamp_sv[22] += +amp_sv[0];
      jamp_sv[76] -= amp_sv[0];
      jamp_sv[90] += +amp_sv[0];
      jamp_sv[100] -= amp_sv[0];

      // *** DIAGRAM 721 OF 1240 ***

      // Wavefunction(s) for diagram number 721
      // (none)

      // Amplitude(s) for diagram number 721
      VVV1_0( w_sv[86], w_sv[1], w_sv[54], COUPs[0], &amp_sv[0] );
      jamp_sv[22] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[29] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[37] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[40] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[43] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[76] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[90] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[100] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 722 OF 1240 ***

      // Wavefunction(s) for diagram number 722
      // (none)

      // Amplitude(s) for diagram number 722
      FFV1_0( w_sv[46], w_sv[2], w_sv[109], COUPs[1], &amp_sv[0] );
      jamp_sv[19] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[22] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[37] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[40] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[79] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[82] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[97] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[100] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[46], w_sv[2], w_sv[110], COUPs[1], &amp_sv[0] );
      jamp_sv[22] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[29] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[37] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[40] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[43] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[76] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[90] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[100] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[46], w_sv[2], w_sv[111], COUPs[1], &amp_sv[0] );
      jamp_sv[19] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[29] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[43] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[76] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[79] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[82] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[90] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[97] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 723 OF 1240 ***

      // Wavefunction(s) for diagram number 723
      // (none)

      // Amplitude(s) for diagram number 723
      VVV1_0( w_sv[104], w_sv[23], w_sv[4], COUPs[0], &amp_sv[0] );
      jamp_sv[18] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[28] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[42] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[52] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[55] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[58] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[66] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[96] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 724 OF 1240 ***

      // Wavefunction(s) for diagram number 724
      // (none)

      // Amplitude(s) for diagram number 724
      FFV1_0( w_sv[25], w_sv[2], w_sv[104], COUPs[1], &amp_sv[0] );
      jamp_sv[18] += +amp_sv[0];
      jamp_sv[28] -= amp_sv[0];
      jamp_sv[42] += +amp_sv[0];
      jamp_sv[96] -= amp_sv[0];

      // *** DIAGRAM 725 OF 1240 ***

      // Wavefunction(s) for diagram number 725
      // (none)

      // Amplitude(s) for diagram number 725
      FFV1_0( w_sv[58], w_sv[96], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[20] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[98] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 726 OF 1240 ***

      // Wavefunction(s) for diagram number 726
      // (none)

      // Amplitude(s) for diagram number 726
      FFV1_0( w_sv[25], w_sv[96], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[18] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[96] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 727 OF 1240 ***

      // Wavefunction(s) for diagram number 727
      // (none)

      // Amplitude(s) for diagram number 727
      FFV1_0( w_sv[58], w_sv[2], w_sv[112], COUPs[1], &amp_sv[0] );
      jamp_sv[20] += +amp_sv[0];
      jamp_sv[52] -= amp_sv[0];
      jamp_sv[66] += +amp_sv[0];
      jamp_sv[98] -= amp_sv[0];

      // *** DIAGRAM 728 OF 1240 ***

      // Wavefunction(s) for diagram number 728
      // (none)

      // Amplitude(s) for diagram number 728
      VVV1_0( w_sv[112], w_sv[1], w_sv[23], COUPs[0], &amp_sv[0] );
      jamp_sv[20] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[28] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[31] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[34] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[42] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[52] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[66] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[98] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 729 OF 1240 ***

      // Wavefunction(s) for diagram number 729
      // (none)

      // Amplitude(s) for diagram number 729
      FFV1_0( w_sv[38], w_sv[2], w_sv[98], COUPs[1], &amp_sv[0] );
      jamp_sv[18] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[20] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[31] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[34] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[55] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[58] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[96] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[98] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[38], w_sv[2], w_sv[62], COUPs[1], &amp_sv[0] );
      jamp_sv[20] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[28] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[31] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[34] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[42] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[52] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[66] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[98] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[38], w_sv[2], w_sv[101], COUPs[1], &amp_sv[0] );
      jamp_sv[18] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[28] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[42] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[52] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[55] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[58] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[66] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[96] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 730 OF 1240 ***

      // Wavefunction(s) for diagram number 730
      // (none)

      // Amplitude(s) for diagram number 730
      FFV1_0( w_sv[3], w_sv[17], w_sv[104], COUPs[1], &amp_sv[0] );
      jamp_sv[61] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[62] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[63] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[64] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[85] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[86] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[87] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[88] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 731 OF 1240 ***

      // Wavefunction(s) for diagram number 731
      // (none)

      // Amplitude(s) for diagram number 731
      FFV1_0( w_sv[26], w_sv[2], w_sv[104], COUPs[1], &amp_sv[0] );
      jamp_sv[18] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[19] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[28] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[29] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[42] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[43] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[96] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[97] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 732 OF 1240 ***

      // Wavefunction(s) for diagram number 732
      // (none)

      // Amplitude(s) for diagram number 732
      FFV1_0( w_sv[3], w_sv[96], w_sv[59], COUPs[1], &amp_sv[0] );
      jamp_sv[18] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[19] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[21] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[23] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[96] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[97] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[99] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[101] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 733 OF 1240 ***

      // Wavefunction(s) for diagram number 733
      // (none)

      // Amplitude(s) for diagram number 733
      FFV1_0( w_sv[26], w_sv[96], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[18] += +amp_sv[0];
      jamp_sv[19] -= amp_sv[0];
      jamp_sv[96] -= amp_sv[0];
      jamp_sv[97] += +amp_sv[0];

      // *** DIAGRAM 734 OF 1240 ***

      // Wavefunction(s) for diagram number 734
      // (none)

      // Amplitude(s) for diagram number 734
      FFV1_0( w_sv[99], w_sv[2], w_sv[59], COUPs[1], &amp_sv[0] );
      jamp_sv[32] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[33] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[38] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[39] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[62] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[63] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[86] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[87] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 735 OF 1240 ***

      // Wavefunction(s) for diagram number 735
      // (none)

      // Amplitude(s) for diagram number 735
      FFV1_0( w_sv[99], w_sv[17], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[63] -= amp_sv[0];
      jamp_sv[86] -= amp_sv[0];
      jamp_sv[87] += +amp_sv[0];

      // *** DIAGRAM 736 OF 1240 ***

      // Wavefunction(s) for diagram number 736
      // (none)

      // Amplitude(s) for diagram number 736
      FFV1_0( w_sv[3], w_sv[96], w_sv[73], COUPs[1], &amp_sv[0] );
      jamp_sv[18] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[19] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[21] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[23] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[96] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[97] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[99] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[101] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[96], w_sv[79], COUPs[1], &amp_sv[0] );
      jamp_sv[19] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[20] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[21] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[22] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[97] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[98] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[99] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[100] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[96], w_sv[80], COUPs[1], &amp_sv[0] );
      jamp_sv[18] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[20] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[22] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[23] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[96] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[98] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[100] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[101] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 737 OF 1240 ***

      // Wavefunction(s) for diagram number 737
      // (none)

      // Amplitude(s) for diagram number 737
      FFV1_0( w_sv[99], w_sv[2], w_sv[73], COUPs[1], &amp_sv[0] );
      jamp_sv[32] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[33] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[38] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[39] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[62] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[63] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[86] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[87] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[99], w_sv[2], w_sv[79], COUPs[1], &amp_sv[0] );
      jamp_sv[38] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[39] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[56] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[57] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[62] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[63] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[80] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[81] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[99], w_sv[2], w_sv[80], COUPs[1], &amp_sv[0] );
      jamp_sv[32] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[33] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[56] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[57] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[80] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[81] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[86] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[87] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 738 OF 1240 ***

      // Wavefunction(s) for diagram number 738
      // (none)

      // Amplitude(s) for diagram number 738
      VVV1_0( w_sv[92], w_sv[73], w_sv[8], COUPs[0], &amp_sv[0] );
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[19] += +amp_sv[0];
      jamp_sv[21] += +amp_sv[0];
      jamp_sv[23] -= amp_sv[0];
      jamp_sv[32] += +amp_sv[0];
      jamp_sv[33] -= amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[39] += +amp_sv[0];
      jamp_sv[62] -= amp_sv[0];
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[97] -= amp_sv[0];
      jamp_sv[99] -= amp_sv[0];
      jamp_sv[101] += +amp_sv[0];
      VVV1_0( w_sv[92], w_sv[79], w_sv[8], COUPs[0], &amp_sv[0] );
      jamp_sv[19] += +amp_sv[0];
      jamp_sv[20] -= amp_sv[0];
      jamp_sv[21] += +amp_sv[0];
      jamp_sv[22] -= amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[39] += +amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[57] -= amp_sv[0];
      jamp_sv[62] -= amp_sv[0];
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[81] -= amp_sv[0];
      jamp_sv[97] -= amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      jamp_sv[99] -= amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      VVV1_0( w_sv[92], w_sv[80], w_sv[8], COUPs[0], &amp_sv[0] );
      jamp_sv[18] += +amp_sv[0];
      jamp_sv[20] -= amp_sv[0];
      jamp_sv[22] -= amp_sv[0];
      jamp_sv[23] += +amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[33] += +amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[57] -= amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[81] -= amp_sv[0];
      jamp_sv[86] -= amp_sv[0];
      jamp_sv[87] += +amp_sv[0];
      jamp_sv[96] -= amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      jamp_sv[101] -= amp_sv[0];

      // *** DIAGRAM 739 OF 1240 ***

      // Wavefunction(s) for diagram number 739
      FFV1_1( w_sv[77], w_sv[0], COUPs[1], cIPD[0], cIPD[1], w_sv[92] );

      // Amplitude(s) for diagram number 739
      FFV1_0( w_sv[7], w_sv[92], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[29] -= amp_sv[0];

      // *** DIAGRAM 740 OF 1240 ***

      // Wavefunction(s) for diagram number 740
      // (none)

      // Amplitude(s) for diagram number 740
      FFV1_0( w_sv[53], w_sv[92], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[27] -= amp_sv[0];

      // *** DIAGRAM 741 OF 1240 ***

      // Wavefunction(s) for diagram number 741
      FFV1_2( w_sv[46], w_sv[0], COUPs[1], cIPD[0], cIPD[1], w_sv[99] );

      // Amplitude(s) for diagram number 741
      FFV1_0( w_sv[99], w_sv[9], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[40] -= amp_sv[0];

      // *** DIAGRAM 742 OF 1240 ***

      // Wavefunction(s) for diagram number 742
      // (none)

      // Amplitude(s) for diagram number 742
      FFV1_0( w_sv[99], w_sv[85], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[46] -= amp_sv[0];

      // *** DIAGRAM 743 OF 1240 ***

      // Wavefunction(s) for diagram number 743
      // (none)

      // Amplitude(s) for diagram number 743
      FFV1_0( w_sv[53], w_sv[9], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[37] -= amp_sv[0];

      // *** DIAGRAM 744 OF 1240 ***

      // Wavefunction(s) for diagram number 744
      // (none)

      // Amplitude(s) for diagram number 744
      FFV1_0( w_sv[7], w_sv[85], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[43] -= amp_sv[0];

      // *** DIAGRAM 745 OF 1240 ***

      // Wavefunction(s) for diagram number 745
      // (none)

      // Amplitude(s) for diagram number 745
      FFV1_0( w_sv[46], w_sv[92], w_sv[29], COUPs[1], &amp_sv[0] );
      jamp_sv[27] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[29] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 746 OF 1240 ***

      // Wavefunction(s) for diagram number 746
      // (none)

      // Amplitude(s) for diagram number 746
      FFV1_0( w_sv[99], w_sv[77], w_sv[29], COUPs[1], &amp_sv[0] );
      jamp_sv[40] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[46] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 747 OF 1240 ***

      // Wavefunction(s) for diagram number 747
      VVV1P0_1( w_sv[0], w_sv[29], COUPs[0], 0., 0., w_sv[96] );

      // Amplitude(s) for diagram number 747
      FFV1_0( w_sv[46], w_sv[77], w_sv[96], COUPs[1], &amp_sv[0] );
      jamp_sv[27] += +amp_sv[0];
      jamp_sv[29] -= amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[46] += +amp_sv[0];

      // *** DIAGRAM 748 OF 1240 ***

      // Wavefunction(s) for diagram number 748
      // (none)

      // Amplitude(s) for diagram number 748
      FFV1_0( w_sv[25], w_sv[92], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[28] -= amp_sv[0];

      // *** DIAGRAM 749 OF 1240 ***

      // Wavefunction(s) for diagram number 749
      // (none)

      // Amplitude(s) for diagram number 749
      FFV1_0( w_sv[48], w_sv[92], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[25] -= amp_sv[0];

      // *** DIAGRAM 750 OF 1240 ***

      // Wavefunction(s) for diagram number 750
      FFV1_2( w_sv[38], w_sv[0], COUPs[1], cIPD[0], cIPD[1], w_sv[104] );

      // Amplitude(s) for diagram number 750
      FFV1_0( w_sv[104], w_sv[87], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[34] -= amp_sv[0];

      // *** DIAGRAM 751 OF 1240 ***

      // Wavefunction(s) for diagram number 751
      // (none)

      // Amplitude(s) for diagram number 751
      FFV1_0( w_sv[104], w_sv[85], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[44] -= amp_sv[0];

      // *** DIAGRAM 752 OF 1240 ***

      // Wavefunction(s) for diagram number 752
      // (none)

      // Amplitude(s) for diagram number 752
      FFV1_0( w_sv[48], w_sv[87], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[31] -= amp_sv[0];

      // *** DIAGRAM 753 OF 1240 ***

      // Wavefunction(s) for diagram number 753
      // (none)

      // Amplitude(s) for diagram number 753
      FFV1_0( w_sv[25], w_sv[85], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[42] -= amp_sv[0];

      // *** DIAGRAM 754 OF 1240 ***

      // Wavefunction(s) for diagram number 754
      // (none)

      // Amplitude(s) for diagram number 754
      FFV1_0( w_sv[38], w_sv[92], w_sv[27], COUPs[1], &amp_sv[0] );
      jamp_sv[25] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[28] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 755 OF 1240 ***

      // Wavefunction(s) for diagram number 755
      // (none)

      // Amplitude(s) for diagram number 755
      FFV1_0( w_sv[104], w_sv[77], w_sv[27], COUPs[1], &amp_sv[0] );
      jamp_sv[34] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[44] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 756 OF 1240 ***

      // Wavefunction(s) for diagram number 756
      VVV1P0_1( w_sv[0], w_sv[27], COUPs[0], 0., 0., w_sv[101] );

      // Amplitude(s) for diagram number 756
      FFV1_0( w_sv[38], w_sv[77], w_sv[101], COUPs[1], &amp_sv[0] );
      jamp_sv[25] += +amp_sv[0];
      jamp_sv[28] -= amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[44] += +amp_sv[0];

      // *** DIAGRAM 757 OF 1240 ***

      // Wavefunction(s) for diagram number 757
      // (none)

      // Amplitude(s) for diagram number 757
      FFV1_0( w_sv[28], w_sv[92], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[26] -= amp_sv[0];

      // *** DIAGRAM 758 OF 1240 ***

      // Wavefunction(s) for diagram number 758
      // (none)

      // Amplitude(s) for diagram number 758
      FFV1_0( w_sv[40], w_sv[92], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[24] -= amp_sv[0];

      // *** DIAGRAM 759 OF 1240 ***

      // Wavefunction(s) for diagram number 759
      FFV1_2( w_sv[41], w_sv[0], COUPs[1], cIPD[0], cIPD[1], w_sv[62] );

      // Amplitude(s) for diagram number 759
      FFV1_0( w_sv[62], w_sv[87], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[32] -= amp_sv[0];

      // *** DIAGRAM 760 OF 1240 ***

      // Wavefunction(s) for diagram number 760
      // (none)

      // Amplitude(s) for diagram number 760
      FFV1_0( w_sv[62], w_sv[9], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[38] -= amp_sv[0];

      // *** DIAGRAM 761 OF 1240 ***

      // Wavefunction(s) for diagram number 761
      // (none)

      // Amplitude(s) for diagram number 761
      FFV1_0( w_sv[40], w_sv[87], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[30] -= amp_sv[0];

      // *** DIAGRAM 762 OF 1240 ***

      // Wavefunction(s) for diagram number 762
      // (none)

      // Amplitude(s) for diagram number 762
      FFV1_0( w_sv[28], w_sv[9], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[36] -= amp_sv[0];

      // *** DIAGRAM 763 OF 1240 ***

      // Wavefunction(s) for diagram number 763
      // (none)

      // Amplitude(s) for diagram number 763
      FFV1_0( w_sv[41], w_sv[92], w_sv[24], COUPs[1], &amp_sv[0] );
      jamp_sv[24] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[26] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 764 OF 1240 ***

      // Wavefunction(s) for diagram number 764
      // (none)

      // Amplitude(s) for diagram number 764
      FFV1_0( w_sv[62], w_sv[77], w_sv[24], COUPs[1], &amp_sv[0] );
      jamp_sv[32] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[38] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 765 OF 1240 ***

      // Wavefunction(s) for diagram number 765
      VVV1P0_1( w_sv[0], w_sv[24], COUPs[0], 0., 0., w_sv[98] );

      // Amplitude(s) for diagram number 765
      FFV1_0( w_sv[41], w_sv[77], w_sv[98], COUPs[1], &amp_sv[0] );
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[26] -= amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[38] += +amp_sv[0];

      // *** DIAGRAM 766 OF 1240 ***

      // Wavefunction(s) for diagram number 766
      // (none)

      // Amplitude(s) for diagram number 766
      FFV1_0( w_sv[26], w_sv[92], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[28] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[29] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 767 OF 1240 ***

      // Wavefunction(s) for diagram number 767
      // (none)

      // Amplitude(s) for diagram number 767
      FFV1_0( w_sv[3], w_sv[92], w_sv[42], COUPs[1], &amp_sv[0] );
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[26] -= amp_sv[0];
      jamp_sv[28] -= amp_sv[0];
      jamp_sv[29] += +amp_sv[0];

      // *** DIAGRAM 768 OF 1240 ***

      // Wavefunction(s) for diagram number 768
      // (none)

      // Amplitude(s) for diagram number 768
      VVV1_0( w_sv[98], w_sv[34], w_sv[6], COUPs[0], &amp_sv[0] );
      jamp_sv[24] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[26] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[32] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[38] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[42] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[43] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[45] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[47] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 769 OF 1240 ***

      // Wavefunction(s) for diagram number 769
      // (none)

      // Amplitude(s) for diagram number 769
      FFV1_0( w_sv[3], w_sv[85], w_sv[98], COUPs[1], &amp_sv[0] );
      jamp_sv[42] += +amp_sv[0];
      jamp_sv[43] -= amp_sv[0];
      jamp_sv[45] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];

      // *** DIAGRAM 770 OF 1240 ***

      // Wavefunction(s) for diagram number 770
      // (none)

      // Amplitude(s) for diagram number 770
      VVV1_0( w_sv[0], w_sv[34], w_sv[42], COUPs[0], &amp_sv[0] );
      jamp_sv[24] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[26] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[28] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[29] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[33] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[39] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[45] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[47] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 771 OF 1240 ***

      // Wavefunction(s) for diagram number 771
      // (none)

      // Amplitude(s) for diagram number 771
      FFV1_0( w_sv[26], w_sv[85], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[42] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[43] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 772 OF 1240 ***

      // Wavefunction(s) for diagram number 772
      VVVV1P0_1( w_sv[0], w_sv[24], w_sv[6], COUPs[2], 0., 0., w_sv[85] );
      VVVV3P0_1( w_sv[0], w_sv[24], w_sv[6], COUPs[2], 0., 0., w_sv[112] );
      VVVV4P0_1( w_sv[0], w_sv[24], w_sv[6], COUPs[2], 0., 0., w_sv[111] );

      // Amplitude(s) for diagram number 772
      FFV1_0( w_sv[3], w_sv[77], w_sv[85], COUPs[1], &amp_sv[0] );
      jamp_sv[24] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[26] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[28] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[29] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[33] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[39] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[45] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[47] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[77], w_sv[112], COUPs[1], &amp_sv[0] );
      jamp_sv[28] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[29] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[32] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[33] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[38] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[39] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[42] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[43] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[77], w_sv[111], COUPs[1], &amp_sv[0] );
      jamp_sv[24] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[26] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[32] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[38] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[42] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[43] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[45] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[47] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 773 OF 1240 ***

      // Wavefunction(s) for diagram number 773
      // (none)

      // Amplitude(s) for diagram number 773
      FFV1_0( w_sv[14], w_sv[92], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[26] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[27] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 774 OF 1240 ***

      // Wavefunction(s) for diagram number 774
      // (none)

      // Amplitude(s) for diagram number 774
      FFV1_0( w_sv[3], w_sv[92], w_sv[16], COUPs[1], &amp_sv[0] );
      jamp_sv[25] += +amp_sv[0];
      jamp_sv[26] -= amp_sv[0];
      jamp_sv[27] += +amp_sv[0];
      jamp_sv[28] -= amp_sv[0];

      // *** DIAGRAM 775 OF 1240 ***

      // Wavefunction(s) for diagram number 775
      // (none)

      // Amplitude(s) for diagram number 775
      VVV1_0( w_sv[101], w_sv[34], w_sv[5], COUPs[0], &amp_sv[0] );
      jamp_sv[25] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[28] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[34] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[36] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[37] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[39] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[41] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[44] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 776 OF 1240 ***

      // Wavefunction(s) for diagram number 776
      // (none)

      // Amplitude(s) for diagram number 776
      FFV1_0( w_sv[3], w_sv[9], w_sv[101], COUPs[1], &amp_sv[0] );
      jamp_sv[36] += +amp_sv[0];
      jamp_sv[37] -= amp_sv[0];
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[41] += +amp_sv[0];

      // *** DIAGRAM 777 OF 1240 ***

      // Wavefunction(s) for diagram number 777
      // (none)

      // Amplitude(s) for diagram number 777
      VVV1_0( w_sv[0], w_sv[34], w_sv[16], COUPs[0], &amp_sv[0] );
      jamp_sv[25] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[26] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[27] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[28] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[35] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[39] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[41] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[45] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 778 OF 1240 ***

      // Wavefunction(s) for diagram number 778
      // (none)

      // Amplitude(s) for diagram number 778
      FFV1_0( w_sv[14], w_sv[9], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[36] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[37] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 779 OF 1240 ***

      // Wavefunction(s) for diagram number 779
      VVVV1P0_1( w_sv[0], w_sv[27], w_sv[5], COUPs[2], 0., 0., w_sv[9] );
      VVVV3P0_1( w_sv[0], w_sv[27], w_sv[5], COUPs[2], 0., 0., w_sv[110] );
      VVVV4P0_1( w_sv[0], w_sv[27], w_sv[5], COUPs[2], 0., 0., w_sv[109] );

      // Amplitude(s) for diagram number 779
      FFV1_0( w_sv[3], w_sv[77], w_sv[9], COUPs[1], &amp_sv[0] );
      jamp_sv[25] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[26] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[27] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[28] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[35] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[39] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[41] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[45] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[77], w_sv[110], COUPs[1], &amp_sv[0] );
      jamp_sv[26] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[27] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[34] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[35] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[36] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[37] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[44] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[45] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[77], w_sv[109], COUPs[1], &amp_sv[0] );
      jamp_sv[25] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[28] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[34] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[36] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[37] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[39] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[41] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[44] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 780 OF 1240 ***

      // Wavefunction(s) for diagram number 780
      // (none)

      // Amplitude(s) for diagram number 780
      FFV1_0( w_sv[12], w_sv[92], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[24] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[25] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 781 OF 1240 ***

      // Wavefunction(s) for diagram number 781
      // (none)

      // Amplitude(s) for diagram number 781
      FFV1_0( w_sv[3], w_sv[92], w_sv[19], COUPs[1], &amp_sv[0] );
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[25] -= amp_sv[0];
      jamp_sv[27] -= amp_sv[0];
      jamp_sv[29] += +amp_sv[0];

      // *** DIAGRAM 782 OF 1240 ***

      // Wavefunction(s) for diagram number 782
      // (none)

      // Amplitude(s) for diagram number 782
      VVV1_0( w_sv[96], w_sv[34], w_sv[4], COUPs[0], &amp_sv[0] );
      jamp_sv[27] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[29] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[30] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[31] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[33] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[35] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[40] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[46] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 783 OF 1240 ***

      // Wavefunction(s) for diagram number 783
      // (none)

      // Amplitude(s) for diagram number 783
      FFV1_0( w_sv[3], w_sv[87], w_sv[96], COUPs[1], &amp_sv[0] );
      jamp_sv[30] += +amp_sv[0];
      jamp_sv[31] -= amp_sv[0];
      jamp_sv[33] -= amp_sv[0];
      jamp_sv[35] += +amp_sv[0];

      // *** DIAGRAM 784 OF 1240 ***

      // Wavefunction(s) for diagram number 784
      // (none)

      // Amplitude(s) for diagram number 784
      VVV1_0( w_sv[0], w_sv[34], w_sv[19], COUPs[0], &amp_sv[0] );
      jamp_sv[24] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[25] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[27] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[29] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[33] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[35] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[41] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[47] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 785 OF 1240 ***

      // Wavefunction(s) for diagram number 785
      // (none)

      // Amplitude(s) for diagram number 785
      FFV1_0( w_sv[12], w_sv[87], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[30] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[31] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 786 OF 1240 ***

      // Wavefunction(s) for diagram number 786
      VVVV1P0_1( w_sv[0], w_sv[4], w_sv[29], COUPs[2], 0., 0., w_sv[87] );
      VVVV3P0_1( w_sv[0], w_sv[4], w_sv[29], COUPs[2], 0., 0., w_sv[34] );
      VVVV4P0_1( w_sv[0], w_sv[4], w_sv[29], COUPs[2], 0., 0., w_sv[86] );

      // Amplitude(s) for diagram number 786
      FFV1_0( w_sv[3], w_sv[77], w_sv[87], COUPs[1], &amp_sv[0] );
      jamp_sv[24] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[25] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[27] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[29] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[33] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[35] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[41] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[47] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[77], w_sv[34], COUPs[1], &amp_sv[0] );
      jamp_sv[27] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[29] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[30] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[31] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[33] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[35] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[40] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[46] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[77], w_sv[86], COUPs[1], &amp_sv[0] );
      jamp_sv[24] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[25] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[30] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[31] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[40] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[41] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[46] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[47] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 787 OF 1240 ***

      // Wavefunction(s) for diagram number 787
      // (none)

      // Amplitude(s) for diagram number 787
      FFV1_0( w_sv[3], w_sv[92], w_sv[30], COUPs[1], &amp_sv[0] );
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[25] -= amp_sv[0];
      jamp_sv[27] -= amp_sv[0];
      jamp_sv[29] += +amp_sv[0];
      FFV1_0( w_sv[3], w_sv[92], w_sv[31], COUPs[1], &amp_sv[0] );
      jamp_sv[25] -= amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[27] -= amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      FFV1_0( w_sv[3], w_sv[92], w_sv[32], COUPs[1], &amp_sv[0] );
      jamp_sv[24] -= amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[29] -= amp_sv[0];

      // *** DIAGRAM 788 OF 1240 ***

      // Wavefunction(s) for diagram number 788
      VVV1P0_1( w_sv[0], w_sv[30], COUPs[0], 0., 0., w_sv[92] );
      VVV1P0_1( w_sv[0], w_sv[31], COUPs[0], 0., 0., w_sv[88] );
      VVV1P0_1( w_sv[0], w_sv[32], COUPs[0], 0., 0., w_sv[106] );

      // Amplitude(s) for diagram number 788
      FFV1_0( w_sv[3], w_sv[77], w_sv[92], COUPs[1], &amp_sv[0] );
      jamp_sv[24] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[25] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[27] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[29] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[33] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[35] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[41] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[47] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[77], w_sv[88], COUPs[1], &amp_sv[0] );
      jamp_sv[25] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[26] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[27] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[28] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[35] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[39] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[41] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[45] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[77], w_sv[106], COUPs[1], &amp_sv[0] );
      jamp_sv[24] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[26] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[28] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[29] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[33] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[39] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[45] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[47] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 789 OF 1240 ***

      // Wavefunction(s) for diagram number 789
      FFV1_2( w_sv[52], w_sv[0], COUPs[1], cIPD[0], cIPD[1], w_sv[90] );

      // Amplitude(s) for diagram number 789
      FFV1_0( w_sv[90], w_sv[35], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[64] -= amp_sv[0];

      // *** DIAGRAM 790 OF 1240 ***

      // Wavefunction(s) for diagram number 790
      // (none)

      // Amplitude(s) for diagram number 790
      FFV1_0( w_sv[90], w_sv[36], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[70] -= amp_sv[0];

      // *** DIAGRAM 791 OF 1240 ***

      // Wavefunction(s) for diagram number 791
      FFV1_1( w_sv[33], w_sv[0], COUPs[1], cIPD[0], cIPD[1], w_sv[114] );

      // Amplitude(s) for diagram number 791
      FFV1_0( w_sv[22], w_sv[114], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[53] -= amp_sv[0];

      // *** DIAGRAM 792 OF 1240 ***

      // Wavefunction(s) for diagram number 792
      // (none)

      // Amplitude(s) for diagram number 792
      FFV1_0( w_sv[21], w_sv[114], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[51] -= amp_sv[0];

      // *** DIAGRAM 793 OF 1240 ***

      // Wavefunction(s) for diagram number 793
      // (none)

      // Amplitude(s) for diagram number 793
      FFV1_0( w_sv[22], w_sv[36], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[67] -= amp_sv[0];

      // *** DIAGRAM 794 OF 1240 ***

      // Wavefunction(s) for diagram number 794
      // (none)

      // Amplitude(s) for diagram number 794
      FFV1_0( w_sv[21], w_sv[35], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[61] -= amp_sv[0];

      // *** DIAGRAM 795 OF 1240 ***

      // Wavefunction(s) for diagram number 795
      // (none)

      // Amplitude(s) for diagram number 795
      FFV1_0( w_sv[90], w_sv[33], w_sv[29], COUPs[1], &amp_sv[0] );
      jamp_sv[64] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[70] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 796 OF 1240 ***

      // Wavefunction(s) for diagram number 796
      // (none)

      // Amplitude(s) for diagram number 796
      FFV1_0( w_sv[52], w_sv[114], w_sv[29], COUPs[1], &amp_sv[0] );
      jamp_sv[51] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[53] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 797 OF 1240 ***

      // Wavefunction(s) for diagram number 797
      // (none)

      // Amplitude(s) for diagram number 797
      FFV1_0( w_sv[52], w_sv[33], w_sv[96], COUPs[1], &amp_sv[0] );
      jamp_sv[51] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[64] -= amp_sv[0];
      jamp_sv[70] += +amp_sv[0];

      // *** DIAGRAM 798 OF 1240 ***

      // Wavefunction(s) for diagram number 798
      // (none)

      // Amplitude(s) for diagram number 798
      FFV1_0( w_sv[90], w_sv[43], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[88] -= amp_sv[0];

      // *** DIAGRAM 799 OF 1240 ***

      // Wavefunction(s) for diagram number 799
      // (none)

      // Amplitude(s) for diagram number 799
      FFV1_0( w_sv[90], w_sv[44], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[94] -= amp_sv[0];

      // *** DIAGRAM 800 OF 1240 ***

      // Wavefunction(s) for diagram number 800
      FFV1_1( w_sv[39], w_sv[0], COUPs[1], cIPD[0], cIPD[1], w_sv[102] );

      // Amplitude(s) for diagram number 800
      FFV1_0( w_sv[56], w_sv[102], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[77] -= amp_sv[0];

      // *** DIAGRAM 801 OF 1240 ***

      // Wavefunction(s) for diagram number 801
      // (none)

      // Amplitude(s) for diagram number 801
      FFV1_0( w_sv[21], w_sv[102], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[75] -= amp_sv[0];

      // *** DIAGRAM 802 OF 1240 ***

      // Wavefunction(s) for diagram number 802
      // (none)

      // Amplitude(s) for diagram number 802
      FFV1_0( w_sv[56], w_sv[44], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[91] -= amp_sv[0];

      // *** DIAGRAM 803 OF 1240 ***

      // Wavefunction(s) for diagram number 803
      // (none)

      // Amplitude(s) for diagram number 803
      FFV1_0( w_sv[21], w_sv[43], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[85] -= amp_sv[0];

      // *** DIAGRAM 804 OF 1240 ***

      // Wavefunction(s) for diagram number 804
      // (none)

      // Amplitude(s) for diagram number 804
      FFV1_0( w_sv[90], w_sv[39], w_sv[27], COUPs[1], &amp_sv[0] );
      jamp_sv[88] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[94] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 805 OF 1240 ***

      // Wavefunction(s) for diagram number 805
      // (none)

      // Amplitude(s) for diagram number 805
      FFV1_0( w_sv[52], w_sv[102], w_sv[27], COUPs[1], &amp_sv[0] );
      jamp_sv[75] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[77] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 806 OF 1240 ***

      // Wavefunction(s) for diagram number 806
      // (none)

      // Amplitude(s) for diagram number 806
      FFV1_0( w_sv[52], w_sv[39], w_sv[101], COUPs[1], &amp_sv[0] );
      jamp_sv[75] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[88] -= amp_sv[0];
      jamp_sv[94] += +amp_sv[0];

      // *** DIAGRAM 807 OF 1240 ***

      // Wavefunction(s) for diagram number 807
      // (none)

      // Amplitude(s) for diagram number 807
      FFV1_0( w_sv[90], w_sv[49], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[112] -= amp_sv[0];

      // *** DIAGRAM 808 OF 1240 ***

      // Wavefunction(s) for diagram number 808
      // (none)

      // Amplitude(s) for diagram number 808
      FFV1_0( w_sv[90], w_sv[50], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[118] -= amp_sv[0];

      // *** DIAGRAM 809 OF 1240 ***

      // Wavefunction(s) for diagram number 809
      FFV1_1( w_sv[47], w_sv[0], COUPs[1], cIPD[0], cIPD[1], w_sv[113] );

      // Amplitude(s) for diagram number 809
      FFV1_0( w_sv[56], w_sv[113], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[101] -= amp_sv[0];

      // *** DIAGRAM 810 OF 1240 ***

      // Wavefunction(s) for diagram number 810
      // (none)

      // Amplitude(s) for diagram number 810
      FFV1_0( w_sv[22], w_sv[113], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[99] -= amp_sv[0];

      // *** DIAGRAM 811 OF 1240 ***

      // Wavefunction(s) for diagram number 811
      // (none)

      // Amplitude(s) for diagram number 811
      FFV1_0( w_sv[56], w_sv[50], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[115] -= amp_sv[0];

      // *** DIAGRAM 812 OF 1240 ***

      // Wavefunction(s) for diagram number 812
      // (none)

      // Amplitude(s) for diagram number 812
      FFV1_0( w_sv[22], w_sv[49], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[109] -= amp_sv[0];

      // *** DIAGRAM 813 OF 1240 ***

      // Wavefunction(s) for diagram number 813
      // (none)

      // Amplitude(s) for diagram number 813
      FFV1_0( w_sv[90], w_sv[47], w_sv[24], COUPs[1], &amp_sv[0] );
      jamp_sv[112] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[118] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 814 OF 1240 ***

      // Wavefunction(s) for diagram number 814
      // (none)

      // Amplitude(s) for diagram number 814
      FFV1_0( w_sv[52], w_sv[113], w_sv[24], COUPs[1], &amp_sv[0] );
      jamp_sv[99] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[101] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 815 OF 1240 ***

      // Wavefunction(s) for diagram number 815
      // (none)

      // Amplitude(s) for diagram number 815
      FFV1_0( w_sv[52], w_sv[47], w_sv[98], COUPs[1], &amp_sv[0] );
      jamp_sv[99] += +amp_sv[0];
      jamp_sv[101] -= amp_sv[0];
      jamp_sv[112] -= amp_sv[0];
      jamp_sv[118] += +amp_sv[0];

      // *** DIAGRAM 816 OF 1240 ***

      // Wavefunction(s) for diagram number 816
      // (none)

      // Amplitude(s) for diagram number 816
      FFV1_0( w_sv[90], w_sv[17], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[64] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[88] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 817 OF 1240 ***

      // Wavefunction(s) for diagram number 817
      // (none)

      // Amplitude(s) for diagram number 817
      FFV1_0( w_sv[90], w_sv[2], w_sv[42], COUPs[1], &amp_sv[0] );
      jamp_sv[64] += +amp_sv[0];
      jamp_sv[88] -= amp_sv[0];
      jamp_sv[112] -= amp_sv[0];
      jamp_sv[118] += +amp_sv[0];

      // *** DIAGRAM 818 OF 1240 ***

      // Wavefunction(s) for diagram number 818
      // (none)

      // Amplitude(s) for diagram number 818
      VVV1_0( w_sv[98], w_sv[103], w_sv[6], COUPs[0], &amp_sv[0] );
      jamp_sv[9] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[15] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[61] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[85] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[99] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[101] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[112] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[118] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 819 OF 1240 ***

      // Wavefunction(s) for diagram number 819
      // (none)

      // Amplitude(s) for diagram number 819
      FFV1_0( w_sv[21], w_sv[2], w_sv[98], COUPs[1], &amp_sv[0] );
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[61] -= amp_sv[0];
      jamp_sv[85] += +amp_sv[0];

      // *** DIAGRAM 820 OF 1240 ***

      // Wavefunction(s) for diagram number 820
      // (none)

      // Amplitude(s) for diagram number 820
      VVV1_0( w_sv[0], w_sv[103], w_sv[42], COUPs[0], &amp_sv[0] );
      jamp_sv[9] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[15] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[21] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[23] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[64] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[88] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[112] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[118] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 821 OF 1240 ***

      // Wavefunction(s) for diagram number 821
      // (none)

      // Amplitude(s) for diagram number 821
      FFV1_0( w_sv[21], w_sv[17], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[61] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[85] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 822 OF 1240 ***

      // Wavefunction(s) for diagram number 822
      // (none)

      // Amplitude(s) for diagram number 822
      FFV1_0( w_sv[52], w_sv[2], w_sv[85], COUPs[1], &amp_sv[0] );
      jamp_sv[9] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[15] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[21] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[23] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[64] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[88] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[112] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[118] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[52], w_sv[2], w_sv[112], COUPs[1], &amp_sv[0] );
      jamp_sv[21] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[23] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[61] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[64] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[85] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[88] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[99] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[101] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[52], w_sv[2], w_sv[111], COUPs[1], &amp_sv[0] );
      jamp_sv[9] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[15] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[61] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[85] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[99] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[101] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[112] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[118] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 823 OF 1240 ***

      // Wavefunction(s) for diagram number 823
      // (none)

      // Amplitude(s) for diagram number 823
      FFV1_0( w_sv[90], w_sv[15], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[70] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[112] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 824 OF 1240 ***

      // Wavefunction(s) for diagram number 824
      // (none)

      // Amplitude(s) for diagram number 824
      FFV1_0( w_sv[90], w_sv[2], w_sv[16], COUPs[1], &amp_sv[0] );
      jamp_sv[70] += +amp_sv[0];
      jamp_sv[88] -= amp_sv[0];
      jamp_sv[94] += +amp_sv[0];
      jamp_sv[112] -= amp_sv[0];

      // *** DIAGRAM 825 OF 1240 ***

      // Wavefunction(s) for diagram number 825
      // (none)

      // Amplitude(s) for diagram number 825
      VVV1_0( w_sv[101], w_sv[103], w_sv[5], COUPs[0], &amp_sv[0] );
      jamp_sv[11] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[21] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[67] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[75] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[77] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[88] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[94] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[109] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 826 OF 1240 ***

      // Wavefunction(s) for diagram number 826
      // (none)

      // Amplitude(s) for diagram number 826
      FFV1_0( w_sv[22], w_sv[2], w_sv[101], COUPs[1], &amp_sv[0] );
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[67] -= amp_sv[0];
      jamp_sv[109] += +amp_sv[0];

      // *** DIAGRAM 827 OF 1240 ***

      // Wavefunction(s) for diagram number 827
      // (none)

      // Amplitude(s) for diagram number 827
      VVV1_0( w_sv[0], w_sv[103], w_sv[16], COUPs[0], &amp_sv[0] );
      jamp_sv[11] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[15] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[17] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[21] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[70] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[88] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[94] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[112] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 828 OF 1240 ***

      // Wavefunction(s) for diagram number 828
      // (none)

      // Amplitude(s) for diagram number 828
      FFV1_0( w_sv[22], w_sv[15], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[67] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[109] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 829 OF 1240 ***

      // Wavefunction(s) for diagram number 829
      // (none)

      // Amplitude(s) for diagram number 829
      FFV1_0( w_sv[52], w_sv[2], w_sv[9], COUPs[1], &amp_sv[0] );
      jamp_sv[11] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[15] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[17] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[21] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[70] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[88] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[94] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[112] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[52], w_sv[2], w_sv[110], COUPs[1], &amp_sv[0] );
      jamp_sv[15] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[17] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[67] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[70] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[75] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[77] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[109] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[112] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[52], w_sv[2], w_sv[109], COUPs[1], &amp_sv[0] );
      jamp_sv[11] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[21] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[67] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[75] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[77] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[88] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[94] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[109] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 830 OF 1240 ***

      // Wavefunction(s) for diagram number 830
      // (none)

      // Amplitude(s) for diagram number 830
      FFV1_0( w_sv[90], w_sv[18], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[94] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[118] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 831 OF 1240 ***

      // Wavefunction(s) for diagram number 831
      // (none)

      // Amplitude(s) for diagram number 831
      FFV1_0( w_sv[90], w_sv[2], w_sv[19], COUPs[1], &amp_sv[0] );
      jamp_sv[64] += +amp_sv[0];
      jamp_sv[70] -= amp_sv[0];
      jamp_sv[94] -= amp_sv[0];
      jamp_sv[118] += +amp_sv[0];

      // *** DIAGRAM 832 OF 1240 ***

      // Wavefunction(s) for diagram number 832
      // (none)

      // Amplitude(s) for diagram number 832
      VVV1_0( w_sv[96], w_sv[103], w_sv[4], COUPs[0], &amp_sv[0] );
      jamp_sv[17] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[23] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[51] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[53] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[64] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[70] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[91] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[115] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 833 OF 1240 ***

      // Wavefunction(s) for diagram number 833
      // (none)

      // Amplitude(s) for diagram number 833
      FFV1_0( w_sv[56], w_sv[2], w_sv[96], COUPs[1], &amp_sv[0] );
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[23] -= amp_sv[0];
      jamp_sv[91] -= amp_sv[0];
      jamp_sv[115] += +amp_sv[0];

      // *** DIAGRAM 834 OF 1240 ***

      // Wavefunction(s) for diagram number 834
      // (none)

      // Amplitude(s) for diagram number 834
      VVV1_0( w_sv[0], w_sv[103], w_sv[19], COUPs[0], &amp_sv[0] );
      jamp_sv[9] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[11] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[17] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[23] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[64] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[70] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[94] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[118] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 835 OF 1240 ***

      // Wavefunction(s) for diagram number 835
      // (none)

      // Amplitude(s) for diagram number 835
      FFV1_0( w_sv[56], w_sv[18], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[91] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[115] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 836 OF 1240 ***

      // Wavefunction(s) for diagram number 836
      // (none)

      // Amplitude(s) for diagram number 836
      FFV1_0( w_sv[52], w_sv[2], w_sv[87], COUPs[1], &amp_sv[0] );
      jamp_sv[9] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[11] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[17] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[23] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[64] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[70] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[94] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[118] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[52], w_sv[2], w_sv[34], COUPs[1], &amp_sv[0] );
      jamp_sv[17] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[23] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[51] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[53] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[64] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[70] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[91] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[115] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[52], w_sv[2], w_sv[86], COUPs[1], &amp_sv[0] );
      jamp_sv[9] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[11] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[51] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[53] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[91] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[94] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[115] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[118] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 837 OF 1240 ***

      // Wavefunction(s) for diagram number 837
      // (none)

      // Amplitude(s) for diagram number 837
      FFV1_0( w_sv[90], w_sv[2], w_sv[30], COUPs[1], &amp_sv[0] );
      jamp_sv[64] += +amp_sv[0];
      jamp_sv[70] -= amp_sv[0];
      jamp_sv[94] -= amp_sv[0];
      jamp_sv[118] += +amp_sv[0];
      FFV1_0( w_sv[90], w_sv[2], w_sv[31], COUPs[1], &amp_sv[0] );
      jamp_sv[70] -= amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[94] -= amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      FFV1_0( w_sv[90], w_sv[2], w_sv[32], COUPs[1], &amp_sv[0] );
      jamp_sv[64] -= amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      jamp_sv[118] -= amp_sv[0];

      // *** DIAGRAM 838 OF 1240 ***

      // Wavefunction(s) for diagram number 838
      // (none)

      // Amplitude(s) for diagram number 838
      FFV1_0( w_sv[52], w_sv[2], w_sv[92], COUPs[1], &amp_sv[0] );
      jamp_sv[9] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[11] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[17] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[23] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[64] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[70] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[94] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[118] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[52], w_sv[2], w_sv[88], COUPs[1], &amp_sv[0] );
      jamp_sv[11] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[15] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[17] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[21] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[70] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[88] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[94] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[112] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[52], w_sv[2], w_sv[106], COUPs[1], &amp_sv[0] );
      jamp_sv[9] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[15] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[21] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[23] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[64] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[88] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[112] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[118] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 839 OF 1240 ***

      // Wavefunction(s) for diagram number 839
      VVV1P0_1( w_sv[0], w_sv[61], COUPs[0], 0., 0., w_sv[90] );

      // Amplitude(s) for diagram number 839
      VVV1_0( w_sv[90], w_sv[10], w_sv[6], COUPs[0], &amp_sv[0] );
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[31] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[74] -= amp_sv[0];
      jamp_sv[80] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[91] += +amp_sv[0];
      jamp_sv[93] += +amp_sv[0];
      jamp_sv[95] -= amp_sv[0];
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[98] -= amp_sv[0];
      jamp_sv[104] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];

      // *** DIAGRAM 840 OF 1240 ***

      // Wavefunction(s) for diagram number 840
      // (none)

      // Amplitude(s) for diagram number 840
      VVV1_0( w_sv[90], w_sv[11], w_sv[5], COUPs[0], &amp_sv[0] );
      jamp_sv[0] -= amp_sv[0];
      jamp_sv[6] += +amp_sv[0];
      jamp_sv[30] += +amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[74] -= amp_sv[0];
      jamp_sv[80] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[98] -= amp_sv[0];
      jamp_sv[104] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      jamp_sv[115] += +amp_sv[0];
      jamp_sv[117] += +amp_sv[0];
      jamp_sv[119] -= amp_sv[0];

      // *** DIAGRAM 841 OF 1240 ***

      // Wavefunction(s) for diagram number 841
      // (none)

      // Amplitude(s) for diagram number 841
      VVVV1_0( w_sv[8], w_sv[5], w_sv[6], w_sv[90], COUPs[2], &amp_sv[0] );
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[31] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[74] -= amp_sv[0];
      jamp_sv[80] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[91] += +amp_sv[0];
      jamp_sv[93] += +amp_sv[0];
      jamp_sv[95] -= amp_sv[0];
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[98] -= amp_sv[0];
      jamp_sv[104] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];
      VVVV3_0( w_sv[8], w_sv[5], w_sv[6], w_sv[90], COUPs[2], &amp_sv[0] );
      jamp_sv[0] -= amp_sv[0];
      jamp_sv[6] += +amp_sv[0];
      jamp_sv[30] += +amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[74] -= amp_sv[0];
      jamp_sv[80] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[98] -= amp_sv[0];
      jamp_sv[104] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      jamp_sv[115] += +amp_sv[0];
      jamp_sv[117] += +amp_sv[0];
      jamp_sv[119] -= amp_sv[0];
      VVVV4_0( w_sv[8], w_sv[5], w_sv[6], w_sv[90], COUPs[2], &amp_sv[0] );
      jamp_sv[0] -= amp_sv[0];
      jamp_sv[1] += +amp_sv[0];
      jamp_sv[6] += +amp_sv[0];
      jamp_sv[7] -= amp_sv[0];
      jamp_sv[30] += +amp_sv[0];
      jamp_sv[31] -= amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[55] += +amp_sv[0];
      jamp_sv[90] += +amp_sv[0];
      jamp_sv[91] -= amp_sv[0];
      jamp_sv[93] -= amp_sv[0];
      jamp_sv[95] += +amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      jamp_sv[115] += +amp_sv[0];
      jamp_sv[117] += +amp_sv[0];
      jamp_sv[119] -= amp_sv[0];

      // *** DIAGRAM 842 OF 1240 ***

      // Wavefunction(s) for diagram number 842
      VVV1P0_1( w_sv[0], w_sv[8], COUPs[0], 0., 0., w_sv[56] );

      // Amplitude(s) for diagram number 842
      VVV1_0( w_sv[56], w_sv[63], w_sv[6], COUPs[0], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[14] += +amp_sv[0];
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[20] += +amp_sv[0];
      jamp_sv[22] += +amp_sv[0];
      jamp_sv[23] -= amp_sv[0];
      jamp_sv[33] -= amp_sv[0];
      jamp_sv[57] += +amp_sv[0];
      jamp_sv[81] += +amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[105] += +amp_sv[0];
      jamp_sv[111] -= amp_sv[0];
      jamp_sv[117] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];

      // *** DIAGRAM 843 OF 1240 ***

      // Wavefunction(s) for diagram number 843
      // (none)

      // Amplitude(s) for diagram number 843
      VVV1_0( w_sv[56], w_sv[64], w_sv[5], COUPs[0], &amp_sv[0] );
      jamp_sv[1] += +amp_sv[0];
      jamp_sv[7] -= amp_sv[0];
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[14] += +amp_sv[0];
      jamp_sv[16] += +amp_sv[0];
      jamp_sv[17] -= amp_sv[0];
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[20] += +amp_sv[0];
      jamp_sv[35] -= amp_sv[0];
      jamp_sv[59] += +amp_sv[0];
      jamp_sv[81] += +amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[93] -= amp_sv[0];
      jamp_sv[95] += +amp_sv[0];
      jamp_sv[105] += +amp_sv[0];
      jamp_sv[111] -= amp_sv[0];

      // *** DIAGRAM 844 OF 1240 ***

      // Wavefunction(s) for diagram number 844
      // (none)

      // Amplitude(s) for diagram number 844
      VVVV1_0( w_sv[61], w_sv[5], w_sv[6], w_sv[56], COUPs[2], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[14] += +amp_sv[0];
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[20] += +amp_sv[0];
      jamp_sv[22] += +amp_sv[0];
      jamp_sv[23] -= amp_sv[0];
      jamp_sv[33] -= amp_sv[0];
      jamp_sv[57] += +amp_sv[0];
      jamp_sv[81] += +amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[105] += +amp_sv[0];
      jamp_sv[111] -= amp_sv[0];
      jamp_sv[117] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];
      VVVV3_0( w_sv[61], w_sv[5], w_sv[6], w_sv[56], COUPs[2], &amp_sv[0] );
      jamp_sv[1] += +amp_sv[0];
      jamp_sv[7] -= amp_sv[0];
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[14] += +amp_sv[0];
      jamp_sv[16] += +amp_sv[0];
      jamp_sv[17] -= amp_sv[0];
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[20] += +amp_sv[0];
      jamp_sv[35] -= amp_sv[0];
      jamp_sv[59] += +amp_sv[0];
      jamp_sv[81] += +amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[93] -= amp_sv[0];
      jamp_sv[95] += +amp_sv[0];
      jamp_sv[105] += +amp_sv[0];
      jamp_sv[111] -= amp_sv[0];
      VVVV4_0( w_sv[61], w_sv[5], w_sv[6], w_sv[56], COUPs[2], &amp_sv[0] );
      jamp_sv[0] -= amp_sv[0];
      jamp_sv[1] += +amp_sv[0];
      jamp_sv[6] += +amp_sv[0];
      jamp_sv[7] -= amp_sv[0];
      jamp_sv[16] += +amp_sv[0];
      jamp_sv[17] -= amp_sv[0];
      jamp_sv[22] -= amp_sv[0];
      jamp_sv[23] += +amp_sv[0];
      jamp_sv[33] += +amp_sv[0];
      jamp_sv[35] -= amp_sv[0];
      jamp_sv[57] -= amp_sv[0];
      jamp_sv[59] += +amp_sv[0];
      jamp_sv[93] -= amp_sv[0];
      jamp_sv[95] += +amp_sv[0];
      jamp_sv[117] += +amp_sv[0];
      jamp_sv[119] -= amp_sv[0];

      // *** DIAGRAM 845 OF 1240 ***

      // Wavefunction(s) for diagram number 845
      // (none)

      // Amplitude(s) for diagram number 845
      VVV1_0( w_sv[0], w_sv[63], w_sv[11], COUPs[0], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[14] += +amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[86] -= amp_sv[0];
      jamp_sv[96] -= amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      jamp_sv[101] -= amp_sv[0];
      jamp_sv[105] += +amp_sv[0];
      jamp_sv[111] -= amp_sv[0];
      jamp_sv[117] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];

      // *** DIAGRAM 846 OF 1240 ***

      // Wavefunction(s) for diagram number 846
      // (none)

      // Amplitude(s) for diagram number 846
      VVV1_0( w_sv[0], w_sv[64], w_sv[10], COUPs[0], &amp_sv[0] );
      jamp_sv[1] += +amp_sv[0];
      jamp_sv[7] -= amp_sv[0];
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[20] += +amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[72] -= amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[81] += +amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[93] -= amp_sv[0];
      jamp_sv[95] += +amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[110] -= amp_sv[0];

      // *** DIAGRAM 847 OF 1240 ***

      // Wavefunction(s) for diagram number 847
      VVVV1P0_1( w_sv[0], w_sv[61], w_sv[5], COUPs[2], 0., 0., w_sv[103] );
      VVVV3P0_1( w_sv[0], w_sv[61], w_sv[5], COUPs[2], 0., 0., w_sv[22] );
      VVVV4P0_1( w_sv[0], w_sv[61], w_sv[5], COUPs[2], 0., 0., w_sv[21] );

      // Amplitude(s) for diagram number 847
      VVV1_0( w_sv[8], w_sv[6], w_sv[103], COUPs[0], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[14] += +amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[86] -= amp_sv[0];
      jamp_sv[96] -= amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      jamp_sv[101] -= amp_sv[0];
      jamp_sv[105] += +amp_sv[0];
      jamp_sv[111] -= amp_sv[0];
      jamp_sv[117] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];
      VVV1_0( w_sv[8], w_sv[6], w_sv[22], COUPs[0], &amp_sv[0] );
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[14] += +amp_sv[0];
      jamp_sv[30] += +amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[74] -= amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      jamp_sv[101] -= amp_sv[0];
      jamp_sv[104] -= amp_sv[0];
      jamp_sv[105] += +amp_sv[0];
      jamp_sv[110] += +amp_sv[0];
      jamp_sv[111] -= amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      jamp_sv[115] += +amp_sv[0];
      VVV1_0( w_sv[8], w_sv[6], w_sv[21], COUPs[0], &amp_sv[0] );
      jamp_sv[0] -= amp_sv[0];
      jamp_sv[6] += +amp_sv[0];
      jamp_sv[30] += +amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[74] -= amp_sv[0];
      jamp_sv[80] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[98] -= amp_sv[0];
      jamp_sv[104] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      jamp_sv[115] += +amp_sv[0];
      jamp_sv[117] += +amp_sv[0];
      jamp_sv[119] -= amp_sv[0];

      // *** DIAGRAM 848 OF 1240 ***

      // Wavefunction(s) for diagram number 848
      VVVV1P0_1( w_sv[0], w_sv[61], w_sv[6], COUPs[2], 0., 0., w_sv[105] );
      VVVV3P0_1( w_sv[0], w_sv[61], w_sv[6], COUPs[2], 0., 0., w_sv[95] );
      VVVV4P0_1( w_sv[0], w_sv[61], w_sv[6], COUPs[2], 0., 0., w_sv[107] );

      // Amplitude(s) for diagram number 848
      VVV1_0( w_sv[8], w_sv[5], w_sv[105], COUPs[0], &amp_sv[0] );
      jamp_sv[1] += +amp_sv[0];
      jamp_sv[7] -= amp_sv[0];
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[20] += +amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[72] -= amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[81] += +amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[93] -= amp_sv[0];
      jamp_sv[95] += +amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[110] -= amp_sv[0];
      VVV1_0( w_sv[8], w_sv[5], w_sv[95], COUPs[0], &amp_sv[0] );
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[20] += +amp_sv[0];
      jamp_sv[31] += +amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[80] -= amp_sv[0];
      jamp_sv[81] += +amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[91] += +amp_sv[0];
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[98] -= amp_sv[0];
      VVV1_0( w_sv[8], w_sv[5], w_sv[107], COUPs[0], &amp_sv[0] );
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[31] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[74] -= amp_sv[0];
      jamp_sv[80] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[91] += +amp_sv[0];
      jamp_sv[93] += +amp_sv[0];
      jamp_sv[95] -= amp_sv[0];
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[98] -= amp_sv[0];
      jamp_sv[104] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];

      // *** DIAGRAM 849 OF 1240 ***

      // Wavefunction(s) for diagram number 849
      VVVV1P0_1( w_sv[0], w_sv[8], w_sv[5], COUPs[2], 0., 0., w_sv[115] );
      VVVV3P0_1( w_sv[0], w_sv[8], w_sv[5], COUPs[2], 0., 0., w_sv[116] );
      VVVV4P0_1( w_sv[0], w_sv[8], w_sv[5], COUPs[2], 0., 0., w_sv[117] );

      // Amplitude(s) for diagram number 849
      VVV1_0( w_sv[61], w_sv[6], w_sv[115], COUPs[0], &amp_sv[0] );
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[18] += +amp_sv[0];
      jamp_sv[20] -= amp_sv[0];
      jamp_sv[34] += +amp_sv[0];
      jamp_sv[58] -= amp_sv[0];
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[74] -= amp_sv[0];
      jamp_sv[76] -= amp_sv[0];
      jamp_sv[77] += +amp_sv[0];
      jamp_sv[81] -= amp_sv[0];
      jamp_sv[87] += +amp_sv[0];
      jamp_sv[93] += +amp_sv[0];
      jamp_sv[95] -= amp_sv[0];
      jamp_sv[104] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];
      VVV1_0( w_sv[61], w_sv[6], w_sv[116], COUPs[0], &amp_sv[0] );
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[14] += +amp_sv[0];
      jamp_sv[16] += +amp_sv[0];
      jamp_sv[17] -= amp_sv[0];
      jamp_sv[34] += +amp_sv[0];
      jamp_sv[35] -= amp_sv[0];
      jamp_sv[58] -= amp_sv[0];
      jamp_sv[59] += +amp_sv[0];
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[74] -= amp_sv[0];
      jamp_sv[76] -= amp_sv[0];
      jamp_sv[77] += +amp_sv[0];
      jamp_sv[104] -= amp_sv[0];
      jamp_sv[105] += +amp_sv[0];
      jamp_sv[110] += +amp_sv[0];
      jamp_sv[111] -= amp_sv[0];
      VVV1_0( w_sv[61], w_sv[6], w_sv[117], COUPs[0], &amp_sv[0] );
      jamp_sv[1] += +amp_sv[0];
      jamp_sv[7] -= amp_sv[0];
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[14] += +amp_sv[0];
      jamp_sv[16] += +amp_sv[0];
      jamp_sv[17] -= amp_sv[0];
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[20] += +amp_sv[0];
      jamp_sv[35] -= amp_sv[0];
      jamp_sv[59] += +amp_sv[0];
      jamp_sv[81] += +amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[93] -= amp_sv[0];
      jamp_sv[95] += +amp_sv[0];
      jamp_sv[105] += +amp_sv[0];
      jamp_sv[111] -= amp_sv[0];

      // *** DIAGRAM 850 OF 1240 ***

      // Wavefunction(s) for diagram number 850
      VVVV1P0_1( w_sv[0], w_sv[8], w_sv[6], COUPs[2], 0., 0., w_sv[118] );
      VVVV3P0_1( w_sv[0], w_sv[8], w_sv[6], COUPs[2], 0., 0., w_sv[119] );
      VVVV4P0_1( w_sv[0], w_sv[8], w_sv[6], COUPs[2], 0., 0., w_sv[120] );

      // Amplitude(s) for diagram number 850
      VVV1_0( w_sv[61], w_sv[5], w_sv[118], COUPs[0], &amp_sv[0] );
      jamp_sv[0] -= amp_sv[0];
      jamp_sv[6] += +amp_sv[0];
      jamp_sv[12] += +amp_sv[0];
      jamp_sv[14] -= amp_sv[0];
      jamp_sv[32] += +amp_sv[0];
      jamp_sv[56] -= amp_sv[0];
      jamp_sv[80] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[98] -= amp_sv[0];
      jamp_sv[100] -= amp_sv[0];
      jamp_sv[101] += +amp_sv[0];
      jamp_sv[105] -= amp_sv[0];
      jamp_sv[111] += +amp_sv[0];
      jamp_sv[117] += +amp_sv[0];
      jamp_sv[119] -= amp_sv[0];
      VVV1_0( w_sv[61], w_sv[5], w_sv[119], COUPs[0], &amp_sv[0] );
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[20] += +amp_sv[0];
      jamp_sv[22] += +amp_sv[0];
      jamp_sv[23] -= amp_sv[0];
      jamp_sv[32] += +amp_sv[0];
      jamp_sv[33] -= amp_sv[0];
      jamp_sv[56] -= amp_sv[0];
      jamp_sv[57] += +amp_sv[0];
      jamp_sv[80] -= amp_sv[0];
      jamp_sv[81] += +amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[98] -= amp_sv[0];
      jamp_sv[100] -= amp_sv[0];
      jamp_sv[101] += +amp_sv[0];
      VVV1_0( w_sv[61], w_sv[5], w_sv[120], COUPs[0], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[14] += +amp_sv[0];
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[20] += +amp_sv[0];
      jamp_sv[22] += +amp_sv[0];
      jamp_sv[23] -= amp_sv[0];
      jamp_sv[33] -= amp_sv[0];
      jamp_sv[57] += +amp_sv[0];
      jamp_sv[81] += +amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[105] += +amp_sv[0];
      jamp_sv[111] -= amp_sv[0];
      jamp_sv[117] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];

      // *** DIAGRAM 851 OF 1240 ***

      // Wavefunction(s) for diagram number 851
      // (none)

      // Amplitude(s) for diagram number 851
      VVVV1_0( w_sv[0], w_sv[61], w_sv[8], w_sv[29], COUPs[2], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[30] -= amp_sv[0];
      jamp_sv[31] += +amp_sv[0];
      jamp_sv[54] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[91] += +amp_sv[0];
      jamp_sv[93] += +amp_sv[0];
      jamp_sv[95] -= amp_sv[0];
      jamp_sv[114] += +amp_sv[0];
      jamp_sv[115] -= amp_sv[0];
      jamp_sv[117] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];
      VVVV3_0( w_sv[0], w_sv[61], w_sv[8], w_sv[29], COUPs[2], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[22] += +amp_sv[0];
      jamp_sv[23] -= amp_sv[0];
      jamp_sv[33] -= amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[57] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[93] += +amp_sv[0];
      jamp_sv[95] -= amp_sv[0];
      jamp_sv[117] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];
      VVVV4_0( w_sv[0], w_sv[61], w_sv[8], w_sv[29], COUPs[2], &amp_sv[0] );
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[22] += +amp_sv[0];
      jamp_sv[23] -= amp_sv[0];
      jamp_sv[30] += +amp_sv[0];
      jamp_sv[31] -= amp_sv[0];
      jamp_sv[33] -= amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[55] += +amp_sv[0];
      jamp_sv[57] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[90] += +amp_sv[0];
      jamp_sv[91] -= amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      jamp_sv[115] += +amp_sv[0];

      // *** DIAGRAM 852 OF 1240 ***

      // Wavefunction(s) for diagram number 852
      // (none)

      // Amplitude(s) for diagram number 852
      VVV1_0( w_sv[8], w_sv[29], w_sv[90], COUPs[0], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[30] -= amp_sv[0];
      jamp_sv[31] += +amp_sv[0];
      jamp_sv[54] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[91] += +amp_sv[0];
      jamp_sv[93] += +amp_sv[0];
      jamp_sv[95] -= amp_sv[0];
      jamp_sv[114] += +amp_sv[0];
      jamp_sv[115] -= amp_sv[0];
      jamp_sv[117] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];

      // *** DIAGRAM 853 OF 1240 ***

      // Wavefunction(s) for diagram number 853
      // (none)

      // Amplitude(s) for diagram number 853
      VVV1_0( w_sv[61], w_sv[29], w_sv[56], COUPs[0], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[22] += +amp_sv[0];
      jamp_sv[23] -= amp_sv[0];
      jamp_sv[33] -= amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[57] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[93] += +amp_sv[0];
      jamp_sv[95] -= amp_sv[0];
      jamp_sv[117] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];

      // *** DIAGRAM 854 OF 1240 ***

      // Wavefunction(s) for diagram number 854
      // (none)

      // Amplitude(s) for diagram number 854
      VVV1_0( w_sv[61], w_sv[8], w_sv[96], COUPs[0], &amp_sv[0] );
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[22] += +amp_sv[0];
      jamp_sv[23] -= amp_sv[0];
      jamp_sv[30] += +amp_sv[0];
      jamp_sv[31] -= amp_sv[0];
      jamp_sv[33] -= amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[55] += +amp_sv[0];
      jamp_sv[57] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[90] += +amp_sv[0];
      jamp_sv[91] -= amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      jamp_sv[115] += +amp_sv[0];

      // *** DIAGRAM 855 OF 1240 ***

      // Wavefunction(s) for diagram number 855
      // (none)

      // Amplitude(s) for diagram number 855
      VVV1_0( w_sv[90], w_sv[45], w_sv[6], COUPs[0], &amp_sv[0] );
      jamp_sv[72] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[74] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[80] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[86] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[90] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[91] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[93] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[95] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 856 OF 1240 ***

      // Wavefunction(s) for diagram number 856
      // (none)

      // Amplitude(s) for diagram number 856
      FFV1_0( w_sv[3], w_sv[44], w_sv[90], COUPs[1], &amp_sv[0] );
      jamp_sv[90] += +amp_sv[0];
      jamp_sv[91] -= amp_sv[0];
      jamp_sv[93] -= amp_sv[0];
      jamp_sv[95] += +amp_sv[0];

      // *** DIAGRAM 857 OF 1240 ***

      // Wavefunction(s) for diagram number 857
      // (none)

      // Amplitude(s) for diagram number 857
      FFV1_0( w_sv[65], w_sv[102], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[76] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[77] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 858 OF 1240 ***

      // Wavefunction(s) for diagram number 858
      // (none)

      // Amplitude(s) for diagram number 858
      FFV1_0( w_sv[3], w_sv[102], w_sv[64], COUPs[1], &amp_sv[0] );
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[74] -= amp_sv[0];
      jamp_sv[76] -= amp_sv[0];
      jamp_sv[77] += +amp_sv[0];

      // *** DIAGRAM 859 OF 1240 ***

      // Wavefunction(s) for diagram number 859
      // (none)

      // Amplitude(s) for diagram number 859
      FFV1_0( w_sv[65], w_sv[44], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[90] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[91] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 860 OF 1240 ***

      // Wavefunction(s) for diagram number 860
      // (none)

      // Amplitude(s) for diagram number 860
      VVV1_0( w_sv[0], w_sv[64], w_sv[45], COUPs[0], &amp_sv[0] );
      jamp_sv[72] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[74] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[76] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[77] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[81] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[87] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[93] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[95] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 861 OF 1240 ***

      // Wavefunction(s) for diagram number 861
      // (none)

      // Amplitude(s) for diagram number 861
      FFV1_0( w_sv[3], w_sv[39], w_sv[105], COUPs[1], &amp_sv[0] );
      jamp_sv[72] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[74] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[76] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[77] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[81] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[87] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[93] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[95] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[39], w_sv[95], COUPs[1], &amp_sv[0] );
      jamp_sv[76] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[77] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[80] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[81] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[86] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[87] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[90] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[91] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[39], w_sv[107], COUPs[1], &amp_sv[0] );
      jamp_sv[72] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[74] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[80] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[86] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[90] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[91] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[93] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[95] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 862 OF 1240 ***

      // Wavefunction(s) for diagram number 862
      // (none)

      // Amplitude(s) for diagram number 862
      FFV1_0( w_sv[41], w_sv[39], w_sv[90], COUPs[1], &amp_sv[0] );
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[74] -= amp_sv[0];
      jamp_sv[80] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];

      // *** DIAGRAM 863 OF 1240 ***

      // Wavefunction(s) for diagram number 863
      // (none)

      // Amplitude(s) for diagram number 863
      FFV1_0( w_sv[41], w_sv[102], w_sv[61], COUPs[1], &amp_sv[0] );
      jamp_sv[72] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[74] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 864 OF 1240 ***

      // Wavefunction(s) for diagram number 864
      // (none)

      // Amplitude(s) for diagram number 864
      FFV1_0( w_sv[62], w_sv[39], w_sv[61], COUPs[1], &amp_sv[0] );
      jamp_sv[80] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[86] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 865 OF 1240 ***

      // Wavefunction(s) for diagram number 865
      // (none)

      // Amplitude(s) for diagram number 865
      VVV1_0( w_sv[90], w_sv[51], w_sv[5], COUPs[0], &amp_sv[0] );
      jamp_sv[96] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[98] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[104] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[110] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[114] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[115] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[117] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[119] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 866 OF 1240 ***

      // Wavefunction(s) for diagram number 866
      // (none)

      // Amplitude(s) for diagram number 866
      FFV1_0( w_sv[3], w_sv[50], w_sv[90], COUPs[1], &amp_sv[0] );
      jamp_sv[114] += +amp_sv[0];
      jamp_sv[115] -= amp_sv[0];
      jamp_sv[117] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];

      // *** DIAGRAM 867 OF 1240 ***

      // Wavefunction(s) for diagram number 867
      // (none)

      // Amplitude(s) for diagram number 867
      FFV1_0( w_sv[65], w_sv[113], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[100] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[101] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 868 OF 1240 ***

      // Wavefunction(s) for diagram number 868
      // (none)

      // Amplitude(s) for diagram number 868
      FFV1_0( w_sv[3], w_sv[113], w_sv[63], COUPs[1], &amp_sv[0] );
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[98] -= amp_sv[0];
      jamp_sv[100] -= amp_sv[0];
      jamp_sv[101] += +amp_sv[0];

      // *** DIAGRAM 869 OF 1240 ***

      // Wavefunction(s) for diagram number 869
      // (none)

      // Amplitude(s) for diagram number 869
      FFV1_0( w_sv[65], w_sv[50], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[114] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[115] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 870 OF 1240 ***

      // Wavefunction(s) for diagram number 870
      // (none)

      // Amplitude(s) for diagram number 870
      VVV1_0( w_sv[0], w_sv[63], w_sv[51], COUPs[0], &amp_sv[0] );
      jamp_sv[96] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[98] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[100] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[101] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[105] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[111] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[117] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[119] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 871 OF 1240 ***

      // Wavefunction(s) for diagram number 871
      // (none)

      // Amplitude(s) for diagram number 871
      FFV1_0( w_sv[3], w_sv[47], w_sv[103], COUPs[1], &amp_sv[0] );
      jamp_sv[96] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[98] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[100] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[101] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[105] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[111] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[117] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[119] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[47], w_sv[22], COUPs[1], &amp_sv[0] );
      jamp_sv[100] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[101] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[104] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[105] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[110] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[111] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[114] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[115] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[47], w_sv[21], COUPs[1], &amp_sv[0] );
      jamp_sv[96] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[98] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[104] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[110] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[114] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[115] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[117] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[119] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 872 OF 1240 ***

      // Wavefunction(s) for diagram number 872
      // (none)

      // Amplitude(s) for diagram number 872
      FFV1_0( w_sv[38], w_sv[47], w_sv[90], COUPs[1], &amp_sv[0] );
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[98] -= amp_sv[0];
      jamp_sv[104] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];

      // *** DIAGRAM 873 OF 1240 ***

      // Wavefunction(s) for diagram number 873
      // (none)

      // Amplitude(s) for diagram number 873
      FFV1_0( w_sv[38], w_sv[113], w_sv[61], COUPs[1], &amp_sv[0] );
      jamp_sv[96] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[98] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 874 OF 1240 ***

      // Wavefunction(s) for diagram number 874
      // (none)

      // Amplitude(s) for diagram number 874
      FFV1_0( w_sv[104], w_sv[47], w_sv[61], COUPs[1], &amp_sv[0] );
      jamp_sv[104] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[110] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 875 OF 1240 ***

      // Wavefunction(s) for diagram number 875
      // (none)

      // Amplitude(s) for diagram number 875
      VVV1_0( w_sv[90], w_sv[23], w_sv[6], COUPs[0], &amp_sv[0] );
      jamp_sv[1] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[7] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[31] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[55] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[96] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[98] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[104] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[110] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 876 OF 1240 ***

      // Wavefunction(s) for diagram number 876
      // (none)

      // Amplitude(s) for diagram number 876
      FFV1_0( w_sv[48], w_sv[2], w_sv[90], COUPs[1], &amp_sv[0] );
      jamp_sv[1] += +amp_sv[0];
      jamp_sv[7] -= amp_sv[0];
      jamp_sv[31] -= amp_sv[0];
      jamp_sv[55] += +amp_sv[0];

      // *** DIAGRAM 877 OF 1240 ***

      // Wavefunction(s) for diagram number 877
      // (none)

      // Amplitude(s) for diagram number 877
      FFV1_0( w_sv[104], w_sv[93], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[34] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[58] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 878 OF 1240 ***

      // Wavefunction(s) for diagram number 878
      // (none)

      // Amplitude(s) for diagram number 878
      FFV1_0( w_sv[104], w_sv[2], w_sv[64], COUPs[1], &amp_sv[0] );
      jamp_sv[34] += +amp_sv[0];
      jamp_sv[58] -= amp_sv[0];
      jamp_sv[104] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];

      // *** DIAGRAM 879 OF 1240 ***

      // Wavefunction(s) for diagram number 879
      // (none)

      // Amplitude(s) for diagram number 879
      FFV1_0( w_sv[48], w_sv[93], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[31] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[55] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 880 OF 1240 ***

      // Wavefunction(s) for diagram number 880
      // (none)

      // Amplitude(s) for diagram number 880
      VVV1_0( w_sv[0], w_sv[64], w_sv[23], COUPs[0], &amp_sv[0] );
      jamp_sv[1] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[7] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[18] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[20] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[34] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[58] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[104] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[110] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 881 OF 1240 ***

      // Wavefunction(s) for diagram number 881
      // (none)

      // Amplitude(s) for diagram number 881
      FFV1_0( w_sv[38], w_sv[2], w_sv[105], COUPs[1], &amp_sv[0] );
      jamp_sv[1] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[7] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[18] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[20] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[34] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[58] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[104] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[110] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[38], w_sv[2], w_sv[95], COUPs[1], &amp_sv[0] );
      jamp_sv[18] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[20] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[31] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[34] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[55] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[58] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[96] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[98] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[38], w_sv[2], w_sv[107], COUPs[1], &amp_sv[0] );
      jamp_sv[1] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[7] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[31] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[55] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[96] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[98] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[104] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[110] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 882 OF 1240 ***

      // Wavefunction(s) for diagram number 882
      // (none)

      // Amplitude(s) for diagram number 882
      VVV1_0( w_sv[90], w_sv[20], w_sv[5], COUPs[0], &amp_sv[0] );
      jamp_sv[0] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[6] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[30] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[54] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[72] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[74] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[80] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[86] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 883 OF 1240 ***

      // Wavefunction(s) for diagram number 883
      // (none)

      // Amplitude(s) for diagram number 883
      FFV1_0( w_sv[40], w_sv[2], w_sv[90], COUPs[1], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[30] -= amp_sv[0];
      jamp_sv[54] += +amp_sv[0];

      // *** DIAGRAM 884 OF 1240 ***

      // Wavefunction(s) for diagram number 884
      // (none)

      // Amplitude(s) for diagram number 884
      FFV1_0( w_sv[62], w_sv[93], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[32] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[56] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 885 OF 1240 ***

      // Wavefunction(s) for diagram number 885
      // (none)

      // Amplitude(s) for diagram number 885
      FFV1_0( w_sv[62], w_sv[2], w_sv[63], COUPs[1], &amp_sv[0] );
      jamp_sv[32] += +amp_sv[0];
      jamp_sv[56] -= amp_sv[0];
      jamp_sv[80] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];

      // *** DIAGRAM 886 OF 1240 ***

      // Wavefunction(s) for diagram number 886
      // (none)

      // Amplitude(s) for diagram number 886
      FFV1_0( w_sv[40], w_sv[93], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[30] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[54] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 887 OF 1240 ***

      // Wavefunction(s) for diagram number 887
      // (none)

      // Amplitude(s) for diagram number 887
      VVV1_0( w_sv[0], w_sv[63], w_sv[20], COUPs[0], &amp_sv[0] );
      jamp_sv[0] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[6] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[12] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[14] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[32] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[56] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[80] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[86] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 888 OF 1240 ***

      // Wavefunction(s) for diagram number 888
      // (none)

      // Amplitude(s) for diagram number 888
      FFV1_0( w_sv[41], w_sv[2], w_sv[103], COUPs[1], &amp_sv[0] );
      jamp_sv[0] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[6] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[12] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[14] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[32] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[56] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[80] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[86] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[41], w_sv[2], w_sv[22], COUPs[1], &amp_sv[0] );
      jamp_sv[12] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[14] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[30] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[32] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[54] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[56] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[72] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[74] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[41], w_sv[2], w_sv[21], COUPs[1], &amp_sv[0] );
      jamp_sv[0] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[6] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[30] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[54] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[72] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[74] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[80] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[86] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 889 OF 1240 ***

      // Wavefunction(s) for diagram number 889
      // (none)

      // Amplitude(s) for diagram number 889
      FFV1_0( w_sv[3], w_sv[18], w_sv[90], COUPs[1], &amp_sv[0] );
      jamp_sv[90] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[91] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[93] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[95] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[114] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[115] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[117] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[119] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 890 OF 1240 ***

      // Wavefunction(s) for diagram number 890
      // (none)

      // Amplitude(s) for diagram number 890
      FFV1_0( w_sv[12], w_sv[2], w_sv[90], COUPs[1], &amp_sv[0] );
      jamp_sv[0] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[1] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[6] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[7] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[30] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[31] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[54] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[55] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 891 OF 1240 ***

      // Wavefunction(s) for diagram number 891
      // (none)

      // Amplitude(s) for diagram number 891
      FFV1_0( w_sv[3], w_sv[93], w_sv[96], COUPs[1], &amp_sv[0] );
      jamp_sv[30] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[31] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[33] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[35] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[54] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[55] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[57] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[59] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 892 OF 1240 ***

      // Wavefunction(s) for diagram number 892
      // (none)

      // Amplitude(s) for diagram number 892
      FFV1_0( w_sv[65], w_sv[2], w_sv[96], COUPs[1], &amp_sv[0] );
      jamp_sv[16] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[17] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[22] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[23] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[90] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[91] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[114] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[115] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 893 OF 1240 ***

      // Wavefunction(s) for diagram number 893
      // (none)

      // Amplitude(s) for diagram number 893
      FFV1_0( w_sv[12], w_sv[93], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[30] += +amp_sv[0];
      jamp_sv[31] -= amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[55] += +amp_sv[0];

      // *** DIAGRAM 894 OF 1240 ***

      // Wavefunction(s) for diagram number 894
      // (none)

      // Amplitude(s) for diagram number 894
      FFV1_0( w_sv[65], w_sv[18], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[90] += +amp_sv[0];
      jamp_sv[91] -= amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      jamp_sv[115] += +amp_sv[0];

      // *** DIAGRAM 895 OF 1240 ***

      // Wavefunction(s) for diagram number 895
      VVV1P0_1( w_sv[0], w_sv[66], COUPs[0], 0., 0., w_sv[65] );

      // Amplitude(s) for diagram number 895
      VVV1_0( w_sv[65], w_sv[13], w_sv[6], COUPs[0], &amp_sv[0] );
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[37] += +amp_sv[0];
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[50] -= amp_sv[0];
      jamp_sv[56] -= amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[67] += +amp_sv[0];
      jamp_sv[69] += +amp_sv[0];
      jamp_sv[71] -= amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[97] += +amp_sv[0];
      jamp_sv[100] -= amp_sv[0];
      jamp_sv[106] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];

      // *** DIAGRAM 896 OF 1240 ***

      // Wavefunction(s) for diagram number 896
      // (none)

      // Amplitude(s) for diagram number 896
      VVV1_0( w_sv[65], w_sv[11], w_sv[4], COUPs[0], &amp_sv[0] );
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[12] += +amp_sv[0];
      jamp_sv[36] += +amp_sv[0];
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[50] -= amp_sv[0];
      jamp_sv[56] -= amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[97] += +amp_sv[0];
      jamp_sv[100] -= amp_sv[0];
      jamp_sv[106] -= amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      jamp_sv[109] += +amp_sv[0];
      jamp_sv[111] += +amp_sv[0];
      jamp_sv[113] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];

      // *** DIAGRAM 897 OF 1240 ***

      // Wavefunction(s) for diagram number 897
      // (none)

      // Amplitude(s) for diagram number 897
      VVVV1_0( w_sv[8], w_sv[4], w_sv[6], w_sv[65], COUPs[2], &amp_sv[0] );
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[37] += +amp_sv[0];
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[50] -= amp_sv[0];
      jamp_sv[56] -= amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[67] += +amp_sv[0];
      jamp_sv[69] += +amp_sv[0];
      jamp_sv[71] -= amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[97] += +amp_sv[0];
      jamp_sv[100] -= amp_sv[0];
      jamp_sv[106] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];
      VVVV3_0( w_sv[8], w_sv[4], w_sv[6], w_sv[65], COUPs[2], &amp_sv[0] );
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[12] += +amp_sv[0];
      jamp_sv[36] += +amp_sv[0];
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[50] -= amp_sv[0];
      jamp_sv[56] -= amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[97] += +amp_sv[0];
      jamp_sv[100] -= amp_sv[0];
      jamp_sv[106] -= amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      jamp_sv[109] += +amp_sv[0];
      jamp_sv[111] += +amp_sv[0];
      jamp_sv[113] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];
      VVVV4_0( w_sv[8], w_sv[4], w_sv[6], w_sv[65], COUPs[2], &amp_sv[0] );
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[3] += +amp_sv[0];
      jamp_sv[12] += +amp_sv[0];
      jamp_sv[13] -= amp_sv[0];
      jamp_sv[36] += +amp_sv[0];
      jamp_sv[37] -= amp_sv[0];
      jamp_sv[66] += +amp_sv[0];
      jamp_sv[67] -= amp_sv[0];
      jamp_sv[69] -= amp_sv[0];
      jamp_sv[71] += +amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[79] += +amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      jamp_sv[109] += +amp_sv[0];
      jamp_sv[111] += +amp_sv[0];
      jamp_sv[113] -= amp_sv[0];

      // *** DIAGRAM 898 OF 1240 ***

      // Wavefunction(s) for diagram number 898
      // (none)

      // Amplitude(s) for diagram number 898
      VVV1_0( w_sv[56], w_sv[69], w_sv[6], COUPs[0], &amp_sv[0] );
      jamp_sv[2] += +amp_sv[0];
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[8] += +amp_sv[0];
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[19] -= amp_sv[0];
      jamp_sv[20] += +amp_sv[0];
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[22] += +amp_sv[0];
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[57] += +amp_sv[0];
      jamp_sv[63] -= amp_sv[0];
      jamp_sv[81] += +amp_sv[0];
      jamp_sv[107] += +amp_sv[0];
      jamp_sv[111] -= amp_sv[0];
      jamp_sv[113] += +amp_sv[0];
      jamp_sv[117] -= amp_sv[0];

      // *** DIAGRAM 899 OF 1240 ***

      // Wavefunction(s) for diagram number 899
      // (none)

      // Amplitude(s) for diagram number 899
      VVV1_0( w_sv[56], w_sv[70], w_sv[4], COUPs[0], &amp_sv[0] );
      jamp_sv[3] += +amp_sv[0];
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[8] += +amp_sv[0];
      jamp_sv[10] += +amp_sv[0];
      jamp_sv[11] -= amp_sv[0];
      jamp_sv[13] -= amp_sv[0];
      jamp_sv[19] -= amp_sv[0];
      jamp_sv[22] += +amp_sv[0];
      jamp_sv[41] -= amp_sv[0];
      jamp_sv[57] += +amp_sv[0];
      jamp_sv[63] -= amp_sv[0];
      jamp_sv[69] -= amp_sv[0];
      jamp_sv[71] += +amp_sv[0];
      jamp_sv[83] += +amp_sv[0];
      jamp_sv[107] += +amp_sv[0];
      jamp_sv[117] -= amp_sv[0];

      // *** DIAGRAM 900 OF 1240 ***

      // Wavefunction(s) for diagram number 900
      // (none)

      // Amplitude(s) for diagram number 900
      VVVV1_0( w_sv[66], w_sv[4], w_sv[6], w_sv[56], COUPs[2], &amp_sv[0] );
      jamp_sv[2] += +amp_sv[0];
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[8] += +amp_sv[0];
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[19] -= amp_sv[0];
      jamp_sv[20] += +amp_sv[0];
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[22] += +amp_sv[0];
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[57] += +amp_sv[0];
      jamp_sv[63] -= amp_sv[0];
      jamp_sv[81] += +amp_sv[0];
      jamp_sv[107] += +amp_sv[0];
      jamp_sv[111] -= amp_sv[0];
      jamp_sv[113] += +amp_sv[0];
      jamp_sv[117] -= amp_sv[0];
      VVVV3_0( w_sv[66], w_sv[4], w_sv[6], w_sv[56], COUPs[2], &amp_sv[0] );
      jamp_sv[3] += +amp_sv[0];
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[8] += +amp_sv[0];
      jamp_sv[10] += +amp_sv[0];
      jamp_sv[11] -= amp_sv[0];
      jamp_sv[13] -= amp_sv[0];
      jamp_sv[19] -= amp_sv[0];
      jamp_sv[22] += +amp_sv[0];
      jamp_sv[41] -= amp_sv[0];
      jamp_sv[57] += +amp_sv[0];
      jamp_sv[63] -= amp_sv[0];
      jamp_sv[69] -= amp_sv[0];
      jamp_sv[71] += +amp_sv[0];
      jamp_sv[83] += +amp_sv[0];
      jamp_sv[107] += +amp_sv[0];
      jamp_sv[117] -= amp_sv[0];
      VVVV4_0( w_sv[66], w_sv[4], w_sv[6], w_sv[56], COUPs[2], &amp_sv[0] );
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[3] += +amp_sv[0];
      jamp_sv[10] += +amp_sv[0];
      jamp_sv[11] -= amp_sv[0];
      jamp_sv[12] += +amp_sv[0];
      jamp_sv[13] -= amp_sv[0];
      jamp_sv[20] -= amp_sv[0];
      jamp_sv[21] += +amp_sv[0];
      jamp_sv[39] += +amp_sv[0];
      jamp_sv[41] -= amp_sv[0];
      jamp_sv[69] -= amp_sv[0];
      jamp_sv[71] += +amp_sv[0];
      jamp_sv[81] -= amp_sv[0];
      jamp_sv[83] += +amp_sv[0];
      jamp_sv[111] += +amp_sv[0];
      jamp_sv[113] -= amp_sv[0];

      // *** DIAGRAM 901 OF 1240 ***

      // Wavefunction(s) for diagram number 901
      // (none)

      // Amplitude(s) for diagram number 901
      VVV1_0( w_sv[0], w_sv[69], w_sv[11], COUPs[0], &amp_sv[0] );
      jamp_sv[2] += +amp_sv[0];
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[8] += +amp_sv[0];
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[62] -= amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[97] -= amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      jamp_sv[99] -= amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      jamp_sv[107] += +amp_sv[0];
      jamp_sv[111] -= amp_sv[0];
      jamp_sv[113] += +amp_sv[0];
      jamp_sv[117] -= amp_sv[0];

      // *** DIAGRAM 902 OF 1240 ***

      // Wavefunction(s) for diagram number 902
      // (none)

      // Amplitude(s) for diagram number 902
      VVV1_0( w_sv[0], w_sv[70], w_sv[13], COUPs[0], &amp_sv[0] );
      jamp_sv[3] += +amp_sv[0];
      jamp_sv[13] -= amp_sv[0];
      jamp_sv[19] -= amp_sv[0];
      jamp_sv[22] += +amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[48] -= amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[57] += +amp_sv[0];
      jamp_sv[63] -= amp_sv[0];
      jamp_sv[69] -= amp_sv[0];
      jamp_sv[71] += +amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      jamp_sv[116] -= amp_sv[0];

      // *** DIAGRAM 903 OF 1240 ***

      // Wavefunction(s) for diagram number 903
      VVVV1P0_1( w_sv[0], w_sv[66], w_sv[4], COUPs[2], 0., 0., w_sv[93] );
      VVVV3P0_1( w_sv[0], w_sv[66], w_sv[4], COUPs[2], 0., 0., w_sv[90] );
      VVVV4P0_1( w_sv[0], w_sv[66], w_sv[4], COUPs[2], 0., 0., w_sv[21] );

      // Amplitude(s) for diagram number 903
      VVV1_0( w_sv[8], w_sv[6], w_sv[93], COUPs[0], &amp_sv[0] );
      jamp_sv[2] += +amp_sv[0];
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[8] += +amp_sv[0];
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[62] -= amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[97] -= amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      jamp_sv[99] -= amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      jamp_sv[107] += +amp_sv[0];
      jamp_sv[111] -= amp_sv[0];
      jamp_sv[113] += +amp_sv[0];
      jamp_sv[117] -= amp_sv[0];
      VVV1_0( w_sv[8], w_sv[6], w_sv[90], COUPs[0], &amp_sv[0] );
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[8] += +amp_sv[0];
      jamp_sv[36] += +amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[50] -= amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      jamp_sv[99] -= amp_sv[0];
      jamp_sv[106] -= amp_sv[0];
      jamp_sv[107] += +amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      jamp_sv[109] += +amp_sv[0];
      jamp_sv[116] += +amp_sv[0];
      jamp_sv[117] -= amp_sv[0];
      VVV1_0( w_sv[8], w_sv[6], w_sv[21], COUPs[0], &amp_sv[0] );
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[12] += +amp_sv[0];
      jamp_sv[36] += +amp_sv[0];
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[50] -= amp_sv[0];
      jamp_sv[56] -= amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[97] += +amp_sv[0];
      jamp_sv[100] -= amp_sv[0];
      jamp_sv[106] -= amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      jamp_sv[109] += +amp_sv[0];
      jamp_sv[111] += +amp_sv[0];
      jamp_sv[113] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];

      // *** DIAGRAM 904 OF 1240 ***

      // Wavefunction(s) for diagram number 904
      VVVV1P0_1( w_sv[0], w_sv[66], w_sv[6], COUPs[2], 0., 0., w_sv[22] );
      VVVV3P0_1( w_sv[0], w_sv[66], w_sv[6], COUPs[2], 0., 0., w_sv[103] );
      VVVV4P0_1( w_sv[0], w_sv[66], w_sv[6], COUPs[2], 0., 0., w_sv[63] );

      // Amplitude(s) for diagram number 904
      VVV1_0( w_sv[8], w_sv[4], w_sv[22], COUPs[0], &amp_sv[0] );
      jamp_sv[3] += +amp_sv[0];
      jamp_sv[13] -= amp_sv[0];
      jamp_sv[19] -= amp_sv[0];
      jamp_sv[22] += +amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[48] -= amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[57] += +amp_sv[0];
      jamp_sv[63] -= amp_sv[0];
      jamp_sv[69] -= amp_sv[0];
      jamp_sv[71] += +amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      jamp_sv[116] -= amp_sv[0];
      VVV1_0( w_sv[8], w_sv[4], w_sv[103], COUPs[0], &amp_sv[0] );
      jamp_sv[19] -= amp_sv[0];
      jamp_sv[22] += +amp_sv[0];
      jamp_sv[37] += +amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[56] -= amp_sv[0];
      jamp_sv[57] += +amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[63] -= amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[67] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[97] += +amp_sv[0];
      jamp_sv[100] -= amp_sv[0];
      VVV1_0( w_sv[8], w_sv[4], w_sv[63], COUPs[0], &amp_sv[0] );
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[37] += +amp_sv[0];
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[50] -= amp_sv[0];
      jamp_sv[56] -= amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[67] += +amp_sv[0];
      jamp_sv[69] += +amp_sv[0];
      jamp_sv[71] -= amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[97] += +amp_sv[0];
      jamp_sv[100] -= amp_sv[0];
      jamp_sv[106] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];

      // *** DIAGRAM 905 OF 1240 ***

      // Wavefunction(s) for diagram number 905
      VVVV1P0_1( w_sv[0], w_sv[8], w_sv[4], COUPs[2], 0., 0., w_sv[107] );
      VVVV3P0_1( w_sv[0], w_sv[8], w_sv[4], COUPs[2], 0., 0., w_sv[95] );
      VVVV4P0_1( w_sv[0], w_sv[8], w_sv[4], COUPs[2], 0., 0., w_sv[105] );

      // Amplitude(s) for diagram number 905
      VVV1_0( w_sv[66], w_sv[6], w_sv[107], COUPs[0], &amp_sv[0] );
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[19] += +amp_sv[0];
      jamp_sv[22] -= amp_sv[0];
      jamp_sv[40] += +amp_sv[0];
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[50] -= amp_sv[0];
      jamp_sv[52] -= amp_sv[0];
      jamp_sv[53] += +amp_sv[0];
      jamp_sv[57] -= amp_sv[0];
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[69] += +amp_sv[0];
      jamp_sv[71] -= amp_sv[0];
      jamp_sv[82] -= amp_sv[0];
      jamp_sv[106] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];
      VVV1_0( w_sv[66], w_sv[6], w_sv[95], COUPs[0], &amp_sv[0] );
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[8] += +amp_sv[0];
      jamp_sv[10] += +amp_sv[0];
      jamp_sv[11] -= amp_sv[0];
      jamp_sv[40] += +amp_sv[0];
      jamp_sv[41] -= amp_sv[0];
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[50] -= amp_sv[0];
      jamp_sv[52] -= amp_sv[0];
      jamp_sv[53] += +amp_sv[0];
      jamp_sv[82] -= amp_sv[0];
      jamp_sv[83] += +amp_sv[0];
      jamp_sv[106] -= amp_sv[0];
      jamp_sv[107] += +amp_sv[0];
      jamp_sv[116] += +amp_sv[0];
      jamp_sv[117] -= amp_sv[0];
      VVV1_0( w_sv[66], w_sv[6], w_sv[105], COUPs[0], &amp_sv[0] );
      jamp_sv[3] += +amp_sv[0];
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[8] += +amp_sv[0];
      jamp_sv[10] += +amp_sv[0];
      jamp_sv[11] -= amp_sv[0];
      jamp_sv[13] -= amp_sv[0];
      jamp_sv[19] -= amp_sv[0];
      jamp_sv[22] += +amp_sv[0];
      jamp_sv[41] -= amp_sv[0];
      jamp_sv[57] += +amp_sv[0];
      jamp_sv[63] -= amp_sv[0];
      jamp_sv[69] -= amp_sv[0];
      jamp_sv[71] += +amp_sv[0];
      jamp_sv[83] += +amp_sv[0];
      jamp_sv[107] += +amp_sv[0];
      jamp_sv[117] -= amp_sv[0];

      // *** DIAGRAM 906 OF 1240 ***

      // Wavefunction(s) for diagram number 906
      // (none)

      // Amplitude(s) for diagram number 906
      VVV1_0( w_sv[66], w_sv[4], w_sv[118], COUPs[0], &amp_sv[0] );
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[6] += +amp_sv[0];
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[12] += +amp_sv[0];
      jamp_sv[38] += +amp_sv[0];
      jamp_sv[56] -= amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[80] -= amp_sv[0];
      jamp_sv[97] += +amp_sv[0];
      jamp_sv[98] -= amp_sv[0];
      jamp_sv[99] += +amp_sv[0];
      jamp_sv[100] -= amp_sv[0];
      jamp_sv[107] -= amp_sv[0];
      jamp_sv[111] += +amp_sv[0];
      jamp_sv[113] -= amp_sv[0];
      jamp_sv[117] += +amp_sv[0];
      VVV1_0( w_sv[66], w_sv[4], w_sv[119], COUPs[0], &amp_sv[0] );
      jamp_sv[19] -= amp_sv[0];
      jamp_sv[20] += +amp_sv[0];
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[22] += +amp_sv[0];
      jamp_sv[38] += +amp_sv[0];
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[56] -= amp_sv[0];
      jamp_sv[57] += +amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[63] -= amp_sv[0];
      jamp_sv[80] -= amp_sv[0];
      jamp_sv[81] += +amp_sv[0];
      jamp_sv[97] += +amp_sv[0];
      jamp_sv[98] -= amp_sv[0];
      jamp_sv[99] += +amp_sv[0];
      jamp_sv[100] -= amp_sv[0];
      VVV1_0( w_sv[66], w_sv[4], w_sv[120], COUPs[0], &amp_sv[0] );
      jamp_sv[2] += +amp_sv[0];
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[8] += +amp_sv[0];
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[19] -= amp_sv[0];
      jamp_sv[20] += +amp_sv[0];
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[22] += +amp_sv[0];
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[57] += +amp_sv[0];
      jamp_sv[63] -= amp_sv[0];
      jamp_sv[81] += +amp_sv[0];
      jamp_sv[107] += +amp_sv[0];
      jamp_sv[111] -= amp_sv[0];
      jamp_sv[113] += +amp_sv[0];
      jamp_sv[117] -= amp_sv[0];

      // *** DIAGRAM 907 OF 1240 ***

      // Wavefunction(s) for diagram number 907
      // (none)

      // Amplitude(s) for diagram number 907
      VVVV1_0( w_sv[0], w_sv[66], w_sv[8], w_sv[27], COUPs[2], &amp_sv[0] );
      jamp_sv[2] += +amp_sv[0];
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[36] -= amp_sv[0];
      jamp_sv[37] += +amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[67] += +amp_sv[0];
      jamp_sv[69] += +amp_sv[0];
      jamp_sv[71] -= amp_sv[0];
      jamp_sv[78] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[108] += +amp_sv[0];
      jamp_sv[109] -= amp_sv[0];
      jamp_sv[111] -= amp_sv[0];
      jamp_sv[113] += +amp_sv[0];
      VVVV3_0( w_sv[0], w_sv[66], w_sv[8], w_sv[27], COUPs[2], &amp_sv[0] );
      jamp_sv[2] += +amp_sv[0];
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[20] += +amp_sv[0];
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[69] += +amp_sv[0];
      jamp_sv[71] -= amp_sv[0];
      jamp_sv[81] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[111] -= amp_sv[0];
      jamp_sv[113] += +amp_sv[0];
      VVVV4_0( w_sv[0], w_sv[66], w_sv[8], w_sv[27], COUPs[2], &amp_sv[0] );
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[20] += +amp_sv[0];
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[36] += +amp_sv[0];
      jamp_sv[37] -= amp_sv[0];
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[66] += +amp_sv[0];
      jamp_sv[67] -= amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[79] += +amp_sv[0];
      jamp_sv[81] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      jamp_sv[109] += +amp_sv[0];

      // *** DIAGRAM 908 OF 1240 ***

      // Wavefunction(s) for diagram number 908
      // (none)

      // Amplitude(s) for diagram number 908
      VVV1_0( w_sv[8], w_sv[27], w_sv[65], COUPs[0], &amp_sv[0] );
      jamp_sv[2] += +amp_sv[0];
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[36] -= amp_sv[0];
      jamp_sv[37] += +amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[67] += +amp_sv[0];
      jamp_sv[69] += +amp_sv[0];
      jamp_sv[71] -= amp_sv[0];
      jamp_sv[78] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[108] += +amp_sv[0];
      jamp_sv[109] -= amp_sv[0];
      jamp_sv[111] -= amp_sv[0];
      jamp_sv[113] += +amp_sv[0];

      // *** DIAGRAM 909 OF 1240 ***

      // Wavefunction(s) for diagram number 909
      // (none)

      // Amplitude(s) for diagram number 909
      VVV1_0( w_sv[66], w_sv[27], w_sv[56], COUPs[0], &amp_sv[0] );
      jamp_sv[2] += +amp_sv[0];
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[20] += +amp_sv[0];
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[69] += +amp_sv[0];
      jamp_sv[71] -= amp_sv[0];
      jamp_sv[81] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[111] -= amp_sv[0];
      jamp_sv[113] += +amp_sv[0];

      // *** DIAGRAM 910 OF 1240 ***

      // Wavefunction(s) for diagram number 910
      // (none)

      // Amplitude(s) for diagram number 910
      VVV1_0( w_sv[66], w_sv[8], w_sv[101], COUPs[0], &amp_sv[0] );
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[20] += +amp_sv[0];
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[36] += +amp_sv[0];
      jamp_sv[37] -= amp_sv[0];
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[66] += +amp_sv[0];
      jamp_sv[67] -= amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[79] += +amp_sv[0];
      jamp_sv[81] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      jamp_sv[109] += +amp_sv[0];

      // *** DIAGRAM 911 OF 1240 ***

      // Wavefunction(s) for diagram number 911
      // (none)

      // Amplitude(s) for diagram number 911
      VVV1_0( w_sv[65], w_sv[37], w_sv[6], COUPs[0], &amp_sv[0] );
      jamp_sv[48] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[50] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[56] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[62] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[66] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[67] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[69] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[71] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 912 OF 1240 ***

      // Wavefunction(s) for diagram number 912
      // (none)

      // Amplitude(s) for diagram number 912
      FFV1_0( w_sv[3], w_sv[36], w_sv[65], COUPs[1], &amp_sv[0] );
      jamp_sv[66] += +amp_sv[0];
      jamp_sv[67] -= amp_sv[0];
      jamp_sv[69] -= amp_sv[0];
      jamp_sv[71] += +amp_sv[0];

      // *** DIAGRAM 913 OF 1240 ***

      // Wavefunction(s) for diagram number 913
      // (none)

      // Amplitude(s) for diagram number 913
      FFV1_0( w_sv[71], w_sv[114], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[52] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[53] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 914 OF 1240 ***

      // Wavefunction(s) for diagram number 914
      // (none)

      // Amplitude(s) for diagram number 914
      FFV1_0( w_sv[3], w_sv[114], w_sv[70], COUPs[1], &amp_sv[0] );
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[50] -= amp_sv[0];
      jamp_sv[52] -= amp_sv[0];
      jamp_sv[53] += +amp_sv[0];

      // *** DIAGRAM 915 OF 1240 ***

      // Wavefunction(s) for diagram number 915
      // (none)

      // Amplitude(s) for diagram number 915
      FFV1_0( w_sv[71], w_sv[36], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[66] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[67] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 916 OF 1240 ***

      // Wavefunction(s) for diagram number 916
      // (none)

      // Amplitude(s) for diagram number 916
      VVV1_0( w_sv[0], w_sv[70], w_sv[37], COUPs[0], &amp_sv[0] );
      jamp_sv[48] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[50] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[52] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[53] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[57] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[63] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[69] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[71] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 917 OF 1240 ***

      // Wavefunction(s) for diagram number 917
      // (none)

      // Amplitude(s) for diagram number 917
      FFV1_0( w_sv[3], w_sv[33], w_sv[22], COUPs[1], &amp_sv[0] );
      jamp_sv[48] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[50] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[52] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[53] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[57] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[63] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[69] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[71] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[33], w_sv[103], COUPs[1], &amp_sv[0] );
      jamp_sv[52] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[53] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[56] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[57] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[62] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[63] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[66] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[67] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[33], w_sv[63], COUPs[1], &amp_sv[0] );
      jamp_sv[48] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[50] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[56] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[62] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[66] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[67] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[69] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[71] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 918 OF 1240 ***

      // Wavefunction(s) for diagram number 918
      // (none)

      // Amplitude(s) for diagram number 918
      FFV1_0( w_sv[41], w_sv[33], w_sv[65], COUPs[1], &amp_sv[0] );
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[50] -= amp_sv[0];
      jamp_sv[56] -= amp_sv[0];
      jamp_sv[62] += +amp_sv[0];

      // *** DIAGRAM 919 OF 1240 ***

      // Wavefunction(s) for diagram number 919
      // (none)

      // Amplitude(s) for diagram number 919
      FFV1_0( w_sv[41], w_sv[114], w_sv[66], COUPs[1], &amp_sv[0] );
      jamp_sv[48] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[50] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 920 OF 1240 ***

      // Wavefunction(s) for diagram number 920
      // (none)

      // Amplitude(s) for diagram number 920
      FFV1_0( w_sv[62], w_sv[33], w_sv[66], COUPs[1], &amp_sv[0] );
      jamp_sv[56] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[62] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 921 OF 1240 ***

      // Wavefunction(s) for diagram number 921
      // (none)

      // Amplitude(s) for diagram number 921
      VVV1_0( w_sv[65], w_sv[51], w_sv[4], COUPs[0], &amp_sv[0] );
      jamp_sv[97] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[100] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[106] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[108] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[109] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[111] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[113] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[116] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 922 OF 1240 ***

      // Wavefunction(s) for diagram number 922
      // (none)

      // Amplitude(s) for diagram number 922
      FFV1_0( w_sv[3], w_sv[49], w_sv[65], COUPs[1], &amp_sv[0] );
      jamp_sv[108] += +amp_sv[0];
      jamp_sv[109] -= amp_sv[0];
      jamp_sv[111] -= amp_sv[0];
      jamp_sv[113] += +amp_sv[0];

      // *** DIAGRAM 923 OF 1240 ***

      // Wavefunction(s) for diagram number 923
      // (none)

      // Amplitude(s) for diagram number 923
      FFV1_0( w_sv[71], w_sv[113], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[98] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[99] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 924 OF 1240 ***

      // Wavefunction(s) for diagram number 924
      // (none)

      // Amplitude(s) for diagram number 924
      FFV1_0( w_sv[3], w_sv[113], w_sv[69], COUPs[1], &amp_sv[0] );
      jamp_sv[97] += +amp_sv[0];
      jamp_sv[98] -= amp_sv[0];
      jamp_sv[99] += +amp_sv[0];
      jamp_sv[100] -= amp_sv[0];

      // *** DIAGRAM 925 OF 1240 ***

      // Wavefunction(s) for diagram number 925
      // (none)

      // Amplitude(s) for diagram number 925
      FFV1_0( w_sv[71], w_sv[49], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[108] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[109] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 926 OF 1240 ***

      // Wavefunction(s) for diagram number 926
      // (none)

      // Amplitude(s) for diagram number 926
      VVV1_0( w_sv[0], w_sv[69], w_sv[51], COUPs[0], &amp_sv[0] );
      jamp_sv[97] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[98] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[99] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[100] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[107] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[111] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[113] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[117] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 927 OF 1240 ***

      // Wavefunction(s) for diagram number 927
      // (none)

      // Amplitude(s) for diagram number 927
      FFV1_0( w_sv[3], w_sv[47], w_sv[93], COUPs[1], &amp_sv[0] );
      jamp_sv[97] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[98] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[99] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[100] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[107] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[111] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[113] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[117] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[47], w_sv[90], COUPs[1], &amp_sv[0] );
      jamp_sv[98] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[99] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[106] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[107] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[108] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[109] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[116] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[117] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[47], w_sv[21], COUPs[1], &amp_sv[0] );
      jamp_sv[97] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[100] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[106] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[108] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[109] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[111] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[113] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[116] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 928 OF 1240 ***

      // Wavefunction(s) for diagram number 928
      // (none)

      // Amplitude(s) for diagram number 928
      FFV1_0( w_sv[46], w_sv[47], w_sv[65], COUPs[1], &amp_sv[0] );
      jamp_sv[97] += +amp_sv[0];
      jamp_sv[100] -= amp_sv[0];
      jamp_sv[106] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];

      // *** DIAGRAM 929 OF 1240 ***

      // Wavefunction(s) for diagram number 929
      // (none)

      // Amplitude(s) for diagram number 929
      FFV1_0( w_sv[46], w_sv[113], w_sv[66], COUPs[1], &amp_sv[0] );
      jamp_sv[97] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[100] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 930 OF 1240 ***

      // Wavefunction(s) for diagram number 930
      // (none)

      // Amplitude(s) for diagram number 930
      FFV1_0( w_sv[99], w_sv[47], w_sv[66], COUPs[1], &amp_sv[0] );
      jamp_sv[106] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[116] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 931 OF 1240 ***

      // Wavefunction(s) for diagram number 931
      // (none)

      // Amplitude(s) for diagram number 931
      VVV1_0( w_sv[65], w_sv[54], w_sv[6], COUPs[0], &amp_sv[0] );
      jamp_sv[3] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[13] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[37] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[79] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[97] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[100] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[106] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[116] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 932 OF 1240 ***

      // Wavefunction(s) for diagram number 932
      // (none)

      // Amplitude(s) for diagram number 932
      FFV1_0( w_sv[53], w_sv[2], w_sv[65], COUPs[1], &amp_sv[0] );
      jamp_sv[3] += +amp_sv[0];
      jamp_sv[13] -= amp_sv[0];
      jamp_sv[37] -= amp_sv[0];
      jamp_sv[79] += +amp_sv[0];

      // *** DIAGRAM 933 OF 1240 ***

      // Wavefunction(s) for diagram number 933
      // (none)

      // Amplitude(s) for diagram number 933
      FFV1_0( w_sv[99], w_sv[94], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[40] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[82] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 934 OF 1240 ***

      // Wavefunction(s) for diagram number 934
      // (none)

      // Amplitude(s) for diagram number 934
      FFV1_0( w_sv[99], w_sv[2], w_sv[70], COUPs[1], &amp_sv[0] );
      jamp_sv[40] += +amp_sv[0];
      jamp_sv[82] -= amp_sv[0];
      jamp_sv[106] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];

      // *** DIAGRAM 935 OF 1240 ***

      // Wavefunction(s) for diagram number 935
      // (none)

      // Amplitude(s) for diagram number 935
      FFV1_0( w_sv[53], w_sv[94], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[37] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[79] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 936 OF 1240 ***

      // Wavefunction(s) for diagram number 936
      // (none)

      // Amplitude(s) for diagram number 936
      VVV1_0( w_sv[0], w_sv[70], w_sv[54], COUPs[0], &amp_sv[0] );
      jamp_sv[3] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[13] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[19] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[22] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[40] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[82] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[106] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[116] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 937 OF 1240 ***

      // Wavefunction(s) for diagram number 937
      // (none)

      // Amplitude(s) for diagram number 937
      FFV1_0( w_sv[46], w_sv[2], w_sv[22], COUPs[1], &amp_sv[0] );
      jamp_sv[3] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[13] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[19] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[22] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[40] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[82] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[106] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[116] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[46], w_sv[2], w_sv[103], COUPs[1], &amp_sv[0] );
      jamp_sv[19] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[22] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[37] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[40] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[79] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[82] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[97] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[100] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[46], w_sv[2], w_sv[63], COUPs[1], &amp_sv[0] );
      jamp_sv[3] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[13] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[37] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[79] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[97] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[100] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[106] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[116] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 938 OF 1240 ***

      // Wavefunction(s) for diagram number 938
      // (none)

      // Amplitude(s) for diagram number 938
      VVV1_0( w_sv[65], w_sv[20], w_sv[4], COUPs[0], &amp_sv[0] );
      jamp_sv[2] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[12] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[36] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[48] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[50] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[56] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[62] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[78] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 939 OF 1240 ***

      // Wavefunction(s) for diagram number 939
      // (none)

      // Amplitude(s) for diagram number 939
      FFV1_0( w_sv[28], w_sv[2], w_sv[65], COUPs[1], &amp_sv[0] );
      jamp_sv[2] += +amp_sv[0];
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[36] -= amp_sv[0];
      jamp_sv[78] += +amp_sv[0];

      // *** DIAGRAM 940 OF 1240 ***

      // Wavefunction(s) for diagram number 940
      // (none)

      // Amplitude(s) for diagram number 940
      FFV1_0( w_sv[62], w_sv[94], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[38] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[80] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 941 OF 1240 ***

      // Wavefunction(s) for diagram number 941
      // (none)

      // Amplitude(s) for diagram number 941
      FFV1_0( w_sv[62], w_sv[2], w_sv[69], COUPs[1], &amp_sv[0] );
      jamp_sv[38] += +amp_sv[0];
      jamp_sv[56] -= amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[80] -= amp_sv[0];

      // *** DIAGRAM 942 OF 1240 ***

      // Wavefunction(s) for diagram number 942
      // (none)

      // Amplitude(s) for diagram number 942
      FFV1_0( w_sv[28], w_sv[94], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[36] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[78] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 943 OF 1240 ***

      // Wavefunction(s) for diagram number 943
      // (none)

      // Amplitude(s) for diagram number 943
      VVV1_0( w_sv[0], w_sv[69], w_sv[20], COUPs[0], &amp_sv[0] );
      jamp_sv[2] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[6] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[8] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[12] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[38] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[56] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[62] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[80] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 944 OF 1240 ***

      // Wavefunction(s) for diagram number 944
      // (none)

      // Amplitude(s) for diagram number 944
      FFV1_0( w_sv[41], w_sv[2], w_sv[93], COUPs[1], &amp_sv[0] );
      jamp_sv[2] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[6] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[8] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[12] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[38] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[56] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[62] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[80] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[41], w_sv[2], w_sv[90], COUPs[1], &amp_sv[0] );
      jamp_sv[6] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[8] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[36] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[38] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[48] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[50] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[78] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[80] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[41], w_sv[2], w_sv[21], COUPs[1], &amp_sv[0] );
      jamp_sv[2] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[12] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[36] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[48] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[50] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[56] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[62] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[78] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 945 OF 1240 ***

      // Wavefunction(s) for diagram number 945
      // (none)

      // Amplitude(s) for diagram number 945
      FFV1_0( w_sv[3], w_sv[15], w_sv[65], COUPs[1], &amp_sv[0] );
      jamp_sv[66] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[67] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[69] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[71] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[108] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[109] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[111] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[113] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 946 OF 1240 ***

      // Wavefunction(s) for diagram number 946
      // (none)

      // Amplitude(s) for diagram number 946
      FFV1_0( w_sv[14], w_sv[2], w_sv[65], COUPs[1], &amp_sv[0] );
      jamp_sv[2] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[3] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[12] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[13] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[36] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[37] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[78] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[79] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 947 OF 1240 ***

      // Wavefunction(s) for diagram number 947
      // (none)

      // Amplitude(s) for diagram number 947
      FFV1_0( w_sv[3], w_sv[94], w_sv[101], COUPs[1], &amp_sv[0] );
      jamp_sv[36] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[37] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[39] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[41] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[78] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[79] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[81] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[83] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 948 OF 1240 ***

      // Wavefunction(s) for diagram number 948
      // (none)

      // Amplitude(s) for diagram number 948
      FFV1_0( w_sv[71], w_sv[2], w_sv[101], COUPs[1], &amp_sv[0] );
      jamp_sv[10] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[11] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[20] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[21] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[66] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[67] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[108] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[109] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 949 OF 1240 ***

      // Wavefunction(s) for diagram number 949
      // (none)

      // Amplitude(s) for diagram number 949
      FFV1_0( w_sv[14], w_sv[94], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[36] += +amp_sv[0];
      jamp_sv[37] -= amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[79] += +amp_sv[0];

      // *** DIAGRAM 950 OF 1240 ***

      // Wavefunction(s) for diagram number 950
      // (none)

      // Amplitude(s) for diagram number 950
      FFV1_0( w_sv[71], w_sv[15], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[66] += +amp_sv[0];
      jamp_sv[67] -= amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      jamp_sv[109] += +amp_sv[0];

      // *** DIAGRAM 951 OF 1240 ***

      // Wavefunction(s) for diagram number 951
      VVV1P0_1( w_sv[0], w_sv[72], COUPs[0], 0., 0., w_sv[71] );

      // Amplitude(s) for diagram number 951
      VVV1_0( w_sv[71], w_sv[13], w_sv[5], COUPs[0], &amp_sv[0] );
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[19] += +amp_sv[0];
      jamp_sv[43] += +amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[52] -= amp_sv[0];
      jamp_sv[58] -= amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[61] += +amp_sv[0];
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[76] -= amp_sv[0];
      jamp_sv[82] -= amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];

      // *** DIAGRAM 952 OF 1240 ***

      // Wavefunction(s) for diagram number 952
      // (none)

      // Amplitude(s) for diagram number 952
      VVV1_0( w_sv[71], w_sv[10], w_sv[4], COUPs[0], &amp_sv[0] );
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[18] += +amp_sv[0];
      jamp_sv[42] += +amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[52] -= amp_sv[0];
      jamp_sv[58] -= amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[76] -= amp_sv[0];
      jamp_sv[82] -= amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[85] += +amp_sv[0];
      jamp_sv[87] += +amp_sv[0];
      jamp_sv[89] -= amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[102] -= amp_sv[0];

      // *** DIAGRAM 953 OF 1240 ***

      // Wavefunction(s) for diagram number 953
      // (none)

      // Amplitude(s) for diagram number 953
      VVVV1_0( w_sv[8], w_sv[4], w_sv[5], w_sv[71], COUPs[2], &amp_sv[0] );
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[19] += +amp_sv[0];
      jamp_sv[43] += +amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[52] -= amp_sv[0];
      jamp_sv[58] -= amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[61] += +amp_sv[0];
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[76] -= amp_sv[0];
      jamp_sv[82] -= amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      VVVV3_0( w_sv[8], w_sv[4], w_sv[5], w_sv[71], COUPs[2], &amp_sv[0] );
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[18] += +amp_sv[0];
      jamp_sv[42] += +amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[52] -= amp_sv[0];
      jamp_sv[58] -= amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[76] -= amp_sv[0];
      jamp_sv[82] -= amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[85] += +amp_sv[0];
      jamp_sv[87] += +amp_sv[0];
      jamp_sv[89] -= amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      VVVV4_0( w_sv[8], w_sv[4], w_sv[5], w_sv[71], COUPs[2], &amp_sv[0] );
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[5] += +amp_sv[0];
      jamp_sv[18] += +amp_sv[0];
      jamp_sv[19] -= amp_sv[0];
      jamp_sv[42] += +amp_sv[0];
      jamp_sv[43] -= amp_sv[0];
      jamp_sv[60] += +amp_sv[0];
      jamp_sv[61] -= amp_sv[0];
      jamp_sv[63] -= amp_sv[0];
      jamp_sv[65] += +amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[85] += +amp_sv[0];
      jamp_sv[87] += +amp_sv[0];
      jamp_sv[89] -= amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[103] += +amp_sv[0];

      // *** DIAGRAM 954 OF 1240 ***

      // Wavefunction(s) for diagram number 954
      // (none)

      // Amplitude(s) for diagram number 954
      VVV1_0( w_sv[56], w_sv[74], w_sv[5], COUPs[0], &amp_sv[0] );
      jamp_sv[4] += +amp_sv[0];
      jamp_sv[7] -= amp_sv[0];
      jamp_sv[10] += +amp_sv[0];
      jamp_sv[13] -= amp_sv[0];
      jamp_sv[14] += +amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[16] += +amp_sv[0];
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[45] -= amp_sv[0];
      jamp_sv[59] += +amp_sv[0];
      jamp_sv[69] -= amp_sv[0];
      jamp_sv[83] += +amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[89] += +amp_sv[0];
      jamp_sv[93] -= amp_sv[0];
      jamp_sv[105] += +amp_sv[0];

      // *** DIAGRAM 955 OF 1240 ***

      // Wavefunction(s) for diagram number 955
      // (none)

      // Amplitude(s) for diagram number 955
      VVV1_0( w_sv[56], w_sv[75], w_sv[4], COUPs[0], &amp_sv[0] );
      jamp_sv[5] += +amp_sv[0];
      jamp_sv[7] -= amp_sv[0];
      jamp_sv[8] += +amp_sv[0];
      jamp_sv[9] -= amp_sv[0];
      jamp_sv[10] += +amp_sv[0];
      jamp_sv[13] -= amp_sv[0];
      jamp_sv[16] += +amp_sv[0];
      jamp_sv[19] -= amp_sv[0];
      jamp_sv[47] -= amp_sv[0];
      jamp_sv[59] += +amp_sv[0];
      jamp_sv[63] -= amp_sv[0];
      jamp_sv[65] += +amp_sv[0];
      jamp_sv[69] -= amp_sv[0];
      jamp_sv[83] += +amp_sv[0];
      jamp_sv[93] -= amp_sv[0];
      jamp_sv[107] += +amp_sv[0];

      // *** DIAGRAM 956 OF 1240 ***

      // Wavefunction(s) for diagram number 956
      // (none)

      // Amplitude(s) for diagram number 956
      VVVV1_0( w_sv[72], w_sv[4], w_sv[5], w_sv[56], COUPs[2], &amp_sv[0] );
      jamp_sv[4] += +amp_sv[0];
      jamp_sv[7] -= amp_sv[0];
      jamp_sv[10] += +amp_sv[0];
      jamp_sv[13] -= amp_sv[0];
      jamp_sv[14] += +amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[16] += +amp_sv[0];
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[45] -= amp_sv[0];
      jamp_sv[59] += +amp_sv[0];
      jamp_sv[69] -= amp_sv[0];
      jamp_sv[83] += +amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[89] += +amp_sv[0];
      jamp_sv[93] -= amp_sv[0];
      jamp_sv[105] += +amp_sv[0];
      VVVV3_0( w_sv[72], w_sv[4], w_sv[5], w_sv[56], COUPs[2], &amp_sv[0] );
      jamp_sv[5] += +amp_sv[0];
      jamp_sv[7] -= amp_sv[0];
      jamp_sv[8] += +amp_sv[0];
      jamp_sv[9] -= amp_sv[0];
      jamp_sv[10] += +amp_sv[0];
      jamp_sv[13] -= amp_sv[0];
      jamp_sv[16] += +amp_sv[0];
      jamp_sv[19] -= amp_sv[0];
      jamp_sv[47] -= amp_sv[0];
      jamp_sv[59] += +amp_sv[0];
      jamp_sv[63] -= amp_sv[0];
      jamp_sv[65] += +amp_sv[0];
      jamp_sv[69] -= amp_sv[0];
      jamp_sv[83] += +amp_sv[0];
      jamp_sv[93] -= amp_sv[0];
      jamp_sv[107] += +amp_sv[0];
      VVVV4_0( w_sv[72], w_sv[4], w_sv[5], w_sv[56], COUPs[2], &amp_sv[0] );
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[5] += +amp_sv[0];
      jamp_sv[8] += +amp_sv[0];
      jamp_sv[9] -= amp_sv[0];
      jamp_sv[14] -= amp_sv[0];
      jamp_sv[15] += +amp_sv[0];
      jamp_sv[18] += +amp_sv[0];
      jamp_sv[19] -= amp_sv[0];
      jamp_sv[45] += +amp_sv[0];
      jamp_sv[47] -= amp_sv[0];
      jamp_sv[63] -= amp_sv[0];
      jamp_sv[65] += +amp_sv[0];
      jamp_sv[87] += +amp_sv[0];
      jamp_sv[89] -= amp_sv[0];
      jamp_sv[105] -= amp_sv[0];
      jamp_sv[107] += +amp_sv[0];

      // *** DIAGRAM 957 OF 1240 ***

      // Wavefunction(s) for diagram number 957
      // (none)

      // Amplitude(s) for diagram number 957
      VVV1_0( w_sv[0], w_sv[74], w_sv[10], COUPs[0], &amp_sv[0] );
      jamp_sv[4] += +amp_sv[0];
      jamp_sv[7] -= amp_sv[0];
      jamp_sv[10] += +amp_sv[0];
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[68] -= amp_sv[0];
      jamp_sv[73] -= amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[83] += +amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[89] += +amp_sv[0];
      jamp_sv[93] -= amp_sv[0];
      jamp_sv[104] += +amp_sv[0];

      // *** DIAGRAM 958 OF 1240 ***

      // Wavefunction(s) for diagram number 958
      // (none)

      // Amplitude(s) for diagram number 958
      VVV1_0( w_sv[0], w_sv[75], w_sv[13], COUPs[0], &amp_sv[0] );
      jamp_sv[5] += +amp_sv[0];
      jamp_sv[13] -= amp_sv[0];
      jamp_sv[16] += +amp_sv[0];
      jamp_sv[19] -= amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[49] -= amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[59] += +amp_sv[0];
      jamp_sv[63] -= amp_sv[0];
      jamp_sv[65] += +amp_sv[0];
      jamp_sv[69] -= amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[92] -= amp_sv[0];
      jamp_sv[106] += +amp_sv[0];

      // *** DIAGRAM 959 OF 1240 ***

      // Wavefunction(s) for diagram number 959
      VVVV1P0_1( w_sv[0], w_sv[72], w_sv[4], COUPs[2], 0., 0., w_sv[94] );
      VVVV3P0_1( w_sv[0], w_sv[72], w_sv[4], COUPs[2], 0., 0., w_sv[65] );
      VVVV4P0_1( w_sv[0], w_sv[72], w_sv[4], COUPs[2], 0., 0., w_sv[21] );

      // Amplitude(s) for diagram number 959
      VVV1_0( w_sv[8], w_sv[5], w_sv[94], COUPs[0], &amp_sv[0] );
      jamp_sv[4] += +amp_sv[0];
      jamp_sv[7] -= amp_sv[0];
      jamp_sv[10] += +amp_sv[0];
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[68] -= amp_sv[0];
      jamp_sv[73] -= amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[83] += +amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[89] += +amp_sv[0];
      jamp_sv[93] -= amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      VVV1_0( w_sv[8], w_sv[5], w_sv[65], COUPs[0], &amp_sv[0] );
      jamp_sv[7] -= amp_sv[0];
      jamp_sv[10] += +amp_sv[0];
      jamp_sv[42] += +amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[52] -= amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[82] -= amp_sv[0];
      jamp_sv[83] += +amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[85] += +amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[93] -= amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      VVV1_0( w_sv[8], w_sv[5], w_sv[21], COUPs[0], &amp_sv[0] );
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[18] += +amp_sv[0];
      jamp_sv[42] += +amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[52] -= amp_sv[0];
      jamp_sv[58] -= amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[76] -= amp_sv[0];
      jamp_sv[82] -= amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[85] += +amp_sv[0];
      jamp_sv[87] += +amp_sv[0];
      jamp_sv[89] -= amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[102] -= amp_sv[0];

      // *** DIAGRAM 960 OF 1240 ***

      // Wavefunction(s) for diagram number 960
      VVVV1P0_1( w_sv[0], w_sv[72], w_sv[5], COUPs[2], 0., 0., w_sv[90] );
      VVVV3P0_1( w_sv[0], w_sv[72], w_sv[5], COUPs[2], 0., 0., w_sv[93] );
      VVVV4P0_1( w_sv[0], w_sv[72], w_sv[5], COUPs[2], 0., 0., w_sv[69] );

      // Amplitude(s) for diagram number 960
      VVV1_0( w_sv[8], w_sv[4], w_sv[90], COUPs[0], &amp_sv[0] );
      jamp_sv[5] += +amp_sv[0];
      jamp_sv[13] -= amp_sv[0];
      jamp_sv[16] += +amp_sv[0];
      jamp_sv[19] -= amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[49] -= amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[59] += +amp_sv[0];
      jamp_sv[63] -= amp_sv[0];
      jamp_sv[65] += +amp_sv[0];
      jamp_sv[69] -= amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[92] -= amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      VVV1_0( w_sv[8], w_sv[4], w_sv[93], COUPs[0], &amp_sv[0] );
      jamp_sv[13] -= amp_sv[0];
      jamp_sv[16] += +amp_sv[0];
      jamp_sv[43] += +amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[58] -= amp_sv[0];
      jamp_sv[59] += +amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[61] += +amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[69] -= amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[76] -= amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      VVV1_0( w_sv[8], w_sv[4], w_sv[69], COUPs[0], &amp_sv[0] );
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[19] += +amp_sv[0];
      jamp_sv[43] += +amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[52] -= amp_sv[0];
      jamp_sv[58] -= amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[61] += +amp_sv[0];
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[76] -= amp_sv[0];
      jamp_sv[82] -= amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];

      // *** DIAGRAM 961 OF 1240 ***

      // Wavefunction(s) for diagram number 961
      // (none)

      // Amplitude(s) for diagram number 961
      VVV1_0( w_sv[72], w_sv[5], w_sv[107], COUPs[0], &amp_sv[0] );
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[19] += +amp_sv[0];
      jamp_sv[46] += +amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[50] -= amp_sv[0];
      jamp_sv[51] += +amp_sv[0];
      jamp_sv[52] -= amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[69] += +amp_sv[0];
      jamp_sv[82] -= amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[106] -= amp_sv[0];
      VVV1_0( w_sv[72], w_sv[5], w_sv[95], COUPs[0], &amp_sv[0] );
      jamp_sv[7] -= amp_sv[0];
      jamp_sv[8] += +amp_sv[0];
      jamp_sv[9] -= amp_sv[0];
      jamp_sv[10] += +amp_sv[0];
      jamp_sv[46] += +amp_sv[0];
      jamp_sv[47] -= amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[50] -= amp_sv[0];
      jamp_sv[51] += +amp_sv[0];
      jamp_sv[52] -= amp_sv[0];
      jamp_sv[82] -= amp_sv[0];
      jamp_sv[83] += +amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[93] -= amp_sv[0];
      jamp_sv[106] -= amp_sv[0];
      jamp_sv[107] += +amp_sv[0];
      VVV1_0( w_sv[72], w_sv[5], w_sv[105], COUPs[0], &amp_sv[0] );
      jamp_sv[5] += +amp_sv[0];
      jamp_sv[7] -= amp_sv[0];
      jamp_sv[8] += +amp_sv[0];
      jamp_sv[9] -= amp_sv[0];
      jamp_sv[10] += +amp_sv[0];
      jamp_sv[13] -= amp_sv[0];
      jamp_sv[16] += +amp_sv[0];
      jamp_sv[19] -= amp_sv[0];
      jamp_sv[47] -= amp_sv[0];
      jamp_sv[59] += +amp_sv[0];
      jamp_sv[63] -= amp_sv[0];
      jamp_sv[65] += +amp_sv[0];
      jamp_sv[69] -= amp_sv[0];
      jamp_sv[83] += +amp_sv[0];
      jamp_sv[93] -= amp_sv[0];
      jamp_sv[107] += +amp_sv[0];

      // *** DIAGRAM 962 OF 1240 ***

      // Wavefunction(s) for diagram number 962
      // (none)

      // Amplitude(s) for diagram number 962
      VVV1_0( w_sv[72], w_sv[4], w_sv[115], COUPs[0], &amp_sv[0] );
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[18] += +amp_sv[0];
      jamp_sv[44] += +amp_sv[0];
      jamp_sv[58] -= amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[74] -= amp_sv[0];
      jamp_sv[75] += +amp_sv[0];
      jamp_sv[76] -= amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[87] += +amp_sv[0];
      jamp_sv[89] -= amp_sv[0];
      jamp_sv[93] += +amp_sv[0];
      jamp_sv[104] -= amp_sv[0];
      VVV1_0( w_sv[72], w_sv[4], w_sv[116], COUPs[0], &amp_sv[0] );
      jamp_sv[13] -= amp_sv[0];
      jamp_sv[14] += +amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[16] += +amp_sv[0];
      jamp_sv[44] += +amp_sv[0];
      jamp_sv[45] -= amp_sv[0];
      jamp_sv[58] -= amp_sv[0];
      jamp_sv[59] += +amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[69] -= amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[74] -= amp_sv[0];
      jamp_sv[75] += +amp_sv[0];
      jamp_sv[76] -= amp_sv[0];
      jamp_sv[104] -= amp_sv[0];
      jamp_sv[105] += +amp_sv[0];
      VVV1_0( w_sv[72], w_sv[4], w_sv[117], COUPs[0], &amp_sv[0] );
      jamp_sv[4] += +amp_sv[0];
      jamp_sv[7] -= amp_sv[0];
      jamp_sv[10] += +amp_sv[0];
      jamp_sv[13] -= amp_sv[0];
      jamp_sv[14] += +amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[16] += +amp_sv[0];
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[45] -= amp_sv[0];
      jamp_sv[59] += +amp_sv[0];
      jamp_sv[69] -= amp_sv[0];
      jamp_sv[83] += +amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[89] += +amp_sv[0];
      jamp_sv[93] -= amp_sv[0];
      jamp_sv[105] += +amp_sv[0];

      // *** DIAGRAM 963 OF 1240 ***

      // Wavefunction(s) for diagram number 963
      // (none)

      // Amplitude(s) for diagram number 963
      VVVV1_0( w_sv[0], w_sv[72], w_sv[8], w_sv[24], COUPs[2], &amp_sv[0] );
      jamp_sv[4] += +amp_sv[0];
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[19] += +amp_sv[0];
      jamp_sv[42] -= amp_sv[0];
      jamp_sv[43] += +amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[61] += +amp_sv[0];
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[84] += +amp_sv[0];
      jamp_sv[85] -= amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[89] += +amp_sv[0];
      jamp_sv[102] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      VVVV3_0( w_sv[0], w_sv[72], w_sv[8], w_sv[24], COUPs[2], &amp_sv[0] );
      jamp_sv[4] += +amp_sv[0];
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[14] += +amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[19] += +amp_sv[0];
      jamp_sv[45] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[89] += +amp_sv[0];
      jamp_sv[105] += +amp_sv[0];
      jamp_sv[107] -= amp_sv[0];
      VVVV4_0( w_sv[0], w_sv[72], w_sv[8], w_sv[24], COUPs[2], &amp_sv[0] );
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[14] += +amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[42] += +amp_sv[0];
      jamp_sv[43] -= amp_sv[0];
      jamp_sv[45] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[60] += +amp_sv[0];
      jamp_sv[61] -= amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[85] += +amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[103] += +amp_sv[0];
      jamp_sv[105] += +amp_sv[0];
      jamp_sv[107] -= amp_sv[0];

      // *** DIAGRAM 964 OF 1240 ***

      // Wavefunction(s) for diagram number 964
      // (none)

      // Amplitude(s) for diagram number 964
      VVV1_0( w_sv[8], w_sv[24], w_sv[71], COUPs[0], &amp_sv[0] );
      jamp_sv[4] += +amp_sv[0];
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[19] += +amp_sv[0];
      jamp_sv[42] -= amp_sv[0];
      jamp_sv[43] += +amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[61] += +amp_sv[0];
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[84] += +amp_sv[0];
      jamp_sv[85] -= amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[89] += +amp_sv[0];
      jamp_sv[102] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];

      // *** DIAGRAM 965 OF 1240 ***

      // Wavefunction(s) for diagram number 965
      // (none)

      // Amplitude(s) for diagram number 965
      VVV1_0( w_sv[72], w_sv[24], w_sv[56], COUPs[0], &amp_sv[0] );
      jamp_sv[4] += +amp_sv[0];
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[14] += +amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[19] += +amp_sv[0];
      jamp_sv[45] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[89] += +amp_sv[0];
      jamp_sv[105] += +amp_sv[0];
      jamp_sv[107] -= amp_sv[0];

      // *** DIAGRAM 966 OF 1240 ***

      // Wavefunction(s) for diagram number 966
      // (none)

      // Amplitude(s) for diagram number 966
      VVV1_0( w_sv[72], w_sv[8], w_sv[98], COUPs[0], &amp_sv[0] );
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[14] += +amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[42] += +amp_sv[0];
      jamp_sv[43] -= amp_sv[0];
      jamp_sv[45] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[60] += +amp_sv[0];
      jamp_sv[61] -= amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[85] += +amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[103] += +amp_sv[0];
      jamp_sv[105] += +amp_sv[0];
      jamp_sv[107] -= amp_sv[0];

      // *** DIAGRAM 967 OF 1240 ***

      // Wavefunction(s) for diagram number 967
      // (none)

      // Amplitude(s) for diagram number 967
      VVV1_0( w_sv[71], w_sv[37], w_sv[5], COUPs[0], &amp_sv[0] );
      jamp_sv[49] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[52] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[58] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[60] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[61] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[63] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[65] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[68] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 968 OF 1240 ***

      // Wavefunction(s) for diagram number 968
      // (none)

      // Amplitude(s) for diagram number 968
      FFV1_0( w_sv[3], w_sv[35], w_sv[71], COUPs[1], &amp_sv[0] );
      jamp_sv[60] += +amp_sv[0];
      jamp_sv[61] -= amp_sv[0];
      jamp_sv[63] -= amp_sv[0];
      jamp_sv[65] += +amp_sv[0];

      // *** DIAGRAM 969 OF 1240 ***

      // Wavefunction(s) for diagram number 969
      // (none)

      // Amplitude(s) for diagram number 969
      FFV1_0( w_sv[76], w_sv[114], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[50] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[51] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 970 OF 1240 ***

      // Wavefunction(s) for diagram number 970
      // (none)

      // Amplitude(s) for diagram number 970
      FFV1_0( w_sv[3], w_sv[114], w_sv[75], COUPs[1], &amp_sv[0] );
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[50] -= amp_sv[0];
      jamp_sv[51] += +amp_sv[0];
      jamp_sv[52] -= amp_sv[0];

      // *** DIAGRAM 971 OF 1240 ***

      // Wavefunction(s) for diagram number 971
      // (none)

      // Amplitude(s) for diagram number 971
      FFV1_0( w_sv[76], w_sv[35], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[60] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[61] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 972 OF 1240 ***

      // Wavefunction(s) for diagram number 972
      // (none)

      // Amplitude(s) for diagram number 972
      VVV1_0( w_sv[0], w_sv[75], w_sv[37], COUPs[0], &amp_sv[0] );
      jamp_sv[49] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[50] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[51] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[52] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[59] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[63] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[65] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[69] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 973 OF 1240 ***

      // Wavefunction(s) for diagram number 973
      // (none)

      // Amplitude(s) for diagram number 973
      FFV1_0( w_sv[3], w_sv[33], w_sv[90], COUPs[1], &amp_sv[0] );
      jamp_sv[49] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[50] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[51] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[52] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[59] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[63] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[65] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[69] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[33], w_sv[93], COUPs[1], &amp_sv[0] );
      jamp_sv[50] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[51] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[58] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[59] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[60] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[61] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[68] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[69] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[33], w_sv[69], COUPs[1], &amp_sv[0] );
      jamp_sv[49] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[52] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[58] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[60] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[61] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[63] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[65] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[68] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 974 OF 1240 ***

      // Wavefunction(s) for diagram number 974
      // (none)

      // Amplitude(s) for diagram number 974
      FFV1_0( w_sv[38], w_sv[33], w_sv[71], COUPs[1], &amp_sv[0] );
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[52] -= amp_sv[0];
      jamp_sv[58] -= amp_sv[0];
      jamp_sv[68] += +amp_sv[0];

      // *** DIAGRAM 975 OF 1240 ***

      // Wavefunction(s) for diagram number 975
      // (none)

      // Amplitude(s) for diagram number 975
      FFV1_0( w_sv[38], w_sv[114], w_sv[72], COUPs[1], &amp_sv[0] );
      jamp_sv[49] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[52] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 976 OF 1240 ***

      // Wavefunction(s) for diagram number 976
      // (none)

      // Amplitude(s) for diagram number 976
      FFV1_0( w_sv[104], w_sv[33], w_sv[72], COUPs[1], &amp_sv[0] );
      jamp_sv[58] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[68] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 977 OF 1240 ***

      // Wavefunction(s) for diagram number 977
      // (none)

      // Amplitude(s) for diagram number 977
      VVV1_0( w_sv[71], w_sv[45], w_sv[4], COUPs[0], &amp_sv[0] );
      jamp_sv[73] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[76] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[82] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[84] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[85] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[87] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[89] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[92] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 978 OF 1240 ***

      // Wavefunction(s) for diagram number 978
      // (none)

      // Amplitude(s) for diagram number 978
      FFV1_0( w_sv[3], w_sv[43], w_sv[71], COUPs[1], &amp_sv[0] );
      jamp_sv[84] += +amp_sv[0];
      jamp_sv[85] -= amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[89] += +amp_sv[0];

      // *** DIAGRAM 979 OF 1240 ***

      // Wavefunction(s) for diagram number 979
      // (none)

      // Amplitude(s) for diagram number 979
      FFV1_0( w_sv[76], w_sv[102], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[74] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[75] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 980 OF 1240 ***

      // Wavefunction(s) for diagram number 980
      // (none)

      // Amplitude(s) for diagram number 980
      FFV1_0( w_sv[3], w_sv[102], w_sv[74], COUPs[1], &amp_sv[0] );
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[74] -= amp_sv[0];
      jamp_sv[75] += +amp_sv[0];
      jamp_sv[76] -= amp_sv[0];

      // *** DIAGRAM 981 OF 1240 ***

      // Wavefunction(s) for diagram number 981
      // (none)

      // Amplitude(s) for diagram number 981
      FFV1_0( w_sv[76], w_sv[43], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[84] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[85] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 982 OF 1240 ***

      // Wavefunction(s) for diagram number 982
      // (none)

      // Amplitude(s) for diagram number 982
      VVV1_0( w_sv[0], w_sv[74], w_sv[45], COUPs[0], &amp_sv[0] );
      jamp_sv[73] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[74] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[75] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[76] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[83] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[87] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[89] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[93] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 983 OF 1240 ***

      // Wavefunction(s) for diagram number 983
      // (none)

      // Amplitude(s) for diagram number 983
      FFV1_0( w_sv[3], w_sv[39], w_sv[94], COUPs[1], &amp_sv[0] );
      jamp_sv[73] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[74] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[75] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[76] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[83] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[87] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[89] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[93] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[39], w_sv[65], COUPs[1], &amp_sv[0] );
      jamp_sv[74] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[75] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[82] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[83] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[84] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[85] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[92] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[93] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[39], w_sv[21], COUPs[1], &amp_sv[0] );
      jamp_sv[73] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[76] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[82] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[84] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[85] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[87] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[89] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[92] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 984 OF 1240 ***

      // Wavefunction(s) for diagram number 984
      // (none)

      // Amplitude(s) for diagram number 984
      FFV1_0( w_sv[46], w_sv[39], w_sv[71], COUPs[1], &amp_sv[0] );
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[76] -= amp_sv[0];
      jamp_sv[82] -= amp_sv[0];
      jamp_sv[92] += +amp_sv[0];

      // *** DIAGRAM 985 OF 1240 ***

      // Wavefunction(s) for diagram number 985
      // (none)

      // Amplitude(s) for diagram number 985
      FFV1_0( w_sv[46], w_sv[102], w_sv[72], COUPs[1], &amp_sv[0] );
      jamp_sv[73] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[76] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 986 OF 1240 ***

      // Wavefunction(s) for diagram number 986
      // (none)

      // Amplitude(s) for diagram number 986
      FFV1_0( w_sv[99], w_sv[39], w_sv[72], COUPs[1], &amp_sv[0] );
      jamp_sv[82] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[92] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 987 OF 1240 ***

      // Wavefunction(s) for diagram number 987
      // (none)

      // Amplitude(s) for diagram number 987
      VVV1_0( w_sv[71], w_sv[54], w_sv[5], COUPs[0], &amp_sv[0] );
      jamp_sv[5] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[19] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[43] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[73] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[76] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[82] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[92] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[103] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 988 OF 1240 ***

      // Wavefunction(s) for diagram number 988
      // (none)

      // Amplitude(s) for diagram number 988
      FFV1_0( w_sv[7], w_sv[2], w_sv[71], COUPs[1], &amp_sv[0] );
      jamp_sv[5] += +amp_sv[0];
      jamp_sv[19] -= amp_sv[0];
      jamp_sv[43] -= amp_sv[0];
      jamp_sv[103] += +amp_sv[0];

      // *** DIAGRAM 989 OF 1240 ***

      // Wavefunction(s) for diagram number 989
      // (none)

      // Amplitude(s) for diagram number 989
      FFV1_0( w_sv[99], w_sv[97], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[46] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[106] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 990 OF 1240 ***

      // Wavefunction(s) for diagram number 990
      // (none)

      // Amplitude(s) for diagram number 990
      FFV1_0( w_sv[99], w_sv[2], w_sv[75], COUPs[1], &amp_sv[0] );
      jamp_sv[46] += +amp_sv[0];
      jamp_sv[82] -= amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[106] -= amp_sv[0];

      // *** DIAGRAM 991 OF 1240 ***

      // Wavefunction(s) for diagram number 991
      // (none)

      // Amplitude(s) for diagram number 991
      FFV1_0( w_sv[7], w_sv[97], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[43] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[103] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 992 OF 1240 ***

      // Wavefunction(s) for diagram number 992
      // (none)

      // Amplitude(s) for diagram number 992
      VVV1_0( w_sv[0], w_sv[75], w_sv[54], COUPs[0], &amp_sv[0] );
      jamp_sv[5] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[13] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[16] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[19] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[46] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[82] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[92] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[106] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 993 OF 1240 ***

      // Wavefunction(s) for diagram number 993
      // (none)

      // Amplitude(s) for diagram number 993
      FFV1_0( w_sv[46], w_sv[2], w_sv[90], COUPs[1], &amp_sv[0] );
      jamp_sv[5] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[13] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[16] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[19] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[46] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[82] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[92] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[106] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[46], w_sv[2], w_sv[93], COUPs[1], &amp_sv[0] );
      jamp_sv[13] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[16] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[43] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[46] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[73] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[76] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[103] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[106] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[46], w_sv[2], w_sv[69], COUPs[1], &amp_sv[0] );
      jamp_sv[5] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[19] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[43] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[73] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[76] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[82] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[92] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[103] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 994 OF 1240 ***

      // Wavefunction(s) for diagram number 994
      // (none)

      // Amplitude(s) for diagram number 994
      VVV1_0( w_sv[71], w_sv[23], w_sv[4], COUPs[0], &amp_sv[0] );
      jamp_sv[4] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[18] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[42] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[49] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[52] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[58] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[68] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[102] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 995 OF 1240 ***

      // Wavefunction(s) for diagram number 995
      // (none)

      // Amplitude(s) for diagram number 995
      FFV1_0( w_sv[25], w_sv[2], w_sv[71], COUPs[1], &amp_sv[0] );
      jamp_sv[4] += +amp_sv[0];
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[42] -= amp_sv[0];
      jamp_sv[102] += +amp_sv[0];

      // *** DIAGRAM 996 OF 1240 ***

      // Wavefunction(s) for diagram number 996
      // (none)

      // Amplitude(s) for diagram number 996
      FFV1_0( w_sv[104], w_sv[97], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[44] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[104] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 997 OF 1240 ***

      // Wavefunction(s) for diagram number 997
      // (none)

      // Amplitude(s) for diagram number 997
      FFV1_0( w_sv[104], w_sv[2], w_sv[74], COUPs[1], &amp_sv[0] );
      jamp_sv[44] += +amp_sv[0];
      jamp_sv[58] -= amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[104] -= amp_sv[0];

      // *** DIAGRAM 998 OF 1240 ***

      // Wavefunction(s) for diagram number 998
      // (none)

      // Amplitude(s) for diagram number 998
      FFV1_0( w_sv[25], w_sv[97], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[42] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[102] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 999 OF 1240 ***

      // Wavefunction(s) for diagram number 999
      // (none)

      // Amplitude(s) for diagram number 999
      VVV1_0( w_sv[0], w_sv[74], w_sv[23], COUPs[0], &amp_sv[0] );
      jamp_sv[4] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[7] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[10] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[18] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[44] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[58] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[68] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[104] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1000 OF 1240 ***

      // Wavefunction(s) for diagram number 1000
      // (none)

      // Amplitude(s) for diagram number 1000
      FFV1_0( w_sv[38], w_sv[2], w_sv[94], COUPs[1], &amp_sv[0] );
      jamp_sv[4] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[7] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[10] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[18] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[44] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[58] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[68] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[104] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[38], w_sv[2], w_sv[65], COUPs[1], &amp_sv[0] );
      jamp_sv[7] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[10] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[42] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[44] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[49] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[52] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[102] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[104] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[38], w_sv[2], w_sv[21], COUPs[1], &amp_sv[0] );
      jamp_sv[4] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[18] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[42] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[49] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[52] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[58] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[68] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[102] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1001 OF 1240 ***

      // Wavefunction(s) for diagram number 1001
      // (none)

      // Amplitude(s) for diagram number 1001
      FFV1_0( w_sv[3], w_sv[17], w_sv[71], COUPs[1], &amp_sv[0] );
      jamp_sv[60] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[61] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[63] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[65] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[84] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[85] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[87] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[89] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1002 OF 1240 ***

      // Wavefunction(s) for diagram number 1002
      // (none)

      // Amplitude(s) for diagram number 1002
      FFV1_0( w_sv[26], w_sv[2], w_sv[71], COUPs[1], &amp_sv[0] );
      jamp_sv[4] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[5] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[18] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[19] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[42] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[43] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[102] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[103] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1003 OF 1240 ***

      // Wavefunction(s) for diagram number 1003
      // (none)

      // Amplitude(s) for diagram number 1003
      FFV1_0( w_sv[3], w_sv[97], w_sv[98], COUPs[1], &amp_sv[0] );
      jamp_sv[42] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[43] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[45] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[47] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[102] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[103] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[105] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[107] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1004 OF 1240 ***

      // Wavefunction(s) for diagram number 1004
      // (none)

      // Amplitude(s) for diagram number 1004
      FFV1_0( w_sv[76], w_sv[2], w_sv[98], COUPs[1], &amp_sv[0] );
      jamp_sv[8] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[9] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[14] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[15] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[60] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[61] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[84] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[85] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1005 OF 1240 ***

      // Wavefunction(s) for diagram number 1005
      // (none)

      // Amplitude(s) for diagram number 1005
      FFV1_0( w_sv[26], w_sv[97], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[42] += +amp_sv[0];
      jamp_sv[43] -= amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[103] += +amp_sv[0];

      // *** DIAGRAM 1006 OF 1240 ***

      // Wavefunction(s) for diagram number 1006
      // (none)

      // Amplitude(s) for diagram number 1006
      FFV1_0( w_sv[76], w_sv[17], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[60] += +amp_sv[0];
      jamp_sv[61] -= amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[85] += +amp_sv[0];

      // *** DIAGRAM 1007 OF 1240 ***

      // Wavefunction(s) for diagram number 1007
      // (none)

      // Amplitude(s) for diagram number 1007
      VVV1_0( w_sv[56], w_sv[59], w_sv[6], COUPs[0], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[14] += +amp_sv[0];
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[19] += +amp_sv[0];
      jamp_sv[21] += +amp_sv[0];
      jamp_sv[23] -= amp_sv[0];
      jamp_sv[33] -= amp_sv[0];
      jamp_sv[39] += +amp_sv[0];
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[105] += +amp_sv[0];
      jamp_sv[107] -= amp_sv[0];
      jamp_sv[113] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];

      // *** DIAGRAM 1008 OF 1240 ***

      // Wavefunction(s) for diagram number 1008
      // (none)

      // Amplitude(s) for diagram number 1008
      VVV1_0( w_sv[56], w_sv[1], w_sv[42], COUPs[0], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[5] += +amp_sv[0];
      jamp_sv[9] -= amp_sv[0];
      jamp_sv[15] += +amp_sv[0];
      jamp_sv[21] += +amp_sv[0];
      jamp_sv[23] -= amp_sv[0];
      jamp_sv[33] -= amp_sv[0];
      jamp_sv[39] += +amp_sv[0];
      jamp_sv[45] += +amp_sv[0];
      jamp_sv[47] -= amp_sv[0];
      jamp_sv[65] += +amp_sv[0];
      jamp_sv[89] -= amp_sv[0];
      jamp_sv[113] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];

      // *** DIAGRAM 1009 OF 1240 ***

      // Wavefunction(s) for diagram number 1009
      // (none)

      // Amplitude(s) for diagram number 1009
      VVVV1_0( w_sv[1], w_sv[24], w_sv[6], w_sv[56], COUPs[2], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[14] += +amp_sv[0];
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[19] += +amp_sv[0];
      jamp_sv[21] += +amp_sv[0];
      jamp_sv[23] -= amp_sv[0];
      jamp_sv[33] -= amp_sv[0];
      jamp_sv[39] += +amp_sv[0];
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[105] += +amp_sv[0];
      jamp_sv[107] -= amp_sv[0];
      jamp_sv[113] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];
      VVVV3_0( w_sv[1], w_sv[24], w_sv[6], w_sv[56], COUPs[2], &amp_sv[0] );
      jamp_sv[4] += +amp_sv[0];
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[14] += +amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[19] += +amp_sv[0];
      jamp_sv[45] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[89] += +amp_sv[0];
      jamp_sv[105] += +amp_sv[0];
      jamp_sv[107] -= amp_sv[0];
      VVVV4_0( w_sv[1], w_sv[24], w_sv[6], w_sv[56], COUPs[2], &amp_sv[0] );
      jamp_sv[0] -= amp_sv[0];
      jamp_sv[2] += +amp_sv[0];
      jamp_sv[4] += +amp_sv[0];
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[23] += +amp_sv[0];
      jamp_sv[33] += +amp_sv[0];
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[45] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[89] += +amp_sv[0];
      jamp_sv[113] += +amp_sv[0];
      jamp_sv[119] -= amp_sv[0];

      // *** DIAGRAM 1010 OF 1240 ***

      // Wavefunction(s) for diagram number 1010
      // (none)

      // Amplitude(s) for diagram number 1010
      VVV1_0( w_sv[98], w_sv[108], w_sv[6], COUPs[0], &amp_sv[0] );
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[24] -= amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[32] += +amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[42] += +amp_sv[0];
      jamp_sv[43] -= amp_sv[0];
      jamp_sv[45] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[61] -= amp_sv[0];
      jamp_sv[85] += +amp_sv[0];
      jamp_sv[99] -= amp_sv[0];
      jamp_sv[101] += +amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      jamp_sv[118] -= amp_sv[0];

      // *** DIAGRAM 1011 OF 1240 ***

      // Wavefunction(s) for diagram number 1011
      // (none)

      // Amplitude(s) for diagram number 1011
      VVV1_0( w_sv[98], w_sv[1], w_sv[11], COUPs[0], &amp_sv[0] );
      jamp_sv[8] += +amp_sv[0];
      jamp_sv[14] -= amp_sv[0];
      jamp_sv[24] -= amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[32] += +amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[84] += +amp_sv[0];
      jamp_sv[99] -= amp_sv[0];
      jamp_sv[101] += +amp_sv[0];
      jamp_sv[102] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      jamp_sv[105] -= amp_sv[0];
      jamp_sv[107] += +amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      jamp_sv[118] -= amp_sv[0];

      // *** DIAGRAM 1012 OF 1240 ***

      // Wavefunction(s) for diagram number 1012
      // (none)

      // Amplitude(s) for diagram number 1012
      VVVV1_0( w_sv[1], w_sv[8], w_sv[6], w_sv[98], COUPs[2], &amp_sv[0] );
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[24] -= amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[32] += +amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[42] += +amp_sv[0];
      jamp_sv[43] -= amp_sv[0];
      jamp_sv[45] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[61] -= amp_sv[0];
      jamp_sv[85] += +amp_sv[0];
      jamp_sv[99] -= amp_sv[0];
      jamp_sv[101] += +amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      jamp_sv[118] -= amp_sv[0];
      VVVV3_0( w_sv[1], w_sv[8], w_sv[6], w_sv[98], COUPs[2], &amp_sv[0] );
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[14] += +amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[42] += +amp_sv[0];
      jamp_sv[43] -= amp_sv[0];
      jamp_sv[45] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[60] += +amp_sv[0];
      jamp_sv[61] -= amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[85] += +amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[103] += +amp_sv[0];
      jamp_sv[105] += +amp_sv[0];
      jamp_sv[107] -= amp_sv[0];
      VVVV4_0( w_sv[1], w_sv[8], w_sv[6], w_sv[98], COUPs[2], &amp_sv[0] );
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[14] += +amp_sv[0];
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[26] -= amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[38] += +amp_sv[0];
      jamp_sv[60] += +amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[99] += +amp_sv[0];
      jamp_sv[101] -= amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[103] += +amp_sv[0];
      jamp_sv[105] += +amp_sv[0];
      jamp_sv[107] -= amp_sv[0];
      jamp_sv[112] -= amp_sv[0];
      jamp_sv[118] += +amp_sv[0];

      // *** DIAGRAM 1013 OF 1240 ***

      // Wavefunction(s) for diagram number 1013
      // (none)

      // Amplitude(s) for diagram number 1013
      VVV1_0( w_sv[0], w_sv[108], w_sv[42], COUPs[0], &amp_sv[0] );
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[23] += +amp_sv[0];
      jamp_sv[24] -= amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[29] -= amp_sv[0];
      jamp_sv[33] += +amp_sv[0];
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[45] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[64] -= amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      jamp_sv[118] -= amp_sv[0];

      // *** DIAGRAM 1014 OF 1240 ***

      // Wavefunction(s) for diagram number 1014
      // (none)

      // Amplitude(s) for diagram number 1014
      VVV1_0( w_sv[0], w_sv[59], w_sv[11], COUPs[0], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[14] += +amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[38] += +amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[86] -= amp_sv[0];
      jamp_sv[96] -= amp_sv[0];
      jamp_sv[97] += +amp_sv[0];
      jamp_sv[99] += +amp_sv[0];
      jamp_sv[101] -= amp_sv[0];
      jamp_sv[105] += +amp_sv[0];
      jamp_sv[107] -= amp_sv[0];
      jamp_sv[113] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];

      // *** DIAGRAM 1015 OF 1240 ***

      // Wavefunction(s) for diagram number 1015
      VVVV1P0_1( w_sv[0], w_sv[1], w_sv[8], COUPs[2], 0., 0., w_sv[11] );
      VVVV3P0_1( w_sv[0], w_sv[1], w_sv[8], COUPs[2], 0., 0., w_sv[42] );
      VVVV4P0_1( w_sv[0], w_sv[1], w_sv[8], COUPs[2], 0., 0., w_sv[76] );

      // Amplitude(s) for diagram number 1015
      VVV1_0( w_sv[24], w_sv[6], w_sv[11], COUPs[0], &amp_sv[0] );
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[23] += +amp_sv[0];
      jamp_sv[24] -= amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[29] -= amp_sv[0];
      jamp_sv[33] += +amp_sv[0];
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[45] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[64] -= amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      jamp_sv[118] -= amp_sv[0];
      VVV1_0( w_sv[24], w_sv[6], w_sv[42], COUPs[0], &amp_sv[0] );
      jamp_sv[0] -= amp_sv[0];
      jamp_sv[2] += +amp_sv[0];
      jamp_sv[4] += +amp_sv[0];
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[23] += +amp_sv[0];
      jamp_sv[33] += +amp_sv[0];
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[45] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[89] += +amp_sv[0];
      jamp_sv[113] += +amp_sv[0];
      jamp_sv[119] -= amp_sv[0];
      VVV1_0( w_sv[24], w_sv[6], w_sv[76], COUPs[0], &amp_sv[0] );
      jamp_sv[0] -= amp_sv[0];
      jamp_sv[2] += +amp_sv[0];
      jamp_sv[4] += +amp_sv[0];
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[26] -= amp_sv[0];
      jamp_sv[28] -= amp_sv[0];
      jamp_sv[29] += +amp_sv[0];
      jamp_sv[64] += +amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[88] -= amp_sv[0];
      jamp_sv[89] += +amp_sv[0];
      jamp_sv[112] -= amp_sv[0];
      jamp_sv[113] += +amp_sv[0];
      jamp_sv[118] += +amp_sv[0];
      jamp_sv[119] -= amp_sv[0];

      // *** DIAGRAM 1016 OF 1240 ***

      // Wavefunction(s) for diagram number 1016
      VVVV1P0_1( w_sv[0], w_sv[1], w_sv[24], COUPs[2], 0., 0., w_sv[97] );
      VVVV3P0_1( w_sv[0], w_sv[1], w_sv[24], COUPs[2], 0., 0., w_sv[71] );
      VVVV4P0_1( w_sv[0], w_sv[1], w_sv[24], COUPs[2], 0., 0., w_sv[21] );

      // Amplitude(s) for diagram number 1016
      VVV1_0( w_sv[8], w_sv[6], w_sv[97], COUPs[0], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[14] += +amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[38] += +amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[86] -= amp_sv[0];
      jamp_sv[96] -= amp_sv[0];
      jamp_sv[97] += +amp_sv[0];
      jamp_sv[99] += +amp_sv[0];
      jamp_sv[101] -= amp_sv[0];
      jamp_sv[105] += +amp_sv[0];
      jamp_sv[107] -= amp_sv[0];
      jamp_sv[113] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];
      VVV1_0( w_sv[8], w_sv[6], w_sv[71], COUPs[0], &amp_sv[0] );
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[14] += +amp_sv[0];
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[26] -= amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[38] += +amp_sv[0];
      jamp_sv[60] += +amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[99] += +amp_sv[0];
      jamp_sv[101] -= amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[103] += +amp_sv[0];
      jamp_sv[105] += +amp_sv[0];
      jamp_sv[107] -= amp_sv[0];
      jamp_sv[112] -= amp_sv[0];
      jamp_sv[118] += +amp_sv[0];
      VVV1_0( w_sv[8], w_sv[6], w_sv[21], COUPs[0], &amp_sv[0] );
      jamp_sv[0] -= amp_sv[0];
      jamp_sv[2] += +amp_sv[0];
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[26] -= amp_sv[0];
      jamp_sv[60] += +amp_sv[0];
      jamp_sv[62] -= amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[97] -= amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[103] += +amp_sv[0];
      jamp_sv[112] -= amp_sv[0];
      jamp_sv[113] += +amp_sv[0];
      jamp_sv[118] += +amp_sv[0];
      jamp_sv[119] -= amp_sv[0];

      // *** DIAGRAM 1017 OF 1240 ***

      // Wavefunction(s) for diagram number 1017
      // (none)

      // Amplitude(s) for diagram number 1017
      VVV1_0( w_sv[1], w_sv[24], w_sv[118], COUPs[0], &amp_sv[0] );
      jamp_sv[0] -= amp_sv[0];
      jamp_sv[2] += +amp_sv[0];
      jamp_sv[8] += +amp_sv[0];
      jamp_sv[14] -= amp_sv[0];
      jamp_sv[32] += +amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[62] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[97] -= amp_sv[0];
      jamp_sv[99] -= amp_sv[0];
      jamp_sv[101] += +amp_sv[0];
      jamp_sv[105] -= amp_sv[0];
      jamp_sv[107] += +amp_sv[0];
      jamp_sv[113] += +amp_sv[0];
      jamp_sv[119] -= amp_sv[0];
      VVV1_0( w_sv[1], w_sv[24], w_sv[119], COUPs[0], &amp_sv[0] );
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[19] += +amp_sv[0];
      jamp_sv[21] += +amp_sv[0];
      jamp_sv[23] -= amp_sv[0];
      jamp_sv[32] += +amp_sv[0];
      jamp_sv[33] -= amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[39] += +amp_sv[0];
      jamp_sv[62] -= amp_sv[0];
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[97] -= amp_sv[0];
      jamp_sv[99] -= amp_sv[0];
      jamp_sv[101] += +amp_sv[0];
      VVV1_0( w_sv[1], w_sv[24], w_sv[120], COUPs[0], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[14] += +amp_sv[0];
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[19] += +amp_sv[0];
      jamp_sv[21] += +amp_sv[0];
      jamp_sv[23] -= amp_sv[0];
      jamp_sv[33] -= amp_sv[0];
      jamp_sv[39] += +amp_sv[0];
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[105] += +amp_sv[0];
      jamp_sv[107] -= amp_sv[0];
      jamp_sv[113] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];

      // *** DIAGRAM 1018 OF 1240 ***

      // Wavefunction(s) for diagram number 1018
      // (none)

      // Amplitude(s) for diagram number 1018
      VVV1_0( w_sv[1], w_sv[8], w_sv[85], COUPs[0], &amp_sv[0] );
      jamp_sv[9] -= amp_sv[0];
      jamp_sv[15] += +amp_sv[0];
      jamp_sv[21] += +amp_sv[0];
      jamp_sv[23] -= amp_sv[0];
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[26] -= amp_sv[0];
      jamp_sv[28] -= amp_sv[0];
      jamp_sv[29] += +amp_sv[0];
      jamp_sv[33] -= amp_sv[0];
      jamp_sv[39] += +amp_sv[0];
      jamp_sv[45] += +amp_sv[0];
      jamp_sv[47] -= amp_sv[0];
      jamp_sv[64] += +amp_sv[0];
      jamp_sv[88] -= amp_sv[0];
      jamp_sv[112] -= amp_sv[0];
      jamp_sv[118] += +amp_sv[0];
      VVV1_0( w_sv[1], w_sv[8], w_sv[112], COUPs[0], &amp_sv[0] );
      jamp_sv[21] += +amp_sv[0];
      jamp_sv[23] -= amp_sv[0];
      jamp_sv[28] -= amp_sv[0];
      jamp_sv[29] += +amp_sv[0];
      jamp_sv[32] += +amp_sv[0];
      jamp_sv[33] -= amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[39] += +amp_sv[0];
      jamp_sv[42] += +amp_sv[0];
      jamp_sv[43] -= amp_sv[0];
      jamp_sv[61] -= amp_sv[0];
      jamp_sv[64] += +amp_sv[0];
      jamp_sv[85] += +amp_sv[0];
      jamp_sv[88] -= amp_sv[0];
      jamp_sv[99] -= amp_sv[0];
      jamp_sv[101] += +amp_sv[0];
      VVV1_0( w_sv[1], w_sv[8], w_sv[111], COUPs[0], &amp_sv[0] );
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[24] -= amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[32] += +amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[42] += +amp_sv[0];
      jamp_sv[43] -= amp_sv[0];
      jamp_sv[45] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[61] -= amp_sv[0];
      jamp_sv[85] += +amp_sv[0];
      jamp_sv[99] -= amp_sv[0];
      jamp_sv[101] += +amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      jamp_sv[118] -= amp_sv[0];

      // *** DIAGRAM 1019 OF 1240 ***

      // Wavefunction(s) for diagram number 1019
      // (none)

      // Amplitude(s) for diagram number 1019
      VVV1_0( w_sv[56], w_sv[68], w_sv[5], COUPs[0], &amp_sv[0] );
      jamp_sv[1] += +amp_sv[0];
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[15] += +amp_sv[0];
      jamp_sv[17] -= amp_sv[0];
      jamp_sv[20] += +amp_sv[0];
      jamp_sv[35] -= amp_sv[0];
      jamp_sv[45] += +amp_sv[0];
      jamp_sv[69] += +amp_sv[0];
      jamp_sv[81] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[89] -= amp_sv[0];
      jamp_sv[95] += +amp_sv[0];
      jamp_sv[111] -= amp_sv[0];

      // *** DIAGRAM 1020 OF 1240 ***

      // Wavefunction(s) for diagram number 1020
      // (none)

      // Amplitude(s) for diagram number 1020
      VVV1_0( w_sv[56], w_sv[1], w_sv[16], COUPs[0], &amp_sv[0] );
      jamp_sv[1] += +amp_sv[0];
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[3] += +amp_sv[0];
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[11] -= amp_sv[0];
      jamp_sv[15] += +amp_sv[0];
      jamp_sv[17] -= amp_sv[0];
      jamp_sv[21] += +amp_sv[0];
      jamp_sv[35] -= amp_sv[0];
      jamp_sv[39] += +amp_sv[0];
      jamp_sv[41] -= amp_sv[0];
      jamp_sv[45] += +amp_sv[0];
      jamp_sv[71] += +amp_sv[0];
      jamp_sv[89] -= amp_sv[0];
      jamp_sv[95] += +amp_sv[0];
      jamp_sv[113] -= amp_sv[0];

      // *** DIAGRAM 1021 OF 1240 ***

      // Wavefunction(s) for diagram number 1021
      // (none)

      // Amplitude(s) for diagram number 1021
      VVVV1_0( w_sv[1], w_sv[27], w_sv[5], w_sv[56], COUPs[2], &amp_sv[0] );
      jamp_sv[1] += +amp_sv[0];
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[15] += +amp_sv[0];
      jamp_sv[17] -= amp_sv[0];
      jamp_sv[20] += +amp_sv[0];
      jamp_sv[35] -= amp_sv[0];
      jamp_sv[45] += +amp_sv[0];
      jamp_sv[69] += +amp_sv[0];
      jamp_sv[81] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[89] -= amp_sv[0];
      jamp_sv[95] += +amp_sv[0];
      jamp_sv[111] -= amp_sv[0];
      VVVV3_0( w_sv[1], w_sv[27], w_sv[5], w_sv[56], COUPs[2], &amp_sv[0] );
      jamp_sv[2] += +amp_sv[0];
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[20] += +amp_sv[0];
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[69] += +amp_sv[0];
      jamp_sv[71] -= amp_sv[0];
      jamp_sv[81] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[111] -= amp_sv[0];
      jamp_sv[113] += +amp_sv[0];
      VVVV4_0( w_sv[1], w_sv[27], w_sv[5], w_sv[56], COUPs[2], &amp_sv[0] );
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[2] += +amp_sv[0];
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[4] += +amp_sv[0];
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[45] -= amp_sv[0];
      jamp_sv[71] -= amp_sv[0];
      jamp_sv[89] += +amp_sv[0];
      jamp_sv[95] -= amp_sv[0];
      jamp_sv[113] += +amp_sv[0];

      // *** DIAGRAM 1022 OF 1240 ***

      // Wavefunction(s) for diagram number 1022
      // (none)

      // Amplitude(s) for diagram number 1022
      VVV1_0( w_sv[101], w_sv[108], w_sv[5], COUPs[0], &amp_sv[0] );
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[25] -= amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[34] += +amp_sv[0];
      jamp_sv[36] += +amp_sv[0];
      jamp_sv[37] -= amp_sv[0];
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[67] -= amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[77] += +amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[94] -= amp_sv[0];
      jamp_sv[109] += +amp_sv[0];

      // *** DIAGRAM 1023 OF 1240 ***

      // Wavefunction(s) for diagram number 1023
      // (none)

      // Amplitude(s) for diagram number 1023
      VVV1_0( w_sv[101], w_sv[1], w_sv[10], COUPs[0], &amp_sv[0] );
      jamp_sv[10] += +amp_sv[0];
      jamp_sv[20] -= amp_sv[0];
      jamp_sv[25] -= amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[34] += +amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[77] += +amp_sv[0];
      jamp_sv[78] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[81] -= amp_sv[0];
      jamp_sv[83] += +amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[94] -= amp_sv[0];
      jamp_sv[108] += +amp_sv[0];

      // *** DIAGRAM 1024 OF 1240 ***

      // Wavefunction(s) for diagram number 1024
      // (none)

      // Amplitude(s) for diagram number 1024
      VVVV1_0( w_sv[1], w_sv[8], w_sv[5], w_sv[101], COUPs[2], &amp_sv[0] );
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[25] -= amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[34] += +amp_sv[0];
      jamp_sv[36] += +amp_sv[0];
      jamp_sv[37] -= amp_sv[0];
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[67] -= amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[77] += +amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[94] -= amp_sv[0];
      jamp_sv[109] += +amp_sv[0];
      VVVV3_0( w_sv[1], w_sv[8], w_sv[5], w_sv[101], COUPs[2], &amp_sv[0] );
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[20] += +amp_sv[0];
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[36] += +amp_sv[0];
      jamp_sv[37] -= amp_sv[0];
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[66] += +amp_sv[0];
      jamp_sv[67] -= amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[79] += +amp_sv[0];
      jamp_sv[81] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      jamp_sv[109] += +amp_sv[0];
      VVVV4_0( w_sv[1], w_sv[8], w_sv[5], w_sv[101], COUPs[2], &amp_sv[0] );
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[20] += +amp_sv[0];
      jamp_sv[25] += +amp_sv[0];
      jamp_sv[28] -= amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[44] += +amp_sv[0];
      jamp_sv[66] += +amp_sv[0];
      jamp_sv[75] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[79] += +amp_sv[0];
      jamp_sv[81] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[88] -= amp_sv[0];
      jamp_sv[94] += +amp_sv[0];
      jamp_sv[108] -= amp_sv[0];

      // *** DIAGRAM 1025 OF 1240 ***

      // Wavefunction(s) for diagram number 1025
      // (none)

      // Amplitude(s) for diagram number 1025
      VVV1_0( w_sv[0], w_sv[108], w_sv[16], COUPs[0], &amp_sv[0] );
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[25] -= amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[27] -= amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[45] -= amp_sv[0];
      jamp_sv[70] -= amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[94] -= amp_sv[0];
      jamp_sv[112] += +amp_sv[0];

      // *** DIAGRAM 1026 OF 1240 ***

      // Wavefunction(s) for diagram number 1026
      // (none)

      // Amplitude(s) for diagram number 1026
      VVV1_0( w_sv[0], w_sv[68], w_sv[10], COUPs[0], &amp_sv[0] );
      jamp_sv[1] += +amp_sv[0];
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[20] += +amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[44] += +amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[72] -= amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[75] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[81] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[89] -= amp_sv[0];
      jamp_sv[95] += +amp_sv[0];
      jamp_sv[110] -= amp_sv[0];

      // *** DIAGRAM 1027 OF 1240 ***

      // Wavefunction(s) for diagram number 1027
      // (none)

      // Amplitude(s) for diagram number 1027
      VVV1_0( w_sv[27], w_sv[5], w_sv[11], COUPs[0], &amp_sv[0] );
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[25] -= amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[27] -= amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[45] -= amp_sv[0];
      jamp_sv[70] -= amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[94] -= amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      VVV1_0( w_sv[27], w_sv[5], w_sv[42], COUPs[0], &amp_sv[0] );
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[2] += +amp_sv[0];
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[4] += +amp_sv[0];
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[45] -= amp_sv[0];
      jamp_sv[71] -= amp_sv[0];
      jamp_sv[89] += +amp_sv[0];
      jamp_sv[95] -= amp_sv[0];
      jamp_sv[113] += +amp_sv[0];
      VVV1_0( w_sv[27], w_sv[5], w_sv[76], COUPs[0], &amp_sv[0] );
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[2] += +amp_sv[0];
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[4] += +amp_sv[0];
      jamp_sv[25] += +amp_sv[0];
      jamp_sv[26] -= amp_sv[0];
      jamp_sv[27] += +amp_sv[0];
      jamp_sv[28] -= amp_sv[0];
      jamp_sv[70] += +amp_sv[0];
      jamp_sv[71] -= amp_sv[0];
      jamp_sv[88] -= amp_sv[0];
      jamp_sv[89] += +amp_sv[0];
      jamp_sv[94] += +amp_sv[0];
      jamp_sv[95] -= amp_sv[0];
      jamp_sv[112] -= amp_sv[0];
      jamp_sv[113] += +amp_sv[0];

      // *** DIAGRAM 1028 OF 1240 ***

      // Wavefunction(s) for diagram number 1028
      VVVV1P0_1( w_sv[0], w_sv[1], w_sv[27], COUPs[2], 0., 0., w_sv[10] );
      VVVV3P0_1( w_sv[0], w_sv[1], w_sv[27], COUPs[2], 0., 0., w_sv[16] );
      VVVV4P0_1( w_sv[0], w_sv[1], w_sv[27], COUPs[2], 0., 0., w_sv[111] );

      // Amplitude(s) for diagram number 1028
      VVV1_0( w_sv[8], w_sv[5], w_sv[10], COUPs[0], &amp_sv[0] );
      jamp_sv[1] += +amp_sv[0];
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[20] += +amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[44] += +amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[72] -= amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[75] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[81] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[89] -= amp_sv[0];
      jamp_sv[95] += +amp_sv[0];
      jamp_sv[110] -= amp_sv[0];
      VVV1_0( w_sv[8], w_sv[5], w_sv[16], COUPs[0], &amp_sv[0] );
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[20] += +amp_sv[0];
      jamp_sv[25] += +amp_sv[0];
      jamp_sv[28] -= amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[44] += +amp_sv[0];
      jamp_sv[66] += +amp_sv[0];
      jamp_sv[75] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[79] += +amp_sv[0];
      jamp_sv[81] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[88] -= amp_sv[0];
      jamp_sv[94] += +amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      VVV1_0( w_sv[8], w_sv[5], w_sv[111], COUPs[0], &amp_sv[0] );
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[4] += +amp_sv[0];
      jamp_sv[25] += +amp_sv[0];
      jamp_sv[28] -= amp_sv[0];
      jamp_sv[66] += +amp_sv[0];
      jamp_sv[68] -= amp_sv[0];
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[73] -= amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[79] += +amp_sv[0];
      jamp_sv[88] -= amp_sv[0];
      jamp_sv[89] += +amp_sv[0];
      jamp_sv[94] += +amp_sv[0];
      jamp_sv[95] -= amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];

      // *** DIAGRAM 1029 OF 1240 ***

      // Wavefunction(s) for diagram number 1029
      // (none)

      // Amplitude(s) for diagram number 1029
      VVV1_0( w_sv[1], w_sv[27], w_sv[115], COUPs[0], &amp_sv[0] );
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[4] += +amp_sv[0];
      jamp_sv[10] += +amp_sv[0];
      jamp_sv[20] -= amp_sv[0];
      jamp_sv[34] += +amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[68] -= amp_sv[0];
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[73] -= amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[77] += +amp_sv[0];
      jamp_sv[81] -= amp_sv[0];
      jamp_sv[83] += +amp_sv[0];
      jamp_sv[89] += +amp_sv[0];
      jamp_sv[95] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];
      VVV1_0( w_sv[1], w_sv[27], w_sv[116], COUPs[0], &amp_sv[0] );
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[15] += +amp_sv[0];
      jamp_sv[17] -= amp_sv[0];
      jamp_sv[34] += +amp_sv[0];
      jamp_sv[35] -= amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[45] += +amp_sv[0];
      jamp_sv[68] -= amp_sv[0];
      jamp_sv[69] += +amp_sv[0];
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[73] -= amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[77] += +amp_sv[0];
      jamp_sv[110] += +amp_sv[0];
      jamp_sv[111] -= amp_sv[0];
      VVV1_0( w_sv[1], w_sv[27], w_sv[117], COUPs[0], &amp_sv[0] );
      jamp_sv[1] += +amp_sv[0];
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[15] += +amp_sv[0];
      jamp_sv[17] -= amp_sv[0];
      jamp_sv[20] += +amp_sv[0];
      jamp_sv[35] -= amp_sv[0];
      jamp_sv[45] += +amp_sv[0];
      jamp_sv[69] += +amp_sv[0];
      jamp_sv[81] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[89] -= amp_sv[0];
      jamp_sv[95] += +amp_sv[0];
      jamp_sv[111] -= amp_sv[0];

      // *** DIAGRAM 1030 OF 1240 ***

      // Wavefunction(s) for diagram number 1030
      // (none)

      // Amplitude(s) for diagram number 1030
      VVV1_0( w_sv[1], w_sv[8], w_sv[9], COUPs[0], &amp_sv[0] );
      jamp_sv[11] -= amp_sv[0];
      jamp_sv[15] += +amp_sv[0];
      jamp_sv[17] -= amp_sv[0];
      jamp_sv[21] += +amp_sv[0];
      jamp_sv[25] += +amp_sv[0];
      jamp_sv[26] -= amp_sv[0];
      jamp_sv[27] += +amp_sv[0];
      jamp_sv[28] -= amp_sv[0];
      jamp_sv[35] -= amp_sv[0];
      jamp_sv[39] += +amp_sv[0];
      jamp_sv[41] -= amp_sv[0];
      jamp_sv[45] += +amp_sv[0];
      jamp_sv[70] += +amp_sv[0];
      jamp_sv[88] -= amp_sv[0];
      jamp_sv[94] += +amp_sv[0];
      jamp_sv[112] -= amp_sv[0];
      VVV1_0( w_sv[1], w_sv[8], w_sv[110], COUPs[0], &amp_sv[0] );
      jamp_sv[15] += +amp_sv[0];
      jamp_sv[17] -= amp_sv[0];
      jamp_sv[26] -= amp_sv[0];
      jamp_sv[27] += +amp_sv[0];
      jamp_sv[34] += +amp_sv[0];
      jamp_sv[35] -= amp_sv[0];
      jamp_sv[36] += +amp_sv[0];
      jamp_sv[37] -= amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[45] += +amp_sv[0];
      jamp_sv[67] -= amp_sv[0];
      jamp_sv[70] += +amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[77] += +amp_sv[0];
      jamp_sv[109] += +amp_sv[0];
      jamp_sv[112] -= amp_sv[0];
      VVV1_0( w_sv[1], w_sv[8], w_sv[109], COUPs[0], &amp_sv[0] );
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[25] -= amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[34] += +amp_sv[0];
      jamp_sv[36] += +amp_sv[0];
      jamp_sv[37] -= amp_sv[0];
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[67] -= amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[77] += +amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[94] -= amp_sv[0];
      jamp_sv[109] += +amp_sv[0];

      // *** DIAGRAM 1031 OF 1240 ***

      // Wavefunction(s) for diagram number 1031
      // (none)

      // Amplitude(s) for diagram number 1031
      VVV1_0( w_sv[56], w_sv[67], w_sv[4], COUPs[0], &amp_sv[0] );
      jamp_sv[3] += +amp_sv[0];
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[11] -= amp_sv[0];
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[22] += +amp_sv[0];
      jamp_sv[41] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[57] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[71] += +amp_sv[0];
      jamp_sv[93] += +amp_sv[0];
      jamp_sv[117] -= amp_sv[0];

      // *** DIAGRAM 1032 OF 1240 ***

      // Wavefunction(s) for diagram number 1032
      // (none)

      // Amplitude(s) for diagram number 1032
      VVV1_0( w_sv[56], w_sv[1], w_sv[19], COUPs[0], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[5] += +amp_sv[0];
      jamp_sv[9] -= amp_sv[0];
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[23] -= amp_sv[0];
      jamp_sv[33] -= amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[47] -= amp_sv[0];
      jamp_sv[65] += +amp_sv[0];
      jamp_sv[71] -= amp_sv[0];
      jamp_sv[95] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];

      // *** DIAGRAM 1033 OF 1240 ***

      // Wavefunction(s) for diagram number 1033
      // (none)

      // Amplitude(s) for diagram number 1033
      VVVV1_0( w_sv[1], w_sv[4], w_sv[29], w_sv[56], COUPs[2], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[22] += +amp_sv[0];
      jamp_sv[23] -= amp_sv[0];
      jamp_sv[33] -= amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[57] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[93] += +amp_sv[0];
      jamp_sv[95] -= amp_sv[0];
      jamp_sv[117] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];
      VVVV3_0( w_sv[1], w_sv[4], w_sv[29], w_sv[56], COUPs[2], &amp_sv[0] );
      jamp_sv[3] += +amp_sv[0];
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[11] -= amp_sv[0];
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[22] += +amp_sv[0];
      jamp_sv[41] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[57] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[71] += +amp_sv[0];
      jamp_sv[93] += +amp_sv[0];
      jamp_sv[117] -= amp_sv[0];
      VVVV4_0( w_sv[1], w_sv[4], w_sv[29], w_sv[56], COUPs[2], &amp_sv[0] );
      jamp_sv[0] -= amp_sv[0];
      jamp_sv[1] += +amp_sv[0];
      jamp_sv[3] += +amp_sv[0];
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[11] -= amp_sv[0];
      jamp_sv[17] -= amp_sv[0];
      jamp_sv[23] += +amp_sv[0];
      jamp_sv[33] += +amp_sv[0];
      jamp_sv[35] -= amp_sv[0];
      jamp_sv[41] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[71] += +amp_sv[0];
      jamp_sv[95] += +amp_sv[0];
      jamp_sv[119] -= amp_sv[0];

      // *** DIAGRAM 1034 OF 1240 ***

      // Wavefunction(s) for diagram number 1034
      // (none)

      // Amplitude(s) for diagram number 1034
      VVV1_0( w_sv[96], w_sv[108], w_sv[4], COUPs[0], &amp_sv[0] );
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[23] -= amp_sv[0];
      jamp_sv[27] -= amp_sv[0];
      jamp_sv[29] += +amp_sv[0];
      jamp_sv[30] += +amp_sv[0];
      jamp_sv[31] -= amp_sv[0];
      jamp_sv[33] -= amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[40] += +amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[53] += +amp_sv[0];
      jamp_sv[64] += +amp_sv[0];
      jamp_sv[70] -= amp_sv[0];
      jamp_sv[91] -= amp_sv[0];
      jamp_sv[115] += +amp_sv[0];

      // *** DIAGRAM 1035 OF 1240 ***

      // Wavefunction(s) for diagram number 1035
      // (none)

      // Amplitude(s) for diagram number 1035
      VVV1_0( w_sv[96], w_sv[1], w_sv[13], COUPs[0], &amp_sv[0] );
      jamp_sv[16] += +amp_sv[0];
      jamp_sv[22] -= amp_sv[0];
      jamp_sv[27] -= amp_sv[0];
      jamp_sv[29] += +amp_sv[0];
      jamp_sv[40] += +amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[53] += +amp_sv[0];
      jamp_sv[54] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[57] -= amp_sv[0];
      jamp_sv[59] += +amp_sv[0];
      jamp_sv[64] += +amp_sv[0];
      jamp_sv[70] -= amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[114] += +amp_sv[0];

      // *** DIAGRAM 1036 OF 1240 ***

      // Wavefunction(s) for diagram number 1036
      // (none)

      // Amplitude(s) for diagram number 1036
      VVVV1_0( w_sv[1], w_sv[8], w_sv[4], w_sv[96], COUPs[2], &amp_sv[0] );
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[23] -= amp_sv[0];
      jamp_sv[27] -= amp_sv[0];
      jamp_sv[29] += +amp_sv[0];
      jamp_sv[30] += +amp_sv[0];
      jamp_sv[31] -= amp_sv[0];
      jamp_sv[33] -= amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[40] += +amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[53] += +amp_sv[0];
      jamp_sv[64] += +amp_sv[0];
      jamp_sv[70] -= amp_sv[0];
      jamp_sv[91] -= amp_sv[0];
      jamp_sv[115] += +amp_sv[0];
      VVVV3_0( w_sv[1], w_sv[8], w_sv[4], w_sv[96], COUPs[2], &amp_sv[0] );
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[22] += +amp_sv[0];
      jamp_sv[23] -= amp_sv[0];
      jamp_sv[30] += +amp_sv[0];
      jamp_sv[31] -= amp_sv[0];
      jamp_sv[33] -= amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[55] += +amp_sv[0];
      jamp_sv[57] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[90] += +amp_sv[0];
      jamp_sv[91] -= amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      jamp_sv[115] += +amp_sv[0];
      VVVV4_0( w_sv[1], w_sv[8], w_sv[4], w_sv[96], COUPs[2], &amp_sv[0] );
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[22] += +amp_sv[0];
      jamp_sv[27] += +amp_sv[0];
      jamp_sv[29] -= amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[46] += +amp_sv[0];
      jamp_sv[51] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[55] += +amp_sv[0];
      jamp_sv[57] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[64] -= amp_sv[0];
      jamp_sv[70] += +amp_sv[0];
      jamp_sv[90] += +amp_sv[0];
      jamp_sv[114] -= amp_sv[0];

      // *** DIAGRAM 1037 OF 1240 ***

      // Wavefunction(s) for diagram number 1037
      // (none)

      // Amplitude(s) for diagram number 1037
      VVV1_0( w_sv[0], w_sv[108], w_sv[19], COUPs[0], &amp_sv[0] );
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[11] -= amp_sv[0];
      jamp_sv[17] -= amp_sv[0];
      jamp_sv[23] += +amp_sv[0];
      jamp_sv[24] -= amp_sv[0];
      jamp_sv[25] += +amp_sv[0];
      jamp_sv[27] += +amp_sv[0];
      jamp_sv[29] -= amp_sv[0];
      jamp_sv[33] += +amp_sv[0];
      jamp_sv[35] -= amp_sv[0];
      jamp_sv[41] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[64] -= amp_sv[0];
      jamp_sv[70] += +amp_sv[0];
      jamp_sv[94] += +amp_sv[0];
      jamp_sv[118] -= amp_sv[0];

      // *** DIAGRAM 1038 OF 1240 ***

      // Wavefunction(s) for diagram number 1038
      // (none)

      // Amplitude(s) for diagram number 1038
      VVV1_0( w_sv[0], w_sv[67], w_sv[13], COUPs[0], &amp_sv[0] );
      jamp_sv[3] += +amp_sv[0];
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[22] += +amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[46] += +amp_sv[0];
      jamp_sv[48] -= amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[51] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[57] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[71] += +amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[116] -= amp_sv[0];

      // *** DIAGRAM 1039 OF 1240 ***

      // Wavefunction(s) for diagram number 1039
      // (none)

      // Amplitude(s) for diagram number 1039
      VVV1_0( w_sv[4], w_sv[29], w_sv[11], COUPs[0], &amp_sv[0] );
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[11] -= amp_sv[0];
      jamp_sv[17] -= amp_sv[0];
      jamp_sv[23] += +amp_sv[0];
      jamp_sv[24] -= amp_sv[0];
      jamp_sv[25] += +amp_sv[0];
      jamp_sv[27] += +amp_sv[0];
      jamp_sv[29] -= amp_sv[0];
      jamp_sv[33] += +amp_sv[0];
      jamp_sv[35] -= amp_sv[0];
      jamp_sv[41] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[64] -= amp_sv[0];
      jamp_sv[70] += +amp_sv[0];
      jamp_sv[94] += +amp_sv[0];
      jamp_sv[118] -= amp_sv[0];
      VVV1_0( w_sv[4], w_sv[29], w_sv[42], COUPs[0], &amp_sv[0] );
      jamp_sv[0] -= amp_sv[0];
      jamp_sv[1] += +amp_sv[0];
      jamp_sv[3] += +amp_sv[0];
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[11] -= amp_sv[0];
      jamp_sv[17] -= amp_sv[0];
      jamp_sv[23] += +amp_sv[0];
      jamp_sv[33] += +amp_sv[0];
      jamp_sv[35] -= amp_sv[0];
      jamp_sv[41] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[71] += +amp_sv[0];
      jamp_sv[95] += +amp_sv[0];
      jamp_sv[119] -= amp_sv[0];
      VVV1_0( w_sv[4], w_sv[29], w_sv[76], COUPs[0], &amp_sv[0] );
      jamp_sv[0] -= amp_sv[0];
      jamp_sv[1] += +amp_sv[0];
      jamp_sv[3] += +amp_sv[0];
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[25] -= amp_sv[0];
      jamp_sv[27] -= amp_sv[0];
      jamp_sv[29] += +amp_sv[0];
      jamp_sv[64] += +amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[70] -= amp_sv[0];
      jamp_sv[71] += +amp_sv[0];
      jamp_sv[94] -= amp_sv[0];
      jamp_sv[95] += +amp_sv[0];
      jamp_sv[118] += +amp_sv[0];
      jamp_sv[119] -= amp_sv[0];

      // *** DIAGRAM 1040 OF 1240 ***

      // Wavefunction(s) for diagram number 1040
      VVVV1P0_1( w_sv[0], w_sv[1], w_sv[29], COUPs[2], 0., 0., w_sv[76] );
      VVVV3P0_1( w_sv[0], w_sv[1], w_sv[29], COUPs[2], 0., 0., w_sv[42] );
      VVVV4P0_1( w_sv[0], w_sv[1], w_sv[29], COUPs[2], 0., 0., w_sv[11] );

      // Amplitude(s) for diagram number 1040
      VVV1_0( w_sv[8], w_sv[4], w_sv[76], COUPs[0], &amp_sv[0] );
      jamp_sv[3] += +amp_sv[0];
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[22] += +amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[46] += +amp_sv[0];
      jamp_sv[48] -= amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[51] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[57] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[71] += +amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[116] -= amp_sv[0];
      VVV1_0( w_sv[8], w_sv[4], w_sv[42], COUPs[0], &amp_sv[0] );
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[22] += +amp_sv[0];
      jamp_sv[27] += +amp_sv[0];
      jamp_sv[29] -= amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[46] += +amp_sv[0];
      jamp_sv[51] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[55] += +amp_sv[0];
      jamp_sv[57] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[64] -= amp_sv[0];
      jamp_sv[70] += +amp_sv[0];
      jamp_sv[90] += +amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      VVV1_0( w_sv[8], w_sv[4], w_sv[11], COUPs[0], &amp_sv[0] );
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[5] += +amp_sv[0];
      jamp_sv[27] += +amp_sv[0];
      jamp_sv[29] -= amp_sv[0];
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[49] -= amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[55] += +amp_sv[0];
      jamp_sv[64] -= amp_sv[0];
      jamp_sv[65] += +amp_sv[0];
      jamp_sv[70] += +amp_sv[0];
      jamp_sv[71] -= amp_sv[0];
      jamp_sv[90] += +amp_sv[0];
      jamp_sv[92] -= amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];

      // *** DIAGRAM 1041 OF 1240 ***

      // Wavefunction(s) for diagram number 1041
      // (none)

      // Amplitude(s) for diagram number 1041
      VVV1_0( w_sv[1], w_sv[29], w_sv[107], COUPs[0], &amp_sv[0] );
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[5] += +amp_sv[0];
      jamp_sv[16] += +amp_sv[0];
      jamp_sv[22] -= amp_sv[0];
      jamp_sv[40] += +amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[49] -= amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[53] += +amp_sv[0];
      jamp_sv[57] -= amp_sv[0];
      jamp_sv[59] += +amp_sv[0];
      jamp_sv[65] += +amp_sv[0];
      jamp_sv[71] -= amp_sv[0];
      jamp_sv[92] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];
      VVV1_0( w_sv[1], w_sv[29], w_sv[95], COUPs[0], &amp_sv[0] );
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[11] -= amp_sv[0];
      jamp_sv[40] += +amp_sv[0];
      jamp_sv[41] -= amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[49] -= amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[53] += +amp_sv[0];
      jamp_sv[92] -= amp_sv[0];
      jamp_sv[93] += +amp_sv[0];
      jamp_sv[116] += +amp_sv[0];
      jamp_sv[117] -= amp_sv[0];
      VVV1_0( w_sv[1], w_sv[29], w_sv[105], COUPs[0], &amp_sv[0] );
      jamp_sv[3] += +amp_sv[0];
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[11] -= amp_sv[0];
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[22] += +amp_sv[0];
      jamp_sv[41] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[57] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[71] += +amp_sv[0];
      jamp_sv[93] += +amp_sv[0];
      jamp_sv[117] -= amp_sv[0];

      // *** DIAGRAM 1042 OF 1240 ***

      // Wavefunction(s) for diagram number 1042
      // (none)

      // Amplitude(s) for diagram number 1042
      VVV1_0( w_sv[1], w_sv[8], w_sv[87], COUPs[0], &amp_sv[0] );
      jamp_sv[9] -= amp_sv[0];
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[23] -= amp_sv[0];
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[25] -= amp_sv[0];
      jamp_sv[27] -= amp_sv[0];
      jamp_sv[29] += +amp_sv[0];
      jamp_sv[33] -= amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[47] -= amp_sv[0];
      jamp_sv[64] += +amp_sv[0];
      jamp_sv[70] -= amp_sv[0];
      jamp_sv[94] -= amp_sv[0];
      jamp_sv[118] += +amp_sv[0];
      VVV1_0( w_sv[1], w_sv[8], w_sv[34], COUPs[0], &amp_sv[0] );
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[23] -= amp_sv[0];
      jamp_sv[27] -= amp_sv[0];
      jamp_sv[29] += +amp_sv[0];
      jamp_sv[30] += +amp_sv[0];
      jamp_sv[31] -= amp_sv[0];
      jamp_sv[33] -= amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[40] += +amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[53] += +amp_sv[0];
      jamp_sv[64] += +amp_sv[0];
      jamp_sv[70] -= amp_sv[0];
      jamp_sv[91] -= amp_sv[0];
      jamp_sv[115] += +amp_sv[0];
      VVV1_0( w_sv[1], w_sv[8], w_sv[86], COUPs[0], &amp_sv[0] );
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[11] -= amp_sv[0];
      jamp_sv[24] -= amp_sv[0];
      jamp_sv[25] += +amp_sv[0];
      jamp_sv[30] += +amp_sv[0];
      jamp_sv[31] -= amp_sv[0];
      jamp_sv[40] += +amp_sv[0];
      jamp_sv[41] -= amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[53] += +amp_sv[0];
      jamp_sv[91] -= amp_sv[0];
      jamp_sv[94] += +amp_sv[0];
      jamp_sv[115] += +amp_sv[0];
      jamp_sv[118] -= amp_sv[0];

      // *** DIAGRAM 1043 OF 1240 ***

      // Wavefunction(s) for diagram number 1043
      // (none)

      // Amplitude(s) for diagram number 1043
      VVVV1_0( w_sv[0], w_sv[1], w_sv[8], w_sv[30], COUPs[2], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[5] += +amp_sv[0];
      jamp_sv[24] -= amp_sv[0];
      jamp_sv[25] += +amp_sv[0];
      jamp_sv[27] += +amp_sv[0];
      jamp_sv[29] -= amp_sv[0];
      jamp_sv[64] -= amp_sv[0];
      jamp_sv[65] += +amp_sv[0];
      jamp_sv[70] += +amp_sv[0];
      jamp_sv[71] -= amp_sv[0];
      jamp_sv[94] += +amp_sv[0];
      jamp_sv[95] -= amp_sv[0];
      jamp_sv[118] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];
      VVVV3_0( w_sv[0], w_sv[1], w_sv[8], w_sv[30], COUPs[2], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[5] += +amp_sv[0];
      jamp_sv[9] -= amp_sv[0];
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[23] -= amp_sv[0];
      jamp_sv[33] -= amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[47] -= amp_sv[0];
      jamp_sv[65] += +amp_sv[0];
      jamp_sv[71] -= amp_sv[0];
      jamp_sv[95] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];
      VVVV4_0( w_sv[0], w_sv[1], w_sv[8], w_sv[30], COUPs[2], &amp_sv[0] );
      jamp_sv[9] -= amp_sv[0];
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[23] -= amp_sv[0];
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[25] -= amp_sv[0];
      jamp_sv[27] -= amp_sv[0];
      jamp_sv[29] += +amp_sv[0];
      jamp_sv[33] -= amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[47] -= amp_sv[0];
      jamp_sv[64] += +amp_sv[0];
      jamp_sv[70] -= amp_sv[0];
      jamp_sv[94] -= amp_sv[0];
      jamp_sv[118] += +amp_sv[0];
      VVVV1_0( w_sv[0], w_sv[1], w_sv[8], w_sv[31], COUPs[2], &amp_sv[0] );
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[2] += +amp_sv[0];
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[4] += +amp_sv[0];
      jamp_sv[25] += +amp_sv[0];
      jamp_sv[26] -= amp_sv[0];
      jamp_sv[27] += +amp_sv[0];
      jamp_sv[28] -= amp_sv[0];
      jamp_sv[70] += +amp_sv[0];
      jamp_sv[71] -= amp_sv[0];
      jamp_sv[88] -= amp_sv[0];
      jamp_sv[89] += +amp_sv[0];
      jamp_sv[94] += +amp_sv[0];
      jamp_sv[95] -= amp_sv[0];
      jamp_sv[112] -= amp_sv[0];
      jamp_sv[113] += +amp_sv[0];
      VVVV3_0( w_sv[0], w_sv[1], w_sv[8], w_sv[31], COUPs[2], &amp_sv[0] );
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[2] += +amp_sv[0];
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[4] += +amp_sv[0];
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[45] -= amp_sv[0];
      jamp_sv[71] -= amp_sv[0];
      jamp_sv[89] += +amp_sv[0];
      jamp_sv[95] -= amp_sv[0];
      jamp_sv[113] += +amp_sv[0];
      VVVV4_0( w_sv[0], w_sv[1], w_sv[8], w_sv[31], COUPs[2], &amp_sv[0] );
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[25] -= amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[27] -= amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[45] -= amp_sv[0];
      jamp_sv[70] -= amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[94] -= amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      VVVV1_0( w_sv[0], w_sv[1], w_sv[8], w_sv[32], COUPs[2], &amp_sv[0] );
      jamp_sv[0] -= amp_sv[0];
      jamp_sv[2] += +amp_sv[0];
      jamp_sv[4] += +amp_sv[0];
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[26] -= amp_sv[0];
      jamp_sv[28] -= amp_sv[0];
      jamp_sv[29] += +amp_sv[0];
      jamp_sv[64] += +amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[88] -= amp_sv[0];
      jamp_sv[89] += +amp_sv[0];
      jamp_sv[112] -= amp_sv[0];
      jamp_sv[113] += +amp_sv[0];
      jamp_sv[118] += +amp_sv[0];
      jamp_sv[119] -= amp_sv[0];
      VVVV3_0( w_sv[0], w_sv[1], w_sv[8], w_sv[32], COUPs[2], &amp_sv[0] );
      jamp_sv[0] -= amp_sv[0];
      jamp_sv[2] += +amp_sv[0];
      jamp_sv[4] += +amp_sv[0];
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[23] += +amp_sv[0];
      jamp_sv[33] += +amp_sv[0];
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[45] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[89] += +amp_sv[0];
      jamp_sv[113] += +amp_sv[0];
      jamp_sv[119] -= amp_sv[0];
      VVVV4_0( w_sv[0], w_sv[1], w_sv[8], w_sv[32], COUPs[2], &amp_sv[0] );
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[23] += +amp_sv[0];
      jamp_sv[24] -= amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[29] -= amp_sv[0];
      jamp_sv[33] += +amp_sv[0];
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[45] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[64] -= amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      jamp_sv[118] -= amp_sv[0];

      // *** DIAGRAM 1044 OF 1240 ***

      // Wavefunction(s) for diagram number 1044
      // (none)

      // Amplitude(s) for diagram number 1044
      VVV1_0( w_sv[1], w_sv[30], w_sv[56], COUPs[0], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[5] += +amp_sv[0];
      jamp_sv[9] -= amp_sv[0];
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[23] -= amp_sv[0];
      jamp_sv[33] -= amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[47] -= amp_sv[0];
      jamp_sv[65] += +amp_sv[0];
      jamp_sv[71] -= amp_sv[0];
      jamp_sv[95] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];
      VVV1_0( w_sv[1], w_sv[31], w_sv[56], COUPs[0], &amp_sv[0] );
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[2] += +amp_sv[0];
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[4] += +amp_sv[0];
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[45] -= amp_sv[0];
      jamp_sv[71] -= amp_sv[0];
      jamp_sv[89] += +amp_sv[0];
      jamp_sv[95] -= amp_sv[0];
      jamp_sv[113] += +amp_sv[0];
      VVV1_0( w_sv[1], w_sv[32], w_sv[56], COUPs[0], &amp_sv[0] );
      jamp_sv[0] -= amp_sv[0];
      jamp_sv[2] += +amp_sv[0];
      jamp_sv[4] += +amp_sv[0];
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[23] += +amp_sv[0];
      jamp_sv[33] += +amp_sv[0];
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[45] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[89] += +amp_sv[0];
      jamp_sv[113] += +amp_sv[0];
      jamp_sv[119] -= amp_sv[0];

      // *** DIAGRAM 1045 OF 1240 ***

      // Wavefunction(s) for diagram number 1045
      // (none)

      // Amplitude(s) for diagram number 1045
      VVV1_0( w_sv[1], w_sv[8], w_sv[92], COUPs[0], &amp_sv[0] );
      jamp_sv[9] -= amp_sv[0];
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[23] -= amp_sv[0];
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[25] -= amp_sv[0];
      jamp_sv[27] -= amp_sv[0];
      jamp_sv[29] += +amp_sv[0];
      jamp_sv[33] -= amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[47] -= amp_sv[0];
      jamp_sv[64] += +amp_sv[0];
      jamp_sv[70] -= amp_sv[0];
      jamp_sv[94] -= amp_sv[0];
      jamp_sv[118] += +amp_sv[0];
      VVV1_0( w_sv[1], w_sv[8], w_sv[88], COUPs[0], &amp_sv[0] );
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[25] -= amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[27] -= amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[45] -= amp_sv[0];
      jamp_sv[70] -= amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[94] -= amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      VVV1_0( w_sv[1], w_sv[8], w_sv[106], COUPs[0], &amp_sv[0] );
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[23] += +amp_sv[0];
      jamp_sv[24] -= amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[29] -= amp_sv[0];
      jamp_sv[33] += +amp_sv[0];
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[45] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[64] -= amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      jamp_sv[118] -= amp_sv[0];

      // *** DIAGRAM 1046 OF 1240 ***

      // Wavefunction(s) for diagram number 1046
      // (none)

      // Amplitude(s) for diagram number 1046
      FFV1_0( w_sv[58], w_sv[114], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[52] -= amp_sv[0];

      // *** DIAGRAM 1047 OF 1240 ***

      // Wavefunction(s) for diagram number 1047
      // (none)

      // Amplitude(s) for diagram number 1047
      FFV1_0( w_sv[48], w_sv[114], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[49] -= amp_sv[0];

      // *** DIAGRAM 1048 OF 1240 ***

      // Wavefunction(s) for diagram number 1048
      // (none)

      // Amplitude(s) for diagram number 1048
      FFV1_0( w_sv[104], w_sv[100], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[58] -= amp_sv[0];

      // *** DIAGRAM 1049 OF 1240 ***

      // Wavefunction(s) for diagram number 1049
      // (none)

      // Amplitude(s) for diagram number 1049
      FFV1_0( w_sv[104], w_sv[36], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[68] -= amp_sv[0];

      // *** DIAGRAM 1050 OF 1240 ***

      // Wavefunction(s) for diagram number 1050
      // (none)

      // Amplitude(s) for diagram number 1050
      FFV1_0( w_sv[48], w_sv[100], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[55] -= amp_sv[0];

      // *** DIAGRAM 1051 OF 1240 ***

      // Wavefunction(s) for diagram number 1051
      // (none)

      // Amplitude(s) for diagram number 1051
      FFV1_0( w_sv[58], w_sv[36], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[66] -= amp_sv[0];

      // *** DIAGRAM 1052 OF 1240 ***

      // Wavefunction(s) for diagram number 1052
      // (none)

      // Amplitude(s) for diagram number 1052
      FFV1_0( w_sv[60], w_sv[114], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[50] -= amp_sv[0];

      // *** DIAGRAM 1053 OF 1240 ***

      // Wavefunction(s) for diagram number 1053
      // (none)

      // Amplitude(s) for diagram number 1053
      FFV1_0( w_sv[40], w_sv[114], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[48] -= amp_sv[0];

      // *** DIAGRAM 1054 OF 1240 ***

      // Wavefunction(s) for diagram number 1054
      // (none)

      // Amplitude(s) for diagram number 1054
      FFV1_0( w_sv[62], w_sv[100], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[56] -= amp_sv[0];

      // *** DIAGRAM 1055 OF 1240 ***

      // Wavefunction(s) for diagram number 1055
      // (none)

      // Amplitude(s) for diagram number 1055
      FFV1_0( w_sv[62], w_sv[35], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[62] -= amp_sv[0];

      // *** DIAGRAM 1056 OF 1240 ***

      // Wavefunction(s) for diagram number 1056
      // (none)

      // Amplitude(s) for diagram number 1056
      FFV1_0( w_sv[40], w_sv[100], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[54] -= amp_sv[0];

      // *** DIAGRAM 1057 OF 1240 ***

      // Wavefunction(s) for diagram number 1057
      // (none)

      // Amplitude(s) for diagram number 1057
      FFV1_0( w_sv[60], w_sv[35], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[60] -= amp_sv[0];

      // *** DIAGRAM 1058 OF 1240 ***

      // Wavefunction(s) for diagram number 1058
      // (none)

      // Amplitude(s) for diagram number 1058
      FFV1_0( w_sv[3], w_sv[114], w_sv[67], COUPs[1], &amp_sv[0] );
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[49] -= amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[53] += +amp_sv[0];

      // *** DIAGRAM 1059 OF 1240 ***

      // Wavefunction(s) for diagram number 1059
      // (none)

      // Amplitude(s) for diagram number 1059
      FFV1_0( w_sv[12], w_sv[114], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[48] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[49] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1060 OF 1240 ***

      // Wavefunction(s) for diagram number 1060
      // (none)

      // Amplitude(s) for diagram number 1060
      FFV1_0( w_sv[3], w_sv[100], w_sv[96], COUPs[1], &amp_sv[0] );
      jamp_sv[54] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[57] -= amp_sv[0];
      jamp_sv[59] += +amp_sv[0];

      // *** DIAGRAM 1061 OF 1240 ***

      // Wavefunction(s) for diagram number 1061
      // (none)

      // Amplitude(s) for diagram number 1061
      VVV1_0( w_sv[96], w_sv[1], w_sv[37], COUPs[0], &amp_sv[0] );
      jamp_sv[51] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[53] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[54] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[55] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[57] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[59] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[64] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[70] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1062 OF 1240 ***

      // Wavefunction(s) for diagram number 1062
      // (none)

      // Amplitude(s) for diagram number 1062
      FFV1_0( w_sv[12], w_sv[100], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[54] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[55] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1063 OF 1240 ***

      // Wavefunction(s) for diagram number 1063
      // (none)

      // Amplitude(s) for diagram number 1063
      VVV1_0( w_sv[0], w_sv[67], w_sv[37], COUPs[0], &amp_sv[0] );
      jamp_sv[48] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[49] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[51] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[53] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[57] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[59] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[65] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[71] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1064 OF 1240 ***

      // Wavefunction(s) for diagram number 1064
      // (none)

      // Amplitude(s) for diagram number 1064
      FFV1_0( w_sv[3], w_sv[33], w_sv[76], COUPs[1], &amp_sv[0] );
      jamp_sv[48] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[49] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[51] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[53] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[57] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[59] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[65] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[71] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[33], w_sv[42], COUPs[1], &amp_sv[0] );
      jamp_sv[51] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[53] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[54] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[55] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[57] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[59] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[64] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[70] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[33], w_sv[11], COUPs[1], &amp_sv[0] );
      jamp_sv[48] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[49] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[54] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[55] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[64] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[65] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[70] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[71] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1065 OF 1240 ***

      // Wavefunction(s) for diagram number 1065
      // (none)

      // Amplitude(s) for diagram number 1065
      FFV1_0( w_sv[78], w_sv[102], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[76] -= amp_sv[0];

      // *** DIAGRAM 1066 OF 1240 ***

      // Wavefunction(s) for diagram number 1066
      // (none)

      // Amplitude(s) for diagram number 1066
      FFV1_0( w_sv[53], w_sv[102], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[73] -= amp_sv[0];

      // *** DIAGRAM 1067 OF 1240 ***

      // Wavefunction(s) for diagram number 1067
      // (none)

      // Amplitude(s) for diagram number 1067
      FFV1_0( w_sv[99], w_sv[89], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[82] -= amp_sv[0];

      // *** DIAGRAM 1068 OF 1240 ***

      // Wavefunction(s) for diagram number 1068
      // (none)

      // Amplitude(s) for diagram number 1068
      FFV1_0( w_sv[99], w_sv[44], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[92] -= amp_sv[0];

      // *** DIAGRAM 1069 OF 1240 ***

      // Wavefunction(s) for diagram number 1069
      // (none)

      // Amplitude(s) for diagram number 1069
      FFV1_0( w_sv[53], w_sv[89], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[79] -= amp_sv[0];

      // *** DIAGRAM 1070 OF 1240 ***

      // Wavefunction(s) for diagram number 1070
      // (none)

      // Amplitude(s) for diagram number 1070
      FFV1_0( w_sv[78], w_sv[44], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[90] -= amp_sv[0];

      // *** DIAGRAM 1071 OF 1240 ***

      // Wavefunction(s) for diagram number 1071
      // (none)

      // Amplitude(s) for diagram number 1071
      FFV1_0( w_sv[60], w_sv[102], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[74] -= amp_sv[0];

      // *** DIAGRAM 1072 OF 1240 ***

      // Wavefunction(s) for diagram number 1072
      // (none)

      // Amplitude(s) for diagram number 1072
      FFV1_0( w_sv[28], w_sv[102], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[72] -= amp_sv[0];

      // *** DIAGRAM 1073 OF 1240 ***

      // Wavefunction(s) for diagram number 1073
      // (none)

      // Amplitude(s) for diagram number 1073
      FFV1_0( w_sv[62], w_sv[89], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[80] -= amp_sv[0];

      // *** DIAGRAM 1074 OF 1240 ***

      // Wavefunction(s) for diagram number 1074
      // (none)

      // Amplitude(s) for diagram number 1074
      FFV1_0( w_sv[62], w_sv[43], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[86] -= amp_sv[0];

      // *** DIAGRAM 1075 OF 1240 ***

      // Wavefunction(s) for diagram number 1075
      // (none)

      // Amplitude(s) for diagram number 1075
      FFV1_0( w_sv[28], w_sv[89], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[78] -= amp_sv[0];

      // *** DIAGRAM 1076 OF 1240 ***

      // Wavefunction(s) for diagram number 1076
      // (none)

      // Amplitude(s) for diagram number 1076
      FFV1_0( w_sv[60], w_sv[43], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[84] -= amp_sv[0];

      // *** DIAGRAM 1077 OF 1240 ***

      // Wavefunction(s) for diagram number 1077
      // (none)

      // Amplitude(s) for diagram number 1077
      FFV1_0( w_sv[3], w_sv[102], w_sv[68], COUPs[1], &amp_sv[0] );
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[73] -= amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[77] += +amp_sv[0];

      // *** DIAGRAM 1078 OF 1240 ***

      // Wavefunction(s) for diagram number 1078
      // (none)

      // Amplitude(s) for diagram number 1078
      FFV1_0( w_sv[14], w_sv[102], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[72] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[73] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1079 OF 1240 ***

      // Wavefunction(s) for diagram number 1079
      // (none)

      // Amplitude(s) for diagram number 1079
      FFV1_0( w_sv[3], w_sv[89], w_sv[101], COUPs[1], &amp_sv[0] );
      jamp_sv[78] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[81] -= amp_sv[0];
      jamp_sv[83] += +amp_sv[0];

      // *** DIAGRAM 1080 OF 1240 ***

      // Wavefunction(s) for diagram number 1080
      // (none)

      // Amplitude(s) for diagram number 1080
      VVV1_0( w_sv[101], w_sv[1], w_sv[45], COUPs[0], &amp_sv[0] );
      jamp_sv[75] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[77] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[78] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[79] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[81] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[83] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[88] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[94] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1081 OF 1240 ***

      // Wavefunction(s) for diagram number 1081
      // (none)

      // Amplitude(s) for diagram number 1081
      FFV1_0( w_sv[14], w_sv[89], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[78] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[79] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1082 OF 1240 ***

      // Wavefunction(s) for diagram number 1082
      // (none)

      // Amplitude(s) for diagram number 1082
      VVV1_0( w_sv[0], w_sv[68], w_sv[45], COUPs[0], &amp_sv[0] );
      jamp_sv[72] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[73] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[75] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[77] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[81] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[83] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[89] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[95] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1083 OF 1240 ***

      // Wavefunction(s) for diagram number 1083
      // (none)

      // Amplitude(s) for diagram number 1083
      FFV1_0( w_sv[3], w_sv[39], w_sv[10], COUPs[1], &amp_sv[0] );
      jamp_sv[72] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[73] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[75] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[77] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[81] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[83] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[89] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[95] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[39], w_sv[16], COUPs[1], &amp_sv[0] );
      jamp_sv[75] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[77] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[78] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[79] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[81] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[83] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[88] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[94] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[39], w_sv[111], COUPs[1], &amp_sv[0] );
      jamp_sv[72] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[73] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[78] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[79] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[88] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[89] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[94] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[95] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1084 OF 1240 ***

      // Wavefunction(s) for diagram number 1084
      // (none)

      // Amplitude(s) for diagram number 1084
      FFV1_0( w_sv[78], w_sv[113], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[100] -= amp_sv[0];

      // *** DIAGRAM 1085 OF 1240 ***

      // Wavefunction(s) for diagram number 1085
      // (none)

      // Amplitude(s) for diagram number 1085
      FFV1_0( w_sv[7], w_sv[113], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[97] -= amp_sv[0];

      // *** DIAGRAM 1086 OF 1240 ***

      // Wavefunction(s) for diagram number 1086
      // (none)

      // Amplitude(s) for diagram number 1086
      FFV1_0( w_sv[99], w_sv[91], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[106] -= amp_sv[0];

      // *** DIAGRAM 1087 OF 1240 ***

      // Wavefunction(s) for diagram number 1087
      // (none)

      // Amplitude(s) for diagram number 1087
      FFV1_0( w_sv[99], w_sv[50], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[116] -= amp_sv[0];

      // *** DIAGRAM 1088 OF 1240 ***

      // Wavefunction(s) for diagram number 1088
      // (none)

      // Amplitude(s) for diagram number 1088
      FFV1_0( w_sv[7], w_sv[91], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[103] -= amp_sv[0];

      // *** DIAGRAM 1089 OF 1240 ***

      // Wavefunction(s) for diagram number 1089
      // (none)

      // Amplitude(s) for diagram number 1089
      FFV1_0( w_sv[78], w_sv[50], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[114] -= amp_sv[0];

      // *** DIAGRAM 1090 OF 1240 ***

      // Wavefunction(s) for diagram number 1090
      // (none)

      // Amplitude(s) for diagram number 1090
      FFV1_0( w_sv[58], w_sv[113], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[98] -= amp_sv[0];

      // *** DIAGRAM 1091 OF 1240 ***

      // Wavefunction(s) for diagram number 1091
      // (none)

      // Amplitude(s) for diagram number 1091
      FFV1_0( w_sv[25], w_sv[113], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[96] -= amp_sv[0];

      // *** DIAGRAM 1092 OF 1240 ***

      // Wavefunction(s) for diagram number 1092
      // (none)

      // Amplitude(s) for diagram number 1092
      FFV1_0( w_sv[104], w_sv[91], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[104] -= amp_sv[0];

      // *** DIAGRAM 1093 OF 1240 ***

      // Wavefunction(s) for diagram number 1093
      // (none)

      // Amplitude(s) for diagram number 1093
      FFV1_0( w_sv[104], w_sv[49], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[110] -= amp_sv[0];

      // *** DIAGRAM 1094 OF 1240 ***

      // Wavefunction(s) for diagram number 1094
      // (none)

      // Amplitude(s) for diagram number 1094
      FFV1_0( w_sv[25], w_sv[91], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[102] -= amp_sv[0];

      // *** DIAGRAM 1095 OF 1240 ***

      // Wavefunction(s) for diagram number 1095
      // (none)

      // Amplitude(s) for diagram number 1095
      FFV1_0( w_sv[58], w_sv[49], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[108] -= amp_sv[0];

      // *** DIAGRAM 1096 OF 1240 ***

      // Wavefunction(s) for diagram number 1096
      // (none)

      // Amplitude(s) for diagram number 1096
      FFV1_0( w_sv[3], w_sv[113], w_sv[59], COUPs[1], &amp_sv[0] );
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[97] -= amp_sv[0];
      jamp_sv[99] -= amp_sv[0];
      jamp_sv[101] += +amp_sv[0];

      // *** DIAGRAM 1097 OF 1240 ***

      // Wavefunction(s) for diagram number 1097
      // (none)

      // Amplitude(s) for diagram number 1097
      FFV1_0( w_sv[26], w_sv[113], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[96] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[97] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1098 OF 1240 ***

      // Wavefunction(s) for diagram number 1098
      // (none)

      // Amplitude(s) for diagram number 1098
      FFV1_0( w_sv[3], w_sv[91], w_sv[98], COUPs[1], &amp_sv[0] );
      jamp_sv[102] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      jamp_sv[105] -= amp_sv[0];
      jamp_sv[107] += +amp_sv[0];

      // *** DIAGRAM 1099 OF 1240 ***

      // Wavefunction(s) for diagram number 1099
      // (none)

      // Amplitude(s) for diagram number 1099
      VVV1_0( w_sv[98], w_sv[1], w_sv[51], COUPs[0], &amp_sv[0] );
      jamp_sv[99] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[101] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[102] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[103] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[105] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[107] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[112] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[118] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1100 OF 1240 ***

      // Wavefunction(s) for diagram number 1100
      // (none)

      // Amplitude(s) for diagram number 1100
      FFV1_0( w_sv[26], w_sv[91], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[102] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[103] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1101 OF 1240 ***

      // Wavefunction(s) for diagram number 1101
      // (none)

      // Amplitude(s) for diagram number 1101
      VVV1_0( w_sv[0], w_sv[59], w_sv[51], COUPs[0], &amp_sv[0] );
      jamp_sv[96] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[97] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[99] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[101] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[105] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[107] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[113] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[119] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1102 OF 1240 ***

      // Wavefunction(s) for diagram number 1102
      // (none)

      // Amplitude(s) for diagram number 1102
      FFV1_0( w_sv[3], w_sv[47], w_sv[97], COUPs[1], &amp_sv[0] );
      jamp_sv[96] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[97] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[99] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[101] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[105] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[107] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[113] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[119] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[47], w_sv[71], COUPs[1], &amp_sv[0] );
      jamp_sv[99] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[101] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[102] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[103] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[105] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[107] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[112] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[118] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[47], w_sv[21], COUPs[1], &amp_sv[0] );
      jamp_sv[96] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[97] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[102] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[103] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[112] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[113] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[118] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[119] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1103 OF 1240 ***

      // Wavefunction(s) for diagram number 1103
      // (none)

      // Amplitude(s) for diagram number 1103
      FFV1_0( w_sv[99], w_sv[2], w_sv[67], COUPs[1], &amp_sv[0] );
      jamp_sv[40] += +amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[92] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];

      // *** DIAGRAM 1104 OF 1240 ***

      // Wavefunction(s) for diagram number 1104
      // (none)

      // Amplitude(s) for diagram number 1104
      FFV1_0( w_sv[99], w_sv[18], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[92] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[116] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1105 OF 1240 ***

      // Wavefunction(s) for diagram number 1105
      // (none)

      // Amplitude(s) for diagram number 1105
      FFV1_0( w_sv[78], w_sv[2], w_sv[96], COUPs[1], &amp_sv[0] );
      jamp_sv[16] += +amp_sv[0];
      jamp_sv[22] -= amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[114] += +amp_sv[0];

      // *** DIAGRAM 1106 OF 1240 ***

      // Wavefunction(s) for diagram number 1106
      // (none)

      // Amplitude(s) for diagram number 1106
      VVV1_0( w_sv[96], w_sv[1], w_sv[54], COUPs[0], &amp_sv[0] );
      jamp_sv[16] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[22] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[27] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[29] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[40] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[46] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[90] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[114] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1107 OF 1240 ***

      // Wavefunction(s) for diagram number 1107
      // (none)

      // Amplitude(s) for diagram number 1107
      FFV1_0( w_sv[78], w_sv[18], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[90] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[114] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1108 OF 1240 ***

      // Wavefunction(s) for diagram number 1108
      // (none)

      // Amplitude(s) for diagram number 1108
      VVV1_0( w_sv[0], w_sv[67], w_sv[54], COUPs[0], &amp_sv[0] );
      jamp_sv[3] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[5] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[16] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[22] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[40] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[46] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[92] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[116] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1109 OF 1240 ***

      // Wavefunction(s) for diagram number 1109
      // (none)

      // Amplitude(s) for diagram number 1109
      FFV1_0( w_sv[46], w_sv[2], w_sv[76], COUPs[1], &amp_sv[0] );
      jamp_sv[3] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[5] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[16] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[22] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[40] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[46] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[92] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[116] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[46], w_sv[2], w_sv[42], COUPs[1], &amp_sv[0] );
      jamp_sv[16] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[22] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[27] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[29] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[40] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[46] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[90] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[114] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[46], w_sv[2], w_sv[11], COUPs[1], &amp_sv[0] );
      jamp_sv[3] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[5] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[27] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[29] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[90] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[92] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[114] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[116] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1110 OF 1240 ***

      // Wavefunction(s) for diagram number 1110
      // (none)

      // Amplitude(s) for diagram number 1110
      FFV1_0( w_sv[104], w_sv[2], w_sv[68], COUPs[1], &amp_sv[0] );
      jamp_sv[34] += +amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[68] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];

      // *** DIAGRAM 1111 OF 1240 ***

      // Wavefunction(s) for diagram number 1111
      // (none)

      // Amplitude(s) for diagram number 1111
      FFV1_0( w_sv[104], w_sv[15], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[68] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[110] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1112 OF 1240 ***

      // Wavefunction(s) for diagram number 1112
      // (none)

      // Amplitude(s) for diagram number 1112
      FFV1_0( w_sv[58], w_sv[2], w_sv[101], COUPs[1], &amp_sv[0] );
      jamp_sv[10] += +amp_sv[0];
      jamp_sv[20] -= amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[108] += +amp_sv[0];

      // *** DIAGRAM 1113 OF 1240 ***

      // Wavefunction(s) for diagram number 1113
      // (none)

      // Amplitude(s) for diagram number 1113
      VVV1_0( w_sv[101], w_sv[1], w_sv[23], COUPs[0], &amp_sv[0] );
      jamp_sv[10] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[20] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[25] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[28] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[34] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[44] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[66] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[108] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1114 OF 1240 ***

      // Wavefunction(s) for diagram number 1114
      // (none)

      // Amplitude(s) for diagram number 1114
      FFV1_0( w_sv[58], w_sv[15], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[66] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[108] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1115 OF 1240 ***

      // Wavefunction(s) for diagram number 1115
      // (none)

      // Amplitude(s) for diagram number 1115
      VVV1_0( w_sv[0], w_sv[68], w_sv[23], COUPs[0], &amp_sv[0] );
      jamp_sv[1] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[4] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[10] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[20] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[34] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[44] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[68] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[110] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1116 OF 1240 ***

      // Wavefunction(s) for diagram number 1116
      // (none)

      // Amplitude(s) for diagram number 1116
      FFV1_0( w_sv[38], w_sv[2], w_sv[10], COUPs[1], &amp_sv[0] );
      jamp_sv[1] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[4] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[10] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[20] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[34] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[44] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[68] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[110] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[38], w_sv[2], w_sv[16], COUPs[1], &amp_sv[0] );
      jamp_sv[10] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[20] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[25] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[28] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[34] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[44] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[66] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[108] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[38], w_sv[2], w_sv[111], COUPs[1], &amp_sv[0] );
      jamp_sv[1] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[4] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[25] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[28] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[66] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[68] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[108] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[110] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1117 OF 1240 ***

      // Wavefunction(s) for diagram number 1117
      // (none)

      // Amplitude(s) for diagram number 1117
      FFV1_0( w_sv[62], w_sv[2], w_sv[59], COUPs[1], &amp_sv[0] );
      jamp_sv[32] += +amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[62] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];

      // *** DIAGRAM 1118 OF 1240 ***

      // Wavefunction(s) for diagram number 1118
      // (none)

      // Amplitude(s) for diagram number 1118
      FFV1_0( w_sv[62], w_sv[17], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[62] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[86] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1119 OF 1240 ***

      // Wavefunction(s) for diagram number 1119
      // (none)

      // Amplitude(s) for diagram number 1119
      FFV1_0( w_sv[60], w_sv[2], w_sv[98], COUPs[1], &amp_sv[0] );
      jamp_sv[8] += +amp_sv[0];
      jamp_sv[14] -= amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[84] += +amp_sv[0];

      // *** DIAGRAM 1120 OF 1240 ***

      // Wavefunction(s) for diagram number 1120
      // (none)

      // Amplitude(s) for diagram number 1120
      VVV1_0( w_sv[98], w_sv[1], w_sv[20], COUPs[0], &amp_sv[0] );
      jamp_sv[8] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[14] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[24] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[26] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[32] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[38] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[60] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[84] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1121 OF 1240 ***

      // Wavefunction(s) for diagram number 1121
      // (none)

      // Amplitude(s) for diagram number 1121
      FFV1_0( w_sv[60], w_sv[17], w_sv[0], COUPs[1], &amp_sv[0] );
      jamp_sv[60] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[84] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1122 OF 1240 ***

      // Wavefunction(s) for diagram number 1122
      // (none)

      // Amplitude(s) for diagram number 1122
      VVV1_0( w_sv[0], w_sv[59], w_sv[20], COUPs[0], &amp_sv[0] );
      jamp_sv[0] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[2] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[8] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[14] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[32] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[38] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[62] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[86] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1123 OF 1240 ***

      // Wavefunction(s) for diagram number 1123
      // (none)

      // Amplitude(s) for diagram number 1123
      FFV1_0( w_sv[41], w_sv[2], w_sv[97], COUPs[1], &amp_sv[0] );
      jamp_sv[0] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[2] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[8] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[14] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[32] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[38] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[62] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[86] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[41], w_sv[2], w_sv[71], COUPs[1], &amp_sv[0] );
      jamp_sv[8] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[14] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[24] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[26] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[32] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[38] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[60] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[84] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[41], w_sv[2], w_sv[21], COUPs[1], &amp_sv[0] );
      jamp_sv[0] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[2] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[24] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[26] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[60] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[62] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[84] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[86] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1124 OF 1240 ***

      // Wavefunction(s) for diagram number 1124
      VVVV1P0_1( w_sv[0], w_sv[1], w_sv[4], COUPs[2], 0., 0., w_sv[21] );
      VVVV3P0_1( w_sv[0], w_sv[1], w_sv[4], COUPs[2], 0., 0., w_sv[71] );
      VVVV4P0_1( w_sv[0], w_sv[1], w_sv[4], COUPs[2], 0., 0., w_sv[97] );

      // Amplitude(s) for diagram number 1124
      VVVV1_0( w_sv[21], w_sv[8], w_sv[5], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[30] -= amp_sv[0];
      jamp_sv[31] += +amp_sv[0];
      jamp_sv[54] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[91] += +amp_sv[0];
      jamp_sv[93] += +amp_sv[0];
      jamp_sv[95] -= amp_sv[0];
      jamp_sv[114] += +amp_sv[0];
      jamp_sv[115] -= amp_sv[0];
      jamp_sv[117] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];
      VVVV3_0( w_sv[21], w_sv[8], w_sv[5], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[30] -= amp_sv[0];
      jamp_sv[54] += +amp_sv[0];
      jamp_sv[72] -= amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[86] -= amp_sv[0];
      jamp_sv[96] -= amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[110] -= amp_sv[0];
      jamp_sv[114] += +amp_sv[0];
      jamp_sv[115] -= amp_sv[0];
      jamp_sv[117] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];
      VVVV4_0( w_sv[21], w_sv[8], w_sv[5], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[1] += +amp_sv[0];
      jamp_sv[7] -= amp_sv[0];
      jamp_sv[31] -= amp_sv[0];
      jamp_sv[55] += +amp_sv[0];
      jamp_sv[72] -= amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[86] -= amp_sv[0];
      jamp_sv[90] += +amp_sv[0];
      jamp_sv[91] -= amp_sv[0];
      jamp_sv[93] -= amp_sv[0];
      jamp_sv[95] += +amp_sv[0];
      jamp_sv[96] -= amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[110] -= amp_sv[0];
      VVVV1_0( w_sv[71], w_sv[8], w_sv[5], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[25] -= amp_sv[0];
      jamp_sv[30] -= amp_sv[0];
      jamp_sv[31] += +amp_sv[0];
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[49] -= amp_sv[0];
      jamp_sv[91] += +amp_sv[0];
      jamp_sv[92] -= amp_sv[0];
      jamp_sv[93] += +amp_sv[0];
      jamp_sv[94] -= amp_sv[0];
      jamp_sv[115] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];
      jamp_sv[117] -= amp_sv[0];
      jamp_sv[118] += +amp_sv[0];
      VVVV3_0( w_sv[71], w_sv[8], w_sv[5], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[30] -= amp_sv[0];
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      jamp_sv[115] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];
      jamp_sv[117] -= amp_sv[0];
      jamp_sv[118] += +amp_sv[0];
      VVVV4_0( w_sv[71], w_sv[8], w_sv[5], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[7] -= amp_sv[0];
      jamp_sv[25] += +amp_sv[0];
      jamp_sv[31] -= amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[91] -= amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[93] -= amp_sv[0];
      jamp_sv[94] += +amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      VVVV1_0( w_sv[97], w_sv[8], w_sv[5], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[0] -= amp_sv[0];
      jamp_sv[1] += +amp_sv[0];
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[25] -= amp_sv[0];
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[49] -= amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[55] += +amp_sv[0];
      jamp_sv[90] += +amp_sv[0];
      jamp_sv[92] -= amp_sv[0];
      jamp_sv[94] -= amp_sv[0];
      jamp_sv[95] += +amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];
      jamp_sv[118] += +amp_sv[0];
      jamp_sv[119] -= amp_sv[0];
      VVVV3_0( w_sv[97], w_sv[8], w_sv[5], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[0] -= amp_sv[0];
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];
      jamp_sv[118] += +amp_sv[0];
      jamp_sv[119] -= amp_sv[0];
      VVVV4_0( w_sv[97], w_sv[8], w_sv[5], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[25] += +amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[94] += +amp_sv[0];
      jamp_sv[95] -= amp_sv[0];
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];

      // *** DIAGRAM 1125 OF 1240 ***

      // Wavefunction(s) for diagram number 1125
      VVV1P0_1( w_sv[21], w_sv[5], COUPs[0], 0., 0., w_sv[59] );
      VVV1P0_1( w_sv[71], w_sv[5], COUPs[0], 0., 0., w_sv[20] );
      VVV1P0_1( w_sv[97], w_sv[5], COUPs[0], 0., 0., w_sv[60] );

      // Amplitude(s) for diagram number 1125
      VVV1_0( w_sv[8], w_sv[6], w_sv[59], COUPs[0], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[30] -= amp_sv[0];
      jamp_sv[54] += +amp_sv[0];
      jamp_sv[72] -= amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[86] -= amp_sv[0];
      jamp_sv[96] -= amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[110] -= amp_sv[0];
      jamp_sv[114] += +amp_sv[0];
      jamp_sv[115] -= amp_sv[0];
      jamp_sv[117] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];
      VVV1_0( w_sv[8], w_sv[6], w_sv[20], COUPs[0], &amp_sv[0] );
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[30] -= amp_sv[0];
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      jamp_sv[115] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];
      jamp_sv[117] -= amp_sv[0];
      jamp_sv[118] += +amp_sv[0];
      VVV1_0( w_sv[8], w_sv[6], w_sv[60], COUPs[0], &amp_sv[0] );
      jamp_sv[0] -= amp_sv[0];
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];
      jamp_sv[118] += +amp_sv[0];
      jamp_sv[119] -= amp_sv[0];

      // *** DIAGRAM 1126 OF 1240 ***

      // Wavefunction(s) for diagram number 1126
      VVV1P0_1( w_sv[21], w_sv[6], COUPs[0], 0., 0., w_sv[17] );
      VVV1P0_1( w_sv[71], w_sv[6], COUPs[0], 0., 0., w_sv[98] );
      VVV1P0_1( w_sv[97], w_sv[6], COUPs[0], 0., 0., w_sv[111] );

      // Amplitude(s) for diagram number 1126
      VVV1_0( w_sv[8], w_sv[5], w_sv[17], COUPs[0], &amp_sv[0] );
      jamp_sv[1] += +amp_sv[0];
      jamp_sv[7] -= amp_sv[0];
      jamp_sv[31] -= amp_sv[0];
      jamp_sv[55] += +amp_sv[0];
      jamp_sv[72] -= amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[86] -= amp_sv[0];
      jamp_sv[90] += +amp_sv[0];
      jamp_sv[91] -= amp_sv[0];
      jamp_sv[93] -= amp_sv[0];
      jamp_sv[95] += +amp_sv[0];
      jamp_sv[96] -= amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[110] -= amp_sv[0];
      VVV1_0( w_sv[8], w_sv[5], w_sv[98], COUPs[0], &amp_sv[0] );
      jamp_sv[7] -= amp_sv[0];
      jamp_sv[25] += +amp_sv[0];
      jamp_sv[31] -= amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[91] -= amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[93] -= amp_sv[0];
      jamp_sv[94] += +amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      VVV1_0( w_sv[8], w_sv[5], w_sv[111], COUPs[0], &amp_sv[0] );
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[25] += +amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[94] += +amp_sv[0];
      jamp_sv[95] -= amp_sv[0];
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];

      // *** DIAGRAM 1127 OF 1240 ***

      // Wavefunction(s) for diagram number 1127
      // (none)

      // Amplitude(s) for diagram number 1127
      VVV1_0( w_sv[21], w_sv[8], w_sv[29], COUPs[0], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[30] -= amp_sv[0];
      jamp_sv[31] += +amp_sv[0];
      jamp_sv[54] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[91] += +amp_sv[0];
      jamp_sv[93] += +amp_sv[0];
      jamp_sv[95] -= amp_sv[0];
      jamp_sv[114] += +amp_sv[0];
      jamp_sv[115] -= amp_sv[0];
      jamp_sv[117] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];
      VVV1_0( w_sv[71], w_sv[8], w_sv[29], COUPs[0], &amp_sv[0] );
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[25] -= amp_sv[0];
      jamp_sv[30] -= amp_sv[0];
      jamp_sv[31] += +amp_sv[0];
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[49] -= amp_sv[0];
      jamp_sv[91] += +amp_sv[0];
      jamp_sv[92] -= amp_sv[0];
      jamp_sv[93] += +amp_sv[0];
      jamp_sv[94] -= amp_sv[0];
      jamp_sv[115] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];
      jamp_sv[117] -= amp_sv[0];
      jamp_sv[118] += +amp_sv[0];
      VVV1_0( w_sv[97], w_sv[8], w_sv[29], COUPs[0], &amp_sv[0] );
      jamp_sv[0] -= amp_sv[0];
      jamp_sv[1] += +amp_sv[0];
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[25] -= amp_sv[0];
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[49] -= amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[55] += +amp_sv[0];
      jamp_sv[90] += +amp_sv[0];
      jamp_sv[92] -= amp_sv[0];
      jamp_sv[94] -= amp_sv[0];
      jamp_sv[95] += +amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];
      jamp_sv[118] += +amp_sv[0];
      jamp_sv[119] -= amp_sv[0];

      // *** DIAGRAM 1128 OF 1240 ***

      // Wavefunction(s) for diagram number 1128
      FFV1_2( w_sv[3], w_sv[21], COUPs[1], cIPD[0], cIPD[1], w_sv[16] );
      FFV1_2( w_sv[3], w_sv[71], COUPs[1], cIPD[0], cIPD[1], w_sv[10] );
      FFV1_2( w_sv[3], w_sv[97], COUPs[1], cIPD[0], cIPD[1], w_sv[68] );

      // Amplitude(s) for diagram number 1128
      FFV1_0( w_sv[16], w_sv[39], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[90] += +amp_sv[0];
      jamp_sv[91] -= amp_sv[0];
      jamp_sv[93] -= amp_sv[0];
      jamp_sv[95] += +amp_sv[0];
      FFV1_0( w_sv[10], w_sv[39], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[91] -= amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[93] -= amp_sv[0];
      jamp_sv[94] += +amp_sv[0];
      FFV1_0( w_sv[68], w_sv[39], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[94] += +amp_sv[0];
      jamp_sv[95] -= amp_sv[0];

      // *** DIAGRAM 1129 OF 1240 ***

      // Wavefunction(s) for diagram number 1129
      // (none)

      // Amplitude(s) for diagram number 1129
      FFV1_0( w_sv[3], w_sv[39], w_sv[17], COUPs[1], &amp_sv[0] );
      jamp_sv[72] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[74] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[80] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[86] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[90] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[91] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[93] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[95] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[39], w_sv[98], COUPs[1], &amp_sv[0] );
      jamp_sv[74] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[78] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[80] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[84] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[91] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[92] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[93] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[94] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[39], w_sv[111], COUPs[1], &amp_sv[0] );
      jamp_sv[72] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[78] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[84] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[86] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[90] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[92] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[94] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[95] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1130 OF 1240 ***

      // Wavefunction(s) for diagram number 1130
      // (none)

      // Amplitude(s) for diagram number 1130
      FFV1_0( w_sv[41], w_sv[39], w_sv[21], COUPs[1], &amp_sv[0] );
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[74] -= amp_sv[0];
      jamp_sv[80] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      FFV1_0( w_sv[41], w_sv[39], w_sv[71], COUPs[1], &amp_sv[0] );
      jamp_sv[74] -= amp_sv[0];
      jamp_sv[78] += +amp_sv[0];
      jamp_sv[80] -= amp_sv[0];
      jamp_sv[84] += +amp_sv[0];
      FFV1_0( w_sv[41], w_sv[39], w_sv[97], COUPs[1], &amp_sv[0] );
      jamp_sv[72] -= amp_sv[0];
      jamp_sv[78] += +amp_sv[0];
      jamp_sv[84] += +amp_sv[0];
      jamp_sv[86] -= amp_sv[0];

      // *** DIAGRAM 1131 OF 1240 ***

      // Wavefunction(s) for diagram number 1131
      // (none)

      // Amplitude(s) for diagram number 1131
      FFV1_0( w_sv[16], w_sv[47], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[114] += +amp_sv[0];
      jamp_sv[115] -= amp_sv[0];
      jamp_sv[117] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];
      FFV1_0( w_sv[10], w_sv[47], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[115] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];
      jamp_sv[117] -= amp_sv[0];
      jamp_sv[118] += +amp_sv[0];
      FFV1_0( w_sv[68], w_sv[47], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[114] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];
      jamp_sv[118] += +amp_sv[0];
      jamp_sv[119] -= amp_sv[0];

      // *** DIAGRAM 1132 OF 1240 ***

      // Wavefunction(s) for diagram number 1132
      // (none)

      // Amplitude(s) for diagram number 1132
      FFV1_0( w_sv[3], w_sv[47], w_sv[59], COUPs[1], &amp_sv[0] );
      jamp_sv[96] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[98] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[104] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[110] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[114] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[115] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[117] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[119] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[47], w_sv[20], COUPs[1], &amp_sv[0] );
      jamp_sv[98] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[102] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[104] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[108] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[115] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[116] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[117] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[118] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[47], w_sv[60], COUPs[1], &amp_sv[0] );
      jamp_sv[96] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[102] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[108] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[110] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[114] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[116] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[118] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[119] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1133 OF 1240 ***

      // Wavefunction(s) for diagram number 1133
      // (none)

      // Amplitude(s) for diagram number 1133
      FFV1_0( w_sv[38], w_sv[47], w_sv[21], COUPs[1], &amp_sv[0] );
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[98] -= amp_sv[0];
      jamp_sv[104] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];
      FFV1_0( w_sv[38], w_sv[47], w_sv[71], COUPs[1], &amp_sv[0] );
      jamp_sv[98] -= amp_sv[0];
      jamp_sv[102] += +amp_sv[0];
      jamp_sv[104] -= amp_sv[0];
      jamp_sv[108] += +amp_sv[0];
      FFV1_0( w_sv[38], w_sv[47], w_sv[97], COUPs[1], &amp_sv[0] );
      jamp_sv[96] -= amp_sv[0];
      jamp_sv[102] += +amp_sv[0];
      jamp_sv[108] += +amp_sv[0];
      jamp_sv[110] -= amp_sv[0];

      // *** DIAGRAM 1134 OF 1240 ***

      // Wavefunction(s) for diagram number 1134
      FFV1_1( w_sv[2], w_sv[21], COUPs[1], cIPD[0], cIPD[1], w_sv[23] );
      FFV1_1( w_sv[2], w_sv[71], COUPs[1], cIPD[0], cIPD[1], w_sv[21] );
      FFV1_1( w_sv[2], w_sv[97], COUPs[1], cIPD[0], cIPD[1], w_sv[71] );

      // Amplitude(s) for diagram number 1134
      FFV1_0( w_sv[38], w_sv[23], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[1] += +amp_sv[0];
      jamp_sv[7] -= amp_sv[0];
      jamp_sv[31] -= amp_sv[0];
      jamp_sv[55] += +amp_sv[0];
      FFV1_0( w_sv[38], w_sv[21], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[7] -= amp_sv[0];
      jamp_sv[25] += +amp_sv[0];
      jamp_sv[31] -= amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      FFV1_0( w_sv[38], w_sv[71], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[25] += +amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];

      // *** DIAGRAM 1135 OF 1240 ***

      // Wavefunction(s) for diagram number 1135
      // (none)

      // Amplitude(s) for diagram number 1135
      FFV1_0( w_sv[38], w_sv[2], w_sv[17], COUPs[1], &amp_sv[0] );
      jamp_sv[1] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[7] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[31] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[55] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[96] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[98] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[104] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[110] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[38], w_sv[2], w_sv[98], COUPs[1], &amp_sv[0] );
      jamp_sv[7] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[25] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[31] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[49] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[98] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[102] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[104] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[108] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[38], w_sv[2], w_sv[111], COUPs[1], &amp_sv[0] );
      jamp_sv[1] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[25] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[49] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[55] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[96] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[102] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[108] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[110] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1136 OF 1240 ***

      // Wavefunction(s) for diagram number 1136
      // (none)

      // Amplitude(s) for diagram number 1136
      FFV1_0( w_sv[41], w_sv[23], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[30] -= amp_sv[0];
      jamp_sv[54] += +amp_sv[0];
      FFV1_0( w_sv[41], w_sv[21], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[30] -= amp_sv[0];
      jamp_sv[48] += +amp_sv[0];
      FFV1_0( w_sv[41], w_sv[71], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[0] -= amp_sv[0];
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[54] -= amp_sv[0];

      // *** DIAGRAM 1137 OF 1240 ***

      // Wavefunction(s) for diagram number 1137
      // (none)

      // Amplitude(s) for diagram number 1137
      FFV1_0( w_sv[41], w_sv[2], w_sv[59], COUPs[1], &amp_sv[0] );
      jamp_sv[0] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[6] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[30] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[54] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[72] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[74] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[80] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[86] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[41], w_sv[2], w_sv[20], COUPs[1], &amp_sv[0] );
      jamp_sv[6] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[24] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[30] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[48] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[74] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[78] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[80] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[84] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[41], w_sv[2], w_sv[60], COUPs[1], &amp_sv[0] );
      jamp_sv[0] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[24] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[48] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[54] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[72] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[78] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[84] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[86] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1138 OF 1240 ***

      // Wavefunction(s) for diagram number 1138
      // (none)

      // Amplitude(s) for diagram number 1138
      FFV1_0( w_sv[3], w_sv[23], w_sv[29], COUPs[1], &amp_sv[0] );
      jamp_sv[0] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[1] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[6] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[7] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[30] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[31] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[54] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[55] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[21], w_sv[29], COUPs[1], &amp_sv[0] );
      jamp_sv[6] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[7] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[24] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[25] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[30] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[31] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[48] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[49] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[71], w_sv[29], COUPs[1], &amp_sv[0] );
      jamp_sv[0] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[1] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[24] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[25] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[48] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[49] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[54] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[55] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1139 OF 1240 ***

      // Wavefunction(s) for diagram number 1139
      // (none)

      // Amplitude(s) for diagram number 1139
      FFV1_0( w_sv[16], w_sv[2], w_sv[29], COUPs[1], &amp_sv[0] );
      jamp_sv[90] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[91] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[93] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[95] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[114] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[115] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[117] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[119] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[10], w_sv[2], w_sv[29], COUPs[1], &amp_sv[0] );
      jamp_sv[91] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[92] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[93] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[94] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[115] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[116] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[117] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[118] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[68], w_sv[2], w_sv[29], COUPs[1], &amp_sv[0] );
      jamp_sv[90] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[92] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[94] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[95] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[114] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[116] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[118] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[119] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1140 OF 1240 ***

      // Wavefunction(s) for diagram number 1140
      VVVV1P0_1( w_sv[0], w_sv[1], w_sv[5], COUPs[2], 0., 0., w_sv[68] );
      VVVV3P0_1( w_sv[0], w_sv[1], w_sv[5], COUPs[2], 0., 0., w_sv[29] );
      VVVV4P0_1( w_sv[0], w_sv[1], w_sv[5], COUPs[2], 0., 0., w_sv[10] );

      // Amplitude(s) for diagram number 1140
      VVVV1_0( w_sv[68], w_sv[8], w_sv[4], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[2] += +amp_sv[0];
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[36] -= amp_sv[0];
      jamp_sv[37] += +amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[67] += +amp_sv[0];
      jamp_sv[69] += +amp_sv[0];
      jamp_sv[71] -= amp_sv[0];
      jamp_sv[78] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[108] += +amp_sv[0];
      jamp_sv[109] -= amp_sv[0];
      jamp_sv[111] -= amp_sv[0];
      jamp_sv[113] += +amp_sv[0];
      VVVV3_0( w_sv[68], w_sv[8], w_sv[4], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[2] += +amp_sv[0];
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[36] -= amp_sv[0];
      jamp_sv[48] -= amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[62] -= amp_sv[0];
      jamp_sv[78] += +amp_sv[0];
      jamp_sv[97] -= amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      jamp_sv[108] += +amp_sv[0];
      jamp_sv[109] -= amp_sv[0];
      jamp_sv[111] -= amp_sv[0];
      jamp_sv[113] += +amp_sv[0];
      jamp_sv[116] -= amp_sv[0];
      VVVV4_0( w_sv[68], w_sv[8], w_sv[4], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[3] += +amp_sv[0];
      jamp_sv[13] -= amp_sv[0];
      jamp_sv[37] -= amp_sv[0];
      jamp_sv[48] -= amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[62] -= amp_sv[0];
      jamp_sv[66] += +amp_sv[0];
      jamp_sv[67] -= amp_sv[0];
      jamp_sv[69] -= amp_sv[0];
      jamp_sv[71] += +amp_sv[0];
      jamp_sv[79] += +amp_sv[0];
      jamp_sv[97] -= amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      jamp_sv[116] -= amp_sv[0];
      VVVV1_0( w_sv[29], w_sv[8], w_sv[4], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[27] -= amp_sv[0];
      jamp_sv[36] -= amp_sv[0];
      jamp_sv[37] += +amp_sv[0];
      jamp_sv[67] += +amp_sv[0];
      jamp_sv[68] -= amp_sv[0];
      jamp_sv[69] += +amp_sv[0];
      jamp_sv[70] -= amp_sv[0];
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[73] -= amp_sv[0];
      jamp_sv[109] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];
      jamp_sv[111] -= amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      VVVV3_0( w_sv[29], w_sv[8], w_sv[4], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[36] -= amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      jamp_sv[109] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];
      jamp_sv[111] -= amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      VVVV4_0( w_sv[29], w_sv[8], w_sv[4], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[13] -= amp_sv[0];
      jamp_sv[27] += +amp_sv[0];
      jamp_sv[37] -= amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[67] -= amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[69] -= amp_sv[0];
      jamp_sv[70] += +amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      VVVV1_0( w_sv[10], w_sv[8], w_sv[4], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[3] += +amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[27] -= amp_sv[0];
      jamp_sv[66] += +amp_sv[0];
      jamp_sv[68] -= amp_sv[0];
      jamp_sv[70] -= amp_sv[0];
      jamp_sv[71] += +amp_sv[0];
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[73] -= amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[79] += +amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      jamp_sv[113] -= amp_sv[0];
      VVVV3_0( w_sv[10], w_sv[8], w_sv[4], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[97] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      jamp_sv[113] -= amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];
      VVVV4_0( w_sv[10], w_sv[8], w_sv[4], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[27] += +amp_sv[0];
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[70] += +amp_sv[0];
      jamp_sv[71] -= amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[97] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];

      // *** DIAGRAM 1141 OF 1240 ***

      // Wavefunction(s) for diagram number 1141
      VVV1P0_1( w_sv[68], w_sv[4], COUPs[0], 0., 0., w_sv[16] );
      VVV1P0_1( w_sv[29], w_sv[4], COUPs[0], 0., 0., w_sv[71] );
      VVV1P0_1( w_sv[10], w_sv[4], COUPs[0], 0., 0., w_sv[21] );

      // Amplitude(s) for diagram number 1141
      VVV1_0( w_sv[8], w_sv[6], w_sv[16], COUPs[0], &amp_sv[0] );
      jamp_sv[2] += +amp_sv[0];
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[36] -= amp_sv[0];
      jamp_sv[48] -= amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[62] -= amp_sv[0];
      jamp_sv[78] += +amp_sv[0];
      jamp_sv[97] -= amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      jamp_sv[108] += +amp_sv[0];
      jamp_sv[109] -= amp_sv[0];
      jamp_sv[111] -= amp_sv[0];
      jamp_sv[113] += +amp_sv[0];
      jamp_sv[116] -= amp_sv[0];
      VVV1_0( w_sv[8], w_sv[6], w_sv[71], COUPs[0], &amp_sv[0] );
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[36] -= amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      jamp_sv[109] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];
      jamp_sv[111] -= amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      VVV1_0( w_sv[8], w_sv[6], w_sv[21], COUPs[0], &amp_sv[0] );
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[97] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      jamp_sv[113] -= amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];

      // *** DIAGRAM 1142 OF 1240 ***

      // Wavefunction(s) for diagram number 1142
      VVV1P0_1( w_sv[68], w_sv[6], COUPs[0], 0., 0., w_sv[23] );
      VVV1P0_1( w_sv[29], w_sv[6], COUPs[0], 0., 0., w_sv[60] );
      VVV1P0_1( w_sv[10], w_sv[6], COUPs[0], 0., 0., w_sv[20] );

      // Amplitude(s) for diagram number 1142
      VVV1_0( w_sv[8], w_sv[4], w_sv[23], COUPs[0], &amp_sv[0] );
      jamp_sv[3] += +amp_sv[0];
      jamp_sv[13] -= amp_sv[0];
      jamp_sv[37] -= amp_sv[0];
      jamp_sv[48] -= amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[62] -= amp_sv[0];
      jamp_sv[66] += +amp_sv[0];
      jamp_sv[67] -= amp_sv[0];
      jamp_sv[69] -= amp_sv[0];
      jamp_sv[71] += +amp_sv[0];
      jamp_sv[79] += +amp_sv[0];
      jamp_sv[97] -= amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      jamp_sv[116] -= amp_sv[0];
      VVV1_0( w_sv[8], w_sv[4], w_sv[60], COUPs[0], &amp_sv[0] );
      jamp_sv[13] -= amp_sv[0];
      jamp_sv[27] += +amp_sv[0];
      jamp_sv[37] -= amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[67] -= amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[69] -= amp_sv[0];
      jamp_sv[70] += +amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      VVV1_0( w_sv[8], w_sv[4], w_sv[20], COUPs[0], &amp_sv[0] );
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[27] += +amp_sv[0];
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[70] += +amp_sv[0];
      jamp_sv[71] -= amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[97] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];

      // *** DIAGRAM 1143 OF 1240 ***

      // Wavefunction(s) for diagram number 1143
      // (none)

      // Amplitude(s) for diagram number 1143
      VVV1_0( w_sv[68], w_sv[8], w_sv[27], COUPs[0], &amp_sv[0] );
      jamp_sv[2] += +amp_sv[0];
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[36] -= amp_sv[0];
      jamp_sv[37] += +amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[67] += +amp_sv[0];
      jamp_sv[69] += +amp_sv[0];
      jamp_sv[71] -= amp_sv[0];
      jamp_sv[78] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[108] += +amp_sv[0];
      jamp_sv[109] -= amp_sv[0];
      jamp_sv[111] -= amp_sv[0];
      jamp_sv[113] += +amp_sv[0];
      VVV1_0( w_sv[29], w_sv[8], w_sv[27], COUPs[0], &amp_sv[0] );
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[27] -= amp_sv[0];
      jamp_sv[36] -= amp_sv[0];
      jamp_sv[37] += +amp_sv[0];
      jamp_sv[67] += +amp_sv[0];
      jamp_sv[68] -= amp_sv[0];
      jamp_sv[69] += +amp_sv[0];
      jamp_sv[70] -= amp_sv[0];
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[73] -= amp_sv[0];
      jamp_sv[109] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];
      jamp_sv[111] -= amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      VVV1_0( w_sv[10], w_sv[8], w_sv[27], COUPs[0], &amp_sv[0] );
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[3] += +amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[27] -= amp_sv[0];
      jamp_sv[66] += +amp_sv[0];
      jamp_sv[68] -= amp_sv[0];
      jamp_sv[70] -= amp_sv[0];
      jamp_sv[71] += +amp_sv[0];
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[73] -= amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[79] += +amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      jamp_sv[113] -= amp_sv[0];

      // *** DIAGRAM 1144 OF 1240 ***

      // Wavefunction(s) for diagram number 1144
      FFV1_2( w_sv[3], w_sv[68], COUPs[1], cIPD[0], cIPD[1], w_sv[59] );
      FFV1_2( w_sv[3], w_sv[29], COUPs[1], cIPD[0], cIPD[1], w_sv[111] );
      FFV1_2( w_sv[3], w_sv[10], COUPs[1], cIPD[0], cIPD[1], w_sv[98] );

      // Amplitude(s) for diagram number 1144
      FFV1_0( w_sv[59], w_sv[33], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[66] += +amp_sv[0];
      jamp_sv[67] -= amp_sv[0];
      jamp_sv[69] -= amp_sv[0];
      jamp_sv[71] += +amp_sv[0];
      FFV1_0( w_sv[111], w_sv[33], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[67] -= amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[69] -= amp_sv[0];
      jamp_sv[70] += +amp_sv[0];
      FFV1_0( w_sv[98], w_sv[33], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[70] += +amp_sv[0];
      jamp_sv[71] -= amp_sv[0];

      // *** DIAGRAM 1145 OF 1240 ***

      // Wavefunction(s) for diagram number 1145
      // (none)

      // Amplitude(s) for diagram number 1145
      FFV1_0( w_sv[3], w_sv[33], w_sv[23], COUPs[1], &amp_sv[0] );
      jamp_sv[48] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[50] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[56] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[62] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[66] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[67] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[69] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[71] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[33], w_sv[60], COUPs[1], &amp_sv[0] );
      jamp_sv[50] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[54] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[56] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[60] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[67] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[68] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[69] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[70] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[33], w_sv[20], COUPs[1], &amp_sv[0] );
      jamp_sv[48] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[54] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[60] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[62] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[66] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[68] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[70] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[71] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1146 OF 1240 ***

      // Wavefunction(s) for diagram number 1146
      // (none)

      // Amplitude(s) for diagram number 1146
      FFV1_0( w_sv[41], w_sv[33], w_sv[68], COUPs[1], &amp_sv[0] );
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[50] -= amp_sv[0];
      jamp_sv[56] -= amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      FFV1_0( w_sv[41], w_sv[33], w_sv[29], COUPs[1], &amp_sv[0] );
      jamp_sv[50] -= amp_sv[0];
      jamp_sv[54] += +amp_sv[0];
      jamp_sv[56] -= amp_sv[0];
      jamp_sv[60] += +amp_sv[0];
      FFV1_0( w_sv[41], w_sv[33], w_sv[10], COUPs[1], &amp_sv[0] );
      jamp_sv[48] -= amp_sv[0];
      jamp_sv[54] += +amp_sv[0];
      jamp_sv[60] += +amp_sv[0];
      jamp_sv[62] -= amp_sv[0];

      // *** DIAGRAM 1147 OF 1240 ***

      // Wavefunction(s) for diagram number 1147
      // (none)

      // Amplitude(s) for diagram number 1147
      FFV1_0( w_sv[59], w_sv[47], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[108] += +amp_sv[0];
      jamp_sv[109] -= amp_sv[0];
      jamp_sv[111] -= amp_sv[0];
      jamp_sv[113] += +amp_sv[0];
      FFV1_0( w_sv[111], w_sv[47], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[109] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];
      jamp_sv[111] -= amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      FFV1_0( w_sv[98], w_sv[47], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[108] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      jamp_sv[113] -= amp_sv[0];

      // *** DIAGRAM 1148 OF 1240 ***

      // Wavefunction(s) for diagram number 1148
      // (none)

      // Amplitude(s) for diagram number 1148
      FFV1_0( w_sv[3], w_sv[47], w_sv[16], COUPs[1], &amp_sv[0] );
      jamp_sv[97] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[100] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[106] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[108] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[109] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[111] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[113] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[116] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[47], w_sv[71], COUPs[1], &amp_sv[0] );
      jamp_sv[100] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[103] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[106] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[109] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[110] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[111] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[112] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[114] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[47], w_sv[21], COUPs[1], &amp_sv[0] );
      jamp_sv[97] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[103] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[108] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[110] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[112] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[113] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[114] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[116] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1149 OF 1240 ***

      // Wavefunction(s) for diagram number 1149
      // (none)

      // Amplitude(s) for diagram number 1149
      FFV1_0( w_sv[46], w_sv[47], w_sv[68], COUPs[1], &amp_sv[0] );
      jamp_sv[97] += +amp_sv[0];
      jamp_sv[100] -= amp_sv[0];
      jamp_sv[106] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];
      FFV1_0( w_sv[46], w_sv[47], w_sv[29], COUPs[1], &amp_sv[0] );
      jamp_sv[100] -= amp_sv[0];
      jamp_sv[103] += +amp_sv[0];
      jamp_sv[106] -= amp_sv[0];
      jamp_sv[114] += +amp_sv[0];
      FFV1_0( w_sv[46], w_sv[47], w_sv[10], COUPs[1], &amp_sv[0] );
      jamp_sv[97] -= amp_sv[0];
      jamp_sv[103] += +amp_sv[0];
      jamp_sv[114] += +amp_sv[0];
      jamp_sv[116] -= amp_sv[0];

      // *** DIAGRAM 1150 OF 1240 ***

      // Wavefunction(s) for diagram number 1150
      FFV1_1( w_sv[2], w_sv[68], COUPs[1], cIPD[0], cIPD[1], w_sv[17] );
      FFV1_1( w_sv[2], w_sv[29], COUPs[1], cIPD[0], cIPD[1], w_sv[68] );
      FFV1_1( w_sv[2], w_sv[10], COUPs[1], cIPD[0], cIPD[1], w_sv[29] );

      // Amplitude(s) for diagram number 1150
      FFV1_0( w_sv[46], w_sv[17], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[3] += +amp_sv[0];
      jamp_sv[13] -= amp_sv[0];
      jamp_sv[37] -= amp_sv[0];
      jamp_sv[79] += +amp_sv[0];
      FFV1_0( w_sv[46], w_sv[68], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[13] -= amp_sv[0];
      jamp_sv[27] += +amp_sv[0];
      jamp_sv[37] -= amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      FFV1_0( w_sv[46], w_sv[29], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[27] += +amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];

      // *** DIAGRAM 1151 OF 1240 ***

      // Wavefunction(s) for diagram number 1151
      // (none)

      // Amplitude(s) for diagram number 1151
      FFV1_0( w_sv[46], w_sv[2], w_sv[23], COUPs[1], &amp_sv[0] );
      jamp_sv[3] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[13] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[37] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[79] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[97] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[100] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[106] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[116] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[46], w_sv[2], w_sv[60], COUPs[1], &amp_sv[0] );
      jamp_sv[13] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[27] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[37] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[73] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[100] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[103] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[106] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[114] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[46], w_sv[2], w_sv[20], COUPs[1], &amp_sv[0] );
      jamp_sv[3] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[27] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[73] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[79] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[97] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[103] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[114] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[116] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1152 OF 1240 ***

      // Wavefunction(s) for diagram number 1152
      // (none)

      // Amplitude(s) for diagram number 1152
      FFV1_0( w_sv[41], w_sv[17], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[2] += +amp_sv[0];
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[36] -= amp_sv[0];
      jamp_sv[78] += +amp_sv[0];
      FFV1_0( w_sv[41], w_sv[68], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[36] -= amp_sv[0];
      jamp_sv[72] += +amp_sv[0];
      FFV1_0( w_sv[41], w_sv[29], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[78] -= amp_sv[0];

      // *** DIAGRAM 1153 OF 1240 ***

      // Wavefunction(s) for diagram number 1153
      // (none)

      // Amplitude(s) for diagram number 1153
      FFV1_0( w_sv[41], w_sv[2], w_sv[16], COUPs[1], &amp_sv[0] );
      jamp_sv[2] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[12] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[36] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[48] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[50] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[56] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[62] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[78] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[41], w_sv[2], w_sv[71], COUPs[1], &amp_sv[0] );
      jamp_sv[12] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[26] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[36] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[50] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[54] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[56] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[60] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[72] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[41], w_sv[2], w_sv[21], COUPs[1], &amp_sv[0] );
      jamp_sv[2] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[26] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[48] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[54] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[60] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[62] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[72] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[78] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1154 OF 1240 ***

      // Wavefunction(s) for diagram number 1154
      // (none)

      // Amplitude(s) for diagram number 1154
      FFV1_0( w_sv[3], w_sv[17], w_sv[27], COUPs[1], &amp_sv[0] );
      jamp_sv[2] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[3] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[12] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[13] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[36] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[37] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[78] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[79] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[68], w_sv[27], COUPs[1], &amp_sv[0] );
      jamp_sv[12] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[13] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[26] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[27] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[36] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[37] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[72] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[73] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[29], w_sv[27], COUPs[1], &amp_sv[0] );
      jamp_sv[2] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[3] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[26] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[27] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[72] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[73] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[78] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[79] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1155 OF 1240 ***

      // Wavefunction(s) for diagram number 1155
      // (none)

      // Amplitude(s) for diagram number 1155
      FFV1_0( w_sv[59], w_sv[2], w_sv[27], COUPs[1], &amp_sv[0] );
      jamp_sv[66] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[67] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[69] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[71] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[108] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[109] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[111] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[113] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[111], w_sv[2], w_sv[27], COUPs[1], &amp_sv[0] );
      jamp_sv[67] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[68] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[69] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[70] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[109] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[110] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[111] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[112] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[98], w_sv[2], w_sv[27], COUPs[1], &amp_sv[0] );
      jamp_sv[66] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[68] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[70] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[71] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[108] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[110] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[112] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[113] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1156 OF 1240 ***

      // Wavefunction(s) for diagram number 1156
      VVVV1P0_1( w_sv[0], w_sv[1], w_sv[6], COUPs[2], 0., 0., w_sv[98] );
      VVVV3P0_1( w_sv[0], w_sv[1], w_sv[6], COUPs[2], 0., 0., w_sv[27] );
      VVVV4P0_1( w_sv[0], w_sv[1], w_sv[6], COUPs[2], 0., 0., w_sv[111] );

      // Amplitude(s) for diagram number 1156
      VVVV1_0( w_sv[98], w_sv[8], w_sv[4], w_sv[5], COUPs[2], &amp_sv[0] );
      jamp_sv[4] += +amp_sv[0];
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[19] += +amp_sv[0];
      jamp_sv[42] -= amp_sv[0];
      jamp_sv[43] += +amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[61] += +amp_sv[0];
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[84] += +amp_sv[0];
      jamp_sv[85] -= amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[89] += +amp_sv[0];
      jamp_sv[102] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      VVVV3_0( w_sv[98], w_sv[8], w_sv[4], w_sv[5], COUPs[2], &amp_sv[0] );
      jamp_sv[4] += +amp_sv[0];
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[42] -= amp_sv[0];
      jamp_sv[49] -= amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[68] -= amp_sv[0];
      jamp_sv[73] -= amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[84] += +amp_sv[0];
      jamp_sv[85] -= amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[89] += +amp_sv[0];
      jamp_sv[92] -= amp_sv[0];
      jamp_sv[102] += +amp_sv[0];
      VVVV4_0( w_sv[98], w_sv[8], w_sv[4], w_sv[5], COUPs[2], &amp_sv[0] );
      jamp_sv[5] += +amp_sv[0];
      jamp_sv[19] -= amp_sv[0];
      jamp_sv[43] -= amp_sv[0];
      jamp_sv[49] -= amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[60] += +amp_sv[0];
      jamp_sv[61] -= amp_sv[0];
      jamp_sv[63] -= amp_sv[0];
      jamp_sv[65] += +amp_sv[0];
      jamp_sv[68] -= amp_sv[0];
      jamp_sv[73] -= amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[92] -= amp_sv[0];
      jamp_sv[103] += +amp_sv[0];
      VVVV1_0( w_sv[27], w_sv[8], w_sv[4], w_sv[5], COUPs[2], &amp_sv[0] );
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[19] += +amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[29] -= amp_sv[0];
      jamp_sv[42] -= amp_sv[0];
      jamp_sv[43] += +amp_sv[0];
      jamp_sv[61] += +amp_sv[0];
      jamp_sv[62] -= amp_sv[0];
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[64] -= amp_sv[0];
      jamp_sv[85] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[97] -= amp_sv[0];
      VVVV3_0( w_sv[27], w_sv[8], w_sv[4], w_sv[5], COUPs[2], &amp_sv[0] );
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[42] -= amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[85] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[96] += +amp_sv[0];
      VVVV4_0( w_sv[27], w_sv[8], w_sv[4], w_sv[5], COUPs[2], &amp_sv[0] );
      jamp_sv[19] -= amp_sv[0];
      jamp_sv[29] += +amp_sv[0];
      jamp_sv[43] -= amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[61] -= amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[63] -= amp_sv[0];
      jamp_sv[64] += +amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[97] += +amp_sv[0];
      VVVV1_0( w_sv[111], w_sv[8], w_sv[4], w_sv[5], COUPs[2], &amp_sv[0] );
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[5] += +amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[29] -= amp_sv[0];
      jamp_sv[60] += +amp_sv[0];
      jamp_sv[62] -= amp_sv[0];
      jamp_sv[64] -= amp_sv[0];
      jamp_sv[65] += +amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[89] -= amp_sv[0];
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[97] -= amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[103] += +amp_sv[0];
      VVVV3_0( w_sv[111], w_sv[8], w_sv[4], w_sv[5], COUPs[2], &amp_sv[0] );
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[89] -= amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      VVVV4_0( w_sv[111], w_sv[8], w_sv[4], w_sv[5], COUPs[2], &amp_sv[0] );
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[29] += +amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[64] += +amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[97] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];

      // *** DIAGRAM 1157 OF 1240 ***

      // Wavefunction(s) for diagram number 1157
      VVV1P0_1( w_sv[98], w_sv[4], COUPs[0], 0., 0., w_sv[59] );
      VVV1P0_1( w_sv[27], w_sv[4], COUPs[0], 0., 0., w_sv[29] );
      VVV1P0_1( w_sv[111], w_sv[4], COUPs[0], 0., 0., w_sv[68] );

      // Amplitude(s) for diagram number 1157
      VVV1_0( w_sv[8], w_sv[5], w_sv[59], COUPs[0], &amp_sv[0] );
      jamp_sv[4] += +amp_sv[0];
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[42] -= amp_sv[0];
      jamp_sv[49] -= amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[68] -= amp_sv[0];
      jamp_sv[73] -= amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[84] += +amp_sv[0];
      jamp_sv[85] -= amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[89] += +amp_sv[0];
      jamp_sv[92] -= amp_sv[0];
      jamp_sv[102] += +amp_sv[0];
      VVV1_0( w_sv[8], w_sv[5], w_sv[29], COUPs[0], &amp_sv[0] );
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[42] -= amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[85] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[96] += +amp_sv[0];
      VVV1_0( w_sv[8], w_sv[5], w_sv[68], COUPs[0], &amp_sv[0] );
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[89] -= amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[102] -= amp_sv[0];

      // *** DIAGRAM 1158 OF 1240 ***

      // Wavefunction(s) for diagram number 1158
      VVV1P0_1( w_sv[98], w_sv[5], COUPs[0], 0., 0., w_sv[17] );
      VVV1P0_1( w_sv[27], w_sv[5], COUPs[0], 0., 0., w_sv[21] );
      VVV1P0_1( w_sv[111], w_sv[5], COUPs[0], 0., 0., w_sv[71] );

      // Amplitude(s) for diagram number 1158
      VVV1_0( w_sv[8], w_sv[4], w_sv[17], COUPs[0], &amp_sv[0] );
      jamp_sv[5] += +amp_sv[0];
      jamp_sv[19] -= amp_sv[0];
      jamp_sv[43] -= amp_sv[0];
      jamp_sv[49] -= amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[60] += +amp_sv[0];
      jamp_sv[61] -= amp_sv[0];
      jamp_sv[63] -= amp_sv[0];
      jamp_sv[65] += +amp_sv[0];
      jamp_sv[68] -= amp_sv[0];
      jamp_sv[73] -= amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[92] -= amp_sv[0];
      jamp_sv[103] += +amp_sv[0];
      VVV1_0( w_sv[8], w_sv[4], w_sv[21], COUPs[0], &amp_sv[0] );
      jamp_sv[19] -= amp_sv[0];
      jamp_sv[29] += +amp_sv[0];
      jamp_sv[43] -= amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[61] -= amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[63] -= amp_sv[0];
      jamp_sv[64] += +amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[97] += +amp_sv[0];
      VVV1_0( w_sv[8], w_sv[4], w_sv[71], COUPs[0], &amp_sv[0] );
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[29] += +amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[64] += +amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[97] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];

      // *** DIAGRAM 1159 OF 1240 ***

      // Wavefunction(s) for diagram number 1159
      // (none)

      // Amplitude(s) for diagram number 1159
      VVV1_0( w_sv[98], w_sv[8], w_sv[24], COUPs[0], &amp_sv[0] );
      jamp_sv[4] += +amp_sv[0];
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[19] += +amp_sv[0];
      jamp_sv[42] -= amp_sv[0];
      jamp_sv[43] += +amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[61] += +amp_sv[0];
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[84] += +amp_sv[0];
      jamp_sv[85] -= amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[89] += +amp_sv[0];
      jamp_sv[102] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      VVV1_0( w_sv[27], w_sv[8], w_sv[24], COUPs[0], &amp_sv[0] );
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[19] += +amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[29] -= amp_sv[0];
      jamp_sv[42] -= amp_sv[0];
      jamp_sv[43] += +amp_sv[0];
      jamp_sv[61] += +amp_sv[0];
      jamp_sv[62] -= amp_sv[0];
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[64] -= amp_sv[0];
      jamp_sv[85] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[97] -= amp_sv[0];
      VVV1_0( w_sv[111], w_sv[8], w_sv[24], COUPs[0], &amp_sv[0] );
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[5] += +amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[29] -= amp_sv[0];
      jamp_sv[60] += +amp_sv[0];
      jamp_sv[62] -= amp_sv[0];
      jamp_sv[64] -= amp_sv[0];
      jamp_sv[65] += +amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[89] -= amp_sv[0];
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[97] -= amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[103] += +amp_sv[0];

      // *** DIAGRAM 1160 OF 1240 ***

      // Wavefunction(s) for diagram number 1160
      FFV1_2( w_sv[3], w_sv[98], COUPs[1], cIPD[0], cIPD[1], w_sv[16] );
      FFV1_2( w_sv[3], w_sv[27], COUPs[1], cIPD[0], cIPD[1], w_sv[20] );
      FFV1_2( w_sv[3], w_sv[111], COUPs[1], cIPD[0], cIPD[1], w_sv[60] );

      // Amplitude(s) for diagram number 1160
      FFV1_0( w_sv[16], w_sv[33], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[60] += +amp_sv[0];
      jamp_sv[61] -= amp_sv[0];
      jamp_sv[63] -= amp_sv[0];
      jamp_sv[65] += +amp_sv[0];
      FFV1_0( w_sv[20], w_sv[33], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[61] -= amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[63] -= amp_sv[0];
      jamp_sv[64] += +amp_sv[0];
      FFV1_0( w_sv[60], w_sv[33], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[64] += +amp_sv[0];
      jamp_sv[65] -= amp_sv[0];

      // *** DIAGRAM 1161 OF 1240 ***

      // Wavefunction(s) for diagram number 1161
      // (none)

      // Amplitude(s) for diagram number 1161
      FFV1_0( w_sv[3], w_sv[33], w_sv[17], COUPs[1], &amp_sv[0] );
      jamp_sv[49] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[52] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[58] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[60] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[61] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[63] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[65] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[68] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[33], w_sv[21], COUPs[1], &amp_sv[0] );
      jamp_sv[52] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[55] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[58] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[61] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[62] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[63] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[64] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[66] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[33], w_sv[71], COUPs[1], &amp_sv[0] );
      jamp_sv[49] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[55] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[60] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[62] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[64] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[65] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[66] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[68] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1162 OF 1240 ***

      // Wavefunction(s) for diagram number 1162
      // (none)

      // Amplitude(s) for diagram number 1162
      FFV1_0( w_sv[38], w_sv[33], w_sv[98], COUPs[1], &amp_sv[0] );
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[52] -= amp_sv[0];
      jamp_sv[58] -= amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      FFV1_0( w_sv[38], w_sv[33], w_sv[27], COUPs[1], &amp_sv[0] );
      jamp_sv[52] -= amp_sv[0];
      jamp_sv[55] += +amp_sv[0];
      jamp_sv[58] -= amp_sv[0];
      jamp_sv[66] += +amp_sv[0];
      FFV1_0( w_sv[38], w_sv[33], w_sv[111], COUPs[1], &amp_sv[0] );
      jamp_sv[49] -= amp_sv[0];
      jamp_sv[55] += +amp_sv[0];
      jamp_sv[66] += +amp_sv[0];
      jamp_sv[68] -= amp_sv[0];

      // *** DIAGRAM 1163 OF 1240 ***

      // Wavefunction(s) for diagram number 1163
      // (none)

      // Amplitude(s) for diagram number 1163
      FFV1_0( w_sv[16], w_sv[39], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[84] += +amp_sv[0];
      jamp_sv[85] -= amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[89] += +amp_sv[0];
      FFV1_0( w_sv[20], w_sv[39], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[85] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      FFV1_0( w_sv[60], w_sv[39], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[89] -= amp_sv[0];

      // *** DIAGRAM 1164 OF 1240 ***

      // Wavefunction(s) for diagram number 1164
      // (none)

      // Amplitude(s) for diagram number 1164
      FFV1_0( w_sv[3], w_sv[39], w_sv[59], COUPs[1], &amp_sv[0] );
      jamp_sv[73] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[76] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[82] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[84] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[85] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[87] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[89] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[92] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[39], w_sv[29], COUPs[1], &amp_sv[0] );
      jamp_sv[76] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[79] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[82] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[85] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[86] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[87] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[88] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[90] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[39], w_sv[68], COUPs[1], &amp_sv[0] );
      jamp_sv[73] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[79] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[84] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[86] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[88] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[89] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[90] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[92] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1165 OF 1240 ***

      // Wavefunction(s) for diagram number 1165
      // (none)

      // Amplitude(s) for diagram number 1165
      FFV1_0( w_sv[46], w_sv[39], w_sv[98], COUPs[1], &amp_sv[0] );
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[76] -= amp_sv[0];
      jamp_sv[82] -= amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      FFV1_0( w_sv[46], w_sv[39], w_sv[27], COUPs[1], &amp_sv[0] );
      jamp_sv[76] -= amp_sv[0];
      jamp_sv[79] += +amp_sv[0];
      jamp_sv[82] -= amp_sv[0];
      jamp_sv[90] += +amp_sv[0];
      FFV1_0( w_sv[46], w_sv[39], w_sv[111], COUPs[1], &amp_sv[0] );
      jamp_sv[73] -= amp_sv[0];
      jamp_sv[79] += +amp_sv[0];
      jamp_sv[90] += +amp_sv[0];
      jamp_sv[92] -= amp_sv[0];

      // *** DIAGRAM 1166 OF 1240 ***

      // Wavefunction(s) for diagram number 1166
      FFV1_1( w_sv[2], w_sv[98], COUPs[1], cIPD[0], cIPD[1], w_sv[23] );
      FFV1_1( w_sv[2], w_sv[27], COUPs[1], cIPD[0], cIPD[1], w_sv[98] );
      FFV1_1( w_sv[2], w_sv[111], COUPs[1], cIPD[0], cIPD[1], w_sv[27] );

      // Amplitude(s) for diagram number 1166
      FFV1_0( w_sv[46], w_sv[23], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[5] += +amp_sv[0];
      jamp_sv[19] -= amp_sv[0];
      jamp_sv[43] -= amp_sv[0];
      jamp_sv[103] += +amp_sv[0];
      FFV1_0( w_sv[46], w_sv[98], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[19] -= amp_sv[0];
      jamp_sv[29] += +amp_sv[0];
      jamp_sv[43] -= amp_sv[0];
      jamp_sv[97] += +amp_sv[0];
      FFV1_0( w_sv[46], w_sv[27], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[29] += +amp_sv[0];
      jamp_sv[97] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];

      // *** DIAGRAM 1167 OF 1240 ***

      // Wavefunction(s) for diagram number 1167
      // (none)

      // Amplitude(s) for diagram number 1167
      FFV1_0( w_sv[46], w_sv[2], w_sv[17], COUPs[1], &amp_sv[0] );
      jamp_sv[5] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[19] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[43] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[73] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[76] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[82] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[92] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[103] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[46], w_sv[2], w_sv[21], COUPs[1], &amp_sv[0] );
      jamp_sv[19] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[29] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[43] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[76] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[79] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[82] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[90] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[97] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[46], w_sv[2], w_sv[71], COUPs[1], &amp_sv[0] );
      jamp_sv[5] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[29] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[73] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[79] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[90] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[92] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[97] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[103] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1168 OF 1240 ***

      // Wavefunction(s) for diagram number 1168
      // (none)

      // Amplitude(s) for diagram number 1168
      FFV1_0( w_sv[38], w_sv[23], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[4] += +amp_sv[0];
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[42] -= amp_sv[0];
      jamp_sv[102] += +amp_sv[0];
      FFV1_0( w_sv[38], w_sv[98], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[42] -= amp_sv[0];
      jamp_sv[96] += +amp_sv[0];
      FFV1_0( w_sv[38], w_sv[27], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[102] -= amp_sv[0];

      // *** DIAGRAM 1169 OF 1240 ***

      // Wavefunction(s) for diagram number 1169
      // (none)

      // Amplitude(s) for diagram number 1169
      FFV1_0( w_sv[38], w_sv[2], w_sv[59], COUPs[1], &amp_sv[0] );
      jamp_sv[4] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[18] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[42] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[49] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[52] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[58] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[68] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[102] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[38], w_sv[2], w_sv[29], COUPs[1], &amp_sv[0] );
      jamp_sv[18] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[28] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[42] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[52] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[55] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[58] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[66] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[96] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[38], w_sv[2], w_sv[68], COUPs[1], &amp_sv[0] );
      jamp_sv[4] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[28] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[49] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[55] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[66] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[68] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[96] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[102] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1170 OF 1240 ***

      // Wavefunction(s) for diagram number 1170
      // (none)

      // Amplitude(s) for diagram number 1170
      FFV1_0( w_sv[3], w_sv[23], w_sv[24], COUPs[1], &amp_sv[0] );
      jamp_sv[4] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[5] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[18] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[19] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[42] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[43] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[102] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[103] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[98], w_sv[24], COUPs[1], &amp_sv[0] );
      jamp_sv[18] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[19] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[28] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[29] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[42] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[43] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[96] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[97] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[27], w_sv[24], COUPs[1], &amp_sv[0] );
      jamp_sv[4] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[5] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[28] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[29] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[96] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[97] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[102] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[103] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1171 OF 1240 ***

      // Wavefunction(s) for diagram number 1171
      // (none)

      // Amplitude(s) for diagram number 1171
      FFV1_0( w_sv[16], w_sv[2], w_sv[24], COUPs[1], &amp_sv[0] );
      jamp_sv[60] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[61] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[63] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[65] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[84] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[85] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[87] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[89] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[20], w_sv[2], w_sv[24], COUPs[1], &amp_sv[0] );
      jamp_sv[61] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[62] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[63] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[64] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[85] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[86] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[87] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[88] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[60], w_sv[2], w_sv[24], COUPs[1], &amp_sv[0] );
      jamp_sv[60] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[62] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[64] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[65] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[84] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[86] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[88] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[89] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1172 OF 1240 ***

      // Wavefunction(s) for diagram number 1172
      VVVV1P0_1( w_sv[0], w_sv[4], w_sv[5], COUPs[2], 0., 0., w_sv[60] );
      VVVV3P0_1( w_sv[0], w_sv[4], w_sv[5], COUPs[2], 0., 0., w_sv[24] );
      VVVV4P0_1( w_sv[0], w_sv[4], w_sv[5], COUPs[2], 0., 0., w_sv[20] );
      FFV1_2( w_sv[3], w_sv[60], COUPs[1], cIPD[0], cIPD[1], w_sv[16] );
      FFV1_2( w_sv[3], w_sv[24], COUPs[1], cIPD[0], cIPD[1], w_sv[27] );
      FFV1_2( w_sv[3], w_sv[20], COUPs[1], cIPD[0], cIPD[1], w_sv[98] );

      // Amplitude(s) for diagram number 1172
      FFV1_0( w_sv[16], w_sv[77], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[42] += +amp_sv[0];
      jamp_sv[43] -= amp_sv[0];
      jamp_sv[45] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      FFV1_0( w_sv[27], w_sv[77], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[43] -= amp_sv[0];
      jamp_sv[44] += +amp_sv[0];
      jamp_sv[45] -= amp_sv[0];
      jamp_sv[46] += +amp_sv[0];
      FFV1_0( w_sv[98], w_sv[77], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[42] -= amp_sv[0];
      jamp_sv[44] += +amp_sv[0];
      jamp_sv[46] += +amp_sv[0];
      jamp_sv[47] -= amp_sv[0];

      // *** DIAGRAM 1173 OF 1240 ***

      // Wavefunction(s) for diagram number 1173
      VVV1P0_1( w_sv[60], w_sv[6], COUPs[0], 0., 0., w_sv[23] );
      VVV1P0_1( w_sv[24], w_sv[6], COUPs[0], 0., 0., w_sv[68] );
      VVV1P0_1( w_sv[20], w_sv[6], COUPs[0], 0., 0., w_sv[29] );

      // Amplitude(s) for diagram number 1173
      FFV1_0( w_sv[3], w_sv[77], w_sv[23], COUPs[1], &amp_sv[0] );
      jamp_sv[24] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[26] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[32] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[38] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[42] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[43] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[45] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[47] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[77], w_sv[68], COUPs[1], &amp_sv[0] );
      jamp_sv[26] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[30] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[32] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[36] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[43] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[44] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[45] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[46] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[77], w_sv[29], COUPs[1], &amp_sv[0] );
      jamp_sv[24] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[30] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[36] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[38] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[42] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[44] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[46] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[47] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1174 OF 1240 ***

      // Wavefunction(s) for diagram number 1174
      // (none)

      // Amplitude(s) for diagram number 1174
      FFV1_0( w_sv[41], w_sv[77], w_sv[60], COUPs[1], &amp_sv[0] );
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[26] -= amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[38] += +amp_sv[0];
      FFV1_0( w_sv[41], w_sv[77], w_sv[24], COUPs[1], &amp_sv[0] );
      jamp_sv[26] -= amp_sv[0];
      jamp_sv[30] += +amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[36] += +amp_sv[0];
      FFV1_0( w_sv[41], w_sv[77], w_sv[20], COUPs[1], &amp_sv[0] );
      jamp_sv[24] -= amp_sv[0];
      jamp_sv[30] += +amp_sv[0];
      jamp_sv[36] += +amp_sv[0];
      jamp_sv[38] -= amp_sv[0];

      // *** DIAGRAM 1175 OF 1240 ***

      // Wavefunction(s) for diagram number 1175
      FFV1_1( w_sv[2], w_sv[60], COUPs[1], cIPD[0], cIPD[1], w_sv[59] );
      FFV1_1( w_sv[2], w_sv[24], COUPs[1], cIPD[0], cIPD[1], w_sv[71] );
      FFV1_1( w_sv[2], w_sv[20], COUPs[1], cIPD[0], cIPD[1], w_sv[21] );

      // Amplitude(s) for diagram number 1175
      FFV1_0( w_sv[52], w_sv[59], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[61] -= amp_sv[0];
      jamp_sv[85] += +amp_sv[0];
      FFV1_0( w_sv[52], w_sv[71], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[51] += +amp_sv[0];
      jamp_sv[61] -= amp_sv[0];
      jamp_sv[75] += +amp_sv[0];
      FFV1_0( w_sv[52], w_sv[21], w_sv[6], COUPs[1], &amp_sv[0] );
      jamp_sv[9] -= amp_sv[0];
      jamp_sv[51] += +amp_sv[0];
      jamp_sv[75] += +amp_sv[0];
      jamp_sv[85] -= amp_sv[0];

      // *** DIAGRAM 1176 OF 1240 ***

      // Wavefunction(s) for diagram number 1176
      // (none)

      // Amplitude(s) for diagram number 1176
      FFV1_0( w_sv[52], w_sv[2], w_sv[23], COUPs[1], &amp_sv[0] );
      jamp_sv[9] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[15] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[61] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[85] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[99] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[101] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[112] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[118] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[52], w_sv[2], w_sv[68], COUPs[1], &amp_sv[0] );
      jamp_sv[15] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[51] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[61] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[75] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[101] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[109] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[112] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[115] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[52], w_sv[2], w_sv[29], COUPs[1], &amp_sv[0] );
      jamp_sv[9] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[51] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[75] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[85] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[99] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[109] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[115] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[118] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1177 OF 1240 ***

      // Wavefunction(s) for diagram number 1177
      // (none)

      // Amplitude(s) for diagram number 1177
      FFV1_0( w_sv[52], w_sv[47], w_sv[60], COUPs[1], &amp_sv[0] );
      jamp_sv[99] += +amp_sv[0];
      jamp_sv[101] -= amp_sv[0];
      jamp_sv[112] -= amp_sv[0];
      jamp_sv[118] += +amp_sv[0];
      FFV1_0( w_sv[52], w_sv[47], w_sv[24], COUPs[1], &amp_sv[0] );
      jamp_sv[101] -= amp_sv[0];
      jamp_sv[109] += +amp_sv[0];
      jamp_sv[112] -= amp_sv[0];
      jamp_sv[115] += +amp_sv[0];
      FFV1_0( w_sv[52], w_sv[47], w_sv[20], COUPs[1], &amp_sv[0] );
      jamp_sv[99] -= amp_sv[0];
      jamp_sv[109] += +amp_sv[0];
      jamp_sv[115] += +amp_sv[0];
      jamp_sv[118] -= amp_sv[0];

      // *** DIAGRAM 1178 OF 1240 ***

      // Wavefunction(s) for diagram number 1178
      // (none)

      // Amplitude(s) for diagram number 1178
      FFV1_0( w_sv[3], w_sv[59], w_sv[72], COUPs[1], &amp_sv[0] );
      jamp_sv[8] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[9] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[14] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[15] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[60] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[61] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[84] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[85] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[71], w_sv[72], COUPs[1], &amp_sv[0] );
      jamp_sv[14] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[15] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[50] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[51] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[60] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[61] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[74] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[75] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[21], w_sv[72], COUPs[1], &amp_sv[0] );
      jamp_sv[8] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[9] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[50] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[51] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[74] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[75] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[84] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[85] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1179 OF 1240 ***

      // Wavefunction(s) for diagram number 1179
      // (none)

      // Amplitude(s) for diagram number 1179
      FFV1_0( w_sv[16], w_sv[2], w_sv[72], COUPs[1], &amp_sv[0] );
      jamp_sv[42] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[43] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[45] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[47] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[102] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[103] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[105] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[107] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[27], w_sv[2], w_sv[72], COUPs[1], &amp_sv[0] );
      jamp_sv[43] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[44] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[45] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[46] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[103] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[104] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[105] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[106] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[98], w_sv[2], w_sv[72], COUPs[1], &amp_sv[0] );
      jamp_sv[42] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[44] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[46] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[47] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[102] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[104] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[106] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[107] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1180 OF 1240 ***

      // Wavefunction(s) for diagram number 1180
      // (none)

      // Amplitude(s) for diagram number 1180
      VVV1_0( w_sv[60], w_sv[72], w_sv[8], COUPs[0], &amp_sv[0] );
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[14] += +amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[42] += +amp_sv[0];
      jamp_sv[43] -= amp_sv[0];
      jamp_sv[45] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[60] += +amp_sv[0];
      jamp_sv[61] -= amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[85] += +amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[103] += +amp_sv[0];
      jamp_sv[105] += +amp_sv[0];
      jamp_sv[107] -= amp_sv[0];
      VVV1_0( w_sv[24], w_sv[72], w_sv[8], COUPs[0], &amp_sv[0] );
      jamp_sv[14] += +amp_sv[0];
      jamp_sv[15] -= amp_sv[0];
      jamp_sv[43] -= amp_sv[0];
      jamp_sv[44] += +amp_sv[0];
      jamp_sv[45] -= amp_sv[0];
      jamp_sv[46] += +amp_sv[0];
      jamp_sv[50] -= amp_sv[0];
      jamp_sv[51] += +amp_sv[0];
      jamp_sv[60] += +amp_sv[0];
      jamp_sv[61] -= amp_sv[0];
      jamp_sv[74] -= amp_sv[0];
      jamp_sv[75] += +amp_sv[0];
      jamp_sv[103] += +amp_sv[0];
      jamp_sv[104] -= amp_sv[0];
      jamp_sv[105] += +amp_sv[0];
      jamp_sv[106] -= amp_sv[0];
      VVV1_0( w_sv[20], w_sv[72], w_sv[8], COUPs[0], &amp_sv[0] );
      jamp_sv[8] += +amp_sv[0];
      jamp_sv[9] -= amp_sv[0];
      jamp_sv[42] -= amp_sv[0];
      jamp_sv[44] += +amp_sv[0];
      jamp_sv[46] += +amp_sv[0];
      jamp_sv[47] -= amp_sv[0];
      jamp_sv[50] -= amp_sv[0];
      jamp_sv[51] += +amp_sv[0];
      jamp_sv[74] -= amp_sv[0];
      jamp_sv[75] += +amp_sv[0];
      jamp_sv[84] += +amp_sv[0];
      jamp_sv[85] -= amp_sv[0];
      jamp_sv[102] += +amp_sv[0];
      jamp_sv[104] -= amp_sv[0];
      jamp_sv[106] -= amp_sv[0];
      jamp_sv[107] += +amp_sv[0];

      // *** DIAGRAM 1181 OF 1240 ***

      // Wavefunction(s) for diagram number 1181
      // (none)

      // Amplitude(s) for diagram number 1181
      VVVV1_0( w_sv[60], w_sv[1], w_sv[8], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[8] += +amp_sv[0];
      jamp_sv[14] -= amp_sv[0];
      jamp_sv[24] -= amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[32] += +amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[84] += +amp_sv[0];
      jamp_sv[99] -= amp_sv[0];
      jamp_sv[101] += +amp_sv[0];
      jamp_sv[102] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      jamp_sv[105] -= amp_sv[0];
      jamp_sv[107] += +amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      jamp_sv[118] -= amp_sv[0];
      VVVV3_0( w_sv[60], w_sv[1], w_sv[8], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[8] += +amp_sv[0];
      jamp_sv[9] -= amp_sv[0];
      jamp_sv[14] -= amp_sv[0];
      jamp_sv[15] += +amp_sv[0];
      jamp_sv[42] -= amp_sv[0];
      jamp_sv[43] += +amp_sv[0];
      jamp_sv[45] += +amp_sv[0];
      jamp_sv[47] -= amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[61] += +amp_sv[0];
      jamp_sv[84] += +amp_sv[0];
      jamp_sv[85] -= amp_sv[0];
      jamp_sv[102] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      jamp_sv[105] -= amp_sv[0];
      jamp_sv[107] += +amp_sv[0];
      VVVV4_0( w_sv[60], w_sv[1], w_sv[8], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[9] -= amp_sv[0];
      jamp_sv[15] += +amp_sv[0];
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[26] -= amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[38] += +amp_sv[0];
      jamp_sv[42] -= amp_sv[0];
      jamp_sv[43] += +amp_sv[0];
      jamp_sv[45] += +amp_sv[0];
      jamp_sv[47] -= amp_sv[0];
      jamp_sv[61] += +amp_sv[0];
      jamp_sv[85] -= amp_sv[0];
      jamp_sv[99] += +amp_sv[0];
      jamp_sv[101] -= amp_sv[0];
      jamp_sv[112] -= amp_sv[0];
      jamp_sv[118] += +amp_sv[0];
      VVVV1_0( w_sv[24], w_sv[1], w_sv[8], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[14] -= amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[30] -= amp_sv[0];
      jamp_sv[32] += +amp_sv[0];
      jamp_sv[36] -= amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[101] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[105] -= amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      jamp_sv[109] -= amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      jamp_sv[115] -= amp_sv[0];
      VVVV3_0( w_sv[24], w_sv[1], w_sv[8], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[14] -= amp_sv[0];
      jamp_sv[15] += +amp_sv[0];
      jamp_sv[43] += +amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[45] += +amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[61] += +amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[105] -= amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      VVVV4_0( w_sv[24], w_sv[1], w_sv[8], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[15] += +amp_sv[0];
      jamp_sv[26] -= amp_sv[0];
      jamp_sv[30] += +amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[36] += +amp_sv[0];
      jamp_sv[43] += +amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[45] += +amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[61] += +amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[101] -= amp_sv[0];
      jamp_sv[109] += +amp_sv[0];
      jamp_sv[112] -= amp_sv[0];
      jamp_sv[115] += +amp_sv[0];
      VVVV1_0( w_sv[20], w_sv[1], w_sv[8], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[30] -= amp_sv[0];
      jamp_sv[36] -= amp_sv[0];
      jamp_sv[38] += +amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[99] += +amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      jamp_sv[107] -= amp_sv[0];
      jamp_sv[109] -= amp_sv[0];
      jamp_sv[115] -= amp_sv[0];
      jamp_sv[118] += +amp_sv[0];
      VVVV3_0( w_sv[20], w_sv[1], w_sv[8], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[42] += +amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[85] += +amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      jamp_sv[107] -= amp_sv[0];
      VVVV4_0( w_sv[20], w_sv[1], w_sv[8], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[24] -= amp_sv[0];
      jamp_sv[30] += +amp_sv[0];
      jamp_sv[36] += +amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[42] += +amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[85] += +amp_sv[0];
      jamp_sv[99] -= amp_sv[0];
      jamp_sv[109] += +amp_sv[0];
      jamp_sv[115] += +amp_sv[0];
      jamp_sv[118] -= amp_sv[0];

      // *** DIAGRAM 1182 OF 1240 ***

      // Wavefunction(s) for diagram number 1182
      VVV1P0_1( w_sv[60], w_sv[1], COUPs[0], 0., 0., w_sv[72] );
      VVV1P0_1( w_sv[24], w_sv[1], COUPs[0], 0., 0., w_sv[60] );
      VVV1P0_1( w_sv[20], w_sv[1], COUPs[0], 0., 0., w_sv[24] );

      // Amplitude(s) for diagram number 1182
      VVV1_0( w_sv[8], w_sv[6], w_sv[72], COUPs[0], &amp_sv[0] );
      jamp_sv[8] += +amp_sv[0];
      jamp_sv[14] -= amp_sv[0];
      jamp_sv[24] -= amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[32] += +amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[84] += +amp_sv[0];
      jamp_sv[99] -= amp_sv[0];
      jamp_sv[101] += +amp_sv[0];
      jamp_sv[102] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      jamp_sv[105] -= amp_sv[0];
      jamp_sv[107] += +amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      jamp_sv[118] -= amp_sv[0];
      VVV1_0( w_sv[8], w_sv[6], w_sv[60], COUPs[0], &amp_sv[0] );
      jamp_sv[14] -= amp_sv[0];
      jamp_sv[26] += +amp_sv[0];
      jamp_sv[30] -= amp_sv[0];
      jamp_sv[32] += +amp_sv[0];
      jamp_sv[36] -= amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[101] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[105] -= amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      jamp_sv[109] -= amp_sv[0];
      jamp_sv[112] += +amp_sv[0];
      jamp_sv[115] -= amp_sv[0];
      VVV1_0( w_sv[8], w_sv[6], w_sv[24], COUPs[0], &amp_sv[0] );
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[30] -= amp_sv[0];
      jamp_sv[36] -= amp_sv[0];
      jamp_sv[38] += +amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[84] -= amp_sv[0];
      jamp_sv[99] += +amp_sv[0];
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      jamp_sv[107] -= amp_sv[0];
      jamp_sv[109] -= amp_sv[0];
      jamp_sv[115] -= amp_sv[0];
      jamp_sv[118] += +amp_sv[0];

      // *** DIAGRAM 1183 OF 1240 ***

      // Wavefunction(s) for diagram number 1183
      // (none)

      // Amplitude(s) for diagram number 1183
      VVV1_0( w_sv[1], w_sv[8], w_sv[23], COUPs[0], &amp_sv[0] );
      jamp_sv[9] -= amp_sv[0];
      jamp_sv[15] += +amp_sv[0];
      jamp_sv[24] += +amp_sv[0];
      jamp_sv[26] -= amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[38] += +amp_sv[0];
      jamp_sv[42] -= amp_sv[0];
      jamp_sv[43] += +amp_sv[0];
      jamp_sv[45] += +amp_sv[0];
      jamp_sv[47] -= amp_sv[0];
      jamp_sv[61] += +amp_sv[0];
      jamp_sv[85] -= amp_sv[0];
      jamp_sv[99] += +amp_sv[0];
      jamp_sv[101] -= amp_sv[0];
      jamp_sv[112] -= amp_sv[0];
      jamp_sv[118] += +amp_sv[0];
      VVV1_0( w_sv[1], w_sv[8], w_sv[68], COUPs[0], &amp_sv[0] );
      jamp_sv[15] += +amp_sv[0];
      jamp_sv[26] -= amp_sv[0];
      jamp_sv[30] += +amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[36] += +amp_sv[0];
      jamp_sv[43] += +amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[45] += +amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[61] += +amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[101] -= amp_sv[0];
      jamp_sv[109] += +amp_sv[0];
      jamp_sv[112] -= amp_sv[0];
      jamp_sv[115] += +amp_sv[0];
      VVV1_0( w_sv[1], w_sv[8], w_sv[29], COUPs[0], &amp_sv[0] );
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[24] -= amp_sv[0];
      jamp_sv[30] += +amp_sv[0];
      jamp_sv[36] += +amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[42] += +amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[85] += +amp_sv[0];
      jamp_sv[99] -= amp_sv[0];
      jamp_sv[109] += +amp_sv[0];
      jamp_sv[115] += +amp_sv[0];
      jamp_sv[118] -= amp_sv[0];

      // *** DIAGRAM 1184 OF 1240 ***

      // Wavefunction(s) for diagram number 1184
      // (none)

      // Amplitude(s) for diagram number 1184
      FFV1_0( w_sv[3], w_sv[47], w_sv[72], COUPs[1], &amp_sv[0] );
      jamp_sv[99] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[101] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[102] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[103] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[105] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[107] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[112] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[118] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[47], w_sv[60], COUPs[1], &amp_sv[0] );
      jamp_sv[101] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[103] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[104] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[105] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[106] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[109] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[112] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[115] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[47], w_sv[24], COUPs[1], &amp_sv[0] );
      jamp_sv[99] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[102] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[104] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[106] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[107] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[109] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[115] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[118] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1185 OF 1240 ***

      // Wavefunction(s) for diagram number 1185
      // (none)

      // Amplitude(s) for diagram number 1185
      FFV1_0( w_sv[16], w_sv[47], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[102] += +amp_sv[0];
      jamp_sv[103] -= amp_sv[0];
      jamp_sv[105] -= amp_sv[0];
      jamp_sv[107] += +amp_sv[0];
      FFV1_0( w_sv[27], w_sv[47], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[103] -= amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[105] -= amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      FFV1_0( w_sv[98], w_sv[47], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[102] -= amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      jamp_sv[107] -= amp_sv[0];

      // *** DIAGRAM 1186 OF 1240 ***

      // Wavefunction(s) for diagram number 1186
      // (none)

      // Amplitude(s) for diagram number 1186
      FFV1_0( w_sv[41], w_sv[2], w_sv[72], COUPs[1], &amp_sv[0] );
      jamp_sv[8] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[14] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[24] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[26] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[32] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[38] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[60] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[84] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[41], w_sv[2], w_sv[60], COUPs[1], &amp_sv[0] );
      jamp_sv[14] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[26] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[30] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[32] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[36] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[50] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[60] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[74] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[41], w_sv[2], w_sv[24], COUPs[1], &amp_sv[0] );
      jamp_sv[8] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[24] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[30] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[36] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[38] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[50] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[74] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[84] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1187 OF 1240 ***

      // Wavefunction(s) for diagram number 1187
      // (none)

      // Amplitude(s) for diagram number 1187
      FFV1_0( w_sv[41], w_sv[59], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[8] += +amp_sv[0];
      jamp_sv[14] -= amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[84] += +amp_sv[0];
      FFV1_0( w_sv[41], w_sv[71], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[14] -= amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[60] -= amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      FFV1_0( w_sv[41], w_sv[21], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[84] -= amp_sv[0];

      // *** DIAGRAM 1188 OF 1240 ***

      // Wavefunction(s) for diagram number 1188
      VVVV1P0_1( w_sv[0], w_sv[4], w_sv[6], COUPs[2], 0., 0., w_sv[21] );
      VVVV3P0_1( w_sv[0], w_sv[4], w_sv[6], COUPs[2], 0., 0., w_sv[71] );
      VVVV4P0_1( w_sv[0], w_sv[4], w_sv[6], COUPs[2], 0., 0., w_sv[59] );
      FFV1_2( w_sv[3], w_sv[21], COUPs[1], cIPD[0], cIPD[1], w_sv[24] );
      FFV1_2( w_sv[3], w_sv[71], COUPs[1], cIPD[0], cIPD[1], w_sv[60] );
      FFV1_2( w_sv[3], w_sv[59], COUPs[1], cIPD[0], cIPD[1], w_sv[72] );

      // Amplitude(s) for diagram number 1188
      FFV1_0( w_sv[24], w_sv[77], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[36] += +amp_sv[0];
      jamp_sv[37] -= amp_sv[0];
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      FFV1_0( w_sv[60], w_sv[77], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[37] -= amp_sv[0];
      jamp_sv[38] += +amp_sv[0];
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[40] += +amp_sv[0];
      FFV1_0( w_sv[72], w_sv[77], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[36] -= amp_sv[0];
      jamp_sv[38] += +amp_sv[0];
      jamp_sv[40] += +amp_sv[0];
      jamp_sv[41] -= amp_sv[0];

      // *** DIAGRAM 1189 OF 1240 ***

      // Wavefunction(s) for diagram number 1189
      VVV1P0_1( w_sv[21], w_sv[5], COUPs[0], 0., 0., w_sv[98] );
      VVV1P0_1( w_sv[71], w_sv[5], COUPs[0], 0., 0., w_sv[27] );
      VVV1P0_1( w_sv[59], w_sv[5], COUPs[0], 0., 0., w_sv[16] );

      // Amplitude(s) for diagram number 1189
      FFV1_0( w_sv[3], w_sv[77], w_sv[98], COUPs[1], &amp_sv[0] );
      jamp_sv[25] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[28] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[34] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[36] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[37] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[39] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[41] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[44] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[77], w_sv[27], COUPs[1], &amp_sv[0] );
      jamp_sv[28] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[31] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[34] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[37] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[38] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[39] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[40] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[42] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[77], w_sv[16], COUPs[1], &amp_sv[0] );
      jamp_sv[25] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[31] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[36] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[38] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[40] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[41] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[42] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[44] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1190 OF 1240 ***

      // Wavefunction(s) for diagram number 1190
      // (none)

      // Amplitude(s) for diagram number 1190
      FFV1_0( w_sv[38], w_sv[77], w_sv[21], COUPs[1], &amp_sv[0] );
      jamp_sv[25] += +amp_sv[0];
      jamp_sv[28] -= amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[44] += +amp_sv[0];
      FFV1_0( w_sv[38], w_sv[77], w_sv[71], COUPs[1], &amp_sv[0] );
      jamp_sv[28] -= amp_sv[0];
      jamp_sv[31] += +amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[42] += +amp_sv[0];
      FFV1_0( w_sv[38], w_sv[77], w_sv[59], COUPs[1], &amp_sv[0] );
      jamp_sv[25] -= amp_sv[0];
      jamp_sv[31] += +amp_sv[0];
      jamp_sv[42] += +amp_sv[0];
      jamp_sv[44] -= amp_sv[0];

      // *** DIAGRAM 1191 OF 1240 ***

      // Wavefunction(s) for diagram number 1191
      FFV1_1( w_sv[2], w_sv[21], COUPs[1], cIPD[0], cIPD[1], w_sv[29] );
      FFV1_1( w_sv[2], w_sv[71], COUPs[1], cIPD[0], cIPD[1], w_sv[68] );
      FFV1_1( w_sv[2], w_sv[59], COUPs[1], cIPD[0], cIPD[1], w_sv[23] );

      // Amplitude(s) for diagram number 1191
      FFV1_0( w_sv[52], w_sv[29], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[67] -= amp_sv[0];
      jamp_sv[109] += +amp_sv[0];
      FFV1_0( w_sv[52], w_sv[68], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[53] += +amp_sv[0];
      jamp_sv[67] -= amp_sv[0];
      jamp_sv[99] += +amp_sv[0];
      FFV1_0( w_sv[52], w_sv[23], w_sv[5], COUPs[1], &amp_sv[0] );
      jamp_sv[11] -= amp_sv[0];
      jamp_sv[53] += +amp_sv[0];
      jamp_sv[99] += +amp_sv[0];
      jamp_sv[109] -= amp_sv[0];

      // *** DIAGRAM 1192 OF 1240 ***

      // Wavefunction(s) for diagram number 1192
      // (none)

      // Amplitude(s) for diagram number 1192
      FFV1_0( w_sv[52], w_sv[2], w_sv[98], COUPs[1], &amp_sv[0] );
      jamp_sv[11] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[21] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[67] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[75] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[77] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[88] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[94] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[109] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[52], w_sv[2], w_sv[27], COUPs[1], &amp_sv[0] );
      jamp_sv[21] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[53] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[67] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[77] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[85] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[88] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[91] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[99] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[52], w_sv[2], w_sv[16], COUPs[1], &amp_sv[0] );
      jamp_sv[11] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[53] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[75] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[85] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[91] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[94] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[99] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[109] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1193 OF 1240 ***

      // Wavefunction(s) for diagram number 1193
      // (none)

      // Amplitude(s) for diagram number 1193
      FFV1_0( w_sv[52], w_sv[39], w_sv[21], COUPs[1], &amp_sv[0] );
      jamp_sv[75] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[88] -= amp_sv[0];
      jamp_sv[94] += +amp_sv[0];
      FFV1_0( w_sv[52], w_sv[39], w_sv[71], COUPs[1], &amp_sv[0] );
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[85] += +amp_sv[0];
      jamp_sv[88] -= amp_sv[0];
      jamp_sv[91] += +amp_sv[0];
      FFV1_0( w_sv[52], w_sv[39], w_sv[59], COUPs[1], &amp_sv[0] );
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[85] += +amp_sv[0];
      jamp_sv[91] += +amp_sv[0];
      jamp_sv[94] -= amp_sv[0];

      // *** DIAGRAM 1194 OF 1240 ***

      // Wavefunction(s) for diagram number 1194
      // (none)

      // Amplitude(s) for diagram number 1194
      FFV1_0( w_sv[3], w_sv[29], w_sv[66], COUPs[1], &amp_sv[0] );
      jamp_sv[10] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[11] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[20] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[21] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[66] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[67] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[108] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[109] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[68], w_sv[66], COUPs[1], &amp_sv[0] );
      jamp_sv[20] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[21] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[52] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[53] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[66] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[67] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[98] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[99] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[23], w_sv[66], COUPs[1], &amp_sv[0] );
      jamp_sv[10] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[11] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[52] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[53] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[98] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[99] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[108] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[109] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1195 OF 1240 ***

      // Wavefunction(s) for diagram number 1195
      // (none)

      // Amplitude(s) for diagram number 1195
      FFV1_0( w_sv[24], w_sv[2], w_sv[66], COUPs[1], &amp_sv[0] );
      jamp_sv[36] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[37] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[39] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[41] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[78] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[79] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[81] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[83] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[60], w_sv[2], w_sv[66], COUPs[1], &amp_sv[0] );
      jamp_sv[37] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[38] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[39] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[40] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[79] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[80] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[81] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[82] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[72], w_sv[2], w_sv[66], COUPs[1], &amp_sv[0] );
      jamp_sv[36] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[38] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[40] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[41] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[78] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[80] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[82] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[83] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1196 OF 1240 ***

      // Wavefunction(s) for diagram number 1196
      // (none)

      // Amplitude(s) for diagram number 1196
      VVV1_0( w_sv[21], w_sv[66], w_sv[8], COUPs[0], &amp_sv[0] );
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[20] += +amp_sv[0];
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[36] += +amp_sv[0];
      jamp_sv[37] -= amp_sv[0];
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[66] += +amp_sv[0];
      jamp_sv[67] -= amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[79] += +amp_sv[0];
      jamp_sv[81] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      jamp_sv[109] += +amp_sv[0];
      VVV1_0( w_sv[71], w_sv[66], w_sv[8], COUPs[0], &amp_sv[0] );
      jamp_sv[20] += +amp_sv[0];
      jamp_sv[21] -= amp_sv[0];
      jamp_sv[37] -= amp_sv[0];
      jamp_sv[38] += +amp_sv[0];
      jamp_sv[39] -= amp_sv[0];
      jamp_sv[40] += +amp_sv[0];
      jamp_sv[52] -= amp_sv[0];
      jamp_sv[53] += +amp_sv[0];
      jamp_sv[66] += +amp_sv[0];
      jamp_sv[67] -= amp_sv[0];
      jamp_sv[79] += +amp_sv[0];
      jamp_sv[80] -= amp_sv[0];
      jamp_sv[81] += +amp_sv[0];
      jamp_sv[82] -= amp_sv[0];
      jamp_sv[98] -= amp_sv[0];
      jamp_sv[99] += +amp_sv[0];
      VVV1_0( w_sv[59], w_sv[66], w_sv[8], COUPs[0], &amp_sv[0] );
      jamp_sv[10] += +amp_sv[0];
      jamp_sv[11] -= amp_sv[0];
      jamp_sv[36] -= amp_sv[0];
      jamp_sv[38] += +amp_sv[0];
      jamp_sv[40] += +amp_sv[0];
      jamp_sv[41] -= amp_sv[0];
      jamp_sv[52] -= amp_sv[0];
      jamp_sv[53] += +amp_sv[0];
      jamp_sv[78] += +amp_sv[0];
      jamp_sv[80] -= amp_sv[0];
      jamp_sv[82] -= amp_sv[0];
      jamp_sv[83] += +amp_sv[0];
      jamp_sv[98] -= amp_sv[0];
      jamp_sv[99] += +amp_sv[0];
      jamp_sv[108] += +amp_sv[0];
      jamp_sv[109] -= amp_sv[0];

      // *** DIAGRAM 1197 OF 1240 ***

      // Wavefunction(s) for diagram number 1197
      // (none)

      // Amplitude(s) for diagram number 1197
      VVVV1_0( w_sv[21], w_sv[1], w_sv[8], w_sv[5], COUPs[2], &amp_sv[0] );
      jamp_sv[10] += +amp_sv[0];
      jamp_sv[20] -= amp_sv[0];
      jamp_sv[25] -= amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[34] += +amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[77] += +amp_sv[0];
      jamp_sv[78] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[81] -= amp_sv[0];
      jamp_sv[83] += +amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[94] -= amp_sv[0];
      jamp_sv[108] += +amp_sv[0];
      VVVV3_0( w_sv[21], w_sv[1], w_sv[8], w_sv[5], COUPs[2], &amp_sv[0] );
      jamp_sv[10] += +amp_sv[0];
      jamp_sv[11] -= amp_sv[0];
      jamp_sv[20] -= amp_sv[0];
      jamp_sv[21] += +amp_sv[0];
      jamp_sv[36] -= amp_sv[0];
      jamp_sv[37] += +amp_sv[0];
      jamp_sv[39] += +amp_sv[0];
      jamp_sv[41] -= amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[67] += +amp_sv[0];
      jamp_sv[78] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[81] -= amp_sv[0];
      jamp_sv[83] += +amp_sv[0];
      jamp_sv[108] += +amp_sv[0];
      jamp_sv[109] -= amp_sv[0];
      VVVV4_0( w_sv[21], w_sv[1], w_sv[8], w_sv[5], COUPs[2], &amp_sv[0] );
      jamp_sv[11] -= amp_sv[0];
      jamp_sv[21] += +amp_sv[0];
      jamp_sv[25] += +amp_sv[0];
      jamp_sv[28] -= amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[36] -= amp_sv[0];
      jamp_sv[37] += +amp_sv[0];
      jamp_sv[39] += +amp_sv[0];
      jamp_sv[41] -= amp_sv[0];
      jamp_sv[44] += +amp_sv[0];
      jamp_sv[67] += +amp_sv[0];
      jamp_sv[75] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[88] -= amp_sv[0];
      jamp_sv[94] += +amp_sv[0];
      jamp_sv[109] -= amp_sv[0];
      VVVV1_0( w_sv[71], w_sv[1], w_sv[8], w_sv[5], COUPs[2], &amp_sv[0] );
      jamp_sv[20] -= amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[31] -= amp_sv[0];
      jamp_sv[34] += +amp_sv[0];
      jamp_sv[42] -= amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[77] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[81] -= amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[85] -= amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[91] -= amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      VVVV3_0( w_sv[71], w_sv[1], w_sv[8], w_sv[5], COUPs[2], &amp_sv[0] );
      jamp_sv[20] -= amp_sv[0];
      jamp_sv[21] += +amp_sv[0];
      jamp_sv[37] += +amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[39] += +amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[67] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[81] -= amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      jamp_sv[99] -= amp_sv[0];
      VVVV4_0( w_sv[71], w_sv[1], w_sv[8], w_sv[5], COUPs[2], &amp_sv[0] );
      jamp_sv[21] += +amp_sv[0];
      jamp_sv[28] -= amp_sv[0];
      jamp_sv[31] += +amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[37] += +amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[39] += +amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[42] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[67] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[85] += +amp_sv[0];
      jamp_sv[88] -= amp_sv[0];
      jamp_sv[91] += +amp_sv[0];
      jamp_sv[99] -= amp_sv[0];
      VVVV1_0( w_sv[59], w_sv[1], w_sv[8], w_sv[5], COUPs[2], &amp_sv[0] );
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[25] += +amp_sv[0];
      jamp_sv[31] -= amp_sv[0];
      jamp_sv[42] -= amp_sv[0];
      jamp_sv[44] += +amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[75] += +amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[85] -= amp_sv[0];
      jamp_sv[91] -= amp_sv[0];
      jamp_sv[94] += +amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      VVVV3_0( w_sv[59], w_sv[1], w_sv[8], w_sv[5], COUPs[2], &amp_sv[0] );
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[36] += +amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      jamp_sv[99] -= amp_sv[0];
      jamp_sv[108] -= amp_sv[0];
      jamp_sv[109] += +amp_sv[0];
      VVVV4_0( w_sv[59], w_sv[1], w_sv[8], w_sv[5], COUPs[2], &amp_sv[0] );
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[25] -= amp_sv[0];
      jamp_sv[31] += +amp_sv[0];
      jamp_sv[36] += +amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[42] += +amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[85] += +amp_sv[0];
      jamp_sv[91] += +amp_sv[0];
      jamp_sv[94] -= amp_sv[0];
      jamp_sv[99] -= amp_sv[0];
      jamp_sv[109] += +amp_sv[0];

      // *** DIAGRAM 1198 OF 1240 ***

      // Wavefunction(s) for diagram number 1198
      VVV1P0_1( w_sv[21], w_sv[1], COUPs[0], 0., 0., w_sv[66] );
      VVV1P0_1( w_sv[71], w_sv[1], COUPs[0], 0., 0., w_sv[21] );
      VVV1P0_1( w_sv[59], w_sv[1], COUPs[0], 0., 0., w_sv[71] );

      // Amplitude(s) for diagram number 1198
      VVV1_0( w_sv[8], w_sv[5], w_sv[66], COUPs[0], &amp_sv[0] );
      jamp_sv[10] += +amp_sv[0];
      jamp_sv[20] -= amp_sv[0];
      jamp_sv[25] -= amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[34] += +amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[77] += +amp_sv[0];
      jamp_sv[78] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[81] -= amp_sv[0];
      jamp_sv[83] += +amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[94] -= amp_sv[0];
      jamp_sv[108] += +amp_sv[0];
      VVV1_0( w_sv[8], w_sv[5], w_sv[21], COUPs[0], &amp_sv[0] );
      jamp_sv[20] -= amp_sv[0];
      jamp_sv[28] += +amp_sv[0];
      jamp_sv[31] -= amp_sv[0];
      jamp_sv[34] += +amp_sv[0];
      jamp_sv[42] -= amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[77] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[81] -= amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[85] -= amp_sv[0];
      jamp_sv[88] += +amp_sv[0];
      jamp_sv[91] -= amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      VVV1_0( w_sv[8], w_sv[5], w_sv[71], COUPs[0], &amp_sv[0] );
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[25] += +amp_sv[0];
      jamp_sv[31] -= amp_sv[0];
      jamp_sv[42] -= amp_sv[0];
      jamp_sv[44] += +amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[75] += +amp_sv[0];
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[85] -= amp_sv[0];
      jamp_sv[91] -= amp_sv[0];
      jamp_sv[94] += +amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      jamp_sv[108] -= amp_sv[0];

      // *** DIAGRAM 1199 OF 1240 ***

      // Wavefunction(s) for diagram number 1199
      // (none)

      // Amplitude(s) for diagram number 1199
      VVV1_0( w_sv[1], w_sv[8], w_sv[98], COUPs[0], &amp_sv[0] );
      jamp_sv[11] -= amp_sv[0];
      jamp_sv[21] += +amp_sv[0];
      jamp_sv[25] += +amp_sv[0];
      jamp_sv[28] -= amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[36] -= amp_sv[0];
      jamp_sv[37] += +amp_sv[0];
      jamp_sv[39] += +amp_sv[0];
      jamp_sv[41] -= amp_sv[0];
      jamp_sv[44] += +amp_sv[0];
      jamp_sv[67] += +amp_sv[0];
      jamp_sv[75] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[88] -= amp_sv[0];
      jamp_sv[94] += +amp_sv[0];
      jamp_sv[109] -= amp_sv[0];
      VVV1_0( w_sv[1], w_sv[8], w_sv[27], COUPs[0], &amp_sv[0] );
      jamp_sv[21] += +amp_sv[0];
      jamp_sv[28] -= amp_sv[0];
      jamp_sv[31] += +amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[37] += +amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[39] += +amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[42] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[67] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[85] += +amp_sv[0];
      jamp_sv[88] -= amp_sv[0];
      jamp_sv[91] += +amp_sv[0];
      jamp_sv[99] -= amp_sv[0];
      VVV1_0( w_sv[1], w_sv[8], w_sv[16], COUPs[0], &amp_sv[0] );
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[25] -= amp_sv[0];
      jamp_sv[31] += +amp_sv[0];
      jamp_sv[36] += +amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[42] += +amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[85] += +amp_sv[0];
      jamp_sv[91] += +amp_sv[0];
      jamp_sv[94] -= amp_sv[0];
      jamp_sv[99] -= amp_sv[0];
      jamp_sv[109] += +amp_sv[0];

      // *** DIAGRAM 1200 OF 1240 ***

      // Wavefunction(s) for diagram number 1200
      // (none)

      // Amplitude(s) for diagram number 1200
      FFV1_0( w_sv[3], w_sv[39], w_sv[66], COUPs[1], &amp_sv[0] );
      jamp_sv[75] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[77] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[78] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[79] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[81] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[83] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[88] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[94] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[39], w_sv[21], COUPs[1], &amp_sv[0] );
      jamp_sv[77] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[79] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[80] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[81] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[82] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[85] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[88] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[91] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[39], w_sv[71], COUPs[1], &amp_sv[0] );
      jamp_sv[75] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[78] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[80] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[82] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[83] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[85] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[91] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[94] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1201 OF 1240 ***

      // Wavefunction(s) for diagram number 1201
      // (none)

      // Amplitude(s) for diagram number 1201
      FFV1_0( w_sv[24], w_sv[39], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[78] += +amp_sv[0];
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[81] -= amp_sv[0];
      jamp_sv[83] += +amp_sv[0];
      FFV1_0( w_sv[60], w_sv[39], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[79] -= amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[81] -= amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      FFV1_0( w_sv[72], w_sv[39], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[78] -= amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];

      // *** DIAGRAM 1202 OF 1240 ***

      // Wavefunction(s) for diagram number 1202
      // (none)

      // Amplitude(s) for diagram number 1202
      FFV1_0( w_sv[38], w_sv[2], w_sv[66], COUPs[1], &amp_sv[0] );
      jamp_sv[10] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[20] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[25] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[28] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[34] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[44] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[66] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[108] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[38], w_sv[2], w_sv[21], COUPs[1], &amp_sv[0] );
      jamp_sv[20] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[28] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[31] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[34] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[42] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[52] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[66] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[98] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[38], w_sv[2], w_sv[71], COUPs[1], &amp_sv[0] );
      jamp_sv[10] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[25] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[31] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[42] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[44] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[52] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[98] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[108] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1203 OF 1240 ***

      // Wavefunction(s) for diagram number 1203
      // (none)

      // Amplitude(s) for diagram number 1203
      FFV1_0( w_sv[38], w_sv[29], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[10] += +amp_sv[0];
      jamp_sv[20] -= amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[108] += +amp_sv[0];
      FFV1_0( w_sv[38], w_sv[68], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[20] -= amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[66] -= amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      FFV1_0( w_sv[38], w_sv[23], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      jamp_sv[108] -= amp_sv[0];

      // *** DIAGRAM 1204 OF 1240 ***

      // Wavefunction(s) for diagram number 1204
      VVVV1P0_1( w_sv[0], w_sv[5], w_sv[6], COUPs[2], 0., 0., w_sv[23] );
      VVVV3P0_1( w_sv[0], w_sv[5], w_sv[6], COUPs[2], 0., 0., w_sv[68] );
      VVVV4P0_1( w_sv[0], w_sv[5], w_sv[6], COUPs[2], 0., 0., w_sv[29] );
      FFV1_2( w_sv[3], w_sv[23], COUPs[1], cIPD[0], cIPD[1], w_sv[71] );
      FFV1_2( w_sv[3], w_sv[68], COUPs[1], cIPD[0], cIPD[1], w_sv[21] );
      FFV1_2( w_sv[3], w_sv[29], COUPs[1], cIPD[0], cIPD[1], w_sv[66] );

      // Amplitude(s) for diagram number 1204
      FFV1_0( w_sv[71], w_sv[77], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[30] += +amp_sv[0];
      jamp_sv[31] -= amp_sv[0];
      jamp_sv[33] -= amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      FFV1_0( w_sv[21], w_sv[77], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[31] -= amp_sv[0];
      jamp_sv[32] += +amp_sv[0];
      jamp_sv[33] -= amp_sv[0];
      jamp_sv[34] += +amp_sv[0];
      FFV1_0( w_sv[66], w_sv[77], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[30] -= amp_sv[0];
      jamp_sv[32] += +amp_sv[0];
      jamp_sv[34] += +amp_sv[0];
      jamp_sv[35] -= amp_sv[0];

      // *** DIAGRAM 1205 OF 1240 ***

      // Wavefunction(s) for diagram number 1205
      VVV1P0_1( w_sv[23], w_sv[4], COUPs[0], 0., 0., w_sv[72] );
      VVV1P0_1( w_sv[68], w_sv[4], COUPs[0], 0., 0., w_sv[60] );
      VVV1P0_1( w_sv[29], w_sv[4], COUPs[0], 0., 0., w_sv[24] );

      // Amplitude(s) for diagram number 1205
      FFV1_0( w_sv[3], w_sv[77], w_sv[72], COUPs[1], &amp_sv[0] );
      jamp_sv[27] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[29] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[30] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[31] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[33] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[35] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[40] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[46] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[77], w_sv[60], COUPs[1], &amp_sv[0] );
      jamp_sv[29] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[31] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[32] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[33] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[34] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[37] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[40] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[43] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[77], w_sv[24], COUPs[1], &amp_sv[0] );
      jamp_sv[27] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[30] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[32] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[34] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[35] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[37] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[43] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[46] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1206 OF 1240 ***

      // Wavefunction(s) for diagram number 1206
      // (none)

      // Amplitude(s) for diagram number 1206
      FFV1_0( w_sv[46], w_sv[77], w_sv[23], COUPs[1], &amp_sv[0] );
      jamp_sv[27] += +amp_sv[0];
      jamp_sv[29] -= amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[46] += +amp_sv[0];
      FFV1_0( w_sv[46], w_sv[77], w_sv[68], COUPs[1], &amp_sv[0] );
      jamp_sv[29] -= amp_sv[0];
      jamp_sv[37] += +amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[43] += +amp_sv[0];
      FFV1_0( w_sv[46], w_sv[77], w_sv[29], COUPs[1], &amp_sv[0] );
      jamp_sv[27] -= amp_sv[0];
      jamp_sv[37] += +amp_sv[0];
      jamp_sv[43] += +amp_sv[0];
      jamp_sv[46] -= amp_sv[0];

      // *** DIAGRAM 1207 OF 1240 ***

      // Wavefunction(s) for diagram number 1207
      FFV1_1( w_sv[2], w_sv[23], COUPs[1], cIPD[0], cIPD[1], w_sv[77] );
      FFV1_1( w_sv[2], w_sv[68], COUPs[1], cIPD[0], cIPD[1], w_sv[16] );
      FFV1_1( w_sv[2], w_sv[29], COUPs[1], cIPD[0], cIPD[1], w_sv[27] );

      // Amplitude(s) for diagram number 1207
      FFV1_0( w_sv[52], w_sv[77], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[23] -= amp_sv[0];
      jamp_sv[91] -= amp_sv[0];
      jamp_sv[115] += +amp_sv[0];
      FFV1_0( w_sv[52], w_sv[16], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[23] -= amp_sv[0];
      jamp_sv[77] += +amp_sv[0];
      jamp_sv[91] -= amp_sv[0];
      jamp_sv[101] += +amp_sv[0];
      FFV1_0( w_sv[52], w_sv[27], w_sv[4], COUPs[1], &amp_sv[0] );
      jamp_sv[17] -= amp_sv[0];
      jamp_sv[77] += +amp_sv[0];
      jamp_sv[101] += +amp_sv[0];
      jamp_sv[115] -= amp_sv[0];

      // *** DIAGRAM 1208 OF 1240 ***

      // Wavefunction(s) for diagram number 1208
      // (none)

      // Amplitude(s) for diagram number 1208
      FFV1_0( w_sv[52], w_sv[2], w_sv[72], COUPs[1], &amp_sv[0] );
      jamp_sv[17] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[23] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[51] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[53] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[64] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[70] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[91] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[115] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[52], w_sv[2], w_sv[60], COUPs[1], &amp_sv[0] );
      jamp_sv[23] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[53] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[61] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[64] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[67] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[77] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[91] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[101] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[52], w_sv[2], w_sv[24], COUPs[1], &amp_sv[0] );
      jamp_sv[17] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[51] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[61] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[67] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[70] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[77] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[101] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[115] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1209 OF 1240 ***

      // Wavefunction(s) for diagram number 1209
      // (none)

      // Amplitude(s) for diagram number 1209
      FFV1_0( w_sv[52], w_sv[33], w_sv[23], COUPs[1], &amp_sv[0] );
      jamp_sv[51] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[64] -= amp_sv[0];
      jamp_sv[70] += +amp_sv[0];
      FFV1_0( w_sv[52], w_sv[33], w_sv[68], COUPs[1], &amp_sv[0] );
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[61] += +amp_sv[0];
      jamp_sv[64] -= amp_sv[0];
      jamp_sv[67] += +amp_sv[0];
      FFV1_0( w_sv[52], w_sv[33], w_sv[29], COUPs[1], &amp_sv[0] );
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[61] += +amp_sv[0];
      jamp_sv[67] += +amp_sv[0];
      jamp_sv[70] -= amp_sv[0];

      // *** DIAGRAM 1210 OF 1240 ***

      // Wavefunction(s) for diagram number 1210
      // (none)

      // Amplitude(s) for diagram number 1210
      FFV1_0( w_sv[3], w_sv[77], w_sv[61], COUPs[1], &amp_sv[0] );
      jamp_sv[16] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[17] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[22] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[23] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[90] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[91] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[114] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[115] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[16], w_sv[61], COUPs[1], &amp_sv[0] );
      jamp_sv[22] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[23] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[76] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[77] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[90] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[91] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[100] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[101] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[27], w_sv[61], COUPs[1], &amp_sv[0] );
      jamp_sv[16] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[17] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[76] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[77] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[100] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[101] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[114] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[115] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1211 OF 1240 ***

      // Wavefunction(s) for diagram number 1211
      // (none)

      // Amplitude(s) for diagram number 1211
      FFV1_0( w_sv[71], w_sv[2], w_sv[61], COUPs[1], &amp_sv[0] );
      jamp_sv[30] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[31] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[33] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[35] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[54] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[55] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[57] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[59] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[21], w_sv[2], w_sv[61], COUPs[1], &amp_sv[0] );
      jamp_sv[31] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[32] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[33] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[34] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[55] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[56] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[57] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[58] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[66], w_sv[2], w_sv[61], COUPs[1], &amp_sv[0] );
      jamp_sv[30] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[32] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[34] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[35] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[54] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[56] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[58] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[59] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1212 OF 1240 ***

      // Wavefunction(s) for diagram number 1212
      // (none)

      // Amplitude(s) for diagram number 1212
      VVV1_0( w_sv[23], w_sv[61], w_sv[8], COUPs[0], &amp_sv[0] );
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[22] += +amp_sv[0];
      jamp_sv[23] -= amp_sv[0];
      jamp_sv[30] += +amp_sv[0];
      jamp_sv[31] -= amp_sv[0];
      jamp_sv[33] -= amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[55] += +amp_sv[0];
      jamp_sv[57] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[90] += +amp_sv[0];
      jamp_sv[91] -= amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      jamp_sv[115] += +amp_sv[0];
      VVV1_0( w_sv[68], w_sv[61], w_sv[8], COUPs[0], &amp_sv[0] );
      jamp_sv[22] += +amp_sv[0];
      jamp_sv[23] -= amp_sv[0];
      jamp_sv[31] -= amp_sv[0];
      jamp_sv[32] += +amp_sv[0];
      jamp_sv[33] -= amp_sv[0];
      jamp_sv[34] += +amp_sv[0];
      jamp_sv[55] += +amp_sv[0];
      jamp_sv[56] -= amp_sv[0];
      jamp_sv[57] += +amp_sv[0];
      jamp_sv[58] -= amp_sv[0];
      jamp_sv[76] -= amp_sv[0];
      jamp_sv[77] += +amp_sv[0];
      jamp_sv[90] += +amp_sv[0];
      jamp_sv[91] -= amp_sv[0];
      jamp_sv[100] -= amp_sv[0];
      jamp_sv[101] += +amp_sv[0];
      VVV1_0( w_sv[29], w_sv[61], w_sv[8], COUPs[0], &amp_sv[0] );
      jamp_sv[16] += +amp_sv[0];
      jamp_sv[17] -= amp_sv[0];
      jamp_sv[30] -= amp_sv[0];
      jamp_sv[32] += +amp_sv[0];
      jamp_sv[34] += +amp_sv[0];
      jamp_sv[35] -= amp_sv[0];
      jamp_sv[54] += +amp_sv[0];
      jamp_sv[56] -= amp_sv[0];
      jamp_sv[58] -= amp_sv[0];
      jamp_sv[59] += +amp_sv[0];
      jamp_sv[76] -= amp_sv[0];
      jamp_sv[77] += +amp_sv[0];
      jamp_sv[100] -= amp_sv[0];
      jamp_sv[101] += +amp_sv[0];
      jamp_sv[114] += +amp_sv[0];
      jamp_sv[115] -= amp_sv[0];

      // *** DIAGRAM 1213 OF 1240 ***

      // Wavefunction(s) for diagram number 1213
      // (none)

      // Amplitude(s) for diagram number 1213
      VVVV1_0( w_sv[23], w_sv[1], w_sv[8], w_sv[4], COUPs[2], &amp_sv[0] );
      jamp_sv[16] += +amp_sv[0];
      jamp_sv[22] -= amp_sv[0];
      jamp_sv[27] -= amp_sv[0];
      jamp_sv[29] += +amp_sv[0];
      jamp_sv[40] += +amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[53] += +amp_sv[0];
      jamp_sv[54] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[57] -= amp_sv[0];
      jamp_sv[59] += +amp_sv[0];
      jamp_sv[64] += +amp_sv[0];
      jamp_sv[70] -= amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[114] += +amp_sv[0];
      VVVV3_0( w_sv[23], w_sv[1], w_sv[8], w_sv[4], COUPs[2], &amp_sv[0] );
      jamp_sv[16] += +amp_sv[0];
      jamp_sv[17] -= amp_sv[0];
      jamp_sv[22] -= amp_sv[0];
      jamp_sv[23] += +amp_sv[0];
      jamp_sv[30] -= amp_sv[0];
      jamp_sv[31] += +amp_sv[0];
      jamp_sv[33] += +amp_sv[0];
      jamp_sv[35] -= amp_sv[0];
      jamp_sv[54] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[57] -= amp_sv[0];
      jamp_sv[59] += +amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[91] += +amp_sv[0];
      jamp_sv[114] += +amp_sv[0];
      jamp_sv[115] -= amp_sv[0];
      VVVV4_0( w_sv[23], w_sv[1], w_sv[8], w_sv[4], COUPs[2], &amp_sv[0] );
      jamp_sv[17] -= amp_sv[0];
      jamp_sv[23] += +amp_sv[0];
      jamp_sv[27] += +amp_sv[0];
      jamp_sv[29] -= amp_sv[0];
      jamp_sv[30] -= amp_sv[0];
      jamp_sv[31] += +amp_sv[0];
      jamp_sv[33] += +amp_sv[0];
      jamp_sv[35] -= amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[46] += +amp_sv[0];
      jamp_sv[51] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[64] -= amp_sv[0];
      jamp_sv[70] += +amp_sv[0];
      jamp_sv[91] += +amp_sv[0];
      jamp_sv[115] -= amp_sv[0];
      VVVV1_0( w_sv[68], w_sv[1], w_sv[8], w_sv[4], COUPs[2], &amp_sv[0] );
      jamp_sv[22] -= amp_sv[0];
      jamp_sv[29] += +amp_sv[0];
      jamp_sv[37] -= amp_sv[0];
      jamp_sv[40] += +amp_sv[0];
      jamp_sv[43] -= amp_sv[0];
      jamp_sv[53] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[57] -= amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[61] -= amp_sv[0];
      jamp_sv[64] += +amp_sv[0];
      jamp_sv[67] -= amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      VVVV3_0( w_sv[68], w_sv[1], w_sv[8], w_sv[4], COUPs[2], &amp_sv[0] );
      jamp_sv[22] -= amp_sv[0];
      jamp_sv[23] += +amp_sv[0];
      jamp_sv[31] += +amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[33] += +amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[57] -= amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[91] += +amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      jamp_sv[101] -= amp_sv[0];
      VVVV4_0( w_sv[68], w_sv[1], w_sv[8], w_sv[4], COUPs[2], &amp_sv[0] );
      jamp_sv[23] += +amp_sv[0];
      jamp_sv[29] -= amp_sv[0];
      jamp_sv[31] += +amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[33] += +amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[37] += +amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[43] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[61] += +amp_sv[0];
      jamp_sv[64] -= amp_sv[0];
      jamp_sv[67] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[91] += +amp_sv[0];
      jamp_sv[101] -= amp_sv[0];
      VVVV1_0( w_sv[29], w_sv[1], w_sv[8], w_sv[4], COUPs[2], &amp_sv[0] );
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[27] += +amp_sv[0];
      jamp_sv[37] -= amp_sv[0];
      jamp_sv[43] -= amp_sv[0];
      jamp_sv[46] += +amp_sv[0];
      jamp_sv[51] += +amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[61] -= amp_sv[0];
      jamp_sv[67] -= amp_sv[0];
      jamp_sv[70] += +amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      VVVV3_0( w_sv[29], w_sv[1], w_sv[8], w_sv[4], COUPs[2], &amp_sv[0] );
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[30] += +amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      jamp_sv[101] -= amp_sv[0];
      jamp_sv[114] -= amp_sv[0];
      jamp_sv[115] += +amp_sv[0];
      VVVV4_0( w_sv[29], w_sv[1], w_sv[8], w_sv[4], COUPs[2], &amp_sv[0] );
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[27] -= amp_sv[0];
      jamp_sv[30] += +amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[37] += +amp_sv[0];
      jamp_sv[43] += +amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[61] += +amp_sv[0];
      jamp_sv[67] += +amp_sv[0];
      jamp_sv[70] -= amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[101] -= amp_sv[0];
      jamp_sv[115] += +amp_sv[0];

      // *** DIAGRAM 1214 OF 1240 ***

      // Wavefunction(s) for diagram number 1214
      VVV1P0_1( w_sv[23], w_sv[1], COUPs[0], 0., 0., w_sv[61] );
      VVV1P0_1( w_sv[68], w_sv[1], COUPs[0], 0., 0., w_sv[23] );
      VVV1P0_1( w_sv[29], w_sv[1], COUPs[0], 0., 0., w_sv[68] );

      // Amplitude(s) for diagram number 1214
      VVV1_0( w_sv[8], w_sv[4], w_sv[61], COUPs[0], &amp_sv[0] );
      jamp_sv[16] += +amp_sv[0];
      jamp_sv[22] -= amp_sv[0];
      jamp_sv[27] -= amp_sv[0];
      jamp_sv[29] += +amp_sv[0];
      jamp_sv[40] += +amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[53] += +amp_sv[0];
      jamp_sv[54] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[57] -= amp_sv[0];
      jamp_sv[59] += +amp_sv[0];
      jamp_sv[64] += +amp_sv[0];
      jamp_sv[70] -= amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[114] += +amp_sv[0];
      VVV1_0( w_sv[8], w_sv[4], w_sv[23], COUPs[0], &amp_sv[0] );
      jamp_sv[22] -= amp_sv[0];
      jamp_sv[29] += +amp_sv[0];
      jamp_sv[37] -= amp_sv[0];
      jamp_sv[40] += +amp_sv[0];
      jamp_sv[43] -= amp_sv[0];
      jamp_sv[53] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[57] -= amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[61] -= amp_sv[0];
      jamp_sv[64] += +amp_sv[0];
      jamp_sv[67] -= amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      VVV1_0( w_sv[8], w_sv[4], w_sv[68], COUPs[0], &amp_sv[0] );
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[27] += +amp_sv[0];
      jamp_sv[37] -= amp_sv[0];
      jamp_sv[43] -= amp_sv[0];
      jamp_sv[46] += +amp_sv[0];
      jamp_sv[51] += +amp_sv[0];
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[61] -= amp_sv[0];
      jamp_sv[67] -= amp_sv[0];
      jamp_sv[70] += +amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      jamp_sv[114] -= amp_sv[0];

      // *** DIAGRAM 1215 OF 1240 ***

      // Wavefunction(s) for diagram number 1215
      // (none)

      // Amplitude(s) for diagram number 1215
      VVV1_0( w_sv[1], w_sv[8], w_sv[72], COUPs[0], &amp_sv[0] );
      jamp_sv[17] -= amp_sv[0];
      jamp_sv[23] += +amp_sv[0];
      jamp_sv[27] += +amp_sv[0];
      jamp_sv[29] -= amp_sv[0];
      jamp_sv[30] -= amp_sv[0];
      jamp_sv[31] += +amp_sv[0];
      jamp_sv[33] += +amp_sv[0];
      jamp_sv[35] -= amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[46] += +amp_sv[0];
      jamp_sv[51] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[64] -= amp_sv[0];
      jamp_sv[70] += +amp_sv[0];
      jamp_sv[91] += +amp_sv[0];
      jamp_sv[115] -= amp_sv[0];
      VVV1_0( w_sv[1], w_sv[8], w_sv[60], COUPs[0], &amp_sv[0] );
      jamp_sv[23] += +amp_sv[0];
      jamp_sv[29] -= amp_sv[0];
      jamp_sv[31] += +amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[33] += +amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[37] += +amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[43] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[61] += +amp_sv[0];
      jamp_sv[64] -= amp_sv[0];
      jamp_sv[67] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[91] += +amp_sv[0];
      jamp_sv[101] -= amp_sv[0];
      VVV1_0( w_sv[1], w_sv[8], w_sv[24], COUPs[0], &amp_sv[0] );
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[27] -= amp_sv[0];
      jamp_sv[30] += +amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[37] += +amp_sv[0];
      jamp_sv[43] += +amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[61] += +amp_sv[0];
      jamp_sv[67] += +amp_sv[0];
      jamp_sv[70] -= amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[101] -= amp_sv[0];
      jamp_sv[115] += +amp_sv[0];

      // *** DIAGRAM 1216 OF 1240 ***

      // Wavefunction(s) for diagram number 1216
      // (none)

      // Amplitude(s) for diagram number 1216
      FFV1_0( w_sv[3], w_sv[33], w_sv[61], COUPs[1], &amp_sv[0] );
      jamp_sv[51] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[53] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[54] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[55] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[57] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[59] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[64] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[70] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[33], w_sv[23], COUPs[1], &amp_sv[0] );
      jamp_sv[53] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[55] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[56] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[57] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[58] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[61] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[64] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[67] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[33], w_sv[68], COUPs[1], &amp_sv[0] );
      jamp_sv[51] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[54] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[56] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[58] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[59] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[61] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[67] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[70] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1217 OF 1240 ***

      // Wavefunction(s) for diagram number 1217
      // (none)

      // Amplitude(s) for diagram number 1217
      FFV1_0( w_sv[71], w_sv[33], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[54] += +amp_sv[0];
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[57] -= amp_sv[0];
      jamp_sv[59] += +amp_sv[0];
      FFV1_0( w_sv[21], w_sv[33], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[55] -= amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[57] -= amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      FFV1_0( w_sv[66], w_sv[33], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[54] -= amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];

      // *** DIAGRAM 1218 OF 1240 ***

      // Wavefunction(s) for diagram number 1218
      // (none)

      // Amplitude(s) for diagram number 1218
      FFV1_0( w_sv[46], w_sv[2], w_sv[61], COUPs[1], &amp_sv[0] );
      jamp_sv[16] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[22] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[27] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[29] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[40] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[46] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[90] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[114] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[46], w_sv[2], w_sv[23], COUPs[1], &amp_sv[0] );
      jamp_sv[22] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[29] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[37] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[40] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[43] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[76] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[90] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[100] -= cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[46], w_sv[2], w_sv[68], COUPs[1], &amp_sv[0] );
      jamp_sv[16] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[27] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[37] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[43] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[46] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[76] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[100] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[114] += +cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1219 OF 1240 ***

      // Wavefunction(s) for diagram number 1219
      // (none)

      // Amplitude(s) for diagram number 1219
      FFV1_0( w_sv[46], w_sv[77], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[16] += +amp_sv[0];
      jamp_sv[22] -= amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[114] += +amp_sv[0];
      FFV1_0( w_sv[46], w_sv[16], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[22] -= amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[90] -= amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      FFV1_0( w_sv[46], w_sv[27], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      jamp_sv[114] -= amp_sv[0];

      // *** DIAGRAM 1220 OF 1240 ***

      // Wavefunction(s) for diagram number 1220
      // (none)

      // Amplitude(s) for diagram number 1220
      VVVV1_0( w_sv[0], w_sv[73], w_sv[8], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[14] += +amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[38] += +amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[86] -= amp_sv[0];
      jamp_sv[96] -= amp_sv[0];
      jamp_sv[97] += +amp_sv[0];
      jamp_sv[99] += +amp_sv[0];
      jamp_sv[101] -= amp_sv[0];
      jamp_sv[105] += +amp_sv[0];
      jamp_sv[107] -= amp_sv[0];
      jamp_sv[113] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];
      VVVV3_0( w_sv[0], w_sv[73], w_sv[8], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[14] += +amp_sv[0];
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[19] += +amp_sv[0];
      jamp_sv[21] += +amp_sv[0];
      jamp_sv[23] -= amp_sv[0];
      jamp_sv[33] -= amp_sv[0];
      jamp_sv[39] += +amp_sv[0];
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[105] += +amp_sv[0];
      jamp_sv[107] -= amp_sv[0];
      jamp_sv[113] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];
      VVVV4_0( w_sv[0], w_sv[73], w_sv[8], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[19] += +amp_sv[0];
      jamp_sv[21] += +amp_sv[0];
      jamp_sv[23] -= amp_sv[0];
      jamp_sv[32] += +amp_sv[0];
      jamp_sv[33] -= amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[39] += +amp_sv[0];
      jamp_sv[62] -= amp_sv[0];
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[97] -= amp_sv[0];
      jamp_sv[99] -= amp_sv[0];
      jamp_sv[101] += +amp_sv[0];
      VVVV1_0( w_sv[0], w_sv[79], w_sv[8], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[6] += +amp_sv[0];
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[12] += +amp_sv[0];
      jamp_sv[38] += +amp_sv[0];
      jamp_sv[56] -= amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[80] -= amp_sv[0];
      jamp_sv[97] += +amp_sv[0];
      jamp_sv[98] -= amp_sv[0];
      jamp_sv[99] += +amp_sv[0];
      jamp_sv[100] -= amp_sv[0];
      jamp_sv[107] -= amp_sv[0];
      jamp_sv[111] += +amp_sv[0];
      jamp_sv[113] -= amp_sv[0];
      jamp_sv[117] += +amp_sv[0];
      VVVV3_0( w_sv[0], w_sv[79], w_sv[8], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[6] += +amp_sv[0];
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[12] += +amp_sv[0];
      jamp_sv[19] += +amp_sv[0];
      jamp_sv[20] -= amp_sv[0];
      jamp_sv[21] += +amp_sv[0];
      jamp_sv[22] -= amp_sv[0];
      jamp_sv[39] += +amp_sv[0];
      jamp_sv[57] -= amp_sv[0];
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[81] -= amp_sv[0];
      jamp_sv[107] -= amp_sv[0];
      jamp_sv[111] += +amp_sv[0];
      jamp_sv[113] -= amp_sv[0];
      jamp_sv[117] += +amp_sv[0];
      VVVV4_0( w_sv[0], w_sv[79], w_sv[8], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[19] += +amp_sv[0];
      jamp_sv[20] -= amp_sv[0];
      jamp_sv[21] += +amp_sv[0];
      jamp_sv[22] -= amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[39] += +amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[57] -= amp_sv[0];
      jamp_sv[62] -= amp_sv[0];
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[81] -= amp_sv[0];
      jamp_sv[97] -= amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      jamp_sv[99] -= amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      VVVV1_0( w_sv[0], w_sv[80], w_sv[8], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[0] -= amp_sv[0];
      jamp_sv[6] += +amp_sv[0];
      jamp_sv[12] += +amp_sv[0];
      jamp_sv[14] -= amp_sv[0];
      jamp_sv[32] += +amp_sv[0];
      jamp_sv[56] -= amp_sv[0];
      jamp_sv[80] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[98] -= amp_sv[0];
      jamp_sv[100] -= amp_sv[0];
      jamp_sv[101] += +amp_sv[0];
      jamp_sv[105] -= amp_sv[0];
      jamp_sv[111] += +amp_sv[0];
      jamp_sv[117] += +amp_sv[0];
      jamp_sv[119] -= amp_sv[0];
      VVVV3_0( w_sv[0], w_sv[80], w_sv[8], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[0] -= amp_sv[0];
      jamp_sv[6] += +amp_sv[0];
      jamp_sv[12] += +amp_sv[0];
      jamp_sv[14] -= amp_sv[0];
      jamp_sv[18] += +amp_sv[0];
      jamp_sv[20] -= amp_sv[0];
      jamp_sv[22] -= amp_sv[0];
      jamp_sv[23] += +amp_sv[0];
      jamp_sv[33] += +amp_sv[0];
      jamp_sv[57] -= amp_sv[0];
      jamp_sv[81] -= amp_sv[0];
      jamp_sv[87] += +amp_sv[0];
      jamp_sv[105] -= amp_sv[0];
      jamp_sv[111] += +amp_sv[0];
      jamp_sv[117] += +amp_sv[0];
      jamp_sv[119] -= amp_sv[0];
      VVVV4_0( w_sv[0], w_sv[80], w_sv[8], w_sv[6], COUPs[2], &amp_sv[0] );
      jamp_sv[18] += +amp_sv[0];
      jamp_sv[20] -= amp_sv[0];
      jamp_sv[22] -= amp_sv[0];
      jamp_sv[23] += +amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[33] += +amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[57] -= amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[81] -= amp_sv[0];
      jamp_sv[86] -= amp_sv[0];
      jamp_sv[87] += +amp_sv[0];
      jamp_sv[96] -= amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      jamp_sv[101] -= amp_sv[0];

      // *** DIAGRAM 1221 OF 1240 ***

      // Wavefunction(s) for diagram number 1221
      VVV1P0_1( w_sv[0], w_sv[73], COUPs[0], 0., 0., w_sv[27] );
      VVV1P0_1( w_sv[0], w_sv[79], COUPs[0], 0., 0., w_sv[1] );
      VVV1P0_1( w_sv[0], w_sv[80], COUPs[0], 0., 0., w_sv[16] );

      // Amplitude(s) for diagram number 1221
      VVV1_0( w_sv[8], w_sv[6], w_sv[27], COUPs[0], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[14] += +amp_sv[0];
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[38] += +amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[86] -= amp_sv[0];
      jamp_sv[96] -= amp_sv[0];
      jamp_sv[97] += +amp_sv[0];
      jamp_sv[99] += +amp_sv[0];
      jamp_sv[101] -= amp_sv[0];
      jamp_sv[105] += +amp_sv[0];
      jamp_sv[107] -= amp_sv[0];
      jamp_sv[113] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];
      VVV1_0( w_sv[8], w_sv[6], w_sv[1], COUPs[0], &amp_sv[0] );
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[6] += +amp_sv[0];
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[12] += +amp_sv[0];
      jamp_sv[38] += +amp_sv[0];
      jamp_sv[56] -= amp_sv[0];
      jamp_sv[62] += +amp_sv[0];
      jamp_sv[80] -= amp_sv[0];
      jamp_sv[97] += +amp_sv[0];
      jamp_sv[98] -= amp_sv[0];
      jamp_sv[99] += +amp_sv[0];
      jamp_sv[100] -= amp_sv[0];
      jamp_sv[107] -= amp_sv[0];
      jamp_sv[111] += +amp_sv[0];
      jamp_sv[113] -= amp_sv[0];
      jamp_sv[117] += +amp_sv[0];
      VVV1_0( w_sv[8], w_sv[6], w_sv[16], COUPs[0], &amp_sv[0] );
      jamp_sv[0] -= amp_sv[0];
      jamp_sv[6] += +amp_sv[0];
      jamp_sv[12] += +amp_sv[0];
      jamp_sv[14] -= amp_sv[0];
      jamp_sv[32] += +amp_sv[0];
      jamp_sv[56] -= amp_sv[0];
      jamp_sv[80] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[98] -= amp_sv[0];
      jamp_sv[100] -= amp_sv[0];
      jamp_sv[101] += +amp_sv[0];
      jamp_sv[105] -= amp_sv[0];
      jamp_sv[111] += +amp_sv[0];
      jamp_sv[117] += +amp_sv[0];
      jamp_sv[119] -= amp_sv[0];

      // *** DIAGRAM 1222 OF 1240 ***

      // Wavefunction(s) for diagram number 1222
      // (none)

      // Amplitude(s) for diagram number 1222
      VVV1_0( w_sv[73], w_sv[6], w_sv[56], COUPs[0], &amp_sv[0] );
      jamp_sv[0] += +amp_sv[0];
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[14] += +amp_sv[0];
      jamp_sv[18] -= amp_sv[0];
      jamp_sv[19] += +amp_sv[0];
      jamp_sv[21] += +amp_sv[0];
      jamp_sv[23] -= amp_sv[0];
      jamp_sv[33] -= amp_sv[0];
      jamp_sv[39] += +amp_sv[0];
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[87] -= amp_sv[0];
      jamp_sv[105] += +amp_sv[0];
      jamp_sv[107] -= amp_sv[0];
      jamp_sv[113] -= amp_sv[0];
      jamp_sv[119] += +amp_sv[0];
      VVV1_0( w_sv[79], w_sv[6], w_sv[56], COUPs[0], &amp_sv[0] );
      jamp_sv[2] -= amp_sv[0];
      jamp_sv[6] += +amp_sv[0];
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[12] += +amp_sv[0];
      jamp_sv[19] += +amp_sv[0];
      jamp_sv[20] -= amp_sv[0];
      jamp_sv[21] += +amp_sv[0];
      jamp_sv[22] -= amp_sv[0];
      jamp_sv[39] += +amp_sv[0];
      jamp_sv[57] -= amp_sv[0];
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[81] -= amp_sv[0];
      jamp_sv[107] -= amp_sv[0];
      jamp_sv[111] += +amp_sv[0];
      jamp_sv[113] -= amp_sv[0];
      jamp_sv[117] += +amp_sv[0];
      VVV1_0( w_sv[80], w_sv[6], w_sv[56], COUPs[0], &amp_sv[0] );
      jamp_sv[0] -= amp_sv[0];
      jamp_sv[6] += +amp_sv[0];
      jamp_sv[12] += +amp_sv[0];
      jamp_sv[14] -= amp_sv[0];
      jamp_sv[18] += +amp_sv[0];
      jamp_sv[20] -= amp_sv[0];
      jamp_sv[22] -= amp_sv[0];
      jamp_sv[23] += +amp_sv[0];
      jamp_sv[33] += +amp_sv[0];
      jamp_sv[57] -= amp_sv[0];
      jamp_sv[81] -= amp_sv[0];
      jamp_sv[87] += +amp_sv[0];
      jamp_sv[105] -= amp_sv[0];
      jamp_sv[111] += +amp_sv[0];
      jamp_sv[117] += +amp_sv[0];
      jamp_sv[119] -= amp_sv[0];

      // *** DIAGRAM 1223 OF 1240 ***

      // Wavefunction(s) for diagram number 1223
      // (none)

      // Amplitude(s) for diagram number 1223
      FFV1_0( w_sv[3], w_sv[47], w_sv[27], COUPs[1], &amp_sv[0] );
      jamp_sv[96] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[97] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[99] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[101] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[105] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[107] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[113] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[119] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[47], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[97] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[98] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[99] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[100] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[107] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[111] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[113] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[117] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[47], w_sv[16], COUPs[1], &amp_sv[0] );
      jamp_sv[96] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[98] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[100] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[101] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[105] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[111] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[117] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[119] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1224 OF 1240 ***

      // Wavefunction(s) for diagram number 1224
      // (none)

      // Amplitude(s) for diagram number 1224
      FFV1_0( w_sv[3], w_sv[113], w_sv[73], COUPs[1], &amp_sv[0] );
      jamp_sv[96] += +amp_sv[0];
      jamp_sv[97] -= amp_sv[0];
      jamp_sv[99] -= amp_sv[0];
      jamp_sv[101] += +amp_sv[0];
      FFV1_0( w_sv[3], w_sv[113], w_sv[79], COUPs[1], &amp_sv[0] );
      jamp_sv[97] -= amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      jamp_sv[99] -= amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      FFV1_0( w_sv[3], w_sv[113], w_sv[80], COUPs[1], &amp_sv[0] );
      jamp_sv[96] -= amp_sv[0];
      jamp_sv[98] += +amp_sv[0];
      jamp_sv[100] += +amp_sv[0];
      jamp_sv[101] -= amp_sv[0];

      // *** DIAGRAM 1225 OF 1240 ***

      // Wavefunction(s) for diagram number 1225
      // (none)

      // Amplitude(s) for diagram number 1225
      FFV1_0( w_sv[41], w_sv[2], w_sv[27], COUPs[1], &amp_sv[0] );
      jamp_sv[0] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[2] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[8] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[14] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[32] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[38] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[62] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[86] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[41], w_sv[2], w_sv[1], COUPs[1], &amp_sv[0] );
      jamp_sv[2] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[6] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[8] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[12] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[38] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[56] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[62] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[80] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[41], w_sv[2], w_sv[16], COUPs[1], &amp_sv[0] );
      jamp_sv[0] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[6] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[12] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[14] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[32] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[56] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[80] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[86] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1226 OF 1240 ***

      // Wavefunction(s) for diagram number 1226
      // (none)

      // Amplitude(s) for diagram number 1226
      FFV1_0( w_sv[62], w_sv[2], w_sv[73], COUPs[1], &amp_sv[0] );
      jamp_sv[32] += +amp_sv[0];
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[62] -= amp_sv[0];
      jamp_sv[86] += +amp_sv[0];
      FFV1_0( w_sv[62], w_sv[2], w_sv[79], COUPs[1], &amp_sv[0] );
      jamp_sv[38] -= amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[62] -= amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      FFV1_0( w_sv[62], w_sv[2], w_sv[80], COUPs[1], &amp_sv[0] );
      jamp_sv[32] -= amp_sv[0];
      jamp_sv[56] += +amp_sv[0];
      jamp_sv[80] += +amp_sv[0];
      jamp_sv[86] -= amp_sv[0];

      // *** DIAGRAM 1227 OF 1240 ***

      // Wavefunction(s) for diagram number 1227
      // (none)

      // Amplitude(s) for diagram number 1227
      VVVV1_0( w_sv[0], w_sv[57], w_sv[8], w_sv[5], COUPs[2], &amp_sv[0] );
      jamp_sv[1] += +amp_sv[0];
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[20] += +amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[44] += +amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[72] -= amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[75] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[81] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[89] -= amp_sv[0];
      jamp_sv[95] += +amp_sv[0];
      jamp_sv[110] -= amp_sv[0];
      VVVV3_0( w_sv[0], w_sv[57], w_sv[8], w_sv[5], COUPs[2], &amp_sv[0] );
      jamp_sv[1] += +amp_sv[0];
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[15] += +amp_sv[0];
      jamp_sv[17] -= amp_sv[0];
      jamp_sv[20] += +amp_sv[0];
      jamp_sv[35] -= amp_sv[0];
      jamp_sv[45] += +amp_sv[0];
      jamp_sv[69] += +amp_sv[0];
      jamp_sv[81] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[89] -= amp_sv[0];
      jamp_sv[95] += +amp_sv[0];
      jamp_sv[111] -= amp_sv[0];
      VVVV4_0( w_sv[0], w_sv[57], w_sv[8], w_sv[5], COUPs[2], &amp_sv[0] );
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[15] += +amp_sv[0];
      jamp_sv[17] -= amp_sv[0];
      jamp_sv[34] += +amp_sv[0];
      jamp_sv[35] -= amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[45] += +amp_sv[0];
      jamp_sv[68] -= amp_sv[0];
      jamp_sv[69] += +amp_sv[0];
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[73] -= amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[77] += +amp_sv[0];
      jamp_sv[110] += +amp_sv[0];
      jamp_sv[111] -= amp_sv[0];
      VVVV1_0( w_sv[0], w_sv[81], w_sv[8], w_sv[5], COUPs[2], &amp_sv[0] );
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[18] += +amp_sv[0];
      jamp_sv[44] += +amp_sv[0];
      jamp_sv[58] -= amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[74] -= amp_sv[0];
      jamp_sv[75] += +amp_sv[0];
      jamp_sv[76] -= amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[87] += +amp_sv[0];
      jamp_sv[89] -= amp_sv[0];
      jamp_sv[93] += +amp_sv[0];
      jamp_sv[104] -= amp_sv[0];
      VVVV3_0( w_sv[0], w_sv[81], w_sv[8], w_sv[5], COUPs[2], &amp_sv[0] );
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[14] -= amp_sv[0];
      jamp_sv[15] += +amp_sv[0];
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[18] += +amp_sv[0];
      jamp_sv[45] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[69] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[87] += +amp_sv[0];
      jamp_sv[89] -= amp_sv[0];
      jamp_sv[93] += +amp_sv[0];
      jamp_sv[105] -= amp_sv[0];
      VVVV4_0( w_sv[0], w_sv[81], w_sv[8], w_sv[5], COUPs[2], &amp_sv[0] );
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[14] -= amp_sv[0];
      jamp_sv[15] += +amp_sv[0];
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[45] += +amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[68] -= amp_sv[0];
      jamp_sv[69] += +amp_sv[0];
      jamp_sv[73] -= amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[105] -= amp_sv[0];
      VVVV1_0( w_sv[0], w_sv[82], w_sv[8], w_sv[5], COUPs[2], &amp_sv[0] );
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[18] += +amp_sv[0];
      jamp_sv[20] -= amp_sv[0];
      jamp_sv[34] += +amp_sv[0];
      jamp_sv[58] -= amp_sv[0];
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[74] -= amp_sv[0];
      jamp_sv[76] -= amp_sv[0];
      jamp_sv[77] += +amp_sv[0];
      jamp_sv[81] -= amp_sv[0];
      jamp_sv[87] += +amp_sv[0];
      jamp_sv[93] += +amp_sv[0];
      jamp_sv[95] -= amp_sv[0];
      jamp_sv[104] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];
      VVVV3_0( w_sv[0], w_sv[82], w_sv[8], w_sv[5], COUPs[2], &amp_sv[0] );
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[12] += +amp_sv[0];
      jamp_sv[14] -= amp_sv[0];
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[18] += +amp_sv[0];
      jamp_sv[20] -= amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[81] -= amp_sv[0];
      jamp_sv[87] += +amp_sv[0];
      jamp_sv[93] += +amp_sv[0];
      jamp_sv[95] -= amp_sv[0];
      jamp_sv[105] -= amp_sv[0];
      jamp_sv[111] += +amp_sv[0];
      VVVV4_0( w_sv[0], w_sv[82], w_sv[8], w_sv[5], COUPs[2], &amp_sv[0] );
      jamp_sv[12] += +amp_sv[0];
      jamp_sv[14] -= amp_sv[0];
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[72] -= amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[105] -= amp_sv[0];
      jamp_sv[110] -= amp_sv[0];
      jamp_sv[111] += +amp_sv[0];

      // *** DIAGRAM 1228 OF 1240 ***

      // Wavefunction(s) for diagram number 1228
      VVV1P0_1( w_sv[0], w_sv[57], COUPs[0], 0., 0., w_sv[62] );
      VVV1P0_1( w_sv[0], w_sv[81], COUPs[0], 0., 0., w_sv[80] );
      VVV1P0_1( w_sv[0], w_sv[82], COUPs[0], 0., 0., w_sv[79] );

      // Amplitude(s) for diagram number 1228
      VVV1_0( w_sv[8], w_sv[5], w_sv[62], COUPs[0], &amp_sv[0] );
      jamp_sv[1] += +amp_sv[0];
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[20] += +amp_sv[0];
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[44] += +amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[72] -= amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[75] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];
      jamp_sv[81] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[89] -= amp_sv[0];
      jamp_sv[95] += +amp_sv[0];
      jamp_sv[110] -= amp_sv[0];
      VVV1_0( w_sv[8], w_sv[5], w_sv[80], COUPs[0], &amp_sv[0] );
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[18] += +amp_sv[0];
      jamp_sv[44] += +amp_sv[0];
      jamp_sv[58] -= amp_sv[0];
      jamp_sv[68] += +amp_sv[0];
      jamp_sv[73] += +amp_sv[0];
      jamp_sv[74] -= amp_sv[0];
      jamp_sv[75] += +amp_sv[0];
      jamp_sv[76] -= amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[87] += +amp_sv[0];
      jamp_sv[89] -= amp_sv[0];
      jamp_sv[93] += +amp_sv[0];
      jamp_sv[104] -= amp_sv[0];
      VVV1_0( w_sv[8], w_sv[5], w_sv[79], COUPs[0], &amp_sv[0] );
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[18] += +amp_sv[0];
      jamp_sv[20] -= amp_sv[0];
      jamp_sv[34] += +amp_sv[0];
      jamp_sv[58] -= amp_sv[0];
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[74] -= amp_sv[0];
      jamp_sv[76] -= amp_sv[0];
      jamp_sv[77] += +amp_sv[0];
      jamp_sv[81] -= amp_sv[0];
      jamp_sv[87] += +amp_sv[0];
      jamp_sv[93] += +amp_sv[0];
      jamp_sv[95] -= amp_sv[0];
      jamp_sv[104] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];

      // *** DIAGRAM 1229 OF 1240 ***

      // Wavefunction(s) for diagram number 1229
      // (none)

      // Amplitude(s) for diagram number 1229
      VVV1_0( w_sv[57], w_sv[5], w_sv[56], COUPs[0], &amp_sv[0] );
      jamp_sv[1] += +amp_sv[0];
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[12] -= amp_sv[0];
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[15] += +amp_sv[0];
      jamp_sv[17] -= amp_sv[0];
      jamp_sv[20] += +amp_sv[0];
      jamp_sv[35] -= amp_sv[0];
      jamp_sv[45] += +amp_sv[0];
      jamp_sv[69] += +amp_sv[0];
      jamp_sv[81] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[89] -= amp_sv[0];
      jamp_sv[95] += +amp_sv[0];
      jamp_sv[111] -= amp_sv[0];
      VVV1_0( w_sv[81], w_sv[5], w_sv[56], COUPs[0], &amp_sv[0] );
      jamp_sv[4] -= amp_sv[0];
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[14] -= amp_sv[0];
      jamp_sv[15] += +amp_sv[0];
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[18] += +amp_sv[0];
      jamp_sv[45] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[69] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[87] += +amp_sv[0];
      jamp_sv[89] -= amp_sv[0];
      jamp_sv[93] += +amp_sv[0];
      jamp_sv[105] -= amp_sv[0];
      VVV1_0( w_sv[82], w_sv[5], w_sv[56], COUPs[0], &amp_sv[0] );
      jamp_sv[1] -= amp_sv[0];
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[12] += +amp_sv[0];
      jamp_sv[14] -= amp_sv[0];
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[17] += +amp_sv[0];
      jamp_sv[18] += +amp_sv[0];
      jamp_sv[20] -= amp_sv[0];
      jamp_sv[35] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[81] -= amp_sv[0];
      jamp_sv[87] += +amp_sv[0];
      jamp_sv[93] += +amp_sv[0];
      jamp_sv[95] -= amp_sv[0];
      jamp_sv[105] -= amp_sv[0];
      jamp_sv[111] += +amp_sv[0];

      // *** DIAGRAM 1230 OF 1240 ***

      // Wavefunction(s) for diagram number 1230
      // (none)

      // Amplitude(s) for diagram number 1230
      FFV1_0( w_sv[3], w_sv[39], w_sv[62], COUPs[1], &amp_sv[0] );
      jamp_sv[72] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[73] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[75] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[77] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[81] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[83] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[89] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[95] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[39], w_sv[80], COUPs[1], &amp_sv[0] );
      jamp_sv[73] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[74] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[75] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[76] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[83] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[87] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[89] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[93] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[39], w_sv[79], COUPs[1], &amp_sv[0] );
      jamp_sv[72] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[74] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[76] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[77] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[81] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[87] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[93] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[95] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1231 OF 1240 ***

      // Wavefunction(s) for diagram number 1231
      // (none)

      // Amplitude(s) for diagram number 1231
      FFV1_0( w_sv[3], w_sv[102], w_sv[57], COUPs[1], &amp_sv[0] );
      jamp_sv[72] += +amp_sv[0];
      jamp_sv[73] -= amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[77] += +amp_sv[0];
      FFV1_0( w_sv[3], w_sv[102], w_sv[81], COUPs[1], &amp_sv[0] );
      jamp_sv[73] -= amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[75] -= amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      FFV1_0( w_sv[3], w_sv[102], w_sv[82], COUPs[1], &amp_sv[0] );
      jamp_sv[72] -= amp_sv[0];
      jamp_sv[74] += +amp_sv[0];
      jamp_sv[76] += +amp_sv[0];
      jamp_sv[77] -= amp_sv[0];

      // *** DIAGRAM 1232 OF 1240 ***

      // Wavefunction(s) for diagram number 1232
      // (none)

      // Amplitude(s) for diagram number 1232
      FFV1_0( w_sv[38], w_sv[2], w_sv[62], COUPs[1], &amp_sv[0] );
      jamp_sv[1] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[4] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[10] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[20] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[34] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[44] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[68] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[110] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[38], w_sv[2], w_sv[80], COUPs[1], &amp_sv[0] );
      jamp_sv[4] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[7] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[10] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[18] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[44] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[58] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[68] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[104] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[38], w_sv[2], w_sv[79], COUPs[1], &amp_sv[0] );
      jamp_sv[1] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[7] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[18] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[20] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[34] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[58] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[104] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[110] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1233 OF 1240 ***

      // Wavefunction(s) for diagram number 1233
      // (none)

      // Amplitude(s) for diagram number 1233
      FFV1_0( w_sv[104], w_sv[2], w_sv[57], COUPs[1], &amp_sv[0] );
      jamp_sv[34] += +amp_sv[0];
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[68] -= amp_sv[0];
      jamp_sv[110] += +amp_sv[0];
      FFV1_0( w_sv[104], w_sv[2], w_sv[81], COUPs[1], &amp_sv[0] );
      jamp_sv[44] -= amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[68] -= amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      FFV1_0( w_sv[104], w_sv[2], w_sv[82], COUPs[1], &amp_sv[0] );
      jamp_sv[34] -= amp_sv[0];
      jamp_sv[58] += +amp_sv[0];
      jamp_sv[104] += +amp_sv[0];
      jamp_sv[110] -= amp_sv[0];

      // *** DIAGRAM 1234 OF 1240 ***

      // Wavefunction(s) for diagram number 1234
      // (none)

      // Amplitude(s) for diagram number 1234
      VVVV1_0( w_sv[0], w_sv[55], w_sv[8], w_sv[4], COUPs[2], &amp_sv[0] );
      jamp_sv[3] += +amp_sv[0];
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[22] += +amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[46] += +amp_sv[0];
      jamp_sv[48] -= amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[51] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[57] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[71] += +amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[116] -= amp_sv[0];
      VVVV3_0( w_sv[0], w_sv[55], w_sv[8], w_sv[4], COUPs[2], &amp_sv[0] );
      jamp_sv[3] += +amp_sv[0];
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[11] -= amp_sv[0];
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[22] += +amp_sv[0];
      jamp_sv[41] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[57] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[71] += +amp_sv[0];
      jamp_sv[93] += +amp_sv[0];
      jamp_sv[117] -= amp_sv[0];
      VVVV4_0( w_sv[0], w_sv[55], w_sv[8], w_sv[4], COUPs[2], &amp_sv[0] );
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[11] -= amp_sv[0];
      jamp_sv[40] += +amp_sv[0];
      jamp_sv[41] -= amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[49] -= amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[53] += +amp_sv[0];
      jamp_sv[92] -= amp_sv[0];
      jamp_sv[93] += +amp_sv[0];
      jamp_sv[116] += +amp_sv[0];
      jamp_sv[117] -= amp_sv[0];
      VVVV1_0( w_sv[0], w_sv[83], w_sv[8], w_sv[4], COUPs[2], &amp_sv[0] );
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[19] += +amp_sv[0];
      jamp_sv[46] += +amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[50] -= amp_sv[0];
      jamp_sv[51] += +amp_sv[0];
      jamp_sv[52] -= amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[69] += +amp_sv[0];
      jamp_sv[82] -= amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[106] -= amp_sv[0];
      VVVV3_0( w_sv[0], w_sv[83], w_sv[8], w_sv[4], COUPs[2], &amp_sv[0] );
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[19] += +amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[69] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[93] += +amp_sv[0];
      jamp_sv[107] -= amp_sv[0];
      VVVV4_0( w_sv[0], w_sv[83], w_sv[8], w_sv[4], COUPs[2], &amp_sv[0] );
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[49] -= amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[92] -= amp_sv[0];
      jamp_sv[93] += +amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      jamp_sv[107] -= amp_sv[0];
      VVVV1_0( w_sv[0], w_sv[84], w_sv[8], w_sv[4], COUPs[2], &amp_sv[0] );
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[19] += +amp_sv[0];
      jamp_sv[22] -= amp_sv[0];
      jamp_sv[40] += +amp_sv[0];
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[50] -= amp_sv[0];
      jamp_sv[52] -= amp_sv[0];
      jamp_sv[53] += +amp_sv[0];
      jamp_sv[57] -= amp_sv[0];
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[69] += +amp_sv[0];
      jamp_sv[71] -= amp_sv[0];
      jamp_sv[82] -= amp_sv[0];
      jamp_sv[106] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];
      VVVV3_0( w_sv[0], w_sv[84], w_sv[8], w_sv[4], COUPs[2], &amp_sv[0] );
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[6] += +amp_sv[0];
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[19] += +amp_sv[0];
      jamp_sv[22] -= amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[57] -= amp_sv[0];
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[69] += +amp_sv[0];
      jamp_sv[71] -= amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[107] -= amp_sv[0];
      jamp_sv[117] += +amp_sv[0];
      VVVV4_0( w_sv[0], w_sv[84], w_sv[8], w_sv[4], COUPs[2], &amp_sv[0] );
      jamp_sv[6] += +amp_sv[0];
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[48] -= amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      jamp_sv[107] -= amp_sv[0];
      jamp_sv[116] -= amp_sv[0];
      jamp_sv[117] += +amp_sv[0];

      // *** DIAGRAM 1235 OF 1240 ***

      // Wavefunction(s) for diagram number 1235
      VVV1P0_1( w_sv[0], w_sv[55], COUPs[0], 0., 0., w_sv[104] );
      VVV1P0_1( w_sv[0], w_sv[83], COUPs[0], 0., 0., w_sv[82] );
      VVV1P0_1( w_sv[0], w_sv[84], COUPs[0], 0., 0., w_sv[81] );

      // Amplitude(s) for diagram number 1235
      VVV1_0( w_sv[8], w_sv[4], w_sv[104], COUPs[0], &amp_sv[0] );
      jamp_sv[3] += +amp_sv[0];
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[22] += +amp_sv[0];
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[46] += +amp_sv[0];
      jamp_sv[48] -= amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[51] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];
      jamp_sv[57] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[71] += +amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[116] -= amp_sv[0];
      VVV1_0( w_sv[8], w_sv[4], w_sv[82], COUPs[0], &amp_sv[0] );
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[19] += +amp_sv[0];
      jamp_sv[46] += +amp_sv[0];
      jamp_sv[49] += +amp_sv[0];
      jamp_sv[50] -= amp_sv[0];
      jamp_sv[51] += +amp_sv[0];
      jamp_sv[52] -= amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[69] += +amp_sv[0];
      jamp_sv[82] -= amp_sv[0];
      jamp_sv[92] += +amp_sv[0];
      jamp_sv[106] -= amp_sv[0];
      VVV1_0( w_sv[8], w_sv[4], w_sv[81], COUPs[0], &amp_sv[0] );
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[19] += +amp_sv[0];
      jamp_sv[22] -= amp_sv[0];
      jamp_sv[40] += +amp_sv[0];
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[50] -= amp_sv[0];
      jamp_sv[52] -= amp_sv[0];
      jamp_sv[53] += +amp_sv[0];
      jamp_sv[57] -= amp_sv[0];
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[69] += +amp_sv[0];
      jamp_sv[71] -= amp_sv[0];
      jamp_sv[82] -= amp_sv[0];
      jamp_sv[106] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];

      // *** DIAGRAM 1236 OF 1240 ***

      // Wavefunction(s) for diagram number 1236
      // (none)

      // Amplitude(s) for diagram number 1236
      VVV1_0( w_sv[55], w_sv[4], w_sv[56], COUPs[0], &amp_sv[0] );
      jamp_sv[3] += +amp_sv[0];
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[6] -= amp_sv[0];
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[11] -= amp_sv[0];
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[22] += +amp_sv[0];
      jamp_sv[41] -= amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[57] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[71] += +amp_sv[0];
      jamp_sv[93] += +amp_sv[0];
      jamp_sv[117] -= amp_sv[0];
      VVV1_0( w_sv[83], w_sv[4], w_sv[56], COUPs[0], &amp_sv[0] );
      jamp_sv[5] -= amp_sv[0];
      jamp_sv[7] += +amp_sv[0];
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[9] += +amp_sv[0];
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[16] -= amp_sv[0];
      jamp_sv[19] += +amp_sv[0];
      jamp_sv[47] += +amp_sv[0];
      jamp_sv[59] -= amp_sv[0];
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[65] -= amp_sv[0];
      jamp_sv[69] += +amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[93] += +amp_sv[0];
      jamp_sv[107] -= amp_sv[0];
      VVV1_0( w_sv[84], w_sv[4], w_sv[56], COUPs[0], &amp_sv[0] );
      jamp_sv[3] -= amp_sv[0];
      jamp_sv[6] += +amp_sv[0];
      jamp_sv[8] -= amp_sv[0];
      jamp_sv[10] -= amp_sv[0];
      jamp_sv[11] += +amp_sv[0];
      jamp_sv[13] += +amp_sv[0];
      jamp_sv[19] += +amp_sv[0];
      jamp_sv[22] -= amp_sv[0];
      jamp_sv[41] += +amp_sv[0];
      jamp_sv[57] -= amp_sv[0];
      jamp_sv[63] += +amp_sv[0];
      jamp_sv[69] += +amp_sv[0];
      jamp_sv[71] -= amp_sv[0];
      jamp_sv[83] -= amp_sv[0];
      jamp_sv[107] -= amp_sv[0];
      jamp_sv[117] += +amp_sv[0];

      // *** DIAGRAM 1237 OF 1240 ***

      // Wavefunction(s) for diagram number 1237
      // (none)

      // Amplitude(s) for diagram number 1237
      FFV1_0( w_sv[3], w_sv[33], w_sv[104], COUPs[1], &amp_sv[0] );
      jamp_sv[48] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[49] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[51] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[53] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[57] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[59] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[65] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[71] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[33], w_sv[82], COUPs[1], &amp_sv[0] );
      jamp_sv[49] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[50] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[51] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[52] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[59] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[63] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[65] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[69] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[3], w_sv[33], w_sv[81], COUPs[1], &amp_sv[0] );
      jamp_sv[48] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[50] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[52] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[53] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[57] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[63] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[69] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[71] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1238 OF 1240 ***

      // Wavefunction(s) for diagram number 1238
      // (none)

      // Amplitude(s) for diagram number 1238
      FFV1_0( w_sv[3], w_sv[114], w_sv[55], COUPs[1], &amp_sv[0] );
      jamp_sv[48] += +amp_sv[0];
      jamp_sv[49] -= amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[53] += +amp_sv[0];
      FFV1_0( w_sv[3], w_sv[114], w_sv[83], COUPs[1], &amp_sv[0] );
      jamp_sv[49] -= amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[51] -= amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      FFV1_0( w_sv[3], w_sv[114], w_sv[84], COUPs[1], &amp_sv[0] );
      jamp_sv[48] -= amp_sv[0];
      jamp_sv[50] += +amp_sv[0];
      jamp_sv[52] += +amp_sv[0];
      jamp_sv[53] -= amp_sv[0];

      // *** DIAGRAM 1239 OF 1240 ***

      // Wavefunction(s) for diagram number 1239
      // (none)

      // Amplitude(s) for diagram number 1239
      FFV1_0( w_sv[46], w_sv[2], w_sv[104], COUPs[1], &amp_sv[0] );
      jamp_sv[3] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[5] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[16] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[22] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[40] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[46] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[92] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[116] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[46], w_sv[2], w_sv[82], COUPs[1], &amp_sv[0] );
      jamp_sv[5] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[13] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[16] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[19] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[46] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[82] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[92] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[106] += +cxtype(0,1)*amp_sv[0];
      FFV1_0( w_sv[46], w_sv[2], w_sv[81], COUPs[1], &amp_sv[0] );
      jamp_sv[3] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[13] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[19] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[22] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[40] -= cxtype(0,1)*amp_sv[0];
      jamp_sv[82] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[106] += +cxtype(0,1)*amp_sv[0];
      jamp_sv[116] -= cxtype(0,1)*amp_sv[0];

      // *** DIAGRAM 1240 OF 1240 ***

      // Wavefunction(s) for diagram number 1240
      // (none)

      // Amplitude(s) for diagram number 1240
      FFV1_0( w_sv[99], w_sv[2], w_sv[55], COUPs[1], &amp_sv[0] );
      jamp_sv[40] += +amp_sv[0];
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[92] -= amp_sv[0];
      jamp_sv[116] += +amp_sv[0];
      FFV1_0( w_sv[99], w_sv[2], w_sv[83], COUPs[1], &amp_sv[0] );
      jamp_sv[46] -= amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[92] -= amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      FFV1_0( w_sv[99], w_sv[2], w_sv[84], COUPs[1], &amp_sv[0] );
      jamp_sv[40] -= amp_sv[0];
      jamp_sv[82] += +amp_sv[0];
      jamp_sv[106] += +amp_sv[0];
      jamp_sv[116] -= amp_sv[0];

      // *** COLOR ALGEBRA BELOW ***
      // (This method used to be called CPPProcess::matrix_1_gg_ttxggg()?)

      // The color matrix (initialize all array elements, with ncolor=1)
      // [NB do keep 'static' for these constexpr arrays, see issue #283]
      static constexpr fptype denom[ncolor] = {324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324, 324};
      static constexpr fptype cf[ncolor][ncolor] = {
      {4096, -512, -512, 64, 64, 640, -512, 64, 64, -8, -8, -80, 64, -8, 640, -80, 568, 496, -8, -80, -80, 496, 496, -224, -512, 64, 64, -8, -8, -80, 64, -8, -8, 1, 1, 10, -8, 1, -80, 10, -71, -62, 1, 10, 10, -62, -62, 28, 64, -8, -8, 1, 1, 10, 640, -80, -80, 10, 10, 100, 568, -71, 496, -62, 505, 514, -71, 19, -62, -53, -134, -44, -8, 1, -80, 10, -71, -62, -80, 10, 496, -62, 19, -53, 496, -62, -224, 28, -134, -44, 505, -134, -134, 442, 442, -116, 1, 10, 10, -62, -62, 28, 10, 100, -62, 514, -53, -44, -62, -53, 28, -44, 442, -116, 514, -44, -44, -116, -116, 136},
      {-512, 4096, 64, 640, -512, 64, 64, -512, -8, -80, 64, -8, -8, -80, -80, 496, 496, -224, 64, -8, 640, -80, 568, 496, 64, -512, -8, -80, 64, -8, -8, 64, 1, 10, -8, 1, 1, 10, 10, -62, -62, 28, -8, 1, -80, 10, -71, -62, -8, 64, 1, 10, -8, 1, -80, 640, 10, 100, -80, 10, -71, 19, -62, -53, -134, -44, 568, -71, 496, -62, 505, 514, 1, 10, 10, -62, -62, 28, 10, 100, -62, 514, -53, -44, -62, -53, 28, -44, 442, -116, 514, -44, -44, -116, -116, 136, -8, 1, -80, 10, -71, -62, -80, 10, 496, -62, 19, -53, 496, -62, -224, 28, -134, -44, 505, -134, -134, 442, 442, -116},
      {-512, 64, 4096, -512, 640, 64, 64, -8, 640, -80, 568, 496, -512, 64, 64, -8, -8, -80, -80, -8, 496, -224, -80, 496, 64, -8, -512, 64, -80, -8, -8, 1, -80, 10, -71, -62, 64, -8, -8, 1, 1, 10, 10, 1, -62, 28, 10, -62, -8, 1, -80, 10, -71, -62, -80, 10, 496, -62, 19, -53, 496, -62, -224, 28, -134, -44, 505, -134, -134, 442, 442, -116, 64, -8, -8, 1, 1, 10, 640, -80, -80, 10, 10, 100, 568, -71, 496, -62, 505, 514, -71, 19, -62, -53, -134, -44, 10, 1, -62, 28, 10, -62, 100, 10, -53, -44, -62, 514, 514, -44, -44, -116, -116, 136, -62, -53, 28, -44, 442, -116},
      {64, 640, -512, 4096, 64, -512, -8, -80, -80, 496, 496, -224, 64, -512, -8, -80, 64, -8, -8, 64, 568, 496, 640, -80, -8, -80, 64, -512, -8, 64, 1, 10, 10, -62, -62, 28, -8, 64, 1, 10, -8, 1, 1, -8, -71, -62, -80, 10, 1, 10, 10, -62, -62, 28, 10, 100, -62, 514, -53, -44, -62, -53, 28, -44, 442, -116, 514, -44, -44, -116, -116, 136, -8, 64, 1, 10, -8, 1, -80, 640, 10, 100, -80, 10, -71, 19, -62, -53, -134, -44, 568, -71, 496, -62, 505, 514, 1, -8, -71, -62, -80, 10, 10, -80, 19, -53, 496, -62, 505, -134, -134, 442, 442, -116, 496, -62, -224, 28, -134, -44},
      {64, -512, 640, 64, 4096, -512, -8, 64, 568, 496, 640, -80, -80, -8, 496, -224, -80, 496, -512, 64, 64, -8, -8, -80, -8, 64, -80, -8, -512, 64, 1, -8, -71, -62, -80, 10, 10, 1, -62, 28, 10, -62, 64, -8, -8, 1, 1, 10, 1, -8, -71, -62, -80, 10, 10, -80, 19, -53, 496, -62, 505, -134, -134, 442, 442, -116, 496, -62, -224, 28, -134, -44, 10, 1, -62, 28, 10, -62, 100, 10, -53, -44, -62, 514, 514, -44, -44, -116, -116, 136, -62, -53, 28, -44, 442, -116, 64, -8, -8, 1, 1, 10, 640, -80, -80, 10, 10, 100, 568, -71, 496, -62, 505, 514, -71, 19, -62, -53, -134, -44},
      {640, 64, 64, -512, -512, 4096, -80, -8, 496, -224, -80, 496, -8, 64, 568, 496, 640, -80, 64, -512, -8, -80, 64, -8, -80, -8, -8, 64, 64, -512, 10, 1, -62, 28, 10, -62, 1, -8, -71, -62, -80, 10, -8, 64, 1, 10, -8, 1, 10, 1, -62, 28, 10, -62, 100, 10, -53, -44, -62, 514, 514, -44, -44, -116, -116, 136, -62, -53, 28, -44, 442, -116, 1, -8, -71, -62, -80, 10, 10, -80, 19, -53, 496, -62, 505, -134, -134, 442, 442, -116, 496, -62, -224, 28, -134, -44, -8, 64, 1, 10, -8, 1, -80, 640, 10, 100, -80, 10, -71, 19, -62, -53, -134, -44, 568, -71, 496, -62, 505, 514},
      {-512, 64, 64, -8, -8, -80, 4096, -512, -512, 64, 64, 640, 640, -80, 64, -8, 496, 568, -80, 496, -8, -80, -224, 496, 64, -8, -8, 1, 1, 10, 640, -80, -80, 10, 10, 100, 568, -71, 496, -62, 505, 514, -71, 19, -62, -53, -134, -44, -512, 64, 64, -8, -8, -80, 64, -8, -8, 1, 1, 10, -8, 1, -80, 10, -71, -62, 1, 10, 10, -62, -62, 28, -80, 10, -8, 1, -62, -71, 496, -62, -224, 28, -134, -44, -80, 10, 496, -62, 19, -53, -134, 505, 442, -116, -134, 442, 10, -62, 1, 10, 28, -62, -62, -53, 28, -44, 442, -116, 10, 100, -62, 514, -53, -44, -44, 514, -116, 136, -44, -116},
      {64, -512, -8, -80, 64, -8, -512, 4096, 64, 640, -512, 64, -80, 496, -8, -80, -224, 496, 640, -80, 64, -8, 496, 568, -8, 64, 1, 10, -8, 1, -80, 640, 10, 100, -80, 10, -71, 19, -62, -53, -134, -44, 568, -71, 496, -62, 505, 514, 64, -512, -8, -80, 64, -8, -8, 64, 1, 10, -8, 1, 1, 10, 10, -62, -62, 28, -8, 1, -80, 10, -71, -62, 10, -62, 1, 10, 28, -62, -62, -53, 28, -44, 442, -116, 10, 100, -62, 514, -53, -44, -44, 514, -116, 136, -44, -116, -80, 10, -8, 1, -62, -71, 496, -62, -224, 28, -134, -44, -80, 10, 496, -62, 19, -53, -134, 505, 442, -116, -134, 442},
      {64, -8, 640, -80, 568, 496, -512, 64, 4096, -512, 640, 64, 64, -8, -512, 64, -80, -8, 496, -224, -80, -8, 496, -80, -8, 1, -80, 10, -71, -62, -80, 10, 496, -62, 19, -53, 496, -62, -224, 28, -134, -44, 505, -134, -134, 442, 442, -116, 64, -8, -512, 64, -80, -8, -8, 1, -80, 10, -71, -62, 64, -8, -8, 1, 1, 10, 10, 1, -62, 28, 10, -62, -8, 1, 64, -8, 10, 1, 568, -71, 496, -62, 505, 514, 640, -80, -80, 10, 10, 100, 19, -71, -134, -44, -62, -53, -62, 28, 10, 1, -62, 10, 514, -44, -44, -116, -116, 136, 100, 10, -53, -44, -62, 514, -53, -62, 442, -116, 28, -44},
      {-8, -80, -80, 496, 496, -224, 64, 640, -512, 4096, 64, -512, -8, -80, 64, -512, -8, 64, 568, 496, -8, 64, -80, 640, 1, 10, 10, -62, -62, 28, 10, 100, -62, 514, -53, -44, -62, -53, 28, -44, 442, -116, 514, -44, -44, -116, -116, 136, -8, -80, 64, -512, -8, 64, 1, 10, 10, -62, -62, 28, -8, 64, 1, 10, -8, 1, 1, -8, -71, -62, -80, 10, 1, 10, -8, 64, 1, -8, -71, 19, -62, -53, -134, -44, -80, 640, 10, 100, -80, 10, -71, 568, 505, 514, 496, -62, -71, -62, 1, -8, 10, -80, 505, -134, -134, 442, 442, -116, 10, -80, 19, -53, 496, -62, -62, 496, -134, -44, -224, 28},
      {-8, 64, 568, 496, 640, -80, 64, -512, 640, 64, 4096, -512, 496, -224, -80, -8, 496, -80, 64, -8, -512, 64, -80, -8, 1, -8, -71, -62, -80, 10, 10, -80, 19, -53, 496, -62, 505, -134, -134, 442, 442, -116, 496, -62, -224, 28, -134, -44, -8, 64, -80, -8, -512, 64, 1, -8, -71, -62, -80, 10, 10, 1, -62, 28, 10, -62, 64, -8, -8, 1, 1, 10, -62, 28, 10, 1, -62, 10, 514, -44, -44, -116, -116, 136, 100, 10, -53, -44, -62, 514, -53, -62, 442, -116, 28, -44, -8, 1, 64, -8, 10, 1, 568, -71, 496, -62, 505, 514, 640, -80, -80, 10, 10, 100, 19, -71, -134, -44, -62, -53},
      {-80, -8, 496, -224, -80, 496, 640, 64, 64, -512, -512, 4096, 568, 496, -8, 64, -80, 640, -8, -80, 64, -512, -8, 64, 10, 1, -62, 28, 10, -62, 100, 10, -53, -44, -62, 514, 514, -44, -44, -116, -116, 136, -62, -53, 28, -44, 442, -116, -80, -8, -8, 64, 64, -512, 10, 1, -62, 28, 10, -62, 1, -8, -71, -62, -80, 10, -8, 64, 1, 10, -8, 1, -71, -62, 1, -8, 10, -80, 505, -134, -134, 442, 442, -116, 10, -80, 19, -53, 496, -62, -62, 496, -134, -44, -224, 28, 1, 10, -8, 64, 1, -8, -71, 19, -62, -53, -134, -44, -80, 640, 10, 100, -80, 10, -71, 568, 505, 514, 496, -62},
      {64, -8, -512, 64, -80, -8, 640, -80, 64, -8, 496, 568, 4096, -512, -512, 64, 64, 640, 496, -80, -224, 496, -8, -80, -8, 1, 64, -8, 10, 1, 568, -71, 496, -62, 505, 514, 640, -80, -80, 10, 10, 100, 19, -71, -134, -44, -62, -53, -80, 10, -8, 1, -62, -71, 496, -62, -224, 28, -134, -44, -80, 10, 496, -62, 19, -53, -134, 505, 442, -116, -134, 442, -512, 64, 64, -8, -8, -80, 64, -8, -8, 1, 1, 10, -8, 1, -80, 10, -71, -62, 1, 10, 10, -62, -62, 28, -62, 10, 28, -62, 1, 10, -53, -62, 442, -116, 28, -44, -44, 514, -116, 136, -44, -116, 10, 100, -62, 514, -53, -44},
      {-8, -80, 64, -512, -8, 64, -80, 496, -8, -80, -224, 496, -512, 4096, 64, 640, -512, 64, -80, 640, 496, 568, 64, -8, 1, 10, -8, 64, 1, -8, -71, 19, -62, -53, -134, -44, -80, 640, 10, 100, -80, 10, -71, 568, 505, 514, 496, -62, 10, -62, 1, 10, 28, -62, -62, -53, 28, -44, 442, -116, 10, 100, -62, 514, -53, -44, -44, 514, -116, 136, -44, -116, 64, -512, -8, -80, 64, -8, -8, 64, 1, 10, -8, 1, 1, 10, 10, -62, -62, 28, -8, 1, -80, 10, -71, -62, 10, -80, -62, -71, -8, 1, -62, 496, -134, -44, -224, 28, -134, 505, 442, -116, -134, 442, -80, 10, 496, -62, 19, -53},
      {640, -80, 64, -8, 496, 568, 64, -8, -512, 64, -80, -8, -512, 64, 4096, -512, 640, 64, -224, 496, 496, -80, -80, -8, -80, 10, -8, 1, -62, -71, 496, -62, -224, 28, -134, -44, -80, 10, 496, -62, 19, -53, -134, 505, 442, -116, -134, 442, -8, 1, 64, -8, 10, 1, 568, -71, 496, -62, 505, 514, 640, -80, -80, 10, 10, 100, 19, -71, -134, -44, -62, -53, 64, -8, -512, 64, -80, -8, -8, 1, -80, 10, -71, -62, 64, -8, -8, 1, 1, 10, 10, 1, -62, 28, 10, -62, 28, -62, -62, 10, 10, 1, -44, 514, -116, 136, -44, -116, -53, -62, 442, -116, 28, -44, 100, 10, -53, -44, -62, 514},
      {-80, 496, -8, -80, -224, 496, -8, -80, 64, -512, -8, 64, 64, 640, -512, 4096, 64, -512, 496, 568, -80, 640, -8, 64, 10, -62, 1, 10, 28, -62, -62, -53, 28, -44, 442, -116, 10, 100, -62, 514, -53, -44, -44, 514, -116, 136, -44, -116, 1, 10, -8, 64, 1, -8, -71, 19, -62, -53, -134, -44, -80, 640, 10, 100, -80, 10, -71, 568, 505, 514, 496, -62, -8, -80, 64, -512, -8, 64, 1, 10, 10, -62, -62, 28, -8, 64, 1, 10, -8, 1, 1, -8, -71, -62, -80, 10, -62, -71, 10, -80, 1, -8, -134, 505, 442, -116, -134, 442, -62, 496, -134, -44, -224, 28, 10, -80, 19, -53, 496, -62},
      {568, 496, -8, 64, -80, 640, 496, -224, -80, -8, 496, -80, 64, -512, 640, 64, 4096, -512, -8, 64, -80, -8, -512, 64, -71, -62, 1, -8, 10, -80, 505, -134, -134, 442, 442, -116, 10, -80, 19, -53, 496, -62, -62, 496, -134, -44, -224, 28, -62, 28, 10, 1, -62, 10, 514, -44, -44, -116, -116, 136, 100, 10, -53, -44, -62, 514, -53, -62, 442, -116, 28, -44, -8, 64, -80, -8, -512, 64, 1, -8, -71, -62, -80, 10, 10, 1, -62, 28, 10, -62, 64, -8, -8, 1, 1, 10, 1, -8, 10, 1, 64, -8, -71, 568, 505, 514, 496, -62, 19, -71, -134, -44, -62, -53, 640, -80, -80, 10, 10, 100},
      {496, -224, -80, -8, 496, -80, 568, 496, -8, 64, -80, 640, 640, 64, 64, -512, -512, 4096, -80, -8, -8, 64, 64, -512, -62, 28, 10, 1, -62, 10, 514, -44, -44, -116, -116, 136, 100, 10, -53, -44, -62, 514, -53, -62, 442, -116, 28, -44, -71, -62, 1, -8, 10, -80, 505, -134, -134, 442, 442, -116, 10, -80, 19, -53, 496, -62, -62, 496, -134, -44, -224, 28, -80, -8, -8, 64, 64, -512, 10, 1, -62, 28, 10, -62, 1, -8, -71, -62, -80, 10, -8, 64, 1, 10, -8, 1, 10, 1, 1, -8, -8, 64, 19, -71, -134, -44, -62, -53, -71, 568, 505, 514, 496, -62, -80, 640, 10, 100, -80, 10},
      {-8, 64, -80, -8, -512, 64, -80, 640, 496, 568, 64, -8, 496, -80, -224, 496, -8, -80, 4096, -512, -512, 64, 64, 640, 1, -8, 10, 1, 64, -8, -71, 568, 505, 514, 496, -62, 19, -71, -134, -44, -62, -53, 640, -80, -80, 10, 10, 100, 10, -80, -62, -71, -8, 1, -62, 496, -134, -44, -224, 28, -134, 505, 442, -116, -134, 442, -80, 10, 496, -62, 19, -53, -62, 10, 28, -62, 1, 10, -53, -62, 442, -116, 28, -44, -44, 514, -116, 136, -44, -116, 10, 100, -62, 514, -53, -44, -512, 64, 64, -8, -8, -80, 64, -8, -8, 1, 1, 10, -8, 1, -80, 10, -71, -62, 1, 10, 10, -62, -62, 28},
      {-80, -8, -8, 64, 64, -512, 496, -80, -224, 496, -8, -80, -80, 640, 496, 568, 64, -8, -512, 4096, 64, 640, -512, 64, 10, 1, 1, -8, -8, 64, 19, -71, -134, -44, -62, -53, -71, 568, 505, 514, 496, -62, -80, 640, 10, 100, -80, 10, -62, 10, 28, -62, 1, 10, -53, -62, 442, -116, 28, -44, -44, 514, -116, 136, -44, -116, 10, 100, -62, 514, -53, -44, 10, -80, -62, -71, -8, 1, -62, 496, -134, -44, -224, 28, -134, 505, 442, -116, -134, 442, -80, 10, 496, -62, 19, -53, 64, -512, -8, -80, 64, -8, -8, 64, 1, 10, -8, 1, 1, 10, 10, -62, -62, 28, -8, 1, -80, 10, -71, -62},
      {-80, 640, 496, 568, 64, -8, -8, 64, -80, -8, -512, 64, -224, 496, 496, -80, -80, -8, -512, 64, 4096, -512, 640, 64, 10, -80, -62, -71, -8, 1, -62, 496, -134, -44, -224, 28, -134, 505, 442, -116, -134, 442, -80, 10, 496, -62, 19, -53, 1, -8, 10, 1, 64, -8, -71, 568, 505, 514, 496, -62, 19, -71, -134, -44, -62, -53, 640, -80, -80, 10, 10, 100, 28, -62, -62, 10, 10, 1, -44, 514, -116, 136, -44, -116, -53, -62, 442, -116, 28, -44, 100, 10, -53, -44, -62, 514, 64, -8, -512, 64, -80, -8, -8, 1, -80, 10, -71, -62, 64, -8, -8, 1, 1, 10, 10, 1, -62, 28, 10, -62},
      {496, -80, -224, 496, -8, -80, -80, -8, -8, 64, 64, -512, 496, 568, -80, 640, -8, 64, 64, 640, -512, 4096, 64, -512, -62, 10, 28, -62, 1, 10, -53, -62, 442, -116, 28, -44, -44, 514, -116, 136, -44, -116, 10, 100, -62, 514, -53, -44, 10, 1, 1, -8, -8, 64, 19, -71, -134, -44, -62, -53, -71, 568, 505, 514, 496, -62, -80, 640, 10, 100, -80, 10, -62, -71, 10, -80, 1, -8, -134, 505, 442, -116, -134, 442, -62, 496, -134, -44, -224, 28, 10, -80, 19, -53, 496, -62, -8, -80, 64, -512, -8, 64, 1, 10, 10, -62, -62, 28, -8, 64, 1, 10, -8, 1, 1, -8, -71, -62, -80, 10},
      {496, 568, -80, 640, -8, 64, -224, 496, 496, -80, -80, -8, -8, 64, -80, -8, -512, 64, 64, -512, 640, 64, 4096, -512, -62, -71, 10, -80, 1, -8, -134, 505, 442, -116, -134, 442, -62, 496, -134, -44, -224, 28, 10, -80, 19, -53, 496, -62, 28, -62, -62, 10, 10, 1, -44, 514, -116, 136, -44, -116, -53, -62, 442, -116, 28, -44, 100, 10, -53, -44, -62, 514, 1, -8, 10, 1, 64, -8, -71, 568, 505, 514, 496, -62, 19, -71, -134, -44, -62, -53, 640, -80, -80, 10, 10, 100, -8, 64, -80, -8, -512, 64, 1, -8, -71, -62, -80, 10, 10, 1, -62, 28, 10, -62, 64, -8, -8, 1, 1, 10},
      {-224, 496, 496, -80, -80, -8, 496, 568, -80, 640, -8, 64, -80, -8, -8, 64, 64, -512, 640, 64, 64, -512, -512, 4096, 28, -62, -62, 10, 10, 1, -44, 514, -116, 136, -44, -116, -53, -62, 442, -116, 28, -44, 100, 10, -53, -44, -62, 514, -62, -71, 10, -80, 1, -8, -134, 505, 442, -116, -134, 442, -62, 496, -134, -44, -224, 28, 10, -80, 19, -53, 496, -62, 10, 1, 1, -8, -8, 64, 19, -71, -134, -44, -62, -53, -71, 568, 505, 514, 496, -62, -80, 640, 10, 100, -80, 10, -80, -8, -8, 64, 64, -512, 10, 1, -62, 28, 10, -62, 1, -8, -71, -62, -80, 10, -8, 64, 1, 10, -8, 1},
      {-512, 64, 64, -8, -8, -80, 64, -8, -8, 1, 1, 10, -8, 1, -80, 10, -71, -62, 1, 10, 10, -62, -62, 28, 4096, -512, -512, 64, 64, 640, -512, 64, 64, -8, -8, -80, 64, -8, 640, -80, 568, 496, -8, -80, -80, 496, 496, -224, 640, -80, -80, 10, 10, 100, 64, -8, -8, 1, 1, 10, 496, -62, 568, -71, 514, 505, -62, -53, -71, 19, -44, -134, -80, 10, 496, -62, 19, -53, -8, 1, -80, 10, -71, -62, -224, 28, 496, -62, -44, -134, -134, 442, 505, -134, -116, 442, 10, 100, -62, 514, -53, -44, 1, 10, 10, -62, -62, 28, 28, -44, -62, -53, -116, 442, -44, -116, 514, -44, 136, -116},
      {64, -512, -8, -80, 64, -8, -8, 64, 1, 10, -8, 1, 1, 10, 10, -62, -62, 28, -8, 1, -80, 10, -71, -62, -512, 4096, 64, 640, -512, 64, 64, -512, -8, -80, 64, -8, -8, -80, -80, 496, 496, -224, 64, -8, 640, -80, 568, 496, -80, 640, 10, 100, -80, 10, -8, 64, 1, 10, -8, 1, -62, -53, -71, 19, -44, -134, 496, -62, 568, -71, 514, 505, 10, 100, -62, 514, -53, -44, 1, 10, 10, -62, -62, 28, 28, -44, -62, -53, -116, 442, -44, -116, 514, -44, 136, -116, -80, 10, 496, -62, 19, -53, -8, 1, -80, 10, -71, -62, -224, 28, 496, -62, -44, -134, -134, 442, 505, -134, -116, 442},
      {64, -8, -512, 64, -80, -8, -8, 1, -80, 10, -71, -62, 64, -8, -8, 1, 1, 10, 10, 1, -62, 28, 10, -62, -512, 64, 4096, -512, 640, 64, 64, -8, 640, -80, 568, 496, -512, 64, 64, -8, -8, -80, -80, -8, 496, -224, -80, 496, -80, 10, 496, -62, 19, -53, -8, 1, -80, 10, -71, -62, -224, 28, 496, -62, -44, -134, -134, 442, 505, -134, -116, 442, 640, -80, -80, 10, 10, 100, 64, -8, -8, 1, 1, 10, 496, -62, 568, -71, 514, 505, -62, -53, -71, 19, -44, -134, 100, 10, -53, -44, -62, 514, 10, 1, -62, 28, 10, -62, -44, -116, 514, -44, 136, -116, 28, -44, -62, -53, -116, 442},
      {-8, -80, 64, -512, -8, 64, 1, 10, 10, -62, -62, 28, -8, 64, 1, 10, -8, 1, 1, -8, -71, -62, -80, 10, 64, 640, -512, 4096, 64, -512, -8, -80, -80, 496, 496, -224, 64, -512, -8, -80, 64, -8, -8, 64, 568, 496, 640, -80, 10, 100, -62, 514, -53, -44, 1, 10, 10, -62, -62, 28, 28, -44, -62, -53, -116, 442, -44, -116, 514, -44, 136, -116, -80, 640, 10, 100, -80, 10, -8, 64, 1, 10, -8, 1, -62, -53, -71, 19, -44, -134, 496, -62, 568, -71, 514, 505, 10, -80, 19, -53, 496, -62, 1, -8, -71, -62, -80, 10, -134, 442, 505, -134, -116, 442, -224, 28, 496, -62, -44, -134},
      {-8, 64, -80, -8, -512, 64, 1, -8, -71, -62, -80, 10, 10, 1, -62, 28, 10, -62, 64, -8, -8, 1, 1, 10, 64, -512, 640, 64, 4096, -512, -8, 64, 568, 496, 640, -80, -80, -8, 496, -224, -80, 496, -512, 64, 64, -8, -8, -80, 10, -80, 19, -53, 496, -62, 1, -8, -71, -62, -80, 10, -134, 442, 505, -134, -116, 442, -224, 28, 496, -62, -44, -134, 100, 10, -53, -44, -62, 514, 10, 1, -62, 28, 10, -62, -44, -116, 514, -44, 136, -116, 28, -44, -62, -53, -116, 442, 640, -80, -80, 10, 10, 100, 64, -8, -8, 1, 1, 10, 496, -62, 568, -71, 514, 505, -62, -53, -71, 19, -44, -134},
      {-80, -8, -8, 64, 64, -512, 10, 1, -62, 28, 10, -62, 1, -8, -71, -62, -80, 10, -8, 64, 1, 10, -8, 1, 640, 64, 64, -512, -512, 4096, -80, -8, 496, -224, -80, 496, -8, 64, 568, 496, 640, -80, 64, -512, -8, -80, 64, -8, 100, 10, -53, -44, -62, 514, 10, 1, -62, 28, 10, -62, -44, -116, 514, -44, 136, -116, 28, -44, -62, -53, -116, 442, 10, -80, 19, -53, 496, -62, 1, -8, -71, -62, -80, 10, -134, 442, 505, -134, -116, 442, -224, 28, 496, -62, -44, -134, -80, 640, 10, 100, -80, 10, -8, 64, 1, 10, -8, 1, -62, -53, -71, 19, -44, -134, 496, -62, 568, -71, 514, 505},
      {64, -8, -8, 1, 1, 10, 640, -80, -80, 10, 10, 100, 568, -71, 496, -62, 505, 514, -71, 19, -62, -53, -134, -44, -512, 64, 64, -8, -8, -80, 4096, -512, -512, 64, 64, 640, 640, -80, 64, -8, 496, 568, -80, 496, -8, -80, -224, 496, 64, -8, -8, 1, 1, 10, -512, 64, 64, -8, -8, -80, -80, 10, -8, 1, -62, -71, 10, -62, 1, 10, 28, -62, 496, -62, -224, 28, -134, -44, -80, 10, -8, 1, -62, -71, 496, -62, -80, 10, -53, 19, 442, -116, -134, 505, 442, -134, -62, -53, 28, -44, 442, -116, 10, -62, 1, 10, 28, -62, -62, 514, 10, 100, -44, -53, -116, 136, -44, 514, -116, -44},
      {-8, 64, 1, 10, -8, 1, -80, 640, 10, 100, -80, 10, -71, 19, -62, -53, -134, -44, 568, -71, 496, -62, 505, 514, 64, -512, -8, -80, 64, -8, -512, 4096, 64, 640, -512, 64, -80, 496, -8, -80, -224, 496, 640, -80, 64, -8, 496, 568, -8, 64, 1, 10, -8, 1, 64, -512, -8, -80, 64, -8, 10, -62, 1, 10, 28, -62, -80, 10, -8, 1, -62, -71, -62, -53, 28, -44, 442, -116, 10, -62, 1, 10, 28, -62, -62, 514, 10, 100, -44, -53, -116, 136, -44, 514, -116, -44, 496, -62, -224, 28, -134, -44, -80, 10, -8, 1, -62, -71, 496, -62, -80, 10, -53, 19, 442, -116, -134, 505, 442, -134},
      {-8, 1, -80, 10, -71, -62, -80, 10, 496, -62, 19, -53, 496, -62, -224, 28, -134, -44, 505, -134, -134, 442, 442, -116, 64, -8, 640, -80, 568, 496, -512, 64, 4096, -512, 640, 64, 64, -8, -512, 64, -80, -8, 496, -224, -80, -8, 496, -80, -8, 1, -80, 10, -71, -62, 64, -8, -512, 64, -80, -8, -8, 1, 64, -8, 10, 1, -62, 28, 10, 1, -62, 10, 568, -71, 496, -62, 505, 514, -8, 1, 64, -8, 10, 1, -80, 10, 640, -80, 100, 10, -134, -44, 19, -71, -53, -62, 514, -44, -44, -116, -116, 136, -62, 28, 10, 1, -62, 10, -53, -44, 100, 10, 514, -62, 442, -116, -53, -62, -44, 28},
      {1, 10, 10, -62, -62, 28, 10, 100, -62, 514, -53, -44, -62, -53, 28, -44, 442, -116, 514, -44, -44, -116, -116, 136, -8, -80, -80, 496, 496, -224, 64, 640, -512, 4096, 64, -512, -8, -80, 64, -512, -8, 64, 568, 496, -8, 64, -80, 640, 1, 10, 10, -62, -62, 28, -8, -80, 64, -512, -8, 64, 1, 10, -8, 64, 1, -8, -71, -62, 1, -8, 10, -80, -71, 19, -62, -53, -134, -44, 1, 10, -8, 64, 1, -8, 10, 100, -80, 640, 10, -80, 505, 514, -71, 568, -62, 496, 505, -134, -134, 442, 442, -116, -71, -62, 1, -8, 10, -80, 19, -53, 10, -80, -62, 496, -134, -44, -62, 496, 28, -224},
      {1, -8, -71, -62, -80, 10, 10, -80, 19, -53, 496, -62, 505, -134, -134, 442, 442, -116, 496, -62, -224, 28, -134, -44, -8, 64, 568, 496, 640, -80, 64, -512, 640, 64, 4096, -512, 496, -224, -80, -8, 496, -80, 64, -8, -512, 64, -80, -8, 1, -8, -71, -62, -80, 10, -8, 64, -80, -8, -512, 64, -62, 28, 10, 1, -62, 10, -8, 1, 64, -8, 10, 1, 514, -44, -44, -116, -116, 136, -62, 28, 10, 1, -62, 10, -53, -44, 100, 10, 514, -62, 442, -116, -53, -62, -44, 28, 568, -71, 496, -62, 505, 514, -8, 1, 64, -8, 10, 1, -80, 10, 640, -80, 100, 10, -134, -44, 19, -71, -53, -62},
      {10, 1, -62, 28, 10, -62, 100, 10, -53, -44, -62, 514, 514, -44, -44, -116, -116, 136, -62, -53, 28, -44, 442, -116, -80, -8, 496, -224, -80, 496, 640, 64, 64, -512, -512, 4096, 568, 496, -8, 64, -80, 640, -8, -80, 64, -512, -8, 64, 10, 1, -62, 28, 10, -62, -80, -8, -8, 64, 64, -512, -71, -62, 1, -8, 10, -80, 1, 10, -8, 64, 1, -8, 505, -134, -134, 442, 442, -116, -71, -62, 1, -8, 10, -80, 19, -53, 10, -80, -62, 496, -134, -44, -62, 496, 28, -224, -71, 19, -62, -53, -134, -44, 1, 10, -8, 64, 1, -8, 10, 100, -80, 640, 10, -80, 505, 514, -71, 568, -62, 496},
      {-8, 1, 64, -8, 10, 1, 568, -71, 496, -62, 505, 514, 640, -80, -80, 10, 10, 100, 19, -71, -134, -44, -62, -53, 64, -8, -512, 64, -80, -8, 640, -80, 64, -8, 496, 568, 4096, -512, -512, 64, 64, 640, 496, -80, -224, 496, -8, -80, 496, -62, -224, 28, -134, -44, -80, 10, -8, 1, -62, -71, 496, -62, -80, 10, -53, 19, 442, -116, -134, 505, 442, -134, 64, -8, -8, 1, 1, 10, -512, 64, 64, -8, -8, -80, -80, 10, -8, 1, -62, -71, 10, -62, 1, 10, 28, -62, -53, -62, 442, -116, 28, -44, -62, 10, 28, -62, 1, 10, -116, 136, -44, 514, -116, -44, -62, 514, 10, 100, -44, -53},
      {1, 10, -8, 64, 1, -8, -71, 19, -62, -53, -134, -44, -80, 640, 10, 100, -80, 10, -71, 568, 505, 514, 496, -62, -8, -80, 64, -512, -8, 64, -80, 496, -8, -80, -224, 496, -512, 4096, 64, 640, -512, 64, -80, 640, 496, 568, 64, -8, -62, -53, 28, -44, 442, -116, 10, -62, 1, 10, 28, -62, -62, 514, 10, 100, -44, -53, -116, 136, -44, 514, -116, -44, -8, 64, 1, 10, -8, 1, 64, -512, -8, -80, 64, -8, 10, -62, 1, 10, 28, -62, -80, 10, -8, 1, -62, -71, -62, 496, -134, -44, -224, 28, 10, -80, -62, -71, -8, 1, 442, -116, -134, 505, 442, -134, 496, -62, -80, 10, -53, 19},
      {-80, 10, -8, 1, -62, -71, 496, -62, -224, 28, -134, -44, -80, 10, 496, -62, 19, -53, -134, 505, 442, -116, -134, 442, 640, -80, 64, -8, 496, 568, 64, -8, -512, 64, -80, -8, -512, 64, 4096, -512, 640, 64, -224, 496, 496, -80, -80, -8, 568, -71, 496, -62, 505, 514, -8, 1, 64, -8, 10, 1, -80, 10, 640, -80, 100, 10, -134, -44, 19, -71, -53, -62, -8, 1, -80, 10, -71, -62, 64, -8, -512, 64, -80, -8, -8, 1, 64, -8, 10, 1, -62, 28, 10, 1, -62, 10, -44, 514, -116, 136, -44, -116, 28, -62, -62, 10, 10, 1, 442, -116, -53, -62, -44, 28, -53, -44, 100, 10, 514, -62},
      {10, -62, 1, 10, 28, -62, -62, -53, 28, -44, 442, -116, 10, 100, -62, 514, -53, -44, -44, 514, -116, 136, -44, -116, -80, 496, -8, -80, -224, 496, -8, -80, 64, -512, -8, 64, 64, 640, -512, 4096, 64, -512, 496, 568, -80, 640, -8, 64, -71, 19, -62, -53, -134, -44, 1, 10, -8, 64, 1, -8, 10, 100, -80, 640, 10, -80, 505, 514, -71, 568, -62, 496, 1, 10, 10, -62, -62, 28, -8, -80, 64, -512, -8, 64, 1, 10, -8, 64, 1, -8, -71, -62, 1, -8, 10, -80, -134, 505, 442, -116, -134, 442, -62, -71, 10, -80, 1, -8, -134, -44, -62, 496, 28, -224, 19, -53, 10, -80, -62, 496},
      {-71, -62, 1, -8, 10, -80, 505, -134, -134, 442, 442, -116, 10, -80, 19, -53, 496, -62, -62, 496, -134, -44, -224, 28, 568, 496, -8, 64, -80, 640, 496, -224, -80, -8, 496, -80, 64, -512, 640, 64, 4096, -512, -8, 64, -80, -8, -512, 64, 514, -44, -44, -116, -116, 136, -62, 28, 10, 1, -62, 10, -53, -44, 100, 10, 514, -62, 442, -116, -53, -62, -44, 28, 1, -8, -71, -62, -80, 10, -8, 64, -80, -8, -512, 64, -62, 28, 10, 1, -62, 10, -8, 1, 64, -8, 10, 1, -71, 568, 505, 514, 496, -62, 1, -8, 10, 1, 64, -8, -134, -44, 19, -71, -53, -62, -80, 10, 640, -80, 100, 10},
      {-62, 28, 10, 1, -62, 10, 514, -44, -44, -116, -116, 136, 100, 10, -53, -44, -62, 514, -53, -62, 442, -116, 28, -44, 496, -224, -80, -8, 496, -80, 568, 496, -8, 64, -80, 640, 640, 64, 64, -512, -512, 4096, -80, -8, -8, 64, 64, -512, 505, -134, -134, 442, 442, -116, -71, -62, 1, -8, 10, -80, 19, -53, 10, -80, -62, 496, -134, -44, -62, 496, 28, -224, 10, 1, -62, 28, 10, -62, -80, -8, -8, 64, 64, -512, -71, -62, 1, -8, 10, -80, 1, 10, -8, 64, 1, -8, 19, -71, -134, -44, -62, -53, 10, 1, 1, -8, -8, 64, 505, 514, -71, 568, -62, 496, 10, 100, -80, 640, 10, -80},
      {1, -8, 10, 1, 64, -8, -71, 568, 505, 514, 496, -62, 19, -71, -134, -44, -62, -53, 640, -80, -80, 10, 10, 100, -8, 64, -80, -8, -512, 64, -80, 640, 496, 568, 64, -8, 496, -80, -224, 496, -8, -80, 4096, -512, -512, 64, 64, 640, -62, 496, -134, -44, -224, 28, 10, -80, -62, -71, -8, 1, 442, -116, -134, 505, 442, -134, 496, -62, -80, 10, -53, 19, -53, -62, 442, -116, 28, -44, -62, 10, 28, -62, 1, 10, -116, 136, -44, 514, -116, -44, -62, 514, 10, 100, -44, -53, 64, -8, -8, 1, 1, 10, -512, 64, 64, -8, -8, -80, -80, 10, -8, 1, -62, -71, 10, -62, 1, 10, 28, -62},
      {10, 1, 1, -8, -8, 64, 19, -71, -134, -44, -62, -53, -71, 568, 505, 514, 496, -62, -80, 640, 10, 100, -80, 10, -80, -8, -8, 64, 64, -512, 496, -80, -224, 496, -8, -80, -80, 640, 496, 568, 64, -8, -512, 4096, 64, 640, -512, 64, -53, -62, 442, -116, 28, -44, -62, 10, 28, -62, 1, 10, -116, 136, -44, 514, -116, -44, -62, 514, 10, 100, -44, -53, -62, 496, -134, -44, -224, 28, 10, -80, -62, -71, -8, 1, 442, -116, -134, 505, 442, -134, 496, -62, -80, 10, -53, 19, -8, 64, 1, 10, -8, 1, 64, -512, -8, -80, 64, -8, 10, -62, 1, 10, 28, -62, -80, 10, -8, 1, -62, -71},
      {10, -80, -62, -71, -8, 1, -62, 496, -134, -44, -224, 28, -134, 505, 442, -116, -134, 442, -80, 10, 496, -62, 19, -53, -80, 640, 496, 568, 64, -8, -8, 64, -80, -8, -512, 64, -224, 496, 496, -80, -80, -8, -512, 64, 4096, -512, 640, 64, -71, 568, 505, 514, 496, -62, 1, -8, 10, 1, 64, -8, -134, -44, 19, -71, -53, -62, -80, 10, 640, -80, 100, 10, -44, 514, -116, 136, -44, -116, 28, -62, -62, 10, 10, 1, 442, -116, -53, -62, -44, 28, -53, -44, 100, 10, 514, -62, -8, 1, -80, 10, -71, -62, 64, -8, -512, 64, -80, -8, -8, 1, 64, -8, 10, 1, -62, 28, 10, 1, -62, 10},
      {-62, 10, 28, -62, 1, 10, -53, -62, 442, -116, 28, -44, -44, 514, -116, 136, -44, -116, 10, 100, -62, 514, -53, -44, 496, -80, -224, 496, -8, -80, -80, -8, -8, 64, 64, -512, 496, 568, -80, 640, -8, 64, 64, 640, -512, 4096, 64, -512, 19, -71, -134, -44, -62, -53, 10, 1, 1, -8, -8, 64, 505, 514, -71, 568, -62, 496, 10, 100, -80, 640, 10, -80, -134, 505, 442, -116, -134, 442, -62, -71, 10, -80, 1, -8, -134, -44, -62, 496, 28, -224, 19, -53, 10, -80, -62, 496, 1, 10, 10, -62, -62, 28, -8, -80, 64, -512, -8, 64, 1, 10, -8, 64, 1, -8, -71, -62, 1, -8, 10, -80},
      {-62, -71, 10, -80, 1, -8, -134, 505, 442, -116, -134, 442, -62, 496, -134, -44, -224, 28, 10, -80, 19, -53, 496, -62, 496, 568, -80, 640, -8, 64, -224, 496, 496, -80, -80, -8, -8, 64, -80, -8, -512, 64, 64, -512, 640, 64, 4096, -512, -44, 514, -116, 136, -44, -116, 28, -62, -62, 10, 10, 1, 442, -116, -53, -62, -44, 28, -53, -44, 100, 10, 514, -62, -71, 568, 505, 514, 496, -62, 1, -8, 10, 1, 64, -8, -134, -44, 19, -71, -53, -62, -80, 10, 640, -80, 100, 10, 1, -8, -71, -62, -80, 10, -8, 64, -80, -8, -512, 64, -62, 28, 10, 1, -62, 10, -8, 1, 64, -8, 10, 1},
      {28, -62, -62, 10, 10, 1, -44, 514, -116, 136, -44, -116, -53, -62, 442, -116, 28, -44, 100, 10, -53, -44, -62, 514, -224, 496, 496, -80, -80, -8, 496, 568, -80, 640, -8, 64, -80, -8, -8, 64, 64, -512, 640, 64, 64, -512, -512, 4096, -134, 505, 442, -116, -134, 442, -62, -71, 10, -80, 1, -8, -134, -44, -62, 496, 28, -224, 19, -53, 10, -80, -62, 496, 19, -71, -134, -44, -62, -53, 10, 1, 1, -8, -8, 64, 505, 514, -71, 568, -62, 496, 10, 100, -80, 640, 10, -80, 10, 1, -62, 28, 10, -62, -80, -8, -8, 64, 64, -512, -71, -62, 1, -8, 10, -80, 1, 10, -8, 64, 1, -8},
      {64, -8, -8, 1, 1, 10, -512, 64, 64, -8, -8, -80, -80, 10, -8, 1, -62, -71, 10, -62, 1, 10, 28, -62, 640, -80, -80, 10, 10, 100, 64, -8, -8, 1, 1, 10, 496, -62, 568, -71, 514, 505, -62, -53, -71, 19, -44, -134, 4096, -512, -512, 64, 64, 640, -512, 64, 64, -8, -8, -80, 64, -8, 640, -80, 568, 496, -8, -80, -80, 496, 496, -224, 496, -62, -80, 10, -53, 19, -224, 28, 496, -62, -44, -134, -8, 1, -80, 10, -71, -62, 442, -134, -116, 442, 505, -134, -62, 514, 10, 100, -44, -53, 28, -44, -62, -53, -116, 442, 1, 10, 10, -62, -62, 28, -116, -44, 136, -116, 514, -44},
      {-8, 64, 1, 10, -8, 1, 64, -512, -8, -80, 64, -8, 10, -62, 1, 10, 28, -62, -80, 10, -8, 1, -62, -71, -80, 640, 10, 100, -80, 10, -8, 64, 1, 10, -8, 1, -62, -53, -71, 19, -44, -134, 496, -62, 568, -71, 514, 505, -512, 4096, 64, 640, -512, 64, 64, -512, -8, -80, 64, -8, -8, -80, -80, 496, 496, -224, 64, -8, 640, -80, 568, 496, -62, 514, 10, 100, -44, -53, 28, -44, -62, -53, -116, 442, 1, 10, 10, -62, -62, 28, -116, -44, 136, -116, 514, -44, 496, -62, -80, 10, -53, 19, -224, 28, 496, -62, -44, -134, -8, 1, -80, 10, -71, -62, 442, -134, -116, 442, 505, -134},
      {-8, 1, -80, 10, -71, -62, 64, -8, -512, 64, -80, -8, -8, 1, 64, -8, 10, 1, -62, 28, 10, 1, -62, 10, -80, 10, 496, -62, 19, -53, -8, 1, -80, 10, -71, -62, -224, 28, 496, -62, -44, -134, -134, 442, 505, -134, -116, 442, -512, 64, 4096, -512, 640, 64, 64, -8, 640, -80, 568, 496, -512, 64, 64, -8, -8, -80, -80, -8, 496, -224, -80, 496, -80, 10, 640, -80, 100, 10, 496, -62, 568, -71, 514, 505, 64, -8, -8, 1, 1, 10, -53, -62, -44, -134, -71, 19, -53, -44, 100, 10, 514, -62, -44, -116, 514, -44, 136, -116, 10, 1, -62, 28, 10, -62, -44, 28, -116, 442, -62, -53},
      {1, 10, 10, -62, -62, 28, -8, -80, 64, -512, -8, 64, 1, 10, -8, 64, 1, -8, -71, -62, 1, -8, 10, -80, 10, 100, -62, 514, -53, -44, 1, 10, 10, -62, -62, 28, 28, -44, -62, -53, -116, 442, -44, -116, 514, -44, 136, -116, 64, 640, -512, 4096, 64, -512, -8, -80, -80, 496, 496, -224, 64, -512, -8, -80, 64, -8, -8, 64, 568, 496, 640, -80, 10, 100, -80, 640, 10, -80, -62, -53, -71, 19, -44, -134, -8, 64, 1, 10, -8, 1, -62, 496, 514, 505, 568, -71, 19, -53, 10, -80, -62, 496, -134, 442, 505, -134, -116, 442, 1, -8, -71, -62, -80, 10, 28, -224, -44, -134, 496, -62},
      {1, -8, -71, -62, -80, 10, -8, 64, -80, -8, -512, 64, -62, 28, 10, 1, -62, 10, -8, 1, 64, -8, 10, 1, 10, -80, 19, -53, 496, -62, 1, -8, -71, -62, -80, 10, -134, 442, 505, -134, -116, 442, -224, 28, 496, -62, -44, -134, 64, -512, 640, 64, 4096, -512, -8, 64, 568, 496, 640, -80, -80, -8, 496, -224, -80, 496, -512, 64, 64, -8, -8, -80, -53, -44, 100, 10, 514, -62, -44, -116, 514, -44, 136, -116, 10, 1, -62, 28, 10, -62, -44, 28, -116, 442, -62, -53, -80, 10, 640, -80, 100, 10, 496, -62, 568, -71, 514, 505, 64, -8, -8, 1, 1, 10, -53, -62, -44, -134, -71, 19},
      {10, 1, -62, 28, 10, -62, -80, -8, -8, 64, 64, -512, -71, -62, 1, -8, 10, -80, 1, 10, -8, 64, 1, -8, 100, 10, -53, -44, -62, 514, 10, 1, -62, 28, 10, -62, -44, -116, 514, -44, 136, -116, 28, -44, -62, -53, -116, 442, 640, 64, 64, -512, -512, 4096, -80, -8, 496, -224, -80, 496, -8, 64, 568, 496, 640, -80, 64, -512, -8, -80, 64, -8, 19, -53, 10, -80, -62, 496, -134, 442, 505, -134, -116, 442, 1, -8, -71, -62, -80, 10, 28, -224, -44, -134, 496, -62, 10, 100, -80, 640, 10, -80, -62, -53, -71, 19, -44, -134, -8, 64, 1, 10, -8, 1, -62, 496, 514, 505, 568, -71},
      {640, -80, -80, 10, 10, 100, 64, -8, -8, 1, 1, 10, 496, -62, 568, -71, 514, 505, -62, -53, -71, 19, -44, -134, 64, -8, -8, 1, 1, 10, -512, 64, 64, -8, -8, -80, -80, 10, -8, 1, -62, -71, 10, -62, 1, 10, 28, -62, -512, 64, 64, -8, -8, -80, 4096, -512, -512, 64, 64, 640, 640, -80, 64, -8, 496, 568, -80, 496, -8, -80, -224, 496, -224, 28, 496, -62, -44, -134, 496, -62, -80, 10, -53, 19, -80, 10, -8, 1, -62, -71, -116, 442, 442, -134, -134, 505, 28, -44, -62, -53, -116, 442, -62, 514, 10, 100, -44, -53, 10, -62, 1, 10, 28, -62, 136, -116, -116, -44, -44, 514},
      {-80, 640, 10, 100, -80, 10, -8, 64, 1, 10, -8, 1, -62, -53, -71, 19, -44, -134, 496, -62, 568, -71, 514, 505, -8, 64, 1, 10, -8, 1, 64, -512, -8, -80, 64, -8, 10, -62, 1, 10, 28, -62, -80, 10, -8, 1, -62, -71, 64, -512, -8, -80, 64, -8, -512, 4096, 64, 640, -512, 64, -80, 496, -8, -80, -224, 496, 640, -80, 64, -8, 496, 568, 28, -44, -62, -53, -116, 442, -62, 514, 10, 100, -44, -53, 10, -62, 1, 10, 28, -62, 136, -116, -116, -44, -44, 514, -224, 28, 496, -62, -44, -134, 496, -62, -80, 10, -53, 19, -80, 10, -8, 1, -62, -71, -116, 442, 442, -134, -134, 505},
      {-80, 10, 496, -62, 19, -53, -8, 1, -80, 10, -71, -62, -224, 28, 496, -62, -44, -134, -134, 442, 505, -134, -116, 442, -8, 1, -80, 10, -71, -62, 64, -8, -512, 64, -80, -8, -8, 1, 64, -8, 10, 1, -62, 28, 10, 1, -62, 10, 64, -8, 640, -80, 568, 496, -512, 64, 4096, -512, 640, 64, 64, -8, -512, 64, -80, -8, 496, -224, -80, -8, 496, -80, 496, -62, 568, -71, 514, 505, -80, 10, 640, -80, 100, 10, -8, 1, 64, -8, 10, 1, -44, -134, -53, -62, 19, -71, -44, -116, 514, -44, 136, -116, -53, -44, 100, 10, 514, -62, -62, 28, 10, 1, -62, 10, -116, 442, -44, 28, -53, -62},
      {10, 100, -62, 514, -53, -44, 1, 10, 10, -62, -62, 28, 28, -44, -62, -53, -116, 442, -44, -116, 514, -44, 136, -116, 1, 10, 10, -62, -62, 28, -8, -80, 64, -512, -8, 64, 1, 10, -8, 64, 1, -8, -71, -62, 1, -8, 10, -80, -8, -80, -80, 496, 496, -224, 64, 640, -512, 4096, 64, -512, -8, -80, 64, -512, -8, 64, 568, 496, -8, 64, -80, 640, -62, -53, -71, 19, -44, -134, 10, 100, -80, 640, 10, -80, 1, 10, -8, 64, 1, -8, 514, 505, -62, 496, -71, 568, -134, 442, 505, -134, -116, 442, 19, -53, 10, -80, -62, 496, -71, -62, 1, -8, 10, -80, -44, -134, 28, -224, -62, 496},
      {10, -80, 19, -53, 496, -62, 1, -8, -71, -62, -80, 10, -134, 442, 505, -134, -116, 442, -224, 28, 496, -62, -44, -134, 1, -8, -71, -62, -80, 10, -8, 64, -80, -8, -512, 64, -62, 28, 10, 1, -62, 10, -8, 1, 64, -8, 10, 1, -8, 64, 568, 496, 640, -80, 64, -512, 640, 64, 4096, -512, 496, -224, -80, -8, 496, -80, 64, -8, -512, 64, -80, -8, -44, -116, 514, -44, 136, -116, -53, -44, 100, 10, 514, -62, -62, 28, 10, 1, -62, 10, -116, 442, -44, 28, -53, -62, 496, -62, 568, -71, 514, 505, -80, 10, 640, -80, 100, 10, -8, 1, 64, -8, 10, 1, -44, -134, -53, -62, 19, -71},
      {100, 10, -53, -44, -62, 514, 10, 1, -62, 28, 10, -62, -44, -116, 514, -44, 136, -116, 28, -44, -62, -53, -116, 442, 10, 1, -62, 28, 10, -62, -80, -8, -8, 64, 64, -512, -71, -62, 1, -8, 10, -80, 1, 10, -8, 64, 1, -8, -80, -8, 496, -224, -80, 496, 640, 64, 64, -512, -512, 4096, 568, 496, -8, 64, -80, 640, -8, -80, 64, -512, -8, 64, -134, 442, 505, -134, -116, 442, 19, -53, 10, -80, -62, 496, -71, -62, 1, -8, 10, -80, -44, -134, 28, -224, -62, 496, -62, -53, -71, 19, -44, -134, 10, 100, -80, 640, 10, -80, 1, 10, -8, 64, 1, -8, 514, 505, -62, 496, -71, 568},
      {568, -71, 496, -62, 505, 514, -8, 1, 64, -8, 10, 1, -80, 10, 640, -80, 100, 10, -134, -44, 19, -71, -53, -62, 496, -62, -224, 28, -134, -44, -80, 10, -8, 1, -62, -71, 496, -62, -80, 10, -53, 19, 442, -116, -134, 505, 442, -134, 64, -8, -512, 64, -80, -8, 640, -80, 64, -8, 496, 568, 4096, -512, -512, 64, 64, 640, 496, -80, -224, 496, -8, -80, -8, 1, 64, -8, 10, 1, -80, 10, -8, 1, -62, -71, -512, 64, 64, -8, -8, -80, -62, 10, 28, -62, 1, 10, 442, -116, -53, -62, -44, 28, -116, 136, -44, 514, -116, -44, -62, 10, 28, -62, 1, 10, 514, -62, -44, -53, 10, 100},
      {-71, 19, -62, -53, -134, -44, 1, 10, -8, 64, 1, -8, 10, 100, -80, 640, 10, -80, 505, 514, -71, 568, -62, 496, -62, -53, 28, -44, 442, -116, 10, -62, 1, 10, 28, -62, -62, 514, 10, 100, -44, -53, -116, 136, -44, 514, -116, -44, -8, -80, 64, -512, -8, 64, -80, 496, -8, -80, -224, 496, -512, 4096, 64, 640, -512, 64, -80, 640, 496, 568, 64, -8, 1, 10, -8, 64, 1, -8, 10, -62, 1, 10, 28, -62, 64, -512, -8, -80, 64, -8, 10, -80, -62, -71, -8, 1, -134, -44, -62, 496, 28, -224, 442, -116, -134, 505, 442, -134, 10, -80, -62, -71, -8, 1, -62, 496, -53, 19, -80, 10},
      {496, -62, -224, 28, -134, -44, -80, 10, -8, 1, -62, -71, 496, -62, -80, 10, -53, 19, 442, -116, -134, 505, 442, -134, 568, -71, 496, -62, 505, 514, -8, 1, 64, -8, 10, 1, -80, 10, 640, -80, 100, 10, -134, -44, 19, -71, -53, -62, 640, -80, 64, -8, 496, 568, 64, -8, -512, 64, -80, -8, -512, 64, 4096, -512, 640, 64, -224, 496, 496, -80, -80, -8, -80, 10, -8, 1, -62, -71, -8, 1, 64, -8, 10, 1, 64, -8, -512, 64, -80, -8, 28, -62, -62, 10, 10, 1, -116, 136, -44, 514, -116, -44, 442, -116, -53, -62, -44, 28, 28, -62, -62, 10, 10, 1, -44, -53, 514, -62, 100, 10},
      {-62, -53, 28, -44, 442, -116, 10, -62, 1, 10, 28, -62, -62, 514, 10, 100, -44, -53, -116, 136, -44, 514, -116, -44, -71, 19, -62, -53, -134, -44, 1, 10, -8, 64, 1, -8, 10, 100, -80, 640, 10, -80, 505, 514, -71, 568, -62, 496, -80, 496, -8, -80, -224, 496, -8, -80, 64, -512, -8, 64, 64, 640, -512, 4096, 64, -512, 496, 568, -80, 640, -8, 64, 10, -62, 1, 10, 28, -62, 1, 10, -8, 64, 1, -8, -8, -80, 64, -512, -8, 64, -62, -71, 10, -80, 1, -8, 442, -116, -134, 505, 442, -134, -134, -44, -62, 496, 28, -224, -62, -71, 10, -80, 1, -8, -53, 19, -62, 496, 10, -80},
      {505, -134, -134, 442, 442, -116, -71, -62, 1, -8, 10, -80, 19, -53, 10, -80, -62, 496, -134, -44, -62, 496, 28, -224, 514, -44, -44, -116, -116, 136, -62, 28, 10, 1, -62, 10, -53, -44, 100, 10, 514, -62, 442, -116, -53, -62, -44, 28, 568, 496, -8, 64, -80, 640, 496, -224, -80, -8, 496, -80, 64, -512, 640, 64, 4096, -512, -8, 64, -80, -8, -512, 64, -71, -62, 1, -8, 10, -80, -62, 28, 10, 1, -62, 10, -8, 64, -80, -8, -512, 64, 1, -8, 10, 1, 64, -8, 505, 514, -71, 568, -62, 496, -134, -44, 19, -71, -53, -62, 1, -8, 10, 1, 64, -8, 10, -80, 100, 10, 640, -80},
      {514, -44, -44, -116, -116, 136, -62, 28, 10, 1, -62, 10, -53, -44, 100, 10, 514, -62, 442, -116, -53, -62, -44, 28, 505, -134, -134, 442, 442, -116, -71, -62, 1, -8, 10, -80, 19, -53, 10, -80, -62, 496, -134, -44, -62, 496, 28, -224, 496, -224, -80, -8, 496, -80, 568, 496, -8, 64, -80, 640, 640, 64, 64, -512, -512, 4096, -80, -8, -8, 64, 64, -512, -62, 28, 10, 1, -62, 10, -71, -62, 1, -8, 10, -80, -80, -8, -8, 64, 64, -512, 10, 1, 1, -8, -8, 64, -134, -44, 19, -71, -53, -62, 505, 514, -71, 568, -62, 496, 10, 1, 1, -8, -8, 64, 100, 10, 10, -80, -80, 640},
      {-71, 568, 505, 514, 496, -62, 1, -8, 10, 1, 64, -8, -134, -44, 19, -71, -53, -62, -80, 10, 640, -80, 100, 10, -62, 496, -134, -44, -224, 28, 10, -80, -62, -71, -8, 1, 442, -116, -134, 505, 442, -134, 496, -62, -80, 10, -53, 19, -8, 64, -80, -8, -512, 64, -80, 640, 496, 568, 64, -8, 496, -80, -224, 496, -8, -80, 4096, -512, -512, 64, 64, 640, 442, -116, -53, -62, -44, 28, -116, 136, -44, 514, -116, -44, -62, 10, 28, -62, 1, 10, 514, -62, -44, -53, 10, 100, -8, 1, 64, -8, 10, 1, -80, 10, -8, 1, -62, -71, -512, 64, 64, -8, -8, -80, -62, 10, 28, -62, 1, 10},
      {19, -71, -134, -44, -62, -53, 10, 1, 1, -8, -8, 64, 505, 514, -71, 568, -62, 496, 10, 100, -80, 640, 10, -80, -53, -62, 442, -116, 28, -44, -62, 10, 28, -62, 1, 10, -116, 136, -44, 514, -116, -44, -62, 514, 10, 100, -44, -53, -80, -8, -8, 64, 64, -512, 496, -80, -224, 496, -8, -80, -80, 640, 496, 568, 64, -8, -512, 4096, 64, 640, -512, 64, -134, -44, -62, 496, 28, -224, 442, -116, -134, 505, 442, -134, 10, -80, -62, -71, -8, 1, -62, 496, -53, 19, -80, 10, 1, 10, -8, 64, 1, -8, 10, -62, 1, 10, 28, -62, 64, -512, -8, -80, 64, -8, 10, -80, -62, -71, -8, 1},
      {-62, 496, -134, -44, -224, 28, 10, -80, -62, -71, -8, 1, 442, -116, -134, 505, 442, -134, 496, -62, -80, 10, -53, 19, -71, 568, 505, 514, 496, -62, 1, -8, 10, 1, 64, -8, -134, -44, 19, -71, -53, -62, -80, 10, 640, -80, 100, 10, -80, 640, 496, 568, 64, -8, -8, 64, -80, -8, -512, 64, -224, 496, 496, -80, -80, -8, -512, 64, 4096, -512, 640, 64, -116, 136, -44, 514, -116, -44, 442, -116, -53, -62, -44, 28, 28, -62, -62, 10, 10, 1, -44, -53, 514, -62, 100, 10, -80, 10, -8, 1, -62, -71, -8, 1, 64, -8, 10, 1, 64, -8, -512, 64, -80, -8, 28, -62, -62, 10, 10, 1},
      {-53, -62, 442, -116, 28, -44, -62, 10, 28, -62, 1, 10, -116, 136, -44, 514, -116, -44, -62, 514, 10, 100, -44, -53, 19, -71, -134, -44, -62, -53, 10, 1, 1, -8, -8, 64, 505, 514, -71, 568, -62, 496, 10, 100, -80, 640, 10, -80, 496, -80, -224, 496, -8, -80, -80, -8, -8, 64, 64, -512, 496, 568, -80, 640, -8, 64, 64, 640, -512, 4096, 64, -512, 442, -116, -134, 505, 442, -134, -134, -44, -62, 496, 28, -224, -62, -71, 10, -80, 1, -8, -53, 19, -62, 496, 10, -80, 10, -62, 1, 10, 28, -62, 1, 10, -8, 64, 1, -8, -8, -80, 64, -512, -8, 64, -62, -71, 10, -80, 1, -8},
      {-134, 505, 442, -116, -134, 442, -62, -71, 10, -80, 1, -8, -134, -44, -62, 496, 28, -224, 19, -53, 10, -80, -62, 496, -44, 514, -116, 136, -44, -116, 28, -62, -62, 10, 10, 1, 442, -116, -53, -62, -44, 28, -53, -44, 100, 10, 514, -62, 496, 568, -80, 640, -8, 64, -224, 496, 496, -80, -80, -8, -8, 64, -80, -8, -512, 64, 64, -512, 640, 64, 4096, -512, 505, 514, -71, 568, -62, 496, -134, -44, 19, -71, -53, -62, 1, -8, 10, 1, 64, -8, 10, -80, 100, 10, 640, -80, -71, -62, 1, -8, 10, -80, -62, 28, 10, 1, -62, 10, -8, 64, -80, -8, -512, 64, 1, -8, 10, 1, 64, -8},
      {-44, 514, -116, 136, -44, -116, 28, -62, -62, 10, 10, 1, 442, -116, -53, -62, -44, 28, -53, -44, 100, 10, 514, -62, -134, 505, 442, -116, -134, 442, -62, -71, 10, -80, 1, -8, -134, -44, -62, 496, 28, -224, 19, -53, 10, -80, -62, 496, -224, 496, 496, -80, -80, -8, 496, 568, -80, 640, -8, 64, -80, -8, -8, 64, 64, -512, 640, 64, 64, -512, -512, 4096, -134, -44, 19, -71, -53, -62, 505, 514, -71, 568, -62, 496, 10, 1, 1, -8, -8, 64, 100, 10, 10, -80, -80, 640, -62, 28, 10, 1, -62, 10, -71, -62, 1, -8, 10, -80, -80, -8, -8, 64, 64, -512, 10, 1, 1, -8, -8, 64},
      {-8, 1, 64, -8, 10, 1, -80, 10, -8, 1, -62, -71, -512, 64, 64, -8, -8, -80, -62, 10, 28, -62, 1, 10, -80, 10, 640, -80, 100, 10, 496, -62, 568, -71, 514, 505, 64, -8, -8, 1, 1, 10, -53, -62, -44, -134, -71, 19, 496, -62, -80, 10, -53, 19, -224, 28, 496, -62, -44, -134, -8, 1, -80, 10, -71, -62, 442, -134, -116, 442, 505, -134, 4096, -512, -512, 64, 64, 640, -512, 64, 64, -8, -8, -80, 64, -8, 640, -80, 568, 496, -8, -80, -80, 496, 496, -224, 514, -62, -44, -53, 10, 100, -44, 28, -116, 442, -62, -53, -116, -44, 136, -116, 514, -44, 1, 10, 10, -62, -62, 28},
      {1, 10, -8, 64, 1, -8, 10, -62, 1, 10, 28, -62, 64, -512, -8, -80, 64, -8, 10, -80, -62, -71, -8, 1, 10, 100, -80, 640, 10, -80, -62, -53, -71, 19, -44, -134, -8, 64, 1, 10, -8, 1, -62, 496, 514, 505, 568, -71, -62, 514, 10, 100, -44, -53, 28, -44, -62, -53, -116, 442, 1, 10, 10, -62, -62, 28, -116, -44, 136, -116, 514, -44, -512, 4096, 64, 640, -512, 64, 64, -512, -8, -80, 64, -8, -8, -80, -80, 496, 496, -224, 64, -8, 640, -80, 568, 496, -62, 496, -53, 19, -80, 10, 28, -224, -44, -134, 496, -62, 442, -134, -116, 442, 505, -134, -8, 1, -80, 10, -71, -62},
      {-80, 10, -8, 1, -62, -71, -8, 1, 64, -8, 10, 1, 64, -8, -512, 64, -80, -8, 28, -62, -62, 10, 10, 1, 496, -62, -80, 10, -53, 19, -224, 28, 496, -62, -44, -134, -8, 1, -80, 10, -71, -62, 442, -134, -116, 442, 505, -134, -80, 10, 640, -80, 100, 10, 496, -62, 568, -71, 514, 505, 64, -8, -8, 1, 1, 10, -53, -62, -44, -134, -71, 19, -512, 64, 4096, -512, 640, 64, 64, -8, 640, -80, 568, 496, -512, 64, 64, -8, -8, -80, -80, -8, 496, -224, -80, 496, -44, -53, 514, -62, 100, 10, -116, -44, 136, -116, 514, -44, -44, 28, -116, 442, -62, -53, 10, 1, -62, 28, 10, -62},
      {10, -62, 1, 10, 28, -62, 1, 10, -8, 64, 1, -8, -8, -80, 64, -512, -8, 64, -62, -71, 10, -80, 1, -8, -62, 514, 10, 100, -44, -53, 28, -44, -62, -53, -116, 442, 1, 10, 10, -62, -62, 28, -116, -44, 136, -116, 514, -44, 10, 100, -80, 640, 10, -80, -62, -53, -71, 19, -44, -134, -8, 64, 1, 10, -8, 1, -62, 496, 514, 505, 568, -71, 64, 640, -512, 4096, 64, -512, -8, -80, -80, 496, 496, -224, 64, -512, -8, -80, 64, -8, -8, 64, 568, 496, 640, -80, -53, 19, -62, 496, 10, -80, 442, -134, -116, 442, 505, -134, 28, -224, -44, -134, 496, -62, 1, -8, -71, -62, -80, 10},
      {-71, -62, 1, -8, 10, -80, -62, 28, 10, 1, -62, 10, -8, 64, -80, -8, -512, 64, 1, -8, 10, 1, 64, -8, 19, -53, 10, -80, -62, 496, -134, 442, 505, -134, -116, 442, 1, -8, -71, -62, -80, 10, 28, -224, -44, -134, 496, -62, -53, -44, 100, 10, 514, -62, -44, -116, 514, -44, 136, -116, 10, 1, -62, 28, 10, -62, -44, 28, -116, 442, -62, -53, 64, -512, 640, 64, 4096, -512, -8, 64, 568, 496, 640, -80, -80, -8, 496, -224, -80, 496, -512, 64, 64, -8, -8, -80, 10, -80, 100, 10, 640, -80, -62, 496, 514, 505, 568, -71, -53, -62, -44, -134, -71, 19, 64, -8, -8, 1, 1, 10},
      {-62, 28, 10, 1, -62, 10, -71, -62, 1, -8, 10, -80, -80, -8, -8, 64, 64, -512, 10, 1, 1, -8, -8, 64, -53, -44, 100, 10, 514, -62, -44, -116, 514, -44, 136, -116, 10, 1, -62, 28, 10, -62, -44, 28, -116, 442, -62, -53, 19, -53, 10, -80, -62, 496, -134, 442, 505, -134, -116, 442, 1, -8, -71, -62, -80, 10, 28, -224, -44, -134, 496, -62, 640, 64, 64, -512, -512, 4096, -80, -8, 496, -224, -80, 496, -8, 64, 568, 496, 640, -80, 64, -512, -8, -80, 64, -8, 100, 10, 10, -80, -80, 640, -53, -62, -44, -134, -71, 19, -62, 496, 514, 505, 568, -71, -8, 64, 1, 10, -8, 1},
      {-80, 10, 640, -80, 100, 10, 496, -62, 568, -71, 514, 505, 64, -8, -8, 1, 1, 10, -53, -62, -44, -134, -71, 19, -8, 1, 64, -8, 10, 1, -80, 10, -8, 1, -62, -71, -512, 64, 64, -8, -8, -80, -62, 10, 28, -62, 1, 10, -224, 28, 496, -62, -44, -134, 496, -62, -80, 10, -53, 19, -80, 10, -8, 1, -62, -71, -116, 442, 442, -134, -134, 505, -512, 64, 64, -8, -8, -80, 4096, -512, -512, 64, 64, 640, 640, -80, 64, -8, 496, 568, -80, 496, -8, -80, -224, 496, -44, 28, -116, 442, -62, -53, 514, -62, -44, -53, 10, 100, 136, -116, -116, -44, -44, 514, 10, -62, 1, 10, 28, -62},
      {10, 100, -80, 640, 10, -80, -62, -53, -71, 19, -44, -134, -8, 64, 1, 10, -8, 1, -62, 496, 514, 505, 568, -71, 1, 10, -8, 64, 1, -8, 10, -62, 1, 10, 28, -62, 64, -512, -8, -80, 64, -8, 10, -80, -62, -71, -8, 1, 28, -44, -62, -53, -116, 442, -62, 514, 10, 100, -44, -53, 10, -62, 1, 10, 28, -62, 136, -116, -116, -44, -44, 514, 64, -512, -8, -80, 64, -8, -512, 4096, 64, 640, -512, 64, -80, 496, -8, -80, -224, 496, 640, -80, 64, -8, 496, 568, 28, -224, -44, -134, 496, -62, -62, 496, -53, 19, -80, 10, -116, 442, 442, -134, -134, 505, -80, 10, -8, 1, -62, -71},
      {496, -62, -80, 10, -53, 19, -224, 28, 496, -62, -44, -134, -8, 1, -80, 10, -71, -62, 442, -134, -116, 442, 505, -134, -80, 10, -8, 1, -62, -71, -8, 1, 64, -8, 10, 1, 64, -8, -512, 64, -80, -8, 28, -62, -62, 10, 10, 1, 496, -62, 568, -71, 514, 505, -80, 10, 640, -80, 100, 10, -8, 1, 64, -8, 10, 1, -44, -134, -53, -62, 19, -71, 64, -8, 640, -80, 568, 496, -512, 64, 4096, -512, 640, 64, 64, -8, -512, 64, -80, -8, 496, -224, -80, -8, 496, -80, -116, -44, 136, -116, 514, -44, -44, -53, 514, -62, 100, 10, -116, 442, -44, 28, -53, -62, -62, 28, 10, 1, -62, 10},
      {-62, 514, 10, 100, -44, -53, 28, -44, -62, -53, -116, 442, 1, 10, 10, -62, -62, 28, -116, -44, 136, -116, 514, -44, 10, -62, 1, 10, 28, -62, 1, 10, -8, 64, 1, -8, -8, -80, 64, -512, -8, 64, -62, -71, 10, -80, 1, -8, -62, -53, -71, 19, -44, -134, 10, 100, -80, 640, 10, -80, 1, 10, -8, 64, 1, -8, 514, 505, -62, 496, -71, 568, -8, -80, -80, 496, 496, -224, 64, 640, -512, 4096, 64, -512, -8, -80, 64, -512, -8, 64, 568, 496, -8, 64, -80, 640, 442, -134, -116, 442, 505, -134, -53, 19, -62, 496, 10, -80, -44, -134, 28, -224, -62, 496, -71, -62, 1, -8, 10, -80},
      {19, -53, 10, -80, -62, 496, -134, 442, 505, -134, -116, 442, 1, -8, -71, -62, -80, 10, 28, -224, -44, -134, 496, -62, -71, -62, 1, -8, 10, -80, -62, 28, 10, 1, -62, 10, -8, 64, -80, -8, -512, 64, 1, -8, 10, 1, 64, -8, -44, -116, 514, -44, 136, -116, -53, -44, 100, 10, 514, -62, -62, 28, 10, 1, -62, 10, -116, 442, -44, 28, -53, -62, -8, 64, 568, 496, 640, -80, 64, -512, 640, 64, 4096, -512, 496, -224, -80, -8, 496, -80, 64, -8, -512, 64, -80, -8, -62, 496, 514, 505, 568, -71, 10, -80, 100, 10, 640, -80, -44, -134, -53, -62, 19, -71, -8, 1, 64, -8, 10, 1},
      {-53, -44, 100, 10, 514, -62, -44, -116, 514, -44, 136, -116, 10, 1, -62, 28, 10, -62, -44, 28, -116, 442, -62, -53, -62, 28, 10, 1, -62, 10, -71, -62, 1, -8, 10, -80, -80, -8, -8, 64, 64, -512, 10, 1, 1, -8, -8, 64, -134, 442, 505, -134, -116, 442, 19, -53, 10, -80, -62, 496, -71, -62, 1, -8, 10, -80, -44, -134, 28, -224, -62, 496, -80, -8, 496, -224, -80, 496, 640, 64, 64, -512, -512, 4096, 568, 496, -8, 64, -80, 640, -8, -80, 64, -512, -8, 64, -53, -62, -44, -134, -71, 19, 100, 10, 10, -80, -80, 640, 514, 505, -62, 496, -71, 568, 1, 10, -8, 64, 1, -8},
      {496, -62, 568, -71, 514, 505, -80, 10, 640, -80, 100, 10, -8, 1, 64, -8, 10, 1, -44, -134, -53, -62, 19, -71, -224, 28, 496, -62, -44, -134, 496, -62, -80, 10, -53, 19, -80, 10, -8, 1, -62, -71, -116, 442, 442, -134, -134, 505, -8, 1, 64, -8, 10, 1, -80, 10, -8, 1, -62, -71, -512, 64, 64, -8, -8, -80, -62, 10, 28, -62, 1, 10, 64, -8, -512, 64, -80, -8, 640, -80, 64, -8, 496, 568, 4096, -512, -512, 64, 64, 640, 496, -80, -224, 496, -8, -80, -116, 442, -44, 28, -53, -62, 136, -116, -116, -44, -44, 514, 514, -62, -44, -53, 10, 100, -62, 10, 28, -62, 1, 10},
      {-62, -53, -71, 19, -44, -134, 10, 100, -80, 640, 10, -80, 1, 10, -8, 64, 1, -8, 514, 505, -62, 496, -71, 568, 28, -44, -62, -53, -116, 442, -62, 514, 10, 100, -44, -53, 10, -62, 1, 10, 28, -62, 136, -116, -116, -44, -44, 514, 1, 10, -8, 64, 1, -8, 10, -62, 1, 10, 28, -62, 64, -512, -8, -80, 64, -8, 10, -80, -62, -71, -8, 1, -8, -80, 64, -512, -8, 64, -80, 496, -8, -80, -224, 496, -512, 4096, 64, 640, -512, 64, -80, 640, 496, 568, 64, -8, -44, -134, 28, -224, -62, 496, -116, 442, 442, -134, -134, 505, -62, 496, -53, 19, -80, 10, 10, -80, -62, -71, -8, 1},
      {-224, 28, 496, -62, -44, -134, 496, -62, -80, 10, -53, 19, -80, 10, -8, 1, -62, -71, -116, 442, 442, -134, -134, 505, 496, -62, 568, -71, 514, 505, -80, 10, 640, -80, 100, 10, -8, 1, 64, -8, 10, 1, -44, -134, -53, -62, 19, -71, -80, 10, -8, 1, -62, -71, -8, 1, 64, -8, 10, 1, 64, -8, -512, 64, -80, -8, 28, -62, -62, 10, 10, 1, 640, -80, 64, -8, 496, 568, 64, -8, -512, 64, -80, -8, -512, 64, 4096, -512, 640, 64, -224, 496, 496, -80, -80, -8, 136, -116, -116, -44, -44, 514, -116, 442, -44, 28, -53, -62, -44, -53, 514, -62, 100, 10, 28, -62, -62, 10, 10, 1},
      {28, -44, -62, -53, -116, 442, -62, 514, 10, 100, -44, -53, 10, -62, 1, 10, 28, -62, 136, -116, -116, -44, -44, 514, -62, -53, -71, 19, -44, -134, 10, 100, -80, 640, 10, -80, 1, 10, -8, 64, 1, -8, 514, 505, -62, 496, -71, 568, 10, -62, 1, 10, 28, -62, 1, 10, -8, 64, 1, -8, -8, -80, 64, -512, -8, 64, -62, -71, 10, -80, 1, -8, -80, 496, -8, -80, -224, 496, -8, -80, 64, -512, -8, 64, 64, 640, -512, 4096, 64, -512, 496, 568, -80, 640, -8, 64, -116, 442, 442, -134, -134, 505, -44, -134, 28, -224, -62, 496, -53, 19, -62, 496, 10, -80, -62, -71, 10, -80, 1, -8},
      {-134, 442, 505, -134, -116, 442, 19, -53, 10, -80, -62, 496, -71, -62, 1, -8, 10, -80, -44, -134, 28, -224, -62, 496, -44, -116, 514, -44, 136, -116, -53, -44, 100, 10, 514, -62, -62, 28, 10, 1, -62, 10, -116, 442, -44, 28, -53, -62, -71, -62, 1, -8, 10, -80, -62, 28, 10, 1, -62, 10, -8, 64, -80, -8, -512, 64, 1, -8, 10, 1, 64, -8, 568, 496, -8, 64, -80, 640, 496, -224, -80, -8, 496, -80, 64, -512, 640, 64, 4096, -512, -8, 64, -80, -8, -512, 64, 514, 505, -62, 496, -71, 568, -44, -134, -53, -62, 19, -71, 10, -80, 100, 10, 640, -80, 1, -8, 10, 1, 64, -8},
      {-44, -116, 514, -44, 136, -116, -53, -44, 100, 10, 514, -62, -62, 28, 10, 1, -62, 10, -116, 442, -44, 28, -53, -62, -134, 442, 505, -134, -116, 442, 19, -53, 10, -80, -62, 496, -71, -62, 1, -8, 10, -80, -44, -134, 28, -224, -62, 496, -62, 28, 10, 1, -62, 10, -71, -62, 1, -8, 10, -80, -80, -8, -8, 64, 64, -512, 10, 1, 1, -8, -8, 64, 496, -224, -80, -8, 496, -80, 568, 496, -8, 64, -80, 640, 640, 64, 64, -512, -512, 4096, -80, -8, -8, 64, 64, -512, -44, -134, -53, -62, 19, -71, 514, 505, -62, 496, -71, 568, 100, 10, 10, -80, -80, 640, 10, 1, 1, -8, -8, 64},
      {505, 514, -71, 568, -62, 496, -134, -44, 19, -71, -53, -62, 1, -8, 10, 1, 64, -8, 10, -80, 100, 10, 640, -80, -134, -44, -62, 496, 28, -224, 442, -116, -134, 505, 442, -134, 10, -80, -62, -71, -8, 1, -62, 496, -53, 19, -80, 10, 442, -116, -53, -62, -44, 28, -116, 136, -44, 514, -116, -44, -62, 10, 28, -62, 1, 10, 514, -62, -44, -53, 10, 100, -8, 64, -80, -8, -512, 64, -80, 640, 496, 568, 64, -8, 496, -80, -224, 496, -8, -80, 4096, -512, -512, 64, 64, 640, 1, -8, 10, 1, 64, -8, 10, -80, -62, -71, -8, 1, -62, 10, 28, -62, 1, 10, -512, 64, 64, -8, -8, -80},
      {-134, -44, 19, -71, -53, -62, 505, 514, -71, 568, -62, 496, 10, 1, 1, -8, -8, 64, 100, 10, 10, -80, -80, 640, 442, -116, -53, -62, -44, 28, -116, 136, -44, 514, -116, -44, -62, 10, 28, -62, 1, 10, 514, -62, -44, -53, 10, 100, -134, -44, -62, 496, 28, -224, 442, -116, -134, 505, 442, -134, 10, -80, -62, -71, -8, 1, -62, 496, -53, 19, -80, 10, -80, -8, -8, 64, 64, -512, 496, -80, -224, 496, -8, -80, -80, 640, 496, 568, 64, -8, -512, 4096, 64, 640, -512, 64, 10, 1, 1, -8, -8, 64, -62, 10, 28, -62, 1, 10, 10, -80, -62, -71, -8, 1, 64, -512, -8, -80, 64, -8},
      {-134, -44, -62, 496, 28, -224, 442, -116, -134, 505, 442, -134, 10, -80, -62, -71, -8, 1, -62, 496, -53, 19, -80, 10, 505, 514, -71, 568, -62, 496, -134, -44, 19, -71, -53, -62, 1, -8, 10, 1, 64, -8, 10, -80, 100, 10, 640, -80, -116, 136, -44, 514, -116, -44, 442, -116, -53, -62, -44, 28, 28, -62, -62, 10, 10, 1, -44, -53, 514, -62, 100, 10, -80, 640, 496, 568, 64, -8, -8, 64, -80, -8, -512, 64, -224, 496, 496, -80, -80, -8, -512, 64, 4096, -512, 640, 64, 10, -80, -62, -71, -8, 1, 1, -8, 10, 1, 64, -8, 28, -62, -62, 10, 10, 1, 64, -8, -512, 64, -80, -8},
      {442, -116, -53, -62, -44, 28, -116, 136, -44, 514, -116, -44, -62, 10, 28, -62, 1, 10, 514, -62, -44, -53, 10, 100, -134, -44, 19, -71, -53, -62, 505, 514, -71, 568, -62, 496, 10, 1, 1, -8, -8, 64, 100, 10, 10, -80, -80, 640, 442, -116, -134, 505, 442, -134, -134, -44, -62, 496, 28, -224, -62, -71, 10, -80, 1, -8, -53, 19, -62, 496, 10, -80, 496, -80, -224, 496, -8, -80, -80, -8, -8, 64, 64, -512, 496, 568, -80, 640, -8, 64, 64, 640, -512, 4096, 64, -512, -62, 10, 28, -62, 1, 10, 10, 1, 1, -8, -8, 64, -62, -71, 10, -80, 1, -8, -8, -80, 64, -512, -8, 64},
      {442, -116, -134, 505, 442, -134, -134, -44, -62, 496, 28, -224, -62, -71, 10, -80, 1, -8, -53, 19, -62, 496, 10, -80, -116, 136, -44, 514, -116, -44, 442, -116, -53, -62, -44, 28, 28, -62, -62, 10, 10, 1, -44, -53, 514, -62, 100, 10, 505, 514, -71, 568, -62, 496, -134, -44, 19, -71, -53, -62, 1, -8, 10, 1, 64, -8, 10, -80, 100, 10, 640, -80, 496, 568, -80, 640, -8, 64, -224, 496, 496, -80, -80, -8, -8, 64, -80, -8, -512, 64, 64, -512, 640, 64, 4096, -512, -62, -71, 10, -80, 1, -8, 28, -62, -62, 10, 10, 1, 1, -8, 10, 1, 64, -8, -8, 64, -80, -8, -512, 64},
      {-116, 136, -44, 514, -116, -44, 442, -116, -53, -62, -44, 28, 28, -62, -62, 10, 10, 1, -44, -53, 514, -62, 100, 10, 442, -116, -134, 505, 442, -134, -134, -44, -62, 496, 28, -224, -62, -71, 10, -80, 1, -8, -53, 19, -62, 496, 10, -80, -134, -44, 19, -71, -53, -62, 505, 514, -71, 568, -62, 496, 10, 1, 1, -8, -8, 64, 100, 10, 10, -80, -80, 640, -224, 496, 496, -80, -80, -8, 496, 568, -80, 640, -8, 64, -80, -8, -8, 64, 64, -512, 640, 64, 64, -512, -512, 4096, 28, -62, -62, 10, 10, 1, -62, -71, 10, -80, 1, -8, 10, 1, 1, -8, -8, 64, -80, -8, -8, 64, 64, -512},
      {1, -8, 10, 1, 64, -8, 10, -80, -62, -71, -8, 1, -62, 10, 28, -62, 1, 10, -512, 64, 64, -8, -8, -80, 10, -80, 100, 10, 640, -80, -62, 496, 514, 505, 568, -71, -53, -62, -44, -134, -71, 19, 64, -8, -8, 1, 1, 10, -62, 496, -53, 19, -80, 10, 28, -224, -44, -134, 496, -62, 442, -134, -116, 442, 505, -134, -8, 1, -80, 10, -71, -62, 514, -62, -44, -53, 10, 100, -44, 28, -116, 442, -62, -53, -116, -44, 136, -116, 514, -44, 1, 10, 10, -62, -62, 28, 4096, -512, -512, 64, 64, 640, -512, 64, 64, -8, -8, -80, 64, -8, 640, -80, 568, 496, -8, -80, -80, 496, 496, -224},
      {10, 1, 1, -8, -8, 64, -62, 10, 28, -62, 1, 10, 10, -80, -62, -71, -8, 1, 64, -512, -8, -80, 64, -8, 100, 10, 10, -80, -80, 640, -53, -62, -44, -134, -71, 19, -62, 496, 514, 505, 568, -71, -8, 64, 1, 10, -8, 1, 514, -62, -44, -53, 10, 100, -44, 28, -116, 442, -62, -53, -116, -44, 136, -116, 514, -44, 1, 10, 10, -62, -62, 28, -62, 496, -53, 19, -80, 10, 28, -224, -44, -134, 496, -62, 442, -134, -116, 442, 505, -134, -8, 1, -80, 10, -71, -62, -512, 4096, 64, 640, -512, 64, 64, -512, -8, -80, 64, -8, -8, -80, -80, 496, 496, -224, 64, -8, 640, -80, 568, 496},
      {10, -80, -62, -71, -8, 1, 1, -8, 10, 1, 64, -8, 28, -62, -62, 10, 10, 1, 64, -8, -512, 64, -80, -8, -62, 496, -53, 19, -80, 10, 28, -224, -44, -134, 496, -62, 442, -134, -116, 442, 505, -134, -8, 1, -80, 10, -71, -62, 10, -80, 100, 10, 640, -80, -62, 496, 514, 505, 568, -71, -53, -62, -44, -134, -71, 19, 64, -8, -8, 1, 1, 10, -44, -53, 514, -62, 100, 10, -116, -44, 136, -116, 514, -44, -44, 28, -116, 442, -62, -53, 10, 1, -62, 28, 10, -62, -512, 64, 4096, -512, 640, 64, 64, -8, 640, -80, 568, 496, -512, 64, 64, -8, -8, -80, -80, -8, 496, -224, -80, 496},
      {-62, 10, 28, -62, 1, 10, 10, 1, 1, -8, -8, 64, -62, -71, 10, -80, 1, -8, -8, -80, 64, -512, -8, 64, 514, -62, -44, -53, 10, 100, -44, 28, -116, 442, -62, -53, -116, -44, 136, -116, 514, -44, 1, 10, 10, -62, -62, 28, 100, 10, 10, -80, -80, 640, -53, -62, -44, -134, -71, 19, -62, 496, 514, 505, 568, -71, -8, 64, 1, 10, -8, 1, -53, 19, -62, 496, 10, -80, 442, -134, -116, 442, 505, -134, 28, -224, -44, -134, 496, -62, 1, -8, -71, -62, -80, 10, 64, 640, -512, 4096, 64, -512, -8, -80, -80, 496, 496, -224, 64, -512, -8, -80, 64, -8, -8, 64, 568, 496, 640, -80},
      {-62, -71, 10, -80, 1, -8, 28, -62, -62, 10, 10, 1, 1, -8, 10, 1, 64, -8, -8, 64, -80, -8, -512, 64, -53, 19, -62, 496, 10, -80, 442, -134, -116, 442, 505, -134, 28, -224, -44, -134, 496, -62, 1, -8, -71, -62, -80, 10, -44, -53, 514, -62, 100, 10, -116, -44, 136, -116, 514, -44, -44, 28, -116, 442, -62, -53, 10, 1, -62, 28, 10, -62, 10, -80, 100, 10, 640, -80, -62, 496, 514, 505, 568, -71, -53, -62, -44, -134, -71, 19, 64, -8, -8, 1, 1, 10, 64, -512, 640, 64, 4096, -512, -8, 64, 568, 496, 640, -80, -80, -8, 496, -224, -80, 496, -512, 64, 64, -8, -8, -80},
      {28, -62, -62, 10, 10, 1, -62, -71, 10, -80, 1, -8, 10, 1, 1, -8, -8, 64, -80, -8, -8, 64, 64, -512, -44, -53, 514, -62, 100, 10, -116, -44, 136, -116, 514, -44, -44, 28, -116, 442, -62, -53, 10, 1, -62, 28, 10, -62, -53, 19, -62, 496, 10, -80, 442, -134, -116, 442, 505, -134, 28, -224, -44, -134, 496, -62, 1, -8, -71, -62, -80, 10, 100, 10, 10, -80, -80, 640, -53, -62, -44, -134, -71, 19, -62, 496, 514, 505, 568, -71, -8, 64, 1, 10, -8, 1, 640, 64, 64, -512, -512, 4096, -80, -8, 496, -224, -80, 496, -8, 64, 568, 496, 640, -80, 64, -512, -8, -80, 64, -8},
      {10, -80, 100, 10, 640, -80, -62, 496, 514, 505, 568, -71, -53, -62, -44, -134, -71, 19, 64, -8, -8, 1, 1, 10, 1, -8, 10, 1, 64, -8, 10, -80, -62, -71, -8, 1, -62, 10, 28, -62, 1, 10, -512, 64, 64, -8, -8, -80, 28, -224, -44, -134, 496, -62, -62, 496, -53, 19, -80, 10, -116, 442, 442, -134, -134, 505, -80, 10, -8, 1, -62, -71, -44, 28, -116, 442, -62, -53, 514, -62, -44, -53, 10, 100, 136, -116, -116, -44, -44, 514, 10, -62, 1, 10, 28, -62, -512, 64, 64, -8, -8, -80, 4096, -512, -512, 64, 64, 640, 640, -80, 64, -8, 496, 568, -80, 496, -8, -80, -224, 496},
      {100, 10, 10, -80, -80, 640, -53, -62, -44, -134, -71, 19, -62, 496, 514, 505, 568, -71, -8, 64, 1, 10, -8, 1, 10, 1, 1, -8, -8, 64, -62, 10, 28, -62, 1, 10, 10, -80, -62, -71, -8, 1, 64, -512, -8, -80, 64, -8, -44, 28, -116, 442, -62, -53, 514, -62, -44, -53, 10, 100, 136, -116, -116, -44, -44, 514, 10, -62, 1, 10, 28, -62, 28, -224, -44, -134, 496, -62, -62, 496, -53, 19, -80, 10, -116, 442, 442, -134, -134, 505, -80, 10, -8, 1, -62, -71, 64, -512, -8, -80, 64, -8, -512, 4096, 64, 640, -512, 64, -80, 496, -8, -80, -224, 496, 640, -80, 64, -8, 496, 568},
      {-62, 496, -53, 19, -80, 10, 28, -224, -44, -134, 496, -62, 442, -134, -116, 442, 505, -134, -8, 1, -80, 10, -71, -62, 10, -80, -62, -71, -8, 1, 1, -8, 10, 1, 64, -8, 28, -62, -62, 10, 10, 1, 64, -8, -512, 64, -80, -8, -62, 496, 514, 505, 568, -71, 10, -80, 100, 10, 640, -80, -44, -134, -53, -62, 19, -71, -8, 1, 64, -8, 10, 1, -116, -44, 136, -116, 514, -44, -44, -53, 514, -62, 100, 10, -116, 442, -44, 28, -53, -62, -62, 28, 10, 1, -62, 10, 64, -8, 640, -80, 568, 496, -512, 64, 4096, -512, 640, 64, 64, -8, -512, 64, -80, -8, 496, -224, -80, -8, 496, -80},
      {514, -62, -44, -53, 10, 100, -44, 28, -116, 442, -62, -53, -116, -44, 136, -116, 514, -44, 1, 10, 10, -62, -62, 28, -62, 10, 28, -62, 1, 10, 10, 1, 1, -8, -8, 64, -62, -71, 10, -80, 1, -8, -8, -80, 64, -512, -8, 64, -53, -62, -44, -134, -71, 19, 100, 10, 10, -80, -80, 640, 514, 505, -62, 496, -71, 568, 1, 10, -8, 64, 1, -8, 442, -134, -116, 442, 505, -134, -53, 19, -62, 496, 10, -80, -44, -134, 28, -224, -62, 496, -71, -62, 1, -8, 10, -80, -8, -80, -80, 496, 496, -224, 64, 640, -512, 4096, 64, -512, -8, -80, 64, -512, -8, 64, 568, 496, -8, 64, -80, 640},
      {-53, 19, -62, 496, 10, -80, 442, -134, -116, 442, 505, -134, 28, -224, -44, -134, 496, -62, 1, -8, -71, -62, -80, 10, -62, -71, 10, -80, 1, -8, 28, -62, -62, 10, 10, 1, 1, -8, 10, 1, 64, -8, -8, 64, -80, -8, -512, 64, -116, -44, 136, -116, 514, -44, -44, -53, 514, -62, 100, 10, -116, 442, -44, 28, -53, -62, -62, 28, 10, 1, -62, 10, -62, 496, 514, 505, 568, -71, 10, -80, 100, 10, 640, -80, -44, -134, -53, -62, 19, -71, -8, 1, 64, -8, 10, 1, -8, 64, 568, 496, 640, -80, 64, -512, 640, 64, 4096, -512, 496, -224, -80, -8, 496, -80, 64, -8, -512, 64, -80, -8},
      {-44, -53, 514, -62, 100, 10, -116, -44, 136, -116, 514, -44, -44, 28, -116, 442, -62, -53, 10, 1, -62, 28, 10, -62, 28, -62, -62, 10, 10, 1, -62, -71, 10, -80, 1, -8, 10, 1, 1, -8, -8, 64, -80, -8, -8, 64, 64, -512, 442, -134, -116, 442, 505, -134, -53, 19, -62, 496, 10, -80, -44, -134, 28, -224, -62, 496, -71, -62, 1, -8, 10, -80, -53, -62, -44, -134, -71, 19, 100, 10, 10, -80, -80, 640, 514, 505, -62, 496, -71, 568, 1, 10, -8, 64, 1, -8, -80, -8, 496, -224, -80, 496, 640, 64, 64, -512, -512, 4096, 568, 496, -8, 64, -80, 640, -8, -80, 64, -512, -8, 64},
      {-62, 496, 514, 505, 568, -71, 10, -80, 100, 10, 640, -80, -44, -134, -53, -62, 19, -71, -8, 1, 64, -8, 10, 1, 28, -224, -44, -134, 496, -62, -62, 496, -53, 19, -80, 10, -116, 442, 442, -134, -134, 505, -80, 10, -8, 1, -62, -71, 1, -8, 10, 1, 64, -8, 10, -80, -62, -71, -8, 1, -62, 10, 28, -62, 1, 10, -512, 64, 64, -8, -8, -80, -116, 442, -44, 28, -53, -62, 136, -116, -116, -44, -44, 514, 514, -62, -44, -53, 10, 100, -62, 10, 28, -62, 1, 10, 64, -8, -512, 64, -80, -8, 640, -80, 64, -8, 496, 568, 4096, -512, -512, 64, 64, 640, 496, -80, -224, 496, -8, -80},
      {-53, -62, -44, -134, -71, 19, 100, 10, 10, -80, -80, 640, 514, 505, -62, 496, -71, 568, 1, 10, -8, 64, 1, -8, -44, 28, -116, 442, -62, -53, 514, -62, -44, -53, 10, 100, 136, -116, -116, -44, -44, 514, 10, -62, 1, 10, 28, -62, 10, 1, 1, -8, -8, 64, -62, 10, 28, -62, 1, 10, 10, -80, -62, -71, -8, 1, 64, -512, -8, -80, 64, -8, -44, -134, 28, -224, -62, 496, -116, 442, 442, -134, -134, 505, -62, 496, -53, 19, -80, 10, 10, -80, -62, -71, -8, 1, -8, -80, 64, -512, -8, 64, -80, 496, -8, -80, -224, 496, -512, 4096, 64, 640, -512, 64, -80, 640, 496, 568, 64, -8},
      {28, -224, -44, -134, 496, -62, -62, 496, -53, 19, -80, 10, -116, 442, 442, -134, -134, 505, -80, 10, -8, 1, -62, -71, -62, 496, 514, 505, 568, -71, 10, -80, 100, 10, 640, -80, -44, -134, -53, -62, 19, -71, -8, 1, 64, -8, 10, 1, 10, -80, -62, -71, -8, 1, 1, -8, 10, 1, 64, -8, 28, -62, -62, 10, 10, 1, 64, -8, -512, 64, -80, -8, 136, -116, -116, -44, -44, 514, -116, 442, -44, 28, -53, -62, -44, -53, 514, -62, 100, 10, 28, -62, -62, 10, 10, 1, 640, -80, 64, -8, 496, 568, 64, -8, -512, 64, -80, -8, -512, 64, 4096, -512, 640, 64, -224, 496, 496, -80, -80, -8},
      {-44, 28, -116, 442, -62, -53, 514, -62, -44, -53, 10, 100, 136, -116, -116, -44, -44, 514, 10, -62, 1, 10, 28, -62, -53, -62, -44, -134, -71, 19, 100, 10, 10, -80, -80, 640, 514, 505, -62, 496, -71, 568, 1, 10, -8, 64, 1, -8, -62, 10, 28, -62, 1, 10, 10, 1, 1, -8, -8, 64, -62, -71, 10, -80, 1, -8, -8, -80, 64, -512, -8, 64, -116, 442, 442, -134, -134, 505, -44, -134, 28, -224, -62, 496, -53, 19, -62, 496, 10, -80, -62, -71, 10, -80, 1, -8, -80, 496, -8, -80, -224, 496, -8, -80, 64, -512, -8, 64, 64, 640, -512, 4096, 64, -512, 496, 568, -80, 640, -8, 64},
      {442, -134, -116, 442, 505, -134, -53, 19, -62, 496, 10, -80, -44, -134, 28, -224, -62, 496, -71, -62, 1, -8, 10, -80, -116, -44, 136, -116, 514, -44, -44, -53, 514, -62, 100, 10, -116, 442, -44, 28, -53, -62, -62, 28, 10, 1, -62, 10, -62, -71, 10, -80, 1, -8, 28, -62, -62, 10, 10, 1, 1, -8, 10, 1, 64, -8, -8, 64, -80, -8, -512, 64, 514, 505, -62, 496, -71, 568, -44, -134, -53, -62, 19, -71, 10, -80, 100, 10, 640, -80, 1, -8, 10, 1, 64, -8, 568, 496, -8, 64, -80, 640, 496, -224, -80, -8, 496, -80, 64, -512, 640, 64, 4096, -512, -8, 64, -80, -8, -512, 64},
      {-116, -44, 136, -116, 514, -44, -44, -53, 514, -62, 100, 10, -116, 442, -44, 28, -53, -62, -62, 28, 10, 1, -62, 10, 442, -134, -116, 442, 505, -134, -53, 19, -62, 496, 10, -80, -44, -134, 28, -224, -62, 496, -71, -62, 1, -8, 10, -80, 28, -62, -62, 10, 10, 1, -62, -71, 10, -80, 1, -8, 10, 1, 1, -8, -8, 64, -80, -8, -8, 64, 64, -512, -44, -134, -53, -62, 19, -71, 514, 505, -62, 496, -71, 568, 100, 10, 10, -80, -80, 640, 10, 1, 1, -8, -8, 64, 496, -224, -80, -8, 496, -80, 568, 496, -8, 64, -80, 640, 640, 64, 64, -512, -512, 4096, -80, -8, -8, 64, 64, -512},
      {514, 505, -62, 496, -71, 568, -44, -134, -53, -62, 19, -71, 10, -80, 100, 10, 640, -80, 1, -8, 10, 1, 64, -8, -44, -134, 28, -224, -62, 496, -116, 442, 442, -134, -134, 505, -62, 496, -53, 19, -80, 10, 10, -80, -62, -71, -8, 1, -116, 442, -44, 28, -53, -62, 136, -116, -116, -44, -44, 514, 514, -62, -44, -53, 10, 100, -62, 10, 28, -62, 1, 10, 1, -8, 10, 1, 64, -8, 10, -80, -62, -71, -8, 1, -62, 10, 28, -62, 1, 10, -512, 64, 64, -8, -8, -80, -8, 64, -80, -8, -512, 64, -80, 640, 496, 568, 64, -8, 496, -80, -224, 496, -8, -80, 4096, -512, -512, 64, 64, 640},
      {-44, -134, -53, -62, 19, -71, 514, 505, -62, 496, -71, 568, 100, 10, 10, -80, -80, 640, 10, 1, 1, -8, -8, 64, -116, 442, -44, 28, -53, -62, 136, -116, -116, -44, -44, 514, 514, -62, -44, -53, 10, 100, -62, 10, 28, -62, 1, 10, -44, -134, 28, -224, -62, 496, -116, 442, 442, -134, -134, 505, -62, 496, -53, 19, -80, 10, 10, -80, -62, -71, -8, 1, 10, 1, 1, -8, -8, 64, -62, 10, 28, -62, 1, 10, 10, -80, -62, -71, -8, 1, 64, -512, -8, -80, 64, -8, -80, -8, -8, 64, 64, -512, 496, -80, -224, 496, -8, -80, -80, 640, 496, 568, 64, -8, -512, 4096, 64, 640, -512, 64},
      {-44, -134, 28, -224, -62, 496, -116, 442, 442, -134, -134, 505, -62, 496, -53, 19, -80, 10, 10, -80, -62, -71, -8, 1, 514, 505, -62, 496, -71, 568, -44, -134, -53, -62, 19, -71, 10, -80, 100, 10, 640, -80, 1, -8, 10, 1, 64, -8, 136, -116, -116, -44, -44, 514, -116, 442, -44, 28, -53, -62, -44, -53, 514, -62, 100, 10, 28, -62, -62, 10, 10, 1, 10, -80, -62, -71, -8, 1, 1, -8, 10, 1, 64, -8, 28, -62, -62, 10, 10, 1, 64, -8, -512, 64, -80, -8, -80, 640, 496, 568, 64, -8, -8, 64, -80, -8, -512, 64, -224, 496, 496, -80, -80, -8, -512, 64, 4096, -512, 640, 64},
      {-116, 442, -44, 28, -53, -62, 136, -116, -116, -44, -44, 514, 514, -62, -44, -53, 10, 100, -62, 10, 28, -62, 1, 10, -44, -134, -53, -62, 19, -71, 514, 505, -62, 496, -71, 568, 100, 10, 10, -80, -80, 640, 10, 1, 1, -8, -8, 64, -116, 442, 442, -134, -134, 505, -44, -134, 28, -224, -62, 496, -53, 19, -62, 496, 10, -80, -62, -71, 10, -80, 1, -8, -62, 10, 28, -62, 1, 10, 10, 1, 1, -8, -8, 64, -62, -71, 10, -80, 1, -8, -8, -80, 64, -512, -8, 64, 496, -80, -224, 496, -8, -80, -80, -8, -8, 64, 64, -512, 496, 568, -80, 640, -8, 64, 64, 640, -512, 4096, 64, -512},
      {-116, 442, 442, -134, -134, 505, -44, -134, 28, -224, -62, 496, -53, 19, -62, 496, 10, -80, -62, -71, 10, -80, 1, -8, 136, -116, -116, -44, -44, 514, -116, 442, -44, 28, -53, -62, -44, -53, 514, -62, 100, 10, 28, -62, -62, 10, 10, 1, 514, 505, -62, 496, -71, 568, -44, -134, -53, -62, 19, -71, 10, -80, 100, 10, 640, -80, 1, -8, 10, 1, 64, -8, -62, -71, 10, -80, 1, -8, 28, -62, -62, 10, 10, 1, 1, -8, 10, 1, 64, -8, -8, 64, -80, -8, -512, 64, 496, 568, -80, 640, -8, 64, -224, 496, 496, -80, -80, -8, -8, 64, -80, -8, -512, 64, 64, -512, 640, 64, 4096, -512},
      {136, -116, -116, -44, -44, 514, -116, 442, -44, 28, -53, -62, -44, -53, 514, -62, 100, 10, 28, -62, -62, 10, 10, 1, -116, 442, 442, -134, -134, 505, -44, -134, 28, -224, -62, 496, -53, 19, -62, 496, 10, -80, -62, -71, 10, -80, 1, -8, -44, -134, -53, -62, 19, -71, 514, 505, -62, 496, -71, 568, 100, 10, 10, -80, -80, 640, 10, 1, 1, -8, -8, 64, 28, -62, -62, 10, 10, 1, -62, -71, 10, -80, 1, -8, 10, 1, 1, -8, -8, 64, -80, -8, -8, 64, 64, -512, -224, 496, 496, -80, -80, -8, 496, 568, -80, 640, -8, 64, -80, -8, -8, 64, 64, -512, 640, 64, 64, -512, -512, 4096}};

      // Sum and square the color flows to get the matrix element
      // (compute |M|^2 by squaring |M|, taking into account colours)
      fptype_sv deltaMEs = { 0 }; // all zeros
      for( int icol = 0; icol < ncolor; icol++ )
      {
        cxtype_sv ztemp_sv = cxzero_sv();
        for( int jcol = 0; jcol < ncolor; jcol++ )
          ztemp_sv += cf[icol][jcol] * jamp_sv[jcol];
        // OLD implementation: why is this not slower? maybe compiler does not compute imaginary part of "ztemp_sv*cxconj(jamp_sv[icol])"?
        //deltaMEs += cxreal( ztemp_sv * cxconj( jamp_sv[icol] ) ) / denom[icol];
        // NEW implementation: keep this even if (surprisingly) it is not faster! it is clearer and easier for tensor core offload anyway...
        // Rewrite the quadratic form (A-iB)(M)(A+iB) as AMA - iBMA + iBMA + BMB = AMA + BMB!
        deltaMEs += ( cxreal( ztemp_sv ) * cxreal( jamp_sv[icol] ) + cximag( ztemp_sv ) * cximag( jamp_sv[icol] ) ) / denom[icol];
      }

      // *** STORE THE RESULTS ***

      // Store the leading color flows for choice of color
      // (NB: jamp2_sv must be an array of fptype_sv)
      // for( int icol = 0; icol < ncolor; icol++ )
      // jamp2_sv[0][icol] += cxreal( jamp_sv[icol]*cxconj( jamp_sv[icol] ) );

      // NB: calculate_wavefunctions ADDS |M|^2 for a given ihel to the running sum of |M|^2 over helicities for the given event(s)
      // FIXME: assume process.nprocesses == 1 for the moment (eventually: need a loop over processes here?)
      allMEs[ievt] += deltaMEs;
    }
    mgDebug( 1, __FUNCTION__ );
    return;
  }

  //--------------------------------------------------------------------------

  CPPProcess::CPPProcess( int numiterations,
                          int ngpublocks,
                          int ngputhreads,
                          bool verbose,
                          bool debug )
    : m_numiterations( numiterations )
    , m_ngpublocks( ngpublocks )
    , m_ngputhreads( ngputhreads )
    , m_verbose( verbose )
    , m_debug( debug )
    , m_pars( 0 )
    , m_masses()
    , m_tHel {
      {-1, -1, -1, -1, -1, -1, -1},
      {-1, -1, -1, -1, -1, -1, 1},
      {-1, -1, -1, -1, -1, 1, -1},
      {-1, -1, -1, -1, -1, 1, 1},
      {-1, -1, -1, -1, 1, -1, -1},
      {-1, -1, -1, -1, 1, -1, 1},
      {-1, -1, -1, -1, 1, 1, -1},
      {-1, -1, -1, -1, 1, 1, 1},
      {-1, -1, -1, 1, -1, -1, -1},
      {-1, -1, -1, 1, -1, -1, 1},
      {-1, -1, -1, 1, -1, 1, -1},
      {-1, -1, -1, 1, -1, 1, 1},
      {-1, -1, -1, 1, 1, -1, -1},
      {-1, -1, -1, 1, 1, -1, 1},
      {-1, -1, -1, 1, 1, 1, -1},
      {-1, -1, -1, 1, 1, 1, 1},
      {-1, -1, 1, -1, -1, -1, -1},
      {-1, -1, 1, -1, -1, -1, 1},
      {-1, -1, 1, -1, -1, 1, -1},
      {-1, -1, 1, -1, -1, 1, 1},
      {-1, -1, 1, -1, 1, -1, -1},
      {-1, -1, 1, -1, 1, -1, 1},
      {-1, -1, 1, -1, 1, 1, -1},
      {-1, -1, 1, -1, 1, 1, 1},
      {-1, -1, 1, 1, -1, -1, -1},
      {-1, -1, 1, 1, -1, -1, 1},
      {-1, -1, 1, 1, -1, 1, -1},
      {-1, -1, 1, 1, -1, 1, 1},
      {-1, -1, 1, 1, 1, -1, -1},
      {-1, -1, 1, 1, 1, -1, 1},
      {-1, -1, 1, 1, 1, 1, -1},
      {-1, -1, 1, 1, 1, 1, 1},
      {-1, 1, -1, -1, -1, -1, -1},
      {-1, 1, -1, -1, -1, -1, 1},
      {-1, 1, -1, -1, -1, 1, -1},
      {-1, 1, -1, -1, -1, 1, 1},
      {-1, 1, -1, -1, 1, -1, -1},
      {-1, 1, -1, -1, 1, -1, 1},
      {-1, 1, -1, -1, 1, 1, -1},
      {-1, 1, -1, -1, 1, 1, 1},
      {-1, 1, -1, 1, -1, -1, -1},
      {-1, 1, -1, 1, -1, -1, 1},
      {-1, 1, -1, 1, -1, 1, -1},
      {-1, 1, -1, 1, -1, 1, 1},
      {-1, 1, -1, 1, 1, -1, -1},
      {-1, 1, -1, 1, 1, -1, 1},
      {-1, 1, -1, 1, 1, 1, -1},
      {-1, 1, -1, 1, 1, 1, 1},
      {-1, 1, 1, -1, -1, -1, -1},
      {-1, 1, 1, -1, -1, -1, 1},
      {-1, 1, 1, -1, -1, 1, -1},
      {-1, 1, 1, -1, -1, 1, 1},
      {-1, 1, 1, -1, 1, -1, -1},
      {-1, 1, 1, -1, 1, -1, 1},
      {-1, 1, 1, -1, 1, 1, -1},
      {-1, 1, 1, -1, 1, 1, 1},
      {-1, 1, 1, 1, -1, -1, -1},
      {-1, 1, 1, 1, -1, -1, 1},
      {-1, 1, 1, 1, -1, 1, -1},
      {-1, 1, 1, 1, -1, 1, 1},
      {-1, 1, 1, 1, 1, -1, -1},
      {-1, 1, 1, 1, 1, -1, 1},
      {-1, 1, 1, 1, 1, 1, -1},
      {-1, 1, 1, 1, 1, 1, 1},
      {1, -1, -1, -1, -1, -1, -1},
      {1, -1, -1, -1, -1, -1, 1},
      {1, -1, -1, -1, -1, 1, -1},
      {1, -1, -1, -1, -1, 1, 1},
      {1, -1, -1, -1, 1, -1, -1},
      {1, -1, -1, -1, 1, -1, 1},
      {1, -1, -1, -1, 1, 1, -1},
      {1, -1, -1, -1, 1, 1, 1},
      {1, -1, -1, 1, -1, -1, -1},
      {1, -1, -1, 1, -1, -1, 1},
      {1, -1, -1, 1, -1, 1, -1},
      {1, -1, -1, 1, -1, 1, 1},
      {1, -1, -1, 1, 1, -1, -1},
      {1, -1, -1, 1, 1, -1, 1},
      {1, -1, -1, 1, 1, 1, -1},
      {1, -1, -1, 1, 1, 1, 1},
      {1, -1, 1, -1, -1, -1, -1},
      {1, -1, 1, -1, -1, -1, 1},
      {1, -1, 1, -1, -1, 1, -1},
      {1, -1, 1, -1, -1, 1, 1},
      {1, -1, 1, -1, 1, -1, -1},
      {1, -1, 1, -1, 1, -1, 1},
      {1, -1, 1, -1, 1, 1, -1},
      {1, -1, 1, -1, 1, 1, 1},
      {1, -1, 1, 1, -1, -1, -1},
      {1, -1, 1, 1, -1, -1, 1},
      {1, -1, 1, 1, -1, 1, -1},
      {1, -1, 1, 1, -1, 1, 1},
      {1, -1, 1, 1, 1, -1, -1},
      {1, -1, 1, 1, 1, -1, 1},
      {1, -1, 1, 1, 1, 1, -1},
      {1, -1, 1, 1, 1, 1, 1},
      {1, 1, -1, -1, -1, -1, -1},
      {1, 1, -1, -1, -1, -1, 1},
      {1, 1, -1, -1, -1, 1, -1},
      {1, 1, -1, -1, -1, 1, 1},
      {1, 1, -1, -1, 1, -1, -1},
      {1, 1, -1, -1, 1, -1, 1},
      {1, 1, -1, -1, 1, 1, -1},
      {1, 1, -1, -1, 1, 1, 1},
      {1, 1, -1, 1, -1, -1, -1},
      {1, 1, -1, 1, -1, -1, 1},
      {1, 1, -1, 1, -1, 1, -1},
      {1, 1, -1, 1, -1, 1, 1},
      {1, 1, -1, 1, 1, -1, -1},
      {1, 1, -1, 1, 1, -1, 1},
      {1, 1, -1, 1, 1, 1, -1},
      {1, 1, -1, 1, 1, 1, 1},
      {1, 1, 1, -1, -1, -1, -1},
      {1, 1, 1, -1, -1, -1, 1},
      {1, 1, 1, -1, -1, 1, -1},
      {1, 1, 1, -1, -1, 1, 1},
      {1, 1, 1, -1, 1, -1, -1},
      {1, 1, 1, -1, 1, -1, 1},
      {1, 1, 1, -1, 1, 1, -1},
      {1, 1, 1, -1, 1, 1, 1},
      {1, 1, 1, 1, -1, -1, -1},
      {1, 1, 1, 1, -1, -1, 1},
      {1, 1, 1, 1, -1, 1, -1},
      {1, 1, 1, 1, -1, 1, 1},
      {1, 1, 1, 1, 1, -1, -1},
      {1, 1, 1, 1, 1, -1, 1},
      {1, 1, 1, 1, 1, 1, -1},
      {1, 1, 1, 1, 1, 1, 1}}
  {
  }

  //--------------------------------------------------------------------------

  CPPProcess::~CPPProcess() {}

  //--------------------------------------------------------------------------

  // Initialize process (with parameters read from user cards)
  void CPPProcess::initProc( const std::string& param_card_name )
  {
    // Instantiate the model class and set parameters that stay fixed during run
    m_pars = Parameters_sm::getInstance();
    SLHAReader slha( param_card_name, m_verbose );
    m_pars->setIndependentParameters( slha );
    m_pars->setIndependentCouplings();
    m_pars->setDependentParameters();
    m_pars->setDependentCouplings();
    if ( m_verbose )
    {
      m_pars->printIndependentParameters();
      m_pars->printIndependentCouplings();
      m_pars->printDependentParameters();
      m_pars->printDependentCouplings();
    }
    // Set external particle masses for this matrix element
    m_masses.push_back( m_pars->ZERO );
    m_masses.push_back( m_pars->ZERO );
    m_masses.push_back( m_pars->mdl_MT );
    m_masses.push_back( m_pars->mdl_MT );
    m_masses.push_back( m_pars->ZERO );
    m_masses.push_back( m_pars->ZERO );
    m_masses.push_back( m_pars->ZERO );
    // Read physics parameters like masses and couplings from user configuration files (static: initialize once)
    m_tIPC[0] = cxmake( m_pars->GC_10 );
m_tIPC[1] = cxmake( m_pars->GC_11 );
m_tIPC[2] = cxmake( m_pars->GC_12 );
m_tIPD[0] = (fptype)m_pars->mdl_MT;
m_tIPD[1] = (fptype)m_pars->mdl_WT;

  }

  //--------------------------------------------------------------------------
  // Define pointer accessors
  const short* CPPProcess::get_tHel_ptr() const {return &(**m_tHel);}

  cxtype* CPPProcess::get_tIPC_ptr() {return m_tIPC;}
  const cxtype* CPPProcess::get_tIPC_ptr() const {return m_tIPC;}

  fptype* CPPProcess::get_tIPD_ptr() {return m_tIPD;}
  const fptype* CPPProcess::get_tIPD_ptr() const {return m_tIPD;}

  //--------------------------------------------------------------------------

  SYCL_EXTERNAL
  void sigmaKin_getGoodHel( const fptype* __restrict__ allmomenta, // input: momenta[nevt*npar*4]
                            fptype* allMEs,           // output: allMEs[nevt], |M|^2 final_avg_over_helicities
                            bool* isGoodHel,          // output: isGoodHel[ncomb] - device array
                            const size_t ievt,
                            const short* __restrict__ cHel,
                            const fptype* __restrict__ cIPC,
                            const fptype* __restrict__ cIPD
                            )
  {
    // FIXME: assume process.nprocesses == 1 for the moment (eventually: need a loop over processes here?)
    fptype allMEsLast = 0;
    for ( int ihel = 0; ihel < ncomb; ihel++ )
    {
      // NB: calculate_wavefunctions ADDS |M|^2 for a given ihel to the running sum of |M|^2 over helicities for the given event(s)
      calculate_wavefunctions( ihel, allmomenta, allMEs, ievt, cHel, cIPC, cIPD );
      if ( allMEs[ievt] != allMEsLast )
      {
        //if ( !isGoodHel[ihel] ) std::cout << "sigmaKin_getGoodHel ihel=" << ihel << " TRUE" << std::endl;
        isGoodHel[ihel] = true;
      }
      allMEsLast = allMEs[ievt]; // running sum up to helicity ihel for event ievt
    }
  }

  //--------------------------------------------------------------------------

  int sigmaKin_setGoodHel( const bool* isGoodHel, int* goodHel ) // input: isGoodHel[ncomb] - host array
  {
    int nGoodHel = 0; // FIXME: assume process.nprocesses == 1 for the moment (eventually nGoodHel[nprocesses]?)
    for ( int ihel = 0; ihel < ncomb; ihel++ )
    {
      //std::cout << "sigmaKin_setGoodHel ihel=" << ihel << ( isGoodHel[ihel] ? " true" : " false" ) << std::endl;
      if ( isGoodHel[ihel] )
      {
        //goodHel[nGoodHel[0]] = ihel; // FIXME: assume process.nprocesses == 1 for the moment
        //nGoodHel[0]++; // FIXME: assume process.nprocesses == 1 for the moment
        goodHel[nGoodHel] = ihel;
        nGoodHel++;
      }
    }
    return nGoodHel;
  }

  //--------------------------------------------------------------------------
  // Evaluate |M|^2, part independent of incoming flavour
  // FIXME: assume process.nprocesses == 1 (eventually: allMEs[nevt] -> allMEs[nevt*nprocesses]?)

  SYCL_EXTERNAL
  void sigmaKin( const fptype* __restrict__ allmomenta, // input: momenta[nevt*npar*4]
                 fptype* allMEs,           // output: allMEs[nevt], |M|^2 final_avg_over_helicities
                 size_t ievt,
                 const short* __restrict__ cHel,
                 const fptype* __restrict__ cIPC,
                 const fptype* __restrict__ cIPD,
                 const int* __restrict__ cNGoodHel,
                 const int* __restrict__ cGoodHel
                 )
  {
    mgDebugInitialise();

    // Denominators: spins, colors and identical particles
    const int denominators = 1536; // FIXME: assume process.nprocesses == 1 for the moment (eventually denominators[nprocesses]?)

    // Set the parameters which change event by event
    // Need to discuss this with Stefan
    //m_pars->setDependentParameters();
    //m_pars->setDependentCouplings();

    // Start sigmaKin_lines
    // PART 0 - INITIALISATION (before calculate_wavefunctions)
    // Reset the "matrix elements" - running sums of |M|^2 over helicities for the given event
    // FIXME: assume process.nprocesses == 1 for the moment (eventually: need a loop over processes here?)
    allMEs[ievt] = 0;

    // PART 1 - HELICITY LOOP: CALCULATE WAVEFUNCTIONS
    // (in both CUDA and C++, using precomputed good helicities)
    // FIXME: assume process.nprocesses == 1 for the moment (eventually: need a loop over processes here?)
    for ( int ighel = 0; ighel < cNGoodHel[0]; ighel++ )
    {
      const int ihel = cGoodHel[ighel];
      calculate_wavefunctions( ihel, allmomenta, allMEs, ievt, cHel, cIPC, cIPD );
    }

    // PART 2 - FINALISATION (after calculate_wavefunctions)
    // Get the final |M|^2 as an average over helicities/colors of the running sum of |M|^2 over helicities for the given event
    // [NB 'sum over final spins, average over initial spins', eg see
    // https://www.uzh.ch/cmsssl/physik/dam/jcr:2e24b7b1-f4d7-4160-817e-47b13dbf1d7c/Handout_4_2016-UZH.pdf]
    // FIXME: assume process.nprocesses == 1 for the moment (eventually: need a loop over processes here?)
    allMEs[ievt] /= (fptype)denominators;
    mgDebugFinalise();
  }

  //--------------------------------------------------------------------------

} // end namespace

//==========================================================================

