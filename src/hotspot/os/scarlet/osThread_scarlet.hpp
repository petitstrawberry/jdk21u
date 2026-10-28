/* Copyright (c) 2026, Scarlet contributors. SPDX-License-Identifier: GPL-2.0-only */
#ifndef OS_SCARLET_OSTHREAD_SCARLET_HPP
#define OS_SCARLET_OSTHREAD_SCARLET_HPP
private:
  typedef pid_t thread_id_t;
  pthread_t _pthread_id;
  Monitor* _startThread_lock;
  int _thread_type;
public:
  int thread_type() const { return _thread_type; }
  void set_thread_type(int type) { _thread_type = type; }
  pthread_t pthread_id() const { return _pthread_id; }
  void set_pthread_id(pthread_t id) { _pthread_id = id; }
  Monitor* startThread_lock() const { return _startThread_lock; }
#ifndef PRODUCT
  intptr_t thread_identifier() const { return (intptr_t)_pthread_id; }
#endif
private:
  void pd_initialize();
  void pd_destroy();
#endif
