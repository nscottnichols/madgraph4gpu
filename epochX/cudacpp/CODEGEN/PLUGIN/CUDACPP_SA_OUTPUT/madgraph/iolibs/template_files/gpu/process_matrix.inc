
      // *** COLOR ALGEBRA BELOW ***
      // (This method used to be called %(process_class_name)s::matrix_%(proc_name)s(%(matrix_args)s)?)
%(color_matrix_lines)s

      // Sum and square the color flows to get the matrix element
      // (compute |M|^2 by squaring |M|, taking into account colours)
      fptype_sv deltaMEs = { 0 }; // all zeros https://en.cppreference.com/w/c/language/array_initialization#Notes
      for( int icol = 0; icol < ncolor; icol++ )
      {
        cxtype_sv ztemp_sv = cxzero_sv();
        for( int jcol = 0; jcol < ncolor; jcol++ )
          ztemp_sv += cf[icol][jcol] * jamp_sv[jcol];
        deltaMEs += cxreal( ztemp_sv * cxconj( jamp_sv[icol] ) ) / denom[icol];
      }

      // *** STORE THE RESULTS ***

      // Store the leading color flows for choice of color
      // (NB: jamp2_sv must be an array of fptype_sv)
      // for( int icol = 0; icol < ncolor; icol++ )
      // jamp2_sv[0][icol] += cxreal( jamp_sv[icol]*cxconj( jamp_sv[icol] ) );

      // NB: calculate_wavefunctions ADDS |M|^2 for a given ihel to the running sum of |M|^2 over helicities for the given event(s)
      // FIXME: assume process.nprocesses == 1 for the moment (eventually: need a loop over processes here?)
#ifdef __CUDACC__
      const int ievt = blockDim.x * blockIdx.x + threadIdx.x; // index of event (thread) in grid
      allMEs[ievt] += deltaMEs;
      //if ( cNGoodHel > 0 ) printf( "calculate_wavefunction: %%6d %%2d %%f\n", ievt, ihel, allMEs[ievt] );
#else
#ifdef MGONGPU_CPPSIMD
      if( isAligned_allMEs )
      {
        *reinterpret_cast<fptype_sv*>( &( allMEs[ipagV * neppV] ) ) += deltaMEs;
      }
      else
      {
        for( int ieppV = 0; ieppV < neppV; ieppV++ )
          allMEs[ipagV * neppV + ieppV] += deltaMEs[ieppV];
      }
      //if ( cNGoodHel > 0 )
      //  for ( int ieppV=0; ieppV<neppV; ieppV++ )
      //    printf( "calculate_wavefunction: %%6d %%2d %%f\n", ipagV*neppV+ieppV, ihel, allMEs[ipagV][ieppV] );
#else
      allMEs[ipagV] += deltaMEs;
      //if ( cNGoodHel > 0 ) printf( "calculate_wavefunction: %%6d %%2d %%f\n", ipagV, ihel, allMEs[ipagV] );
#endif
#endif
    }
    mgDebug( 1, __FUNCTION__ );
    return;
  }