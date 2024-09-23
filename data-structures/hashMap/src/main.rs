use std::fmt::Debug;
use std::cmp::PartialEq;

const INITIAL_CAPACITY: usize = 11;

pub struct HashTable<K, V> {
    buckets: Vec<Vec<(K, V, bool)>>, // (Key, Value, bool para deleted flag)
    capacity: usize,
}

pub trait HashHEHE {
    // http://www.cse.yorku.ca/~oz/hash.html
    fn hash(&self) -> usize;
}

impl HashHEHE for String {
    fn hash(&self) -> usize {
        let mut result: usize = 5381;
        for c in self.bytes() {
            result = ((result << 5).wrapping_add(result)).wrapping_add(c.into());
        }
        result
    }
}

impl<K, V> HashTable<K, V>
where
    K: Clone + Debug + HashHEHE + PartialEq,
    V: Clone + Debug,
{
    pub fn new() -> Self {
        Self {
            buckets: vec![Vec::new(); INITIAL_CAPACITY],
            capacity: INITIAL_CAPACITY,
        }
    }

    fn extend_mem(&mut self) {
        self.capacity *= 2;
        let mut new_buckets = vec![Vec::new(); self.capacity];
        for bucket in &self.buckets {
            for (key, value, _) in bucket {
                let index = key.hash() % self.capacity;
                new_buckets[index].push((key.clone(), value.clone(), false));
            }
        }
        self.buckets = new_buckets;
    }

    pub fn insert(&mut self, key: K, value: V) {
        if self.buckets.len() >= self.capacity / 2 {
            self.extend_mem();
        }
        let index = self.get_index(&key);
        let bucket = &mut self.buckets[index];
        for (k, v, deleted) in bucket.iter_mut() {
            if *k == key {
                if *deleted {
                    *deleted = false;
                }
                *v = value;
                return;
            }
        }
        bucket.push((key, value, false));
    }

    pub fn get_all(&self) {
        for (i, bucket) in self.buckets.iter().enumerate() {
            for (key, value, deleted) in bucket {
                if !*deleted {
                    println!("Bucket {}: Key: {:?}, Value: {:?}", i, key, value);
                }
            }
        }
    }

    pub fn get_by_key(&self, key: &K) -> Option<&V> {
        let index = self.get_index(key);
        for (k, v, deleted) in &self.buckets[index] {
            if *k == *key && !*deleted {
                return Some(v);
            }
        }
        None
    }

    fn get_index(&self, key: &K) -> usize {
        key.hash() % self.capacity
    }

    pub fn get_mut(&mut self, key: &K) -> Option<&mut V> {
        let index = self.get_index(key);
        for (k, v, deleted) in &mut self.buckets[index] {
            if *k == *key && !*deleted {
                return Some(v);
            }
        }
        None
    }

}

fn main() {
    let mut table = HashTable::<String, String>::new();
    table.insert("eu".to_string(), "minha muie".to_string());
    table.insert("hehe".to_string(), "chicrete".to_string());

    table.get_all();

    if let Some(value) = table.get_by_key(&"key1".to_string()) {
        println!("Found: {}", value);
    }

    table.get_all();
}

// ================= TEST ================================
#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_basic_insertion() {
        let mut table = HashTable::<String, String>::new();
        table.insert("key1".to_string(), "value1".to_string());
        table.insert("key2".to_string(), "value2".to_string());

        assert_eq!(table.get_by_key(&"key1".to_string()), Some(&"value1".to_string()));
        assert_eq!(table.get_by_key(&"key2".to_string()), Some(&"value2".to_string()));
    }

    #[test]
    fn test_update_value() {
        let mut table = HashTable::<String, String>::new();
        table.insert("key1".to_string(), "value1".to_string());
        assert_eq!(table.get_by_key(&"key1".to_string()), Some(&"value1".to_string()));

        // Update the value for the existing key
        table.insert("key1".to_string(), "updated_value".to_string());
        assert_eq!(table.get_by_key(&"key1".to_string()), Some(&"updated_value".to_string()));
    }

    #[test]
    fn test_deleted_flag_handling() {
        let mut table = HashTable::<String, String>::new();
        table.insert("key1".to_string(), "value1".to_string());

        // Mimic the deletion by setting the deleted flag in a custom way
        let index = table.get_index(&"key1".to_string());
        if let Some((_, _, deleted)) = table.buckets[index].get_mut(0) {
            *deleted = true;
        }

        // Now, key1 should not be retrievable
        assert_eq!(table.get_by_key(&"key1".to_string()), None);

        // Reinsert the same key and value, it should behave as a new entry
        table.insert("key1".to_string(), "new_value".to_string());
        assert_eq!(table.get_by_key(&"key1".to_string()), Some(&"new_value".to_string()));
    }

    #[test]
    fn test_capacity_expansion() {
        let mut table = HashTable::<String, String>::new();
        let initial_capacity = table.capacity;

        // Insert elements to trigger a capacity expansion
        for i in 0..(initial_capacity / 2 + 1) {
            table.insert(format!("key{}", i), format!("value{}", i));
        }

        // Check that the capacity has been increased
        assert!(table.capacity > initial_capacity);

        // Ensure all values are still present after expansion
        for i in 0..(initial_capacity / 2 + 1) {
            assert_eq!(table.get_by_key(&format!("key{}", i)), Some(&format!("value{}", i)));
        }
    }

    #[test]
    fn test_get_mut() {
        let mut table = HashTable::<String, String>::new();
        table.insert("key1".to_string(), "value1".to_string());

        // Get mutable reference and modify the value
        if let Some(value) = table.get_mut(&"key1".to_string()) {
            *value = "mutated_value".to_string();
        }

        // Ensure the value has been updated
        assert_eq!(table.get_by_key(&"key1".to_string()), Some(&"mutated_value".to_string()));
    }
}

