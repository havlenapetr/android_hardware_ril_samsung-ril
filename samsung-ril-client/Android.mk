LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../include

LOCAL_MODULE := libsamsungril-client
LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES := samsung-ril-client.c

LOCAL_SHARED_LIBRARIES := liblog libcutils

include $(BUILD_SHARED_LIBRARY)
