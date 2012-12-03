#include <fstream>
#include <iostream>
#include <string>

#include "json/json.h"
#include "json/reader.h"

void OpenJsonRedisDump(const std::string &filename,
                       std::string *contents) {
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
  OpenJsonRedisDump("src/dump.dat", &json_doc);

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

  // Get the value of the member of root named 'encoding', return 'UTF-8' if
  // there is no such member.
  std::string encoding = root.get("encoding", "UTF-8" ).asString();
  // Get the value of the member of root named 'encoding', return a 'null' value
  // if there is no such member.
  const Json::Value plugins = root["plug-ins"];
  // for ( int index = 0; index < plugins.size(); ++index )  // Iterates over the
  //                                                         // sequence elements.
  //   loadPlugIn( plugins[index].asString() );

  return 0;
}
