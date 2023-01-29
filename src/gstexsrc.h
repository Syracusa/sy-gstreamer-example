#ifndef EXSRC_H
#define EXSRC_H

#include <gst/gst.h>
#include <gst/base/gstpushsrc.h>

/* Element object context */
typedef struct _GstExSrc
{
  GstPushSrc parent;
  GstPad *srcpad;
  guint16 count;
  gint64 last_poll; /* Last data poll(monotime in us) */
} GstExSrc;

/* Element class context */
typedef struct _GstExSrcClass
{
  GstPushSrcClass parent_class;
} GstExSrcClass;

/* Standard Macros */
#define GST_TYPE_EX_SRC (gst_ex_src_get_type())
#define GST_EX_SRC(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), GST_TYPE_EX_SRC, GstExSrc))
#define GST_EX_SRC_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass), GST_TYPE_EX_SRC, GstExSrcClass))
#define GST_IS_EX_SRC(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), GST_TYPE_EX_SRC))
#define GST_IS_EX_SRC_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass), GST_TYPE_EX_SRC))

/* Standard type returning function */
GType gst_ex_src_get_type(void);

/* gstelement.h:139
Declare function with name "gst_element_register_ex_src()"
*/
GST_ELEMENT_REGISTER_DECLARE(ex_src);

#endif