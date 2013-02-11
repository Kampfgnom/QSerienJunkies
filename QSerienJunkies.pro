TEMPLATE = subdirs

CONFIG += ordered
SUBDIRS = src example

example.depends = src

OTHER_FILES += README.md
