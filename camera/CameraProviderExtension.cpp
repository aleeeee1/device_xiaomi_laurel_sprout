/*
 * Copyright (C) 2024 LibreMobileOS Foundation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "CameraProviderExtension.laurel_sprout"
#define LOG_NDEBUG 0
#define LOG_NIDEBUG 0
#define LOG_NDDEBUG 0

#include "CameraProviderExtension.h"

#include <fstream>
#include <android-base/logging.h>
#include <cstring>

#define TORCH_BRIGHTNESS "brightness"
#define TOGGLE_SWITCH "/sys/devices/platform/soc/1c40000.qcom,spmi/spmi-0/spmi0-03/1c40000.qcom,spmi:qcom,pmi632@3:qcom,leds@d300/leds/led:switch_0/brightness"

static std::string kTorchLedPath = "/sys/devices/platform/soc/1c40000.qcom,spmi/spmi-0/spmi0-03/1c40000.qcom,spmi:qcom,pmi632@3:qcom,leds@d300/leds/led:torch_0";

/**
 * Write value to path and close file.
 */
template <typename T>
static void set(const std::string& path, const T& value) {
    std::ofstream file(path);
    if (!file) {
        LOG(ERROR) << "Failed to open " << path << " for writing" << strerror(errno);
        return;
    }
    file << value;
    if (file.fail()) {
        LOG(ERROR) << "Failed to write value " << value << " to " << path;
    } else {
        LOG(INFO) << "Wrote value " << value << " to " << path;
    }
}

/**
 * Read value from the path and close file.
 */
template <typename T>
static T get(const std::string& path, const T& def) {
    std::ifstream file(path);
    T result;

    if (!file) {
        LOG(ERROR) << "Failed to open " << path << " for reading, returning default " << def;
        return def;
    }

    file >> result;
    if (file.fail()) {
        LOG(ERROR) << "Failed to read value from " << path << ", returning default " << def;
        return def;
    }

    LOG(INFO) << "Read value " << result << " from " << path;
    return result;
}

bool supportsTorchStrengthControlExt() {
    LOG(INFO) << "supportsTorchStrengthControlExt() called: returning true";
    return true;
}

bool supportsSetTorchModeExt() {
    LOG(INFO) << "supportsSetTorchModeExt() called: returning false";
    return false;
}

int32_t getTorchDefaultStrengthLevelExt() {
    int32_t level = 80;
    LOG(INFO) << "getTorchDefaultStrengthLevelExt() called: returning " << level;
    return level;
}

int32_t getTorchMaxStrengthLevelExt() {
    int32_t maxLevel = 200;
    LOG(INFO) << "getTorchMaxStrengthLevelExt() called: returning " << maxLevel;
    return maxLevel;
}

int32_t getTorchStrengthLevelExt() {
    auto node = kTorchLedPath + "/" + TORCH_BRIGHTNESS;
    LOG(INFO) << "getTorchStrengthLevelExt() reading from " << node;
    int32_t level = get(node, 0);
    LOG(INFO) << "Current torch strength level: " << level;
    return level;
}

void setTorchStrengthLevelExt(int32_t torchStrength, bool enabled) {
    LOG(INFO) << "setTorchStrengthLevelExt() called with strength=" << torchStrength << ", enabled=" << enabled;

    LOG(DEBUG) << "Disabling toggle switch first";
    set(TOGGLE_SWITCH, 0);

    auto node = kTorchLedPath + "/" + TORCH_BRIGHTNESS;
    LOG(DEBUG) << "Setting brightness to " << torchStrength << " at " << node;
    set(node, torchStrength);

    if (enabled) {
        LOG(DEBUG) << "Re-enabling toggle switch";
        set(TOGGLE_SWITCH, 1);
    } else {
        LOG(DEBUG) << "Torch is not enabled, toggle remains off";
    }
}

void setTorchModeExt(bool enabled) {
    LOG(INFO) << "setTorchModeExt() called with enabled=" << enabled;
    int32_t strength = getTorchDefaultStrengthLevelExt();
    setTorchStrengthLevelExt(enabled ? strength : 0, enabled);
}