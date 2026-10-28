/* Copyright (c) 2026, Scarlet contributors. SPDX-License-Identifier: GPL-2.0-only */
#include "memory/allocation.inline.hpp"
#include "runtime/mutexLocker.hpp"
#include "runtime/osThread.hpp"
void OSThread::pd_initialize() {
  _thread_id = 0;
  _pthread_id = 0;
  _thread_type = 0;
  _startThread_lock = new Monitor(Mutex::event, "startThread_lock");
}
void OSThread::pd_destroy() { delete _startThread_lock; }
