SUBDIRS = lib_json .

bin_PROGRAMS = entrupy_main

entrupy_main_SOURCES = main.cc stl_util.h leveldb_util.h
entrupy_main_LDFLAGS = -L$(top_srcdir)/leveldb-1.7.0 -lleveldb

entrupy_main_LDADD = lib_json/libjson.la 

entrupy_main_CXXFLAGS = -I$(top_srcdir)/include 
entrupy_main_CXXFLAGS += -I$(top_srcdir)/leveldb-1.7.0/include

bin_PROGRAMS += query_main
query_main_SOURCES = query_main.cc stl_util.h leveldb_util.h
query_main_LDFLAGS = -L$(top_srcdir)/leveldb-1.7.0 -lleveldb

query_main_LDADD = lib_json/libjson.la 

query_main_CXXFLAGS = -I$(top_srcdir)/include 
query_main_CXXFLAGS += -I$(top_srcdir)/leveldb-1.7.0/include
