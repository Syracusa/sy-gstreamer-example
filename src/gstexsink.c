#include "gstexsink.h"

G_DEFINE_TYPE(GstExSink, gst_ex_sink, GST_TYPE_ELEMENT);

GST_ELEMENT_REGISTER_DEFINE(ex_sink, "ex-sink", GST_RANK_NONE, GST_TYPE_EX_SINK);

static GstStaticPadTemplate sink_template = GST_STATIC_PAD_TEMPLATE("sink",
                                                                    GST_PAD_SINK,
                                                                    GST_PAD_ALWAYS,
                                                                    GST_STATIC_CAPS_ANY);


static GstFlowReturn
gst_ex_sink_render(GstBaseSink *bsink, GstBuffer *buffer);

static void
gst_ex_sink_class_init(GstExSinkClass *klass)
{
  GST_DEBUG("gst_ex_sink_class_init() called");
  GObjectClass *gobject_class = (GObjectClass *)klass;
  GstElementClass *gstelement_class = (GstElementClass *)klass;
  GstBaseSinkClass *gstbasesink_class = (GstBaseSinkClass *)klass;

  (void)gobject_class;
  (void)gstelement_class;

  gst_element_class_add_static_pad_template(gstelement_class, &sink_template);

  gstbasesink_class->render = gst_ex_sink_render;

  gst_element_class_set_static_metadata(gstelement_class,
                                        "Basics sink element example",
                                        "N/A",
                                        "N/A",
                                        "N/A");

}

static void
gst_ex_sink_init(GstExSink *ex_sink)
{
  GST_LOG_OBJECT(ex_sink, "gst_ex_sink_init() called");
  ex_sink->sinkpad = gst_pad_new_from_static_template(
    &sink_template, "sink");
  gst_element_add_pad(GST_ELEMENT(ex_sink), ex_sink->sinkpad);
}

static GstFlowReturn
gst_ex_sink_render(GstBaseSink *bsink, GstBuffer *buffer)
{
  GstExSink *ex_sink = (GstExSink *)bsink;

  GstMapInfo info;
  if (!gst_buffer_map(buffer, &info, GST_MAP_READWRITE))
  {
    GST_ERROR_OBJECT(ex_sink, "Can't mapping buffer\n");
    return GST_FLOW_ERROR;
  }

  for (int i = 0; i < info.size; i++)
  {
    g_print("%x ", info.data[i]);
  }
  g_print("\n");

  return GST_FLOW_OK;
}