/*
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details.
 *
 * Author: Alessandro Decina <alessandro.d@gmail.com>
 */

#include <gst/gst.h>
#include <gst/rtsp-server/rtsp-server.h>

#include "gst-rtsp-cam-media-factory.h"

static gboolean
timeout (GstRTSPServer *server, gboolean ignored)
{
  GstRTSPSessionPool *pool;

  pool = gst_rtsp_server_get_session_pool (server);
  gst_rtsp_session_pool_cleanup (pool);
  g_object_unref (pool);

  return TRUE;
}

static char *video_device = NULL;
static char *video_codec = NULL;
static int video_width = -1;
static int video_height = -1;
static int fps_n = 0;
static int fps_d = 1;
static char *audio_device = NULL;
static char *audio_codec = NULL;
static gboolean no_audio = FALSE;
static gboolean no_video = FALSE;

static const GOptionEntry option_entries[] = {
  {"video-device", 0, 0, G_OPTION_ARG_STRING, &video_device,
      "The video height", NULL},
  {"video-codec", 0, 0, G_OPTION_ARG_STRING, &video_codec,
      "The video codec", NULL},
  {"video-width", 0, 0, G_OPTION_ARG_INT, &video_width,
      "The video width", NULL},
  {"video-height", 0, 0, G_OPTION_ARG_INT, &video_height,
      "The video height", NULL},
  {"video-fps-n", 0, 0, G_OPTION_ARG_INT, &fps_n,
      "The video framerate numerator", NULL},
  {"video-fps-d", 0, 0, G_OPTION_ARG_INT, &fps_d,
      "The video framerate denominator", NULL},
  {"audio-device", 0, 0, G_OPTION_ARG_STRING, &audio_device,
      "The audio height", NULL},
  {"audio-codec", 0, 0, G_OPTION_ARG_STRING, &audio_codec,
      "The audio codec", NULL},
  {"no-audio", 0, 0, G_OPTION_ARG_NONE, &no_audio,
      "Don't stream audio", NULL},
  {"no-video", 0, 0, G_OPTION_ARG_NONE, &no_video,
      "Don't stream video", NULL},
  {NULL}
};


int
main(int argc, char **argv)
{
  GMainLoop *loop;
  GstRTSPServer *server;
  GstRTSPMediaMapping *mapping;
  GstRTSPCamMediaFactory *factory;
  gchar *name;
  GstRTSPUrl *local_url; 
  GOptionContext *ctx;
  GOptionGroup *gst_group;
  gboolean res;
  GError *error = NULL;

  g_type_init ();
  g_thread_init (NULL);

  ctx = g_option_context_new ("rtsp://host:port/path");
  g_option_context_add_main_entries (ctx, option_entries, NULL);
  gst_group = gst_init_get_option_group ();
  g_option_context_add_group (ctx, gst_group);
  res = g_option_context_parse (ctx, &argc, &argv, &error);
  g_option_context_free (ctx);

  gst_init (&argc, &argv);

  if (!res) {
    g_printerr ("command line error: %s\n", error->message);
    g_error_free (error);

    return 1;
  }

  if (argc != 2) {
    g_printerr ("missing rtsp url argument\n");

    return 1;
  }

  if (gst_rtsp_url_parse (argv[1], &local_url) != GST_RTSP_OK) {
    g_printerr ("invalid rtsp url\n");

    return 1;
  }

  loop = g_main_loop_new (NULL, FALSE);

  server = gst_rtsp_server_new ();
  gst_rtsp_server_set_port (server, local_url->port);

  name = g_strdup_printf ("rtsp-cam-factory-%s", argv[2]);
  factory = gst_rtsp_cam_media_factory_new ();
  gst_object_set_name (GST_OBJECT (factory), name);
  g_free (name);
  g_object_set (factory, "video-device", video_device,
      "video", !no_video,
      "video-width", video_width,
      "video-height", video_height,
      "video-codec", video_codec,
      "video-framerate", fps_n, fps_d,
      "audio", !no_audio,
      "audio-device", audio_device,
      "audio-codec", audio_codec,
      NULL);

  gst_rtsp_media_factory_set_shared (GST_RTSP_MEDIA_FACTORY (factory), TRUE);
  mapping = gst_rtsp_server_get_media_mapping (server);
  gst_rtsp_media_mapping_add_factory (mapping, local_url->abspath,
      GST_RTSP_MEDIA_FACTORY (factory));
  g_object_unref (mapping);

  gst_rtsp_url_free (local_url);

  gst_rtsp_server_attach (server, NULL);

  g_timeout_add_seconds (10, (GSourceFunc) timeout, server); 
  /* start serving */
  g_main_loop_run (loop);

  return 0;
}
