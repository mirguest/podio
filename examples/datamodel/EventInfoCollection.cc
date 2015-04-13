// standard includes
#include <stdexcept>


#include "EventInfoCollection.h"

EventInfoCollection::EventInfoCollection() : m_collectionID(0), m_entries() ,m_refCollections(nullptr), m_data(new EventInfoDataContainer() ) {
  
}

const EventInfo EventInfoCollection::operator[](int index) const {
  return EventInfo(m_entries[index]);
}

int  EventInfoCollection::size() const {
  return m_entries.size();
}

EventInfo EventInfoCollection::create(){
  auto entry = new EventInfoEntry();
  m_entries.emplace_back(entry);

  entry->id = {int(m_entries.size()-1),m_collectionID};
  return EventInfo(entry);
}

void EventInfoCollection::clear(){
  m_data->clear();
  for (auto& entry : m_entries) { delete entry; }
  m_entries.clear();

}

void EventInfoCollection::prepareForWrite(){
  int index = 0;
  auto size = m_entries.size();
  m_data->reserve(size);
  for (auto& entry : m_entries) {m_data->push_back(entry->data); }
  if (m_refCollections != nullptr) {
    for (auto& pointer : (*m_refCollections)) {pointer->clear(); }
  }
  
  for(int i=0, size = m_data->size(); i != size; ++i){
  
  }

}

void EventInfoCollection::prepareAfterRead(){
  int index = 0;
  for (auto& data : *m_data){
    auto entry = new EventInfoEntry({index,m_collectionID}, data);
    
    m_entries.emplace_back(entry);
    ++index;
  }
}

bool EventInfoCollection::setReferences(albers::Registry* registry){
  
  return true; //TODO: check success
}

void EventInfoCollection::push_back(EventInfo object){
    int size = m_entries.size();
    auto entry = object.m_entry;
    if (entry->id.index == albers::ObjectID::untracked) {
        entry->id = {size,m_collectionID};
        m_entries.push_back(entry);
    } else {
      throw std::invalid_argument( "Cannot add an object to collection that is already owned by another collection." );

    }
}

void EventInfoCollection::setBuffer(void* address){
  m_data = static_cast<EventInfoDataContainer*>(address);
}


const EventInfo EventInfoCollectionIterator::operator* () const {
  m_object.m_entry = (*m_collection)[m_index];
  return m_object;
}

const EventInfo* EventInfoCollectionIterator::operator-> () const {
    m_object.m_entry = (*m_collection)[m_index];
    return &m_object;
}

const EventInfoCollectionIterator& EventInfoCollectionIterator::operator++() const {
  ++m_index;
 return *this;
}
