
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
      
      for( char octantIdx = 0; octantIdx < 8; octantIdx++ ) {
        m_childrenArray[ octantIdx ] = Octant( m_octree, this, 
                                               getChildMinPidIdx( octantIdx ),
                                               getChildMaxPidIdx( octantIdx ),
                                               getChildMinCorner( octantIdx ),
                                               getChildMaxCorner( octantIdx ) )
      }
    }
  }

  template <class PrecT>
  unsigned long long int Octree<PrecT>::getChildMinPidIdx( char octantIdx ) {
    /*
     * Condensed down into a single variabel declaration for better
     * parallel memory use.
     */
    unsigned long long int output = m_maxPidIdx - m_minPidIdx;

    // Assumes a CSIM_OCTANT_PARTICLE_CUTOFF value of greater than 8
    
    #if( CSIM_DEBUG == 1 )
    if( output < 8 ) { CSIM_M_DEBUG_LOG( "Octant::getChildMinPidIdx : Bounds size < 8" ); }
    #endif

    output = m_minPidIdx + ( octantIdx * 
             ( ( unsigned long long int output ) ( output / 8 ) ) );

    return output;
  }

  template <class PrecT>
  unsigned long long int Octree<PrecT>::getChildMaxPidIdx( char octantIdx ) {
    // See getChildMinPidIdx
    unsigned long long int output = m_maxPidIdx - m_minPidIdx;

    #if( CSIM_DEBUG == 1 )
    if( output < 8 ) { CSIM_M_DEBUG_LOG( "Octant::getChildMinPidIdx : Bounds size < 8" ); }
    #endif

    if( octantIdx != 8 ) {
      output = m_minPidIdx + ( ( octantIdx + 1 ) * 
               ( ( unsigned long long int output ) ( output / 8 ) ) );
    }
    else {
      // Guaranteeing proper coverage
      output = m_maxPidIdx;
    }

    return output;
  }

  template <class PrecT>
  Vector<PrecT> Octree<PrecT>::getChildMinCorner( char octantIdx ) {
    Vector<PrecT> output = m_minCorner;
    PrecT halfLength = ( m_maxCorner.x - m_minCorner.x ) / 2;

    // Afforeded by octant indexing structure
    if( octantIdx >= 4 ) {
      output.x += halfLength;
      octantIdx -= 4;
    }
    if( octantIdx >= 2 ) {
      output.y += halfLength;
      octantIdx -= 2:
    }
    if( octantIdx >= 1 ) {
      output.z += halfLength;
      octantIdx -= 1:

  }

  template <class PrecT>
  Vector<PrecT> Octree<PrecT>::getChildMaxCorner( char octantIdx ) {
    Vector<PrecT> output = m_maxCorner;
    PrecT halfLength = ( m_maxCorner.x - m_minCorner.x ) / 2;

    // Afforeded by octant indexing structure
    if( octantIdx >= 4 ) {
      octantIdx -= 4;
    }
    else {
      output.x -= halfLength;
    }

    if( octantIdx >= 2 ) {
      octantIdx -= 2:
    }
    else {
      output.y -= halfLength;
    }

    if( octantIdx >= 1 ) {
      octantIdx -= 1:
    }
    else {
      output.z -= halfLength;
    }

  }

}

#endif
