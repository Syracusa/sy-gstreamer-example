#ifndef EXFILTER_H
#define EXFILTER_H

#include <gst/gst.h>

/* Element object context */
typedef struct _GstExFilter
{
  GstElement parent;
  GstPad *sinkpad;  
  GstPad *srcpad;
} GstExFilter;

/* Element class context */
typedef struct _GstExFilterClass
{
  GstElementClass parent_class;
} GstExFilterClass;

/* Standard Macros */
#define GST_TYPE_EX_FILTER (gst_ex_filter_get_type())
#define GST_EX_FILTER(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), GST_TYPE_EX_FILTER, GstExFilter))
#define GST_EX_FILTER_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass), GST_TYPE_EX_FILTER, GstExFilterClass))
#define GST_IS_EX_FILTER(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), GST_TYPE_EX_FILTER))
#define GST_IS_EX_FILTER_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass), GST_TYPE_EX_FILTER))

/* Standard type returning function */
GType gst_ex_filter_get_type(void);

GST_ELEMENT_REGISTER_DECLARE(ex_filter);

#endif