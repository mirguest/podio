//AUTOMATICALLY GENERATED - DO NOT EDIT

#ifndef ExampleReferencingTypeCollection_H
#define  ExampleReferencingTypeCollection_H

#include <string>
#include <vector>
#include <deque>
#include <array>

// albers specific includes
#include "albers/Registry.h"
#include "albers/CollectionBase.h"

// datamodel specific includes
#include "ExampleReferencingTypeData.h"
#include "ExampleReferencingType.h"
#include "ExampleReferencingTypeEntry.h"

typedef std::vector<ExampleReferencingTypeData> ExampleReferencingTypeDataContainer;
typedef std::deque<ExampleReferencingTypeEntry*> ExampleReferencingTypeEntryPointerContainer;

class ExampleReferencingTypeCollectionIterator {

  public:
    ExampleReferencingTypeCollectionIterator(int index, const ExampleReferencingTypeEntryPointerContainer* collection) : m_index(index), m_object(nullptr), m_collection(collection) {}

    bool operator!=(const ExampleReferencingTypeCollectionIterator& x) const {
      return m_index != x.m_index; //TODO: may not be complete
    }

    const ExampleReferencingType operator*() const;
    const ExampleReferencingType* operator->() const;
    const ExampleReferencingTypeCollectionIterator& operator++() const;

  private:
    mutable int m_index;
    mutable ExampleReferencingType m_object;
    const ExampleReferencingTypeEntryPointerContainer* m_collection;
};

/**
A Collection is identified by an ID.
*/

class ExampleReferencingTypeCollection : public albers::CollectionBase {

public:
  typedef const ExampleReferencingTypeCollectionIterator const_iterator;

  ExampleReferencingTypeCollection();
//  ExampleReferencingTypeCollection(const ExampleReferencingTypeCollection& ) = delete; // deletion doesn't work w/ ROOT IO ! :-(
//  ExampleReferencingTypeCollection(ExampleReferencingTypeVector* data, int collectionID);
  ~ExampleReferencingTypeCollection(){};

  void clear();
  /// Append a new object to the collection, and return this object.
  ExampleReferencingType create();

  /// Append a new object to the collection, and return this object.
  /// Initialized with the parameters given
  template<typename... Args>
  ExampleReferencingType create(Args&&... args);
  int size() const;

  /// Returns the object of given index
  const ExampleReferencingType operator[](int index) const;

  /// Append object to the collection
  void push_back(ExampleReferencingType object);

  void prepareForWrite();
  void prepareAfterRead();
  void setBuffer(void* address);
  bool setReferences(albers::Registry* registry);

  albers::CollRefCollection* referenceCollections() { return m_refCollections;};

  void setID(unsigned ID){m_collectionID = ID;};

  // support for the iterator protocol
  const const_iterator begin() const {
    return const_iterator(0, &m_entries);
  }
  const	const_iterator end() const {
    return const_iterator(m_entries.size(), &m_entries);
  }

  /// returns the address of the pointer to the data buffer
  void* getBufferAddress() { return (void*)&m_data;};

  /// returns the pointer to the data buffer
  std::vector<ExampleReferencingTypeData>* _getBuffer() { return m_data;};

   

private:
  int m_collectionID;
  ExampleReferencingTypeEntryPointerContainer m_entries;
  // members to handle 1-to-N-relations
  std::vector<ExampleCluster>* m_rel_Clusters; //relation buffer for r/w
  std::vector<std::vector<ExampleCluster>*> m_rel_Clusters_tmp;
 
  // members to handle streaming
  albers::CollRefCollection* m_refCollections;
  ExampleReferencingTypeDataContainer* m_data;
};

template<typename... Args>
ExampleReferencingType  ExampleReferencingTypeCollection::create(Args&&... args){
  int size = m_entries.size();
  auto entry = new ExampleReferencingTypeEntry({size,m_collectionID},{args...});
  m_entries.push_back(entry);
  return ExampleReferencingType(entry);
}



#endif
