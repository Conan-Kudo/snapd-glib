include $(top_srcdir)/glib-tap.mk

test_programs = \
	test-glib

if COMPILE_SNAPD_QT
test_programs += test-qt
endif

test_glib_SOURCES = test-glib.c mock-snapd.c mock-snapd.h
test_glib_CFLAGS = -g $(WARN_CFLAGS) \
	$(SNAPD_CFLAGS) \
	-I$(top_srcdir)
test_glib_LDADD = $(top_builddir)/snapd-glib/libsnapd-glib.la $(SNAPD_LIBS)

test_qt_SOURCES = test-qt.cpp test-qt.h mock-snapd.c mock-snapd.h
nodist_test_qt_SOURCES = test-qt_moc.cpp
test_qt_CPPFLAGS = -g $(WARN_CFLAGS) \
	-fPIC \
	$(SNAPD_CFLAGS) \
	$(SNAPD_QT_CFLAGS) \
	-I$(top_srcdir)/snapd-qt
test_qt_CXXFLAGS = --std=c++11
test_qt_LDADD = $(top_builddir)/snapd-glib/libsnapd-glib.la $(top_builddir)/snapd-qt/libsnapd-qt.la $(SNAPD_LIBS) $(SNAPD_QT_LIBS)

test-qt_moc.cpp: test-qt.h
	$(AM_V_GEN) $(MOC5) $< -o $@

CLEANFILES += test-qt_moc.cpp
