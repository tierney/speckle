SUBDIRS = lib_json .

bin_PROGRAMS = entrupy_main

entrupy_main_SOURCES = main.cc
entrupy_main_LDADD = lib_json/libjson.la
entrupy_main_CXXFLAGS = -I$(top_srcdir)/include
