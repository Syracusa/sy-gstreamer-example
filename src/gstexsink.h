#ifndef EXSINK_H
#define EXSINK_H

#include <gst/gst.h>
#include <gst/base/gstbasesink.h>

/* Element object context */
typedef struct _GstExSink
{
  GstBaseSink parent;
  GstPad *sinkpad;
} GstExSink;

/* Element class context */
typedef struct _GstExSinkClass
{
  GstBaseSinkClass parent_class;
} GstExSinkClass;

/* Standard Macros */
#define GST_TYPE_EX_SINK (gst_ex_sink_get_type())
#define GST_EX_SINK(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), GST_TYPE_EX_SINK, GstExSink))
#define GST_EX_SINK_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass), GST_TYPE_EX_SINK, GstExSinkClass))
#define GST_IS_EX_SINK(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), GST_TYPE_EX_SINK))
#define GST_IS_EX_SINK_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass), GST_TYPE_EX_SINK))

/* Standard type returning function */
GType gst_ex_sink_get_type(void);

GST_ELEMENT_REGISTER_DECLARE(ex_sink);

#endif