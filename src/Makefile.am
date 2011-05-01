bin_PROGRAMS = gst-rtsp-cam
lib_LTLIBRARIES = libgstrtspcam.la

libgstrtspcam_la_SOURCES = \
	gst-rtsp-cam-media-factory.c

libgstrtspcam_la_CFLAGS = $(GST_CFLAGS) $(GST_RTSP_SERVER_CFLAGS) -Wall -Werror
libgstrtspcam_la_LIBADD = $(GST_LIBS) $(GST_RTSP_SERVER_LIBS) -lgstinterfaces-0.10
libgstrtspcam_la_LDFLAGS = -avoid-version -no-undefined -dynamic

gst_rtsp_cam_SOURCES = \
	gst-rtsp-cam.c

gst_rtsp_cam_CFLAGS = $(GST_CFLAGS) $(GST_RTSP_SERVER_CFLAGS) -Wall -Werror
gst_rtsp_cam_LDADD = $(GST_LIBS) $(GST_RTSP_SERVER_LIBS) -lgstinterfaces-0.10 $(builddir)/libgstrtspcam.la
gst_rtsp_cam_LDFLAGS = -avoid-version -no-undefined -dynamic

noinst_HEADERS = \
	gst-rtsp-cam-media-factory.h
