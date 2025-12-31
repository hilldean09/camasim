
#ifndef CSIM_OCTREE_HPP
#define CSIM_OCTREE_HPP

#include "./pre_controls.hpp"
#include "./structs.hpp"

namespace CSIM::Octree {
  
  template <class PrecT>
  class Octree {
    public:
      // Constructor //
      Octree();

      
      // Initialisers //
      void initialise( PrecT* pidBufferPtr, unsigned long long int pidBufferSize );


      // Accessors //
      unsigned long long int* getPidBufferPointer() { return m_pidBufferPtr; }
      unsigned long long int getPidBufferSize() { return m_pidBufferSize; }


      // Methods //
      void generateTree();
      void stripTree();

    
      // Misc //
      ~Octree();

    private:
      // Attributes //
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

      
      // Methods //
      void generateChildren();
    
      PrecT getNetMass() { return m_netMass; }
      Vector<PrecT> getCentreOfMass() { return m_centreOfMass; }


      // Misc //
      ~Octant();

    private:
      // Attributes //
      unsigned long long int m_minPidIdx;
      unsigned long long int m_maxPidIdx;

      Octree* m_octree;
      Octant* m_parent;
      Octant** m_childrenArray;
      bool m_isRoot;

      Vector<PrecT> m_minCorner;
      Vector<PrecT> m_maxCorner;

      PrecT m_netMass;
      Vector<PrecT> m_centreOfMass;
  };

}

#include "octree.tpp"

#endif
