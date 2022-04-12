cmake_minimum_required(VERSION 3.18)


project (XmlConverter)


# use libxml2 library (without excessive options)
option(LIBXML2_WITH_ICONV "Add ICONV support" OFF)
option(LIBXML2_WITH_ICU "Add ICU support" OFF)
option(LIBXML2_WITH_LZMA "Add LZMA support" OFF)
option(LIBXML2_WITH_PYTHON "Build Python bindings" OFF)
option(LIBXML2_WITH_REGEXPS "Add Regular Expressions support" OFF)
option(LIBXML2_WITH_SAX1 "Add the older SAX1 interface" OFF)
option(LIBXML2_WITH_SCHEMAS "Add Relax-NG and Schemas support" OFF)
option(LIBXML2_WITH_SCHEMATRON "Add Schematron support" OFF)
option(LIBXML2_WITH_TESTS "Build tests" OFF)
option(LIBXML2_WITH_THREADS "Add multithread support" OFF)
option(LIBXML2_WITH_ZLIB "Use libz" OFF)
add_subdirectory(libxml2)

