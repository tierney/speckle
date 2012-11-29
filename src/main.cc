#include <iostream>
#include <string>

#include "json/json.h"
#include "json/reader.h"

int main(int argc, char **argv) {
  Json::Value root;   // will contains the root value after parsing.
  Json::Reader reader;

  std::string json_doc = "{\"hello\":\"world\"}";
  
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
