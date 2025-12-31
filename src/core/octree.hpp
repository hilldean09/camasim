
#ifndef CSIM_OCTREE_HPP
#define CSIM_OCTREE_HPP

#include "./pre_controls.hpp"
#include "./structs.hpp"
#include "./particle_cloud.hpp"

namespace CSIM::Octree {
  
  template <class PrecT>
  class Octree {
    public:
      // Constructor //
      Octree();

      
      // Initialisers //
      void initialise( Particle_Cloud<PrecT> particleCloudPointer,
                       PrecT* pidBufferPtr, unsigned long long int pidBufferSize );


      // Accessors //
      Particle_Cloud<PrecT>* getParticleCloudPointer() { return m_particleCloudPtr; }
      unsigned long long int* getPidBufferPointer() { return m_pidBufferPtr; }
      unsigned long long int getPidBufferSize() { return m_pidBufferSize; }

      Octant* getRootOctant() { return m_rootOctant; }


      // Methods //
      void stripTree();

    
      // Misc //
      ~Octree();

    private:
      // Attributes //
      Particle_Cloud<PrecT>* m_particleCloudPtr;
      unsigned long long int* m_pidBufferPtr;
      unsigned long long int m_pidBufferSize;

      Octant* m_rootOctant;
      
      // Initialisers //
      void initDefaults();

  };

  /*
   * The Octant class is not meant for wide public use, hence
   * it's non-standard structure.
   */
  template <class PrecT>
  class Octant {
    public:
      // Constructuors //
      Octant( Octree* octree, Octant* parent,
              unsigned long long int minPidIdx, unsigned long long int maxPidIdx,
              Vector<PrecT> minCorner, Vector<PrecT>, maxCorner );

    
      // Accessors //
      Octant** getChildrenArray() { return m_childrenArray; }

      unsigned long long int getMinPidIdx() { return m_minPidIdx; }
      unsigned long long int getMaxPidIdx() { return m_maxPidIdx; }

      Vector<PrecT> getMinCorner() { return m_minCorner; }
      Vector<PrecT> getMaxCorner() { return m_maxCorner; }

      PrecT getNetMass() { return m_netMass; }
      Vector<PrecT> getCentreOfMass() { return m_centreOfMass; }
      

      // Methods //
      bool subdivide();
    

      // Misc //
      ~Octant();


    private:
      // Attributes //
      Octree* m_octree;
      Octant* m_parent;
      Octant* m_childrenArray[ 8 ];
      bool m_isRoot;

      unsigned long long int m_minPidIdx;
      unsigned long long int m_maxPidIdx;

      Vector<PrecT> m_minCorner;
      Vector<PrecT> m_maxCorner;

      PrecT m_netMass;
      Vector<PrecT> m_centreOfMass;
  };

}

#include "octree.tpp"

#endif
