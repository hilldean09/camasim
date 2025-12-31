
#ifndef CSIM_OCTREE_TPP
#define CSIM_OCTREE_TPP

#include "./structs.hpp"
#include "./pre_controls.hpp"
#include "./particle_cloud.hpp"

namespace CSIM::Octree {

  ///// OCTREE /////
  template <class PrecT>
  Octree<PrecT>::Octree() {
    initDefaults();
  }

  // Initialisers //
  template <class PrecT>
  void Octree<PrecT>::initialise( Particle_Cloud<PrecT>* particleCloudPointer,
                                  PrecT* pidBufferPointer, unsigned long long int pidBufferSize ) {
    m_particleCloudPtr = particleCloudPointer;
    m_pidBufferPtr = pidBufferPointer;
    m_pidBufferSize = pidBufferSize;
  }

  template <class PrecT>
  void Octree<PrecT>::initDefaults() {
    m_particleCloudPtr = nullptr;
    m_pidBufferPtr = nullptr;
    m_pidBufferSize = 0;

    m_rootOctant = nullptr;
  }

  
  ///// OCTANT /////
  template <class PrecT>
  Octant<PrecT>::Octant( Octree* octree, Octant* parent,
                         unsigned long long int minPidIdx, unsigned long long int maxPidIdx,
                         Vector<PrecT> minCorner, Vector<PrecT>, maxCorner ) {
    m_Octree = octree;
    m_parent = parent;

    // Detecting if root octant //
    if( parent == nullptr ) { m_isRoot = true; }
    else { m_isRoot = false; }
    
    m_minPidIdx = minPidIdx;
    m_maxPidIdx = maxPidIdx;

    m_minCorner = minCorner;
    m_maxCorner = maxCorner;

  }
  
}

#endif
