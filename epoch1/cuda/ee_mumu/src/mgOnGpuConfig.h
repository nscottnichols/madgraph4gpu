#ifndef MGONGPUCONFIG_H
#define MGONGPUCONFIG_H 1

// ** NB1 Throughputs (e.g. 6.8E8) are events/sec for "./gcheck.exe -p 65536 128 12"
// ** NB2 Baseline on b7g47n0004 fluctuates (probably depends on load on other VMs)

// Memory layout for momenta: AOSOA, AOS, SOA (CHOOSE ONLY ONE)
// AOSOA (ASA) layout is hardcoded: fine-tune it using the nepopR and neppM parameters below

// Choose how random numbers are generated
// If one of these macros has been set from outside with e.g. -DMGONGPU_CURAND_ONHOST, nothing happens.
#if not defined MGONGPU_CURAND_ONDEVICE and not defined MGONGPU_CURAND_ONHOST and not defined MGONGPU_COMMONRAND_ONHOST
// Curand random number generation (CHOOSE ONLY ONE)
#define MGONGPU_CURAND_ONDEVICE 1 // default (curand: CUDA on device, C++ on host)
//#define MGONGPU_CURAND_ONHOST 1 // (curand: CUDA on host, C++ on host)
//#define MGONGPU_COMMONRAND_ONHOST 1 // (common rand: CUDA on host, C++ on host)
#endif

// Memory choice for wavefunctions: registries/"local", global, shared (CHOOSE ONLY ONE)
// Local storage (registries plus spillover to local) is hardcoded: fine tune it using maxrregcount in the Makefile
// [NB: new throughputs on 1GPU/4CPU system]

// Floating point precision (CHOOSE ONLY ONE)
#define MGONGPU_FPTYPE_DOUBLE 1 // default (~6.8E8)
//#define MGONGPU_FPTYPE_FLOAT 1 // 2.4x faster (~1.64E9 against 6.8E8)

// Complex type in cuda: thrust or cucomplex (CHOOSE ONLY ONE)
#ifdef __CUDACC__
#define MGONGPU_CXTYPE_THRUST 1 // default (~6.8E8)
//#define MGONGPU_CXTYPE_CUCOMPLEX 1 // ~5% slower (6.5E8 against 6.8E8)
#endif

// Cuda nsight compute (ncu) debug: add dummy lines to ease SASS program flow navigation
#ifdef __CUDACC__
#undef MGONGPU_NSIGHT_DEBUG // default
//#define MGONGPU_NSIGHT_DEBUG 1
#endif

namespace mgOnGpu
{

  // --- Type definitions

  // Floating point type: fptype
#if defined MGONGPU_FPTYPE_DOUBLE
  typedef double fptype; // double precision (8 bytes, fp64)
#elif defined MGONGPU_FPTYPE_FLOAT
  typedef float fptype; // single precision (4 bytes, fp32)
#else
#error One of MGONGPU_FPTYPE_DOUBLE or MGONGPU_FPTYPE_FLOAT must be defined
#endif

  // --- Physics process-specific constants that are best declared at compile time

  const int np4 = 4; // the dimension of 4-momenta (E,px,py,pz)

  const int npari = 2; // #particles in the initial state (incoming): e+ e-
  const int nparf = 2; // #particles in the final state (outgoing): mu+ mu-
  const int npar = npari + nparf; // #particles in total (external): e+ e- -> mu+ mu-

  const int ncomb = 16; // #helicity combinations: 16=2(spin up/down for fermions)**4(npar)

  // --- Platform-specific software implementation details

  // Maximum number of blocks per grid
  // ** NB Some arrays of pointers will be allocated statically to fit all these blocks
  // ** (the actual memory for each block will then be allocated dynamically only for existing blocks)
  //const int nbpgMAX = 2048;

  // Maximum number of threads per block
  //const int ntpbMAX = 256; // AV Apr2021: why had I set this to 256?
  const int ntpbMAX = 1024; // NB: 512 is ok, but 1024 does fail with "too many resources requested for launch"

  // Alignment requirement for using reinterpret_cast with SIMD vectorized code
  // (using reinterpret_cast with non aligned memory may lead to segmentation faults!)
#ifndef __CUDACC__
  constexpr int cppAlign = 64; // alignment requirement for SIMD vectorization (64-byte i.e. 512-bit)
#endif

  // C++ SIMD vectorization width (this will be used to set neppV)
#ifndef __CUDACC__
#if defined __AVX512VL__
#ifdef MGONGPU_PVW512
  // "512z" AVX512 with 512 width (512-bit ie 64-byte): 8 (DOUBLE) or 16 (FLOAT)
#ifdef MGONGPU_FPTYPE_DOUBLE
#define MGONGPU_CPPSIMD 8
#else
#define MGONGPU_CPPSIMD 16
#endif
#else
  // "512y" AVX512 with 256 width (256-bit ie 32-byte): 4 (DOUBLE) or 8 (FLOAT) [gcc DEFAULT]
#ifdef MGONGPU_FPTYPE_DOUBLE
#define MGONGPU_CPPSIMD 4
#else
#define MGONGPU_CPPSIMD 8
#endif
#endif
#elif defined __AVX2__
  // "avx2" AVX2 (256-bit ie 32-byte): 4 (DOUBLE) or 8 (FLOAT) [clang DEFAULT]
#ifdef MGONGPU_FPTYPE_DOUBLE
#define MGONGPU_CPPSIMD 4
#else
#define MGONGPU_CPPSIMD 8
#endif
#elif defined __SSE4_2__
  // "sse4" SSE4.2 (128-bit ie 16-byte): 2 (DOUBLE) or 4 (FLOAT)
#ifdef MGONGPU_FPTYPE_DOUBLE
#define MGONGPU_CPPSIMD 2
#else
#define MGONGPU_CPPSIMD 4
#endif
#else
  // "none" i.e. no SIMD (*** NB: this is equivalent to AOS ***)
#undef MGONGPU_CPPSIMD
#endif
#endif

  // Number of Events Per Page in the momenta AOSOA memory layout
  // (these are all best kept as a compile-time constants: see issue #23)
#ifdef __CUDACC__
#undef MGONGPU_CPPSIMD
  // -----------------------------------------------------------------------------------------------
  // --- GPUs: neppM is best set to a power of 2 times the number of fptype's in a 32-byte cacheline
  // --- This is relevant to ensure coalesced access to momenta in global memory
  // --- Note that neppR is hardcoded and may differ from neppM and neppV on some platforms
  // -----------------------------------------------------------------------------------------------
  //const int neppM = 64/sizeof(fptype); // 2x 32-byte GPU cache lines (512 bits): 8 (DOUBLE) or 16 (FLOAT)
  const int neppM = 32/sizeof(fptype); // (DEFAULT) 32-byte GPU cache line (256 bits): 4 (DOUBLE) or 8 (FLOAT)
  //const int neppM = 1;  // *** NB: this is equivalent to AOS ***
#else
  // -----------------------------------------------------------------------------------------------
  // --- CPUs: neppM is best set equal to the number of fptype's (neppV) in a vector register
  // --- This is relevant to ensure faster access to momenta from C++ memory cache lines
  // --- However, neppM is now decoupled from neppV (issue #176) and can be separately hardcoded
  // --- In practice, neppR, neppM and neppV can now all be different
  // -----------------------------------------------------------------------------------------------
#ifdef MGONGPU_CPPSIMD
  const int neppM = MGONGPU_CPPSIMD; // (DEFAULT) neppM=neppV for optimal performance
#else
  const int neppM = 1; // (DEFAULT) neppM=neppV for optimal performance (NB: this is equivalent to AOS)
#endif
  //const int neppM = 64/sizeof(fptype); // maximum CPU vector width (512 bits): 8 (DOUBLE) or 16 (FLOAT)
  //const int neppM = 32/sizeof(fptype); // lower CPU vector width (256 bits): 4 (DOUBLE) or 8 (FLOAT)
  //const int neppM = 1; // *** NB: this is equivalent to AOS ***
#endif

  // Number of Events Per Page in the random number AOSOA memory layout
  // *** NB Different values of neppR lead to different physics results: the ***
  // *** same 1d array is generated, but it is interpreted in different ways ***
  const int neppR = 8; // HARDCODED TO GIVE ALWAYS THE SAME PHYSICS RESULTS!

}

// Expose typedefs and operators outside the namespace
using mgOnGpu::fptype;

// Cuda nsight compute (ncu) debug: add dummy lines to ease SASS program flow navigation
// Arguments (not used so far): text is __FUNCTION__, code is 0 (start) or 1 (end)
#if defined __CUDACC__ && defined MGONGPU_NSIGHT_DEBUG
#define mgDebugDeclare()                              \
  __shared__ float mgDebugCounter[mgOnGpu::ntpbMAX];
#define mgDebugInitialise()                     \
  { mgDebugCounter[threadIdx.x]=0; }
#define mgDebug( code, text )                   \
  { mgDebugCounter[threadIdx.x] += 1; }
#define mgDebugFinalise()                                               \
  { if ( blockIdx.x == 0 && threadIdx.x == 0 ) printf( "MGDEBUG: counter=%f\n", mgDebugCounter[threadIdx.x] ); }
#else
#define mgDebugDeclare()                        \
  /*noop*/
#define mgDebugInitialise()                     \
  { /*noop*/ }
#define mgDebug( code, text )                   \
  { /*noop*/ }
#define mgDebugFinalise()                       \
  { /*noop*/ }
#endif

// Define empty CUDA declaration specifiers for C++
#ifndef __CUDACC__
#define __global__
//#define __host__
#define __device__
#endif

#endif // MGONGPUCONFIG_H
