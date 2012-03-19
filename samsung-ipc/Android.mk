ifneq ($(TARGET_IPC_LIB),)
LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := libsamsung-ipc
LOCAL_MODULE_TAGS := optional

LOCAL_CFLAGS := $(TARGET_IPC_LIB_CFLAGS)

LOCAL_SRC_FILES := \
    ipc.c \
    ipc_util.c \
    util.c \
    rfs.c \
    gen.c \
    gprs.c \
    misc.c \
    net.c \
    sec.c

LOCAL_C_INCLUDES := \
    external/openssl/include \
    $(LOCAL_PATH)/include

LOCAL_SHARED_LIBRARIES := libutils libcrypto
LOCAL_STATIC_LIBRARIES := $(TARGET_IPC_LIB)

include $(BUILD_STATIC_LIBRARY)

#include $(call all-makefiles-under,$(LOCAL_PATH))

endif
