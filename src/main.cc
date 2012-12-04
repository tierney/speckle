// Copyright (c) 2012 Matt Tierney. All Rights Reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <assert.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "json/json.h"
#include "json/reader.h"
#include "leveldb/db.h"
#include "stl_util.h"
#include "leveldb_util.h"

void OpenJsonRedisDump(const std::string& filename,
                       std::string* contents) {
  std::ifstream fin(filename.c_str());

  fin.seekg(0, std::ios::end);   
  contents->reserve(fin.tellg());
  fin.seekg(0, std::ios::beg);

  contents->assign((std::istreambuf_iterator<char>(fin)),
                   std::istreambuf_iterator<char>());
}

int main(int argc, char **argv) {
  std::string json_doc;
  std::cout << "Reading the file." << std::endl;
  OpenJsonRedisDump("/Users/tierney/data/dump.dat", &json_doc);

  std::cout << "Attempting to parse." << std::endl;
  Json::Value root;   // will contains the root value after parsing.
  Json::Reader reader;
  
  bool parsingSuccessful = reader.parse( json_doc, root );
  if (!parsingSuccessful) {
    // report to the user the failure and their locations in the document.
    std::cout  << "Failed to parse configuration\n"
               << reader.getFormatedErrorMessages();
    return -1;
  }

  // const Json::Value::Members members = root.getMemberNames();
  // for (int i = 0; i < members.size(); i++) {
  //   std::cout << members[i] << std::endl;
  //   for (int j = 0; j < root[members[i]].size(); j++) {
  //     std::cout << " " << root[members[i]][j] << std::endl;
  //   }
  // }

  leveldb::DB* db;

  leveldb::Options options;
  options.create_if_missing = true;
  leveldb::Status status = leveldb::DB::Open(options, "/tmp/testdb", &db);
  assert(status.ok());

  const Json::Value::Members members = root.getMemberNames();
  for (int i = 0; i < members.size(); i++) {
    // std::cout << members[i] << std::endl;
    const std::string& key =  members[i];

    for (int j = 0; j < root[members[i]].size(); j++) {
      // std::cout << " " << root[members[i]][j] << std::endl;
      const std::string& value = root[members[i]][j].asString();
      const std::string new_key(CreateLevelDBKey(key, db));
      db->Put(leveldb::WriteOptions(), new_key, value);
    }
  }

  delete db;
  
  return 0;
}
