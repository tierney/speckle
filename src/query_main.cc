// Copyright 2012 Matt Tierney. All Rights Reserved.
// BSD-Style License.

#include <assert.h>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "leveldb/db.h"
#include "leveldb_util.h"
#include "stl_util.h"

int main(int argc, char** argv) {
  // Read in the test values.

  std::ifstream fin("test.in");
  std::vector<std::string> inputs((std::istream_iterator<std::string>(fin)),
                                  std::istream_iterator<std::string>());

  leveldb::DB* db;

  leveldb::Options options;
  options.create_if_missing = true;
  leveldb::Status status = leveldb::DB::Open(options, "/tmp/testdb", &db);
  assert(status.ok());

  std::map<std::string, int> counter;
  
  for (int i = 0; i < inputs.size(); i++) {
    int highest_id = LevelDBKeys::LatestKeyId(inputs[i], db);
    for (int key_id = 0; key_id < highest_id; key_id++) {
      std::string key(LevelDBKeys::CreateKey(inputs[i], key_id));

      std::string value;
      leveldb::Status status = db->Get(leveldb::ReadOptions(), key, &value);
      assert(status.ok());
      
      if (!ContainsKey(counter, value)) {
        counter[value] = 0;
      }
      counter[value]++;
    }
  }
  std::map<std::string, int>::iterator iter = std::max_element(counter.begin(), counter.end());
  std::cout << iter->first << std::endl;
  
  delete db;
  return 0;
}
