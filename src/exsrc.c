#include "exsrc.h"

G_DEFINE_TYPE(GstExSrc, gst_ex_src, GST_TYPE_ELEMENT);

#if 1
/* Define function with name "gst_element_register_ex_src()" */
GST_ELEMENT_REGISTER_DEFINE(ex_src, "ex-src", GST_RANK_NONE, GST_TYPE_EX_SRC);
#else
gboolean gst_element_register_ex_src(GstPlugin *plugin)
{
  return gst_element_register(plugin, "ex-src", GST_RANK_NONE, GST_TYPE_EX_SRC);
}
#endif

static GstStaticPadTemplate src_template = GST_STATIC_PAD_TEMPLATE("src",
                                                                   GST_PAD_SRC,
                                                                   GST_PAD_ALWAYS,
                                                                   GST_STATIC_CAPS_ANY);


static GstFlowReturn
gst_ex_src_fill(GstPushSrc *psrc, GstBuffer *outbuf);

static void
gst_ex_src_class_init(GstExSrcClass *klass)
{
  GST_DEBUG("gst_ex_src_class_init() called");
  GObjectClass *gobject_class = (GObjectClass *)klass;
  GstElementClass *gstelement_class = (GstElementClass *)klass;
  GstBaseSrcClass *gstbasesrc_class = (GstBaseSrcClass *)klass;
  GstPushSrcClass *gstpushsrc_class = (GstPushSrcClass *)klass;

  (void)gstbasesrc_class;
  (void)gobject_class;

  gst_element_class_add_static_pad_template(gstelement_class, &src_template);

  gstpushsrc_class->fill = gst_ex_src_fill;
}

static void
gst_ex_src_init(GstExSrc *ex_src)
{
  GST_LOG_OBJECT(ex_src, "gst_ex_src_init() called");
  ex_src->count = 0;
  ex_src->last_poll = g_get_monotonic_time();
  ex_src->byte_per_ms = 1;
}

static GstFlowReturn
gst_ex_src_fill(GstPushSrc *psrc, GstBuffer *outbuf)
{
  GstExSrc *ex_src = (GstExSrc *)psrc;
  gint64 timediff = g_get_monotonic_time() - ex_src->last_poll;
  gint64 available = timediff / (ex_src->byte_per_ms * 1000);

  GstMapInfo info;
  if (!gst_buffer_map(outbuf, &info, GST_MAP_READWRITE))
  {
    GST_ERROR_OBJECT(ex_src, "Can't mapping buffer\n");
    return GST_FLOW_ERROR;
  }

  if (available < 1)
  {
    GST_LOG_OBJECT(ex_src, "No data to write\n");
    gst_buffer_resize(outbuf, 0, 0);
    return GST_FLOW_OK;
  }

  gint64 write_len;
  if (available < info.size)
    write_len = available;
  else
    write_len = info.size;

  for (int i = 0; i < write_len; i++)
  {
    info.data[i] = 0xfa;
  }
  gst_buffer_resize(outbuf, 0, write_len);
  ex_src->last_poll += write_len * (ex_src->byte_per_ms * 1000);
  GST_LOG_OBJECT(ex_src, "%ld byte filled\n", write_len);

  return GST_FLOW_OK;
}