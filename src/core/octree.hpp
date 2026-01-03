
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
                       unsigned long long int pidBufferSize );


      // Accessors //
      Particle_Cloud<PrecT>* getParticleCloudPointer() const { return m_particleCloudPtr; }
      unsigned long long int getPidBufferSize() const { return m_pidBufferSize; }

      unsigned long long int* getPidBufferPointer() const { return m_pidBuffer; }
      unsigned long long int getPidTmpBufferPointer() const { return m_pidTmpBuffer; }
      
      char* getOctantIdxBuffer() const { return m_octantIdxBuffer; }

      Octant* getRootOctant() const { return m_rootOctant; }


      // Methods //
      Octant* generateRoot();
      void stripTree();

    
      // Misc //
      ~Octree();

    private:
      // Attributes //
      Particle_Cloud<PrecT>* m_particleCloudPtr;
      unsigned long long int m_pidBufferSize;

      unsigned long long int* m_pidBuffer;
      unsigned long long int* m_pidTmpBuffer;

      char* m_octantIdxBuffer;

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
              Vector<PrecT> minCorner, Vector<PrecT> maxCorner );
    
      // Accessors //
      Octree<PrecT>* getOctree() const { return m_octree; }
      Octant<PrecT>* getParent() const { return m_parent; }
      Octant<Prect>** getChildrenArray() const { return m_childrenArray; }

      unsigned long long int getMinPidIdx() const { return m_minPidIdx; }
  
      unsigned long long int getMaxPidIdx() const { return m_maxPidIdx; }

      Vector<PrecT> getMinCorner() const { return m_minCorner; }
      Vector<PrecT> getMaxCorner() const { return m_maxCorner; }

      Vector<PrecT> getCentre() const { return m_centre; }

      PrecT getNetMass() const { return m_netMass; }
      Vector<PrecT> getCentreOfMass() const { return m_centreOfMass; }
      

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
      bool m_isParent;

      unsigned long long int m_minPidIdx;
      unsigned long long int m_maxPidIdx;

      Vector<PrecT> m_minCorner;
      Vector<PrecT> m_maxCorner;

      Vector<PrecT> m_centre;

      PrecT m_netMass;
      Vector<PrecT> m_centreOfMass;

  
      // Methods //
      unsigned long long int getChildMinPidIdx( char octantIdx );
      unsigned long long int getChildMaxPidIdx( char octantIdx );

      Vector<PrecT> getChildMinCorner( char octantIdx );
      Vector<PrecT> getChildMaxCorner( char octantIdx );
  };

}

#include "octree.tpp"

#endif
