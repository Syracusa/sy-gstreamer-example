#include "exsrc.h"

/* https://github.com/GNOME/glib/blob/main/gobject/gtype.h */
G_DEFINE_TYPE(GstExSrc, gst_ex_src, GST_TYPE_ELEMENT);
GST_ELEMENT_REGISTER_DEFINE(ex_src, "ex-src", GST_RANK_NONE, GST_TYPE_MY_FILTER);

static GstStaticPadTemplate src_template = GST_STATIC_PAD_TEMPLATE("src",
    GST_PAD_SRC,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS_ANY);

static void 
gst_ex_src_class_init(GstExSrcClass *klass)
{
    GObjectClass *gobject_class = (GObjectClass *)klass;
    GstElementClass *gstelement_class = (GstElementClass *)klass;
    GstBaseSrcClass *gstbasesrc_calss = (GObjectClass *)klass;
    GstPushSrcClass *gstpushsrc_class = (GObjectClass *)klass;

    // gst_element_class_add_static_pad_template

}

static void
gst_ex_src_init()
{

}