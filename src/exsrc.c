#include "exsrc.h"

/* https://github.com/GNOME/glib/blob/main/gobject/gtype.h */
G_DEFINE_TYPE(GstExSrc, gst_ex_src, GST_TYPE_ELEMENT);


#if 1
/* gstelement.h:94 
Define function with name "gst_element_register_ex_src()"
*/
GST_ELEMENT_REGISTER_DEFINE(ex_src, "ex-src", GST_RANK_NONE, GST_TYPE_EX_SRC);
#else
gboolean gst_element_register_ex_src(GstPlugin * plugin){
    return gst_element_register(plugin, "ex-src", GST_RANK_NONE, GST_TYPE_EX_SRC);
}

#endif


static GstStaticPadTemplate src_template = GST_STATIC_PAD_TEMPLATE("src",
    GST_PAD_SRC,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS_ANY);

static void 
gst_ex_src_class_init(GstExSrcClass *klass)
{
    GObjectClass *gobject_class = (GObjectClass *)klass;
    GstElementClass *gstelement_class = (GstElementClass *)klass;
    GstBaseSrcClass *gstbasesrc_calss = (GstBaseSrcClass *)klass;
    GstPushSrcClass *gstpushsrc_class = (GstPushSrcClass *)klass;

    // gst_element_class_add_static_pad_template

}

static void
gst_ex_src_init(GstExSrc *obj)
{

}