/*
 * Copyright (C) 2022 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "UdfpsHandler.laurel_sprout"

#include "UdfpsHandler.h"

#include <android-base/logging.h>
#include <fcntl.h>
#include <poll.h>
#include <thread>
#include <unistd.h>
#include <android-base/strings.h>
#include <cutils/properties.h>
#include <hardware/hardware.h>
#include <inttypes.h>
#include <fstream>

#define COMMAND_NIT 10
#define PARAM_NIT_FOD 1
#define PARAM_NIT_NONE 0

#define FOD_STATUS_PATH "/sys/class/touch/tp_dev/fod_status"
#define FOD_STATUS_ON 1
#define FOD_STATUS_OFF 0

#define DISPPARAM_PATH "/sys/class/drm/card0-DSI-1/disp_param"
#define DISPPARAM_HBM_FOD_ON "0x1d20FE0"
#define DISPPARAM_HBM_FOD_OFF "0x20f0F20"

template <typename T>
static void set(const std::string& path, const T& value) {
    std::ofstream file(path);
    file << value;
}

class LaurelSproutUdfpsHandler : public UdfpsHandler {
  public:
    void init(fingerprint_device_t *device) {
        mDevice = device;
    }

    void onFingerDown(uint32_t /*x*/, uint32_t /*y*/, float /*minor*/, float /*major*/) {
        LOG(DEBUG) << __func__;

        set(FOD_STATUS_PATH, FOD_STATUS_ON);
        set(DISPPARAM_PATH, DISPPARAM_HBM_FOD_ON);
        mDevice->extCmd(mDevice, COMMAND_NIT, PARAM_NIT_FOD);
    }

    void onFingerUp() {
        LOG(DEBUG) << __func__;

        set(FOD_STATUS_PATH, FOD_STATUS_OFF);
        set(DISPPARAM_PATH, DISPPARAM_HBM_FOD_OFF);
        mDevice->extCmd(mDevice, COMMAND_NIT, PARAM_NIT_NONE);
    }
    
    void onAcquired(int32_t result, int32_t vendorCode) {
        LOG(DEBUG) << __func__;

        if (result == FINGERPRINT_ACQUIRED_GOOD) {
            set(FOD_STATUS_PATH, FOD_STATUS_OFF);
            set(DISPPARAM_PATH, DISPPARAM_HBM_FOD_OFF);
        } else if (vendorCode == 21 || vendorCode == 23) {
            /*
             * vendorCode = 21 waiting for fingerprint authentication
             * vendorCode = 23 waiting for fingerprint enroll
             */
            set(FOD_STATUS_PATH, FOD_STATUS_ON);
        }
    }

    void preEnroll() {
        LOG(DEBUG) << __func__;

        mDevice->pre_enroll(mDevice);
    }

    void enroll() {
        LOG(DEBUG) << __func__;
    }

    void postEnroll() {
        LOG(DEBUG) << __func__;

        onFingerUp();
        mDevice->post_enroll(mDevice);
    }

    void cancel() {
        LOG(DEBUG) << __func__;
        
        mDevice->cancel(mDevice);
    }

  private:
    fingerprint_device_t *mDevice;
};

static UdfpsHandler* create() {
    return new LaurelSproutUdfpsHandler();
}

static void destroy(UdfpsHandler* handler) {
    delete handler;
}

extern "C" UdfpsHandlerFactory UDFPS_HANDLER_FACTORY = {
    .create = create,
    .destroy = destroy,
};