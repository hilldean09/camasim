
#ifndef CSIM_PARTICLE_CLOUD_TPP
#define CSIM_PARTICLE_CLOUD_TPP

#include <cstdlib>
#include <cstring>
#include <cmath>
#include <random>
#include <numbers>

#include "pre_controls.hpp"
#include "structs.hpp"
#include "./octree.hpp"
#include "cuda/csim_cuda.hpp"

namespace CSIM {
  
  // Initialisers //
  template <class PrecT>
  void Particle_Cloud<PrecT>::initialise( unsigned long long int p_number, std::default_random_engine* randomEnginePtr ) {

    initDefaults();

    initPNumber( p_number );
    initStatuses();

    initRandomEngine( randomEnginePtr );
    initAnglesDistribution();

    initPositions();
    initVelocities();
    initAccelerations();
    initForces();

    initMasses();
    initRadii();
    initPartialRestitutions();
  
    initCudaBuffers();
  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::initDefaults() {
    m_p_number = 1;
    m_randomEnginePtr  = nullptr;
    m_statuses = nullptr;

    m_positions = { nullptr, nullptr, nullptr, nullptr };
    m_velocities = { nullptr, nullptr, nullptr, nullptr };
    m_accelerations = { nullptr, nullptr, nullptr, nullptr };
    m_forces = { nullptr, nullptr, nullptr, nullptr };

    m_d_positions = nullptr;
    m_d_velocities = nullptr;
    m_d_accelerations = nullptr;
    m_d_forces = nullptr;

    m_masses = nullptr;
    m_radii = nullptr;
    m_partial_restitutions = nullptr;
  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::initPNumber( unsigned long long int p_number ) {
    m_p_number = p_number;
  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::initStatuses() {
    m_statuses = (char*) std::malloc( m_p_number * sizeof( char ) );

    // Initialising all particles to active
    for( unsigned int idx = 0; idx < m_p_number; idx++ ) {
      m_statuses[ idx ] = (char) 1;
    }
  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::initRandomEngine( std::default_random_engine* randomEnginePtr ) {
    m_randomEnginePtr = randomEnginePtr;
  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::initAnglesDistribution() {
    m_anglesDistribution = std::uniform_real_distribution<PrecT>( -2.0 * std::numbers::pi_v<PrecT>, 2.0 * std::numbers::pi_v<PrecT> );
  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::initPositions() {
    m_positions.arenaPtr = ( PrecT* ) std::malloc( 3 * m_p_number * sizeof( PrecT ) );
    
    m_positions.setPtrs( m_p_number );

    // Initialising random particle positions
    for( unsigned int idx = 0; idx < m_p_number; idx++ ) {
      generateRandomPosition( idx );
    }
  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::initVelocities() {
    m_velocities.arenaPtr = ( PrecT* ) std::malloc( 3 * m_p_number * sizeof( PrecT ) );

    m_velocities.setPtrs( m_p_number );

    // Initialising ranndom particle velocities
    for( unsigned int idx = 0; idx < m_p_number; idx++ ) {
      generateRandomVelocity( idx );
    }
  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::initAccelerations() {
    m_accelerations.arenaPtr = ( PrecT* ) std::malloc( 3 * m_p_number * sizeof( PrecT ) );

    m_accelerations.setPtrs( m_p_number );

    for( unsigned int idx = 0; idx < 3 * m_p_number; idx++ ) {
      m_accelerations.arenaPtr[ idx ] = 0;
    }
  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::initForces() {
    m_forces.arenaPtr = ( PrecT* ) std::malloc( 3 * m_p_number * sizeof( PrecT ) );

    m_forces.setPtrs( m_p_number );

    for( unsigned int idx = 0; idx < 3 * m_p_number; idx++ ) {
      m_forces.arenaPtr[ idx ] = 0;
    }
  }
  
  template <class PrecT>
  void Particle_Cloud<PrecT>::initMasses() {
    m_masses = ( PrecT* ) std::malloc( m_p_number * sizeof( PrecT ) );

    for( unsigned int idx = 0; idx < m_p_number; idx++ ) {
      generateRandomMass( idx );
    }
  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::initRadii() {
    m_radii = ( PrecT* ) std::malloc( m_p_number * sizeof( PrecT ) );

    for( unsigned int idx = 0; idx < m_p_number; idx++ ) {
      generateRandomRadius( idx );
    }
  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::initPartialRestitutions() {
    m_partial_restitutions = ( PrecT* ) std::malloc( m_p_number * sizeof( PrecT ) );

    for( unsigned int idx = 0; idx < m_p_number; idx++ ) {
      generateRandomPartialRestitution( idx );
    }
  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::generateRandomPosition( unsigned long long int idx ) {
    // Creating polar representation
    PrecT newPolar = m_anglesDistribution( *m_randomEnginePtr );
    PrecT newAzimuth = m_anglesDistribution( *m_randomEnginePtr );
    PrecT newRadius = m_radialPositionDistribution( *m_randomEnginePtr );

    Radial_Vector<PrecT> newRadialVector = { newPolar, newAzimuth, newRadius };

    // Cartesian representation
    Vector<PrecT> newVector = newRadialVector.getCartesian();

    // Assigning new values
    m_positions.x[ idx ] = newVector.x;
    m_positions.y[ idx ] = newVector.y;
    m_positions.z[ idx ] = newVector.z;
  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::generateRandomVelocity( unsigned long long int idx ) {
    // Creating polar representation
    PrecT newPolar = m_anglesDistribution( *m_randomEnginePtr );
    PrecT newAzimuth = m_anglesDistribution( *m_randomEnginePtr );
    PrecT newRadius = m_radialVelocityDistribution( *m_randomEnginePtr );

    Radial_Vector<PrecT> newRadialVector = { newPolar, newAzimuth, newRadius };

    // Cartesian representation
    Vector<PrecT> newVector = newRadialVector.getCartesian();

    // Assigning new values
    m_velocities.x[ idx ] = newVector.x;
    m_velocities.y[ idx ] = newVector.y;
    m_velocities.z[ idx ] =  newVector.z;
  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::generateRandomMass( unsigned long long int idx ) {
    // Ensuring non-negative, non-zero mass
    PrecT newMass = -1;
    while( newMass <= 0 ) {
      newMass = m_massDistribution( *m_randomEnginePtr );
    }

    m_masses[ idx ] = newMass;
  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::generateRandomRadius( unsigned long long int idx ) {
    // Ensuring non-negative, non-zero radius 
    PrecT newRadius = -1;
    while( newRadius <= 0 ) {
      newRadius = m_radiusDistribution( *m_randomEnginePtr );
    }

    m_radii[ idx ] = newRadius;
  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::generateRandomPartialRestitution( unsigned long long int idx ) {
    // Ensuring 0 - 0.5 range
    PrecT newPartialRestitution = -1;
    while( newPartialRestitution < 0 || newPartialRestitution > 0.5 ) {
      newPartialRestitution = m_partialRestitutionDistribution( *m_randomEnginePtr );
    }

    m_partial_restitutions[ idx ] = newPartialRestitution;
  }


  // Mutators //
  template <class PrecT>
  void Particle_Cloud<PrecT>::setDistribution( const char distribution, PrecT mean, PrecT standardDeviation ) {
    /* 'p' for postion, 'v' for velocity,
     * 'm' for mass. 'r' for radius, and
     * 'e' for partial restitution (elasticity).
     */
    switch( distribution ) {
      case 'p':
        m_radialPositionDistribution = std::normal_distribution<PrecT>( mean, standardDeviation );
        break;
      case 'v':
        m_radialVelocityDistribution = std::normal_distribution<PrecT>( mean, standardDeviation );
        break;
      case 'm':
        m_massDistribution = std::normal_distribution<PrecT>( mean, standardDeviation );
        break;
      case 'r':
        m_radiusDistribution = std::normal_distribution<PrecT>( mean, standardDeviation );
        break;
      case 'e':
        m_partialRestitutionDistribution = std::normal_distribution<PrecT>( mean, standardDeviation );
        break;

    }

  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::initCudaBuffers() {
    #if( CSIM_USE_CUDA == 1 )
    
    CSIM_CUDA::cu_p_allocateBuffers<PrecT>( m_d_positions, 
                          m_d_velocities,
                          m_d_accelerations,
                          m_d_forces,
                          m_p_number );

    CSIM_CUDA::cu_p_initialiseBuffers<PrecT>( m_positions, m_d_positions,
                            m_velocities, m_d_velocities,
                            m_accelerations, m_d_accelerations,
                            m_forces, m_d_forces,
                            m_p_number );

    #endif
  }

  
  // Methods //
  template <class PrecT>
  void Particle_Cloud<PrecT>::setCudaConstants( PrecT step ) {
    #if( CSIM_USE_CUDA == 1 )
    CSIM_CUDA::cu_p_setConstants( step, m_p_number );
    #endif
  }

  template <class PrecT>
  template <bool preMemcpy, bool postMemcpy>
  void Particle_Cloud<PrecT>::applyVelocity() {
    #if( CSIM_USE_CUDA == 1 )

    #if( CSIM_VERBOSITY > 3 )
    std::cout << CSIM_LOG_HEADER( "Particle_Cloud::applyVelocity" ) << "Using CUDA" << std::endl;
    #endif

    CSIM_CUDA::cu_p_applyVelocity<PrecT, preMemcpy, postMemcpy>( m_positions, m_d_positions,
                                                                 m_velocities, m_d_velocities,
                                                                 m_p_number );
    #else
    // TODO: Add CPU version
    #endif
  }

  template <class PrecT>
  template <bool preMemcpy, bool postMemcpy>
  void Particle_Cloud<PrecT>::applyAcceleration() {
    #if( CSIM_USE_CUDA == 1 )
    CSIM_CUDA::cu_p_applyAcceleration<PrecT, preMemcpy, postMemcpy>( m_velocities, m_d_velocities,
                                                                     m_accelerations, m_d_accelerations,
                                                                     m_p_number );
    #else
    // TODO: Add CPU version
    #endif
  }

  template <class PrecT>
  void Particle_Cloud<PrecT>::generateOctree( Octree::Octree<PrecT>* octreePtr ) {
    Octree::Octant<PrecT>* rootOctantPtr = octreePtr->generateRoot();
    
    #pragma omp parallel 
    {
      #pragma omp single nowait
      rec_populateOctant< false >( octreePtr, rootOctantPtr );
    }

    std::cout << std::to_string( octreePtr->getPidBufferPointer()[ 10 ] ) << std::endl; // DEBUG

    // TODO: Add centre of mass calculation
  }

  /*
   * I am aware this is a huge function, however, given the massive
   * amount of parallelism and functions, some is to reduce overhead
   */
  template <class PrecT>
  template <bool UseTempBuffer>
  void Particle_Cloud<PrecT>::rec_populateOctant( Octree::Octree<PrecT>* octreePtr, 
                                                  Octree::Octant<PrecT>* octantPtr ) {
    // Local constants
    unsigned long long int minPidIdx = octantPtr->getMinPidIdx();
    unsigned long long int maxPidIdx = octantPtr->getMinPidIdx();
    
    if( octantPtr->subdivide() == true ) {

      unsigned long long int* activePidBuffer;
      unsigned long long int* writeBuffer;

      if( UseTempBuffer == false ) {
        activePidBuffer = octreePtr->getPidBufferPointer();
        writeBuffer = octreePtr->getPidTmpBufferPointer();
      }
      else {
        activePidBuffer = octreePtr->getPidTmpBufferPointer();
        writeBuffer = octreePtr->getPidBufferPointer();
      }

      char* octantIdxBuffer = octreePtr->getOctantIdxBuffer();

      // "Local" mutables
      unsigned long long int octantIdxHistogram[ 8 ] = { 0, 0, 0, 0,
                                                         0, 0, 0, 0 };
      Octree::Octant<PrecT>** childrenArray = octantPtr->getChildrenArray();

      // Classification TODO: Contemplate OpenMP taskloop after benchmarking
      char pidIdxOctantIdx = 0;

      #pragma omp parallel for if( octantPtr->isRoot() == true )
      for( unsigned long long int pidIdx = minPidIdx;
          pidIdx < maxPidIdx;
          pidIdx++ ) {
        /* A funny naming convension here but it means to to say
        * the octantIdx of this pidIdx is [x], this is to keep 
        * consistency with the octantIdxBuffer
        */
        pidIdxOctantIdx = getOctantIdx( activePidBuffer[ pidIdx ], octantPtr->getCentre() );

        octantIdxHistogram[ ( int ) pidIdxOctantIdx ]++;
        octantIdxBuffer[ ( int ) pidIdx ] = pidIdxOctantIdx;

      }

      // Calculating write offsets, applying child bounds
      unsigned long long int octantIdxOffsets[ 8 ];
      octantIdxOffsets[ 0 ] = 0;
      childrenArray[ 0 ]->setPidIdxBounds( minPidIdx, octantIdxHistogram[ 0 ] );

      for( char octantIdx = 1; octantIdx < 8; octantIdx++ ) {
        octantIdxOffsets[ ( int ) octantIdx ] = octantIdxOffsets[ ( int ) octantIdx - 1 ] + 
                                        octantIdxHistogram[ ( int ) octantIdx - 1 ];
        
        childrenArray[ ( int ) octantIdx ]->setPidIdxBounds( minPidIdx + octantIdxOffsets [ ( int ) octantIdx ],
                                                     minPidIdx + octantIdxOffsets [ ( int ) octantIdx ] + octantIdxHistogram[ ( int ) octantIdx ] );

      }

      // Writing to writeBuffer
      unsigned long long int octantIdxLocalOffsets[ 8 ] = { 0, 0, 0, 0,
                                                            0, 0, 0, 0 };

      for( unsigned long long int pidIdx = minPidIdx;
           pidIdx < maxPidIdx;
           pidIdx++ ) {
        // Note, reusing pidIdxOctantIdx declaration from previous
        pidIdxOctantIdx = octantIdxBuffer[ pidIdx ];

        writeBuffer[ minPidIdx + octantIdxOffsets[ ( int ) pidIdxOctantIdx ] +
                     octantIdxLocalOffsets[ ( int ) pidIdxOctantIdx ] ] = activePidBuffer[ pidIdx ];

        octantIdxLocalOffsets[ ( int ) pidIdxOctantIdx ]++;

      }

      // Recursion
      CSIM::Octree::Octant<PrecT>* childOctantPtr;

      for( char octantIdx = 0; octantIdx < 8; octantIdx ++ ) {
        if( octantIdxHistogram[ ( int ) octantIdx ] > 0 ) {
          childOctantPtr = childrenArray[ ( int ) octantIdx ];

          if( UseTempBuffer == false ) {
            #pragma omp task default( none ) firstprivate( octreePtr, childOctantPtr )
            rec_populateOctant<true>( octreePtr, childOctantPtr );
          }
          else {
            #pragma omp task default( none ) firstprivate( octreePtr, childOctantPtr )
            rec_populateOctant<false>( octreePtr, childOctantPtr );
          }
        }

      }

    }
    else {
      // Ensuring up to date memory in the pid buffer
      if( UseTempBuffer == true ) {
        std::memcpy( ( void* ) octreePtr->getPidBufferPointer()[ minPidIdx ],
                     ( void* ) octreePtr->getPidTmpBufferPointer()[ minPidIdx ],
                     ( maxPidIdx - minPidIdx ) * sizeof( unsigned long long int ) );
      }

    }

  }

  template <class PrecT>
  char Particle_Cloud<PrecT>::getOctantIdx( unsigned long long int pid, Vector<PrecT> centre ) const {
    char output = 0;

    /* The bitwise OR combination operator is used to implement
     * a base-8 octant ID system
     */
    if( m_positions.x[ pid ] > centre.x ) output |= 4;
    if( m_positions.y[ pid ] > centre.y ) output |= 2;
    if( m_positions.z[ pid ] > centre.z ) output |= 1;

    return output;
  }


  // Misc //
  template <class PrecT>
  Particle_Cloud<PrecT>::~Particle_Cloud() {

    std::free( m_statuses );

    std::free( m_positions.arenaPtr );
    std::free( m_velocities.arenaPtr );
    std::free( m_accelerations.arenaPtr );
    std::free( m_forces.arenaPtr );

    std::free( m_masses );
    std::free( m_radii );
    std::free( m_partial_restitutions );

  }

}

#endif
