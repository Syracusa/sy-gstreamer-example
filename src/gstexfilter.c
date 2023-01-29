#include "gstexfilter.h"

G_DEFINE_TYPE(GstExFilter, gst_ex_filter, GST_TYPE_ELEMENT);

GST_ELEMENT_REGISTER_DEFINE(ex_filter, "ex-filter", GST_RANK_NONE, GST_TYPE_EX_FILTER);


static GstStaticPadTemplate src_template = GST_STATIC_PAD_TEMPLATE("src",
                                                                   GST_PAD_SRC,
                                                                   GST_PAD_ALWAYS,
                                                                   GST_STATIC_CAPS_ANY);


static GstStaticPadTemplate sink_template = GST_STATIC_PAD_TEMPLATE("sink",
                                                                    GST_PAD_SINK,
                                                                    GST_PAD_ALWAYS,
                                                                    GST_STATIC_CAPS_ANY);

static GstFlowReturn gst_ex_filter_chain(GstPad *pad,
                                         GstObject *parent,
                                         GstBuffer *buf);

static void
gst_ex_filter_class_init(GstExFilterClass *klass)
{
    GST_DEBUG("gst_ex_filter_class_init() called");
    GObjectClass *gobject_class = (GObjectClass *)klass;
    GstElementClass *gstelement_class = (GstElementClass *)klass;

    (void)gobject_class;

    gst_element_class_add_static_pad_template(gstelement_class, &src_template);
    gst_element_class_add_static_pad_template(gstelement_class, &sink_template);


    gst_element_class_set_static_metadata(gstelement_class,
                                          "Basics sink element example",
                                          "N/A",
                                          "N/A",
                                          "N/A");

}

static void
gst_ex_filter_init(GstExFilter *ex_filter)
{
    GST_LOG_OBJECT(ex_filter, "gst_ex_filter_init() called");
    ex_filter->sinkpad = gst_pad_new_from_static_template(
        &sink_template, "sink");
    ex_filter->srcpad = gst_pad_new_from_static_template(
        &src_template, "src");

    gst_pad_set_chain_function(ex_filter->sinkpad, gst_ex_filter_chain);

    gst_element_add_pad(GST_ELEMENT(ex_filter), ex_filter->sinkpad);
    gst_element_add_pad(GST_ELEMENT(ex_filter), ex_filter->srcpad);
}

static GstFlowReturn gst_ex_filter_chain(GstPad *pad,
                                         GstObject *parent,
                                         GstBuffer *buf)
{
    GstExFilter *ex_filter = GST_EX_FILTER(parent);

    GstMapInfo info;
    if (!gst_buffer_map(buf, &info, GST_MAP_READWRITE))
    {
        GST_ERROR_OBJECT(ex_filter, "Can't mapping buffer\n");
        return GST_FLOW_ERROR;
    }

    g_print("%lu bytes filtered\n", info.size);

    gst_buffer_unmap (buf, &info);

    return gst_pad_push(ex_filter->srcpad, buf);
}