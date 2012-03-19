LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := ipc-modemctrl

LOCAL_MODULE_TAGS := optional
                                                                                                                                                                                                                                                                                                                        
ifeq ($(DEBUG),true)
    LOCAL_CFLAGS += -DDEBUG
    LOCAL_CFLAGS += -DLOG_STDOUT
endif

LOCAL_CFLAGS := $(TARGET_IPC_LIB_CFLAGS)
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../include

LOCAL_SRC_FILES := modemctrl.c

LOCAL_STATIC_LIBRARIES := libsamsung-ipc
LOCAL_SHARED_LIBRARIES := libutils

include $(BUILD_EXECUTABLE)
