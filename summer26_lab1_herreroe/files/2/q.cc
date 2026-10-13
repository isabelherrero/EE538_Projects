#include "q.h"

#include <functional>
#include <stdexcept>

VectorHashMap::VectorHashMap(std::size_t bucket_count)
    : buckets_(bucket_count == 0 ? 1 : bucket_count), size_(0) {}

bool VectorHashMap::Insert(const std::string& key, int value) {
  auto& bucket = buckets_[BucketIndex(key)];
  for (auto& entry : bucket) {
    if (entry.first == key) {
      entry.second = value;
      return false;
    }
  }

  bucket.push_back({key, value});
  ++size_;
  return true;
}

bool VectorHashMap::Contains(const std::string& key) const {
  const auto& bucket = buckets_[BucketIndex(key)];
  for (const auto& entry : bucket) {
    if (entry.first == key) {
      return true;
    }
  }
  return false;
}

int VectorHashMap::Get(const std::string& key) const {
  const auto& bucket = buckets_[BucketIndex(key)];
  for (const auto& entry : bucket) {
    if (entry.first == key) {
      return entry.second;
    }
  }
  throw std::out_of_range("key not found: " + key);
}

bool VectorHashMap::Erase(const std::string& key) {
  auto& bucket = buckets_[BucketIndex(key)];
  for (auto it = bucket.begin(); it != bucket.end(); ++it) {
    if (it->first == key) {
      bucket.erase(it);
      --size_; // added
      return true;
    }
  }
  return false;
}

std::size_t VectorHashMap::Size() const { return size_; }

bool VectorHashMap::Empty() const { return size_ == 0; }

double VectorHashMap::LoadFactor() const {
  return static_cast<double>(size_) / static_cast<double>(buckets_.size());
}

void VectorHashMap::Rehash(std::size_t new_bucket_count) {
  if (new_bucket_count == 0) {
    new_bucket_count = 1;
  }

  auto old_buckets = buckets_;
  buckets_.clear();
  buckets_.resize(new_bucket_count);
  size_ = 0;

  for (const auto& bucket : old_buckets) {
    for (const auto& entry : bucket) {
      Insert(entry.first, entry.second);
    }
  }
}

std::vector<std::vector<std::pair<std::string, int>>>
VectorHashMap::BucketsForDebug() const {
  return buckets_;
}

std::size_t VectorHashMap::BucketIndex(const std::string& key) const {
  return std::hash<std::string>{}(key) % buckets_.size();
}
