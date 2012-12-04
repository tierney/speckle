#ifndef _LEVELDB_UTIL_H_
#define _LEVELDB_UTIL_H_

#include <string>

#include "leveldb/db.h"

class LevelDBKeys {
 public:
  static int LatestKeyId(const std::string& base, leveldb::DB* const db) {
    // Assume that @db is already opened and status is ok.
    for (int id = 0; ; id++) {
      std::string value;
      leveldb::Status status = db->Get(leveldb::ReadOptions(),
                                       CreateKey(base, id),
                                       &value);
      if (!status.ok()) {
        return id;
      }
    }
  }
  
  static std::string CreateKey(const std::string& base, int id) {
    std::string new_key(base);

    // Simple itoa.
    std::stringstream stream;
    stream << id;
    std::string new_id;
    stream >> new_id;

    new_key.append(new_id);
    return new_key;
  }
};

std::string CreateLevelDBKey(const std::string& base, leveldb::DB* const db) {
  return LevelDBKeys::CreateKey(base, LevelDBKeys::LatestKeyId(base, db));
}

#endif  // _LEVELDB_UTIL_H_
