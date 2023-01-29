#!/bin/bash

# This folder is not searched by gst-env when finding plugin
# So just copy plugin into random 
cp builddir/libgstex.so ../gstreamer/builddir/subprojects/gst-plugins-good/gst/spectrum/