/*
 * Copyright (C) 2022 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "UdfpsHandler.laurel_sprout"

#include "UdfpsHandler.h"

#include <android-base/logging.h>
#include <android-base/strings.h>
#include <cutils/properties.h>
#include <fcntl.h>
#include <hardware/hardware.h>
#include <inttypes.h>
#include <poll.h>
#include <unistd.h>

#include <fstream>
#include <thread>

#define COMMAND_NIT 10
#define PARAM_NIT_FOD 1
#define PARAM_NIT_NONE 0

#define FOD_STATUS_PATH "/sys/class/touch/tp_dev/fod_status"
#define FOD_STATUS_ON 1
#define FOD_STATUS_OFF 0

template <typename T>
static void set(const std::string& path, const T& value) {
    std::ofstream file(path);
    file << value;
}

static const char* kFodUiPaths[] = {
    "/sys/devices/platform/soc/soc:qcom,dsi-display-primary/fod_ui",
    "/sys/devices/platform/soc/soc:qcom,dsi-display/fod_ui",
};

static bool readBool(int fd) {
    char c;
    int rc;

    rc = lseek(fd, 0, SEEK_SET);
    if (rc) {
        LOG(ERROR) << "failed to seek fd, err: " << rc;
        return false;
    }

    rc = read(fd, &c, sizeof(char));
    if (rc != 1) {
        LOG(ERROR) << "failed to read bool from fd, err: " << rc;
        return false;
    }

    return c != '0';
}

class LaurelSproutUdfpsHandler : public UdfpsHandler {
   public:
    void init(fingerprint_device_t* device) {
        mDevice = device;

        std::thread([this]() {
            int fodUiFd;
            for (auto& path : kFodUiPaths) {
                fodUiFd = open(path, O_RDONLY);
                if (fodUiFd >= 0) {
                    break;
                }
            }

            if (fodUiFd < 0) {
                LOG(ERROR) << "failed to open fd, err: " << fodUiFd;
                return;
            }

            struct pollfd fodUiPoll = {
                .fd = fodUiFd,
                .events = POLLERR | POLLPRI,
                .revents = 0,
            };

            while (true) {
                int rc = poll(&fodUiPoll, 1, -1);
                if (rc < 0) {
                    LOG(ERROR) << "failed to poll fd, err: " << rc;
                    continue;
                }

                bool fodUi = readBool(fodUiFd);

                mDevice->extCmd(mDevice, COMMAND_NIT, fodUi ? PARAM_NIT_FOD : PARAM_NIT_NONE);
                if (!fodUi) {
                    set(FOD_STATUS_PATH, FOD_STATUS_OFF);
                }
            }
        }).detach();
    }

    void onFingerDown(uint32_t /*x*/, uint32_t /*y*/, float /*minor*/, float /*major*/) {
        LOG(DEBUG) << __func__;

        set(FOD_STATUS_PATH, FOD_STATUS_ON);
    }

    void onFingerUp() {
        LOG(DEBUG) << __func__;
    }

    void onAcquired(int32_t result, int32_t vendorCode) {
        LOG(DEBUG) << __func__;

        if (result == FINGERPRINT_ACQUIRED_GOOD) {
            set(FOD_STATUS_PATH, FOD_STATUS_OFF);
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
    fingerprint_device_t* mDevice;
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