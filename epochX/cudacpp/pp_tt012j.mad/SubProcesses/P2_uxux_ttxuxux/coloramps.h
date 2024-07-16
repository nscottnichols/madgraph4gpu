// Copyright (C) 2020-2024 CERN and UCLouvain.
// Licensed under the GNU Lesser General Public License (version 3 or later).
// Created by: A. Valassi (Dec 2022) for the MG5aMC CUDACPP plugin.
// Further modified by: A. Valassi (2022-2024) for the MG5aMC CUDACPP plugin.

#ifndef COLORAMPS_H
#define COLORAMPS_H 1

namespace mgOnGpu
{

  __device__ constexpr bool icolamp[14][6] = {
    { false, false, false, false, true, false },
    { true, false, false, false, false, false },
    { true, false, false, false, true, false },
    { false, false, false, false, true, false },
    { true, false, false, false, false, false },
    { false, true, false, false, false, false },
    { false, false, true, false, false, false },
    { false, true, true, false, false, false },
    { false, true, false, false, false, false },
    { false, false, true, false, false, false },
    { false, false, true, false, false, false },
    { false, true, false, false, false, false },
    { true, false, false, false, false, false },
    { false, false, false, false, true, false }
  };

}
#endif // COLORAMPS_H
