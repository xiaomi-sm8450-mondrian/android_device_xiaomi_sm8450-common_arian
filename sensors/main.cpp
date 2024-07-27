/*
 * Copyright (C) 2024 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "NonUiNotifier"

#include <android-base/logging.h>

#include "AodNotifier.h"
#include "NonUiNotifier.h"
#include "SensorNotifierExt.h"

int main() {
    sp<ISensorManager> manager = ISensorManager::getService();
    if (manager == nullptr) {
        LOG(ERROR) << "failed to get ISensorManager";
        return EXIT_FAILURE;
    }

    std::unique_ptr<AodNotifier> aodNotifier = std::make_unique<AodNotifier>(manager);
    std::unique_ptr<NonUiNotifier> nonUiNotifier = std::make_unique<NonUiNotifier>(manager);

    aodNotifier->activate();
    nonUiNotifier->activate();

    activateAdditionalNotifiers(manager);

    while (true) {
        // Sleep to keep the notifiers alive
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }

    // Should never reach this
    return EXIT_SUCCESS;
}
