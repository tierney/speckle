SUBDIRS = lib_json .

bin_PROGRAMS = speckle_main

speckle_main_SOURCES = main.cc stl_util.h leveldb_util.h
speckle_main_LDFLAGS = -L$(top_builddir)/leveldb-1.7.0

speckle_main_LDADD = lib_json/libjson.la -lleveldb -lpthread

speckle_main_CXXFLAGS = -I$(top_srcdir)/include
speckle_main_CXXFLAGS += -I$(top_srcdir)/leveldb-1.7.0/include

bin_PROGRAMS += query_main
query_main_SOURCES = query_main.cc stl_util.h leveldb_util.h
query_main_LDFLAGS = -L$(top_builddir)/leveldb-1.7.0

query_main_LDADD = lib_json/libjson.la -lleveldb -lpthread

query_main_CXXFLAGS = -I$(top_srcdir)/include
query_main_CXXFLAGS += -I$(top_srcdir)/leveldb-1.7.0/include
