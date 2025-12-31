
#ifndef CSIM_OCTREE_HPP
#define CSIM_OCTREE_HPP

#include "./pre_controls.hpp"
#include "./structs.hpp"

namespace CSIM::Octree {
  
  template <class PrecT>
  class Octree {
    public:

    private:
      // Attributes //
      unsigned long long int* m_pidBufferPtr;
      unsigned long long int m_pidBufferSize;

      Octant* m_rootOctant;
  };

  template <class PrecT>
  class Octant {
    public:

    private:
      // Attributes //
      unsigned long long int m_minPidIdx;
      unsigned long long int m_maxPidIdx;

      Octant* m_parent;
      Octant** m_childrenArray;

      Vector<PrecT> m_minCorner;
      Vector<PrecT> m_maxCorner;

      PrecT m_netMass;
      Vector<PrecT> m_centreOfMass;
  };

}

#include "octree.tpp"

#endif
