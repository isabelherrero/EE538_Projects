#ifndef VECTOR_HASH_MAP_H
#define VECTOR_HASH_MAP_H

#include <cstddef>
#include <functional>
#include <string>
#include <utility>
#include <vector>

// Activity 2: Vector-only hash map.
//
// Implement a small hash map from std::string to int using std::vector storage.
//
// Allowed:
//   * std::vector
//   * std::pair
//   * std::string
//   * std::hash<std::string>
//
// Forbidden:
//   * std::map
//   * std::unordered_map
//   * std::list
//
// Collision strategy:
//   Use separate chaining, but each bucket must be a std::vector of key/value
//   pairs. Do not use linked lists.
//
// Behavior:
//   * A constructor argument of 0 should create 1 bucket.
//   * Insert returns true when a new key is inserted.
//   * Insert returns false when an existing key is overwritten.
//   * Get throws std::out_of_range when the key does not exist.
//   * Erase returns true when a key is removed and false when it is missing.
//   * Rehash preserves all existing key/value pairs.
//   * Rehash(0) should rebuild the map with 1 bucket.
//   * No automatic rehashing is required. Only Rehash changes bucket count.
class VectorHashMap {
 public:
  // Creates a hash map with `bucket_count` buckets.
  //
  // If `bucket_count` is 0, create exactly 1 bucket. This avoids division by
  // zero when computing `hash(key) % buckets_.size()`.
  explicit VectorHashMap(std::size_t bucket_count = 8);

  // Inserts or updates one key/value pair.
  //
  // If `key` is not already present:
  //   * store `(key, value)`
  //   * increase Size() by 1
  //   * return true
  //
  // If `key` is already present:
  //   * replace the old value with `value`
  //   * keep Size() unchanged
  //   * return false
  bool Insert(const std::string& key, int value);

  // Returns true if `key` is currently stored in the map.
  // Returns false otherwise.
  bool Contains(const std::string& key) const;

  // Returns the value associated with `key`.
  //
  // Throws std::out_of_range if `key` is not stored in the map.
  int Get(const std::string& key) const;

  // Removes `key` and its value from the map.
  //
  // If `key` is present:
  //   * remove the key/value pair
  //   * decrease Size() by 1
  //   * return true
  //
  // If `key` is missing:
  //   * leave the map unchanged
  //   * return false
  bool Erase(const std::string& key);

  // Returns the number of key/value pairs stored in the map.
  //
  // This is not the number of buckets. It is the number of entries across all
  // buckets.
  std::size_t Size() const;

  // Returns true exactly when Size() is 0.
  bool Empty() const;

  // Returns Size() divided by the number of buckets as a double.
  //
  // Example: 3 entries in 4 buckets has load factor 0.75.
  double LoadFactor() const;

  // Rebuilds the bucket array with `new_bucket_count` buckets.
  //
  // Every existing key/value pair must still be present after rehashing.
  // Because the bucket count changes, entries may move to different buckets.
  //
  // If `new_bucket_count` is 0, rebuild with exactly 1 bucket.
  //
  // Do not call Rehash automatically from Insert. In this lab, bucket count
  // changes only when this function is called directly.
  void Rehash(std::size_t new_bucket_count);

  // Exposes bucket state for tests and visualization. Production containers
  // usually avoid this, but it makes this learning lab observable.
  //
  // Return a copy of the current buckets. Each inner vector is one bucket, and
  // each pair is one stored key/value entry.
  std::vector<std::vector<std::pair<std::string, int>>> BucketsForDebug() const;

 private:
  // The outer vector is the bucket array. Each bucket stores all entries whose
  // keys hash to that bucket index.
  std::vector<std::vector<std::pair<std::string, int>>> buckets_;

  // The total number of key/value pairs stored across all buckets.
  std::size_t size_ = 0;

  // Computes the bucket index for `key`.
  //
  // Precondition: buckets_.size() is greater than 0.
  std::size_t BucketIndex(const std::string& key) const;
};

#endif  // VECTOR_HASH_MAP_H
