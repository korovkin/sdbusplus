/*
 * Copyright (c) 2023 NVIDIA Corporation
 *
 * Licensed under the Apache License Version 2.0 with LLVM Exceptions
 * (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 *
 *   https://llvm.org/LICENSE.txt
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

#include "__meta.hpp"

namespace stdexec
{
template <class _Fn, class... _Ts>
    requires __nothrow_callable<_Fn, _Ts...>
struct __scope_guard;

template <class _Fn>
struct __scope_guard<_Fn>
{
    [[no_unique_address]] _Fn __fn_;
    [[no_unique_address]] __immovable __hidden_{};
    bool __dismissed_{false};

    ~__scope_guard()
    {
        if (!__dismissed_)
            ((_Fn &&) __fn_)();
    }

    void __dismiss() noexcept
    {
        __dismissed_ = true;
    }
};

template <class _Fn, class _T0>
struct __scope_guard<_Fn, _T0>
{
    [[no_unique_address]] _Fn __fn_;
    [[no_unique_address]] _T0 __t0_;
    [[no_unique_address]] __immovable __hidden_{};

    bool __dismissed_{false};

    void __dismiss() noexcept
    {
        __dismissed_ = true;
    }

    ~__scope_guard()
    {
        if (!__dismissed_)
            ((_Fn &&) __fn_)((_T0 &&) __t0_);
    }
};

template <class _Fn, class _T0, class _T1>
struct __scope_guard<_Fn, _T0, _T1>
{
    [[no_unique_address]] _Fn __fn_;
    [[no_unique_address]] _T0 __t0_;
    [[no_unique_address]] _T1 __t1_;
    [[no_unique_address]] __immovable __hidden_{};

    bool __dismissed_{false};

    void __dismiss() noexcept
    {
        __dismissed_ = true;
    }

    ~__scope_guard()
    {
        if (!__dismissed_)
            ((_Fn &&) __fn_)((_T0 &&) __t0_, (_T1 &&) __t1_);
    }
};

template <class _Fn, class _T0, class _T1, class _T2>
struct __scope_guard<_Fn, _T0, _T1, _T2>
{
    [[no_unique_address]] _Fn __fn_;
    [[no_unique_address]] _T0 __t0_;
    [[no_unique_address]] _T1 __t1_;
    [[no_unique_address]] _T2 __t2_;
    [[no_unique_address]] __immovable __hidden_{};

    bool __dismissed_{false};

    void __dismiss() noexcept
    {
        __dismissed_ = true;
    }

    ~__scope_guard()
    {
        if (!__dismissed_)
            ((_Fn &&) __fn_)((_T0 &&) __t0_, (_T1 &&) __t1_, (_T2 &&) __t2_);
    }
};

template <class _Fn, class... _Ts>
__scope_guard(_Fn, _Ts...) -> __scope_guard<_Fn, _Ts...>;
} // namespace stdexec
