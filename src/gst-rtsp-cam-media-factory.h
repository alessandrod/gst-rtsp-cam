/* GStreamer
 * Copyright (C) 2010 Alessandro Decina <alessandro.d@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include <gst/gst.h>
#include <gst/rtsp-server/rtsp-media-factory.h>

#ifndef __GST_RTSP_CAM_MEDIA_FACTORY_H__
#define __GST_RTSP_CAM_MEDIA_FACTORY_H__

G_BEGIN_DECLS

/* types for the media factory */
#define GST_TYPE_RTSP_CAM_MEDIA_FACTORY              (gst_rtsp_cam_media_factory_get_type ())
#define GST_IS_RTSP_CAM_MEDIA_FACTORY(obj)           (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GST_TYPE_RTSP_CAM_MEDIA_FACTORY))
#define GST_IS_RTSP_CAM_MEDIA_FACTORY_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), GST_TYPE_RTSP_CAM_MEDIA_FACTORY))
#define GST_RTSP_CAM_MEDIA_FACTORY_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), GST_TYPE_RTSP_CAM_MEDIA_FACTORY, GstRTSPCamMediaFactoryClass))
#define GST_RTSP_CAM_MEDIA_FACTORY(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), GST_TYPE_RTSP_CAM_MEDIA_FACTORY, GstRTSPCamMediaFactory))
#define GST_RTSP_CAM_MEDIA_FACTORY_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), GST_TYPE_RTSP_CAM_MEDIA_FACTORY, GstRTSPCamMediaFactoryClass))
#define GST_RTSP_CAM_MEDIA_FACTORY_CAST(obj)         ((GstRTSPCamMediaFactory*)(obj))
#define GST_RTSP_CAM_MEDIA_FACTORY_CLASS_CAST(klass) ((GstRTSPCamMediaFactoryClass*)(klass))

typedef struct _GstRTSPCamMediaFactory GstRTSPCamMediaFactory;
typedef struct _GstRTSPCamMediaFactoryClass GstRTSPCamMediaFactoryClass;

struct _GstRTSPCamMediaFactory {
  GstRTSPMediaFactory factory;

  gboolean video;
  gboolean audio;

  gchar *video_device;
  gint video_width;
  gint video_height;
  gint fps_n;
  gint fps_d;
  gchar *video_codec;

  gchar *audio_device;
  gchar *audio_codec;
};

struct _GstRTSPCamMediaFactoryClass {
  GstRTSPMediaFactoryClass klass;
};

GType gst_rtsp_cam_media_factory_get_type (void);

GstRTSPCamMediaFactory * gst_rtsp_cam_media_factory_new ();

G_END_DECLS

#endif /* __GST_RTSP_CAM_MEDIA_FACTORY_H__ */
