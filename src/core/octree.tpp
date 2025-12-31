
#ifndef CSIM_OCTREE_TPP
#define CSIM_OCTREE_TPP

#include "./structs.hpp"
#include "./pre_controls.hpp"
#include "./particle_cloud.hpp"

#include <cstdlib>

namespace CSIM::Octree {

  ///// OCTREE /////
  template <class PrecT>
  Octree<PrecT>::Octree() {
    initDefaults();
  }

  // Initialisers //
  template <class PrecT>
  void Octree<PrecT>::initialise( Particle_Cloud<PrecT>* particleCloudPointer,
                                  unsigned long long int pidBufferSize ) {
    m_particleCloudPtr = particleCloudPointer;
    m_pidBufferSize = pidBufferSize;

    m_pidBuffer = std::malloc( pidBufferSize * sizeof( unsigned long long int ) );
    m_pidTmpBuffer = std::malloc( pidBufferSize * sizeof( unsigned long long int ) );
    // TODO: Investigate collapsing into a single malloc

  }

  template <class PrecT>
  void Octree<PrecT>::initDefaults() {
    m_particleCloudPtr = nullptr;
    m_pidBuffer = nullptr;
    m_pidBufferSize = 0;

    m_pidTmpBuffer = nullptr;

    m_rootOctant = nullptr;
  }

  template <class PrecT>
  Octree<PrecT>::~Octree() {
    std::free( m_pidBuffer );
    std::free( m_pidTmpBuffer );
  }

  
  ///// OCTANT /////
  template <class PrecT>
  Octant<PrecT>::Octant( Octree* octree, Octant* parent,
                         unsigned long long int minPidIdx, unsigned long long int maxPidIdx,
                         Vector<PrecT> minCorner, Vector<PrecT>, maxCorner ) {
    m_octree = octree;
    m_parent = parent;
    
    // Detecting if root octant //
    if( parent == nullptr ) { m_isRoot = true; }
    else { m_isRoot = false; }

    for( char idx = 0; idx < 8; idx++ ) {
      m_childrenArray[ idx ] = nullptr;
    }

    m_minPidIdx = minPidIdx;
    m_maxPidIdx = maxPidIdx;

    m_minCorner = minCorner;
    m_maxCorner = maxCorner;

  }

  
  // Methods //
  template <class PrecT>
  bool Octree<PrecT>::subdivide() {
    if( ( m_maxPidIdx - m_minPidIdx ) > CSIM_OCTANT_PARTICLE_CUTOFF ) {

      PrecT halfLength = ( m_maxCorner.x - m_minCorner.x ) / 2;
      
      for( char octantIdx = 0; octantIdx < 8; octantIdx++ ) {
        m_childrenArray[ octantIdx ] = Octant( m_octree, &this, 
          

      }
    }
  }
}

#endif
