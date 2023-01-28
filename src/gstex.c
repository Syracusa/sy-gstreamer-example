#include "gstexsrc.h"
#include "gstexsink.h"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

static gboolean
plugin_init (GstPlugin * plugin)
{
  gboolean ret = FALSE;

  ret |= GST_ELEMENT_REGISTER (ex_sink, plugin);
  ret |= GST_ELEMENT_REGISTER (ex_src, plugin);

  return ret;
}

GST_PLUGIN_DEFINE (GST_VERSION_MAJOR,
    GST_VERSION_MINOR,
    ex,
    "Gstreamer Example Plugin",
    plugin_init, "VERSION", "GST_LICENSE", "N/A", "GST_PACKAGE_ORIGIN")
