#include "q.h"

#include <functional>
#include <stdexcept>

namespace {

std::size_t NormalizeBucketCount(std::size_t bucket_count) {
  return bucket_count == 0 ? 1 : bucket_count;
}

}

VectorHashMap::VectorHashMap(std::size_t bucket_count)
    : buckets_(NormalizeBucketCount(bucket_count)) {}

bool VectorHashMap::Insert(const std::string& key, int value) {
  auto& bucket = buckets_[BucketIndex(key)];

  for (auto& entry : bucket) {
    if (entry.first == key) {
      entry.second = value;
      return false;
    }
  }

  bucket.emplace_back(key, value);
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
  throw std::out_of_range("key not found");
}

bool VectorHashMap::Erase(const std::string& key) {
  auto& bucket = buckets_[BucketIndex(key)];

  for (auto it = bucket.begin(); it != bucket.end(); ++it) {
    if (it->first == key) {
      bucket.erase(it);
      --size_;
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
  std::vector<std::vector<std::pair<std::string, int>>> new_buckets(
      NormalizeBucketCount(new_bucket_count));

  for (const auto& bucket : buckets_) {
    for (const auto& entry : bucket) {
      std::size_t new_index =
          std::hash<std::string>{}(entry.first) % new_buckets.size();
      new_buckets[new_index].push_back(entry);
    }
  }

  buckets_ = std::move(new_buckets);
}

std::vector<std::vector<std::pair<std::string, int>>>
VectorHashMap::BucketsForDebug() const {
  return buckets_;
}

std::size_t VectorHashMap::BucketIndex(const std::string& key) const {
  return std::hash<std::string>{}(key) % buckets_.size();
}